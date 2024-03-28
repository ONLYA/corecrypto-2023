/* Copyright (c) (2022,2023) Apple Inc. All rights reserved.
 *
 * corecrypto is licensed under Apple Inc.’s Internal Use License Agreement (which
 * is contained in the License.txt file distributed with corecrypto) and only to
 * people who accept that license. IMPORTANT:  Any license rights granted to you by
 * Apple Inc. (if any) are limited to internal use within your organization only on
 * devices and computers you own or control, for the sole purpose of verifying the
 * security characteristics and correct functioning of the Apple Software.  You may
 * not, directly or indirectly, redistribute the Apple Software or any portions thereof.
 */

#include "cche_internal.h"
#include "ccpolyzp_po2cyc_random.h"
#include "cche_util.h"

CC_PURE cc_size CCHE_ENCRYPT_ZERO_SYMMETRIC_HELPER_WORKSPACE_N(cc_size degree, cc_size nmoduli)
{
    struct ccpolyzp_po2cyc_dims dims = { .degree = (uint32_t)degree, .nmoduli = (uint32_t)nmoduli };
    return ccn_nof_size(sizeof_struct_ccpolyzp_po2cyc_block_rng_state()) +
           CC_MAX_EVAL(CCPOLYZP_PO2CYC_RANDOM_UNIFORM_WORKSPACE_N(degree) + ccpolyzp_po2cyc_nof_n(&dims),
                       CCPOLYZP_PO2CYC_RANDOM_CBD_WORKSPACE_N(degree));
}

/// @brief Symmetric encryption of zero polynomial
/// @param ws Workspace
/// @param ctext The ciphertext where to store the encrypted zero polynomial, must be allocated with
/// `cche_ciphertext_fresh_npolys()` polynomials. Note, should be cast to `cche_ciphertext_eval_t` if `evaluation_format` is
/// true.
/// @param param_ctx The parameter context where to get the polynomial context from
/// @param secret_key The secret key to use for the encryption
/// @param nmoduli The number of moduli that should be in the ciphertext context
/// @param evaluation_format If true, the ciphertext will be stored in evaluation format
/// @param seed if nonnull, then the seed used for generating `a` will be stored here
/// @param rng The base rng to use for seed generation
/// @return CCERR_OK if operation was successful
/// @details For BFV, the ciphertext is the pair of polynmomials: `(-(as + e), a)`, where `a` is uniformly random polynomial, `s`
/// is the secret key and `e` is sampled from the error distribution. For BGV, the ciphertext is the pair of polynomials `(-(as +
/// te), a)`, where `t` is the plaintext modulus If the seed pointer is nonnull, the function additionally stores the seed to
/// generate  `a`.
static int cche_encrypt_zero_symmetric_helper_ws(cc_ws_t ws,
                                                 cche_ciphertext_coeff_t ctext,
                                                 cche_param_ctx_const_t param_ctx,
                                                 cche_secret_key_const_t secret_key,
                                                 uint32_t nmoduli,
                                                 bool evaluation_format,
                                                 cche_rng_seed_t seed,
                                                 struct ccrng_state *rng)
{
    int rv = CCERR_OK;
    CC_DECL_BP_WS(ws, bp);

    cc_require_or_return(ccpolyzp_po2cyc_ctx_eq(secret_key->context, cche_param_ctx_encrypt_key_context(param_ctx)),
                         CCERR_PARAMETER);
    cc_require_or_return(nmoduli > 0 && nmoduli <= cche_param_ctx_encrypt_key_context(param_ctx)->dims.nmoduli, CCERR_PARAMETER);

    // initialize the ciphertext polynomials with a context
    ccpolyzp_po2cyc_ctx_const_t ciphertext_ctx =
        ccpolyzp_po2cyc_ctx_chain_context_const(cche_param_ctx_chain_const(param_ctx), nmoduli);
    cche_ciphertext_coeff_init(ctext, param_ctx, cche_ciphertext_fresh_npolys(), ciphertext_ctx);

    // ciphertext (c0, c1) = (-(a * s + e), a)
    // c1 = a in evaluation format
    ccpolyzp_po2cyc_t a = (ccpolyzp_po2cyc_t)cche_ciphertext_coeff_polynomial(ctext, 1);

    // randomize poly a
    if (seed) {
        rv = ccrng_generate(rng, CCPOLYZP_PO2CYC_RANDOM_RNG_SEED_SIZE, seed);
        cc_require(rv == CCERR_OK, errOut);
        ccpolyzp_po2cyc_block_rng_state_t block_rng = CCPOLYZP_PO2CYC_BLOCK_RNG_STATE_ALLOC_WS(ws);
        rv = ccpolyzp_po2cyc_block_rng_init(block_rng, (ccpolyzp_po2cyc_block_rng_seed_const_t)seed);
        cc_require(rv == CCERR_OK, errOut);
        rv = ccpolyzp_po2cyc_random_uniform_ws(ws, a, (struct ccrng_state *)block_rng);
        cc_require(rv == CCERR_OK, errOut);
    } else {
        rv = ccpolyzp_po2cyc_random_uniform_ws(ws, a, rng);
        cc_require(rv == CCERR_OK, errOut);
    }

    // randomize error polynomial
    ccpolyzp_po2cyc_coeff_t err_poly = (ccpolyzp_po2cyc_coeff_t)CCPOLYZP_PO2CYC_ALLOC_WS(ws, &ciphertext_ctx->dims);
    err_poly->context = ciphertext_ctx;
    rv = ccpolyzp_po2cyc_random_cbd_ws(ws, (ccpolyzp_po2cyc_t)err_poly, rng, CCPOLYZP_PO2CYC_RANDOM_CBD_SIGMA3_2);
    cc_require(rv == CCERR_OK, errOut);

    // If HeScheme is BGV, scale error polynomial by plaintext modulus t
    if (cche_param_ctx_he_scheme(param_ctx) == CCHE_SCHEME_BGV) {
        ccrns_int t = cche_param_ctx_plaintext_modulus(param_ctx);
        ccrns_int t_array[CCPOLYZP_PO2CYC_NMODULI_MAX] = { t };
        for (uint32_t i = 0; i < nmoduli; ++i) {
            t_array[i] = t;
        }
        ccpolyzp_po2cyc_coeff_scalar_mul_ws(ws, err_poly, err_poly, t_array);
    }

    // calculate c0 = a * s
    ccpolyzp_po2cyc_eval_t c0_eval = (ccpolyzp_po2cyc_eval_t)cche_ciphertext_coeff_polynomial(ctext, 0);
    cche_mul_poly_sk(c0_eval, (ccpolyzp_po2cyc_eval_const_t)a, secret_key);

    if (evaluation_format) {
        rv = ccpolyzp_po2cyc_fwd_ntt(err_poly);
        cc_require(rv == CCERR_OK, errOut);
        // c0 = c0 + e = a * s + e for BFV
        // c0 = c0 + t * e = a * s + t * e for BGV
        ccpolyzp_po2cyc_eval_add(c0_eval, c0_eval, (ccpolyzp_po2cyc_eval_const_t)err_poly);
        // c0 = -c0 = -(a * s + e) for BFV
        // c0 = -c0 = -(a * s + t * e) for BGV
        ccpolyzp_po2cyc_eval_negate(c0_eval, c0_eval);
    } else {
        // invNTT on c0 and a
        rv = ccpolyzp_po2cyc_inv_ntt(c0_eval);
        cc_require(rv == CCERR_OK, errOut);
        ccpolyzp_po2cyc_coeff_t c0_coeff = (ccpolyzp_po2cyc_coeff_t)c0_eval;
        rv = ccpolyzp_po2cyc_inv_ntt((ccpolyzp_po2cyc_eval_t)a);
        cc_require(rv == CCERR_OK, errOut);
        ccpolyzp_po2cyc_coeff_add(c0_coeff, c0_coeff, err_poly);
        // c0 = -c0 = -(a * s + e) for BFV
        // c0 = -c0 = -(a * s + t * e) for BGV
        ccpolyzp_po2cyc_coeff_negate(c0_coeff, c0_coeff);
    }

    // zeroize e
    ccn_clear(ccpolyzp_po2cyc_nof_n(&ciphertext_ctx->dims), (cc_unit *)err_poly);

    ctext->npolys = cche_ciphertext_fresh_npolys();
    ctext->param_ctx = param_ctx;
    ctext->correction_factor = CCHE_CIPHERTEXT_FRESH_CORRECTION_FACTOR;

errOut:
    CC_FREE_BP_WS(ws, bp);
    return rv;
}

CC_PURE cc_size CCHE_ENCRYPT_ZERO_SYMMETRIC_EVAL_WORKSPACE_N(cc_size degree, cc_size nmoduli)
{
    return CCHE_ENCRYPT_ZERO_SYMMETRIC_HELPER_WORKSPACE_N(degree, nmoduli);
}

int cche_encrypt_zero_symmetric_eval_ws(cc_ws_t ws,
                                        cche_ciphertext_eval_t ctext,
                                        cche_param_ctx_const_t param_ctx,
                                        cche_secret_key_const_t secret_key,
                                        uint32_t nmoduli,
                                        cche_rng_seed_t seed,
                                        struct ccrng_state *rng)
{
    return cche_encrypt_zero_symmetric_helper_ws(
        ws, (cche_ciphertext_coeff_t)ctext, param_ctx, secret_key, nmoduli, true, seed, rng);
}

CC_PURE cc_size CCHE_ENCRYPT_ZERO_SYMMETRIC_COEFF_WORKSPACE_N(cc_size degree, cc_size nmoduli)
{
    return CCHE_ENCRYPT_ZERO_SYMMETRIC_HELPER_WORKSPACE_N(degree, nmoduli);
}

int cche_encrypt_zero_symmetric_coeff_ws(cc_ws_t ws,
                                         cche_ciphertext_coeff_t ctext,
                                         cche_param_ctx_const_t param_ctx,
                                         cche_secret_key_const_t secret_key,
                                         uint32_t nmoduli,
                                         cche_rng_seed_t seed,
                                         struct ccrng_state *rng)
{
    return cche_encrypt_zero_symmetric_helper_ws(ws, ctext, param_ctx, secret_key, nmoduli, false, seed, rng);
}

CC_PURE cc_size CCHE_ENCRYPT_SYMMETRIC_WORKSPACE_N(cc_size degree, cc_size nmoduli)
{
    return CC_MAX_EVAL(CCHE_ENCRYPT_ZERO_SYMMETRIC_COEFF_WORKSPACE_N(degree, nmoduli),
                       CCHE_CIPHERTEXT_PLAINTEXT_ADD_WORKSPACE_N(degree));
}

int cche_encrypt_symmetric_ws(cc_ws_t ws,
                              cche_ciphertext_coeff_t ctext,
                              cche_plaintext_const_t ptext,
                              cche_param_ctx_const_t param_ctx,
                              cche_secret_key_const_t secret_key,
                              uint32_t nmoduli,
                              cche_rng_seed_t seed,
                              struct ccrng_state *rng)
{
    int rv = CCERR_OK;
    rv = cche_encrypt_zero_symmetric_coeff_ws(ws, ctext, param_ctx, secret_key, nmoduli, seed, rng);
    cc_require(rv == CCERR_OK, errOut);
    rv = cche_ciphertext_plaintext_add_ws(ws, ctext, ctext, ptext);
    cc_require(rv == CCERR_OK, errOut);
errOut:
    return rv;
}

int cche_encrypt_symmetric(cche_ciphertext_coeff_t ctext,
                           cche_plaintext_const_t ptext,
                           cche_param_ctx_const_t param_ctx,
                           cche_secret_key_const_t secret_key,
                           uint32_t nmoduli,
                           cche_rng_seed_t seed,
                           struct ccrng_state *rng)
{
    CC_ENSURE_DIT_ENABLED

    CC_DECL_WORKSPACE_OR_FAIL(ws, CCHE_ENCRYPT_SYMMETRIC_WORKSPACE_N(cche_param_ctx_polynomial_degree(param_ctx), nmoduli));
    int rv = cche_encrypt_symmetric_ws(ws, ctext, ptext, param_ctx, secret_key, nmoduli, seed, rng);
    CC_FREE_WORKSPACE(ws);
    return rv;
}
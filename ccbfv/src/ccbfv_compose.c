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

#include "cc_internal.h"
#include "ccbfv_priv.h"
#include "ccbfv_util.h"
#include "ccbfv_internal.h"

/// @brief Returns the number of plaintext polynomials required to decompose an RNS component of a ciphertext's polynomial
/// @param ctext The ciphertext to decompose
/// @param rns_idx The RNS index
/// @param skip_lsb The number of least significant bits to skip
static uint32_t
ccbfv_ciphertext_coeff_decompose_nptexts_rns(ccbfv_ciphertext_coeff_const_t ctext, uint32_t rns_idx, const uint32_t skip_lsb)
{
    ccrns_int ptext_modulus = ccbfv_param_ctx_plaintext_modulus(ctext->param_ctx);
    uint32_t log2_t = ccpolyzp_po2cyc_log2_uint64(ptext_modulus);

    ccpolyzp_po2cyc_ctx_const_t poly_ctx = ccbfv_ciphertext_coeff_ctx(ctext);
    ccrns_int qi = ccpolyzp_po2cyc_ctx_int_modulus(poly_ctx, rns_idx);
    uint32_t log2_qi = ccpolyzp_po2cyc_ceil_log2_uint64(qi);
    return cc_ceiling(log2_qi - skip_lsb, log2_t);
}

uint32_t ccbfv_ciphertext_coeff_decompose_nptexts(ccbfv_ciphertext_coeff_const_t ctext)
{
    CC_ENSURE_DIT_ENABLED
    return ccbfv_ciphertext_coeff_decompose_nptexts_skip_lsbs(ctext, NULL);
}

uint32_t ccbfv_ciphertext_coeff_decompose_nptexts_skip_lsbs(
    ccbfv_ciphertext_coeff_const_t ctext,
    const uint32_t *cc_counted_by(ctext->npoly *ccbfv_ciphertext_coeff_ctx(ctext)->dims.nmoduli) skip_lsbs)
{
    CC_ENSURE_DIT_ENABLED

    const uint32_t nmoduli = ccbfv_ciphertext_coeff_ctx(ctext)->dims.nmoduli;
    uint32_t nptexts = 0;
    for (uint32_t poly_idx = 0; poly_idx < ctext->npolys; ++poly_idx) {
        for (uint32_t rns_idx = 0; rns_idx < nmoduli; ++rns_idx) {
            const uint32_t skip_lsb = skip_lsbs ? skip_lsbs[poly_idx * nmoduli + rns_idx] : 0;
            nptexts += ccbfv_ciphertext_coeff_decompose_nptexts_rns(ctext, rns_idx, skip_lsb);
        }
    }

    return nptexts;
}

int ccbfv_ciphertext_coeff_compose(ccbfv_ciphertext_coeff_t ctext,
                                   uint32_t nptexts,
                                   ccbfv_plaintext_const_t *cc_counted_by(nptexts) ptexts,
                                   uint32_t nmoduli)
{
    CC_ENSURE_DIT_ENABLED
    return ccbfv_ciphertext_coeff_compose_skip_lsbs(ctext, nptexts, ptexts, nmoduli, NULL);
}

int ccbfv_ciphertext_coeff_compose_skip_lsbs(ccbfv_ciphertext_coeff_t ctext,
                                             uint32_t nptexts,
                                             ccbfv_plaintext_const_t *cc_counted_by(nptexts) ptexts,
                                             uint32_t nmoduli,
                                             const uint32_t *cc_counted_by(ccbfv_ciphertext_fresh_npolys() * nmoduli) skip_lsbs)
{
    CC_ENSURE_DIT_ENABLED

    cc_require_or_return(nptexts > 0, CCERR_PARAMETER);
    ccbfv_param_ctx_const_t param_ctx = (*ptexts)->param_ctx;
    cc_require_or_return(nmoduli <= ccbfv_param_ctx_key_ctx_nmoduli(param_ctx), CCERR_PARAMETER);
    ccpolyzp_po2cyc_ctx_const_t cipher_ctx = ccbfv_param_ctx_ciphertext_context_specific(param_ctx, nmoduli);

    // initialize ciphertext
    size_t ciphertext_nbytes = ccbfv_ciphertext_sizeof(param_ctx, nmoduli, ccbfv_ciphertext_fresh_npolys());
    memset(ctext, 0, ciphertext_nbytes);
    ccbfv_ciphertext_coeff_init(ctext, param_ctx, ccbfv_ciphertext_fresh_npolys(), cipher_ctx);

    cc_require_or_return(nptexts == ccbfv_ciphertext_coeff_decompose_nptexts_skip_lsbs(ctext, skip_lsbs), CCERR_PARAMETER);

    ccrns_int ptext_modulus = ccbfv_param_ctx_plaintext_modulus(ctext->param_ctx);
    uint32_t log2_t = ccpolyzp_po2cyc_log2_uint64(ptext_modulus);

    for (uint32_t ctext_poly_idx = 0, ptext_poly_idx = 0; ctext_poly_idx < ctext->npolys; ++ctext_poly_idx) {
        ccpolyzp_po2cyc_coeff_t ctext_poly = ccbfv_ciphertext_coeff_polynomial(ctext, ctext_poly_idx);
        ccpolyzp_po2cyc_ctx_const_t ctext_ctx = ctext_poly->context;

        for (uint32_t rns_idx = 0; rns_idx < ctext_ctx->dims.nmoduli; ++rns_idx) {
            const uint32_t skip_lsb = skip_lsbs ? skip_lsbs[ctext_poly_idx * nmoduli + rns_idx] : 0;
            uint32_t expansion = ccbfv_ciphertext_coeff_decompose_nptexts_rns(ctext, rns_idx, skip_lsb);
            ccrns_int shift = skip_lsb;
            for (uint32_t expansion_idx = 0; expansion_idx < expansion; ++expansion_idx, ++ptext_poly_idx) {
                // Ensure no overflow from shift
                cc_require_or_return(shift < CCRNS_INT_NBITS, CCERR_PARAMETER);
                ccbfv_plaintext_const_t ptext = ptexts[ptext_poly_idx];
                ccpolyzp_po2cyc_coeff_const_t ptext_poly = ccbfv_plaintext_polynomial_const(ptext);
                for (uint32_t coeff_idx = 0; coeff_idx < ctext_ctx->dims.degree; ++coeff_idx) {
                    ccrns_int ptext_coeff = ccpolyzp_po2cyc_coeff_data_int(ptext_poly, 0, coeff_idx);
                    ccrns_int ctext_coeff = ccpolyzp_po2cyc_coeff_data_int(ctext_poly, rns_idx, coeff_idx);
                    ctext_coeff |= ptext_coeff << shift;
                    cc_unit *ctext_data = CCPOLYZP_PO2CYC_DATA(ctext_poly, rns_idx, coeff_idx);
                    ccpolyzp_po2cyc_rns_int_to_units(ctext_data, ctext_coeff);
                }
                shift += log2_t;
            }
        }
    }

    return CCERR_OK;
}

int ccbfv_ciphertext_coeff_decompose(uint32_t nptexts,
                                     ccbfv_plaintext_t *cc_counted_by(nptexts) ptexts,
                                     ccbfv_ciphertext_coeff_const_t ctext)
{
    CC_ENSURE_DIT_ENABLED
    return ccbfv_ciphertext_coeff_decompose_skip_lsbs(nptexts, ptexts, ctext, NULL);
}

int ccbfv_ciphertext_coeff_decompose_skip_lsbs(
    uint32_t nptexts,
    ccbfv_plaintext_t *cc_counted_by(nptexts) ptexts,
    ccbfv_ciphertext_coeff_const_t ctext,
    const uint32_t *cc_counted_by(ctext->npoly *ccbfv_ciphertext_coeff_ctx(ctext)->dims.nmoduli) skip_lsbs)
{
    CC_ENSURE_DIT_ENABLED

    cc_require_or_return(nptexts == ccbfv_ciphertext_coeff_decompose_nptexts_skip_lsbs(ctext, skip_lsbs), CCERR_PARAMETER);

    ccbfv_param_ctx_const_t param_ctx = ctext->param_ctx;
    ccrns_int ptext_modulus = ccbfv_param_ctx_plaintext_modulus(ctext->param_ctx);
    uint32_t log2_t = ccpolyzp_po2cyc_log2_uint64(ptext_modulus);
    ccrns_int t_mask = ((ccrns_int)1 << log2_t) - 1;
    const uint32_t nmoduli = ccbfv_ciphertext_coeff_ctx(ctext)->dims.nmoduli;

    for (uint32_t ctext_poly_idx = 0, ptext_poly_idx = 0; ctext_poly_idx < ctext->npolys; ++ctext_poly_idx) {
        ccpolyzp_po2cyc_coeff_const_t ctext_poly = ccbfv_ciphertext_coeff_polynomial_const(ctext, ctext_poly_idx);

        for (uint32_t rns_idx = 0; rns_idx < nmoduli; ++rns_idx) {
            const uint32_t skip_lsb = skip_lsbs ? skip_lsbs[ctext_poly_idx * nmoduli + rns_idx] : 0;
            uint32_t expansion = ccbfv_ciphertext_coeff_decompose_nptexts_rns(ctext, rns_idx, skip_lsb);
            ccrns_int shift = skip_lsb;
            for (uint32_t expand_poly_idx = 0; expand_poly_idx < expansion; ++expand_poly_idx, ++ptext_poly_idx) {
                ccbfv_plaintext_t ptext = ptexts[ptext_poly_idx];
                ccbfv_plaintext_init(ptext, param_ctx);
                ccpolyzp_po2cyc_coeff_t ptext_poly = ccbfv_plaintext_polynomial(ptext);
                for (uint32_t coeff_idx = 0; coeff_idx < ctext_poly->context->dims.degree; ++coeff_idx) {
                    ccrns_int ctext_coeff = ccpolyzp_po2cyc_coeff_data_int(ctext_poly, rns_idx, coeff_idx);
                    ccrns_int ptext_coeff = (ctext_coeff >> shift) & t_mask;
                    cc_unit *ptext_data = CCPOLYZP_PO2CYC_DATA(ptext_poly, 0, coeff_idx);
                    ccpolyzp_po2cyc_rns_int_to_units(ptext_data, ptext_coeff);
                }
                shift += log2_t;
            }
        }
    }

    return CCERR_OK;
}

/* Copyright (c) (2019,2022,2023) Apple Inc. All rights reserved.
 *
 * corecrypto is licensed under Apple Inc.’s Internal Use License Agreement (which
 * is contained in the License.txt file distributed with corecrypto) and only to
 * people who accept that license. IMPORTANT:  Any license rights granted to you by
 * Apple Inc. (if any) are limited to internal use within your organization only on
 * devices and computers you own or control, for the sole purpose of verifying the
 * security characteristics and correct functioning of the Apple Software.  You may
 * not, directly or indirectly, redistribute the Apple Software or any portions thereof.
 */

#include "ccdict.h"
#include "testbyteBuffer.h"
#include "cctest_driver.h"
#include "cctestvector_parser.h"
#include "cctest_runner.h"

#include <corecrypto/ccsha2.h>
#include "ccec25519_internal.h"
#include "cced25519_internal.h"

bool crypto_test_ed25519_runner(ccdict_t vector)
{
    bool result = true;

    STRING_TO_BUFFER(id, cctestvector_key_id);
    STRING_TO_BUFFER(curve, cctestvector_key_curve);
    HEX_VALUE_TO_BUFFER(pk, cctestvector_key_pk);
    HEX_VALUE_TO_BUFFER(sk, cctestvector_key_sk);
    HEX_VALUE_TO_BUFFER(msg, cctestvector_key_msg);
    HEX_VALUE_TO_BUFFER(signature, cctestvector_key_signature);

    uint64_t test_result = ccdict_get_uint64(vector, cctestvector_key_valid);

    if (!(id && curve && signature && pk && sk && msg)) {
        result = false;
        goto cleanup_req;
    }

    if (strlen("edwards25519") != curve->len || memcmp(curve->bytes, "edwards25519", curve->len) || signature->len != 64) {
        goto cleanup_req;
    }

    struct ccrng_state *rng = ccrng(NULL);
    const struct ccdigest_info *di = ccsha512_di();

    for (unsigned i = 0; i < CC_ARRAY_LEN(ccec_cp_ed25519_impls); i++) {
        ccec_const_cp_t cp = ccec_cp_ed25519_impls[i]();

        // Generate a non-deterministic signature.
        ccec25519signature sig;
        int rc = cced25519_sign_with_rng(di, rng, sig, msg->len, msg->bytes, pk->bytes, sk->bytes);
        CC_WYCHEPROOF_CHECK_OP_RESULT(rc == CCERR_OK, result, cleanup_req);

        rc = memcmp(sig, signature->bytes, sizeof(sig));
        CC_WYCHEPROOF_CHECK_OP_RESULT(rc != 0, result, cleanup_req);

        // And verify it.
        rc = cced25519_verify_internal(cp, di, msg->len, msg->bytes, sig, pk->bytes);
        CC_WYCHEPROOF_CHECK_OP_RESULT(rc == CCERR_OK, result, cleanup_req);

        // Verify the test vector's signature.
        rc = cced25519_verify_internal(cp, di, msg->len, msg->bytes, signature->bytes, pk->bytes);
        CC_WYCHEPROOF_CHECK_OP_RESULT(rc == CCERR_OK, result, cleanup);

        // Re-create the deterministic signature.
        rc = cced25519_sign_deterministic(di, rng, sig, msg->len, msg->bytes, pk->bytes, sk->bytes);
        CC_WYCHEPROOF_CHECK_OP_RESULT(rc == CCERR_OK, result, cleanup_req);

        rc = memcmp(sig, signature->bytes, sizeof(sig));
        CC_WYCHEPROOF_CHECK_OP_RESULT(rc == 0, result, cleanup_req);
    }

cleanup:
    if (test_result == cctestvector_result_invalid) {
        result = !result;
    }

cleanup_req:
    if (!result) {
        fprintf(stderr, "Test ID %s failed\n", id_string);
    }

    RELEASE_BUFFER(id);
    RELEASE_BUFFER(curve);
    RELEASE_BUFFER(pk);
    RELEASE_BUFFER(sk);
    RELEASE_BUFFER(msg);
    RELEASE_BUFFER(signature);

    return result;
}

/* Copyright (c) (2012,2015,2019,2021,2022) Apple Inc. All rights reserved.
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
#include "ccn_internal.h"
#include <corecrypto/ccz_priv.h>

bool ccz_is_zero(const ccz *s)
{
    CC_ENSURE_DIT_ENABLED

    /* This should work too now that everything is always pre-trimmed. */
    // return ccz_n(s) == 0;
    return ccn_is_zero(ccz_n(s), s->u);
}

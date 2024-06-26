/* Copyright (c) (2021) Apple Inc. All rights reserved.
 *
 * corecrypto is licensed under Apple Inc.’s Internal Use License Agreement (which
 * is contained in the License.txt file distributed with corecrypto) and only to 
 * people who accept that license. IMPORTANT:  Any license rights granted to you by 
 * Apple Inc. (if any) are limited to internal use within your organization only on 
 * devices and computers you own or control, for the sole purpose of verifying the 
 * security characteristics and correct functioning of the Apple Software.  You may 
 * not, directly or indirectly, redistribute the Apple Software or any portions thereof.
 */

#define FIPS_RSA_OAEP_KEY_N ccn_nof(2048)
#define FIPS_RSA_OAEP_KEY_SIZE ccn_sizeof_n(FIPS_RSA_OAEP_KEY_N)

static const uint8_t FIPS_RSA_OAEP_KEY[] = {
    0x30, 0x82, 0x04, 0xa3, 0x02, 0x01, 0x00, 0x02, 0x82, 0x01, 0x01, 0x00, 0xa2, 0xb4, 0x51, 0xa0,
    0x7d, 0x0a, 0xa5, 0xf9, 0x6e, 0x45, 0x56, 0x71, 0x51, 0x35, 0x50, 0x51, 0x4a, 0x8a, 0x5b, 0x46,
    0x2e, 0xbe, 0xf7, 0x17, 0x09, 0x4f, 0xa1, 0xfe, 0xe8, 0x22, 0x24, 0xe6, 0x37, 0xf9, 0x74, 0x6d,
    0x3f, 0x7c, 0xaf, 0xd3, 0x18, 0x78, 0xd8, 0x03, 0x25, 0xb6, 0xef, 0x5a, 0x17, 0x00, 0xf6, 0x59,
    0x03, 0xb4, 0x69, 0x42, 0x9e, 0x89, 0xd6, 0xea, 0xc8, 0x84, 0x50, 0x97, 0xb5, 0xab, 0x39, 0x31,
    0x89, 0xdb, 0x92, 0x51, 0x2e, 0xd8, 0xa7, 0x71, 0x1a, 0x12, 0x53, 0xfa, 0xcd, 0x20, 0xf7, 0x9c,
    0x15, 0xe8, 0x24, 0x7f, 0x3d, 0x3e, 0x42, 0xe4, 0x6e, 0x48, 0xc9, 0x8e, 0x25, 0x4a, 0x2f, 0xe9,
    0x76, 0x53, 0x13, 0xa0, 0x3e, 0xff, 0x8f, 0x17, 0xe1, 0xa0, 0x29, 0x39, 0x7a, 0x1f, 0xa2, 0x6a,
    0x8d, 0xce, 0x26, 0xf4, 0x90, 0xed, 0x81, 0x29, 0x96, 0x15, 0xd9, 0x81, 0x4c, 0x22, 0xda, 0x61,
    0x04, 0x28, 0xe0, 0x9c, 0x7d, 0x96, 0x58, 0x59, 0x42, 0x66, 0xf5, 0xc0, 0x21, 0xd0, 0xfc, 0xec,
    0xa0, 0x8d, 0x94, 0x5a, 0x12, 0xbe, 0x82, 0xde, 0x4d, 0x1e, 0xce, 0x6b, 0x4c, 0x03, 0x14, 0x5b,
    0x5d, 0x34, 0x95, 0xd4, 0xed, 0x54, 0x11, 0xeb, 0x87, 0x8d, 0xaf, 0x05, 0xfd, 0x7a, 0xfc, 0x3e,
    0x09, 0xad, 0xa0, 0xf1, 0x12, 0x64, 0x22, 0xf5, 0x90, 0x97, 0x5a, 0x19, 0x69, 0x81, 0x6f, 0x48,
    0x69, 0x8b, 0xcb, 0xba, 0x1b, 0x4d, 0x9c, 0xae, 0x79, 0xd4, 0x60, 0xd8, 0xf9, 0xf8, 0x5e, 0x79,
    0x75, 0x00, 0x5d, 0x9b, 0xc2, 0x2c, 0x4e, 0x5a, 0xc0, 0xf7, 0xc1, 0xa4, 0x5d, 0x12, 0x56, 0x9a,
    0x62, 0x80, 0x7d, 0x3b, 0x9a, 0x02, 0xe5, 0xa5, 0x30, 0xe7, 0x73, 0x06, 0x6f, 0x45, 0x3d, 0x1f,
    0x5b, 0x4c, 0x2e, 0x9c, 0xf7, 0x82, 0x02, 0x83, 0xf7, 0x42, 0xb9, 0xd5, 0x02, 0x03, 0x01, 0x00,
    0x01, 0x02, 0x82, 0x01, 0x00, 0x76, 0x27, 0xee, 0xf3, 0x56, 0x7b, 0x2a, 0x27, 0x26, 0x8e, 0x52,
    0x05, 0x3e, 0xcd, 0x31, 0xc3, 0xa7, 0x17, 0x2c, 0xcb, 0x9d, 0xdc, 0xee, 0x81, 0x9b, 0x30, 0x6a,
    0x5b, 0x3c, 0x66, 0xb7, 0x57, 0x3c, 0xa4, 0xfa, 0x88, 0xef, 0xc6, 0xf3, 0xc4, 0xa0, 0x0b, 0xfa,
    0x0a, 0xe7, 0x13, 0x9f, 0x64, 0x54, 0x3a, 0x4d, 0xac, 0x3d, 0x05, 0x82, 0x3f, 0x6f, 0xf4, 0x77,
    0xcf, 0xce, 0xc8, 0x4f, 0xe2, 0xac, 0x7a, 0x68, 0xb1, 0x72, 0x04, 0xb3, 0x90, 0x23, 0x2e, 0x11,
    0x03, 0x10, 0xc4, 0xe8, 0x99, 0xc4, 0xe7, 0xc1, 0x09, 0x67, 0xdb, 0x4a, 0xcd, 0xe0, 0x42, 0xdb,
    0xbf, 0x19, 0xdb, 0xe0, 0x0b, 0x4b, 0x47, 0x41, 0xde, 0x10, 0x20, 0xaa, 0xaa, 0xff, 0xb5, 0x05,
    0x4c, 0x79, 0x7c, 0x9f, 0x13, 0x6f, 0x7d, 0x93, 0xac, 0x3f, 0xc8, 0xca, 0xff, 0x66, 0x54, 0x24,
    0x2d, 0x78, 0x21, 0xeb, 0xee, 0x51, 0x7b, 0xf5, 0x37, 0xf4, 0x43, 0x66, 0xa0, 0xfd, 0xd4, 0x5a,
    0xe0, 0x5b, 0x99, 0x09, 0xc2, 0xe6, 0xcc, 0x1e, 0xd9, 0x28, 0x1e, 0xff, 0x43, 0x99, 0xf7, 0x6c,
    0x96, 0xb9, 0x62, 0x33, 0xec, 0x29, 0xae, 0x0b, 0xbf, 0x0d, 0x75, 0x2b, 0x23, 0x4f, 0xc1, 0x97,
    0x38, 0x9f, 0x51, 0x05, 0x0a, 0xa1, 0xac, 0xd0, 0x1c, 0x07, 0x4c, 0x3a, 0xc8, 0xfb, 0xdb, 0x9e,
    0xa8, 0xb6, 0x51, 0xa9, 0x59, 0x95, 0xe8, 0xdb, 0x4a, 0xd5, 0xc4, 0x3b, 0x6c, 0x86, 0x73, 0xe5,
    0xa1, 0x26, 0xe7, 0xee, 0x94, 0xb8, 0xdf, 0xf4, 0xc5, 0xaf, 0xc0, 0x12, 0x59, 0xbc, 0x8d, 0xa7,
    0x69, 0x50, 0xba, 0xe6, 0xf8, 0xba, 0xe7, 0x15, 0xf5, 0x09, 0x85, 0xb0, 0xd6, 0xf6, 0x6d, 0x04,
    0xc6, 0xfe, 0xf3, 0xb7, 0x00, 0x72, 0x0e, 0xec, 0xdc, 0xdf, 0x17, 0x1b, 0xb7, 0xb1, 0xec, 0xbe,
    0x72, 0x89, 0xc4, 0x67, 0xc1, 0x02, 0x81, 0x81, 0x00, 0xdc, 0x43, 0x10, 0x50, 0xf7, 0x82, 0xe8,
    0x94, 0xfb, 0x52, 0x48, 0x24, 0x7d, 0x98, 0xcb, 0x7d, 0x58, 0xb8, 0xd1, 0xe2, 0x4f, 0x3b, 0x55,
    0xd0, 0x41, 0xc5, 0x6e, 0x4d, 0xe0, 0x86, 0xb0, 0xd5, 0xbb, 0x02, 0x8b, 0xda, 0x42, 0xee, 0xb5,
    0xd2, 0x34, 0xd5, 0x68, 0x1e, 0x58, 0x09, 0xd4, 0x15, 0xe6, 0xa2, 0x89, 0xad, 0x4c, 0xfb, 0xf7,
    0x8f, 0x97, 0x8f, 0x6c, 0x35, 0x81, 0x4f, 0x50, 0xee, 0xbf, 0xf1, 0xc5, 0xb8, 0x0a, 0x69, 0xf7,
    0x88, 0xe8, 0x1e, 0x6b, 0xab, 0x5d, 0xda, 0xa7, 0x83, 0x69, 0xd6, 0x59, 0xd1, 0x43, 0xec, 0x6f,
    0x17, 0xe7, 0x98, 0x13, 0xa5, 0x75, 0xcf, 0xad, 0x9c, 0x56, 0x91, 0x56, 0xb9, 0x01, 0x13, 0xe2,
    0xe9, 0x11, 0x0a, 0xd9, 0xe7, 0xb4, 0x8a, 0x1c, 0x93, 0x48, 0xa6, 0xe6, 0x53, 0x32, 0x11, 0x91,
    0x29, 0x0e, 0xa3, 0x6c, 0xfb, 0x3a, 0x5b, 0x18, 0xf1, 0x02, 0x81, 0x81, 0x00, 0xbd, 0x1a, 0x81,
    0xe7, 0x97, 0x7f, 0x98, 0x98, 0x12, 0x22, 0x73, 0xae, 0x32, 0x22, 0xb5, 0x98, 0xea, 0x5f, 0xb1,
    0x9e, 0xb4, 0xea, 0xbc, 0x38, 0x30, 0x8a, 0x5e, 0x32, 0x19, 0x66, 0x03, 0xb2, 0xe5, 0x00, 0xff,
    0xb7, 0x9f, 0x5b, 0x88, 0x68, 0x16, 0x61, 0x1d, 0xeb, 0xc4, 0x72, 0xfa, 0xc4, 0x55, 0x44, 0x07,
    0x0b, 0xeb, 0x05, 0x7c, 0x94, 0x13, 0x78, 0xa6, 0x86, 0x8a, 0xf3, 0xb7, 0xa0, 0x3d, 0x3f, 0x98,
    0x80, 0xec, 0x47, 0xd5, 0xe0, 0x89, 0xb9, 0x4f, 0xbd, 0xe5, 0x42, 0xab, 0xa9, 0xae, 0x8d, 0x72,
    0xc5, 0x70, 0x88, 0xd7, 0xab, 0xf5, 0xb1, 0x31, 0xf3, 0x90, 0x98, 0xf7, 0xbc, 0x16, 0x0f, 0x90,
    0x53, 0x6a, 0xbc, 0x94, 0x92, 0xfd, 0x4e, 0x06, 0xf3, 0xed, 0x72, 0x99, 0xd4, 0xb9, 0x7b, 0xb0,
    0x36, 0x77, 0x20, 0x7d, 0x95, 0x66, 0x9f, 0x14, 0x0c, 0xfb, 0xc2, 0x0f, 0x25, 0x02, 0x81, 0x81,
    0x00, 0xa9, 0x4b, 0x52, 0x8b, 0x28, 0xf2, 0x91, 0x59, 0x91, 0x21, 0xd9, 0x19, 0x52, 0xff, 0xd1,
    0xc7, 0xf2, 0x1d, 0x7c, 0x14, 0x79, 0xd9, 0x9d, 0x47, 0x88, 0x85, 0xfb, 0x16, 0x18, 0x70, 0xee,
    0x12, 0x18, 0xbf, 0x08, 0x47, 0x26, 0x12, 0xdb, 0xe5, 0x49, 0x7e, 0x8d, 0x9c, 0x65, 0x06, 0x88,
    0xe0, 0x9c, 0x78, 0x69, 0x61, 0xae, 0x3e, 0x2c, 0x35, 0x4d, 0xc4, 0x8a, 0xe3, 0x45, 0x14, 0x75,
    0x9c, 0x4c, 0x23, 0xc4, 0x58, 0x84, 0x88, 0x96, 0x1d, 0xc0, 0x6b, 0x41, 0x4e, 0x61, 0xc0, 0xe1,
    0xe7, 0xfb, 0xbd, 0x29, 0x23, 0xd3, 0x15, 0x32, 0xfe, 0x28, 0x9f, 0x96, 0xda, 0x22, 0x07, 0x11,
    0xe5, 0x8c, 0x14, 0x01, 0x98, 0x08, 0xe0, 0x04, 0x14, 0x27, 0x69, 0x33, 0xbb, 0x07, 0xe4, 0xef,
    0xb9, 0xb4, 0xa9, 0xb3, 0x76, 0x56, 0x91, 0x72, 0x05, 0x20, 0x9f, 0x33, 0xf0, 0x95, 0x15, 0xd7,
    0xc1, 0x02, 0x81, 0x80, 0x3a, 0xf0, 0xe7, 0x2a, 0x93, 0x3a, 0xef, 0x09, 0xff, 0x25, 0x03, 0xdf,
    0x78, 0xba, 0xfe, 0xd5, 0x31, 0xc0, 0x2f, 0xf1, 0xa2, 0xbc, 0x43, 0x7c, 0x54, 0x0c, 0xdc, 0xbd,
    0x4a, 0xd3, 0x54, 0x35, 0xcf, 0x51, 0x17, 0x63, 0x59, 0x65, 0x43, 0x48, 0x06, 0x29, 0xb1, 0x14,
    0xca, 0x7f, 0x78, 0x0f, 0xf7, 0xef, 0xa3, 0x2e, 0xa0, 0xcb, 0x6e, 0x00, 0x0d, 0x6d, 0x9e, 0xa1,
    0xf2, 0xef, 0x71, 0xfd, 0x9c, 0xf9, 0x94, 0x84, 0x22, 0xa1, 0x65, 0x55, 0x7e, 0x37, 0xe7, 0x55,
    0xed, 0xfe, 0x70, 0xd9, 0x0b, 0x92, 0x05, 0x02, 0xeb, 0x47, 0x8b, 0xc9, 0x8a, 0x63, 0xf7, 0x88,
    0xce, 0x3a, 0x0f, 0x85, 0x6d, 0x6e, 0xde, 0x72, 0x51, 0xa3, 0x83, 0xbf, 0xa8, 0xfa, 0x48, 0x0a,
    0x81, 0xa9, 0x25, 0xaf, 0x7b, 0x3c, 0xc5, 0x38, 0xc4, 0xba, 0xb8, 0xc9, 0xf7, 0x59, 0x7f, 0xfb,
    0x68, 0x01, 0x1d, 0x8d, 0x02, 0x81, 0x80, 0x26, 0x40, 0xfb, 0xfb, 0xcf, 0xef, 0xb1, 0x63, 0xee,
    0x7a, 0x87, 0xb6, 0x48, 0x3a, 0x66, 0xee, 0x41, 0xf9, 0x56, 0xd9, 0x0f, 0xa8, 0xa7, 0x93, 0x9b,
    0xfc, 0x04, 0x2e, 0xe0, 0x92, 0x4b, 0x1b, 0x79, 0x93, 0xd0, 0x44, 0x5f, 0x75, 0x8d, 0x51, 0x93,
    0x3e, 0x85, 0x17, 0x9c, 0x03, 0x20, 0xb0, 0xc9, 0x68, 0xb4, 0x8a, 0x91, 0xc3, 0x8b, 0x5b, 0xe9,
    0x23, 0xe1, 0x09, 0x7c, 0x0c, 0x56, 0x2f, 0x88, 0xd4, 0x22, 0x94, 0xb6, 0xa2, 0x75, 0x9b, 0xaf,
    0xa5, 0x42, 0x8a, 0x74, 0xf1, 0x27, 0x08, 0x74, 0xe4, 0x5f, 0x6f, 0xcc, 0x60, 0xf2, 0x16, 0x02,
    0xde, 0x5e, 0xcc, 0xd1, 0x43, 0xcf, 0x31, 0x24, 0x1f, 0x59, 0x21, 0xb5, 0xad, 0x39, 0x83, 0xfb,
    0x54, 0xef, 0x17, 0xbe, 0x3b, 0x28, 0x53, 0x67, 0xe5, 0x0c, 0x99, 0x9c, 0x67, 0x24, 0x7b, 0x55,
    0x2f, 0xe4, 0xbf, 0xce, 0x94, 0x5f, 0x7b
};

static const uint8_t FIPS_RSA_OAEP_MESSAGE[] = {
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

static const uint8_t FIPS_RSA_OAEP_CIPHERTEXT[] = {
    0x09, 0x69, 0x58, 0x78, 0x6e, 0xe7, 0x97, 0x20, 0x50, 0xd6, 0x7a, 0x9e, 0x4b, 0x69, 0xd6, 0xc6,
    0xaf, 0x7d, 0xb7, 0xcc, 0x67, 0x43, 0x86, 0xdf, 0x72, 0x57, 0x70, 0xdd, 0x29, 0x12, 0x9b, 0x82,
    0x6e, 0x39, 0x55, 0x23, 0x30, 0x10, 0x4c, 0x8d, 0x71, 0xe6, 0xcc, 0x3a, 0x30, 0x14, 0xdd, 0x2f,
    0x61, 0xb5, 0x41, 0x53, 0xaf, 0x51, 0xb0, 0x43, 0x8d, 0x44, 0x7e, 0xe9, 0x39, 0xf9, 0xe3, 0xc1,
    0x3b, 0xb8, 0xb0, 0x0a, 0x37, 0xde, 0xa6, 0xa0, 0x68, 0xf6, 0xc9, 0xd2, 0x7e, 0x84, 0x8b, 0x1b,
    0xe7, 0xa1, 0xee, 0xeb, 0x3e, 0xe5, 0x0b, 0x78, 0x03, 0x6f, 0xba, 0x95, 0xae, 0x46, 0x94, 0x8c,
    0xa5, 0xb1, 0x3f, 0x35, 0x6e, 0xa2, 0x4d, 0xb1, 0x0f, 0x60, 0xdc, 0x09, 0xe4, 0xb8, 0xba, 0xd8,
    0xf7, 0x66, 0xb6, 0x68, 0xef, 0x72, 0x52, 0x44, 0x32, 0x08, 0x0a, 0x0c, 0xe0, 0x0e, 0xd6, 0x76,
    0xd6, 0xd5, 0xe3, 0x54, 0x98, 0x4b, 0x10, 0x78, 0x52, 0x04, 0x12, 0x52, 0x58, 0x48, 0x15, 0x6d,
    0x06, 0xf0, 0x65, 0x24, 0x69, 0xf9, 0x57, 0x91, 0xba, 0xa3, 0xd9, 0xa7, 0x98, 0xae, 0x53, 0x70,
    0x94, 0xf7, 0x6f, 0x97, 0x6f, 0xae, 0xcd, 0x5c, 0x9c, 0xe0, 0xc9, 0x30, 0xa7, 0x59, 0x10, 0xc6,
    0x3d, 0xac, 0xf6, 0x34, 0x85, 0xcb, 0x4b, 0x5e, 0x7b, 0xdb, 0xcf, 0x4d, 0x80, 0xe7, 0x40, 0x37,
    0xea, 0xa1, 0xa8, 0xfe, 0x4b, 0x52, 0x93, 0x0b, 0xec, 0x6b, 0xe9, 0x9c, 0xf6, 0xac, 0x88, 0xcf,
    0x58, 0x78, 0xdb, 0xf6, 0x85, 0x9d, 0x45, 0x6a, 0x95, 0xdb, 0xc3, 0x46, 0x54, 0xee, 0xc4, 0x25,
    0xde, 0x84, 0xca, 0x2a, 0x53, 0x5d, 0x51, 0x74, 0x03, 0xa9, 0xaa, 0xda, 0x82, 0x7e, 0x7d, 0x00,
    0x93, 0xec, 0xfc, 0x97, 0xed, 0x05, 0x6a, 0x76, 0x52, 0x82, 0x5e, 0x9a, 0x45, 0xcb, 0x2d, 0xcb
};

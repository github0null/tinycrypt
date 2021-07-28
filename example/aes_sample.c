/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-22     MurphyZhao   the first version
 */

#include "tiny_aes.h"

#define TEST_TINY_AES_IV  "0123456789ABCDEF"
#define TEST_TINY_AES_KEY "0123456789ABCDEF0123456789ABCDEF"

static int test_tiny_aes(void)
{
    tiny_aes_context ctx;
    uint8_t iv[16 + 1];
    uint8_t private_key[32 + 1];

    unsigned char data[] = "1234567890123456";
    unsigned char data_encrypt[32];
    unsigned char data_decrypt[32];

    /* encrypt */
    memcpy(iv, TEST_TINY_AES_IV, strlen(TEST_TINY_AES_IV));
    iv[sizeof(iv) - 1] = '\0';
    memcpy(private_key, TEST_TINY_AES_KEY, strlen(TEST_TINY_AES_KEY));
    private_key[sizeof(private_key) - 1] = '\0';

    memset(data_encrypt, 0x0, sizeof(data_encrypt));
    tiny_aes_setkey_enc(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, strlen(data), iv, data, data_encrypt);

    /* decrypt */
    memcpy(iv, TEST_TINY_AES_IV, strlen(TEST_TINY_AES_IV));
    iv[sizeof(iv) - 1] = '\0';
    memcpy(private_key, TEST_TINY_AES_KEY, strlen(TEST_TINY_AES_KEY));
    private_key[sizeof(private_key) - 1] = '\0';

    memset(data_decrypt, 0x0, sizeof(data_decrypt));
    tiny_aes_setkey_dec(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_DECRYPT, strlen(data), iv, data_encrypt, data_decrypt);

    if(memcmp(data, data_decrypt, strlen(data)) == 0)
    {
        printf("AES CBC mode passed!\n");
        return 0;
    }
    else
    {
        printf("AES CBC mode failed!");
        return -1;
    }
}

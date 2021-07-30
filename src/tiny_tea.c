#include "tiny_tea.h"

#define TINY_CRYPT_TEA

#if defined(TINY_CRYPT_TEA)

static void tea_encrypt_(uint32_t *first, uint32_t *second,
                         tiny_tea_times_t times, uint32_t *key)
{
    uint32_t y = *first;
    uint32_t z = *second;
    uint32_t sum = 0;

    uint32_t delta = 0x9e3779b9;
    int32_t i;

    for (i = 0; i < times; i++)
    {
        sum += delta;
        y += ((z << 4) + key[0]) ^ (z + sum) ^ ((z >> 5) + key[1]);
        z += ((y << 4) + key[2]) ^ (y + sum) ^ ((y >> 5) + key[3]);
    }

    *first = y;
    *second = z;
}

static void tea_decrypt_(uint32_t *first, uint32_t *second,
                         tiny_tea_times_t times, uint32_t *key)
{
    uint32_t sum = 0;
    uint32_t y = *first;
    uint32_t z = *second;
    uint32_t delta = 0x9e3779b9;
    int32_t i;

    sum = delta * times;

    for (i = 0; i < times; i++)
    {
        z -= (y << 4) + key[2] ^ y + sum ^ (y >> 5) + key[3];
        y -= (z << 4) + key[0] ^ z + sum ^ (z >> 5) + key[1];
        sum -= delta;
    }

    *first = y;
    *second = z;
}

void tiny_tea_encrypt(uint8_t *buffer, uint32_t size,
                      tiny_tea_times_t times, tiny_tea_key_t key)
{
    int8_t *ptr = buffer;
    int32_t lsize = size;

    while (ptr < (buffer + size) && lsize >= 8)
    {
        tea_encrypt_((uint32_t *)ptr, (uint32_t *)(ptr + sizeof(uint32_t)), times, key);
        ptr += 8;
        lsize -= 8;
    }
}

void tiny_tea_decrypt(uint8_t *buffer, uint32_t size,
                      tiny_tea_times_t times, tiny_tea_key_t key)
{
    int8_t *ptr = buffer;
    int32_t lsize = size;

    while (ptr < (buffer + size) && lsize >= 8)
    {
        tea_decrypt_((uint32_t *)ptr, (uint32_t *)(ptr + sizeof(uint32_t)), times, key);
        ptr += 8;
        lsize -= 8;
    }
}

#endif

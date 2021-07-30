/**
 * @brief TEA encryption algorithm 
*/

#ifndef TINY_CRYPT_TEA_H__
#define TINY_CRYPT_TEA_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
    TEA_CRYPT_TIMES_8 = 8,
    TEA_CRYPT_TIMES_16 = 16,
    TEA_CRYPT_TIMES_32 = 32,
} tiny_tea_times_t;

typedef uint32_t tiny_tea_key_t[4];

/**
 * @brief encrypt a buffer with TEA algorithm.
 * 
 * if buffer size is not multiples of 8, it will ignore the remain data.
 * 
 * @param buffer    buffer ptr
 * @param size      buffer size
 * @param times     crypt rounds times   
 * @param key       private key (16 byte)
*/
void tiny_tea_encrypt(uint8_t *buffer, uint32_t size,
                      tiny_tea_times_t times, tiny_tea_key_t key);

/**
 * @brief decrypt a buffer with TEA algorithm.
 * 
 * if buffer size is not multiples of 8, it will ignore the remain data.
 * 
 * @param buffer    buffer ptr
 * @param size      buffer size
 * @param times     crypt rounds times   
 * @param key       private key (16 byte)
*/
void tiny_tea_decrypt(uint8_t *buffer, uint32_t size,
                      tiny_tea_times_t times, tiny_tea_key_t key);

#ifdef __cplusplus
}
#endif

#endif

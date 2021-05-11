#include <stdint.h>
#include <printf.h>

#include "bsp.h"
#include "riscv.h"
#include "type.h"

#define AES_MAXNR 14
struct aes_key_st {
     unsigned int rd_key[4 *(AES_MAXNR + 1)];
     int rounds;
};
typedef struct aes_key_st AES_KEY;

unsigned char in[16] __attribute__((aligned(4)));
unsigned char out[16] __attribute__((aligned(4)));
unsigned int rk[60];

void
AES_encrypt(const unsigned char *in, unsigned char *out, const AES_KEY *key);
int
AES_set_encrypt_key(const unsigned char *userKey, const int bits, AES_KEY *key);

void isr(void)
{
	;
}

static void print_buffer(const char *prefix, void *buffer, unsigned int length)
{
	printf("%8s: ", prefix);
	for (unsigned int i = 0; i < length; i++)
	{
	  //if (i != 0)
	  //{
	  //		printf(", ");
	  //	}
	  printf("%02x", ((uint8_t *)buffer)[i]);
	}
	printf("\n");
}

int main(void)
{
	bsp_init();
	printf("Hello, AES Test!\n");

	/*
	const uint8_t key[] __attribute__((aligned(4))) =
	//{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	//  {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  };
	{0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81};
	__attribute__((aligned(4))) uint8_t plaintext[] =
	//{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	//  {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  };
	//{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };
	{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
	*/

	/* AES-128 
	const uint8_t key[16] __attribute__((aligned(4))) = {0x5e, 0xcf, 0x7c, 0xd9, 0x08, 0x03, 0x47, 0x19, 0xbe, 0x33, 0x65, 0xde, 0x92, 0x1b, 0xc9, 0xf6};
	const uint8_t plaintext[16] __attribute__((aligned(4))) = {0x5f, 0x46, 0x32, 0x05, 0x74, 0xe8, 0x47, 0x7b, 0xc3, 0x95, 0xd8, 0x64, 0xa3, 0x5b, 0x66, 0x27};
	const uint8_t reference[16] __attribute__((aligned(4))) = {0x96, 0x9f, 0xfc, 0x08, 0xb9, 0xc8, 0x80, 0x89, 0xee, 0xf6, 0xae, 0x36, 0x78, 0x85, 0xe7, 0x73};
	*/

	// AES-256
	const uint8_t key[32] __attribute__((aligned(4))) = {0x70, 0x69, 0x19, 0xa0, 0x40, 0x61, 0x05, 0x17, 0xf7, 0xff, 0xf5, 0x27, 0x2b, 0x64, 0x04, 0x67, 0xc5, 0x06, 0x7a, 0x4b, 0xba, 0x57, 0x78, 0xad, 0x6c, 0xdd, 0xcb, 0xf4, 0x73, 0x03, 0x15, 0x64};
	const uint8_t plaintext[16] __attribute__((aligned(4))) = {0x0b, 0x25, 0xf6, 0x7a, 0x11, 0xec, 0x9d, 0xf5, 0x73, 0x05, 0xfb, 0xe9, 0x48, 0x8a, 0xd6, 0x1b};
	const uint8_t reference[16] __attribute__((aligned(4))) = {0xc4, 0xb8, 0x9f, 0x45, 0x4e, 0xd8, 0x55, 0xa8, 0xa8, 0x63, 0x0b, 0xc8, 0x14, 0x87, 0x7e, 0x94};
	
	
	uint8_t result[16] __attribute__((aligned(4)));
	uint8_t output[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	AES_KEY key_storage;
	
	print_buffer("Key", key, sizeof(key));
	printf("Setting key\n");
	AES_set_encrypt_key(key, sizeof(key)*8, &key_storage);
	printf("Running encrypt\n");
	AES_encrypt(plaintext, output, &key_storage);
	
	print_buffer("Plain", plaintext, 16);
	print_buffer("Key", key, 16);
	print_buffer("Result", output, 16);

	int match = 1;
	for(int i = 0; i < 16; i++ ) {
	  if (output[i] != reference[i]) {
	      match = 0;
	    }
	}
	if (match == 1) {
	  printf("matched\n");
	} else {
	  printf("mismatch!\n");
	}

	//b'9837d6c3e6b7485efa27d1cdc5620d64'
	//b'66e94bd4ef8a2c3b884cfa59ca342b2e'
  
	printf("DONE\n");

	while (1)
	{
	}
}

/*

trial
b'603deb1015ca71be2b73aef0857d7781'
b'6bc1bee22e409f96e93d7e117393172a'
b'b0ff175a6e941a9f16871b5fa8fd1813'
base
b'00000000000000000000000000000001'
b'00000000000000000000000000000001'
b'a17e9f69e4f25a8b8620b4af78eefd6f'

base
b'00000000000000000000000000000000'
b'00000000000000000000000000000000'
b'66e94bd4ef8a2c3b884cfa59ca342b2e'

base
b'00000000000000000000000000000000'
b'00000000000000000000000000000001'
b'58e2fccefa7e3061367f1d57a4e7455a'

base
b'08000000000000000000000000000000'
b'00000000000000000000000000000001'
b'2dd0c0a8af5655ace0fee4930c050c3a'

base
b'00000000000000000000000000000000'
b'08000000000000000000000000000001'
b'08ec3e9235c6a30a6fefa4a1326c0564'
*/

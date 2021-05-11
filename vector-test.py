#!/usr/bin/python3

from Crypto.Cipher import AES
import binascii
import os

key_array = [	0x60,
		0x3d,
		0xeb,
		0x10,

		0x15,
		0xca,
		0x71,
		0xbe,

		0x2b,
		0x73,
		0xae,
		0xf0,

		0x85,
		0x7d,
		0x77,
		0x81,

		#0x1f,
		#0x35,
		#0x2c,
		#0x07,
		#0x3b,
		#0x61,
		#0x08,
		#0xd7,
		#0x2d,
		#0x98,
		#0x10,
		#0xa3,
		#0x09,
		#0x14,
		#0xdf,
		#0xf4,
]

key = bytearray(key_array)

plaintext = bytearray(
               [0x6b,
		0xc1,
		0xbe,
		0xe2,

		0x2e,
		0x40,
		0x9f,
		0x96,

		0xe9,
		0x3d,
		0x7e,
		0x11,

		0x73,
		0x93,
		0x17,
		0x2a,])

def bytes_to_c_arr(data, lowercase=True):
        return [format(b, '#04x' if lowercase else '#04X') for b in data]


cipher = AES.new(key, AES.MODE_ECB)
ciphertext = cipher.encrypt(plaintext)

print("trial")
print(binascii.hexlify(key))
print(binascii.hexlify(plaintext))
print(binascii.hexlify(ciphertext)) # b'ee3c7d1387356a27675efe95fc050f40'


#print("base")
#key2 = bytearray([ 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  ])
#plaintext2 = bytearray([ 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  ])
key2 = os.urandom(32)
plaintext2 = os.urandom(16)
cipher2 = AES.new(key2, AES.MODE_ECB)
print(binascii.hexlify(key2))
print(binascii.hexlify(plaintext2))
ciphertext2 = cipher2.encrypt(plaintext2)
print(binascii.hexlify(ciphertext2))

print("const uint8_t key[32] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(key2))))
print("const uint8_t plaintext[16] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(plaintext2))))
print("const uint8_t reference[16] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(ciphertext2))))

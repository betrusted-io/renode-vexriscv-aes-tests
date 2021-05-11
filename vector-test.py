#!/usr/bin/python3

from Crypto.Cipher import AES
import binascii
import os

def bytes_to_c_arr(data, lowercase=True):
        return [format(b, '#04x' if lowercase else '#04X') for b in data]

#print("base")
#key2 = bytearray([ 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  ])
#plaintext2 = bytearray([ 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,  ])

key2 = os.urandom(32)  # pick 16 or 32 here for 128 or 256 bit AES
plaintext2 = os.urandom(16)
cipher2 = AES.new(key2, AES.MODE_ECB)
print(binascii.hexlify(key2))
print(binascii.hexlify(plaintext2))
ciphertext2 = cipher2.encrypt(plaintext2)
print(binascii.hexlify(ciphertext2))

if len(key2) == 32:
  print("const uint8_t key[32] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(key2))))
else:
  print("const uint8_t key[16] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(key2))))
print("const uint8_t plaintext[16] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(plaintext2))))
print("const uint8_t reference[16] __attribute__((aligned(4))) = {{{}}};".format(", ".join(bytes_to_c_arr(ciphertext2))))

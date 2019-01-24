#include <stdio.h>
#include <stdlib.h>
#include "../../../data_utility.h"


// XORs the plaintext with key bytes and stores the result in ciphertext.
// Can handle multi-byte keys, key bytes are then applied successively.
// Plaintext length is not required to be a multiple of the key length, the procedure just stops when the plaintext ends.
void xor_encode(const unsigned char *plaintext, const int plaintext_length, const unsigned char *key, const int key_length, unsigned char *ciphertext) {
    for(int i = 0; i < plaintext_length; i++) {
		ciphertext[i] = plaintext[i] ^ key[i % key_length];
	}
}


// Arguments expected:
// argv[1]: Name of the file containing the shellcode to be encoded (raw format expected)
// argv[2]: Name of the file where the encoded shellcode shall be written to
// argv[3]: Name of the file the key to be applied is stored (raw format)
int main(int argc, char **argv) {	
	int shellcode_size;
    int key_length;	

    printf("Starting XOR encoder...\n");
    
	// Read shellcode from file into memory
    printf("Reading shellcode from file %s, expecting raw format.\n", argv[1]);	
    unsigned char *shellcode = data_from_file_raw(argv[1], &shellcode_size);
    printf("Shellcode size in bytes is %d\n", shellcode_size);

    // Read encryption key from file into memory
    printf("Reading key from file %s, expecting raw format.\n", argv[3]);
    unsigned char *key = data_from_file_raw(argv[3], &key_length);
    printf("Key length in bytes is %d\n", key_length);

    // Encrypt and write ciphertext to file
	unsigned char *ciphertext = (unsigned char *) malloc(shellcode_size);
    printf("Applying XOR algorithm\n");
	xor_encode(shellcode, shellcode_size, key, key_length, ciphertext);	
    printf("Writing shellcode to file %s\n", argv[2]);
	data_to_file_raw(ciphertext, shellcode_size, argv[2]);
	
	return 0;
}

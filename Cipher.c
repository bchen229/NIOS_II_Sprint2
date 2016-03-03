#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Structures.h"
#include "Cipher.h"
#include "SD_CARD.h"

int char2hex(char c) {
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'a':
		return 10;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	default:
		return -1;
	}
}

char hex2char(int h) {
	switch (h) {
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'e';
	case 15:
		return 'f';
	default:
		return -1;
	}
}

char* convertKey(char* key, int len) {
	int i;
	for (i = 0; i < len; i++) {
		key[i] = hex2char(key[i]);
	}
	return key;
}

int find(char* buf, int bufsize, char c) {
	int i;
	for (i = 0; i < bufsize; i++) {
		if ((buf[i]) == (c))
			return i;
	}
	return -1;
}

void keygen(char* key, char* pw, int pwlen) {
	// assert(strlen(pw)==pwlen);
	assert(pwlen<16);
	int i, j;
	for (i = 0; i < 16; i++)
		key[i] = (-1 & 0xff);
	for (i = 0, j = 0; i < pwlen; i++) {
		char xor_ = (pw[i] & 0xf) ^ (pw[i] >> 4);
		// search if we have seen this char before
		if (find(key, 16, xor_) != -1) {
			while (find(key, 16, xor_) != -1) {
				xor_++;
				xor_ %= 0xf;
				xor_ &= 0xf;
			}
			key[i] = ((xor_ % 15) & 0xf);
		} else
			key[i] = (xor_ & 0xf); // add as usual
	}
	for (j = 0, i = pwlen; i < 16; i++) {
		while (find(key, 16, j) != -1)
			j++;
		key[i] = j & 0xf;
	}

	writeToSD(key, KEYFILE);
}

void printkey(char* key) {
	int i;
	for (i = 0; i < 16; i++)
		(i % 4 == 3) ?
				printf("%x\n", (key[i] & 0xff)) : printf("%x", (key[i] & 0xff));
	printf("\n");
}

char* encrypt(char* key, char* plaintext, int textlen) {
	char *ciphertext = (char*) malloc(sizeof(char) * textlen);
	int i;

	char a, b, a_, b_; // a: MS nibble, b: LS nibble of char
	int ai, aj, ak; // ai, aj: 2D coords, ak: 1D index
	int bi, bj, bk; // bi, bj: 2D coords, bk: 1D index
	int coldiff; // abs(bj-aj) difference of columns

	for (i = 0; i < textlen; i++) {
		a = (plaintext[i] >> 4) & 0xf;
		b = (plaintext[i] & 0xf);
		ak = find(key, 16, a);
		bk = find(key, 16, b);
		ai = ak / 4;
		bi = bk / 4;
		aj = ak % 4;
		bj = bk % 4;
		coldiff = abs(bj - aj);

		if (ai == bi) { //same row
			a_ = key[ai * 4 + ((aj + 1 > 3) ? 0 : aj + 1)];
			b_ = key[bi * 4 + ((bj + 1 > 3) ? 0 : bj + 1)];
		} else if (aj == bj) { //same column
			a_ = key[(((ai + 1) % 4) * 4 + aj)];
			b_ = key[(((bi + 1) % 4) * 4 + bj)];
		} else if (aj > bj) { //first char to the right of the second char
			a_ = key[ak - coldiff];
			b_ = key[bk + coldiff];
		} else if (bj > aj) { //second char to the right of the first char
			a_ = key[ak + coldiff];
			b_ = key[bk - coldiff];
		}
		ciphertext[i] = ((a_ << 4) | b_) & 0xff;
	}
	return ciphertext;
}

char* decrypt(char* key, char* ciphertext, int textlen) {
	char *plaintext = (char*) malloc(sizeof(char) * textlen);
	int i;
	char a, b, a_, b_; // a: MS nibble, b: LS nibble of char
	int ai, aj, ak; // ai, aj: 2D coords, ak: 1D index
	int bi, bj, bk; // bi, bj: 2D coords, bk: 1D index
	int coldiff; // abs(bj-aj) difference of columns

	for (i = 0; i < textlen; i++) {
		a = (ciphertext[i] >> 4) & 0xf;
		b = (ciphertext[i] & 0xf);
		ak = find(key, 16, a);
		bk = find(key, 16, b);
		ai = ak / 4;
		bi = bk / 4;
		aj = ak % 4;
		bj = bk % 4;
		coldiff = abs(bj - aj);

		if (ai == bi) { //same row
			a_ = key[ai * 4 + ((aj - 1 < 0) ? 3 : aj - 1)];
			b_ = key[bi * 4 + ((bj - 1 < 0) ? 3 : bj - 1)];
		} else if (aj == bj) { //same column
			a_ = key[(((ai - 1) < 0) ? 3 : ai - 1) * 4 + aj];
			b_ = key[(((bi - 1) < 0) ? 3 : bi - 1) * 4 + bj];
		} else if (aj > bj) { //first char to the right of the second char
			a_ = key[ak - coldiff];
			b_ = key[bk + coldiff];
		} else if (bj > aj) { //second char to the right of the first char
			a_ = key[ak + coldiff];
			b_ = key[bk - coldiff];
		}
		plaintext[i] = ((a_ << 4) | b_) & 0xff;
	}
	return plaintext;
}

char* pad(char* text, int length, int blocksize, char padchar) {
	int i;

	if (length % blocksize == 0) {
		char* padded = (char*) malloc(sizeof(char) * length);
		strcpy(padded, text);
		return padded;
	}
	int padding = blocksize - length % blocksize;
	char* padded = (char*) malloc(sizeof(char) * (length + padding));
	strcpy(padded, text);

	for (i = length; i < length + padding; i++)
		padded[i] = padchar;
	return padded;
}

char** blocky(char *text, int length, int blocksize, char padchar) {
	int i, j;
	int numblocks = ceil(((double) length) / ((double) blocksize));
	char* padded = pad(text, length, blocksize, padchar);
	char** blocks = (char**) malloc(sizeof(char*) * numblocks);
	for (i = 0; i < numblocks; i++) {
		blocks[i] = (char*) malloc(sizeof(char) * blocksize);
		for (j = 0; j < blocksize; j++)
			blocks[i][j] = padded[i * blocksize + j] & 0xff;
	}

	return blocks;
}

int func_4char2int(char* block, int blocksize) {
	assert(blocksize%2==0);
	assert(blocksize<=4);

	int i, val = 0;
	for (i = 0; i < sizeof(int); i++) {
		val <<= 8;
		val |= block[i] & 0xff;
	}
	return val;
}

char* func_int_2_4char(int val) {
	int i;
	char* block = (char*) malloc(sizeof(char) * sizeof(int));
	for (i = sizeof(int) - 1; i >= 0; i--) {
		block[i] = val & 0xff;
		val >>= 8;
	}
	return block;
}

char* xor4char(char* t1, char* t2) {
	return func_int_2_4char(func_4char2int(t1, 4) ^ func_4char2int(t2, 4));
}

char* encryptCBC(char* key, char* plaintext, int length, int blocksize) {
	int i;
	int numblocks = ceil(((double) length) / ((double) blocksize));

	// Open a random byte
	FILE *fp = fopen("/dev/random", "r");

	int IV = 0;
	for (i = 0; i < sizeof(int); i++) { // fill initialization vector with values from CSPRNG
		IV <<= 8;
		IV |= fgetc(fp);
	}
	IV = 0x6aa29ebe; // fixed IV; for testing

	char** blocks = blocky(plaintext, length, blocksize, '~');
	char *cipher = malloc(sizeof(char) * (numblocks + 1) * blocksize);
	char *cprev = malloc(sizeof(char) * blocksize);
	char *p = malloc(sizeof(char) * blocksize);
	char *c = malloc(sizeof(char) * blocksize);

	strncpy(cipher, func_int_2_4char(IV), 4); // initialize: C_0 = IV

	for (i = 1; i < numblocks + 1; i++) { // start at i = 1 with P_1, C_1
		strncpy(cprev, cipher + (i - 1) * blocksize, blocksize); // C_{i-1}
		strcpy(p, blocks[i - 1]); // P_i
		c = encrypt(key, xor4char(p, cprev), blocksize); // C_i = P_i xor C_{i-1}
		strncpy(cipher + i * blocksize, c, blocksize); // append cipher block to ciphertext
		strcpy(cprev, c); // update C_{i-1}
	}

	return cipher;
}

char* decryptCBC(char* key, char* ciphertext, int plaintxt_len, int blocksize) {
	int i;
	int numblocks = ceil(((double) plaintxt_len) / ((double) blocksize));

	char* plaintext = malloc(sizeof(char) * plaintxt_len);
	char *cprev = malloc(sizeof(char) * blocksize);
	char *p = malloc(sizeof(char) * blocksize);
	char *d = malloc(sizeof(char) * blocksize);

	int IV = 0x6aa29ebe; // fixed IV; for testing
	strncpy(ciphertext, func_int_2_4char(IV), 4); // initialize: C_0 = IV

	for (i = 1; i < numblocks + 1; i++) { // start at i=1 with C_0 = IV, P_1, C_1
		strncpy(cprev, ciphertext + (i - 1) * blocksize, blocksize); // C_{i-1}
		d = decrypt(key, ciphertext + i * blocksize, blocksize); // D_K(C_i)
		p = xor4char(d, cprev); // P_i = C_{i-1} xor D_K(C_i)
		strncpy(cprev, ciphertext + i * blocksize, blocksize); // update C_{i-1}
		strncpy(plaintext + (i - 1) * blocksize, p, blocksize); // append P_i
	}
	return plaintext;
}

void printCipher(char* cipher, int length) {
	int i;

	for (i = 0; i < length; i++) // add zeros to single digit chars
		((int) (cipher[i] & 0xff) < 16) ?
				printf("0%x", cipher[i] & 0xff) :
				printf("%x", cipher[i] & 0xff);
}

char* writeCipher(char* cipher, int length) {
	int i;

	char* doublecipher = malloc(sizeof(char) * length * 2);
	for (i = 0; i < length * 2; i++) { // add zeros to single digit chars
		printf("[%x]", cipher[i] & 0xff);
		doublecipher[2 * i] = hex2char((cipher[i] >> 4) & 0xf);
		doublecipher[2 * i + 1] = hex2char(cipher[i] & 0xf);
	}
	doublecipher[length * 2 + 1] = '\0';
	return doublecipher;
}

char* parseCipher(char* input, int inputlength) {
	assert(inputlength%2==0);
	int i;
	char *cipher = malloc(sizeof(char) * (inputlength / 2));
	for (i = 0; i < inputlength; i += 2)
		cipher[i / 2] = (char2hex(input[i]) << 4) | char2hex(input[i + 1]);
	return cipher;
}

char * encryptData(char * buffer) {

	encryptedtextlen = strlen(buffer) + 1;

	char keyInput[16];
	readFromSD(keyInput, KEYFILE, 16);

	char *encryptedData;
	encryptedData = encrypt(keyInput, buffer, encryptedtextlen);
	char *encdata_w = writeCipher(encryptedData, encryptedtextlen);

	return encdata_w;
}

char * decryptData(char * buffer) {

	char keyInput[16];
	readFromSD(keyInput, KEYFILE, 16);

	char *parsedData_w = parseCipher(buffer, (encryptedtextlen) * 2);
	char* plaintext = decrypt(keyInput, parsedData_w, encryptedtextlen);

	return plaintext;
}

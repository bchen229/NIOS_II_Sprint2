int char2hex(char c);
char hex2char(int h);

/**
 * Converts key to writable format
 */
char* convertKey(char* key, int len);

int find(char* buf, int bufsize, char c);

/**
 * Expects a password less than 16 chars long
 * returns a 4x4 nibble matrix
 * The nibbles should not repeat. Assert 16 unique values
 */
void keygen(char* key, char* pw, int pwlen);

/**
 * prints the key in 4x4 format
 */
void printkey(char* key);

/**
 * encryption without chaining expects 4x4 key
 * Then substitutes bytes in the plaintext using the key
 */
char* encrypt(char* key, char* plaintext, int textlen);

/**
 * decryption without chaining expects 4x4 key
 * Then substitutes bytes in the cipher using the key
 * NOTE: length of cipher should equal length of plaintext
 */
char* decrypt(char* key, char* ciphertext, int textlen);

/**
 * Adds additional characters to the end of the plaintext to meet the nearest
 * blocksize can specify padding character
 */
char* pad(char* text, int length, int blocksize, char padchar);

/**
 * Divides the plaintext into blocks of size blocksize for use in
 * chaining encryption
 */
char** blocky(char *text, int length, int blocksize, char padchar);

/**
 * Converts 4 char arrays to integers for ease of printing or XORing
 */
int func_4char2int(char* block, int blocksize);

/**
 * Converts integers to 4 char arrays to store back
 */
char* func_int_2_4char(int val);

/**
 * Quick function to evaluate the XOR of two chars
 */
char* xor4char(char* t1, char* t2);

/**
 * Encrypt using chaining mode Uses 4x4 key plaintext of length x char
 * blocksize: restricted to 4 for NIOS Resulting cipher is length + 4
 * to accommodate initialization vector
 */
char* encryptCBC(char* key, char* plaintext, int length, int blocksize);

/**
 * Decrypt a chaining mode cipher uses 4x4 key
 * ciphertext -- IV should be the first 4 bytes of the array
 * length argument is the plaintext length -- that's: ciphertext.length - 4
 * blocksize = 4
 * Outputs a printable char array (may contain padding characters)
 */
char* decryptCBC(char* key, char* ciphertext, int plaintxt_len, int blocksize);

/**
 * Prints byte stream in terminal viewable format
 * ie. converts each byte to two hex digits
 * eg. [0xef] --> [0xe][0xf]
 */
void printCipher(char* cipher, int length);

/**
 * Outputs byte stream in saveable format -- to be later parsed
 * ie. converts each byte to two hex digits
 * eg. [0xef] --> [0xe][0xf]
 * output length should be twice the cipher length
 */
char* writeCipher(char* cipher, int length);

/**
 * Converts byte stream back to original hex values (max 0xff ie in [0,255])
 * for decryption. Decrypter will not understand cipher if this is not used!
 * ie. converts each byte to two hex digits
 * eg. [0xef] --> [0xe][0xf]
 * cipher length should be half the input length
 */
char* parseCipher(char* input, int inputlength);

char * encryptData(char * buffer);
char * decryptData(char * buffer);

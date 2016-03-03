/**
 * Writes contents of buffer into SD card with file name, fileName.
 * If no file exists, a new file will be created. Returns 0 on success,
 * -1 on failure.
 */
int writeToSD(char* buffer, char* fileName);

/**
 * Read from file fileName into buffer. Returns 0 on success, -1
 * on failure.
 */
int readFromSD(char* buffer, char* fileName, int bufferSize);

/**
 * Format and save information to SD card in file contactInformation.txt.
 * Returns 0 on success, -1 on failure. Max character length of 512 chars.
 * Format: Name, Address, Phone Number, Emergency Contact.
 */
int formatAndSaveSD(char* name, char* address, char* phone, char* emergency, char* file);

/**
 * Takes in name, address, phone, and emergency buffers. Read holds the
 * "," delimited string to be separated.
 */
int loadInfo(char* name, char* address, char* phone, char* emergency, char* read);

/**
 * Writes contents of an encrypted buffer into SD card with file name, fileName.
 * If no file exists, a new file will be created. Returns 0 on success,
 * -1 on failure.
 */
int writeToSDEncrypted(char* buffer, char* fileName);

/**
 * Read encrypted data from file fileName into buffer.
 * Returns 0 on success, -1 on failure.
 */
int readFromSDEncrypted(char* buffer, char* fileName, int bufferSize);

/**
 * Format and save information in encrypted form to SD card to the file.
 * Returns 0 on success, -1 on failure. Max character length of 512 chars.
 * Format: Name, Address, Phone Number, Emergency Contact.
 */
int formatAndSaveSDEncrypted(char* name, char* address, char* phone, char* emergency, char* file);

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "altera_up_sd_card_avalon_interface.h"
#include "Structures.h"
#include "Font_alg.h"
#include "SD_Card.h"
#include "Cipher.h"
#include "Colours.h"

int writeToSD(char* buffer, char* fileName) {
	alt_up_sd_card_dev *device_reference = NULL;
	short int myFileHandle;
	int i;

	//printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL) {
		//printf("SDCard Open FAILED\n");
		return -1;
	} else {
		//printf("SDCard Open PASSED\n");
	}
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
			myFileHandle = alt_up_sd_card_fopen(fileName, false);
			if (myFileHandle == -1) {
				myFileHandle = alt_up_sd_card_fopen(fileName, true);
			}
			if (myFileHandle != -1) {
				//printf("File Opened\n");
				for (i = 0; i < strlen(buffer); i++) {
					if (alt_up_sd_card_write(myFileHandle, buffer[i])
							== false) {
						//printf("Error writing to file...\n");
						return -1;
					}
				}
				//printf("Done!!!\n");
				alt_up_sd_card_fclose(myFileHandle);
				return 0;
			} else {
				//printf("File NOT Opened\n");
			}
		}
	}
	return -1;
}

int readFromSD(char* buffer, char* fileName, int bufferSize) {
	alt_up_sd_card_dev *device_reference = NULL;
	short int myFileHandle;
	int i;
	char tempChar[2];
	tempChar[1] = '\0';

	//printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL) {
		//printf("SDCard Open FAILED\n");
		return -1;
	} else {
		//printf("SDCard Open PASSED\n");
	}
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		myFileHandle = alt_up_sd_card_fopen(fileName, false);
		if (myFileHandle == -1) {
			myFileHandle = alt_up_sd_card_fopen(fileName, true);
		}
		if (myFileHandle != -1) {
			//printf("File Opened\n");
			for (i = 0; i < bufferSize; i++) {
				tempChar[0] = alt_up_sd_card_read(myFileHandle);
				if (tempChar[0] < 0) {
					return 0;
				}
				strcat(buffer, tempChar);
			}
			//printf("Done!!!\n");
			alt_up_sd_card_fclose(myFileHandle);
			return 0;
		} else {
			//printf("File NOT Opened\n");
		}
	}
	return -1;
}

int formatAndSaveSD(char* name, char* address, char* phone, char* emergency, char* file) {

	char data[512] = "";
	int ret = 0;

	strcat(data, name);
	strcat(data, "$,");
	strcat(data, address);
	strcat(data, "$,");
	strcat(data, phone);
	strcat(data, "$,");
	strcat(data, emergency);
	strcat(data, "$,");

	ret += writeToSD(data, file);
	if (ret == 0) {
		return 0;
	}
	return -1;
}

int loadInfo(char* name, char* address, char* phone, char* emergency, char* read) {

	const char delim[2] = ",";

	printf("read: %s", read);
	strcpy(name, strtok(read, delim));
	strcpy(address, strtok(NULL, delim));
	strcpy(phone, strtok(NULL, delim));
	strcpy(emergency, strtok(NULL, delim));

	name[strlen(name) - 1] = '\0';
	address[strlen(address) - 1] = '\0';
	phone[strlen(phone) - 1] = '\0';
	emergency[strlen(emergency) - 1] = '\0';

	return 0;
}

int writeToSDEncrypted(char* buffer, char* fileName) {
	alt_up_sd_card_dev *device_reference = NULL;
	short int myFileHandle;
	int i;

	char *encryptedBuffer = encryptData(buffer);

	printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL) {
		printf("SDCard Open FAILED\n");
		return -1;
	} else {
		printf("SDCard Open PASSED\n");
	}
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
			myFileHandle = alt_up_sd_card_fopen(fileName, false);
			if (myFileHandle == -1) {
				myFileHandle = alt_up_sd_card_fopen(fileName, true);
			}
			if (myFileHandle != -1) {
				printf("File Opened\n");
				for (i = 0; i < strlen(buffer); i++) {
					if (alt_up_sd_card_write(myFileHandle, buffer[i])
							== false) {
						printf("Error writing to file...\n");
						return -1;
					}
				}
				printf("Done!!!\n");
				alt_up_sd_card_fclose(myFileHandle);
			} else {
				printf("File NOT Opened\n");
			}
		}
	}
	return 0;
}

int readFromSDEncrypted(char* buffer, char* fileName, int bufferSize) {
	alt_up_sd_card_dev *device_reference = NULL;
	short int myFileHandle;
	int i;
	char tempChar[2];
	tempChar[1] = '\0';

	//printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL) {
		//printf("SDCard Open FAILED\n");
		return -1;
	} else {
		//printf("SDCard Open PASSED\n");
	}
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		myFileHandle = alt_up_sd_card_fopen(fileName, false);
		if (myFileHandle == -1) {
			myFileHandle = alt_up_sd_card_fopen(fileName, true);
		}
		if (myFileHandle != -1) {
			//printf("File Opened\n");
			for (i = 0; i < bufferSize; i++) {
				tempChar[0] = alt_up_sd_card_read(myFileHandle);
				if (tempChar[0] < 0) {
					return 0;
				}
				strcat(buffer, tempChar);
			}
			//printf("Done!!!\n");
			alt_up_sd_card_fclose(myFileHandle);

			char *decryptedData = decryptData(buffer);
			printf("Decrypted after read: %s", buffer);
			return 0;
		} else {
			//printf("File NOT Opened\n");
		}
	}
	return -1;
}

int formatAndSaveSDEncrypted(char* name, char* address, char* phone, char* emergency, char* file) {

	char data[512] = "";
	int ret = 0;

	strcpy(data, name);
	strcat(data, "$,");
	strcat(data, address);
	strcat(data, "$,");
	strcat(data, phone);
	strcat(data, "$,");
	strcat(data, emergency);
	strcat(data, "$,");

	ret += writeToSDEncrypted(data, file);
	if (ret == 0) {
		return 0;
	}
	return -1;
}

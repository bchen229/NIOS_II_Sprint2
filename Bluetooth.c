#include "Hardware.h"

void initBluetooth(void) {
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	// program baud rate generator to use 115k baud
	Bluetooth_Baud = 0x01;
	Bluetooth_Control = 0x15; // x16 clock , 8 data , no parity , 1 stop , no interrupt

}

char getcharBluetooth(void) {
	int rx;
	// poll Rx bit in 6850 status register. Wait for it to become '1'
	// read received character from 6850 RxData register.
	while ((Bluetooth_Status & 0x01) != 0x01);

	rx = Bluetooth_RxData;
	printf("THIS IS WHAT WE RECIEVE : %c\n", rx);
	return rx;
}

int putcharBluetooth(char c) {
	// poll Tx bit in 6850 status register. Wait for it to become '1'

	// write 'c' to the 6850 TxData register to output the character

	while ((Bluetooth_Status & 0x02) != 0x02)
		;

	Bluetooth_TxData = c & (char) 0x7F;

	return Bluetooth_TxData; // return c
}

void enterCommandMode(void) {

	char *commandInit = "$$$";
	usleep(1000000);
	putStringBluetooth(commandInit);
	printf("Enter Command Mode\n");
	usleep(1000000);
}

void setDeviceName(void) {

	char *deviceName = "SN,CPEN GROUP 3\r\n";
	printf("setting device name \n");
	putStringBluetooth(deviceName);
}

void factoryReset(void) {

	char *resetCommand = "SF,1\r\n";
	printf("factory resetting \n");
	putStringBluetooth(resetCommand);
}

void setBluetoothPassword(void) {

	char *password = "SP,password\r\n";
	printf("setting device password \n");
	putStringBluetooth(password);

}

void putStringBluetooth(char *s) {
	char i;
	while ((i = *s) != 0) {

		putcharBluetooth(i);
		s++;
	}
}

/* Set up the Register for 9600 baud , 8 bit data  , no parity  and 1 stop*/
void Init_GPS(void);

/* This Function reads the GPS data from the serial port*/
char GetData(void);

/*This functoin sends commands to the GPS  */
void putcharGPS(int c);

/* This function goes through the command string and send the string charater by character */
void putString(char *s);

// this function stops the logging in GPS
void StopLogging(void);

// This function clears logging for GPS
void ClearLogging(void);

// this function starts logging in GPS
void StartLogger(void);

// these two functions take a 4 byte IEEE-754 format float
// (passed as a 4 byte int representing latitude and longitude values)
// in big endian format and converts it to an ASCII decimal string
// which it returns with decimal point in the string.
// output format is xx.yyyy
char *FloatToLatitudeConversion(int x);

// output format is (-)xxx.yyyy
char *FloatToLongitudeConversion(int x);

// takes a 4 byte float in string form (8 chars) and converts to 4 byte form
// (still stored in an int but in float form)
// and swaps the bytes order the reason for this is the GPS outputs the
// longitude and latitude LOG data in 4 byte float form but as little endian
// NIOS however uses big endian
int swapEndian(char *s);

// This Function search for the GPGGA data format from the GPS and send 1 if the command is in GPGGA format
int checkBuff(char *buff);

// This Function parse the GPGGA command and print the UTC time on the LCD and the Console
void printTime(int hour, int minute, int seconds, char buff[256],
		char* secondBuff, char* minuteBuff, char* timeBuff);

// This function parse the Lantitude and longitude
void printCoordinates(int latStart, int longStart, char buff[256],
		char* latitude, char* longitude);

/**
 *   This function converts decimal degrees to radians
 */
double deg2rad(double deg);

/**
 * This function converts radians to decimal degrees
 */
double rad2deg(double rad);

/**
 * Calculate the distance between two points (latitude and longitude)
 */
double distance(double lat1, double lon1, double lat2, double lon2, char unit);

/**
 * Checks distance from a predefined latitude and longitude
 * in meters.
 */
void checkDistance();

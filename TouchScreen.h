#define Touch_Control (*(volatile unsigned char *)(0x84000230))
#define Touch_Status (*(volatile unsigned char *)(0x84000230))
#define Touch_Transmit (*(volatile unsigned char *)(0x84000232))
#define Touch_Recieve (*(volatile unsigned char *)(0x84000232))
#define Touch_Baud (*(volatile unsigned char *)(0x84000234))

#define ALARM_INTERVAL 2 //seconds

/**
 * Initialise touch screen controller.
 */
void Init_Touch(void);

/**
 * Test if screen touched.
 */
int ScreenTouched(void);

/**
 * Wait for screen to be touched.
 */
void WaitForTouch();

/**
 * This function waits for a touch screen press event and returns X,Y coord.
 */
void GetPress(Point *p1);

/**
 * This function waits for a touch screen release event and returns X,Y coord.
 */
void GetRelease(Point *p1);

/**
 * Writes input 'c' into the Touch_Transmit register.
 */
int putcharTouch(int c);

/**
 * Check Touch_Recieve to see if touch is valid.
 */
int getcharTouch(void);

/*
 *
 * Name: updateTime
 * Description: This function checks the data from the gps and print out the time
 * Parameters: void
 *
 */
void updateTime();

/*
 *
 * Name: updateCoord
 * Description: This function checks the data from the gps and print out the coordinates recieved from the GPS
 * Parameters: void
 *
 */
void updateCoord();

/*
 *
 * Name: updateCoordNoPrint
 * Description: This function checks the data from the gps. Used to get the distance for geofencing
 * Parameters: void
 *
 */
void updateCoordNoPrint();



/**
 * Interrupt. Updates the time, coordinates and resets
 * the DE2 LEDs.
 */
void timerISR();

void executePWSetupPress(int choice, int *inputBoxPressed, int *buttonPressed,
		int * sdBoxPressed);

void executePWLogin(int choice, int *inputBoxPressed, int *buttonPressed,
		int * sdBoxPressed);

void executeLoggingSettings(int choice, int *inputBoxPressed,
		int *buttonPressed, int * sdBoxPressed);

void executeMapPress(Button theButton, int choice);

void executeKeyPress(int choice);

/**
 * displays the current menu based on global current page
 * Then evaluates the button press and updates current page
 * Uses a while true loop.
 */
void MainMenu();

/**
 * Function which draws the current page based on button choice
 */
int displayMenu(int *keyPressed, int *inputBoxPressed, int *buttonPressed,
		int * sdBoxPressed);

/*
 *
 * Name: decrementBuffer
 * Description: This functions updates the buffer upon deletion of characters
 * Parameters: Page
 *
 */
void decrementBuffer(Page *currentScreen);

/*
 *
 * Name: clearBuffer
 * Description: This functions empties the buffer
 * Parameters: Page
 *
 */
void clearBuffer(Page *currentScreen);

/*
 *
 * Name: updateBuffer
 * Description: This functions updates the buffer corresponding to the keyboard input
 * Parameters: key ,a Page
 *
 */
void updateBuffer(Key k, Page *currentScreen);



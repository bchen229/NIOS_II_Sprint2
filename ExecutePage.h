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

/*
 * Name: validpress
 * Purpose: Checks the button of the corresponding page and make sure the press is within the bound of the buttons
 * Parameters: point , page , int
 */
int validpress(Point release, Page currentPage, int * buttonPressed);

/*
 * Name: validkeypress
 * Purpose: Checks the keys of the corresponding page and make sure the press is within the bound of the keys
 * Parameters: point , page , int
 */
int validkeypress(Point release, Page currentPage, int * keyPressed);

/*
 * Name: validinputboxpress
 * Purpose: Checks the inputboxes of the corresponding page and make sure the press is within the bound of the box
 * Parameters: point , page , int
 */
int validinputboxpress(Point release, Page currentPage, int * inputBoxPressed);

/*
 * Name: validsdboxpress
 * Purpose: Checks the sdbox of the corresponding page and make sure the press is within the bound of the sdboxes
 * Parameters: point , page , int
 */
int validsdboxpress(Point release, Page currentPage, int * sdBoxPressed);

/**
 * Name : checkChoice
 * Purpose:Evaluates which area was pressed and returns the value
 * 			of the key, inputbox, button, or sdbox pressed.
 * Parameters: point , page , button , sdbox;
 *
 */
int checkChoice(Point p, Page * globalCurrentPage, int *keyPressed,
		int *inputBoxPressed, int *buttonPressed, int * sdBoxPressed);





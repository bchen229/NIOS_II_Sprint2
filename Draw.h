/*
 *
 * Name: drawButton
 * Description: This function draws the rectangular box as a button, using the DrawRectangleFill function implemented
 * Parameters: Button
 *
 */
void drawButton(Button *b);

/*
 *
 * Name: drawObject
 * Description: This function draws the rectangular box as a object, using the DrawRectangleFill function implemented
 * Parameters: Object
 *
 */
void drawObject(Object *o);

/*
 *
 * Name: drawKey
 * Description: This function draws the rectangular box as a key, using the DrawRectangleFill function implemented
 * Parameters: Key
 *
 */
void drawKey(Key *k);

/*
 *
 * Name: drawPage
 * Description: This function draws a page based on the number of boxes,object and buttons of the page
 * Parameters: Page
 *
 */
void drawPage(Page * currentScreen);

/**
 * Draw Menus
 */
void drawMenu();

/*
 *
 * Name: drawKeyboard
 * Description: This function draws the keyboard on the page being passed
 * Parameters: Page
 *
 */
void drawKeyboard(Page * currentScreen);

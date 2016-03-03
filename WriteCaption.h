/*
 *
 * Name: WriteCaptionButton
 * Description: This function writes a caption to the centre of button struct
 * Parameters: Button , font color , backgroundcolor
 *
 */
void writeCaptionButton(Button * button, int fontColor, int backgroundColor);

/*
 *
 * Name: WriteCaptionObject
 * Description: This function writes a text to the centre of the Object struct
 * Parameters: Object , font colour , backgroundcolor
 *
 */
void writeCaptionObject(Object * object, int fontColor, int backgroundColor);

/*
 *
 * Name: WriteCaptionObjectLarge
 * Description: This function writes a text to the centre of the Larger Objects struct
 * Parameters: Object , font colour , backgroundcolor
 *
 */
void writeCaptionObjectLarge(Object * object, int fontColor,
		int backgroundColor);

/*
 *
 * Name: WriteCaptionKey
 * Description: This function writes a text to the centre of the key struct
 * Parameters: key , font colour , backgroundcolor
 *
 */
void writeCaptionKey(Key * k, int fontColor, int backgroundColor);

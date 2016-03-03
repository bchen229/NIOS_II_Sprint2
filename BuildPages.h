// function declarations for BuildPages.c

/**
 * Constructor for home page
 */
void buildHomePage(Page *home);

/**
 * Build "Destination" page
 */
void buildDestPage(Page *destination);

/**
 * Build Map Page
 */
void buildMapPage(Page *Map);

/**
 * Build "self" page
 */
void buildSelfPage(Page *self);

/**
 * Build "Keys" page
 */
void buildKeysPage(Page *keys);

/**
 * Constructs the menu structure and contents
 * and returns the home page
 */
Page* buildMenu(void);

/**
 * Builds the password login page
 */
void buildPWLoginPage(Page *password);

/**
 * Builds the password setup page
 */
void buildPWSetupPage(Page *passwordSetup);

/**
 * Builds the logging settings page
 */
void buildLoggingSettingsPage(Page * loggingSettings);

/**
 * Builds the panic page
 */
void buildPanicPage(Page *panicPage);

/**
 * Builds the address page
 */
void buildAddressesPage(Page *addresses);

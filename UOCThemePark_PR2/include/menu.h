#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

typedef enum {	MAIN_MENU_NO_OPTION = -1, 
				MAIN_MENU_LOAD, MAIN_MENU_SAVE, 
				MAIN_MENU_VISITOR, MAIN_MENU_FAIRGROUNDRIDE, 
				MAIN_MENU_STAT, MAIN_MENU_EXIT} tMainMenuOptions;

typedef enum {	VISITOR_MENU_NO_OPTION = -1, 
				VISITOR_MENU_LIST, VISITOR_MENU_LIST_ORDERED_DESC, 
				VISITOR_MENU_ADD, VISITOR_MENU_DEL, 
                VISITOR_MENU_CLEAR_ALL, VISITOR_MENU_SELECT_PREMIUM_VISITORS,
                VISITOR_MENU_EXIT} tVisitorMenuOptions;

typedef enum {	FAIRGROUNDRIDE_MENU_NO_OPTION = -1, 
				FAIRGROUNDRIDE_MENU_LIST, FAIRGROUNDRIDE_MENU_ADD, 
				FAIRGROUNDRIDE_MENU_SELECT_BY_CRITERIA,
				FAIRGROUNDRIDE_MENU_OUTOFORDER_BY_AREA,
				FAIRGROUNDRIDE_MENU_UPDATE_AVERAGEAWAITINGTIME,
				FAIRGROUNDRIDE_VISITORS_RECOMMENDATION,
                FAIRGROUNDRIDE_MENU_EXIT} tFairgroundRideMenuOptions;


/* Define the stats menu options type */
typedef enum {	STAT_MENU_NO_OPTION = -1,
				STAT_MENU_AVG_TIME_IN_PARK,
				STAT_MENU_MIN_MAX_AGE_VISITOR,
				STAT_MENU_BEST_FAIRGROUNDRIDE_RATIO,
				STAT_MENU_SMALLEST_FAIRGROUNDRIDE_COST_TRIP,
				STAT_MENU_PARK_AVERAGE_WAITING_TIME,
                STAT_MENU_EXIT} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();


/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the visitor management menu options */
void printVisitorMenuOptions();

/* Get the option for the visitor management menu */
tVisitorMenuOptions getVisitorMenuOption();

/* Perform the actions for the visitor management menu */
void visitorMenu(tAppData *appData);

/* Print the fairground rides management menu options */
void printFairgroundRideMenuOptions();

/* Get the option for the fairground rides management menu */
tFairgroundRideMenuOptions getFairgroundRideMenuOption();

/* Perform the actions for the fairground rides management menu */
void fairgroundRideMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the status menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the status menu */
void statMenu(tAppData appData);


								

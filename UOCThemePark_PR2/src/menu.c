#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "iomenu.h"
#include "fairgroundRide.h"
#include "visitor.h"

int getOption(int numOptions) {
	int option = MAIN_MENU_NO_OPTION;
		
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
			scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("[ERROR] Incorrect option.\n");
		}
	}
	 return option;
}


tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(6)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
	tError retVal;
		
	/* Assign the data path */
	appDataSetPathApp(appData,"../");
		
	/* Start the menu */
	option = MAIN_MENU_NO_OPTION;
	
	while (option != MAIN_MENU_EXIT) {
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
		
		/* Do the action for the given option */
		if (option == MAIN_MENU_LOAD) {
			appDataLoadFromFile(appData,&retVal);
			if(retVal==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
		} else if (option == MAIN_MENU_SAVE) {
			appDataSaveToFile(*appData,&retVal);
			if(retVal==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
		} else if (option == MAIN_MENU_VISITOR) {
			visitorMenu(appData);
		} else if (option == MAIN_MENU_FAIRGROUNDRIDE) {
			fairgroundRideMenu(appData);
		} else if (option == MAIN_MENU_STAT) {
			statMenu(*appData);
		} 
	} 
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage visitors\n");
	printf("4) Manage fairground rides\n");
	printf("5) View statistics\n");
	printf("6) Exit\n");	
}

/*********************************
 **   VISITOR MANAGEMENT MENU **
*********************************/
void printVisitorMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Visitors\n");
	printf("=======================\n");
	printf("1) List visitors\n");	
	printf("2) List visitors descendant ordered\n");
	printf("3) Add visitor\n");
	printf("4) Delete visitor\n");	
	printf("5) Clear all visitors\n");
	printf("6) Select premium and large family, by age\n");
	printf("7) Exit\n");	
}
	
tVisitorMenuOptions getVisitorMenuOption() {
	/* Convert to the correct type */
	return (tVisitorMenuOptions)(getOption(7)-1);  
}

void visitorMenu(tAppData *appData) {
	
	tVisitorMenuOptions option;
	tVisitor newVisitor;
	tVisitorTable visitorTable, resultTable;
	char visitorStr[MAX_LINE];
	int i, pos=0;
	int selectedAge;
	tError retVal;
			
	/* Start the menu */
	option = VISITOR_MENU_NO_OPTION;
	while(option!=VISITOR_MENU_EXIT) {
		/* Show list of options and ask the user for an option */
		printVisitorMenuOptions();
		option=getVisitorMenuOption();
		
		/* Do the action for the given option */
		if (option == VISITOR_MENU_LIST ) {
			getVisitors(*appData, &visitorTable);
			printVisitorTable(visitorTable);
		} else if (option == VISITOR_MENU_LIST_ORDERED_DESC) {
			getVisitors(*appData, &visitorTable);
			visitorTableSort(&visitorTable);
			printVisitorTable(visitorTable);
		} else if (option == VISITOR_MENU_ADD) {
			printf("Enter the information for the new visitor:\n>> ");
			readVisitor(&newVisitor,&retVal);
			
			if(retVal == OK) {
				getVisitorStr(newVisitor, MAX_LINE, visitorStr);
				
				addVisitor(appData, newVisitor, &retVal);
				if(retVal==OK){
					printf("Visitor added: %s\n", visitorStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("[ERRROR] A visitor with the same ID already exists. Visitor not added\n");
				} else {
					printf("[ERROR] No more space in visitor table. Visitor not added\n");
				}
			} else {
				printf("[ERROR] Error in input. Visitor not added\n");
			}
			
		} else if (option == VISITOR_MENU_DEL) {
			getVisitors(*appData, &visitorTable);			
			/* Print the visitors */			
			printVisitorTable(visitorTable);		

			if (visitorTable.nVisitors > 0) {
				/* Ask the number of the register to be removed */
				printf("Enter the position of the visitor to delete:\n>> ");
				pos=getOption(visitorTable.nVisitors);
				/* Remove the selected visitor */				
				removeVisitor(appData, visitorTable.table[pos-1]);
			}
		} else if (option == VISITOR_MENU_CLEAR_ALL) {
			getVisitors(*appData, &visitorTable);	
			for (i= 0; i< visitorTable.nVisitors; i++) {
				/* Remove the visitor */				
				removeVisitor(appData, visitorTable.table[i]);
			}
		} else if (option == VISITOR_MENU_SELECT_PREMIUM_VISITORS) {
            /* Ask the age to be selected */
			printf("Enter the selected age:\n>> ");
			scanf("%d", &selectedAge);			
			if (selectedAge < 0) {
				printf("[ERROR] Error in input criteria\n");
			}
			else {
				getVisitors(*appData, &visitorTable);
				visitorTableSelect(visitorTable, selectedAge, &resultTable); 
				printVisitorTable(resultTable);
			}
		} 
	} 
}

/********************************
 **   FAIRGROUNDRIDE MANAGEMENT MENU **
********************************/
void printFairgroundRideMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage fairground rides\n");
	printf("=======================\n");
	printf("1) List fairground rides\n");	
	printf("2) Add fairground ride\n"); 
	printf("3) Select fairground rides by criteria\n");
	printf("4) Select fairground rides out of order by area map\n");
	printf("5) Update average waiting time fairground rides\n");
	printf("6) List recommended fairground rides to visitors\n");
	printf("7) Exit\n");	
}

tFairgroundRideMenuOptions getFairgroundRideMenuOption() {
	/* Convert to the correct type */
	return (tFairgroundRideMenuOptions)(getOption(7)-1);
}

void fairgroundRideMenu(tAppData *appData) {
	tError retVal = OK;
	tFairgroundRideMenuOptions option;
	tFairgroundRideTable fairgroundRideTable, resultTable;
	tFairgroundRide newFairgroundRide;
	char fairgroundRideStr[MAX_LINE];
	
	char selectedAreaMap;
	char selectedAreasMap[2];
	
	int numVisitorsQueue, minutesDownUp, percEmptySeats;
	
	int selectedType;
	int selectedCategory;
	
	/* Start the menu */
	option = FAIRGROUNDRIDE_MENU_NO_OPTION;
	
	while(option!=FAIRGROUNDRIDE_MENU_EXIT) 
	{
		/* Show list of options and ask the user for an option */
		printFairgroundRideMenuOptions();
		option=getFairgroundRideMenuOption();
		
		/* Do the action for the given option */
		if (option == FAIRGROUNDRIDE_MENU_LIST) {
			getFairgroundRides(*appData, &fairgroundRideTable);
			printFairgroundRideTable(fairgroundRideTable);
		} else if (option == FAIRGROUNDRIDE_MENU_ADD) {
			readFairgroundRide(&newFairgroundRide,&retVal);
		
			if(retVal == OK) {
				getFairgroundRideStr(newFairgroundRide, MAX_LINE, fairgroundRideStr);
				
				addFairgroundRide(appData, newFairgroundRide, &retVal);
				if (retVal == OK) {
					printf("Fairground ride added: %s\n", fairgroundRideStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("[ERROR] A fairground ride with the same ID already exists. Fairground ride not added.\n");
				} else {
					printf("[ERROR] No more space in fairground ride table. Fairground ride not added.\n");
				}
			} else {
				printf("[ERROR] Error in input. Fairground ride not added\n");
			}
		} else if (option == FAIRGROUNDRIDE_MENU_SELECT_BY_CRITERIA) {
            /* Ask the criteria to be selected */
			printf("Enter the selected type (1 digit being 0=ROLLER_COASTER 1=VIRTUAL_SIMULATOR 2=CAR_TRACK 3=BABY_CIRCUITS 4=MAT 5=SHOW_CINEMA 6=TERROR_PASSAGE):\n>> "); 
			scanf("%d", &selectedType);			
			printf("Enter the selected category (1 digit being 0=STRONG 1=MODERATE 2=CHILDISH):\n>>");
			scanf("%d", &selectedCategory);	
			getchar();
			printf("Enter the selected area of the park (an upper letter):\n>> ");
			scanf("%c", &selectedAreaMap);			
			
			if ( (selectedType <0 || selectedType > 6) ||
					(selectedCategory < 0 || selectedCategory > 2) ||
					(selectedAreaMap < 'A' || selectedAreaMap > 'Z') )  {
				printf("[ERROR] Error in input criteria\n");
			}
			else {
				getFairgroundRides(*appData, &fairgroundRideTable);
				fairgroundRideTableSelect(fairgroundRideTable, (tFairgroundRideType)selectedType, 
                      (tFairgroundRideCategory)selectedCategory, selectedAreaMap, &resultTable);
				printFairgroundRideTable(resultTable);
			}
		} else if (option == FAIRGROUNDRIDE_MENU_OUTOFORDER_BY_AREA) {
            /* Ask the criteria to be selected */
			printf("Enter the first selected area of the park (an upper letter):\n>> ");
			scanf("%c", &(selectedAreasMap[0]));
			getchar();
			printf("Enter the second selected area of the park (an upper letter):\n>> ");
			scanf("%c", &(selectedAreasMap[1]));			
			if ( (selectedAreasMap[0] < 'A' || selectedAreasMap[0] > 'Z') ||
				 (selectedAreasMap[1] < 'A' || selectedAreasMap[1] > 'Z')) {
				printf("[ERROR] Error in input criteria\n");
			}
			else {
				getFairgroundRides(*appData, &fairgroundRideTable);
				fairgroundRideTableOutOfOrder(fairgroundRideTable, selectedAreasMap, &resultTable);
				printFairgroundRideTable(resultTable);			
			}
        } else if (option == FAIRGROUNDRIDE_MENU_UPDATE_AVERAGEAWAITINGTIME) {
			printf("Number of visitors before me:\n>> ");
			scanf("%d", &numVisitorsQueue);

			printf("Minutes to get up and down fairground ride:\n>> ");
			scanf("%d", &minutesDownUp);

			printf("Percentatge empty seats (integer value between 0 and 100 (both included)):\n>> ");
			scanf("%d", &percEmptySeats);
			
			if (numVisitorsQueue < 0 || minutesDownUp < 0 || (percEmptySeats < 0 || percEmptySeats > 100)) {
				printf("[ERROR] Error in input criteria\n");
			} 
			else {
				getFairgroundRides(*appData, &fairgroundRideTable);
				fairgroundRideTableUpdateWaitingTime(&fairgroundRideTable, numVisitorsQueue, minutesDownUp, percEmptySeats);
				printFairgroundRideTable(fairgroundRideTable);
			}
		} else if (option == FAIRGROUNDRIDE_VISITORS_RECOMMENDATION) { 
			printf("Area of the park (an upper letter):\n>> "); 
			scanf("%c", &selectedAreaMap);		
			if (selectedAreaMap < 'A' || selectedAreaMap > 'Z') {
				printf("[ERROR] Error in input criteria\n");
			}
			else {
				printVisitorRecommendationsByHeight(*appData, selectedAreaMap);
			}
		}
	} 	
}


/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get average time in park\n");
	printf("2) Get minimum and maximun age of visitor in park\n");	
	printf("3) Get best fairground ride ratio\n");
	printf("4) Get smallest fairground ride cost trip\n");
	printf("5) Get average waiting time all fairground rides\n");
	printf("6) Exit\n");	
}

tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(6)-1);
}

void statMenu(tAppData appData) 
{
	tStatMenuOptions option;
	tVisitorTable visitorTable;
	tFairgroundRideTable fairgroundRideTable;
    float avg, bestRatio, smallestCostTrip, averageWaitingTime;
	int minAge, maxAge, percEmptySeats;
	
	/* Start the menu */
	option = STAT_MENU_NO_OPTION;
	while(option!=STAT_MENU_EXIT) {
		/* Show list of options and ask the user for an option */
		printStatMenuOptions();
		option=getStatMenuOption();
		
		/* Do the action for the given option */
		if (option == STAT_MENU_AVG_TIME_IN_PARK) {			
			getVisitors(appData, &visitorTable);
			avg = (float)visitorTableGetAverageTimeInPark(visitorTable);
            printf("Average time in park: %.2f\n", avg);
		}
		else if (option == STAT_MENU_MIN_MAX_AGE_VISITOR) {			
			getVisitors(appData, &visitorTable);
			visitorTableGetMinMaxAgeVisitor(visitorTable, &minAge, &maxAge);
			if (minAge == -1 && maxAge == -1) {
				printf("No visitors in park\n");
			}
			printf("Minimum age: %d and maximum age: %d\n", minAge, maxAge);
		}
		else if (option == STAT_MENU_BEST_FAIRGROUNDRIDE_RATIO) {			
			getFairgroundRides(appData, &fairgroundRideTable);
			bestRatio = (float)fairgroundRideTableGetBestRatio(fairgroundRideTable);
			printf("Best ratio: %.2f\n", bestRatio);
		}
		else if (option == STAT_MENU_SMALLEST_FAIRGROUNDRIDE_COST_TRIP) {
			getFairgroundRides(appData, &fairgroundRideTable);

			printf("Percentatge empty seats (integer value between 0 and 100 (both included)):\n");
			scanf("%d", &percEmptySeats);
			if (percEmptySeats < 0 || percEmptySeats > 100) {
				printf("[ERROR] Error in input criteria\n");
			}
			else {
				smallestCostTrip = (float)fairgroundRideGetSmallestCostTrip(fairgroundRideTable, percEmptySeats);
				printf("Smallest cost: %.2f€\n", smallestCostTrip);
			}
		}
		else if (option == STAT_MENU_PARK_AVERAGE_WAITING_TIME) {
			getFairgroundRides(appData, &fairgroundRideTable);
			
			averageWaitingTime = (float)fairgroundRideTableGetAverageWaitingTimePark(fairgroundRideTable);
			printf("Average waiting time all fairground rides: %.2f minutes\n", averageWaitingTime);
			
		}
	}
}




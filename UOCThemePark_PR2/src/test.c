#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "util.h"
#include "visitor.h"
#include "fairgroundRide.h"
#include "management.h"
#include "queue.h"
#include "stack.h"

/*
 * VISITOR1:	45 years|premium|not has disability|large family|not discount|GENERAL|682 minutes in park
 * VISITOR2:	70 years|not premium|not has disability|large family|discount|FOR A WALK|415 minutes in park
 * VISITOR3:	46 years|premium|has disability|large family|not discount|GENERAL FAST PASS|925 minutes in park
 * VISITOR4:	20 years|premium|not has disability|not large family|not discount|GENERAL FAST PASS|715 minutes in park
 * VISITOR5:	50 years|premium|not has disability|large family|not discount|GENERAL FAST PASS|810 minutes in park
 * VISITOR6:	2  years|not premium|not has disability|large family|not discount|GENERAL|626 minutes in park
 * VISITOR7:	6  years|premium|not has disability|large family|not discount|GENERAL FAST PASS|305 minutes in park
 * VISITOR8:	21 years|not premium|not has disability|not large family|not discount|FOR A WALK|235 minutes in park
 * VISITOR9:	10 years|not premium|not has disability|not large family|not discount|FOR A WALK|734 minutes in park
 * VISITOR10:	45 years|premium|not has disability|large family|not discount|GENERAL|682 minutes in park
 * VISITOR11:	45 years|premium|not has disability|large family|not discount|GENERAL|682 minutes in park
 * VISITOR12:	10 years|not premium|not has disability|not large family|not discount|FOR A WALK|734 minutes in park
 * VISITOR13:	9 years|not premium|not has disability|not large family|not discount|FOR A WALK|734 minutes in park
 */ 
#define VISITOR1 "10 LUISA MARTINEZ 00000000T 12/2/1975 BARCELONA 155.00 1 0 1 0 0.00 1 9:33 20:55 0"	
#define VISITOR2 "20 CARMEN FUENTES 87654321V 14/5/1950 CORDOBA 170.50 0 0 1 1 10.00 0 11:00 17:55 0"
#define VISITOR3 "30 PETER WILLIAMS 98765432N 27/1/1974 DUBLIN 180.60 1 1 1 0 0.00 2 8:30 23:55 0"
#define VISITOR4 "40 JUSTINE LECLERC 12345678Z 16/12/2000 PARIS 195.00 1 0 0 0 0.00 2 10:05 22:00 0"
#define VISITOR5 "50 JUSTINE LEBLANC 52455666U 29/11/1970 CANNES 165.10 1 0 1 0 0.00 2 9:45 23:15 0"
#define VISITOR6 "60 MICHELLE TANER 85471235T 7/6/2018 ROMA 90.10 0 0 1 0 0.00 1 10:00 20:26 0"
#define VISITOR7 "70 DONNA JOE 52425325S 16/4/2014 SIDNEY 115.10 1 0 1 0 0.00 2 12:00 17:05 0"
#define VISITOR8 "80 KIMBERLY GIBLER 78954125M 18/6/1999 ATLANTA 180.10 0 0 0 0 0.00 0 10:33 14:28 0"
#define VISITOR9 "90 PAULA GARCIA 12345214D 6/1/2010 MADRID 139.99 0 0 0 0 0.00 0 9:07 21:21 0"
#define VISITOR10 "100 JUSTINE GARCIA 33345214J 12/2/1975 BARCELONA 155.00 1 0 1 0 0.00 1 9:33 20:55 0"	
#define VISITOR11 "110 PETER FUENTES 44345214Q 12/2/1975 LONDRES 155.00 1 0 1 0 0.00 1 9:33 20:55 0"
#define VISITOR12 "120 LUISA GIBLER 67745214O 6/1/2010 GIRONA 155.00 1 0 1 0 0.00 1 9:33 20:55 0"
#define VISITOR13 "130 MARISA ORTIZ 55553332U 6/1/2011 ASTORGA 155.00 1 0 1 0 0.00 1 9:33 20:55 0"

/*
 * FRIDE1:	ROLLER COASTER|STRONG|WORKING|FORBIDDEN|FORBIDDEN|FORBIDDEN|ALLOWED
 * FRIDE2:	VIRTUAL SIMULATOR|MODERATE|WORKING|FORBIDDEN|FORBIDDEN|ALLOWED WITH COMPANION|ALLOWED
 * FRIDE3:	CAR TRACK|STRONG|OUT OF ORDER|FORBIDDEN|FORBIDDEN|ALLOWED WITH COMPANION|ALLOWED
 * FRIDE4:	BABY CIRCUITS|CHILDISH|WORKING|ALLOWED WITH COMPANION|ALLOWED|ALLOWED|ALLOWED
 * FRIDE5:	BABY CIRCUITS|CHILDISH|OUT OF ORDER|ALLOWED|ALLOWED|ALLOWED|ALLOWED
 * FRIDE6:	MAT|CHILDISH|OUT OF ORDER|ALLOWED|ALLOWED|ALLOWED|ALLOWED
 * FRIDE7:	SHOW CINEMA|CHILDISH|WORKING|ALLOWED WITH COMPANION|ALLOWED WITH COMPANION|ALLOWED|ALLOWED
 * FRIDE8:	TERROR PASSAGE|STRONG|OUT OF ORDER|FORBIDDEN|FORBIDDEN|ALLOWED WITH COMPANION|ALLOWED
 * FRIDE9:	ROLLER COASTER|MODERATE|WORKING|FORBIDDEN|ALLOWED WITH COMPANION|ALLOWED WITH COMPANION|ALLOWED
 */ 
#define FAIRGROUNDRIDE1 "10 DRAGON 0 0 A 0 0 0 0 2 90 120 12 1 6.50 1"			
#define FAIRGROUNDRIDE2 "20 INFERNO 1 1 A 0 0 0 1 2 100 100 12 1 10.00 1"		
#define FAIRGROUNDRIDE3 "30 CRASH 2 0 B 1 0 0 1 2 20 24 12 0 0.00 0"			
#define FAIRGROUNDRIDE4 "40 YOGUI 3 2 C 0 1 2 2 2 30 60 10 1 3.50 0" 
#define FAIRGROUNDRIDE5 "50 CARROUSSEL 3 2 A 1 2 2 2 2 10 110 80 1 4.00 0"
#define FAIRGROUNDRIDE6 "60 JUMPING 4 2 A 1 2 2 2 2 10 180 8 1 5.00 0"
#define FAIRGROUNDRIDE7 "70 CINETOUR 5 2 C 0 1 1 2 2 90 300 60 0 0.00 0"
#define FAIRGROUNDRIDE8 "80 FREDDY 6 0 A 1 0 0 1 2 140 330 12 1 10.00 1"
#define FAIRGROUNDRIDE9 "90 TAMITAMI 0 1 B 0 0 1 1 2 45 125 22 0 0.0 1"

/*
 * MANAGEMENT1:	Management of fg.ride 10 with no visitor in any queue nor stack
 */ 
#define MANAGEMENT1 "10"	
#define EMPTY_QUEUE "0"
#define EMPTY_STACK "0"

void runTests()
{
	int passedTestPR1=0, passedTestPR2=0;
	int totalTestPR1=0, totalTestPR2=0;
    float ratioPR1= 0.0, ratioPR2= 0.0, ratioTotal= 0.0;

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);
	
	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");
    if (totalTestPR1 > 0)
        ratioPR1= (float)passedTestPR1/totalTestPR1*100.0;
    printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, ratioPR1);

    if (totalTestPR2 > 0)
        ratioPR2= (float)passedTestPR2/totalTestPR2*100.0;
    printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, ratioPR2);
    
    if (totalTestPR1+totalTestPR2 > 0) {
        ratioTotal= (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0;
	}
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, ratioTotal);
	printf("===================================\n");	
}

/*************
 * PR1 TESTS *
 *************/
 
void runTestsPR1(int *totalTest, int *passedTest) 

{
	*totalTest=0;
	*passedTest=0;

    testCopyCompare(totalTest, passedTest);
    testSelection(totalTest, passedTest);
    testFilterCombination(totalTest, passedTest);
    testStatistics(totalTest, passedTest);
    testTableOperation(totalTest, passedTest);
}

void testCopyCompare(int *totalTest, int *passedTest)
{
	tVisitor v1, v1Copy, v2, v3, v4;

	printf("==================================\n");
	printf(" DATE AND TIME COPY (Exercise 3)\n");
	printf("==================================\n");

	printf("\nTest 3.1: Copy dates");
	(*totalTest)++;
	tDate date1, date2; 
	dateInit(&date1, 3, 3, 2000);
	dateCopy(&date2, date1);
	if (dateCompare(date1, date2) == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;	
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.2: Copy times");
	(*totalTest)++;
	tTime time1, time2; 
	timeInit(&time1, 22, 22);
	timeCopy(&time2, time1);

	if (timeCompare(time1, time2) == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;	
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("==============================================\n");
	printf(" VISITORS COPY AND COMPARISON (Exercise 3)\n");
	printf("==============================================\n");

	printf("\nTest 3.3: Copy visitor");
	(*totalTest)++;
	getVisitorObject(VISITOR1, &v1);
	visitorCopy(&v1Copy, v1);
    if (visitorCompare(v1,v1Copy) == 0 && v1.id == v1Copy.id){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.4: Compare equal visitors");
	(*totalTest)++;
	getVisitorObject(VISITOR1, &v1);
    if (visitorCompare(v1,v1) == 0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.5: Comparison, first visitor greater than second");
	(*totalTest)++;
	getVisitorObject(VISITOR4, &v3);
	getVisitorObject(VISITOR5, &v4);
	if (visitorCompare(v3, v4) > 0){
		   printf("\n\t-> OK\n");
			(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.6: Compare case-unsensitive strings");
	(*totalTest)++;
	visitorCopy(&v2, v1);
	strcpy(v2.name, "Luisa");
	strcpy(v2.surname, "Martinez");
	strcpy(v2.docNumber, "00000000t");
	strcpy(v2.city, "BaRcElOnA");
	
	if (visitorCompare(v1, v2) == 0){
		   printf("\n\t-> OK\n");
			(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}

void testSelection(int *totalTest, int *passedTest) 
{
	tVisitorTable visitors, visitorsEmpty, result;
	tVisitor v1, v2, v3, v4, v5;
	tError retVal;

    getVisitorObject(VISITOR1, &v1);
    getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
    getVisitorObject(VISITOR5, &v5);

    visitorTableInit(&visitorsEmpty);	
    visitorTableInit(&result);
    visitorTableInit(&visitors);	

    visitorTableAddElement(&visitors, v1, &retVal);
    visitorTableAddElement(&visitors, v2, &retVal);
    visitorTableAddElement(&visitors, v3, &retVal);
    visitorTableAddElement(&visitors, v4, &retVal);
    visitorTableAddElement(&visitors, v5, &retVal);

	printf("=================================================\n");
	printf(" VISITOR SELECTION (Exercise 4)\n");
	printf("=================================================\n");
	printf("\nTest 4.1: Select visitors on an empty table");
	(*totalTest)++;

	visitorTableSelect(visitorsEmpty, 45, &result);
	if(result.nVisitors == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}

	printf("\nTest 4.2: One visitor coincident selection in non empty table");
	(*totalTest)++;	
    visitorTableSelect(visitors, 49, &result);
	if(result.nVisitors	== 1) {
		if(visitorCompare(result.table[0], v5) != 0) {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}

	printf("\nTest 4.3: Visitors from coincident selection in non empty table");
	(*totalTest)++;	
    visitorTableSelect(visitors, 45, &result);
	if(result.nVisitors	== 2) {
		if((visitorCompare(result.table[0], v3) != 0) ||
           (visitorCompare(result.table[1], v5) != 0))  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}

	printf("\nTest 4.4: Visitors no coincident selection in non empty table");
	(*totalTest)++;	
    visitorTableSelect(visitors, 70, &result);
	if(result.nVisitors	== 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}

	printf("\nTest 4.5: Apply discounts on an empty table");
	(*totalTest)++;	
    visitorTableSelect(visitorsEmpty, 35, &result);

	if(result.nVisitors	== 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}

	printf("\nTest 4.6: Apply discount on coincident selection in non empty table");
	(*totalTest)++;	
	visitorTableApplyDiscounts(visitors, &result);
	if(result.nVisitors	== 3) {
		if( ( ((result.table[0].id == 10 && result.table[0].hasDiscount && result.table[0].discount == 15.0) && 
			   (result.table[1].id == 30 && result.table[1].hasDiscount && result.table[1].discount == 15.0) && 
			   (result.table[2].id == 50 && result.table[2].hasDiscount && result.table[2].discount == 15.0)) ) ) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		} else {
            printf("\n\t-> FAIL (Result values are not correct). Expected:\n");
            printf("First visitor: id %d, has discount %d, discount %.2f\n", result.table[0].id, result.table[0].hasDiscount, result.table[0].discount);
            printf("Second visitor: id %d, has discount %d, discount %.2f\n", result.table[1].id, result.table[1].hasDiscount, result.table[1].discount);
            printf("Third visitor: id %d, has discount, %d, discount %.2f\n", result.table[2].id, result.table[2].hasDiscount, result.table[2].discount);
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}
    
	printf("\nTest 4.7: Apply discount on non coincident selection in non empty table");
	(*totalTest)++;	
	visitors.table[0].isLargeFamily = false;
	visitors.table[2].purchasedTicket = FOR_A_WALK;
	visitors.table[4].isPremium = false;
	
	visitorTableApplyDiscounts(visitors, &result);
	if(result.nVisitors	== 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nVisitors);
	}	
}	

void testFilterCombination(int *totalTest, int *passedTest) 
{
	tVisitor v1, v2, v3, v4, v5, v6, v7, v8, v9;
	tFairgroundRide f1, f2, f3, f4, f5, f6, f7, f8, f9;
	tVisitorTable visitors, visitorsEmpty;
	tFairgroundRideTable fairgroundRides, fairgroundRidesEmpty;
	tFairgroundRideTable result;
	tError retVal;

    getVisitorObject(VISITOR1, &v1);
    getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
    getVisitorObject(VISITOR5, &v5);
    getVisitorObject(VISITOR6, &v6);
    getVisitorObject(VISITOR7, &v7);
    getVisitorObject(VISITOR8, &v8);
    getVisitorObject(VISITOR9, &v9);

	visitorTableInit(&visitorsEmpty);	
	visitorTableInit(&visitors);	
	visitorTableAddElement(&visitors, v1, &retVal);
    visitorTableAddElement(&visitors, v2, &retVal);
    visitorTableAddElement(&visitors, v3, &retVal);
    visitorTableAddElement(&visitors, v4, &retVal);
	visitorTableAddElement(&visitors, v5, &retVal);
	visitorTableAddElement(&visitors, v6, &retVal);
    visitorTableAddElement(&visitors, v7, &retVal);
    visitorTableAddElement(&visitors, v8, &retVal);
	visitorTableAddElement(&visitors, v9, &retVal);

	getFairgroundRideObject(FAIRGROUNDRIDE1, &f1);
	getFairgroundRideObject(FAIRGROUNDRIDE2, &f2);
	getFairgroundRideObject(FAIRGROUNDRIDE3, &f3);
	getFairgroundRideObject(FAIRGROUNDRIDE4, &f4);
	getFairgroundRideObject(FAIRGROUNDRIDE5, &f5);
	getFairgroundRideObject(FAIRGROUNDRIDE6, &f6);
	getFairgroundRideObject(FAIRGROUNDRIDE7, &f7);
	getFairgroundRideObject(FAIRGROUNDRIDE8, &f8);
	getFairgroundRideObject(FAIRGROUNDRIDE9, &f9);	

	fairgroundRideTableInit(&fairgroundRidesEmpty);
	fairgroundRideTableInit(&fairgroundRides);

	fairgroundRideTableAddElement(&fairgroundRides, f1, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f2, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f3, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f4, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f5, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f6, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f7, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f8, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f9, &retVal);	

	printf("=================================================\n");
	printf(" FILTER COMBINATION (Exercise 5)\n");
	printf("=================================================\n");

	printf("\nTest 5.1: Visitor recommendation: on an empty fairground ride table empty");
	(*totalTest)++;
	visitorRecommendationByHeight(v1, fairgroundRidesEmpty, 'A', &result);
	if (result.nFairgroundRides == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nFairgroundRides);
	}

	printf("\nTest 5.2: Visitor recommendation (less than 100): ");
	(*totalTest)++;
	visitorRecommendationByHeight(v8, fairgroundRides, 'A', &result);
	if (result.nFairgroundRides == 2) {
		if(fairgroundRideCompare(result.table[0], f1) != 0 ||
		   fairgroundRideCompare(result.table[1], f2) != 0)  {
			   printf("\n\t-> FAIL (Result values are not correct)\n");
		} 
		else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nFairgroundRides);
	}	

	printf("\nTest 5.3: Visitor recommendation (between 100 and 120): ");
	(*totalTest)++;
    
	visitorRecommendationByHeight(v7, fairgroundRides, 'B', &result);
	if (result.nFairgroundRides == 1) {
		if(fairgroundRideCompare(result.table[0], f9) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nFairgroundRides);
	}	

	printf("\nTest 5.4: Visitor recommendation (between 120 and 140): ");
	(*totalTest)++;
    
	visitorRecommendationByHeight(v9, fairgroundRides, 'C', &result);
	if (result.nFairgroundRides == 2) {
		if(fairgroundRideCompare(result.table[0], f4) != 0 ||
		   fairgroundRideCompare(result.table[1], f7) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nFairgroundRides);
	}	

	printf("\nTest 5.5: Visitor recommendation (greater than 140): ");
	(*totalTest)++;

	visitorRecommendationByHeight(v3, fairgroundRides, 'A', &result);
	if (result.nFairgroundRides == 2) {
		if(fairgroundRideCompare(result.table[0], f1) != 0 ||
		   fairgroundRideCompare(result.table[1], f2) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nFairgroundRides);
	}	
}

void testStatistics(int *totalTest, int *passedTest) 
{
	tVisitor v1, v2, v3, v4, v5, v6, v7, v8, v9;
	tVisitorTable visitors, visitorsEmpty;
	float avg;
	char strAvg[MAX_LINE];
	int minAge, maxAge;
	tError retVal;

	getVisitorObject(VISITOR1, &v1);
	getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
	getVisitorObject(VISITOR5, &v5);
	getVisitorObject(VISITOR6, &v6);
    getVisitorObject(VISITOR7, &v7);
    getVisitorObject(VISITOR8, &v8);
	getVisitorObject(VISITOR9, &v9);

	visitorTableInit(&visitorsEmpty);	

	printf("=================================================\n");
	printf(" STATISTICS (Exercise 6)\n");
	printf("=================================================\n");

	printf("\nTest 6.1: Average of an empty table");
	(*totalTest)++;
    avg = visitorTableGetAverageTimeInPark(visitorsEmpty);
	if (avg == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 0.0, avg);
	}

    visitorTableInit(&visitors);	
	visitorTableAddElement(&visitors, v1, &retVal);
	printf("\nTest 6.2: Average of a single visitor");
	(*totalTest)++;
	
    avg = visitorTableGetAverageTimeInPark(visitors);
	sprintf(strAvg, "%.2f", avg);
	if (strcmp(strAvg, "11.37") == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 11.37, avg);
	}
	
	visitorTableInit(&visitors);	
	visitorTableAddElement(&visitors, v1, &retVal);
    visitorTableAddElement(&visitors, v2, &retVal);
    visitorTableAddElement(&visitors, v3, &retVal);
    visitorTableAddElement(&visitors, v4, &retVal);
	visitorTableAddElement(&visitors, v5, &retVal);
	visitorTableAddElement(&visitors, v6, &retVal);
    visitorTableAddElement(&visitors, v7, &retVal);
    visitorTableAddElement(&visitors, v8, &retVal);
	visitorTableAddElement(&visitors, v9, &retVal);
	
	printf("\nTest 6.3: Average of all visitors");
	(*totalTest)++;
	
    avg = visitorTableGetAverageTimeInPark(visitors);
	sprintf(strAvg, "%.2f", avg);

	if (strcmp(strAvg, "10.09") == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 10.09, avg);
	}
	
	printf("\nTest 6.4: Minimum and maximum visitors age of an empty table");
	(*totalTest)++;
	visitorTableGetMinMaxAgeVisitor(visitorsEmpty, &minAge, &maxAge);
	if (minAge == -1 && maxAge == -1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected minimum and maximum age result. Expected [minimum age/maximum age] [%d/%d] and returned [%d/%d])\n", -1, -1, minAge, maxAge);
	}

	printf("\nTest 6.5: Minimum and maximum visitors age of a full table");
	(*totalTest)++;
	visitorTableGetMinMaxAgeVisitor(visitors, &minAge, &maxAge);
	if (minAge == 2 && maxAge == 70) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected minimum and maximum age result. Expected [minimum age/maximum age] [%d/%d] and returned [%d/%d])\n", 2, 70, minAge, maxAge);
	}
}

void testTableOperation(int *totalTest, int *passedTest) 
{
	tVisitor v1, v2, v3, v4, v5, v6, v7, v8, v9, v1Copy;
	tVisitorTable visitors, visitorsEmpty;
	tError retVal;
    
	visitorTableInit(&visitorsEmpty);    

	printf("=================================================\n");
	printf(" TABLE OPERATIONS (Exercise 7)\n");
	printf("=================================================\n");

	printf("\nTest 7.1: Ordered an empty table");
	(*totalTest)++;
    visitorTableSort(&visitorsEmpty);
	if (visitorsEmpty.nVisitors == 0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, visitorsEmpty.nVisitors);
	}

	printf("\nTest 7.2: Ordered a table with 1 element");
	visitorTableInit(&visitors);	
	getVisitorObject(VISITOR1, &v1);
	visitorTableAddElement(&visitors, v1, &retVal);

	(*totalTest)++;
    visitorTableSort(&visitors);
	if (visitors.nVisitors == 1) {
		if(visitorCompare(visitors.table[0], v1) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, visitorsEmpty.nVisitors);
	}

	printf("\nTest 7.3: Ordered a table with 2 elements (already ordered)");
	visitorTableInit(&visitors);	
	getVisitorObject(VISITOR3, &v3);
	getVisitorObject(VISITOR9, &v9);
	
	visitorTableAddElement(&visitors, v3, &retVal);
	visitorTableAddElement(&visitors, v9, &retVal);

	(*totalTest)++;
    visitorTableSort(&visitors);
	if (visitors.nVisitors == 2) {
		if(visitorCompare(visitors.table[0], v3) != 0 || 
		   visitorCompare(visitors.table[1], v9) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 2, visitors.nVisitors);
	}

	printf("\nTest 7.4: Ordered a table with 2 elements (not ordered previously)");
	visitorTableInit(&visitors);	
	getVisitorObject(VISITOR1, &v1);
	visitorCopy(&v1Copy, v1);
	v1Copy.satisfaction = 10;

	visitorTableAddElement(&visitors, v1Copy, &retVal);
	visitorTableAddElement(&visitors, v1, &retVal);
	(*totalTest)++;

    visitorTableSort(&visitors);
	if (visitors.nVisitors == 2) {
		if(visitorCompare(visitors.table[0], v1Copy) != 0 || 
		   visitorCompare(visitors.table[1], v1) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 2, visitors.nVisitors);
	}

	printf("\nTest 7.5: Ordered a table with all elements equal");
	visitorTableInit(&visitors);	
	getVisitorObject(VISITOR1, &v1);
	visitorTableAddElement(&visitors, v1, &retVal);
	visitorTableAddElement(&visitors, v1, &retVal);
	visitorTableAddElement(&visitors, v1, &retVal);
	visitorTableAddElement(&visitors, v1, &retVal);
	
	(*totalTest)++;
    visitorTableSort(&visitors);
	if (visitors.nVisitors == 4) {
		if(visitorCompare(visitors.table[0], v1) != 0 || 
		   visitorCompare(visitors.table[1], v1) != 0 || 
		   visitorCompare(visitors.table[2], v1) != 0 ||
		   visitorCompare(visitors.table[3], v1) != 0)  {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 4, visitors.nVisitors);
	}	

	getVisitorObject(VISITOR1, &v1);
	getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
	getVisitorObject(VISITOR5, &v5);
	getVisitorObject(VISITOR6, &v6);
    getVisitorObject(VISITOR7, &v7);
    getVisitorObject(VISITOR8, &v8);
	getVisitorObject(VISITOR9, &v9);

	printf("\nTest 7.6: Ordered a table with diferent elements");
	visitorTableInit(&visitors);	
	visitorTableAddElement(&visitors, v1, &retVal);
	visitorTableAddElement(&visitors, v2, &retVal);
	visitorTableAddElement(&visitors, v3, &retVal);
	visitorTableAddElement(&visitors, v4, &retVal);
	visitorTableAddElement(&visitors, v5, &retVal);
	visitorTableAddElement(&visitors, v6, &retVal);
	visitorTableAddElement(&visitors, v7, &retVal);
	visitorTableAddElement(&visitors, v8, &retVal);
	visitorTableAddElement(&visitors, v9, &retVal);

	(*totalTest)++;
    visitorTableSort(&visitors);
	if (visitors.nVisitors == 9) {
		if(visitorCompare(visitors.table[0], v3) != 0 || 
		   visitorCompare(visitors.table[1], v9) != 0 || 
		   visitorCompare(visitors.table[2], v6) != 0 ||
		   visitorCompare(visitors.table[3], v1) != 0 ||
		   visitorCompare(visitors.table[4], v8) != 0 ||
		   visitorCompare(visitors.table[5], v4) != 0 ||
		   visitorCompare(visitors.table[6], v5) != 0 ||
		   visitorCompare(visitors.table[7], v7) != 0 ||
		   visitorCompare(visitors.table[8], v2) != 0)   {
			printf("\n\t-> FAIL (Result values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 9, visitors.nVisitors);
	}	
}

/*************
 * PR2 TESTS *
 *************/

void runTestsPR2(int *totalTest, int *passedTest) 
{
	*totalTest=0;
	*passedTest=0;
	
    testCheckings(totalTest,passedTest);
    testGroupProcessing(totalTest,passedTest);
    testRideProcessing(totalTest,passedTest);
}

void testCheckings(int *totalTest, int *passedTest) 
{
    tFairgroundRideHeightRequirement access;
    tRideManagement m1;
    tFairgroundRide f1, f2, f3, f4;
    tFairgroundRideTable fairgroundRides;
    tVisitor v1, v2, v3, v4, v5, v6;
    tVisitorGroup vg1, vg2, vg3, vg6;
    tVisitorTable visitors;
	tError retVal;
	
	getFairgroundRideObject(FAIRGROUNDRIDE1, &f1);
	getFairgroundRideObject(FAIRGROUNDRIDE2, &f2);
	getFairgroundRideObject(FAIRGROUNDRIDE3, &f3);
	getFairgroundRideObject(FAIRGROUNDRIDE4, &f4);
		
	fairgroundRideTableInit(&fairgroundRides);
	fairgroundRideTableAddElement(&fairgroundRides, f1, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f2, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f3, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f4, &retVal);
	
    getVisitorObject(VISITOR1, &v1);
    getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
    getVisitorObject(VISITOR5, &v5);
    getVisitorObject(VISITOR6, &v6);
    
    visitorTableInit(&visitors);
    visitorTableAddElement(&visitors,v1,&retVal);
    visitorTableAddElement(&visitors,v2,&retVal);
    visitorTableAddElement(&visitors,v3,&retVal);
    visitorTableAddElement(&visitors,v4,&retVal);
    visitorTableAddElement(&visitors,v5,&retVal);
    visitorTableAddElement(&visitors,v6,&retVal);
    
    vg1.groupSize= 1;
    vg1.visitor= v1.id;
    vg2.groupSize= 1;
    vg2.visitor= v2.id;
    vg3.groupSize= 1;
    vg3.visitor= v3.id;
    vg6.groupSize= 2;
    vg6.visitor= v6.id;

    getManagementObject(MANAGEMENT1,&m1);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.fastPassQueue);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.singleQueue);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.mainQueue);
    
    m1.rowQueues.nRows= 3;
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[0]);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[1]);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[2]);
    
    m1.wagons.nRows= 3;
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[0]);
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[1]);
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[2]);

	printf("=================================================\n");
	printf(" CHECKINGS (Exercise 1)\n");
	printf("=================================================\n");

	printf("\nTest 1.1: Check ride: correct ride management object");
	(*totalTest)++;
	if (checkRide(m1,fairgroundRides)) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected TRUE and returned FALSE)\n");
	}

	printf("\nTest 1.2: Check ride: unknown fairground id");
	(*totalTest)++;
    m1.fairgroundId= 100;
	if (checkRide(m1,fairgroundRides)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected FALSE and returned TRUE)\n");
	}

	printf("\nTest 1.3: Check ride: fairground is out of order");
	(*totalTest)++;
    m1.fairgroundId= 30;
	if (checkRide(m1,fairgroundRides)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected FALSE and returned TRUE)\n");
	}

	printf("\nTest 1.4: Check ride: fairground with wrong persons per trip");
	(*totalTest)++;
    m1.fairgroundId= 40;
	if (checkRide(m1,fairgroundRides)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected FALSE and returned TRUE)\n");
	}

	printf("\nTest 1.5: Check ride: presence of persons in row queues");
	(*totalTest)++;
    m1.fairgroundId= 10;
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[0],vg1);
	if (checkRide(m1,fairgroundRides)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected FALSE and returned TRUE)\n");
	}

	printf("\nTest 1.6: Check ride: presence of persons in wagons");
	(*totalTest)++;
    m1.fairgroundId= 10;
    visitorQueueDequeue(&m1.rowQueues.rowQueue[0]);
    visitorStackPush(&m1.wagons.wagonRow[0],vg1.visitor);
	if (checkRide(m1,fairgroundRides)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected FALSE and returned TRUE)\n");
	}

	printf("\nTest 1.7: Check ride: presence of persons in main, single and fast-pass queues");
	(*totalTest)++;
    m1.fairgroundId= 10;
    visitorStackPop(&m1.wagons.wagonRow[0]);
    visitorQueueEnqueue(&m1.mainQueue,vg1);
    visitorQueueEnqueue(&m1.singleQueue,vg2);
    visitorQueueEnqueue(&m1.fastPassQueue,vg3);
	if (checkRide(m1,fairgroundRides)) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected checking result. Expected TRUE and returned FALSE)\n");
	}
    visitorQueueDequeue(&m1.mainQueue);
    visitorQueueDequeue(&m1.singleQueue);
    visitorQueueDequeue(&m1.fastPassQueue);
 
	printf("\nTest 1.8: Check group: next group fits");
	(*totalTest)++;    
	if (checkGroup(m1.rowQueues,12)) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected TRUE and returned FALSE)\n");
	}   

	printf("\nTest 1.9: Check group: next group does not fit due to max seats exceeded");
	(*totalTest)++;    
	if (checkGroup(m1.rowQueues,13) == false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}   
    
	printf("\nTest 1.10: Check group: next group does not fit due presence of other visitors");
	(*totalTest)++;    
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[0],vg1);
	if (checkGroup(m1.rowQueues,12) == false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}   
    visitorQueueDequeue(&m1.rowQueues.rowQueue[0]);

    access.lessThan100= FORBIDDEN;
    access.between100_120= FORBIDDEN;
    access.between120_140= ALLOWED_WITH_COMPANION;
    access.greaterThan140= ALLOWED;
    
	printf("\nTest 1.11: Check height: visitor with height under 1m (with companion)");
	(*totalTest)++;   
    if (checkHeight(0.95, access, true)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  

	printf("\nTest 1.12: Check height: visitor with height between 1m and 1,2m (with companion)");
	(*totalTest)++;   
    if (checkHeight(1.1, access, true)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  

	printf("\nTest 1.13: Check height: visitor with height between 1,2m and 1,4m (with companion)");
	(*totalTest)++;   
    if (checkHeight(1.3, access, true)==true) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected TRUE and returned FALSE)\n");
	}  
    
	printf("\nTest 1.14: Check height: visitor with height between 1,2m and 1,4m (no companion)");
	(*totalTest)++;   
    if (checkHeight(1.3, access, false)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  
    
	printf("\nTest 1.15: Check height: visitor with height over 1,4m (no companion)");
	(*totalTest)++;   
    if (checkHeight(1.5, access, false)==true) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected TRUE and returned FALSE)\n");
	}

	printf("\nTest 1.16: Check visitor: unknown visitor");
	(*totalTest)++;   
    vg1.visitor= 1000;
    if (checkVisitor(vg1,f1,visitors,true,TEMP_QUEUE)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  
    
	printf("\nTest 1.17: Check visitor: group in single queue");
	(*totalTest)++;   
    vg1.visitor= v1.id;
    vg1.groupSize= 2;
    if (checkVisitor(vg1,f1,visitors,false,SINGLE_QUEUE)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  
    
	printf("\nTest 1.18: Check visitor: visitor with normal pass in fast-pass queue");
	(*totalTest)++;   
    vg1.groupSize= 1;
    v1.purchasedTicket= GENERAL;
    if (checkVisitor(vg1,f1,visitors,false,FAST_PASS_QUEUE)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  
    
	printf("\nTest 1.19: Check visitor: visitor for a walk intending to access a ride");
	(*totalTest)++;   
    visitors.table[0].purchasedTicket= FOR_A_WALK;
    if (checkVisitor(vg1,f1,visitors,false,MAIN_QUEUE)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  
    
	printf("\nTest 1.20: Check visitor: visitor does not reach minimun height requirements");
	(*totalTest)++;   
    if (checkVisitor(vg6,f1,visitors,false,FAST_PASS_QUEUE)==false) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected FALSE and returned TRUE)\n");
	}  

	printf("\nTest 1.21: Check visitor: visitor accessing with adult");
	(*totalTest)++;   
    if (checkVisitor(vg6,f4,visitors,true,MAIN_QUEUE)==true) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected result. Expected TRUE and returned FALSE)\n");
	}  
}

void testGroupProcessing(int *totalTest, int *passedTest) 
{
    tRideManagement m1;
    tFairgroundRide f1, f2, f3, f4;
    tFairgroundRideTable fairgroundRides;
    tVisitor v1, v2, v3, v4, v5, v6, v8, v10, v11, v12;
    tVisitorGroup vg1, vg2, vg3, vg4, vg5, vg6, vg8, vg10, vg11, vg12;
    tVisitorTable visitors;
    unsigned int freeSeats, prevFreeSeats;
	tError retVal;
	
	getFairgroundRideObject(FAIRGROUNDRIDE1, &f1);
	getFairgroundRideObject(FAIRGROUNDRIDE2, &f2);
	getFairgroundRideObject(FAIRGROUNDRIDE3, &f3);
	getFairgroundRideObject(FAIRGROUNDRIDE4, &f4);
		
	fairgroundRideTableInit(&fairgroundRides);
	fairgroundRideTableAddElement(&fairgroundRides, f1, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f2, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f3, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f4, &retVal);
	
    getVisitorObject(VISITOR1, &v1);
    getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
    getVisitorObject(VISITOR5, &v5);
    getVisitorObject(VISITOR6, &v6);
    getVisitorObject(VISITOR8, &v8);
    getVisitorObject(VISITOR10, &v10);
    getVisitorObject(VISITOR11, &v11);
    getVisitorObject(VISITOR12, &v12);
    
    visitorTableInit(&visitors);
    visitorTableAddElement(&visitors,v1,&retVal);
    visitorTableAddElement(&visitors,v2,&retVal);
    visitorTableAddElement(&visitors,v3,&retVal);
    visitorTableAddElement(&visitors,v4,&retVal);
    visitorTableAddElement(&visitors,v5,&retVal);
    visitorTableAddElement(&visitors,v6,&retVal);
    visitorTableAddElement(&visitors,v8,&retVal);
    visitorTableAddElement(&visitors,v10,&retVal);
    visitorTableAddElement(&visitors,v11,&retVal);
    visitorTableAddElement(&visitors,v12,&retVal);

    getManagementObject(MANAGEMENT1,&m1);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.fastPassQueue);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.singleQueue);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.mainQueue);
    
    m1.rowQueues.nRows= 3;
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[0]);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[1]);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[2]);
    
    m1.wagons.nRows= 3;
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[0]);
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[1]);
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[2]);

	printf("=================================================\n");
	printf(" GROUP PROCESSING (Exercise 2)\n");
	printf("=================================================\n");

	printf("\nTest 2.1: Check group: empty group");
	(*totalTest)++;
    freeSeats= f1.numPersonsTrip;
    processGroup(&m1.fastPassQueue, &m1.rowQueues, 0, f1, visitors, &freeSeats, FAST_PASS_QUEUE);
	if (visitorQueueEmpty(m1.rowQueues.rowQueue[0]) && 
        visitorQueueEmpty(m1.rowQueues.rowQueue[1]) && 
        visitorQueueEmpty(m1.rowQueues.rowQueue[2])) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected processing result. Expected empty row queues as result)\n");
	}
    
	printf("\nTest 2.2: Check group: group of three persons in the fast-pass queue (only one can ride)");
	(*totalTest)++;
    freeSeats= f1.numPersonsTrip;
    vg1.groupSize= 3; vg1.visitor= v1.id;
    vg3.groupSize= 3; vg3.visitor= v3.id;
    vg6.groupSize= 3; vg6.visitor= v6.id;
    visitorQueueEnqueue(&m1.fastPassQueue,vg1);
    visitorQueueEnqueue(&m1.fastPassQueue,vg3);
    visitorQueueEnqueue(&m1.fastPassQueue,vg6);
    processGroup(&m1.fastPassQueue, &m1.rowQueues, 3, f1, visitors, &freeSeats, FAST_PASS_QUEUE);
	if (visitorQueueEmpty(m1.fastPassQueue) && 
        visitorQueueLength(m1.rowQueues.rowQueue[0])==1 && 
        visitorQueueHead(m1.rowQueues.rowQueue[0]).visitor==30 &&
        freeSeats == f1.numPersonsTrip-1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected processing result. Expected only visitor 30 allowed to ride)\n");
	}
    
	printf("\nTest 2.3: Check group: group of five persons in the main queue (four of them can ride)");
	(*totalTest)++;
    prevFreeSeats= freeSeats;
    vg2.groupSize= 5; vg2.visitor= v2.id;
    vg4.groupSize= 5; vg4.visitor= v4.id;
    vg5.groupSize= 5; vg5.visitor= v5.id;
    vg10.groupSize= 5; vg10.visitor= v10.id;
    vg11.groupSize= 5; vg11.visitor= v11.id;
    visitorQueueEnqueue(&m1.mainQueue,vg2);
    visitorQueueEnqueue(&m1.mainQueue,vg4);
    visitorQueueEnqueue(&m1.mainQueue,vg5);
    visitorQueueEnqueue(&m1.mainQueue,vg10);
    visitorQueueEnqueue(&m1.mainQueue,vg11);
    processGroup(&m1.mainQueue, &m1.rowQueues, 5, f1, visitors, &freeSeats, MAIN_QUEUE);
	if (visitorQueueEmpty(m1.mainQueue) && 
        visitorQueueLength(m1.rowQueues.rowQueue[0])==4 && 
        visitorQueueLength(m1.rowQueues.rowQueue[1])==1 && 
        visitorQueueHead(m1.rowQueues.rowQueue[0]).visitor==30 &&
        visitorQueueHead(m1.rowQueues.rowQueue[1]).visitor==110 &&
        freeSeats == prevFreeSeats-4) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected processing result. Expected four visitors allowed to ride)\n");
	}
    
	printf("\nTest 2.4: Check group: kid in the single queue (cannot ride)");
	(*totalTest)++;
    prevFreeSeats= freeSeats;
    vg6.groupSize= 1; vg6.visitor= v6.id;
    visitorQueueEnqueue(&m1.singleQueue,vg6);
    processGroup(&m1.singleQueue, &m1.rowQueues, 1, f1, visitors, &freeSeats, SINGLE_QUEUE);
	if (visitorQueueEmpty(m1.singleQueue) && 
        visitorQueueLength(m1.rowQueues.rowQueue[0])==4 && 
        visitorQueueLength(m1.rowQueues.rowQueue[1])==1 && 
        visitorQueueHead(m1.rowQueues.rowQueue[0]).visitor==30 &&
        visitorQueueHead(m1.rowQueues.rowQueue[1]).visitor==110 &&
        freeSeats == prevFreeSeats) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected processing result. Expected kid not allowed to ride)\n");
	}
    
	printf("\nTest 2.5: Check group: visitor for a walk in the single queue (cannot ride)");
	(*totalTest)++;
    prevFreeSeats= freeSeats;
    vg8.groupSize= 1; vg8.visitor= v8.id;
    visitorQueueEnqueue(&m1.singleQueue,vg8);
    processGroup(&m1.singleQueue, &m1.rowQueues, 1, f1, visitors, &freeSeats, SINGLE_QUEUE);
	if (visitorQueueEmpty(m1.singleQueue) && 
        visitorQueueLength(m1.rowQueues.rowQueue[0])==4 && 
        visitorQueueLength(m1.rowQueues.rowQueue[1])==1 && 
        visitorQueueHead(m1.rowQueues.rowQueue[0]).visitor==30 &&
        visitorQueueHead(m1.rowQueues.rowQueue[1]).visitor==110 &&
        freeSeats == prevFreeSeats) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected processing result. Visitors for a walk are not allowed to ride)\n");
	}
    
	printf("\nTest 2.6: Check group: visitor in the single queue (allowed to ride)");
	(*totalTest)++;
    prevFreeSeats= freeSeats;
    vg12.groupSize= 1; vg12.visitor= v12.id;
    visitorQueueEnqueue(&m1.singleQueue,vg12);
    processGroup(&m1.singleQueue, &m1.rowQueues, 1, f1, visitors, &freeSeats, SINGLE_QUEUE);
	if (visitorQueueEmpty(m1.singleQueue) && 
        visitorQueueLength(m1.rowQueues.rowQueue[0])==4 && 
        visitorQueueLength(m1.rowQueues.rowQueue[1])==2 && 
        visitorQueueHead(m1.rowQueues.rowQueue[0]).visitor==30 &&
        visitorQueueHead(m1.rowQueues.rowQueue[1]).visitor==110 &&
        freeSeats == prevFreeSeats-1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected processing result. Visitors for a walk are not allowed to ride)\n");
	}
}

void testRideProcessing(int *totalTest, int *passedTest) 
{
    tRideManagement m1;
    tFairgroundRide f1, f2, f3, f4;
    tFairgroundRideTable fairgroundRides;
    tVisitor v1, v2, v3, v4, v5, v6;
    tVisitorGroup vg1, vg2, vg3, vg4, vg5, vg6;
    tVisitorTable visitors;
	tError retVal;
	
	getFairgroundRideObject(FAIRGROUNDRIDE1, &f1);
	getFairgroundRideObject(FAIRGROUNDRIDE2, &f2);
	getFairgroundRideObject(FAIRGROUNDRIDE3, &f3);
	getFairgroundRideObject(FAIRGROUNDRIDE4, &f4);
		
	fairgroundRideTableInit(&fairgroundRides);
	fairgroundRideTableAddElement(&fairgroundRides, f1, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f2, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f3, &retVal);
	fairgroundRideTableAddElement(&fairgroundRides, f4, &retVal);
	
    getVisitorObject(VISITOR1, &v1);
    getVisitorObject(VISITOR2, &v2);
    getVisitorObject(VISITOR3, &v3);
    getVisitorObject(VISITOR4, &v4);
    getVisitorObject(VISITOR5, &v5);
    getVisitorObject(VISITOR6, &v6);
    
    visitorTableInit(&visitors);
    visitorTableAddElement(&visitors,v1,&retVal);
    visitorTableAddElement(&visitors,v2,&retVal);
    visitorTableAddElement(&visitors,v3,&retVal);
    visitorTableAddElement(&visitors,v4,&retVal);
    visitorTableAddElement(&visitors,v5,&retVal);
    visitorTableAddElement(&visitors,v6,&retVal);
    
    vg1.groupSize= 1;
    vg1.visitor= v1.id;
    vg2.groupSize= 1;
    vg2.visitor= v2.id;
    vg3.groupSize= 1;
    vg3.visitor= v3.id;
    vg4.groupSize= 1;
    vg4.visitor= v4.id;
    vg5.groupSize= 1;
    vg5.visitor= v5.id;
    vg6.groupSize= 2;
    vg6.visitor= v6.id;

    getManagementObject(MANAGEMENT1,&m1);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.fastPassQueue);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.singleQueue);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.mainQueue);
    
    m1.rowQueues.nRows= 3;
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[0]);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[1]);
    getVisitorQueueObject(EMPTY_QUEUE,&m1.rowQueues.rowQueue[2]);
    
    m1.wagons.nRows= 3;
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[0]);
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[1]);
    getVisitorStackObject(EMPTY_STACK,&m1.wagons.wagonRow[2]);

	printf("=================================================\n");
	printf(" RIDE PROCESSING (Exercise 3)\n");
	printf("=================================================\n");

	printf("\nTest 3.1: Fill wagons: empty row queues");
	(*totalTest)++;
    fillWagons(&m1);
	if (visitorStackEmpty(m1.wagons.wagonRow[0]) && 
        visitorStackEmpty(m1.wagons.wagonRow[1]) &&
        visitorStackEmpty(m1.wagons.wagonRow[2])) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected wagons filling result. Expected empty stacks and some are not empty)\n");
	}
    
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[0],vg1);
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[0],vg2);
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[0],vg3);
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[0],vg4);
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[1],vg5);
    visitorQueueEnqueue(&m1.rowQueues.rowQueue[1],vg6);
    
	printf("\nTest 3.2: Fill wagons: row queues with six visitors");
	(*totalTest)++;
    fillWagons(&m1);
	if (visitorStackSize(m1.wagons.wagonRow[0])==4 && 
        visitorStackSize(m1.wagons.wagonRow[1])==2 &&
        visitorStackSize(m1.wagons.wagonRow[2])==0 && 
        visitorQueueEmpty(m1.rowQueues.rowQueue[0]) &&
        visitorQueueEmpty(m1.rowQueues.rowQueue[1]) &&
        visitorQueueEmpty(m1.rowQueues.rowQueue[2])) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected wagons filling result. Expected all six visitors moved from queues to wagons)\n");
	}    
    
	printf("\nTest 3.3: Clear wagons: clear wagons with visitors");
	(*totalTest)++;
    clearWagons(&m1);
	if (visitorStackEmpty(m1.wagons.wagonRow[0]) && 
        visitorStackEmpty(m1.wagons.wagonRow[1]) &&
        visitorStackEmpty(m1.wagons.wagonRow[2]) && 
        visitorQueueEmpty(m1.rowQueues.rowQueue[0]) &&
        visitorQueueEmpty(m1.rowQueues.rowQueue[1]) &&
        visitorQueueEmpty(m1.rowQueues.rowQueue[2])) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected cleaning result. Expected all six visitors moved out from wagons)\n");
	}  
    
	printf("\nTest 3.4: Clear wagons: clear empty wagons");
	(*totalTest)++;
    clearWagons(&m1);
	if (visitorStackEmpty(m1.wagons.wagonRow[0]) && 
        visitorStackEmpty(m1.wagons.wagonRow[1]) &&
        visitorStackEmpty(m1.wagons.wagonRow[2]) && 
        visitorQueueEmpty(m1.rowQueues.rowQueue[0]) &&
        visitorQueueEmpty(m1.rowQueues.rowQueue[1]) &&
        visitorQueueEmpty(m1.rowQueues.rowQueue[2])) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected cleaning result. Expected no effect after cleaning empty wagons)\n");
	}  
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/********************************************** 
 *        METHODS string
 *********************************************/
void convertStringToUpper(char *string)
{
    int i, len;
    char originalChar;
    
    len= strlen(string);
    for (i= 0; i < len; i++) {
        originalChar= string[i];
        if (originalChar >= 'a' && originalChar <= 'z') 
            string[i]= originalChar + 'A' - 'a';
    }
}


int stringCompareUpper( char *s1, char *s2 )
{
    int result= 0;

    char string1[MAX_LINE];
    char string2[MAX_LINE];
    
    strcpy( string1, s1 );
    strcpy( string2, s2 );
    convertStringToUpper( string1 );
    convertStringToUpper( string2 );
   
    result= strcmp(string1,string2);
    return result;
}

bool isStringYes( char *input )
{
	return (stringCompareUpper(input, "YES") == 0);
}


bool isStringNo( char *input )
{	
	return (stringCompareUpper(input, "NO") == 0);
}

/********************************************** 
 *        METHODS bool
 *********************************************/
 
int booleanCompare(bool b1, bool b2) {
    
    int result;
    
	if (b1 > b2)		result = 1;
	else if (b1 < b2)	result = -1;
	else 				result = 0;
	return result;
}


/********************************************** 
 *        METHODS date
 *********************************************/
void dateInit(tDate *date, int day, int month, int year)
{
	date->day = day;
	date->month = month;
	date->year = year;
}

void dateCopy(tDate *dst, tDate src)
{
/*************** PR1 EX3A *****************/		
	dst->day = src.day;
	dst->month = src.month;
	dst->year = src.year;
/******************************************/	
}

int dateCompare(tDate d1, tDate d2) {
    
    int result = 0;
    
    if (d1.year > d2.year)        result= 1;
    else if (d1.year < d2.year)   result= -1;
    else {
        if (d1.month > d2.month)            result= 1;
        else if (d1.month < d2.month)       result= -1;
        else {
            if (d1.day > d2.day)                result= 1;
            else if (d1.day < d2.day)           result= -1;
        }
    }
    
    return result;
}

bool validateDate(tDate d)
{
	bool result = true;
	if (d.year <= 1900 || d.year >= YEAR_ACTUAL){
		result = false;
	}
	else {
		if (d.month < 1 || d.month > 12) {
			result = false;
		} else {
			if (d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 || d.month == 8 || d.month == 10 || d.month == 12) {
				result = (d.day >= 1 && d.day <= 31);
			}
			else if (d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) {
				result = (d.day >= 1 && d.day <= 30);
			} else { 	/* d.month = 2 */
				if( (d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0 ) {
					result = (d.day >= 1 && d.day <= 29);
				}
				else {
					result = (d.day >= 1 && d.day <= 28);
				}
			}
		}
	}
	return result;
}

int calculateAge(tDate birthDate)
{
   return YEAR_ACTUAL - birthDate.year;
}


/********************************************** 
 *        METHODS time
 *********************************************/

void timeInit(tTime *time, int hour, int minutes)
{
	time->hour = hour;
	time->minutes = minutes;
}

void timeCopy(tTime *dst, tTime src) 
{
/*************** PR1 EX3A *****************/		
	dst->hour = src.hour;
	dst->minutes = src.minutes;
/******************************************/		
}

int timeCompare(tTime t1, tTime t2) {
    
	int result = 0;
    
	if (t1.hour > t2.hour)			result = 1;
	else if (t1.hour < t2.hour)		result = -1;
	else {
		if (t1.minutes > t2.minutes)		result = 1;
		else if (t1.minutes < t2.minutes)	result = -1;
	}
	return result;
}

bool validateTime(tTime t)
{
	bool result;
	if (( t.hour < 0 || t.hour > 23) || (t.minutes < 0 || t.minutes > 59) ) {
		result = false;
	}
	else {
		result = true;
	}
	return result;
}

int diffTime(tTime t1, tTime t2)
{
	int minutes = t1.minutes - t2.minutes;
	int hours = t1.hour - t2.hour;
	
	if (minutes < 0) 
	{
		hours = hours - 1;
		minutes = 60 + minutes;
	}
	return hours * 60 + minutes;
}

/********************************************** 
 *        METHODS time in park
 *********************************************/

void timeInParkCopy(tTimeInPark *dst, tTimeInPark src)
{
	timeCopy(&(dst->timeEnter), src.timeEnter);
	timeCopy(&(dst->timeExit), src.timeExit);
}

int timeInParkCompare(tTimeInPark t1, tTimeInPark t2)
{
	int result = 0;
	result = timeCompare(t1.timeEnter, t2.timeEnter);	
	if (result == 0) {
		result = timeCompare(t1.timeExit, t2.timeExit);
	}
	
	return result;
}

/********************************************** 
 *        METHODS height
 *********************************************/

int heightCompare(float h1, float h2)
{
	int result;
	
	if (h1 > h2) 
	{
		if ( (h1 - h2) < 5.0)
			result = 0;
		else
			result = 1;
	}
	else	
	{
		if ( (h2 - h1) < 5.0)
			result = 0;
		else
			result = -1;
	}
	return result;
}

/********************************************** 
 *        METHODS discount
 *********************************************/
int discountCompare(bool hasDiscount1, float discount1, bool hasDiscount2, float discount2)
{
	int result;
	if (!hasDiscount1 || !hasDiscount2)		
	{
		result = booleanCompare(hasDiscount1, hasDiscount2);
	}
	else
	{
		if (discount1 > discount2)
		{
			result = 1;
		}
		else if (discount1 < discount2)
		{
			result = -1;
		}
		else 
		{
			result = 0;
		}
	}
	
	return result;
}

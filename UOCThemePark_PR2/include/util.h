#include "data.h"

/********************************************** 
 *        METHODS string
 *********************************************/
/* Convert a string to uppercase */
void convertStringToUpper( char *string );

/* Compares two strings in uppercase */
int stringCompareUpper( char *s1, char *s2 );

/* Returns TRUE if input string is 'yes' (case insensitive), and FALSE otherwise */
bool isStringYes( char *input );

/* Returns TRUE if input string is 'no' (case insensitive), and FALSE otherwise */
bool isStringNo( char *input );

/********************************************** 
 *        METHODS boolean
 *********************************************/

/* Compare two booleans. Return:
 * 		1 	 	b1 > b2  | 	-1		b1 < b2  |  	0		b1 = b2 
 */
int booleanCompare(bool b1, bool b2);


/********************************************** 
 *        METHODS date
 *********************************************/

/* Initialize the date */
void dateInit(tDate *date, int day, int month, int year);

/* Copy the date src to dst*/
void dateCopy(tDate *dst, tDate src); 

/* Compare two dates. Returns:
 * 		1 	 	d1 > d2  | 	-1		d1 < d2  |  	0		d1 = d2 
 */
int dateCompare(tDate d1, tDate d2);

/* Validate date (correct day, month and year, and year greater than 1900 and less than actual year) */
bool validateDate(tDate d);

/* Calculate approximate age (difference between actual year and birth year) (being birth year less than actual date) */
int calculateAge(tDate birthDate);

/********************************************** 
 *        METHODS time
 *********************************************/

/* Initialize the object time */
void timeInit(tTime *time, int hour, int minutes);

/* Copy the time data src to dst*/
void timeCopy(tTime *dst, tTime src);

/* Compares times (within the same day). Returns:
 * 		1 	 	h1 > h2  | 	-1		h1 < h2  |  	0		h1 = h2  
 */
int timeCompare(tTime h1, tTime h2);

/* Validate time (24 hours format) */
bool validateTime(tTime t);


/* Calculate difference between two times t1 - t2 (being t1 > t2) and returns minutes difference */
int diffTime(tTime t1, tTime t2);


/********************************************** 
 *        METHODS time in park
 *********************************************/
 
/* Copy the time in park data src to dst*/
void timeInParkCopy(tTimeInPark *dst, tTimeInPark src);

/* Compares times in park (first compares time enter and if necessary time exit). Returns:
 * 		1 	 	t1 > t2  | 	-1		t1 < t2  |  	0		t1 = t2 
 */
int timeInParkCompare(tTimeInPark t1, tTimeInPark t2);


/********************************************** 
 *        METHODS height
 *********************************************/

/* Compares height (equals if difference < 5.0). Returns:
 * 		h1 > h2   	0 if diff < 5 | 1 otherwise
 * 		h1 < h2   	0 if diff < 5 | -1 otherwise
 */
int heightCompare(float h1, float h2);


/********************************************** 
 *        METHODS discount
 *********************************************/
/* Compares discount. Returns:
 * 		v1 hasn't discount and v2 hasn't discount 		returns		0
 * 		v1 has discount and v2 hasn't discount			returns 	1
 * 		v1 hasn't discount and v2 has discount			returns 	-1
 * 		v1 has discount and v2 has discount
 * 				0			v1.discount = v2.discount
 * 				1			v1.discount > v2.discount
 * 				-1			v1.discount < v2.discount
 */
int discountCompare(bool hasDiscount1, float discount1, bool hasDiscount2, float discount2);
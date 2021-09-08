#include "data.h"

/* Get a textual representation of a visitor */
void getVisitorStr(tVisitor visitor, int maxSize, char *str);
	
/* Get a visitor object from its textual representation */
void getVisitorObject(const char *str, tVisitor *visitor);

/* Copy the visitor data in src to dst */
void visitorCopy(tVisitor *dst, tVisitor src);

/* Compare two visitors. Returns:
 * 		1 	 	obj1 > obj2  | 	-1		obj1 < obj2  |  	0		obj1 = obj2 
 */
int visitorCompare(tVisitor obj1, tVisitor obj2);

/* Says if a visitor is an adult one, given its id and a table of visitors */
bool isAdultVisitor( tVisitorId id, tVisitorTable visitors );

/* Initialize the table of visitors */
void visitorTableInit(tVisitorTable *visitorTable);

/* Add a new visitor to the table of visitors */
void visitorTableAddElement(tVisitorTable *visitorTable, tVisitor visitor, tError *retVal);

/* Find a visitor in the table and returns its position */
int visitorTableFindById(tVisitorTable visitorTable, tVisitorId id);

/* Remove the first occurence of a visitor in the table */
void visitorTableRemoveElement(tVisitorTable *visitorTable, tVisitor visitor);

/* Load the table of visitors from a file */
void visitorTableLoadFromFile(tVisitorTable *visitorTable, const char* filename, tError *retVal);

/* Save a table of visitors to a file */
void visitorTableSaveToFile(tVisitorTable visitorTable, const char* filename, tError *retVal);
 
/* Selects visitors who:
 * 		are older than 'age' years and
 * 		are large family and
 * 		are park members (premium) and
 * 		bought the ticket GENERAL or GENERAL_FAST_PASS
*/
void visitorTableSelect(tVisitorTable visitorTable, int age, tVisitorTable *result);

/* Apply an 15% discount to all visitors who
 * 		are older than 35 years and
 * 		are large family and
 * 		are park members (premium) and
 * 		bought the ticket GENERAL or GENERAL_FAST_PASS
*/
void visitorTableApplyDiscounts(tVisitorTable visitorTable, tVisitorTable *result);

/* Return the average time in park */
float visitorTableGetAverageTimeInPark(tVisitorTable visitorsTable);

/* Get the minimum age and the maximum age of visitors in park */
void visitorTableGetMinMaxAgeVisitor(tVisitorTable visitorTable, int *minAge, int *maxAge);

/* Sort a visitor table */
void visitorTableSort(tVisitorTable *visitorTable);

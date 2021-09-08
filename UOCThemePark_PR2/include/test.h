/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR1 */
void runTestsPR1(int* totalTest, int* passedTest);

/* Test the copy and comparison of visitors */
void testCopyCompare(int* totalTest, int* passedTest);

/* Test the selection calls */
void testSelection(int* totalTest, int* passedTest);

/* Test the filter combination calls */
void testFilterCombination(int* totalTest, int* passedTest);

/* Test the statistics calls */
void testStatistics(int* totalTest, int* passedTest);

/* Test the table operations calls */
void testTableOperation(int* totalTest, int* passedTest);

/* Runs the applications tests corresponding to PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Test the general checkings */
void testCheckings(int* totalTest, int* passedTest);

/* Test the group processing */
void testGroupProcessing(int *totalTest, int *passedTest);

/* Test the ride processing */
void testRideProcessing(int *totalTest, int *passedTest);

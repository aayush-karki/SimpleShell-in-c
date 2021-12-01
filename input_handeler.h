#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief ValidInput tests if the input is valid or not
 * 
 * A input is consider valid if it has exactly one '(', ')', and ','
 * char in it. 
 * It also has a max length of 30.
 * Inbetween '('and ')' char a valid input should have
 *  only digits char except for exactly one ','
 * 
 * A example of valid input look processName5(25,10000)
 * @param inputPtr: pointer to the input
 * @retuns 1 for valid input, -1 for invalid input
*/
int ValidInput(char* inputPtr);

/**
 * @brief GetInputProcessName extracts the process name from the input
 * 
 * @note returns a dyanamically allocated arrar of char which should be freed up manually
 * 
 * @param inputPtr: pointer to the input
 * @return a char ptr that points to dynamically allocated array 
 * 		containg the process name
 */
char* GetInputProcessName(char* inputPtr);

/**
 * 
 * @brief GetInputNumArg extracts the number argument from the input corresponding to n
 * 
 * @note returns a dyanamically allocated arrar of char which should be freed up manually
 * 
 * @param inputPtr: pointer to the input
 * @return a char ptr that points to dynamically allocated array 
 * 		containg the number argument
 * @return NULL if number argument passed is not a digit
 * 
 */
char* GetInputNumArg(char* inputPtr);

/**
 * 
 * @brief GetInputQtArg extracts the qt argument from the input corresponding to n
 * 
 * @note returns a dyanamically allocated arrar of char which should be freed up manually
 * 
 * @param inputPtr: pointer to the input
 * @return a char ptr that points to dynamically allocated array 
 * 		containg the qt argument
 * @return NULL if qt argument passed is not a digit
 * 
 */
char* GetInputQtArg(char* inputPtr);

/**
 * 
 * @brief IsInputBg checkes if the process is background process or not
 * 
 * @param inputPtr: pointer to the input
 * @return 0 if it is not a background process
 * 	    1 if it is a background process
 * 
 */
char IsInputBg(char* inputPtr);

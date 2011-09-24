/******************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2011 Assignment #2 - Vending Machine
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Yallara Username : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by Christopher Hoobin and Xiaodong Li
******************************************************************************/

#include "vm.h"
#include "vm_options.h"
#include "vm_utility.h"

int main(int argc, char *argv[])
{
   VendingMachineType vm;

   int initFlag, dataFlag;

   /* Initialise the vending machine to a safe empty state. */
   initFlag = systemInit(&vm);

   /* Populate the vending machine with data from the csv files. */
   if(argc == 3){
      dataFlag = loadData(&vm, argv[1], argv[2]);
   } else {
      printf("Invalid number of command line arguments");
      exit(EXIT_FAILURE);
   }

   /* Testing to see if both systemInit(.) and loadData(.) are ok */
   if (initFlag == FAILURE || dataFlag == FAILURE)
     exit(EXIT_FAILURE);

   /* Interactive menu providing user with access to the 9 menu options */

   /* Deallocate all dynamically allocated memory. */
   systemFree(&vm);

   exit(EXIT_SUCCESS);
}

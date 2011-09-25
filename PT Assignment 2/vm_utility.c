/*****************************************************************************
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
#include "vm_utility.h"
#include "vm_options.h"
#include <string.h>

/****************************************************************************
* Function readRestOfLine() is used for buffer clearing.
* Please refer to "test_fgets.c" on Blackboard:
* "Course Documents"->"Function Examples"->"Input Validation Examples"
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}


/****************************************************************************
* Initialises the system to a safe empty state.
****************************************************************************/
int systemInit(VendingMachineType *vm)
{
}

/*================= insertNode ================== 
 This function inserts a single node into a linked list.
 head is pointer to the list; may be null.
 prev points to new node's logical predecessor.
 name contains person's name to be inserted.
 The function returns the head pointer.
 */
ProductNodeType *insertNode(ProductNodeType *head, ProductNodeType *previous, char* string)
{   
   ProductNodeType *node;
   
   /* allocate storage */
   if ((node = (ProductNodeType *)malloc(sizeof(ProductNodeType))) == NULL)
   {
      printf("Memory overflow in insertNode\n");
      exit(1);
   }
   
   strcpy(node->name, string);
   
   if (previous == NULL)
   {
      /* inserting before first node or to empty list */
      node->nextProduct = head;
      head = node;
   }/* if prev */
   else
   {
      /* inserting in middle or at end */
      node->nextProduct = previous->nextProduct;
      previous->nextProduct = node;
   }
   return head;
} /* insertNode */

void printList(ProductNodeType *p)
{   
   printf("\nList contains:\n");
   while (p != NULL)
   {
      printf("%s -> ", p->name);
      p = p->nextProduct;
   } /* while */
   printf("\n");
   return;
} /* printList */

/****************************************************************************
* Loads all data into the system.
****************************************************************************/
int loadData(VendingMachineType *vm, char *stockfile, char *coinsFile)
{
   FILE *stock;
   FILE *coins;
   unsigned long stockSize, coinsSize;
   char *stockData, *coinsData;
   char tempString[] = " ";
   
   ProductNodeType *head = NULL;
   ProductNodeType *previous = NULL;
   ProductNodeType *current;
      
   if((stock=fopen(stockfile, "r")) == NULL) {
      printf("Cannot open stock file.\n");
      return FAILURE;
   } else if((coins=fopen(coinsFile, "r")) == NULL) {
      printf("Cannot open coins file.\n");
      return FAILURE;
   } else {
      printf("Files loaded successfully.\n\n");
      
      /*getting the sizes of the files*/
      fseek(stock, 0L, SEEK_END);
      stockSize = ftell(stock);
      fseek(stock, 0L, SEEK_SET);
      stockData = malloc(stockSize);
      
      fseek(coins, 0L, SEEK_END);
      coinsSize = ftell(coins);
      fseek(coins, 0L, SEEK_SET);
      coinsData = malloc(coinsSize);
      current = malloc(4099);
      
      /*copying data from files to strings*/
      while(fread(tempString, sizeof(char), 1, stock) > 0){
         if(strcmp(tempString, "\n") != 0){
            strcat(stockData, tempString);
         } else {
            /*strcpy(current->name, stockData);*/
            head = insertNode(head, previous, stockData);
            strcpy(stockData, "");
         }
      }
      
      printList(head);
      
      fclose(stock);
      free(current);
      free(stockData);
      free(coinsData);
      return SUCCESS;
   }
}

/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(VendingMachineType *vm)
{
}

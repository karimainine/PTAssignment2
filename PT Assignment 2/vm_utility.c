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
ProductNodeType *insertNode(ProductNodeType * head, ProductNodeType * node)
{  
   ProductNodeType *current, *previous;
   
   if(head == NULL){
      head = node;
      head->nextProduct = NULL;
   } else {
      node->nextProduct = head;
      head = node;
      
   }
   return head;
} /* insertNode */

void printList(ProductNodeType *p)
{   
   printf("\nProduct                                  Brand                Price Qty");
   printf("\n---------------------------------------- -------------------- ----- ---\n");
   
   while (p != NULL)
   {
      printf("\n%-40.40s %-20.20s %5d %3d\n ", p->name, p->brand, p->price, p->qty);
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
   char tempString[PRODUCT_NAME_MAX + PRODUCT_BRAND_MAX + PRODUCT_PRICE_MAX + PRODUCT_QTY_MAX + 2] = "";
   
   char *name;
   char *brand;
   unsigned quantity;
   unsigned price;
   
   ProductNodeType *node = NULL;
   
   if((stock=fopen(stockfile, "r")) == NULL) {
      printf("Cannot open stock file.\n");
      return FAILURE;
   } else if((coins=fopen(coinsFile, "r")) == NULL) {
      printf("Cannot open coins file.\n");
      return FAILURE;
   } else {      
      /*copying data from files to lists*/
      while(fgets(tempString, sizeof(tempString), stock) != NULL){
         /*strcpy(current->name, stockData);*/
         name = strtok(tempString,",");
         brand = strtok('\0',",");
         price = (unsigned) atof(strtok('\0',","));
         /*ptr = strtok('\0',"\0");*/
         quantity = (unsigned) atof(strtok('\0',"\0"));
         
         node = malloc(sizeof(ProductNodeType));
         strcpy(node->name, name);
         strcpy(node->brand, brand);
         node->price = price;
         node->qty = quantity;
         
         vm->headProduct = insertNode(vm->headProduct, node);
      }
      
      fclose(stock);
      return SUCCESS;
   }
}

/****************************************************************************
 * This function has an array of Strings containing the menu options. It 
 * loops through the array and prints the options to the user. 
 ****************************************************************************/

void displayMainMenu()
{
   char * userMenu [USER_OPTIONS_NUM] = {"1) Purchase Product",
      "2) Display Products", 
      "3) Save and Exit"};
   
   char * adminMenu [ADMIN_OPTIONS_NUM] = {"4) Add Product",
      "5) Remove Products", 
      "6) Display Coins",
      "7) Restock Products",
      "8) Restock Coins",
      "9) Abort"};
   
   int i;
   char * str;
   
   printf("\n%s\n","Main Menu:");
   
   for(i=0; i<USER_OPTIONS_NUM; i++)
   {
      str = userMenu[i];
      printf("%s\n",str);
   }
   
   printf("\n%s\n","Supplier-Only Menu:");
   
   for(i=0; i<ADMIN_OPTIONS_NUM; i++)
   {
      str = adminMenu[i];
      printf("%s\n",str);
   }
   
   printf("\nSelect your option (1-9):");
}


/****************************************************************************
 * Deallocates memory used in the program.
 ****************************************************************************/
void systemFree(VendingMachineType *vm)
{
}

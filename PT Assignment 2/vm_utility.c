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
 * This function is used in a general function that takes the string entered 
 * by the user and returns the int value of it. The function is given a max
 * size to check for the number of characters entered. Any extra characters
 * will indicate an invalid Input and will be handled using the 
 * readRestOfLine() function. It is also given a max and a min range for 
 * the int values to check on. If the input is not within the range, the user
 * is informed that is an Invalid Input and allowed to try again.
 
 * This function is based on the a function in the Blackboard that handles
 * the users input, buffer, etc. but changed to fit the application.
 ****************************************************************************/

int getUserInt(char * message, int maxSize, int minRange, int maxRange)
{
   char *myString = malloc(sizeof(maxSize)); 
   int value;
   int finished = FALSE;
   char *ptr;
   do 
   {
      printf("\n%s\n", message);
      value = -1;
      
      fgets(myString, (maxSize + EXTRA_SPACES), stdin);
      
      if(myString[0] == '\n')
      {
         finished = TRUE;
      }
      else if (myString[strlen(myString) - 1] != '\n')
      {
         printf("Invalid Input.\n");
         readRestOfLine();
      }
      else
      {
         myString[strlen(myString) - 1] = '\0';
         value = (int) strtol(myString, &ptr, 10);
         
         if (value < minRange || value > maxRange || (int)*ptr != 0)
         {	
            printf("Invalid Input.\n");
         }
         else
         {
            finished = TRUE;
         }
      }
   } while (!finished); 
   free(myString);
   return value;
}



/****************************************************************************
 * Initialises the system to a safe empty state.
 ****************************************************************************/
int systemInit(VendingMachineType *vm)
{
   vm->headProduct = NULL;
   vm->totalCoins = 0;
   vm->totalProducts = 0;
   
   return SUCCESS;
}

/*================= insertNode ================== 
 This function inserts a single node into a linked list.
 head is pointer to the list; may be null.
 prev points to new node's logical predecessor.
 name contains person's name to be inserted.
 The function returns the head pointer.
 */
void insertNode(VendingMachineType * vm, ProductNodeType * node)
{  
   ProductNodeType *current, *previous;
   
   current = vm->headProduct;
   previous = NULL;
   
   while (current != NULL && strcmp(current->name, node->name) < 0){
      previous = current;
      current = current->nextProduct;
   }
   
   node->nextProduct = current;
   
   if(previous == NULL){
      vm->headProduct = node;
   } else {
      previous->nextProduct = node;
   }
} /* insertNode */

/****************************************************************************
 * Loads all data into the system.
 ****************************************************************************/
int loadData(VendingMachineType *vm, char *stockfile, char *coinsFile)
{
   FILE *stock;
   FILE *coins;
   char tempString[PRODUCT_NAME_MAX + PRODUCT_BRAND_MAX + PRODUCT_PRICE_MAX + PRODUCT_QTY_MAX + EXTRA_SPACES] = "";
   char *tokenString = NULL;
   char name[PRODUCT_NAME_MAX + EXTRA_SPACES] = {'\0'};
   char brand[PRODUCT_BRAND_MAX + EXTRA_SPACES] = {'\0'};
   unsigned quantity = 0;
   unsigned price = 0;
   char *ptr;
   unsigned coinValue, coinQuantity;
   
   ProductNodeType *node = NULL;
   CoinType coin;
   int i=0;
   int j=0;
   
   if((stock=fopen(stockfile, "r")) == NULL) {
      printf("Cannot open stock file.\n");
      return FAILURE;
   } else if((coins=fopen(coinsFile, "r")) == NULL) {
      printf("Cannot open coins file.\n");
      return FAILURE;
   } else {      
      /*copying data from files to lists*/
      while(fgets(tempString, sizeof(tempString), stock) != NULL){
         i=0;
         tokenString = strtok(tempString,",");
         while(tokenString != NULL){
            switch(i){
               case 0:
               {
                  if(strlen(tokenString) > PRODUCT_NAME_MAX){
                     printf("\nInvalid file format.\n");
                     return FAILURE;
                  }else{
                     strcpy(name, tokenString);
                  }
                  break;
               }
               case 1:
               {
                  if(strlen(tokenString) > PRODUCT_BRAND_MAX){
                     printf("\nInvalid file format.\n");
                     return FAILURE;
                  }else{
                     strcpy(brand, tokenString);
                  }
                  break;
               }
               case 2:
               {
                  price = (unsigned) strtol(tokenString, &ptr, 10);
                  if ((strlen(tokenString) > PRODUCT_PRICE_MAX) || strcmp(ptr,"")!=0){
                     printf("\nInvalid file format.\n");
                     return FAILURE;
                  }
                  break;
               }
               case 3:
               {
                  if( (ptr = strchr(tokenString, '\n')) != NULL){
                     *ptr = '\0';
                  }
                  quantity = (unsigned) strtol(tokenString, &ptr, 10);
                  if ((strlen(tokenString) > PRODUCT_QTY_MAX) || strcmp(ptr,"")!=0){
                     printf("\nInvalid file format.\n");
                     return FAILURE;
                  }
                  break;
               }
               default:
               {
                  printf("\nInvalid file format.\n");
                  return FAILURE;
               }
            }
            
            tokenString = strtok('\0',",");
            i++;
         }
         
         node = getProduct(name, vm);
         
         if(node != NULL){
            node->qty += quantity;
         } else {
            node = malloc(sizeof(ProductNodeType));
            strcpy(node->name, name);
            strcpy(node->brand, brand);
            node->price = price;
            node->qty = quantity;
            
            insertNode(vm, node);
            vm->totalProducts++;
         }
      }      
      fclose(stock);
         
      i=0;
      vm->totalCoins = 0;
      while(fgets(tempString, sizeof(tempString), coins) != NULL){
         j=0;
         tokenString = strtok(tempString,",");
         while(tokenString != NULL){
            switch(j){
               case 0:
               {
                  coinValue = (unsigned) strtol(tokenString, &ptr, 10);
                  if ((coinValue != 200 && coinValue != 100 && coinValue != 50 && coinValue != 20 && coinValue != 10 && coinValue != 5) || strcmp(ptr,"")!=0){
                     printf("\nInvalid file format.\n");
                     return FAILURE;
                  }
                  break;
               }
               case 1:
               {
                  if( (ptr = strchr(tokenString, '\n')) != NULL){
                     *ptr = '\0';
                  }
                  coinQuantity = (unsigned) strtol(tokenString, &ptr, 10);
                  if (strcmp(ptr,"")!=0 || coinQuantity > MAX_COIN_VALUE){
                     printf("\nInvalid file format.\n");
                     return FAILURE;
                  }
                  break;
               }
               default:
               {
                  printf("\nInvalid file format.\n");
                  return FAILURE;
               }
            }
            tokenString = strtok('\0',",");
            j++;
         }
         
         coin.value = coinValue;
         coin.qty = coinQuantity;
         vm->coins[i] = coin;
         i++;
         vm->totalCoins++;
      }
      
      if(vm->totalCoins != DISTINCT_COINS){
         printf("\nInvalid file format.\n");
         return FAILURE;
      }      
      fclose(coins);
      
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
}

void getProductName(char *input)
{
   char myString[PRODUCT_NAME_MAX + EXTRA_SPACES];
   int finished = FALSE;
   int length;
   
   do 
   {
      printf("\nEnter a product name (1­-40 characters):\n");
      myString[0] = '\0';
      fgets(myString, PRODUCT_NAME_MAX + EXTRA_SPACES, stdin);
      length = (int)strlen(myString) - 1;
      
      if(myString[0] == '\n')
      {
         /*input = myString;*/
         strcpy(input, myString);
         finished = TRUE;
      }
      else if (length < STRING_MIN_CHARS || length > PRODUCT_NAME_MAX)
      {
         printf("Invalid Input.\n");
         if (myString[length] != '\n')
         {
            readRestOfLine();
         }
      }
      else
      {
         myString[length] = '\0';
         strcpy(input, myString);
         finished = TRUE;
      }
   } while (!finished);
}

void getBrandName(char *input)
{
   char myString[PRODUCT_BRAND_MAX + EXTRA_SPACES];
   int finished = FALSE;
   int length;
   
   do 
   {
      printf("\nEnter a brand name (1­-20 characters):\n");
      myString[0] = '\0';
      fgets(myString, PRODUCT_BRAND_MAX + EXTRA_SPACES, stdin);
      length = (int)strlen(myString) - 1;
      
      if(myString[0] == '\n')
      {
         strcpy(input, myString);
         finished = TRUE;
      }
      else if (length < STRING_MIN_CHARS || length > PRODUCT_BRAND_MAX)
      {
         printf("Invalid Input.\n");
         if (myString[length] != '\n')
         {
            readRestOfLine();
         }
      }
      else
      {
         myString[length] = '\0';
         strcpy(input, myString);
         finished = TRUE;
      }
   } while (!finished);
}

ProductNodeType* getProduct(char* productName, VendingMachineType *vm){
   ProductNodeType *current;
   current = vm->headProduct;
   while(current != NULL){
      if(strcmp(current->name, productName) == 0){
         return current;
      }
      current = current->nextProduct;
   }
   return NULL;
}

double makePayment(double price, VendingMachineType *vm, int *paymentComplete){
   double remainingValue;
   double change = 0;
   int coinInserted;
   remainingValue = price;
   do {
      printf("\nEnter a coin ($%.2f remaining): " , remainingValue/100);
      coinInserted = getCoins(vm);
      if(coinInserted != -1){
         if(coinInserted < remainingValue){
            remainingValue = remainingValue - coinInserted;
         } else {
            change = coinInserted - remainingValue;
            remainingValue = 0;
         }
      } else {
         *paymentComplete = FAILURE;
         return (price - remainingValue);
      }
   } while (remainingValue > 0);
   
   *paymentComplete = SUCCESS;
   return change;
}

int getCoins(VendingMachineType *vm){
   char myString[PRODUCT_PRICE_MAX + EXTRA_SPACES]; 
   int value;
   int finished = FALSE;
   char *ptr;
   int i;
   do 
   {
      value = -1;
      fgets(myString, PRODUCT_PRICE_MAX + EXTRA_SPACES, stdin);
      
      if(myString[0] == '\n')
      {
         finished = TRUE;
      }
      else if (myString[strlen(myString) - 1] != '\n')
      {
         printf("Invalid Input.\n");
         readRestOfLine();
      }
      else
      {
         myString[strlen(myString) - 1] = '\0';
         value = (int) strtol(myString, &ptr, 10);
         for(i=0; i<DISTINCT_COINS; i++){
            if(value == vm->coins[i].value){
               vm->coins[i].qty++;
               return value;
            }
         }
         printf("Invalid coin value. Please Enter a valid coin value: ");
      }
   } while (!finished);
   return value;
}

void printChangeCoins(double change, VendingMachineType* vm){
   int i;
   printf("Your change coins are: ");
   for(i=0; (i<DISTINCT_COINS && change > 0); i++){
      while (change >= vm->coins[i].value && vm->coins[i].qty > 0){
         change = change - ((double)(vm->coins[i].value));
         printf("$%.2f ",((double)(vm->coins[i].value))/100);
         vm->coins[i].qty--;
      }
      
   }
   printf("\n");
}

void deleteNode(VendingMachineType* vm, char* productName){
   ProductNodeType *previous = NULL;
   ProductNodeType *current;
   int found = FAILURE;
   for (current = vm->headProduct; current != NULL; current = current->nextProduct){
      if(strcmp(current->name, productName) == 0){
         found = SUCCESS;
         if(previous == NULL){
            vm->headProduct = current->nextProduct;
         } else {
            previous->nextProduct = current->nextProduct;
         }
         free(current);
         vm->totalProducts--;
      } else {
         previous = current; 
      }
   }
   
   if(found == SUCCESS){
      printf("\n%s removed from the vending machine\n", productName);
   } else {
      printf("\n%s not found in the vending machine. Please try again.\n", productName);
   }
}

/****************************************************************************
 * Deallocates memory used in the program.
 ****************************************************************************/
void systemFree(VendingMachineType *vm)
{
}

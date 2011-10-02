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

/****************************************************************************
* Menu option #1: Purchase Product
* Allows the user to purchase a product by specifying the product name and
* insert coins into the system in an interactive fashion. User is given any
* change necessary.
****************************************************************************/
void purchaseProduct(VendingMachineType *vm)
{
   char *productName;
   ProductNodeType *selectedProduct = NULL;
   productName = getProductName(productName);
   if(*productName != '\n'){
      selectedProduct = getProduct(productName, vm);
      if(selectedProduct != NULL){
         printf("\nProduct Price: %d\n", selectedProduct->price);
      }else{
         printf("\nProduct not found. Please try again.\n");
      }
   }
   
}

/****************************************************************************
* Menu option #2: Display Products
* Allows the user to view all products in the vending machine.
****************************************************************************/
void displayProducts(VendingMachineType *vm)
{
   ProductNodeType *current;
   current = vm->headProduct;
   printf("\nProduct                                  Brand                Price Qty");
   printf("\n---------------------------------------- -------------------- ----- ---\n");
   
   while (current != NULL)
   {
      printf("%-40.40s %-20.20s %5d %3d\n", current->name, current->brand, current->price, current->qty);
      current = current->nextProduct;
   }
   printf("\n");
}

/****************************************************************************
* Menu option #3: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(VendingMachineType *vm, char *stockFile, char *coinsFile)
{
}

/****************************************************************************
* Menu option #4: Add Product
* Allows a supplier to add a new product to the vending machine. All
* necessary information is prompted for.
****************************************************************************/
void addProduct(VendingMachineType *vm)
{
}

/****************************************************************************
* Menu option #5: Remove Product
* Allows a supplier to remove a product from the vending machine.
****************************************************************************/
void removeProduct(VendingMachineType *vm)
{
}

/****************************************************************************
* Menu option #6: Display Coins
* Allows a supplier to view a summary of all coins in the vending machine.
****************************************************************************/
void displayCoins(VendingMachineType *vm)
{
   int i;
   printf("\nCoin  Quantity\n");
   printf("----- --------\n");
   for(i=0; i<vm->totalCoins; i++){
      CoinType coin = vm->coins[i];
      
      printf("%4d %5d\n", coin.value, coin.qty);
   }
}

/****************************************************************************
* Menu option #7: Restock Products
* Allows the supplier to restock the vending machine products to the default
* level. The STOCK_DEFAULT constant from vm.h is used here.
****************************************************************************/
void restockProducts(VendingMachineType* vm)
{
}

/****************************************************************************
* Menu option #8: Restock Coins
* Allows the supplier to restock the vending machine coins to the default
* level. The COINS_DEFAULT constant from vm.h is used here.
****************************************************************************/
void restockCoins(VendingMachineType *vm)
{
}

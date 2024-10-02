#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "Catalog.h"        // our menu class, more info in this file

using namespace std;

// PROTOTYPES:

void showMenus();               // all menu options
void chooseMenu();              // main navigation (also to avoid clogging up main)

void openMenu(vector<string>&, vector<double>&, int&, int&, bool&); // opens the menu of the user's choice
void openCart(vector<string>&, vector<double>&, int&);              // opens the user's cart

void userCheckout(vector<string>, vector<double>, int, bool); // checkout, when the user finishes shopping
double calculateTax(double);                                  // tax based on city, for total price

int main() {

  cout << "----------------------------------" << endl;
  cout << "-            7-Eleven            -" << endl; // sick title am i right
  cout << "----------------------------------" << endl;
  cout << endl;

  cout << "Hello, what would you like to purchase in this convenient store?" << endl << endl;
  cout << endl << endl;
  
  cout << "      All Keys:" << endl;
  cout << "----------------------" << endl << endl;

  showMenus();

  cout << "|" << endl;
  cout << "| ~ '0' to view your cart (you can only check if you are in this menu)" << endl;
  cout << "| ~ '-1' to reshow above options (in case you shop for a long while)" << endl;
  cout << "| ~ '-2' to enter checkout" << endl;
  cout << endl;

  cout << "----------------------" << endl << endl;

  chooseMenu();

  return 0;
  
}

void chooseMenu() {

  int userInput;                // used to view different categories, check inventory, continue to checkout

  bool isShopping = true;       // triggers the menus loop
  bool isFirstTime = true;      // just for a measure related to checking the user's cart
  // if false, it means that the user can now check their cart after their first time shopping :)

  vector<string> cartItems;     // the cart of all the items the user wants to purchase!
  vector<double> cartPrices;    // the prices of all the items in the cart
  int totalItems = 0;           // total items in user's cart, default set to 0

  cout << "Enter one of the options listed above: ";
  cin >> userInput;

  cout << endl;

  while(isShopping == true) {

    cout << "=============================================" << endl << endl;

    if (userInput == -2) { // option for checkout
      isShopping = false; // ends the while loop, thus letting user enter checkout
    }

    else if (userInput == -1) { // if the user wants to reshow the menu
      cout << "                    Keys:" << endl << endl;
      showMenus();
      cout << endl << "=============================================" << endl << endl;
      cout << endl << "Choose one of the above options " <<
        "(or 0 to open cart, -1 to reshow options, -2 to enter checkout): ";
      cin >> userInput;
    }

    else if (userInput == 0) { // lets the user check their cart

      // EXPLANATION OF isFirstTime:
      // if the user has not chosen a single item yet, it will stay true, which means
      // that they will be prompted with the sad fact they haven't chosen anything...
      // if false, then they can view their cart.

      if (isFirstTime == true) {
        cout << "You have nothing in your cart! Start shopping now!" << endl << endl;
        cout << "=============================================" << endl << endl;
        cout << endl << "Enter another menu option " <<
          "(0 to open cart, -1 to reshow options, -2 to enter checkout): ";
        cin >> userInput;
      }

      else {
        openCart(cartItems, cartPrices, totalItems);
        cout << endl << "Enter another menu option " <<
          "(0 to open cart, -1 to reshow options, -2 to enter checkout): ";
        cin >> userInput;
      }

    }

    else if (userInput > 0 && userInput < 6) { // if the user chooses a menu (options 1 - 5)
      openMenu(cartItems, cartPrices, userInput, totalItems, isFirstTime);
      cout << endl << "Enter another menu option " <<
        "(0 to open cart, -1 to reshow options, -2 to enter checkout): ";
      cin >> userInput;
    }

    else { // just a measure that continues the while loop if the user inputs something invalid
      cout << "Please enter a valid menu option: ";
      cin >> userInput;
    }

    cout << endl;

  }

  userCheckout(cartItems, cartPrices, totalItems, isFirstTime);
  
}

void openMenu(vector<string>& cartItems, vector<double>& cartPrices, int& userInput, int& totalItems, bool& isFirstTime) {

  int input; // whatever the user chooses to add to their cart

  string itemsArray[5];          // every individual item in each menu
  double pricesArray[5];         // every individual price in each menu
  bool validInput = false;       // further explained below, meant for choosing an item

  ifstream foodItems;

  // these branches are meant to promp a specific menu that the user chooses.
  // comes in handy as we don't want to repeat HUNDREDS of lines of code
  // (this would be our biggest mistake yet)

  if (userInput == 1)
    foodItems.open("food.txt"); // food menu

  if (userInput == 2)
    foodItems.open("beverages.txt"); // beverages menu

  if (userInput == 3)
    foodItems.open("health.txt"); // health/self care menu

  if (userInput == 4)
    foodItems.open("cleaning.txt"); // cleaning supplies menu

  if (userInput == 5)
    foodItems.open("miscellaneous.txt"); // miscellaneous menu

  

  if (!foodItems.is_open()) { // if the external file is missing, then the program is aborted
    cout << "!! ERROR: UNABLE TO OPEN THE REQUESTED MENU !!" << endl << endl;
    cout << "| Reason: the external file associated with this menu cannot be found." << endl;
    cout << "|" << endl;
    cout << "| Please ensure such external file(s) are in their correct place." << endl;
    cout << "| Aborting program..." << endl;
    exit(1);
  }

  

  for (int i = 0; i < 5; i++) { // grabbing all menu data from external file...

    getline(foodItems, itemsArray[i]);
    foodItems >> pricesArray[i];
    foodItems.ignore();

  }

  foodItems.close(); // external file closed

  // now putting the array data into the Catalog class's constructors
  Catalog foodList(itemsArray[0], itemsArray[1], itemsArray[2], itemsArray[3], itemsArray[4]);
  Catalog foodPrices(pricesArray[0], pricesArray[1], pricesArray[2], pricesArray[3], pricesArray[4]);

  // printing the entire menu

  cout << "Menu Items:" << endl;
  cout << "1. " << foodList.getItem1() << ": $" <<
    fixed << setprecision(2) << foodPrices.getPrice1() << endl;
  cout << "2. " << foodList.getItem2() << ": $" <<
    fixed << setprecision(2) << foodPrices.getPrice2() << endl;
  cout << "3. " << foodList.getItem3() << ": $" <<
    fixed << setprecision(2) << foodPrices.getPrice3() << endl;
  cout << "4. " << foodList.getItem4() << ": $" <<
    fixed << setprecision(2) << foodPrices.getPrice4() << endl;
  cout << "5. " << foodList.getItem5() << ": $" <<
    fixed << setprecision(2) << foodPrices.getPrice5() << endl;
  cout << endl;

  cout << "Choose an item to add to your cart (-1 to go back): ";
  cin >> input;

  cout << endl;

  while (validInput == false) {

    // EXPLANATION OF BOOLEAN VALUES IN THIS CASE:

    // isFirstTime - now that the user finally chose an item, they can now check their cart :)
    // validInput  - if false (only if the user enters an invalid option), the while loop continues
    //               until they choose a valid option

    if (input == -1) // go back to the previous menu
      validInput = true;

    else if (input == 1) { // add the first item to the user's cart
      cartItems.push_back(foodList.getItem1());
      cartPrices.push_back(foodPrices.getPrice1());
      totalItems = totalItems + 1;
      
      isFirstTime = false;
      validInput = true;

      cout << "* TADA! Added " << foodList.getItem1() << " to your cart *" << endl << endl;
    }

    else if (input == 2) { // add the second item to the user's cart
      cartItems.push_back(foodList.getItem2());
      cartPrices.push_back(foodPrices.getPrice2());
      totalItems = totalItems + 1;
      
      isFirstTime = false;
      validInput = true;

      cout << "* TADA! Added " << foodList.getItem2() << " to your cart *" << endl << endl;
    }

    else if (input == 3) { // add the third item to the user's cart
      cartItems.push_back(foodList.getItem3());
      cartPrices.push_back(foodPrices.getPrice3());
      totalItems = totalItems + 1;
      
      isFirstTime = false;
      validInput = true;

      cout << "* TADA! Added " << foodList.getItem3() << " to your cart *" << endl << endl;
    }

    else if (input == 4) { // add the fourth item to the user's cart
      cartItems.push_back(foodList.getItem4());
      cartPrices.push_back(foodPrices.getPrice4());
      totalItems = totalItems + 1;
      
      isFirstTime = false;
      validInput = true;

      cout << "* TADA! Added " << foodList.getItem4() << " to your cart *" << endl << endl;
    }

    else if (input == 5) { // add the fifth item to the user's cart
      cartItems.push_back(foodList.getItem5());
      cartPrices.push_back(foodPrices.getPrice5());
      totalItems = totalItems + 1;
      
      isFirstTime = false;
      validInput = true;

      cout << "* TADA! Added " << foodList.getItem5() << " to your cart *" << endl << endl;
    }

    // another measure in case any knuckleheads input anything invalid
    else if (input < 1 || input > 5) {
      cout << "Please enter a valid option: ";
      cin >> input;
      cout << endl;
    }
    
  }

  cout << "=============================================" << endl;
  
}

void openCart(vector<string>& cartItems, vector<double>& cartPrices, int& totalItems) {

  // totalItems comes in handy here as it is the amount of elements in each vector

  // each element is output here...
  for(int i = 0; i < totalItems; i++) {
    cout << (i + 1) << ". " << cartItems.at(i) << " ($" << cartPrices.at(i) << ")" << endl;
  }
  
}

void showMenus() { // did you forget what the options are? If yes, this can help

  cout << "| ~ '1' to open the Food menu" << endl;
  cout << "| ~ '2' to open the beverages menu" << endl;
  cout << "| ~ '3' to open the health/self care menu" << endl;
  cout << "| ~ '4' to open the cleaning supplies menu" << endl;
  cout << "| ~ '5' to open the miscellaneous menu" << endl;

}

void userCheckout(vector<string> cartItems, vector<double> cartPrices, int totalItems, bool firstTime) {

    if (firstTime == true) { // user enters checkout without choosing an item
      cout << "You have added nothing to your cart." << endl;
      cout << "There is no total, subtotal, nor tax." << endl;
      cout << "Thank you for shopping, sorry to see you go so soon." << endl;
      exit(0);
    }
  
    double subtotal = 0.0;

    for(int i = 0; i < totalItems; ++i) {
      subtotal = subtotal + cartPrices.at(i); // for calculateTax function
    }

    ofstream receipt;

    receipt.open("receipt.txt"); // receipt file to be created

    double tax = calculateTax(subtotal); // before getting total
    double total = subtotal + tax;

    receipt << "         RECEIPT\n" << endl; // outputting receipt
    receipt << "7-Eleven\n" << endl;
    receipt << "---------------------------\n" << endl;
    receipt << "Items and prices:" << endl;
    for(int i = 0; i < totalItems; ++i) {
      receipt << (i + 1) << ". " << cartItems.at(i) <<
        " -- $" << fixed << setprecision(2) << cartPrices.at(i) << endl;
    }
    cout << endl;
    receipt << "---------------------------\n" << endl;

    receipt << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    receipt << "Tax: $" << fixed << setprecision(2) << tax << endl;
    receipt << "Total: $" << fixed << setprecision(2) << total << endl;

    receipt.close();

    cout << "Thank you for shopping!" << endl;
    cout << "Your receipt should be in a text file called 'receipt.txt'." << endl; // the end
}

// My teammate's work - he wrote the base code from here, and all I did was
// was make it easier to read.

// Reference for tax rates (Effective October 1st, 2024): https://www.cdtfa.ca.gov/taxes-and-fees/rates.aspx

double calculateTax(double subtotal) {

    bool validCity = false;
    double taxRate = 0.0;

    int city;
    cout << "Cities: \n" << endl;
    cout << "1. San Francisco" << endl;
    cout << "2. Fresno" << endl;
    cout << "3. Los Angeles" << endl;
    cout << "4. Monterey\n" << endl;
  
    cout << "Choose the number of one of these cities to calculate tax: ";
    cin >> city;

    while(validCity == false) {

      if (city == 1) {
          taxRate = 0.086; // 8.6% tax rate for San Francisco, CA
          validCity = true;
      }
      else if (city == 2) {
          taxRate = 0.084; // 8.4% tax rate for Fresno, CA
          validCity = true;
      }
      else if (city == 3) {
          taxRate = 0.095; // 9.5% tax rate for Los Angeles, CA
          validCity = true;
      }
      else if (city == 4) {
          taxRate = 0.093; // 9.3% tax rate for Monterey, CA
          validCity = true;
      }
      else {
          cout << endl;
          cout << "Choose a valid option (1 - 5): "; // restarts loop if user enters an invalid option
          cin >> city;
      }
      
    }

    return subtotal * taxRate; // calculated tax
}
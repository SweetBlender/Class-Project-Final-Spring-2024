#include <iostream>
using namespace std;

/*

welcome to Catalog.h!
---------------------

This class contains each item in each category. Each object based on this class is one category.
For Example: an object can be based on a food menu, another can be based on a drink menu, etc.

For each category, there will be an amount of five items,
hence why there are 5 string and double variables.

*/

class Catalog {
public:
  Catalog();                                            // default constructor
  Catalog(string, string, string, string, string);      // constructor for items
  Catalog(double, double, double, double, double);      // constructor for prices
  ~Catalog();                                           // destructor

  // Getters (we don't need setters, we can just use constructors lol):
  string getItem1() const;
  string getItem2() const;
  string getItem3() const;
  string getItem4() const;
  string getItem5() const;

  double getPrice1() const;
  double getPrice2() const;
  double getPrice3() const;
  double getPrice4() const;
  double getPrice5() const;

private: // each item in a category, along with their prices.
  string item1, item2, item3, item4, item5;
  double price1, price2, price3, price4, price5;

};
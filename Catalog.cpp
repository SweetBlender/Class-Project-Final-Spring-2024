#include <iostream>
#include "Catalog.h"

using namespace std;

// CONSTRUCTORS:

Catalog::Catalog() { // default constructor, which obviously means default values
  
  item1 = "N/A";
  item2 = "N/A";
  item3 = "N/A";
  item4 = "N/A";
  item5 = "N/A";

  price1 = 0;
  price2 = 0;
  price3 = 0;
  price4 = 0;
  price5 = 0;
  
}

Catalog::Catalog(string item1, string item2, string item3, string item4, string item5) { // items
  
  this->item1 = item1;
  this->item2 = item2;
  this->item3 = item3;
  this->item4 = item4;
  this->item5 = item5;
  
}

Catalog::Catalog(double price1, double price2, double price3, double price4, double price5) { // prices

  this->price1 = price1;
  this->price2 = price2;
  this->price3 = price3;
  this->price4 = price4;
  this->price5 = price5;

}

// GETTERS:

string Catalog::getItem1() const {
  return item1;
}

string Catalog::getItem2() const {
  return item2;
}

string Catalog::getItem3() const {
  return item3;
}

string Catalog::getItem4() const {
  return item4;
}

string Catalog::getItem5() const {
  return item5;
}

double Catalog::getPrice1() const {
  return price1;
}

double Catalog::getPrice2() const {
  return price2;
}

double Catalog::getPrice3() const {
  return price3;
}

double Catalog::getPrice4() const {
  return price4;
}

double Catalog::getPrice5() const {
  return price5;
}

// DESTRUCTOR:

Catalog::~Catalog() {} // no printing needed...
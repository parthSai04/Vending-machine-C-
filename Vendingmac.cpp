
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
using namespace std;
template <typename T>
class Product
{
protected:
 string name;
 double price;
public:
 Product(string name, double price) : name(name),
price(price) {}
 virtual ~Product() {}
 virtual void display() const = 0;
 string getName() const
 {
 return name;
 }
 double getPrice() const
 {
 return price;
 }
};
template <typename T>
class Drink : public Product<T>
{
private:
 double volume;
public:
 Drink(string name, double price, double volume) :
Product<T>(name, price), volume(volume) {}
 void display() const override
 {
 cout << "- " << this->name << " (Rs" << this->price
<< ", " << volume << "ml)\n";
 }
};
template <typename T>
class Snack : public Product<T>
{
private:
 string type;
public:
 Snack(string name, double price, string type) :
Product<T>(name, price), type(type) {}
 void display() const override
 {
 cout << "- " << this->name << " (Rs" << this->price
<< ", " << type << ")\n";
 }
};
template <typename T>
class VendingMachine {
private:
 vector<Product<T>*> products;
 map<T, int> inventory;
 double balance;
public:
 VendingMachine(vector<Product<T>*> products) :
products(products), balance(0.0)
 {
 // products in stock of vending machine is 10
 for (auto p : products)
 {
 inventory[p->getName()] = 10;
 }
 }
 ~VendingMachine()
 {
 for (auto p : products)
 {
 delete p;
 }
 }
 void displayProducts() const {
 cout << "Products available:\n";
 for (int i = 0; i < products.size(); i++)
 {
 cout << i + 1 << ". ";
 products[i]->display();
 }
 }
 bool purchase(const T& product, int quantity)
 {
 auto it = inventory.find(product);
 if (it == inventory.end())
 {
 throw invalid_argument("Invalid product");
 }
 if (it->second < quantity)
 {
 cout << "Insufficient inventory. Do you want to buy something else? (Y/N) ";
 char ch;
 cin >> ch;
 if (ch == 'Y' || ch == 'y')
 {
 return false;
 }
 else if (ch != 'N' && ch != 'n')
 {
 throw invalid_argument("Invalid choice");
 }
 return true;
 }
 for (auto p : products)
 {
 if (p->getName() == product)
 {
 double price = p->getPrice() * quantity;
 if (balance < price)
 {
 cout << "Insufficient balance. Do you want to insert more currency? (Y/N) ";
 char ch;
 cin >> ch;
 if (ch == 'Y' || ch == 'y')
 {
 return false;
 }
 else if (ch != 'N' && ch != 'n')
 {
 throw invalid_argument("Invalid choice");
 }
 return true;
 }
 balance -= price;
 it->second -= quantity;
 cout << "You have purchased " << quantity <<" " << product << "(s) for Rs" << price << "\n";
 cout << "Balance remaining: Rs" << balance
<< "\n";
 return true;
 }
 }
 throw invalid_argument("Invalid product");
 }
 bool payWithCash(double amount)
 {
 if (amount <= 0)
 {
 throw invalid_argument("Invalid amount");
 }
 balance += amount;
 cout << "Cash accepted: Rs" << amount << "\n";
 cout << "Balance: Rs" << balance << "\n";
 return true;
 }
 bool payWithDigital(double amount)
 {
 if (amount <= 0)
 {
 throw invalid_argument("Invalid amount");
 }
 cout << "Connecting to payment gateway...\n";
 cout << "Payment successful: Rs" << amount <<
"\n";
 balance += amount;
 cout << "Balance: Rs" << balance << "\n";
 return true;
 }
};
int main()
{
 string st="vending mechine";
 cout<<"------VENDING MACHINE--------"<<endl;
 vector<Product<string>*> products {
 new Drink<string>("coke", 45.0, 250),
 new Drink<string>("Coke", 90.0, 500),
 new Drink<string>("pepsi", 45.0, 250),
 new Drink<string>("Pepsi", 90.0, 500),
 new Drink<string>("sprite", 45.0, 250),
 new Drink<string>("Sprite", 90.0, 500),
 new Drink<string>("fanta", 45.0, 250),
 new Drink<string>("Fanta", 90.0, 500),
 new Drink<string>("appyFizz", 35.0, 250),
 new Drink<string>("AppyFizz", 70.0, 500),
 new Drink<string>("Water", 20.0, 500),
 new Drink<string>("water", 10.0, 250),
 new Drink<string>("Lassi", 20.0, 250),
 new Drink<string>("Amul Milk", 20.0, 250),
 new Drink<string>("Tea", 30.0, 250),
 new Drink<string>("Iced Tea", 35.0, 250),
 new Drink<string>("Frooti", 20.0, 250),
 new Drink<string>("Chocolate Milkshake", 25.0,250),
 new Drink<string>("Mango Milkshake", 25.0, 250),
 new Drink<string>("Hot Chocolate", 40.0, 350),
 new Drink<string>("Real Orange Juice", 20.0, 250),
 new Snack<string>("Chips", 30.0, "Lays"),
 new Snack<string>("Biscuit", 25.0, "Oreo"),
 new Snack<string>("biscuit", 25.0, "JimJam"),
 new Snack<string>("Sandwich", 35.0, "Cheese"),
 new Snack<string>("Pizza Pockets", 50.0,"cheese"),
 new Snack<string>("Cupcake", 45.0, "ChocoChip"),
 new Snack<string>("toffee",2.0,"eclairs"),
 new Snack<string>("Toffee",5.0,"melody"),
 new Snack<string>("choclate",20,"dairy milk"),
 };
 ofstream outfile("product.txt");
 outfile<<st;
 cout<<st;
 ifstream infile("products.txt");
 string name, type;
 double price, volume;
 char productType;
 while (infile >> productType >> name >> price)
 {
 if (productType == 'D')
 {
 infile >> volume;
 products.push_back(new Drink<string>(name,price, volume));
 }
 else if (productType == 'S')
 {
 infile >> type;
 products.push_back(new Snack<string>(name,price, type));
 }
 }
 VendingMachine<string> vm(products);
 vm.displayProducts();
 double amount;
 char choice;
 string product;
 int quantity;
 cout << "Select payment method (C for cash payment/D for digital payment): ";
 cin >> choice;
 try
 {
 if (choice == 'C' || choice == 'c')
 {
 do
 {
 cout << "Enter amount (in Rs): ";
 cin >> amount;
 }
 while (!vm.payWithCash(amount));
 }
 else if (choice == 'D' || choice == 'd')
 {
 do
 {
 cout << "Enter amount (in Rs): ";
 cin >> amount;
 }
 while (!vm.payWithDigital(amount));
 }
 else
 {
 throw invalid_argument("Invalid payment method");
 }
 do
 {
 cout << "Enter product number (1-" <<
products.size() << "): ";
 int productNumber;
 cin >> productNumber;
 if (productNumber < 1 || productNumber >
products.size())
 {
 cout << "Invalid product number. Do you want to buy something else? (Y/N) ";
 char ch;
 cin >> ch;
 if (ch == 'N' || ch == 'n')
 {
 break;
 }
 else if (ch != 'Y' && ch != 'y')
 {
 throw invalid_argument("Invalid choice");
 }
 continue;
 }
 cout << "Enter quantity: ";
 cin >> quantity;
 product = products[productNumber - 1]->getName();
 if (vm.purchase(product, quantity))
 {
 char ch;
 cout << "Do you want to buy something else?(Y/N) ";
 cin >> ch;
 if (ch == 'N' || ch == 'n')
 {
 break;
 }
 else if (ch != 'Y' && ch != 'y')
 {
 throw invalid_argument("Invalid choice");
 }
 }
 else
 {
 if (choice == 'C' || choice == 'c')
 {
 do
 {
 cout << "Enter amount (in Rs): ";
 cin >> amount;
 }
 while (!vm.payWithCash(amount));
 }
 else if (choice == 'D' || choice == 'd')
 {
 do
 {
 cout << "Enter amount (in Rs): ";
 cin >> amount;
 } while (!vm.payWithDigital(amount));
 }
 }
 }
 while (true);
 }
 catch (const exception& e)
 {
 cout << "Error: " << e.what() << "\n";
 return 1;
 }
 cout << "Thank you for using our vending machine\n";
 return 0;
}

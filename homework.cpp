#include <iostream>
using namespace std;
//class Book {
//
//public: 
//	string title;
//	string author;
//	int pages;
// 
//	void displayInfo() {
//
//		cout << "title: "  << title << " The author: " << author << " Page: " << pages << endl;
//	}
//};
//int main() {
//
//	Book b1;
//	b1.title = "Kolobok";
//	b1.author = "narod";
//	b1.pages = 20;
//	b1.displayInfo();
//	return 0;
//}
//2
//class Student {
//
//private:
//	string name;
//	int age;
//
//public: 
//     Student(string n, int a)
//	{
//     
//		name = n;
//		age = a;
//
//	 }
//    
//	void display() {
//
//		cout << "Name: " << name << " Age: " << age << endl;
//
//	}
//
//};
//int main() {
//
//	Student s1("Luisne", 18);
//	s1.display();
//	return 0;
//
//}
//4
//class Car
//{
//private:
//    int speed;
//
//public:
//    void setSpeed(int s)
//    {
//        if (s >= 0)
//            speed = s;
//        else
//            cout << "Speed cannot be negative!" << endl;
//    }
//
//    int getSpeed()
//    {
//        return speed;
//    }
//};
//
//
//int main()
//{
//    Car car1;
//    car1.setSpeed(100);
//    cout << "Car speed: " << car1.getSpeed() << endl;
//
//    car1.setSpeed(-10);
//
//
//    return 0;
//}
//5
//#include <string>
//class Person
//{
//protected:
//    string name;
//    int age;
//
//public:
//    Person(string n, int a)
//    {
//        name = n;
//        age = a;
//    }
//
//    void displayPerson()
//    {
//        cout << "Name: " << name << ", Age: " << age << endl;
//    }
//};
//
//class Employee : public Person
//{
//private:
//    string position;
//
//public:
//    Employee(string n, int a, string p) : Person(n, a)
//    {
//        position = p;
//    }
//
//    void displayEmployee()
//    {
//        displayPerson();
//        cout << "Position: " << position << endl;
//    }
//};

//int main()
//{
//    Employee e1("Alex", 30, "Developer");
//    e1.displayEmployee();
//
//    return 0;
//}
//6
//class Shape {
//public:
//    virtual double area() const = 0;
//
//    virtual ~Shape() = default;
//};
//
//class Rectangle : public Shape {
//private:
//    double width;
//    double height;
//
//public:
//    Rectangle(double w, double h) : width(w), height(h) {}
//
//    
//    double area() const override {
//        return width * height;
//    }
//};
//
//
//class Circle : public Shape {
//private:
//    double radius;
//
//public:
//  
//    Circle(double r) : radius(r) {}
//
//
//    double area() const override {
//        return 3.14 * radius * radius; 
//    }
//};
//
//int main() {
//
//    Rectangle rect(5.0, 3.0);  
//    Circle circle(4.0);          
//
//   
//    Shape* shapes[] = { &rect, &circle };
//
//    std::cout << "Площади фигур:\n";
//    for (Shape* shape : shapes) {
//        std::cout << shape->area() << "\n";
//    }
//
//    return 0;
//}
//7
//class Point {
//public:
//	double  x;
//	double  y;
//
//      Point() : x(0.0), y(0.0) {}
// };
//
//int main() {
//
//        Point p;
//
//        std::cout << "Cordinates:\n";
//        std::cout << "X = " << p.x << ", Y = " << p.y << "\n";
//
//        return 0;
// }
//8
//class Point {
//public:
//	double x;
//	double y;
//
//	Point(double x1, double y1) {
//
//		x = x1;
//
//	    y = y1;
//
//	}
//
//    void displayinfo() {
//
//		cout << "Cordinates: " << endl;
//
//	}
//};
//int Main() {
//
//	Point p1(5.00, 10.00);
//	p1.displayinfo();
//	return 0;
//
//}

//9 
//class BankAccount {
//
//private:
//	double balance;
//    string  accountNumber;
//public:
//	BankAccount(const string& accNum, double initialBalance = 0.0)
//		: accountNumber(accNum), balance(initialBalance) {
//	}
//	void deposit(int amount) {
//		if (amount > 0) {
//			balance += amount;
//			cout << "Add " << amount << " succsess.\n";
//		}
//		else {
//		    cout << "Error.\n";
//		}
//	}
//	void withdraw(int amount)
//	{
//		if (amount <= 0) {
//			std::cout << "Error, the sum has to be more than 0!\n";
//			return;
//		}
//		if (balance >= amount) {
//			balance -= amount;
//			std::cout << "minus  " << amount << " ok.\n";
//		}
//		else {
//			std::cout << "error, you don't have enough money \n";
//			std::cout << "your money : " << balance << ", requested amount: " << amount << "\n";
//		}
//	}
//
//	
//	void display() const {
//		std::cout << "Account number: " << accountNumber << "\n";
//		std::cout << "Balance: " << balance << "\n";
//	}
//};
//int main() {
//
//	BankAccount account("Agj12345", 1000.0);
//
//
//	std::cout << "Initial account status:\n";
//	account.display();
//
//
//
//	account.deposit(5000);      
//	account.withdraw(200);    
//	account.withdraw(1500); 
//	account.deposit(-100);  
//
//	std::cout << "\nFinal account balance:\n";
//	account.display();
//
//	return 0;
//}
//	
//`10




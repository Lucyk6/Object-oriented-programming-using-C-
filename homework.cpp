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

/*class Student {
private:
    string name;
public:

    Student(const string& studentName) : name(studentName) {}

 
   string getName() const {
        return name;
    }

  
    void setName(const string& newName) {
        name = newName;
    }
};

void changeStudentName(Student& student, const string& newName) {
    student.setName(newName);
}

int main() {
    Student student1("lusiine");
    Student student2("lizaa");

    cout << "Name of first student: " << student1.getName() << endl;
    cout << "Name of second student : " << student2.getName() <<endl;

    changeStudentName(student1, "Liza ");

    changeStudentName(student2, "Lusine ");

 
    cout << "first: " << student1.getName() <<endl;
    cout << "scond : " << student2.getName() << endl;

    return 0;
}
//11
#include <iostream>
#include <string>

class Animal {
protected:
    std::string name;
public:
    Animal(const std::string& animalName) : name(animalName) {}
    std::string getName() const { return name; }
};

class Dog : public Animal {
private:
    std::string breed;
public:
    Dog(const std::string& dogName, const std::string& dogBreed)
        : Animal(dogName), breed(dogBreed) {
    }

    std::string getBreed() const { return breed; }
};

int main() {
    Dog myDog("murka", "doberman");
    std::cout << "Name: " << myDog.getName() << std::endl;
    std::cout << "poroda: " << myDog.getBreed() << std::endl;
    return 0;
}
//12
#include <iostream>

class Rectangle {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double area() const {
        return length * width;
    }

    double perimeter() const {
        return 2 * (length + width);
    }
};

int main() {
    Rectangle rect(5.0, 3.0);
    std::cout << "S: " << rect.area() << std::endl;
    std::cout << "P: " << rect.perimeter() << std::endl;
    return 0;
}
//13
#include <iostream>

class Counter {
private:
    int count;
public:
    Counter() : count(0) {}

    void increment() {
        count++;
    }

    int getCount() const {
        return count;
    }
};

int main() {
    Counter myCounter;
    myCounter.increment();
    myCounter.increment();
    myCounter.increment();
    std::cout << "znachenie : " << myCounter.getCount() << std::endl;
    return 0;
}
//14
#include <iostream>

class Vehicle {
public:
    virtual void fuelEfficiency() const {
        std::cout << "Fuel efficiency of the base vehicle" << std::endl;
    }
    virtual ~Vehicle() = default; 
};

class Car : public Vehicle {
public:
    void fuelEfficiency() const override {
        std::cout << "Vehicle efficiency: 8 l/100 km" << std::endl;
    }
};

class Truck : public Vehicle {
public:
    void fuelEfficiency() const override {
        std::cout << "Truck efficiency: 25 l/100 km" << std::endl;
    }
};

int main() {
    Vehicle* vehicles[3];
    vehicles[0] = new Car();
    vehicles[1] = new Truck();
    vehicles[2] = new Vehicle();

    for (int i = 0; i < 3; ++i) {
        vehicles[i]->fuelEfficiency();
    }


    for (int i = 0; i < 3; ++i) {
        delete vehicles[i];
    }
    return 0;
}
//15
#include <iostream>
#include <vector>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
public:
    Book(const std::string& bookTitle, const std::string& bookAuthor)
        : title(bookTitle), author(bookAuthor) {
    }

    void display() const {
        std::cout << "\"" << title << "\" — " << author << std::endl;
    }

    friend class Library; 
};

class Library {
private:
    std::vector<Book> books;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayAllBooks() const {
        if (books.empty()) {
            std::cout << "clean liberary" << std::endl;
            return;
        }
        std::cout << "List of books in the library:" << std::endl;
        for (const auto& book : books) {
            book.display();
        }
    }
};

int main() {
    Library myLibrary;
    Book book1("War and Peace", "Tolstoy");
    Book book2("Crime and punishment", "Fyodor Dostoevsky");
    Book book3("The Master and Margarita", "Mikhail Bulgakov");

    myLibrary.addBook(book1);
    myLibrary.addBook(book2);
    myLibrary.addBook(book3);

    myLibrary.displayAllBooks();
    return 0;
}
*/




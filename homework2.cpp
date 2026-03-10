//1
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;

public:

    Student() : name("Unknown"), age(0) {}

    Student(const string& name, int age) : name(name), age(age) {}

    ~Student() {
        cout << "Destructor called for student: " << name << endl;
    }

    void print() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    Student s1;
    Student s2("Alex", 20);

    s1.print();
    s2.print();

    return 0;
}
//2
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
	string title;
	int pages;
public:
 
    Book(const string& title, int pages) : title(title), pages(pages) {
        cout << "Book created" << endl;
    }
    ~Book() {
        cout << "Book deleted" << endl;

    }
    void printInfo() const {
        cout << "Title: " << title << ", Pages: " << pages << endl;
    }

};
int main() {

    Book b1("kolobok", 55);
    b1.printInfo();
    Book b2("the great gasby", 359);
    b2.printInfo();

}
//3
#include <iostream>
#include <string>
using namespace std;

class Car{
private:
	string Brand;
	int year;
public:
 
public:
    
    Car(const string& brand, int year) : Brand(brand), year(year) {}

    Car() : Brand("Unknown"), year(0) {}

    void info() const {
        cout << "Brand: " << Brand << ", Year: " << year << endl;
    }
};
int main() {

    Car cars[3] = {
        Car("Toyota", 2020),
        Car("BMW", 2022),
        Car("Mersedes",2024)
    };

    cout << "Car information:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ". ";
        cars[i].info();
    }

    return 0;
}


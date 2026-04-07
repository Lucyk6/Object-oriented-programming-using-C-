#include <iostream>
using namespace std;
class Transport {
public:
    virtual void move() = 0;

};
class car :public Transport {
public:
    void move() {
        cout << "is turned on" << endl;
    }
};
class Bike: public Transport {
public:
    void move() {
        cout << "is turned off" << endl;
    }
};
int main()
{
    Transport* t;
    car cm;
    Bike b;
    t = &cm;
    t->move();
    t = &b;
    t->move();


 }
 
 2)
class Animal {
public:
    virtual void Sounds() = 0;

};
class Dog :public Animal {
public:
    void Sounds() {
        cout << "Wouf" << endl;
    }
};
class Cow : public Animal {
public:
    void Sounds() {
        cout << "MUUU" << endl;
    }
};
int main()
{
    Animal* a;
    Dog d;
    Cow c;
    a = &d;
    a->Sounds();
    a = &c;
    a->Sounds();
}
/*3)*/

class Shape {
public:
    virtual double area() const = 0;

};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() const override {
        return side * side;
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const override {
        return 0.5 * base * height;
    }
};
int main()
{
    Shape* s1 = new Square(5);
    Shape* s2 = new Triangle(3, 4);
    cout << "Square area: " << s1->area() << endl;
    cout << "Triangle area: " << s2->area() << endl;
    delete s1;
    delete s2;
    return 0;

}
4)
class Device {
public:
    virtual void turnOn() = 0; 
};

class Phone : public Device {
public:
    void turnOn() override {
        cout << "Phone is turned on." << endl;
    }
};

class Laptop : public Device {
public:
    void turnOn() override {
        cout << "Laptop is turned on." << endl;
    }
};

int main() {
    Phone myPhone;
    Laptop myLaptop;

    myPhone.turnOn();    
    myLaptop.turnOn();   

    return 0;
}
5)
class Drink {
public:
    virtual void prepare() = 0; 
    virtual ~Drink() {}
};

class Tea : public Drink {
public:
    void prepare() override {
        cout << "Preparing tea..." << endl;
    }
};

class Coffee : public Drink {
public:
    void prepare() override {
        cout << "Preparing coffee..." << endl;
    }
};

int main() {
    Tea myTea;
    Coffee myCoffee;
    myTea.prepare();    
    myCoffee.prepare(); 

    return 0;
}
6)
class Payment {
public:
    virtual void pay() = 0;
    virtual ~Payment() {}
};


class Card : public Payment {
public:
    void pay() override {
        cout << "Paying with card." << endl;
    }
};

class Cash : public Payment {
public:
    void pay() override {
        cout << "Paying with cash." << endl;
    }
};

class Crypto : public Payment {
public:
    void pay() override {
        cout << "Paying with cryptocurrency." << endl;
    }
};

int main() {
  
    Payment* payments[3];

    payments[0] = new Card();
    payments[1] = new Cash();
    payments[2] = new Crypto();

    for (int i = 0; i < 3; ++i) {
        payments[i]->pay();
        delete payments[i];
    }

    return 0;
}
7)
class Employee {
public:
    virtual void salary() = 0;
    virtual ~Employee() {}
};


class Manager : public Employee {
public:
    void salary() override {
        cout << "3000" << endl;
    }
};

class Developer : public Employee {
public:
    void salary() override {
        cout << "5894794" << endl;
    }
};

int main() {

    Employee* Employees[2];

    Employees[0] = new Manager();
    Employees[1] = new Developer();

    for (int i = 0; i < 2; ++i) {
        Employees[i]->salary();
        delete Employees[i];
    }

    return 0;
}
8)
class File {
public:
    virtual void open() = 0;
    virtual ~File() {}
};

class TextFile : public File {
public:
    void open() override {
        cout << "open txt file." << endl;
    }
};


class ImageFile : public File {
public:
    void open() override {
        cout << "open graphic files ." << endl;
    }
};

int main() {
    File* f1 = new TextFile();
    File* f2 = new ImageFile();
    f1->open();
    f2->open();
    delete f1;
    delete f2;
    return 0;
}
9)
class Message {
public:
    virtual void send() = 0;
    virtual ~Message() {}
};

class Email : public Message {
public:
    void send() override {
        cout << "Отправлено сообщение Email." << endl;
    }
};

class SMS : public Message {
public:
    void send() override {
        cout << "Отправлено сообщение SMS." << endl;
    }
};

int main() {
    Message* m1 = new Email();
    Message* m2 = new SMS();

    m1->send();
    m2->send();

    delete m1;
    delete m2;
    return 0;
}
10)
class Enemy {
public:
    virtual void attack() = 0;
    virtual ~Enemy() {}
};

class Zombie : public Enemy {
public:
    void attack() override {
        cout << "zombiee" << endl;
    }
};

class Alien : public Enemy {
public:
    void attack() override {
        cout << "alienn wuaaaa" << endl;
    }
};

int main() {
    Enemy* e1 = new Zombie();
    Enemy* e2 = new Alien();

    e1->attack();
    e2->attack();

    delete e1;
    delete e2;
    return 0;
}
11)
class Account {
public:
    virtual void calculateInterest() = 0;
    virtual ~Account() {}
};

class SavingsAccount : public Account {
public:
    void calculateInterest() override {
        cout << "Calculating interest for savings account." << endl;
    }
};

class FixedDeposit : public Account {
public:
    void calculateInterest() override {
        cout << "Calculating interest for fixed deposit." << endl;
    }
};

int main() {
    Account* acc1 = new SavingsAccount();
    Account* acc2 = new FixedDeposit();

    acc1->calculateInterest();
    acc2->calculateInterest();

    delete acc1;
    delete acc2;
    return 0;
}
12)
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    double M_PI = 3.14;
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};
int main() {
    Shape* rect = new Rectangle(3.0, 4.0);
    Shape* circ = new Circle(5.0);

    cout << "Rectangle area: " << rect->area() << endl;
    cout << "Rectangle perimeter: " << rect->perimeter() << endl;
    cout << "Circle area: " << circ->area() << endl;
    cout << "Circle perimeter: " << circ->perimeter() << endl;

    delete rect;
    delete circ;
    return 0;
}
13)
class Media {
public:
    virtual void play() = 0;
    virtual ~Media() {}
};

class Audio : public Media {
public:
    void play() override {
        cout << "Playing audio." << endl;
    }
};

class Video : public Media {
public:
    void play() override {
        cout << "Playing video." << endl;
    }
};

int main() {
    Media* media1 = new Audio();
    Media* media2 = new Video();

    media1->play();
    media2->play();

    delete media1;
    delete media2;
    return 0;
}
 14)
class Notification {
public:
    virtual void notify() = 0;
    virtual ~Notification() {}
};

class Push : public Notification {
public:
    void notify() override {
        cout << "Push notification sent." << endl;
    }
};

class EmailNotification : public Notification {
public:
    void notify() override {
        cout << "Email notification sent." << endl;
    }
};

int main() {
    Notification* notif1 = new Push();
    Notification* notif2 = new EmailNotification();

    notif1->notify();
    notif2->notify();

    delete notif1;
    delete notif2;
    return 0;
}
15)
class Robot {
public:
    virtual void work() = 0;
    virtual ~Robot() {}
};

class CleanerRobot : public Robot {
public:
    void work() override {
        cout << "Cleaning the house." << endl;
    }
};

class BuilderRobot : public Robot {
public:
    void work() override {
        cout << "Building structures." << endl;
    }
};

int main() {
    Robot* robot1 = new CleanerRobot();
    Robot* robot2 = new BuilderRobot();

    robot1->work();
    robot2->work();

    delete robot1;
    delete robot2;
    return 0;
}
16)
#include <iostream>
using namespace std;

class Flyable {
public:
    virtual void fly() = 0;
    virtual ~Flyable() {}
};

class Swimmable {
public:
    virtual void swim() = 0;
    virtual ~Swimmable() {}
};

class Duck : public Flyable, public Swimmable {
public:
    void fly() override {
        cout << "Duck is flying." << endl;
    }
    void swim() override {
        cout << "Duck is swimming." << endl;
    }
};

int main() {
    Duck d;
    d.fly();
    d.swim();
    return 0;
}
17)
#include <iostream>
using namespace std;

class Logger {
public:
    virtual void log(const string& message) = 0;
    virtual ~Logger() {}
};

class FileLogger : public Logger {
public:
    void log(const string& message) override {
        cout << "Log to file: " << message << endl;
    }
};

class ConsoleLogger : public Logger {
public:
    void log(const string& message) override {
        cout << "Console log: " << message << endl;
    }
};

int main() {
    Logger* logger1 = new FileLogger();
    Logger* logger2 = new ConsoleLogger();

    logger1->log("Error occurred");
    logger2->log("Warning message");

    delete logger1;
    delete logger2;
    return 0;
}
18)
#include <iostream>
using namespace std;

class Delivery {
public:
    virtual void deliver() = 0;
    virtual ~Delivery() {}
};

class Courier : public Delivery {
public:
    void deliver() override {
        cout << "Delivering by courier." << endl;
    }
};

class Drone : public Delivery {
public:
    void deliver() override {
        cout << "Delivering by drone." << endl;
    }
};

int main() {
    Delivery* del1 = new Courier();
    Delivery* del2 = new Drone();

    del1->deliver();
    del2->deliver();

    delete del1;
    delete del2;
    return 0;
}
19)
#include <iostream>
using namespace std;
class Course {
public:
    virtual void start() = 0;
    virtual ~Course() {}
};

class OnlineCourse : public Course {
public:
    void start() override {
        cout << "Starting online course." << endl;
    }
};

class OfflineCourse : public Course {
public:
    void start() override {
        cout << "Starting offline course." << endl;
    }
};

int main() {
    Course* c1 = new OnlineCourse();
    Course* c2 = new OfflineCourse();

    c1->start();
    c2->start();

    delete c1;
    delete c2;
    return 0;
}
20)
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Product {
public:
    virtual double getPrice() const = 0;
    virtual ~Product() {}
};

class Book : public Product {
private:
    double price;
public:
    Book(double p) : price(p) {}
    double getPrice() const override {
        return price;
    }
};

class Electronics : public Product {
private:
    double price;
public:
    Electronics(double p) : price(p) {}
    double getPrice() const override {
        return price;
    }
};

class Clothing : public Product {
private:
    double price;
public:
    Clothing(double p) : price(p) {}
    double getPrice() const override {
        return price;
    }
};

int main() {
    vector<Product*> products;

    products.push_back(new Book(15.99));
    products.push_back(new Electronics(199.99));
    products.push_back(new Clothing(49.99));

    double total = 0;
    for (auto p : products) {
        cout << "Price: $" << p->getPrice() << endl;
        total += p->getPrice();
    }
    cout << "all price: $" << total << endl;
    for (auto p : products) {
        delete p;
    }
    return 0;
}

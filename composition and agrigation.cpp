#include <iostream>
using namespace std;
1)
class  Author {
public:
	void name() {
		cout << "smth" << endl;
	}
};
class Book {
private:
	Author* author;

public:
	Book(Author* a) {
		author = a;
	 }

	void run() {
		author->name();
	}
};
int main()
{
	Author a;
	Book b(&a);
	b.run();
}
 2)
class Furniture {
public:
	void chair() {

		cout << "nice chair" << endl;

	 }
};
class Room {

private:

	Furniture f;
public:
	void run() {
		f.chair();
	}
};
int main() {
	Room r;
	r.run();
 
}
3)
class Account {
public:
    Account(const string& userName) : username(userName) {}
    void show() const { cout << "Account of user: " << username << endl; }
private:
    string username;
};

class User {
public:
    User(const string& name) : username(name), account(new Account(name)) {}
    ~User() { delete account; }

    void show() const {
        cout << "User: " << username << endl;
        account->show();
    }
private:
    string username;
    Account* account;
};
int main() {
    User user1("Ivan");
    User user2("jflsdfj");
    user1.show();
    user2.show();
    return 0;
}
4)
#include <vector>
#include <string>
using namespace std;

class Teacher {
public:
    Teacher(const string& name) : teacherName(name) {}
    void show() const { cout << "Teacher: " << teacherName << endl; }
private:
    string teacherName;
};

class School {
public:
    void addTeacher(const Teacher& t) { teachers.push_back(t); }
    void showTeachers() const {
        for (const auto& t : teachers) {
            t.show();
        }
    }
private:
    vector<Teacher> teachers; 
};
int main() {
 
    School mySchool;

    Teacher teacher1("Ilya aoaoao");
    Teacher teacher2("Max zyev");
    Teacher teacher3("Liza Mishenko");
    mySchool.addTeacher(teacher1);
    mySchool.addTeacher(teacher2);
    mySchool.addTeacher(teacher3);

    mySchool.showTeachers();
    return 0;
}
5)
#include <vector>
#include <string>
using namespace std;

class Wheel {
public:
    Wheel(int size) : diameter(size) {}
    void show() const { cout << "Wheel diameter: " << diameter << endl; }
private:
    int diameter;
};

class Car {
public:
    Car(int numWheels, int wheelSize) {
        for (int i = 0; i < numWheels; i++) {
            wheels.push_back(Wheel(wheelSize));
        }
    }

    void showWheels() const {
        for (const auto& w : wheels) {
            w.show();
        }
    }
private:
    vector<Wheel> wheels; 

};
int main() {
    Car myCar(4, 16);
    myCar.showWheels();
    return 0;
}
6)
#include <vector>
#include <string>
using namespace std;

class Employee {
public:
    Employee(const string& name) : empName(name) {}
    void show() const { cout << "Employee: " << empName << endl; }
private:
    string empName;
};

class Company {
public:
    void addEmployee(Employee* e) { employees.push_back(e); }
    void showEmployees() const {
        for (const auto& e : employees) {
            e->show();
        }
    }
private:
    vector<Employee*> employees; 
};
int main() {
  
    Employee* emp1 = new Employee("liza");
    Employee* emp2 = new Employee("max");
    Employee* emp3 = new Employee("ilya");
    Company myCompany;

    myCompany.addEmployee(emp1);
    myCompany.addEmployee(emp2);
    myCompany.addEmployee(emp3);

    myCompany.showEmployees();

    delete emp1;
    delete emp2;
    delete emp3;

    return 0;
}
7)
#include <string>
using namespace std;

class Keyboard {
public:
    void pressKey() { cout << "Key pressed." << endl; }
};

class Laptop {
public:
    Laptop() : keyboard(new Keyboard) {}
    ~Laptop() { delete keyboard; }

    void useKeyboard() { keyboard->pressKey(); }
private:
    Keyboard* keyboard;
};
int main() {

    Laptop myLaptop;

    myLaptop.useKeyboard();

    return 0;
}
8)
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    Student(const string& name) : studentName(name) {}
    void show() const { cout << "Student: " << studentName << endl; }
private:
    string studentName;
};

class Course {
public:
    void addStudent(Student* s) { students.push_back(s); }
    void showStudents() const {
        for (const auto& s : students) {
            s->show();
        }
    }
private:
    vector<Student*> students; 
};
int main() {

    Student* s1 = new Student("anna");
    Student* s2 = new Student("liza");
    Student* s3 = new Student("ao");


    Course myCourse;


    myCourse.addStudent(s1);
    myCourse.addStudent(s2);
    myCourse.addStudent(s3);


    myCourse.showStudents();

    delete s1;
    delete s2;
    delete s3;

    return 0;
}
9-15)
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Track {
public:
    string title;
    string artist;

    Track(const string& t, const string& a) : title(t), artist(a) {}
    void show() const {
        cout << "Track: " << title << " by " << artist << endl;
    }
};

class Player {
public:
    vector<Track*> tracks; 

    void addTrack(Track* track) {
        tracks.push_back(track);
    }

    void showTracks() const {
        for (auto track : tracks) {
            track->show();
        }
    }
};

class Customer {
public:
    string name;

    Customer(const string& n) : name(n) {}
    void show() const {
        cout << "Customer: " << name << endl;
    }
};

class Order {
public:
    Customer* customer; 
    string product;

    Order(Customer* c, const string& p) : customer(c), product(p) {}

    void show() const {
        customer->show();
        cout << "Order for: " << product << endl;
    }
};


class Battery {
public:
    int capacity;

    Battery(int c) : capacity(c) {}
    void show() const {
        cout << "Battery capacity: " << capacity << " mAh" << endl;
    }
};

class Smartphone {
public:
    Battery battery; 

    Smartphone(int batteryCapacity) : battery(batteryCapacity) {}

    void show() const {
        cout << "Smartphone with ";
        battery.show();
    }
};


class Book {
public:
    string title;
    string author;

    Book(const string& t, const string& a) : title(t), author(a) {}
    void show() const {
        cout << "Book: " << title << " by " << author << endl;
    }
};

class Library {
public:
    vector<Book*> books;

    void addBook(Book* book) {
        books.push_back(book);
    }

    void showBooks() const {
        for (auto b : books) {
            b->show();
        }
    }
};

class Level {
public:
    int number;

    Level(int n) : number(n) {}
    void show() const {
        cout << "Level: " << number << endl;
    }
};

class Game {
public:
    Level level; 

    Game(int levelNumber) : level(levelNumber) {}

    void show() const {
        cout << "Game with ";
        level.show();
    }
};


class Database {
public:
    string name;

    Database(const string& n) : name(n) {}
    void show() const {
        cout << "Database: " << name << endl;
    }
};

class Server {
public:
    Database* db;

    Server(Database* database) : db(database) {}

    void show() const {
        cout << "Server connected to ";
        if (db) db->show();
        else cout << "no database" << endl;
    }
};

int main() {
    Track t1("Imagine", "John Lennon");
    Track t2("Hey Jude", "The Beatles");
    Player player;
    player.addTrack(&t1);
    player.addTrack(&t2);
    player.showTracks();

    Customer customer("Ivan Ivanov");
    Order order(&customer, "Smartphone");
    order.show();

    Smartphone smartphone(4000);
    smartphone.show();


    Book book1("1984", "George Orwell");
    Book book2("Brave New World", "Aldous Huxley");
    Library library;
    library.addBook(&book1);
    library.addBook(&book2);
    library.showBooks();

    Game game(3);
    game.show();

    Database db("MainDB");
    Server server(&db);
    server.show();

    return 0;
}
16-20


class Car {
public:
    string model;

    Car(const string& m) : model(m) {}

    void show() const {
        cout << "Car model: " << model << endl;
    }
};

class Fleet {
public:
    vector<Car*> cars; 

    void addCar(Car* car) {
        cars.push_back(car);
    }

    void showFleet() const {
        for (auto car : cars) {
            car->show();
        }
    }
};

class Heart {
public:
    void beat() const {
        cout << "Heart is beating." << endl;
    }
};

class Human {
public:
    Heart heart;

    void live() const {
        cout << "Human is alive and ";
        heart.beat();
    }
};

class Cart {
public:
    void showItems() const {
        cout << "Cart items displayed." << endl;
    }
};

class User {
public:
    Cart cart; 

    void browse() const {
        cout << "User is browsing. ";
        cart.showItems();
    }
};

class Subject {
public:
    string name;

    Subject(const string& n) : name(n) {}
    void show() const {
        cout << "Subject: " << name << endl;
    }
};

class Teacher {
public:
    string name;
    vector<Subject*> subjects; 

    Teacher(const string& n) : name(n) {}

    void addSubject(Subject* subj) {
        subjects.push_back(subj);
    }

    void showSubjects() const {
        cout << "Teacher " << name << " teaches:" << endl;
        for (auto subj : subjects) {
            subj->show();
        }
    }
};

class CPU {
public:
    void run() const {
        cout << "CPU is running." << endl;
    }
};

class GPU {
public:
    void run() const {
        cout << "GPU is running." << endl;
    }
};

class RAM {
public:
    void run() const {
        cout << "RAM is running." << endl;
    }
};

class Computer {
public:
    CPU cpu; 
    vector<GPU*> gpus; 
    vector<RAM*> rams; 

    void addGPU(GPU* gpu) {
        gpus.push_back(gpu);
    }

    void addRAM(RAM* ram) {
        rams.push_back(ram);
    }

    void run() const {
        cout << "Starting computer components:" << endl;
        cpu.run();
        for (auto gpu : gpus) gpu->run();
        for (auto ram : rams) ram->run();
        cout << "System is up and running." << endl;
    }
};

int main() {

    Car car1("Toyota Camry");
    Car car2("BMW M3");
    Fleet fleet;
    fleet.addCar(&car1);
    fleet.addCar(&car2);
    cout << "Автопарк:" << endl;
    fleet.showFleet();

    Human human;
    human.live();

    User user;
    user.browse();

    Subject math("Mathematics");
    Subject physics("Physics");
    Teacher teacher("Mr. Smith");
    teacher.addSubject(&math);
    teacher.addSubject(&physics);
    teacher.showSubjects();

    CPU cpu;
    GPU gpu1, gpu2;
    RAM ram1, ram2;
    Computer myPC;
    myPC.addGPU(&gpu1);
    myPC.addGPU(&gpu2);
    myPC.addRAM(&ram1);
    myPC.addRAM(&ram2);
    myPC.run();

    return 0;
}

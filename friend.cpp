#include <iostream>
using namespace std;
class Number {
private:
    double value;
public:
    Number(double v) : value(v){}
    friend void shownumbers(Number n1, Number n2);

};
void shownumbers(Number n1, Number n2)
{
    cout << "nubers" << n1.value<< n2.value << endl;
  
}

int main()
{
    Number n1(45.4);
    Number n2(55.4);
    shownumbers(n1,n2);

}
2)
class Value
{
private:
    int first;
    int second;

public:
    Value(int f, int s) : first(f), second(s) {}

    friend int getSum(const Value& v);
};

int getSum(const Value& v)
{
    return v.first + v.second;
}

int main()
{
    Value f1(1000, 7);  
    Value s2(500, 9009);

    int sumF1 = getSum(f1);
    int sumS2 = getSum(s2);

    std::cout << "Sum of f1: " << sumF1 << std::endl;
    std::cout << "Sum of s2: " << sumS2 << std::endl;

    return 0;
}
3)#include <iostream>
using namespace std;

class Data {
private:
    int value;
public:
    Data(int v) : value(v) {}
    int getValue() const { return value; }
    
    friend int max(const Data& a, const Data& b);
};

int max(const Data& a, const Data& b) {
    return (a.value > b.value) ? a.value : b.value;
}

int main() {
    Data d1(10), d2(20);
    cout << "Максимум: " << max(d1, d2) << endl; // Выведет 20
    return 0;
}
4)#include <iostream>
using namespace std;

class Point {
private:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    friend bool isEqual(const Point& p1, const Point& p2);
};

bool isEqual(const Point& p1, const Point& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

int main() {
    Point p1(1.5, 2.5), p2(1.5, 2.5);
    if (isEqual(p1, p2)) {
        cout << "equal" << endl;
    }
    else {
        cout << "not equal" << endl;
    }
    return 0;
}
5)
    #include <iostream>
using namespace std;

class Multiplier {
private:
    int value;
public:
    Multiplier(int v = 1) : value(v) {}
    int getValue() const { return value; }

    friend int multiply(const Multiplier& m1, const Multiplier& m2);
};

int multiply(const Multiplier& m1, const Multiplier& m2) {
    return m1.value * m2.value;
}

int main() {
    Multiplier m1(5), m2(3);
    cout << "Result: " << multiply(m1, m2) << endl; // 15
    return 0;
}
6)#include <iostream>
using namespace std;

class Number {
private:
    int num;
public:
    Number(int n = 0) : num(n) {}
    int getNum() const { return num; }
    
    friend int difference(const Number& n1, const Number& n2);
};

int difference(const Number& n1, const Number& n2) {
    return n1.num - n2.num;
}

int main() {
    Number n1(10), n2(3);
    cout << "Разность: " << difference(n1, n2) << endl; // 7
    return 0;
}
7)#include <iostream>
using namespace std;

class Container {
private:
    int data;
public:
    Container(int d = 0) : data(d) {}
    void print() const { cout << "Data: " << data << endl; }
    
    friend void swap(Container& c1, Container& c2);
};

void swap(Container& c1, Container& c2) {
    int temp = c1.data;
    c1.data = c2.data;
    c2.data = temp;
}

int main() {
    Container c1(10), c2(20);
    cout << "Before:" << endl;
    c1.print();
    c2.print();
    
    swap(c1, c2);
    
    cout << "After:" << endl;
    c1.print();
    c2.print();
    return 0;
}
8)
    #include <iostream>
using namespace std;

class Value {
private:
    int val;
public:
    Value(int v = 0) : val(v) {}
    int getVal() const { return val; }
    
    friend int minOfThree(const Value& v1, const Value& v2, const Value& v3);
};

int minOfThree(const Value& v1, const Value& v2, const Value& v3) {
    int minVal = v1.val;
    if (v2.val < minVal) minVal = v2.val;
    if (v3.val < minVal) minVal = v3.val;
    return minVal;
}


int main() {
    Value v1(15), v2(8), v3(22);
    cout << "Min: " << minOfThree(v1, v2, v3) << endl; // 8
    return 0;
}
9)#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    double salary;
public:
    Employee(string n, double s) : name(n), salary(s) {}
    string getName() const { return name; }
    double getSalary() const { return salary; }
    
    friend string higherSalary(const Employee& e1, const Employee& e2);
};

string higherSalary(const Employee& e1, const Employee& e2) {
    if (e1.salary > e2.salary) {
        return e1.name + " is more";
    } else if (e2.salary > e1.salary) {
        return e2.name + " is more";
    } else {
        return "equal";
    }
}

int main() {
    Employee emp1("Анна", 50000);
    Employee emp2("Борис", 60000);
    cout << higherSalary(emp1, emp2) << endl;
    return 0;
}
10)
    #include <iostream>
using namespace std;

class Point {
private:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    friend double distance(const Point& p1, const Point& p2);
};

double distance(const Point& p1, const Point& p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main() {
    Point p1(1, 2), p2(4, 6);
    cout << "Расстояние: " << distance(p1, p2) << endl; // |4-1| + |6-2| = 7
    return 0;
}
11)
 #include <iostream>
using namespace std;

class Box {
private:
    int length, width, height;
public:
    Box(int l = 0, int w = 0, int h = 0)
        : length(l), width(w), height(h) {}
    
    void print() const {
        cout << "Box: " << length << "x" << width << "x" << height << endl;
    }
    
    friend Box operator+(const Box& b1, const Box& b2);
};

Box operator+(const Box& b1, const Box& b2) {
    return Box(b1.length + b2.length,
               b1.width + b2.width,
               b1.height + b2.height);
}

int main() {
    Box box1(2, 3, 4), box2(1, 1, 1);
    Box result = box1 + box2;
    result.print(); 
12)#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string username;
    int id;
public:
    User(string u = "", int i = 0) : username(u), id(i) {}
    
    friend bool operator==(const User& u1, const User& u2);
};

bool operator==(const User& u1, const User& u2) {
    return (u1.username == u2.username) && (u1.id == u2.id);
}

int main() {
    User user1("alice", 101), user2("alice", 101);
    if (user1 == user2) {
        cout << "simmilar" << endl;
    } else {
        cout << "aren't similar" << endl;
    }
    return 0;
}
13)
    #include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    double price;
public:
    Product(string n = "Unknown", double p = 0.0) : name(n), price(p) {}
    
    friend ostream& operator<<(ostream& os, const Product& p);
};

ostream& operator<<(ostream& os, const Product& p) {
    os << "Product: " << p.name << ", Price: $" << p.price;
    return os;
}

int main() {
    Product p1("Laptop", 999.99);
    cout << p1 << endl; 
    return 0;
}
14)
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    double gpa;
public:
    Student(string n = "", int a = 0, double g = 0.0)
        : name(n), age(a), gpa(g) {}
    
    void print() const {
        cout << "Student: " << name << ", Age: " << age
             << ", GPA: " << gpa << endl;
    }
    
    friend istream& operator>>(istream& is, Student& s);
};

istream& operator>>(istream& is, Student& s) {
    cout << "Введите имя: ";
    getline(is, s.name);
    cout << "Введите возраст: ";
    is >> s.age;
    cout << "Введите GPA: ";
    is >> s.gpa;
    is.ignore(); // очистка буфера
    return is;
}

int main() {
    Student s;
    cin >> s;
    s.print();
    return 0;
}
15)
    #include <iostream>
using namespace std;

class Score {
private:
    int value;
public:
    Score(int v = 0) : value(v) {}
    int getValue() const { return value; }
    
    friend Score maxOfThree(const Score& s1, const Score& s2, const Score& s3);
};

Score maxOfThree(const Score& s1, const Score& s2, const Score& s3) {
    Score maxScore = s1;
    if (s2.value > maxScore.value) maxScore = s2;
    if (s3.value > maxScore.value) maxScore = s3;
    return maxScore;
}

int main() {
    Score s1(85), s2(92), s3(78);
    Score maxScore = maxOfThree(s1, s2, s3);
    cout << "Max coints: " << maxScore.getValue() << endl; // 92
    return 0;
}
16)
    #include <iostream>
#include <vector>
using namespace std;

class Database {
private:
    vector<string> data;
    string password;
public:
    Database(string pwd) : password(pwd) {}
    void addData(string item) { data.push_back(item); }
    
    friend class Admin;
};

class Admin {
public:
    void showData(const Database& db) {
        cout << "Данные базы:" << endl;
        for (const auto& item : db.data) {
            cout << "- " << item << endl;
        }
        cout << "Password: " << db.password << endl;
    }
};
int main() {
    Database db("secret123");
    db.addData("User1");
    db.addData("User2");
    
    Admin admin;
    admin.showData(db);
    return 0;
}

17)
    #include <iostream>
#include <vector>
#include <string>
using namespace std;

class System {
private:
    vector<string> logs;
    int errorCount;
public:
    System() : errorCount(0) {}
    void logError(string message) {
        logs.push_back("ERROR: " + message);
        errorCount++;
    }
    
    friend class Logger;
};

class Logger {
public:
    void dumpLogs(const System& sys) {
        cout << "count of errors: " << sys.errorCount << endl;
        cout << "List of errors:" << endl;
        for (const auto& log : sys.logs) {
            cout << log << endl;
        }
    }

int main() {
    System sys;
    sys.logError("Connection error");
    sys.logError("timeout");
    
    Logger logger;
    logger.dumpLogs(sys);
    return 0;
}
18)
#include <iostream>
#include <string>
using namespace std;

class Student;

class Teacher {
public:
    void viewStudentData(const Student& student);
};

class Student {
private:
    string name;
    int grade;
    string major;
public:
    Student(string n, int g, string m)
        : name(n), grade(g), major(m) {}
    
    friend void Teacher::viewStudentData(const Student&);
};

void Teacher::viewStudentData(const Student& student) {
    cout << "Student: " << student.name << endl;
    cout << "Mark: " << student.grade << endl;
    cout << "Specialization: " << student.major << endl;
}

int main() {
    Student student("Ivan Ivonov", 5, "Math");
    Teacher teacher;
    teacher.viewStudentData(student);
    return 0;
}

19)
#include <iostream>
#include <string>
using namespace std;

class SecurityManager; 


class SecureData {
private:
    string confidentialInfo;
    int secretCode;
public:
    SecureData(string info, int code)
        : confidentialInfo(info), secretCode(code) {}
    
    friend class SecurityManager;
};

class SecurityManager {
public:
    void accessData(const SecureData& data) {
        cout << "Confidential information: " << data.confidentialInfo << endl;
        cout << "Secret code: " << data.secretCode << endl;
    }
    void modifyData(SecureData& data, string newInfo, int newCode) {
        data.confidentialInfo = newInfo;
        data.secretCode = newCode;
    }
};
int main() {
    SecureData data("Top Secret", 12345);
    SecurityManager manager;
    manager.accessData(data);
    manager.modifyData(data, "New Secret", 54321);

20)
    #include <iostream>
#include <string>
using namespace std;

class SecurityManager; 

class SecureData {
private:
    string confidentialInfo;
    int secretCode;
public:
    SecureData(string info, int code)
        : confidentialInfo(info), secretCode(code) {}
    
    friend class SecurityManager;
};

class SecurityManager {
public:
    void accessData(const SecureData& data) {
        cout << "Confidential information: " << data.confidentialInfo << endl;
        cout << "Secret code: " << data.secretCode << endl;
    }
    void modifyData(SecureData& data, string newInfo, int newCode) {
        data.confidentialInfo = newInfo;
        data.secretCode = newCode;
    }
};

int main() {
    SecureData data("Top Secret", 12345);
    SecurityManager manager;
    manager.accessData(data);
    manager.modifyData(data, "New Secret", 54321);


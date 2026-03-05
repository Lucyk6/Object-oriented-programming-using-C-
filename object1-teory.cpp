1) #include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    string name;
    int age;

    void displayInfo() 
    {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main()
{
    Student s1;         
    s1.name = "Ivan";   
    s1.age = 20;

    s1.displayInfo(); 

    return 0;
}
2) #include <iostream>
#include <string>
using namespace std;

class Person
{
private:
    string name;
    int age;

public:
    Person(string n, int a)
    {
        name = n;
        age = a;
    }

    void display()
    {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main()
{
    Person p1("Anna", 25);  
    p1.display();

    return 0;
}
 3)#include <iostream>
using namespace std;

class Car
{
private:
    int speed;

public:
    void setSpeed(int s)
    {
        if (s >= 0)
            speed = s;
        else
            cout << "Speed cannot be negative!" << endl;
    }

    int getSpeed()
    {
        return speed;
    }
};

int main()
{
    Car car1;
    car1.setSpeed(100);         
    cout << "Car speed: " << car1.getSpeed() << endl;

    car1.setSpeed(-10);     


    return 0;
}
4) #include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    int age;

public:
    Person(string n, int a)
    {
        name = n;
        age = a;
    }

    void displayPerson()
    {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Employee : public Person
{
private:
    string position;

public:
    Employee(string n, int a, string p) : Person(n, a)
    {
        position = p;
    }

    void displayEmployee()
    {
        displayPerson(); 
        cout << "Position: " << position << endl;
    }
};

int main()
{
    Employee e1("Alex", 30, "Developer");
    e1.displayEmployee();

    return 0;
}






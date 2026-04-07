#include <iostream>
using namespace std;
//1)
//class  Author {
//public:
//	void name() {
//		cout << "smth" << endl;
//	}
//};
//class Book {
//private:
//	Author* author;
//
//public:
//	Book(Author* a) {
//		author = a;
//	 }
//
//	void run() {
//		author->name();
//	}
//};
//int main()
//{
//	Author a;
//	Book b(&a);
//	b.run();
//}
// 2)
//class Furniture {
//public:
//	void chair() {
//
//		cout << "nice chair" << endl;
//
//	 }
//};
//class Room {
//
//private:
//
//	Furniture f;
//public:
//	void run() {
//		f.chair();
//	}
//};
//int main() {
//	Room r;
//	r.run();
// 
//}
//3)
//class Account {
//public:
//    Account(const string& userName) : username(userName) {}
//    void show() const { cout << "Account of user: " << username << endl; }
//private:
//    string username;
//};
//
//class User {
//public:
//    User(const string& name) : username(name), account(new Account(name)) {}
//    ~User() { delete account; }
//
//    void show() const {
//        cout << "User: " << username << endl;
//        account->show();
//    }
//private:
//    string username;
//    Account* account;
//};
//int main() {
//    User user1("Ivan");
//    User user2("jflsdfj");
//    user1.show();
//    user2.show();
//    return 0;
//}
//4)
//#include <vector>
//#include <string>
//using namespace std;
//
//class Teacher {
//public:
//    Teacher(const string& name) : teacherName(name) {}
//    void show() const { cout << "Teacher: " << teacherName << endl; }
//private:
//    string teacherName;
//};
//
//class School {
//public:
//    void addTeacher(const Teacher& t) { teachers.push_back(t); }
//    void showTeachers() const {
//        for (const auto& t : teachers) {
//            t.show();
//        }
//    }
//private:
//    vector<Teacher> teachers; 
//};
//int main() {
// 
//    School mySchool;
//
//    Teacher teacher1("Ilya aoaoao");
//    Teacher teacher2("Max zyev");
//    Teacher teacher3("Liza Mishenko");
//    mySchool.addTeacher(teacher1);
//    mySchool.addTeacher(teacher2);
//    mySchool.addTeacher(teacher3);
//
//    mySchool.showTeachers();
//    return 0;
//}
//5)
//#include <vector>
//#include <string>
//using namespace std;
//
//class Wheel {
//public:
//    Wheel(int size) : diameter(size) {}
//    void show() const { cout << "Wheel diameter: " << diameter << endl; }
//private:
//    int diameter;
//};
//
//class Car {
//public:
//    Car(int numWheels, int wheelSize) {
//        for (int i = 0; i < numWheels; i++) {
//            wheels.push_back(Wheel(wheelSize));
//        }
//    }
//
//    void showWheels() const {
//        for (const auto& w : wheels) {
//            w.show();
//        }
//    }
//private:
//    vector<Wheel> wheels; 
//
//};
//int main() {
//    Car myCar(4, 16);
//    myCar.showWheels();
//    return 0;
//}

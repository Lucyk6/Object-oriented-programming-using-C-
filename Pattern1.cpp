#include <iostream>
using namespace std;
////1
//class Logger {
//private:
//    Logger()=default;
//
//public:
//    static Logger& getInstance() {
//        static Logger instance;  
//        return instance;
//    }
//
//    void log(string msg) {
//        cout << "LOG: " << msg << endl;
//    }
//    void print(const std::string& msg) {  //3
//        std::cout << "LOG: " << msg << std::endl;
//    }
//};
////2
//int main() {
//    Logger& logger1 = Logger::getInstance();
//    Logger& logger2 = Logger::getInstance();
//
//    cout << "Address of logger1: " << &logger1 << endl;
//    cout << "Address of logger2: " << &logger2 << endl;
//
//    if (&logger1 == &logger2) {
//        cout << "SUCCESS: Both references point to the same Logger object!" << endl;
//    }
//    else {
//        cout << "ERROR: References point to different objects!" << endl;
//    }
//
//    logger1.print("Test message from logger1");//3
//    logger2.log("Testik");
//
//    return 0;
//}
//
//4
//#include <iostream>
//using namespace std;
//
//class Counter
//{
//private:
//    int count;
//    Counter() : count(0) {}
//
//public:
//    static Counter& getInstance()
//    {
//        static Counter instance;
//        return instance;
//    }
//
//    void increment()
//    {
//        count++;
//    }
//
//    int getCount()
//    {
//        return count;
//    }
//};
//
//int main()
//{
//    Counter::getInstance().increment();
//    Counter::getInstance().increment();
//
//    cout << Counter::getInstance().getCount();
//}

//5
//
//class App
//{
//private:
//    string name;
//
//    App() : name("MyApp") {}
//
//public:
//    static App& getInstance()
//    {
//        static App instance;
//        return instance;
//    }
//
//    void print()
//    {
//        cout << name;
//    }
//};
//int main() 
//{
//    App& app = App::getInstance();
//    app.print();
//
//}
//6
//#include <iostream>
//using namespace std;
//
//class Config
//{
//private:
//    int volume;
//    Config() : volume(50) {}
//
//public:
//    static Config& getInstance()
//    {
//        static Config instance;
//        return instance;
//    }
//
//    void setVolume(int v)
//    {
//        if (v < 0) volume = 0;
//        else if (v > 100) volume = 100;
//        else volume = v;
//    }
//
//    int getVolume()
//    {
//        cout << "Enter volume (0-100): ";
//        cin >> volume; 
//        return volume;
//    }
//};
//
//int main()
//{   
//    cout << "Current volume: " << Config::getInstance().getVolume() << endl;
//
//    cout << "Saved volume: " << Config::getInstance().getVolume() << endl;
//   return 0;
//}
//7 
//class Config
//{
//private:
//    int volume;
//    Config() : volume(50) {}
//
//public:
//    static Config& getInstance()
//    {
//        static Config instance;
//        return instance;
//    }
//
//    void setVolume(int v)
//    {
//        volume = v;
//    }
//
//    int getVolume()
//    {
//        return volume;
//    }
//};
//
//int main()
//{
//    Config::getInstance().setVolume(80);
//
//    cout << Config::getInstance().getVolume();
//}
//8
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Logger {
private:
    Logger() = default;  
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance;  
        return instance;
    }

    void log(const string& message) {
        cout << "[LOG] " << message << endl;
    }
};

#define LOG(msg) Logger::getInstance().log(msg)

void processOrder() {
    LOG("Processing order started");
    LOG("Order processed successfully");
}

void updateUserProfile() {
    LOG("Updating user profile");
    LOG("Profile updated");
}

class DataManager {
private:
    map<string, int> data;
    DataManager() = default;

    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

public:
    static DataManager& getInstance() {
        static DataManager instance;
        return instance;
    }

    void setValue(const string& key, int value) {
        data[key] = value;
        LOG("DataManager: set " + key + " = " + to_string(value));
    }

    int getValue(const string& key) {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second;
        }
        LOG("DataManager: key '" + key + "' not found");
        return -1;
    }

    void printAll() {
        LOG("DataManager contents:");
        for (const auto& pair : data) {
            cout << "  " << pair.first << " = " << pair.second << endl;
        }
    }
};
class UserManager {
private:
    vector<string> users;
    UserManager() = default;

    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;

public:
    static UserManager& getInstance() {
        static UserManager instance;
        return instance;
    }

    void addUser(const string& username) {
        users.push_back(username);
        LOG("UserManager: user '" + username + "' added");
    }

    void printUsers() {
        LOG("UserManager: registered users (" + to_string(users.size()) + "):");
        for (size_t i = 0; i < users.size(); ++i) {
            cout << "  " << (i + 1) << ". " << users[i] << endl;
        }
    }
};
class ObjectCounter {
private:
    int count = 0;
    ObjectCounter() = default;

    ObjectCounter(const ObjectCounter&) = delete;
    ObjectCounter& operator=(const ObjectCounter&) = delete;

public:
    static ObjectCounter& getInstance() {
        static ObjectCounter instance;
        return instance;
    }

    void createObject() {
        ++count;
        LOG("ObjectCounter: object created. Total: " + to_string(count));
    }

    int getCount() const {
        return count;
    }
};

int main() {
    ///8-9
    LOG("Application started — демонстрация паттерна Logger");

    processOrder();
    updateUserProfile();

    LOG("Demonstration of logging from different functions completed\n");

    //10
    LOG("Testing DataManager (Singleton + Map)");

    DataManager::getInstance().setValue("users_count", 150);
    DataManager::getInstance().setValue("orders_count", 200);

    cout << "Users count: " << DataManager::getInstance().getValue("users_count") << endl;
    cout << "Orders count: " << DataManager::getInstance().getValue("revenue") << endl;  // Не существующий ключ

    DataManager::getInstance().printAll();
    cout << endl;

    // 14
    LOG("Testing UserManager (Singleton + Collection)");

    UserManager::getInstance().addUser("Alice");
    UserManager::getInstance().addUser("Bob");
    UserManager::getInstance().addUser("Charlie");

    UserManager::getInstance().printUsers();
    cout << endl;
//15
    LOG("Testing ObjectCounter (Singleton + Counter)");

    cout << "Initial object count: " << ObjectCounter::getInstance().getCount() << endl;

    ObjectCounter::getInstance().createObject();
    ObjectCounter::getInstance().createObject();

    for (int i = 0; i < 3; ++i) {
        ObjectCounter::getInstance().createObject();
    }

    cout << "Final object count: " << ObjectCounter::getInstance().getCount() << endl;
    cout << endl;

    LOG("Testing Singleton protection");

    LOG("All Singleton patterns work correctly!");

    return 0;
}

//1
#include <iostream>
class SubsystemA {
public:
    void operationA() { std::cout << "Subsystem A operation\n"; }
};

class SubsystemB {
public:
    void operationB() { std::cout << "Subsystem B operation\n"; }
};

class SubsystemC {
public:
    void operationC() { std::cout << "Subsystem C operation\n"; }
};

// Фасад
class SimpleFacade {
private:
    SubsystemA* subA;
    SubsystemB* subB;
    SubsystemC* subC;
public:
    SimpleFacade() : subA(new SubsystemA()), subB(new SubsystemB()), subC(new SubsystemC()) {}
    ~SimpleFacade() { delete subA; delete subB; delete subC; }
    
    void simpleOperation() {
        subA->operationA();
        subB->operationB();
        subC->operationC();
    }
};
//2
class SystemFacade {
private:
    SubsystemA a;
    SubsystemB b;
    SubsystemC c;
public:
    void start() {
        std::cout << "Starting system...\n";
        a.operationA();
        b.operationB();
        c.operationC();
        std::cout << "System ready!\n";
    }
};
//3
int main() {
    SubsystemA a;
    SubsystemB b;
    SubsystemC c;
    a.operationA();
    b.operationB();
    c.operationC();
    return 0;
}
//
int main() {
    SystemFacade facade;
    facade.start();
    return 0;
}
//4
void complexSequence() {
    SubsystemA a; a.operationA();
    SubsystemB b; b.operationB();
}

int main() {
    complexSequence(); 
    complexSequence(); 
    return 0;
}
class RepeatedFacade {
private:
    SubsystemA a;
    SubsystemB b;
public:
    void doComplexSequence() {
        a.operationA();
        b.operationB();
    }
};

int main() {
    RepeatedFacade facade;
    facade.doComplexSequence();
    facade.doComplexSequence();
    return 0;
}

//5
class ExtendedFacade : public SimpleFacade {
public:
    void shutdown() {
        std::cout << "Shutting down...\n";
    }
};
//6
class CPU {
public:
    void freeze() { std::cout << "CPU: freeze\n"; }
    void jump(long position) { std::cout << "CPU: jump to " << position << "\n"; }
    void execute() { std::cout << "CPU: execute\n"; }
};

class Memory {
public:
    void load(long position, char* data) {
        std::cout << "Memory: load data '" << data << "' at " << position << "\n";
    }
};

class Disk {
public:
    void read(long lba, int size) {
        std::cout << "Disk: read " << size << " bytes from LBA " << lba << "\n";
    }
};

class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    Disk disk;
public:
    void startComputer() {
        cpu.freeze();
        memory.load(0x1000, "data");
        cpu.jump(0x1000);
        cpu.execute();
        disk.read(0, 1024);
    }
};
//7
class Validator {
public:
    bool validateEmail(const std::string& email) {
        std::cout << "Validator: validating " << email << "\n";
        return true; 
    }
};

class Database {
public:
    void saveUser(const std::string& username, const std::string& email) {
        std::cout << "Database: saving user " << username << "\n";
    }
};

class EmailService {
public:
    void sendWelcomeEmail(const std::string& email) {
        std::cout << "EmailService: sending welcome email to " << email << "\n";
    }
};

class UserService {
private:
    Validator validator;
    Database db;
    EmailService emailService;
public:
    bool registerUser(const std::string& username, const std::string& email) {
        if (!validator.validateEmail(email)) return false;
        db.saveUser(username, email);
        emailService.sendWelcomeEmail(email);
        return true;
    }
};
//8
class Validator {
public:
    bool validateEmail(const std::string& email) {
        std::cout << "Validator: validating " << email << "\n";
        return true; // упрощённая проверка
    }
};

class Database {
public:
    void saveUser(const std::string& username, const std::string& email) {
        std::cout << "Database: saving user " << username << "\n";
    }
};

class EmailService {
public:
    void sendWelcomeEmail(const std::string& email) {
        std::cout << "EmailService: sending welcome email to " << email << "\n";
    }
};

class UserService {
private:
    Validator validator;
    Database db;
    EmailService emailService;
public:
    bool registerUser(const std::string& username, const std::string& email) {
        if (!validator.validateEmail(email)) return false;
        db.saveUser(username, email);
        emailService.sendWelcomeEmail(email);
        return true;
    }
};
//9
class TV {
public:
    void on() { std::cout << "TV is ON\n"; }
    void setChannel(int channel) { std::cout << "TV: channel " << channel << "\n"; }
};

class AudioSystem {
public:
    void on() { std::cout << "AudioSystem is ON\n"; }
    void setVolume(int level) { std::cout << "Audio: volume " << level << "\n"; }
};

class DVD {
public:
    void on() { std::cout << "DVD is ON\n"; }
    void play() { std::cout << "DVD: playing movie\n"; }
};

class HomeTheaterFacade {
private:
    TV tv;
    AudioSystem audio;
    DVD dvd;
public:
    void watchMovie() {
        tv.on();
        tv.setChannel(5);
        audio.on();
        audio.setVolume(20);
        dvd.on();
        dvd.play();
    }
    void endMovie() {
        dvd.off();
        audio.off();
        tv.off();
    }
};
//10
#include <fstream>

class LoggingFacade : public HomeTheaterFacade {
private:
    std::ofstream logFile;
public:
    LoggingFacade() { logFile.open("home_theater.log"); }
    ~LoggingFacade() { if (logFile.is_open()) logFile.close(); }
    
    void watchMovie() override {
        logFile << "INFO: Starting movie session\n";
        HomeTheaterFacade::watchMovie();
        logFile << "INFO: Movie session started\n";
    }
};
//11
class ParameterizedFacade {
private:
    UserService userService;
    EmailService emailService;
public:
    void registerUserWithWelcome(const std::string& username, const std::string& email) {
        std::cout << "Registering user: " << username << "\n";
        userService.registerUser(username, email);
        emailService.sendWelcomeEmail(email);
    }
};
//12
class ParameterizedFacade {
private:
    UserService userService;
    EmailService emailService;
public:
    void registerUserWithWelcome(const std::string& username, const std::string& email) {
        std::cout << "Registering user: " << username << "\n";
        userService.registerUser(username, email);
        emailService.sendWelcomeEmail(email);
    }
};
//13
class ComplexHidingFacade {
private:
    std::vector<std::string> cache;
    int retryCount = 3;
public:
    bool processData(const std::string& data) {
        if (cache.size() > 100) {
            cache.clear();
            std::cout << "Cache cleared\n";
        }
        
        for (int i = 0; i < retryCount; ++i) {
            if (tryProcess(data)) {
                cache.push_back(data);
                return true;
            }
        }
        return false;
    }
private:
    bool tryProcess(const std::string& data) {
        std::cout << "Processing: " << data << " (attempt)\n";
        return true; 
    }
};
//14
class ErrorHandlingFacade {
private:
    Database db;
    Validator validator;
public:
    bool safeRegisterUser(const std::string& username, const std::string& email) {
        try {
            if (username.empty() || email.empty()) {
                throw std::invalid_argument("Username and email cannot be empty");
            }
            
            if (!validator.validateEmail(email)) {
                std::cout << "Invalid email format\n";
                return false;
            }
            
            db.saveUser(username, email);
            std::cout << "User registered successfully\n";
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return false;
        }
    }
};
//15
class AdminFacade {
private:
    Database db;
    EmailService emailService;
public:
    void createUserWithNotification(const std::string& username, const std::string& email) {
        db.saveUser(username, email);
        emailService.sendWelcomeEmail(email);
        std::cout << "Admin: User created with notification\n";
    }
};

class UserFacade {
private:
    EmailService emailService;
public:
    void changeEmail(const std::string& newEmail) {
        emailService.sendConfirmationEmail(newEmail);
        std::cout << "User: Email change initiated\n";
    }
};
//16
class OldPaymentSystem {
public:
    void makePayment(double amount, const std::string& currency) {
        std::cout << "Old system: payment of " << amount << " " << currency << "\n";
    }
};

class PaymentAdapter {
private:
    OldPaymentSystem oldSystem;
public:
    void processPayment(double amount) {
        oldSystem.makePayment(amount, "USD");
    }
};

class ModernFacade {
private:
    PaymentAdapter paymentAdapter;
    AuthService auth;
public:
    bool makePurchase(double amount) {
        if (!auth.isAuthenticated()) {
            return false;
        }
        paymentAdapter.processPayment(amount);
        return true;
    }
};
//17
class OldPaymentSystem {
public:
    void makePayment(double amount, const std::string& currency) {
        std::cout << "Old system: payment of " << amount << " " << currency << "\n";
    }
};

class PaymentAdapter {
private:
    OldPaymentSystem oldSystem;
public:
    void processPayment(double amount) {
        oldSystem.makePayment(amount, "USD");
    }
};

class ModernFacade {
private:
    PaymentAdapter paymentAdapter;
    AuthService auth;
public:
    bool makePurchase(double amount) {
        if (!auth.isAuthenticated()) {
            return false;
        }
        paymentAdapter.processPayment(amount);
        return true;
    }
};
//18
class OldPaymentSystem {
public:
    void makePayment(double amount, const std::string& currency) {
        std::cout << "Old system: payment of " << amount << " " << currency << "\n";
    }
};
class PaymentAdapter {
private:
    OldPaymentSystem oldSystem;
public:
    void processPayment(double amount) {
        oldSystem.makePayment(amount, "USD");
    }
};

class ModernFacade {
private:
    PaymentAdapter paymentAdapter;
    AuthService auth;
public:
    bool makePurchase(double amount) {
        if (!auth.isAuthenticated()) {
            return false;
        }
        paymentAdapter.processPayment(amount);
        return true;
    }
};
//19
#include <vector>
#include <algorithm>

class VectorFacade {
private:
    std::vector<int> data;
public:
    void addElements(const std::vector<int>& elements) {
        data.insert(data.end(), elements.begin(), elements.end());
    }
    
    void sortAscending() {
        std::sort(data.begin(), data.end());
    }
    
    void removeDuplicates() {
        auto last = std::unique(data.begin(), data.end());
        data.erase(last, data.end());
    }
    
    void printAll() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
};

VectorFacade facade;
facade.addElements({3, 1, 4, 1, 5});
facade.sortAscending();
facade.removeDuplicates();
facade.printAll(); 
//20
class AuthService {
public:
    bool authenticate(const std::string& token) {
        std::cout << "Auth: authenticating token " << token << "\n";
        return !token.empty();
    }
};

class PaymentService {
public:
    bool processPayment(double amount) {
        std::cout << "Payment: processing " << amount << " USD\n";
        return amount > 0;
    }
};

class NotificationService {
public:
    void sendOrderConfirmation(const std::string& email) {
        std::cout << "Notification: sending confirmation to " << email << "\n";
    }
};

class OrderFacade {
private:
    AuthService auth;
    PaymentService payment;
    NotificationService notification;
public:
    bool placeOrder(const std::string& userToken,
                   double amount,



#include <iostream>
#include <string>
#include <stdexcept>

class Character {
private:
    std::string name;
    std::string characterClass;
    int health;
    int mana;
    int strength;
    int agility;
    int intelligence;
    std::string weapon;
    std::string armor;

    Character() = default; 

    friend class CharacterBuilder;
public:
    void print() const {
        std::cout << "Character: " << name << " (" << characterClass << ")\n";
        std::cout << "HP: " << health << ", Mana: " << mana << "\n";
        std::cout << "Str: " << strength << ", Agi: " << agility << ", Int: " << intelligence << "\n";
        std::cout << "Weapon: " << weapon << ", Armor: " << armor << "\n";
    }
};

class CharacterBuilder {
private:
    Character character;
public:
    CharacterBuilder() {
        // Значения по умолчанию
        character.health = 100;
        character.mana = 50;
        character.strength = 10;
        character.agility = 10;
        character.intelligence = 10;
    }

    CharacterBuilder& setName(const std::string& n) {
        character.name = n;
        return *this;
    }

    CharacterBuilder& setClass(const std::string& c) {
        character.characterClass = c;
        return *this;
    }

    CharacterBuilder& setHealth(int h) {
        character.health = h;
        return *this;
    }

    CharacterBuilder& setMana(int m) {
        character.mana = m;
        return *this;
    }

    CharacterBuilder& setStrength(int s) {
        character.strength = s;
        return *this;
    }

    CharacterBuilder& setAgility(int a) {
        character.agility = a;
        return *this;
    }

    CharacterBuilder& setIntelligence(int i) {
        character.intelligence = i;
        return *this;
    }

    CharacterBuilder& setWeapon(const std::string& w) {
        character.weapon = w;
        return *this;
    }

    CharacterBuilder& setArmor(const std::string& a) {
        character.armor = a;
        return *this;
    }

    Character build() {
        if (character.name.empty()) {
            throw std::invalid_argument("Character name cannot be empty");
        }
        if (character.health <= 0) {
            throw std::invalid_argument("Health must be greater than 0");
        }
        return character;
    }
};

int main() {
    try {
        Character warrior = CharacterBuilder()
            .setName("Aragorn")
            .setClass("Warrior")
            .setHealth(150)
            .setStrength(25)
            .setWeapon("Long Sword")
            .setArmor("Chain Mail")
            .build();

        warrior.print();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
  
    return 0;
}
//2
#include <vector>

class Order {
private:
    std::string customerName;
    std::vector<std::string> products;
    std::string deliveryMethod;
    std::string promoCode;
    bool giftWrapping;
    std::string comment;

    friend class OrderBuilder;
public:
    void printOrder() const {
        std::cout << "Order for: " << customerName << "\n";
        std::cout << "Products: ";
        for (const auto& product : products) {
            std::cout << product << " ";
        }
        std::cout << "\nDelivery: " << deliveryMethod;
        if (!promoCode.empty()) std::cout << ", Promo: " << promoCode;
        if (giftWrapping) std::cout << ", Gift wrapping";
        if (!comment.empty()) std::cout << ", Comment: " << comment;
        std::cout << "\n";
    }
};

class OrderBuilder {
private:
    Order order;
public:
    OrderBuilder& setCustomerName(const std::string& name) {
        order.customerName = name;
        return *this;
    }

    OrderBuilder& addProduct(const std::string& product) {
        order.products.push_back(product);
        return *this;
    }

    OrderBuilder& setDeliveryMethod(const std::string& method) {
        order.deliveryMethod = method;
        return *this;
    }

    OrderBuilder& setPromoCode(const std::string& code) {
        order.promoCode = code;
        return *this;
    }

    OrderBuilder& enableGiftWrapping() {
        order.giftWr-wrapping = true;
        return *this;
    }

    OrderBuilder& setComment(const std::string& comment) {
        order.comment = comment;
        return *this;
    }

    Order build() {
        if (order.products.empty()) {
            throw std::invalid_argument("Order must have at least one product");
        }
        return order;
    }
};
//3
#include <map>

class HttpRequest {
private:
    std::string method;
    std::string url;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> params;
    std::string body;

    friend class HttpRequestBuilder;
public:
    void printRequest() const {
        std::cout << method << " " << url << "\n";
        for (const auto& [key, value] : headers) {
            std::cout << key << ": " << value << "\n";
        }
        if (!params.empty()) {
            std::cout << "Params: ";
            for (const auto& [key, value] : params) {
                std::cout << key << "=" << value << "&";
            }
            std::cout << "\n";
        }
        if (!body.empty()) {
            std::cout << "Body: " << body << "\n";
        }
    }
};

class HttpRequestBuilder {
private:
    HttpRequest request;
public:
    RequestBuilder& setMethod(const std::string& m) {
        request.method = m;
        return *this;
    }

    RequestBuilder& setUrl(const std::string& u) {
        request.url = u;
        return *this;
    }

    RequestBuilder& addHeader(const std::string& key, const std::string& value) {
        request.headers[key] = value;
        return *this;
    }

    RequestBuilder& addParam(const std::string& key, const std::string& value) {
        request.params[key] = value;
        return *this;
    }

    RequestBuilder& setBody(const std::string& b) {
        request.body = b;
        return *this;
    }

    HttpRequest build() {
        if (request.url.empty()) {
            throw std::invalid_argument("URL cannot be empty");
        }
        return request;
    }
};
//4
class DatabaseConfig {
private:
    std::string host;
    int port;
    std::string login;
    std::string password;
    std::string databaseName;
    bool useSSL;
    int timeout;

    friend class DatabaseConfigBuilder;
public:
    void printConfig() const {
        std::cout << "Host: " << host << ":" << port << "\n";
        std::cout << "Login: " << login << ", DB: " << databaseName << "\n";
        std::cout << "SSL: " << (useSSL ? "enabled" : "disabled") << ", Timeout: " << timeout << "s\n";
        if (password.empty()) {
            std::cout        << "Warning: Password is empty!\n";
    }
}

class DatabaseConfigBuilder {
private:
    DatabaseConfig config;
public:
    DatabaseConfigBuilder() {
        // Значения по умолчанию
        config.host = "localhost";
        config.port = 5432;
        config.login = "admin";
        config.password = "";
        config.databaseName = "default_db";
        config.useSSL = false;
        config.timeout = 30;
    }

    DatabaseConfigBuilder& setHost(const std::string& h) {
        config.host = h;
        return *this;
    }

    DatabaseConfigBuilder& setPort(int p) {
        if (p < 1 || p > 65535) {
            throw std::invalid_argument("Port must be between 1 and 65535");
        }
        config.port = p;
        return *this;
    }

    DatabaseConfigBuilder& setLogin(const std::string& l) {
        config.login = l;
        return *this;
    }

    DatabaseConfigBuilder& setPassword(const std::string& p) {
        config.password = p;
        return *this;
    }

    DatabaseConfigBuilder& setDatabaseName(const std::string& db) {
        config.databaseName = db;
        return *this;
    }

    DatabaseConfigBuilder& enableSSL() {
        config.useSSL = true;
        return *this;
    }

    DatabaseConfigBuilder& setTimeout(int t) {
        config.timeout = t;
        return *this;
    }

    DatabaseConfig build() {
        if (config.password.empty()) {
            std::cout << "Warning: Database password is not set!\n";
        }
        return config;
    }
};

// Использование
int main() {
    try {
        DatabaseConfig config = DatabaseConfigBuilder()
            .setHost("db.example.com")
            .setPort(5432)
            .setLogin("user123")
            .setPassword("secure_pass")
            .setDatabaseName("myapp_db")
            .enableSSL()
            .setTimeout(60)
            .build();

        config.printConfig();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
//5
class Query {
private:
    std::string selectClause;
    std::string fromClause;
    std::string whereClause;
    std::string orderByClause;
    int limitValue;
    bool hasSelect = false;
    bool hasFrom = false;

    friend class QueryBuilder;
public:
    std::string toString() const {
        std::string query = "SELECT " + selectClause + " FROM " + fromClause;
        if (!whereClause.empty()) query += " WHERE " + whereClause;
        if (!orderByClause.empty()) query += " ORDER BY " + orderByClause;
        if (limitValue > 0) query += " LIMIT " + std::to_string(limitValue);
        return query + ";";
    }
};

class QueryBuilder {
private:
    Query query;
public:
    QueryBuilder& select(const std::string& fields) {
        query.selectClause = fields;
        query.hasSelect = true;
        return *this;
    }

    QueryBuilder& from(const std::string& table) {
        query.fromClause = table;
        query.hasFrom = true;
        return *this;
    }

    QueryBuilder& where(const std::string& condition) {
        query.whereClause = condition;
        return *this;
    }

    QueryBuilder& orderBy(const std::string& field) {
        query.orderByClause = field;
        return *this;
    }

    QueryBuilder& limit(int count) {
        query.limitValue = count;
        return *this;
    }

    Query build() {
        if (!query.hasSelect) {
            throw std::invalid_argument("SELECT clause is required");
        }
        if (!query.hasFrom) {
            throw std::invalid_argument("FROM clause is required");
        }
        return query;
    }
};

int main() {
    try {
        Query q = QueryBuilder()
            .select("name, age")
            .from("Users")
            .where("age > 18")
            .orderBy("name")
            .limit(10)
            .build();

        std::cout << q.toString() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
//6
#include <memory>

class Computer {
private:
    std::string cpu;
    std::string gpu;
    std::string ram;
    std::string ssd;
    std::string hdd;
    bool wifi;
    bool bluetooth;
    bool waterCooling;

    friend class ComputerBuilder;
public:
    void printConfig() const {
        std::cout << "Computer Configuration:\n";
        std::cout << "CPU: " << cpu << "\n";
        std::cout << "GPU: " << gpu << "\n";
        std::cout << "RAM: " << ram << "\n";
        std::cout << "SSD: " << ssd << "\n";
        std::cout << "HDD: " << hdd << "\n";
        std::cout << "Wi‑Fi: " << (wifi ? "Yes" : "No") << "\n";
        std::cout << "Bluetooth: " << (bluetooth ? "Yes" : "No") << "\n";
        std::cout << "Water Cooling: " << (waterCooling ? "Yes" : "No") << "\n\n";
    }
};

class ComputerBuilder {
private:
    Computer computer;
public:
    ComputerBuilder& setCPU(const std::string& c) {
        computer.cpu = c;
        return *this;
    }

    ComputerBuilder& setGPU(const std::string& g) {
        computer.gpu = g;
        return *this;
    }

    ComputerBuilder& setRAM(const std::string& r) {
        computer.ram = r;
        return *this;
    }

    ComputerBuilder& setSSD(const std::string& s) {
        computer.ssd = s;
        return *this;
    }

    ComputerBuilder& setHDD(const std::string& h) {
        computer.hdd = h;
        return *this;
    }

    ComputerBuilder& enableWiFi() {
        computer.wifi = true;
        return *this;
    }

    ComputerBuilder& enableBluetooth() {
        computer.bluetooth = true;
        return *this;
    }

    ComputerBuilder& enableWaterCooling() {
        computer.waterCooling = true;
        return *this;
    }

    Computer build() { return computer; }
};

class ComputerDirector {
public:
    static Computer buildOfficePC() {
        return ComputerBuilder()
            .setCPU("Intel Core i3")
            .setGPU("Integrated")
            .setRAM("8GB")
            .setSSD("256GB")
            .setHDD("1TB")
            .enableWiFi()
            .enableBluetooth()
            .build();
    }

    static Computer buildGamingPC() {
        return ComputerBuilder()
            .setCPU("AMD Ryzen 7")
            .setGPU("NVIDIA RTX 4080")
            .setRAM("32GB")
            .setSSD("1TB NVMe")
            .setHDD("2TB")
            .enableWiFi()
            .enableBluetooth()
            .enableWaterCooling()
            .build();
    }

    static Computer buildServer() {
        return ComputerBuilder()
            .setCPU("Dual Xeon")
            .setGPU("None")
            .setRAM("128GB")
            .setSSD("4TB NVMe RAID")
            .setHDD("8TB RAID")
            .enableWiFi(false)
            .enableBluetooth(false) 
            .build();
    }
};

int main() {
    Computer officePC = ComputerDirector::buildOfficePC();
    Computer gamingPC = ComputerDirector::buildGamingPC();
    Computer server = ComputerDirector::buildServer();

    officePC.printConfig();
    gamingPC.printConfig();
    server.printConfig();

    return 0;
}
//7
class UserProfile {
private:
    std::string login;
    std::string email;
    std::string phone;
    std::string city;
    int age;
    std::string role;
    bool isVerified;

    friend class UserProfileBuilder;
public:
    void printProfile() const {
        std::cout << "User Profile:\n";
        std::cout << "Login: " << login << "\n";
        std::cout << "Email: " << email << "\n";
        if (!phone.empty()) std::cout << "Phone: " << phone << "\n";
        if (!city.empty()) std::cout << "City: " << city << "\n";
        if (age > 0) std::cout << "Age: " << age << "\n";
        std::cout << "Role: " << role << "\n";
        std::cout << "Verified: " << (isVerified ? "Yes" : "No") << "\n\n";
    }
};

class UserProfileBuilder {
private:
    UserProfile profile;
public:
    UserProfileBuilder() {
        profile.role = "user";
        profile.isVerified = false;
    }

    UserProfileBuilder& setLogin(const std::string& l) {
        profile.login = l;
        return *this;
    }

    UserProfileBuilder& setEmail(const std::string& e) {
        profile.email = e;
        return *this;
    }

    UserProfileBuilder& setPhone(const std::string& p) {
        profile.phone = p;
        return *this;
    }

    UserProfileBuilder& setCity(const std::string& c) {
        profile.city = c;
        return *this;
    }

    UserProfileBuilder& setAge(int a) {
        profile.age = a;
        return *this;
    }

    UserProfileBuilder& setRole(const std::string& r) {
        profile.role = r;
        return *this;
    }

    UserProfileBuilder& verify() {
        profile.isVerified = true;
        return *this;
    }

    UserProfile build() {
        if (profile.email.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email format: missing @");
        }
        if (profile.login.empty()) {
            throw std::invalid_argument("Login cannot be empty");
        }
        return profile;
    }
};
//8
#include <vector>

class GameLevel {
private:
    std::string name;
    std::string difficulty;
    std::vector<std::string> enemies;
    std::vector<std::string> items;
    bool hasBoss;
    std::string weatherEffect;

    friend class GameLevelBuilder;
public:
    void printLevel() const {
        std::cout << "Level: " << name << " (" << difficulty << ")\n";
        std::cout << "Enemies: ";
        for (const auto& enemy : enemies) {
            std::cout << enemy << " ";
        }
        std::cout << "\nItems: ";
        for (const auto& item : items) {
            std::cout << item << " ";
        }
        std::cout << "\nBoss: " << (hasBoss ? "Yes" : "No");
        if (!weatherEffect.empty()) {
            std::cout << ", Weather: " << weatherEffect;
        }
        std::cout << "\n\n";
    }
};

class GameLevelBuilder {
private:
    GameLevel level;
public:
    GameLevelBuilder& setName(const std::string& n) {
        level.name = n;
        return *this;
    }

    GameLevelBuilder& setDifficulty(const std::string& d) {
        level.difficulty = d;
        return *this;
    }

    GameLevelBuilder& addEnemy(const std::string& enemy) {
        level.enemies.push_back(enemy);
        return *this;
    }

    GameLevelBuilder& addItem(const std::string& item) {
        level.items.push_back(item);
        return *this;
    }

    GameLevelBuilder& enableBoss() {
        level.hasBoss = true;
        return *this;
    }

    GameLevelBuilder& setWeatherEffect(const std::string& weather) {
        level.weatherEffect = weather;
        return *this;
    }

    GameLevel build() {
        if (level.name.empty()) {
            throw std::invalid_argument("Level name cannot be empty");
        }
        return level;
    }
};
//9
enum class NotificationChannel {
    EMAIL,
    SMS,
    PUSH
};

class Notification {
private:
    std::string recipient;
    std::string title;
    std::string text;
    NotificationChannel channel;
    int priority;
    bool requiresConfirmation;

    friend class NotificationBuilder;
public:
    void send() const {
        std::string channelStr;
        switch (channel) {
            case NotificationChannel::EMAIL: channelStr = "Email"; break;
            case NotificationChannel::SMS: channelStr = "SMS"; break;
            case NotificationChannel::PUSH: channelStr = "Push"; break;
        }

        std::cout << "Sending notification to: " << recipient << "\n";
        std::cout << "Channel: " << channelStr << " (Priority: " << priority << ")\n";
        std::cout << "Title: " << title << "\n";
        std::cout << "Text: " << text << "\n";
        std::cout << "Confirmation required: " << (requiresConfirmation ? "Yes" : "No") << "\n\n";
    }
};

class NotificationBuilder {
private:
    Notification notification;
public:
    NotificationBuilder& setRecipient(const std::string& r) {
        notification.recipient = r;
        return *this;
    }

    NotificationBuilder& setTitle(const std::string& t) {
        notification.title = t;
        return *this;
    }

    NotificationBuilder& setText(const std::string& t) {
        notification.text = t;
        return *this;
    }

    NotificationBuilder& setChannel(NotificationChannel c) {
        notification.channel = c;
        return *this;
    }

    NotificationBuilder& setPriority(int p) {
        notification.priority = p;
        return *this;
    }

    NotificationBuilder& requireConfirmation() {
        notification.requiresConfirmation = true;
        return *this;
    }

    Notification build() {
        if (notification.recipient.empty()) {
            throw std::invalid_argument("Recipient cannot be empty");
        }
        if (notification.text.empty()) {
            throw std::invalid_argument("Notification text cannot be empty");
        }
        return notification;
    }
};
//10
#include <iostream>
#include <string>

class Order {
private:
    std::string customerName;
    std::vector<std::string> products;
    std::string deliveryMethod;
    double totalAmount;

    friend class OrderBuilder;
public:
    void printOrder() const {
        std::cout << "Order for: " << customerName << "\n";
        std::cout << "Products: ";
        for (const auto& product : products) {
            std::cout << product << " ";
        }
        std::cout << "\nDelivery: " << deliveryMethod << "\n";
        std::cout << "Total: $" << totalAmount << "\n\n";
    }

    double getTotal() const { return totalAmount; }
    const std::string& getCustomerName() const { return customerName; }
};

class OrderBuilder {
private:
    Order order;
public:
    OrderBuilder& setCustomerName(const std::string& name) {
        order.customerName = name;
        return *this;
    }

    OrderBuilder& addProduct(const std::string& product, double price) {
        order.products.push_back(product);
        order.totalAmount += price;
        return *this;
    }

    OrderBuilder& setDeliveryMethod(const std::string& method) {
        order.deliveryMethod = method;
        return *this;
    }

    Order build() {
        if (order.products.empty()) {
            throw std::invalid_argument("Order must have at least one product");
        }
        return order;
    }
};

class PaymentService {
public:
    static bool processPayment(const Order& order) {
        std::cout << "Processing payment of $" << order.getTotal() << " for " << order.getCustomerName() << "\n";
        return true; // Успешная оплата
    }
};

class DeliveryService {
public:
    static void arrangeDelivery(const Order& order) {
        std::cout << "Arranging delivery via " << order.deliveryMethod << " for " << order.getCustomerName() << "\n";
    }
};

class NotificationService {
public:
    static void sendConfirmation(const Order& order) {
        std::cout << "Sending order confirmation to " << order.getCustomerName() << "\n";
    }
};

class OrderFacade {
public:
    void placeOrder(const Order& order) {
        order.printOrder();

        if (PaymentService::processPayment(order)) {
            DeliveryService::arrangeDelivery(order);
            NotificationService::sendConfirmation(order);
            std::cout << "Order successfully placed!\n\n";
        } else {
            std::cout << "Order failed!\n\n";
        }
    }
};
int main() {
    OrderFacade facade;

    Order order = OrderBuilder()
        .setCustomerName("John Doe")
        .addProduct("Laptop", 999.99)
        .addProduct("Mouse", 25.50)
        .setDeliveryMethod("Express Courier")
        .build();

    facade.placeOrder(order);
    return 0;
}
//11
#include <iostream>
#include <string>

class Order {
private:
    std::string customerName;
    std::vector<std::string> products;
    std::string deliveryMethod;
    double totalAmount;

    friend class OrderBuilder;
public:
    void printOrder() const {
        std::cout << "Order for: " << customerName << "\n";
        std::cout << "Products: ";
        for (const auto& product : products) {
            std::cout << product << " ";
        }
        std::cout << "\nDelivery: " << deliveryMethod << "\n";
        std::cout << "Total: $" << totalAmount << "\n\n";
    }

    double getTotal() const { return totalAmount; }
    const std::string& getCustomerName() const { return customerName; }
};

class OrderBuilder {
private:
    Order order;
public:
    OrderBuilder& setCustomerName(const std::string& name) {
        order.customerName = name;
        return *this;
    }

    OrderBuilder& addProduct(const std::string& product, double price) {
        order.products.push_back(product);
        order.totalAmount += price;
        return *this;
    }

    OrderBuilder& setDeliveryMethod(const std::string& method) {
        order.deliveryMethod = method;
        return *this;
    }

    Order build() {
        if (order.products.empty()) {
            throw std::invalid_argument("Order must have at least one product");
        }
        return order;
    }
};

class PaymentService {
public:
    static bool processPayment(const Order& order) {
        std::cout << "Processing payment of $" << order.getTotal() << " for " << order.getCustomerName() << "\n";
        return true; // Успешная оплата
    }
};

class DeliveryService {
public:
    static void arrangeDelivery(const Order& order) {
        std::cout << "Arranging delivery via " << order.deliveryMethod << " for " << order.getCustomerName() << "\n";
    }
};

class NotificationService {
public:
    static void sendConfirmation(const Order& order) {
        std::cout << "Sending order confirmation to " << order.getCustomerName() << "\n";
    }
};

class OrderFacade {
public:
    void placeOrder(const Order& order) {
        order.printOrder();

        if (PaymentService::processPayment(order)) {
            DeliveryService::arrangeDelivery(order);
            NotificationService::sendConfirmation(order);
            std::cout << "Order successfully placed!\n\n";
        } else {
            std::cout << "Order failed!\n\n";
        }
    }
};

int main() {
    OrderFacade facade;

    Order order = OrderBuilder()
        .setCustomerName("John Doe")
        .addProduct("Laptop", 999.99)
        .addProduct("Mouse", 25.50)
        .setDeliveryMethod("Express Courier")
        .build();

    facade.placeOrder(order);
    return 0;
}
//12
class Character {
private:
    std::string name;
    std::string characterClass;
    int health;
    std::string weapon;

    friend class CharacterBuilder;
public:
    Character clone() const {
        return *this; // Простое копирование (мелкое)
    }

    void print() const {
        std::cout << "Character: " << name << " (" << characterClass << ")\n";
        std::cout << "HP: " << health << ", Weapon: " << weapon << "\n\n";
    }
};

class CharacterBuilder {
private:
    Character character;
public:
    CharacterBuilder& setName(const std::string& n) {
        character.name = n;
        return *this;
    }

    CharacterBuilder& setClass(const std::string& c) {
        character.characterClass = c;
        return *this;
    }

    CharacterBuilder& setHealth(int h) {
        character.health = h;
        return *this;
    }

    CharacterBuilder& setWeapon(const std::string& w) {
        character.weapon = w;
        return *this;
    }

    Character build() { return character; }
};

int main() {

    Character warriorPrototype = CharacterBuilder()
        .setName("Warrior Prototype")
        .setClass("Warrior")
        .setHealth(150)
        .setWeapon("Sword")
        .build();

    Character warrior1 = warriorPrototype.clone();
    warrior1.setName("Aragorn");
    warrior1.setWeapon("Elven Sword");

    Character warrior2 = warriorPrototype.clone();
    warrior2.setName("Boromir");
    warrior2.setWeapon("Shield and Sword");

    Character warrior3 = warriorPrototype.clone();
    warrior3.setName("Legolas");
    warrior3.setWeapon("Bow");class Character {
private:
    std::string name;
    std::string characterClass;
    int health;
    std::string weapon;

    friend class CharacterBuilder;
public:
    Character clone() const {
        return *this; // Простое копирование (мелкое)
    }

    void print() const {
        std::cout << "Character: " << name << " (" << characterClass << ")\n";
        std::cout << "HP: " << health << ", Weapon: " << weapon << "\n\n";
    }
};

class CharacterBuilder {
private:
    Character character;
public:
    CharacterBuilder& setName(const std::string& n) {
        character.name = n;
        return *this;
    }

    CharacterBuilder& setClass(const std::string& c) {
        character.characterClass = c;
        return *this;
    }

    CharacterBuilder& setHealth(int h) {
        character.health = h;
        return *this;
    }

    CharacterBuilder& setWeapon(const std::string& w) {
        character.weapon = w;
        return *this;
    }

    Character build() { return character; }
};
int main() {
    Character warriorPrototype = CharacterBuilder()
        .setName("Warrior Prototype")
        .setClass("Warrior")
        .setHealth(150)
        .setWeapon("Sword")
        .build();

    Character warrior1 = warriorPrototype.clone();
    warrior1.setName("Aragorn");
    warrior1.setWeapon("Elven Sword");

    Character warrior2 = warriorPrototype.clone();
    warrior2.setName("Boromir");
    warrior2.setWeapon("Shield and Sword");

    Character warrior3 = warriorPrototype.clone();
    warrior3.setName("Legolas");
    warrior3.setWeapon("Bow");
    warrior1.print();
    warrior2.print();
    warrior3.print();

    return 0;
}
//13
#include <stdexcept>
#include <regex>

// Кастомные исключения
class InvalidEmailException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid email format";
    }
};

class EmptyNameException : public std::exception {
    const char* what() const noexcept override {
        return "Name cannot be empty";
    }
};

class User {
private:
    std::string name;
    std::string email;
    int age;
    std::string phone;

    friend class UserBuilder;
public:
    void print() const {
        std::cout << "User: " << name << "\n";
        std::cout << "Email: " << email << "\n";
        std::cout << "Age: " << age << "\n";
        if (!phone.empty()) std::cout << "Phone: " << phone << "\n";
        std::cout << "\n";
    }
};

class UserBuilder {
private:
    User user;
public:
    UserBuilder& setName(const std::string& n) {
        if (n.empty()) throw EmptyNameException();
        user.name = n;
        return *this;
    }

    UserBuilder& setEmail(const std::string& e) {
        std::regex pattern(R"(\w+@\w+\.\w+)");
        if (!std::regex_match(e, pattern)) throw InvalidEmailException();
        user.email = e;
        return *this;
    }

    UserBuilder& setAge(int a) {
        if (a < 0 || a > 150) {
            throw std::invalid_argument("Age must be between 0 and 150");
        }
        user.age = a;
        return *this;
    }

    UserBuilder& setPhone(const std::string& p) {
        user.phone = p;
        return *this;
    }

    User build() {
        if (user.name.empty()) throw EmptyNameException();
        if (user.email.empty()) throw InvalidEmailException();
        return user;
    }
};

int main() {
    try {
        User user1 = UserBuilder()
            .setName("Alice")
            .setEmail("alice@example.com")
            .setAge(25)
            .setPhone("+1234567890")
            .build();
        user1.print();

        User user2 = UserBuilder()
            .setName("")
            .setEmail("invalid-email")
            .setAge(-5)
            .build();
        user2.print();
    } catch (const EmptyNameException& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
    } catch (const InvalidEmailException& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
    }
    return 0;
}
//14
class Config {
private:
    std::string server;
    int port;
    bool sslEnabled;
    int timeout;

    friend class ConfigBuilder;
public:
    void print() const {
        std::cout << "Config: " << server << ":" << port;
        std::cout << ", SSL: " << (sslEnabled ? "on" : "off");
        std::cout << ", Timeout: " << timeout << "s\n\n";
    }
};

class ConfigBuilder {
private:
    Config config;
public:
    ConfigBuilder& setServer(const std::string& s) {
        config.server = s;
        return *this;
    }

    ConfigBuilder& setPort(int p) {
        config.port = p;
        return *this;
    }

    ConfigBuilder& enableSSL() {
        config.sslEnabled = true;
        return *this;
    }

    ConfigBuilder& setTimeout(int t) {
        config.timeout = t;
        return *this;
    }

    template<typename Func>
    ConfigBuilder& configure(Func func) {
        func(*this);
        return *this;
    }

    Config build() { return config; }
};

int main() {
    auto commonConfig = [](ConfigBuilder& builder) {
        builder.setServer("localhost")
               .setPort(8080)
               .enableSSL();
    };

    Config devConfig = ConfigBuilder()
        .configure(commonConfig)
        .setTimeout(30)
        .build();

    Config prodConfig = ConfigBuilder()
        .configure(commonConfig)
        .setServer("prod.example.com")
        .setTimeout(60)
        .build();

    devConfig.print();
    prodConfig.print();
    return 0;
}
//15#include <vector>

class SQLQuery {
private:
    std::string selectClause;
    std::string fromClause;
    std::vector<std::string> joinClauses;
    std::string whereClause;
    std::string orderByClause;
    int limitValue;

    friend class SQLQueryBuilder;
public:
    std::string toString() const {
        std::string query = "SELECT " + selectClause + " FROM " + fromClause;

        for (const auto& join : joinClauses) {
            query += " " + join;
        }

        if (!whereClause.empty()) query += " WHERE " + whereClause;
        if (!orderByClause.empty()) query += " ORDER BY " + orderByClause;
        if (limitValue > 0) query += " LIMIT " + std::to_string(limitValue);

        return query + ";";
    }
};

class SQLQueryBuilder {
private:
    SQLQuery query;
public:
    SQLQueryBuilder& select(const std::string& fields) {
        query.selectClause = fields;
        return *this;
    }

    SQLQueryBuilder& from(const std::string& table) {
        query.fromClause = table;
        return *this;
    }

    SQLQueryBuilder& innerJoin(const std::string& table, const std::string& condition) {
        query.joinClauses.push_back("INNER JOIN " + table + " ON " + condition);
        return *this;
    }

    SQLQueryBuilder& leftJoin(const std::string& table, const std::string& condition) {
        query.joinClauses.push_back("LEFT JOIN " + table + " ON " + condition);
        return *this;
    }

    SQLQueryBuilder& where(const std::string& condition) {
        query.whereClause = condition;
        return *this;
    }

    SQLQueryBuilder& orderBy(const std::string& field) {
        query.orderByClause = field;
        return *this;
    }

    SQLQueryBuilder& limit(int count) {
        query.limitValue = count;
        return *this;
    }

    SQLQuery build() {
        if (query.selectClause.empty() || query.fromClause.empty()) {
            throw std::invalid_argument("SELECT and FROM clauses are required");
        }
        return query;
    }
};

int main() {
    try {
        SQLQuery q = SQLQueryBuilder()
            .select("u.name, o.order_date, p.product_name")
            .from("users u")
            .innerJoin("orders o", "u.id = o.user_id")
            .innerJoin("products p", "            "p.id = o.product_id")
            .where("u.age > 18")
            .orderBy("o.order_date DESC")
            .limit(10)
            .build();

        std::cout << q.toString() << "\n\n";
        SQLQuery q2 = SQLQueryBuilder()
            .select("u.name, d.department_name, d.location")
            .from("users u")
            .leftJoin("departments d", "u.department_id = d.id")
            .where("d.location = 'New York'")
            .orderBy("u.name")
            .build();

        std::cout << q2.toString() << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error building query: " << e.what() << "\n";
    }
    return 0;
}

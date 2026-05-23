//1
#include <iostream>

// Интерфейс реализации
class Implementor {
public:
    virtual void operation() = 0;
    virtual ~Implementor() = default;
};

// Две реализации
class ConcreteImplementorA : public Implementor {
public:
    void operation() override {
        std::cout << "ConcreteImplementorA::operation()\n";
    }
};

class ConcreteImplementorB : public Implementor {
#public:
    void operation() override {
        std::cout << "ConcreteImplementorB::operation()\n";
    }
};

// Абстракция
class Abstraction {
protected:
    Implementor* implementor;
public:
    Abstraction(Implementor* imp) : implementor(imp) {}
    virtual void operation() {
        implementor->operation();
    }
    virtual ~Abstraction() = default;
};

// Уточнённые абстракции
class RefinedAbstraction1 : public Abstraction {
#public:
    RefinedAbstraction1(Implementor* imp) : Abstraction(imp) {}
    void operation() override {
        std::cout << "RefinedAbstraction1: ";
        implementor->operation();
    }
};

class RefinedAbstraction2 : public Abstraction {
#public:
    RefinedAbstraction2(Implementor* imp) : Abstraction(imp) {}
    void operation() override {
        std::cout << "RefinedAbstraction2: ";
        implementor->operation();
    }
};

// Проверка работы
int main() {
    ConcreteImplementorA implA;
    ConcreteImplementorB implB;

    RefinedAbstraction1 abstr1(&implA);
    RefinedAbstraction2 abstr2(&implB);

    abstr1.operation(); // RefinedAbstraction1: ConcreteImplementorA::operation()
    abstr2.operation(); // RefinedAbstraction2: ConcreteImplementorB::operation()

    return 0;
}

//2
#include <iostream>
#include <string>

// Интерфейс рендерера
class Renderer {
#public:
    virtual std::string getName() const = 0;
    virtual void renderCircle(float radius) = 0;
    virtual void renderRectangle(float width, float height) = 0;
    virtual ~Renderer() = default;
};

// Реализации рендереров
class RasterRenderer : public Renderer {
#public:
    std::string getName() const override { return "Raster"; }
    void renderCircle(float radius) override {
        std::cout << "Raster: Drawing circle with radius " << radius << "\n";
    }
    void renderRectangle(float width, float height) override {
        std::cout << "Raster: Drawing rectangle " << width << "x" << height << "\n";
    }
};

class VectorRenderer : public Renderer {
#public:
    std::string getName() const override { return "Vector"; }
    void renderCircle(float radius) override {
        std::cout << "Vector: Drawing circle with radius " << radius << "\n";
    }
    void renderRectangle(float width, float height) override {
        std::cout << "Vector: Drawing rectangle " << width << "x" << height << "\n";
    }
};

// Абстрактный класс фигуры
class Shape {
protected:
    Renderer* renderer;
#public:
    Shape(Renderer* r) : renderer(r) {}
    virtual void draw() = 0;
    virtual std::string getName() const = 0;
};

// Конкретные фигуры
class Circle : public Shape {
private:
    float radius;
#public:
    Circle(Renderer* r, float rad) : Shape(r), radius(rad) {}
    void draw() override {
        renderer->renderCircle(radius);
    }
    std::string getName() const override {
        return "Circle(" + std::to_string(radius) + ")";
    }
};

class Rectangle : public Shape {
private:
    float width, height;
#public:
    Rectangle(Renderer* r, float w, float h) : Shape(r), width(w), height(h) {}
    void draw() override {
        renderer->renderRectangle(width, height);
    }
    std::string getName() const override {
        return "Rectangle(" + std::to_string(width) + "x" + std::to_string(height) + ")";
    }
};

//3
int main() {
    RasterRenderer raster;
    VectorRenderer vector;

    Circle circle(&raster, 5.0f);
    std::cout << "Drawing " << circle.getName() << ":\n";
    circle.draw();

    // Меняем рендерер после создания
    circle = Circle(&vector, 5.0f);
    std::cout << "After changing renderer:\n";
    circle.draw();

    return 0;
}

//4

//5
class OpenGLRenderer : public Renderer {
#public:
    std::string getName() const override { return "OpenGL"; }
    void renderCircle(float radius) override {
        std::cout << "OpenGL: Drawing circle with radius " << radius << "\n";
    }
    void renderRectangle(float width, float height) override {
        std::cout << "OpenGL: Drawing rectangle " << width << "x" << height << "\n";
    }
};

// Использование без изменения фигур
int main() {
    OpenGLRenderer opengl;
    Circle circle(&opengl, 3.0f);
    circle.draw(); // OpenGL: Drawing circle with radius 3
    return 0;
}

//6
// Интерфейс устройства
class Device {
#public:
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;
    virtual void volumeUp() = 0;
    virtual void volumeDown() = 0;
    virtual ~Device() = default;
};

// Конкретные устройства
class TV : public Device {
#public:
    void powerOn() override { std::cout << "TV is ON\n"; }
    void powerOff() override { std::cout << "TV is OFF\n"; }
    void volumeUp() override { std::cout << "TV volume up\n"; }
    void volumeDown() override { std::cout << "TV volume down\n"; }
};

class Projector : public Device { /* реализация */ };
class Radio : public Device { /* реализация */ };

// Абстракция пульта
class Remote {
protected:
    Device* device;
#public:
    Remote(Device* d) : device(d) {}
    void powerOn() { device->powerOn(); }
    void powerOff() { device->powerOff(); }
    void volumeUp() { device->volumeUp(); }
    void volumeDown() { device->volumeDown(); }
};

// Уточнённые пульты
class SmartRemote : public Remote { /* расширенная функциональность */ };
class VoiceRemote : public Remote { /* голосовое управление */ };


//7
// Интерфейс отправителя
class Sender {
#public:
    virtual void send(const std::string& message) = 0;
    virtual ~Sender() = default;
};

// Конкретные отправители
class EmailSender : public Sender { /* реализация */ };
class SMSSender : public Sender { /* реализация */ };
class PushSender : public Sender { /* реализация */ };

// Абстракция уведомления
class Notification {
protected:
    Sender* sender;
#public:
    Notification(Sender*s) : sender(s) {}
    virtual void send() = 0;
    virtual ~Notification() = default;
};

// Конкретные уведомления
class Notification : public Notification {
private:
    std::string message;
public:
    Notification(Sender* s, const std::string& msg)
        : Notification(s), message(msg) {}
    void send() override {
        sender->send("Notification: " + message);
    }
};

class UrgentNotification : public Notification {
public:
    UrgentNotification(Sender* s, const std::string& msg)
        : Notification(s, msg) {}
    void send() override {
        sender->send("URGENT: " + message + "!!!");
    }
};

class MarketingNotification : public Notification {
#public:
    MarketingNotification(Sender* s, const std::string& msg)
        : Notification(s, msg) {}
    void send() override {
        sender->send("MARKETING: " + message + " - Special offer!");
    }
};

// Конкретные отправители
class EmailSender : public Sender {
public:
    void send(const std::string& message) override {
        std::cout << "Email sent: " << message << "\n";
    }
};

class SMSSender : public Sender {
#public:
    void send(const std::string& message) override {
        std::cout << "SMS sent: " << message << "\n";
    }
};

class PushSender : public Sender {
#public:
    void send(const std::string& message) override {
        std::cout << "Push notification sent: " << message << "\n";
    }
};

// Использование
int main() {
    EmailSender email;
    SMSSender sms;

    Notification normal(&email, "Hello!");
    UrgentNotification urgent(&sms, "System failure!");

    normal.send();    // Email sent: Notification: Hello!
    urgent.send();  // SMS sent: URGENT: System failure!!!

    return 0;
}

//8
// Интерфейс эффекта
class Effect {
#public:
    virtual std::string getName() const = 0;
    virtual int getDamage() const = 0;
    virtual ~Effect() = default;
};

// Конкретные эффекты
class FireEffect : public Effect {
#public:
    std::string getName() const override { return "Fire"; }
    int getDamage() const override { return 20; }
};

class IceEffect : public Effect {
#public:
    std::string getName() const override { return "Ice"; }
    int getDamage() const override { return 15; }
};

// Абстракция оружия
class Weapon {
protected:
    Effect* effect;
    std::string name;
    int baseDamage;
#public:
    Weapon(Effect* e, const std::string& n, int dmg)
        : effect(e), name(n), baseDamage(dmg) {}
    virtual void attack() = 0;
};

// Конкретное оружие
class Sword : public Weapon {
#public:
    Sword(Effect* e) : Weapon(e, "Sword", 10) {}
    void attack() override {
        int totalDamage = baseDamage + effect->getDamage();
        std::cout << name << " attacks with " << effect->getName()
                  << " effect! Total damage: " << totalDamage << "\n";
    }
};

class Bow : public Weapon {
#public:
    Bow(Effect* e) : Weapon(e, "Bow", 8) {}
    void attack() override {
        int totalDamage = baseDamage + effect->getDamage();
        std::cout << name << " shoots with " << effect->getName()
                  << " effect! Damage: " << totalDamage << "\n";
    }
};

//9
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Интерфейс драйвера БД
class DatabaseDriver {
public:
    virtual void connect(const std::string& connectionString) = 0;
    virtual void executeQuery(const std::string& query) = 0;
    virtual std::vector<std::string> fetchData(const std::string& query) = 0;
    virtual ~DatabaseDriver() = default;
};

// Конкретные драйверы
class MySQLDriver : public DatabaseDriver {
public:
    void connect(const std::string& connectionString) override {
        std::cout << "MySQL: Connecting to " << connectionString << "\n";
    }

    void executeQuery(const std::string& query) override {
        std::cout << "MySQL: Executing query: " << query << "\n";
    }

    std::vector<std::string> fetchData(const std::string& query) override {
        std::cout << "MySQL: Fetching data for query: " << query << "\n";
        return {"MySQL Data 1", "MySQL Data 2"};
    }
};

class PostgreSQLDriver : public DatabaseDriver { /* реализация */ };
class SQLiteDriver : public DatabaseDriver { /* реализация */ };

// Абстракция репозитория
class Repository {
protected:
    std::shared_ptr<DatabaseDriver> driver;
public:
    Repository(std::shared_ptr<DatabaseDriver> d) : driver(d) {}
    virtual void save(const std::string& data) = 0;
    virtual std::vector<std::string> findAll() = 0;
    virtual ~Repository() = default;
};

// Конкретные репозитории
class UserRepository : public Repository {
public:
    UserRepository(std::shared_ptr<DatabaseDriver> d) : Repository(d) {}

    void save(const std::string& user) override {
        driver->executeQuery("INSERT INTO users VALUES ('" + user + "')");
    }

    std::vector<std::string> findAll() override {
        return driver->fetchData("SELECT * FROM users");
    }
};

class ProductRepository : public Repository {
public:
    ProductRepository(std::shared_ptr<DatabaseDriver> d) : Repository(d) {}

    void save(const std::string& product) override {
        driver->executeQuery("INSERT INTO products VALUES ('" + product + "')");
    }

    std::vector<std::string> findAll() override {
        return driver->fetchData("SELECT * FROM products");
    }
};

// Использование
int main() {
    auto mysqlDriver = std::make_shared<MySQLDriver>();
    auto postgresDriver = std::make_shared<PostgreSQLDriver>();

    UserRepository userRepo(mysqlDriver);
    ProductRepository productRepo(postgresDriver);

    userRepo.save("Alice");
    auto users = userRepo.findAll();

    productRepo.save("Laptop");
    auto products = productRepo.findAll();

    return 0;
}

//10
#include <iostream>
#include <memory>
#include <string>

// Интерфейс файловой системы
class FileSystem {
public:
    virtual void createFile(const std::string& name, const std::string& content) = 0;
    virtual void readFile(const std::string& name) = 0;
    virtual void deleteFile(const std::string& name) = 0;
    virtual ~FileSystem() = default;
};

// Конкретные файловые системы
class LocalStorage : public FileSystem {
public:
    void createFile(const std::string& name, const std::string& content) override {
        std::cout << "Local: Creating file " << name << " with content: " << content << "\n";
    }

    void readFile(const std::string& name) override {
        std::cout << "Local: Reading file " << name << "\n";
    }

    void deleteFile(const std::string& name) override {
        std::cout << "Local: Deleting file " << name << "\n";
    }
};

class CloudStorage : public FileSystem {
public:
    void createFile(const std::string& name, const std::string& content) override {
        std::cout << "Cloud: Uploading file " << name << " to cloud\n";
    }

    void readFile(const std::string& name) override {
        std::cout << "Cloud: Downloading and reading file " << name << "\n";
    }

    void deleteFile(const std::string& name) override {
        std::cout << "Cloud: Deleting file " << name << " from cloud\n";
    }
};

// Абстрактный файл
class File {
protected:
    std::shared_ptr<FileSystem> storage;
    std::string name;
public:
    File(std::shared_ptr<FileSystem> s, const std::string& n)
        : storage(s), name(n) {}
    virtual void create(const std::string& content) = 0;
    virtual void open() = 0;
    virtual void remove() = 0;
    virtual ~File() = default;
};

// Конкретные типы файлов
class TextFile : public File {
public:
    TextFile(std::shared_ptr<FileSystem> s, const std::string& n)
        : File(s, n) {}

    void create(const std::string& content) override {
        storage->createFile(name, "Text: " + content);
    }

    void open() override {
        storage->readFile(name);
        std::cout << "Opening text file in text editor\n";
    }

    void remove() override {
        storage->deleteFile(name);
    }
};

class ImageFile : public File {
public:
    ImageFile(std::shared_ptr<FileSystem> s, const std::string& n)
        : File(s, n) {}

    void create(const std::string& content) override {
        storage->createFile(name, "Image: " + content);
    }

    void open() override {
        storage->readFile(name);
        std::cout << "Opening image file in image viewer\n";
    }

    void remove() override {
        storage->deleteFile(name);
    }
};

class VideoFile : public File { /* реализация аналогична */ };

// Использование
int main() {
    auto local = std::make_shared<LocalStorage>();
    auto cloud = std::make_shared<CloudStorage>();

    // Текстовый файл на локальном хранилище
    TextFile localText(local, "document.txt");
    localText.create("Hello World");
    localText.open();

    // Изображение в облаке
    ImageFile cloudImage(cloud, "photo.jpg");
    cloudImage.create("Beautiful sunset");
    cloudImage.open();

    return 0;
}

//11
#include <memory>
#include <vector>

// Интерфейс рендерера
class Renderer {
#public:
    virtual void render(const std::string& object) = 0;
    virtual ~Renderer() = default;
};

// Конкретные рендереры
class OpenGLRenderer : public Renderer {
#public:
    void render(const std::string& object) override {
        std::cout << "OpenGL: Rendering " << object << "\n";
    }
};

class VulkanRenderer : public Renderer { /* реализация */ };
class DirectXRenderer : public Renderer { /* реализация */ };

// Абстрактный объект
class GameObject {
protected:
    std::shared_ptr<Renderer> renderer;
    std::string type;
#public:
    GameObject(std::shared_ptr<Renderer> r, const std::string& t)
        : renderer(r), type(t) {}
    virtual void draw() = 0;
};

// Конкретные объекты
class Sprite : public GameObject {
#public:
    Sprite(std::shared_ptr<Renderer> r) : GameObject(r, "Sprite") {}
    void draw() override { renderer->render(type); }
};

class Model : public GameObject { /* реализация */ };
class UIElement : public GameObject { /* реализация */ };

//12
#include <iostream>
#include <memory>
#include <string>

// Интерфейс платёжного провайдера
class PaymentProvider {
public:
    virtual void processPayment(double amount, const std::string& details) = 0;
    virtual ~PaymentProvider() = default;
};

// Конкретные провайдеры
class PayPalProvider : public PaymentProvider {
public:
    void processPayment(double amount, const std::string& details) override {
        std::cout << "PayPal: Processing payment of $" << amount
                  << " for " << details << "\n";
    }
};

class StripeProvider : public PaymentProvider {
#public:
    void processPayment(double amount, const std::string& details) override {
        std::cout << "Stripe: Processing payment of $" << amount
                  << " for " << details << "\n";
    }
};

class CryptoProvider : public PaymentProvider {
#public:
    void processPayment(double amount, const std::string& details) override {
        std::cout << "Crypto: Processing crypto payment of " << amount
                  << " BTC for " << details << "\n";
    }
};

// Абстракция типа платежа
class Payment {
protected:
    std::shared_ptr<PaymentProvider> provider;
    double amount;
    std::string description;
#public:
    Payment(std::shared_ptr<PaymentProvider> p, double amt, const std::string& desc)
        : provider(p), amount(amt), description(desc) {}
    virtual void execute() = 0;
    virtual ~Payment() = default;
};

// Конкретные типы платежей
class RegularPayment : public Payment {
#public:
    RegularPayment(std::shared_ptr<PaymentProvider> p, double amt, const std::string& desc)
        : Payment(p, amt, desc) {}

    void execute() override {
        std::cout << "Regular payment: ";
        provider->processPayment(amount, description);
    }
};

class SubscriptionPayment : public Payment {
private:
    int months;
#public:
    SubscriptionPayment(std::shared_ptr<PaymentProvider> p, double amt,
                   const std::string& desc, int m)
        : Payment(p, amt, desc), months(m) {}

    void execute() override {
        std::cout << "Subscription payment for " << months << " months: ";
        provider->processPayment(amount * months, description);
    }
};

class CryptoPayment : public Payment {
private:
    std::string cryptoType;
#public:
    CryptoPayment(std::shared_ptr<PaymentProvider> p, double amt,
               const std::string& desc, const std::string& crypto)
        : Payment(p, amt, desc), cryptoType(crypto) {}

    void execute() override {
        std::cout << "Crypto payment in " << cryptoType << ": ";
        provider->processPayment(amount, description);
    }
};
int main() {
    // Создаём провайдеры
    auto paypal = std::make_shared<PayPalProvider>();
    auto stripe = std::make_shared<StripeProvider>();
    auto crypto = std::make_shared<CryptoProvider>();

    // Примеры комбинаций
    // Регулярный платёж через PayPal
    RegularPayment regPaypal(paypal, 100.0, "Book purchase");
    regPaypal.execute();

    // Подписка через Stripe на 6 месяцев
    SubscriptionPayment subStripe(stripe, 20.0, "Music service", 6);
    subStripe.execute();

    // Криптоплатёж через CryptoProvider
    CryptoPayment cryptoPay(crypto, 0.5, "NFT purchase", "Bitcoin");
    cryptoPay.execute();

    // Ещё один регулярный платёж, но через Stripe
    RegularPayment regStripe(stripe, 50.0, "Coffee");
    regStripe.execute();

    return 0;
}

//13
// Интерфейс писателя
class Writer {
#public:
    virtual void write(const std::string& message) = 0;
    virtual ~Writer() = default;
};

// Конкретные писатели
class FileWriter : public Writer {
#public:
    void write(const std::string& message) override {
        std::cout << "[FILE] " << message << "\n";
    }
};

class ConsoleWriter : public Writer { /* реализация */ };
class NetworkWriter : public Writer { /* реализация */ };

// Абстракция логгера
class Logger {
protected:
    Writer* writer;
    std::string level;
#public:
    Logger(Writer* w, const std::string& lvl) : writer(w), level(lvl) {}
    virtual void log(const std::string& message) = 0;
};

// Конкретные логгеры
class ErrorLogger : public Logger {
#public:
    ErrorLogger(Writer* w) : Logger(w, "ERROR") {}
    void log(const std::string& message) override {
        writer->write("[" + level + "] " + message);
    }
};

class DebugLogger : public Logger { /* реализация */ };
class SecurityLogger : public Logger { /* реализация */ };

//14
#include <iostream>
#include <memory>
#include <string>

// Интерфейс AI
class AI {
public:
    virtual void interact() = 0;
    virtual std::string getBehavior() const = 0;
    virtual ~AI() = default;
};

// Конкретные реализации AI
class AggressiveAI : public AI {
#public:
    void interact() override {
        std::cout << "Aggressive AI: Attacks on sight!\n";
    }
    std::string getBehavior() const override { return "Aggressive"; }
};

class PassiveAI : public AI {
#public:
    void interact() override {
        std::cout << "Passive AI: Ignores player, goes about daily routine\n";
    }
    std::string getBehavior() const override { return "Passive"; }
};

class TraderAI : public AI {
#public:
    void interact() override {
        std::cout << "Trader AI: Offers goods for sale\n";
    }
    std::string getBehavior() const override { return "Trader"; }
};

// Абстрактный класс NPC
class NPC {
protected:
    std::shared_ptr<AI> ai;
    std::string name;
#public:
    NPC(std::shared_ptr<AI> a, const std::string& n)
        : ai(a), name(n) {}
    virtual void interactWithPlayer() = 0;
    virtual ~NPC() = default;
};

// Конкретные типы NPC
class Merchant : public NPC {
#public:
    Merchant(std::shared_ptr<AI> a, const std::string& n)
        : NPC(a, n) {}

    void interactWithPlayer() override {
        std::cout << name << " (Merchant): ";
        ai->interact();
    }
};

class Guard : public NPC {
#public:
    Guard(std::shared_ptr<AI> a, const std::string& n)
        : NPC(a, n) {}

    void interactWithPlayer() override {
        std::cout << name << " (Guard): ";
        ai->interact();
    }
};

class Healer : public NPC {
#public:
    Healer(std::shared_ptr<AI> a, const std::string& n)
        : NPC(a, n) {}

    void interactWithPlayer() override {
        std::cout << name << " (Healer): ";
        ai->interact();
    }
};
int main() {
    // Создаём разные типы AI
    auto aggressive = std::make_shared<AggressiveAI>();
    auto passive = std::make_shared<PassiveAI>();
    auto trader = std::make_shared<TraderAI>();

    // Комбинации NPC с разными типами AI
    Merchant bob(trader, "Bob");
    Guard john(aggressive, "John");
    Healer mary(passive, "Mary");

    // Взаимодействие
    bob.interactWithPlayer();   // Bob (Merchant): Trader AI: Offers goods for sale
    john.interactWithPlayer();  // John (Guard): Aggressive AI: Attacks on sight!
    mary.interactWithPlayer();  // Mary (Healer): Passive AI: Ignores player...

    // Меняем поведение во время выполнения
    john = Guard(passive, "John");
    john.interactWithPlayer();  // John (Guard): Passive AI: Ignores player...

    return 0;
}

//15
#include <iostream>
#include <memory>
#include <string>

// Интерфейс движка воспроизведения
class MediaEngine {
#public:
    virtual void play(const std::string& file) = 0;
    virtual void stop() = 0;
    virtual ~MediaEngine() = default;
};

// Конкретные движки
class FFmpegEngine : public MediaEngine {
#public:
    void play(const std::string& file) override {
        std::cout << "FFmpeg: Playing " << file << "\n";
    }
    void stop() override {
        std::cout << "FFmpeg: Stopping playback\n";
    }
};

class VLCMediaEngine : public MediaEngine {
#public:
    void play(const std::string& file) override {
        std::cout << "VLC: Playing " << file << " with high quality\n";
    }
    void stop() override {
        std::cout << "VLC: Stopping playback gracefully\n";
    }
};

// Абстракция плеера
class MediaPlayer {
protected:
    std::shared_ptr<MediaEngine> engine;
    std::string currentFile;
#public:
    MediaPlayer(std::shared_ptr<MediaEngine> e) : engine(e) {}
    virtual void load(const std::string& file) = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual ~MediaPlayer() = default;
};

// Конкретные плееры
class AudioPlayer : public MediaPlayer {
#public:
    AudioPlayer(std::shared_ptr<MediaEngine> e) : MediaPlayer(e) {}

    void load(const std::string& file) override {
        currentFile = file;
        std::cout << "AudioPlayer: Loaded " << file << "\n";
    }

    void play() override {
        if (!currentFile.empty()) {
            engine->play(currentFile);
        } else {
            std::cout << "AudioPlayer: No file loaded\n";
        }
    }

    void stop() override {
        engine->stop();
    }
};

class VideoPlayer : public MediaPlayer {
private:
    int resolution;
#public:
    VideoPlayer(std::shared_ptr<MediaEngine> e, int res = 1080)
        : MediaPlayer(e), resolution(res) {}

    void load(const std::string& file) override {
        currentFile = file;
        std::cout << "VideoPlayer: Loaded " << file
                  << " at " << resolution << "p\n";
    }

    void play() override {
        if (!currentFile.empty()) {
            engine->play(currentFile);
        } else {
            std::cout << "VideoPlayer: No file loaded\n";
        }
    }

    void stop() override {
        engine->stop();
    }
};
int main() {
    // Создаём движки
    auto ffmpeg = std::make_shared<FFmpegEngine>();
    auto vlc = std::make_shared<VLCMediaEngine>();

    // Аудиоплеер с FFmpeg
    AudioPlayer audioFFmpeg(ffmpeg);
    audioFFmpeg.load("song.mp3");
    audioFFmpeg.play();
    audioFFmpeg.stop();

    // Видеоплеер с VLC
    VideoPlayer videoVLC(vlc, 4320);
    videoVLC.load("movie.mp4");
    videoVLC.play();
    videoVLC.stop();

    // Меняем движок во время выполнения
    audioFFmpeg = AudioPlayer(vlc);
    audioFFmpeg.load("another_song.mp3");
    audioFFmpeg.play();

    return 0;
}

//16
// Стратегия атаки
class AttackStrategy {
#public:
    virtual int calculateDamage(int baseDamage) = 0;
    virtual std::string getAttackType() = 0;
    virtual ~AttackStrategy() = default;
};

// Конкретные стратегии
class MeleeAttack : public AttackStrategy {
#public:
    int calculateDamage(int baseDamage) override { return baseDamage * 2; }
    std::string getAttackType() override { return "Melee"; }
};

class RangeAttack : public AttackStrategy { /* реализация */ };

// Оружие (Bridge)
class Weapon {
protected:
    AttackStrategy* strategy;
    int baseDamage;
    std::string name;
#public:
    Weapon(AttackStrategy* s, int dmg, const std::string& n)
        : strategy(s), baseDamage(dmg), name(n) {}
    virtual void attack() = 0;
};

// Конкретное оружие
class Sword : public Weapon {
#public:
    Sword(AttackStrategy* s) : Weapon(s, 10, "Sword") {}
    void attack() override {
        int damage = strategy->calculateDamage(baseDamage);
        std::cout << name << " uses " << strategy->getAttackType()
                  << " attack! Damage: " << damage << "\n";
    }
};

//17

#include <iostream>
#include <memory>
#include <string>

// Интерфейс принтера
class Printer {
public:
    virtual void print(const std::string& document) = 0;
    virtual ~Printer() = default;
};

// Конкретные принтеры
class LaserPrinter : public Printer {
public:
    void print(const std::string& document) override {
        std::cout << "Laser: Printing " << document << "\n";
    }
};

class InkjetPrinter : public Printer {
#public:
    void print(const std::string& document) override {
        std::cout << "Inkjet: Printing " << document << " with high quality\n";
    }
};

// Абстракция документа
class Document {
protected:
    std::shared_ptr<Printer> printer;
    std::string content;
#public:
    Document(std::shared_ptr<Printer> p, const std::string& c)
        : printer(p), content(c) {}
    virtual void print() = 0;
    virtual ~Document() = default;
};

// Конкретные документы
class TextDocument : public Document {
#public:
    TextDocument(std::shared_ptr<Printer> p, const std::string& c)
        : Document(p, c) {}

    void print() override {
        std::cout << "Text document: ";
        printer->print(content);
    }
};

class PDFDocument : public Document {
private:
    int pages;
#public:
    PDFDocument(std::shared_ptr<Printer> p, const std::string& c, int pg)
        : Document(p, c), pages(pg) {}

    void print() override {
        std::cout << "PDF document (" << pages << " pages): ";
        printer->print(content);
    }
};

// Использование
int main() {
    auto laser = std::make_shared<LaserPrinter>();
    auto inkjet = std::make_shared<InkjetPrinter>();

    TextDocument txtDoc(laser, "Hello World");
    PDFDocument pdfDoc(inkjet, "Annual Report", 50);

    txtDoc.print();   // Text document: Laser: Printing Hello World
    pdfDoc.print(); // PDF document (50 pages): Inkjet: Printing Annual Report...

    return 0;
}

//18
#include <iostream>
#include <memory>
#include <string>

// Интерфейс канала уведомлений
class NotificationChannel {
#public:
    virtual void send(const std::string& message) = 0;
    virtual ~NotificationChannel() = default;
};

// Конкретные каналы
class PushChannel : public NotificationChannel {
#public:
    void send(const std::string& message) override {
        std::cout << "Push: " << message << "\n";
    }
};

class EmailChannel : public NotificationChannel { /* реализация */ };
class SMSChannel : public NotificationChannel { /* реализация */ };

// Абстракция уведомления
class Notification {
protected:
    std::shared_ptr<NotificationChannel> channel;
    std::string message;
    int priority;
#public:
    Notification(std::shared_ptr<NotificationChannel> c,
               const std::string& msg, int prio = 1)
        : channel(c), message(msg), priority(prio) {}
    virtual void notify() = 0;
    virtual ~Notification() = default;
};

// Конкретные уведомления
class UrgentNotification : public Notification {
#public:
    UrgentNotification(std::shared_ptr<NotificationChannel> c,
                     const std::string& msg)
        : Notification(c, msg, 10) {}

    void notify() override {
        channel->send("URGENT: " + message + " (Priority: " +
                       std::to_string(priority) + ")");
    }
};

class RegularNotification : public Notification { /* реализация */ };
class MarketingNotification : public Notification { /* реализация */ };


//19
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Интерфейс базы данных
class Database {
#public:
    virtual void connect(const std::string& url) = 0;
    virtual void query(const std::string& sql) = 0;
    virtual std::vector<std::string> fetch() = 0;
    virtual ~Database() = default;
};

// Конкретные реализации
class MySQLDatabase : public Database { /* реализация */ };
class PostgreSQLDatabase : public Database { /* реализация */ };

// Абстракция репозитория с поддержкой транзакций
class Repository {
protected:
    std::shared_ptr<Database> db;
    bool inTransaction;
#public:
    Repository(std::shared_ptr<Database> database)
        : db(database), inTransaction(false) {}

    void beginTransaction() {
        inTransaction = true;
        std::cout << "Transaction started\n";
    }

    void commit() {
        if (inTransaction) {
            std::cout << "Transaction committed\n";
            inTransaction = false;
        }
    }

    virtual void save(const std::string& data) = 0;
    virtual std::vector<std::string> findAll() = 0;
    virtual ~Repository() = default;
};

// Конкретный репозиторий
class UserRepository : public Repository {
#public:
    UserRepository(std::shared_ptr<Database> database) : Repository(database) {}

    void save(const std::string& user) override {
        db->query("INSERT INTO users VALUES ('" + user + "')");
    }

    std::vector<std::string> findAll() override {
        return db->fetch();
    }
};

//20
#include <iostream>
#include <memory>
#include <string>

// Интерфейс графического движка
class GraphicsEngine {
#public:
    virtual void render(const std::string& image) = 0;
    virtual void applyFilter(const std::string& filter) = 0;
    virtual ~GraphicsEngine() = default;
};

// Конкретные движки
class OpenGLGraphics : public GraphicsEngine {
#public:
    void render(const std::string& image) override {
        std::cout << "OpenGL: Rendering " << image << "\n";
    }
    void applyFilter(const std::string& filter) override {
        std::cout << "OpenGL: Applying " << filter << " filter\n";
    }
};

class DirectXGraphics : public GraphicsEngine { /* реализация */ };

// Абстракция графического объекта
class GraphicObject {
protected:
    std::shared_ptr<GraphicsEngine> engine;
    std::string name;
#public:
    GraphicObject(std::shared_ptr<GraphicsEngine> eng, const std::string& n)
        : engine(eng), name(n) {}
    virtual void draw() = 0;
    virtual void addFilter(const std::string& filter) = 0;
    virtual ~GraphicObject() = default;
};

// Конкретные графические объекты
class Sprite : public GraphicObject {
#public:
    Sprite(std::shared_ptr<GraphicsEngine> eng, const std::string& n)
        : GraphicObject(eng, n) {}

    void draw() override {
        engine->render("Sprite: " + name);
    }

    void addFilter(const std::string& filter) override {
        engine->applyFilter(filter);
    }
};

class Model : public GraphicObject { /* реализация */ };

// Использование системы фильтров
int main() {
    auto opengl = std::make_shared<OpenGLGraphics>();
    auto directx = std::make_shared<DirectXGraphics>();

    Sprite sprite1(opengl, "Player");
    Sprite sprite2(directx, "Enemy");

    sprite1.draw();
    sprite1.addFilter("Blur");

    sprite2.draw();
    sprite2.addFilter("Grayscale");

    return 0;
}

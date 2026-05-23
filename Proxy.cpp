//1
#include <iostream>
#include <string>

struct Subject {
    virtual void request() = 0;
    virtual ~Subject() = default;
};

struct RealSubject : Subject {
    void request() override {
        std::cout << "[RealSubject] Выполняется запрос
";
    }
};

struct Proxy : Subject {
    Proxy() : real_(std::make_unique<RealSubject>()) {}

    void request() override {
        std::cout << "[Proxy] До вызова
";
        real_->request();
        std::cout << "[Proxy] После вызова
";
    }
private:
    std::unique_ptr<RealSubject> real_;
};

int main() {
    std::unique_ptr<Subject> s = std::make_unique<Proxy>();
    s->request();
}
//2
#include <iostream>
#include <string>
#include <memory>

struct Image {
    virtual void display() = 0;
    virtual ~Image() = default;
};

struct RealImage : Image {
    explicit RealImage(const std::string& file) : file_(file) {
        std::cout << "[RealImage] Загрузка: " << file_ << "
";
    }
    void display() override {
        std::cout << "[RealImage] Отображение: " << file_ << "
";
    }
private:
    std::string file_;
};

struct ImageProxy : Image {
    explicit ImageProxy(const std::string& file) : file_(file) {}

    void display() override {
        if (!real_) {
            real_ = std::make_unique<RealImage>(file_);
        }
        real_->display();
    }
private:
    std::string file_;
    std::unique_ptr<RealImage> real_;
};

int main() {
    ImageProxy img("photo.jpg");
    std::cout << "--- Первый вызов:
";
    img.display();
    std::cout << "--- Повторный вызов:
";
    img.display();
}
//3
#include <iostream>
#include <string>
#include <memory>

struct Image {
    virtual void display() = 0;
    virtual ~Image() = default;
};

struct RealImage : Image {
    explicit RealImage(const std::string& file) : file_(file) {
        std::cout << "[RealImage] Загрузка: " << file_ << "
";
    }
    void display() override {
        std::cout << "[RealImage] Отображение: " << file_ << "
";
    }
private:
    std::string file_;
};

struct ImageProxy : Image {
    explicit ImageProxy(const std::string& file) : file_(file) {}

    void display() override {
        if (!real_) {
            real_ = std::make_unique<RealImage>(file_);
        }
        real_->display();
    }
private:
    std::string file_;
    std::unique_ptr<RealImage> real_;
};

int main() {
    ImageProxy img("photo.jpg");
    std::cout << "--- Первый вызов:
";
    img.display();
    std::cout << "--- Повторный вызов:
";
    img.display();
}
//4
#include <iostream>
#include <chrono>
#include <string>

struct Service {
    virtual void process() = 0;
    virtual ~Service() = default;
};

struct RealService : Service {
    void process() override {
        std::cout << "[RealService] Обработка данных
";
    }
};

struct LoggingProxy : Service {
    explicit LoggingProxy(std::unique_ptr<Service> s)
        : inner_(std::move(s)), count_(0) {}

    void process() override {
        using Clock = std::chrono::steady_clock;
        auto start = Clock::now();
        std::cout << "[Log] Начало операции #" << ++count_ << "
";

        inner_->process();

        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(
            Clock::now() - start).count();
        std::cout << "[Log] Завершено за " << ms << " мкс
";
    }
private:
    std::unique_ptr<Service> inner_;
    int count_;
};

int main() {
    auto proxy = std::make_unique<LoggingProxy>(
        std::make_unique<RealService>());
    proxy->process();
    proxy->process();
}
//5
#include <iostream>
#include <unordered_map>
#include <string>

struct Calculator {
    virtual int compute(int n) = 0;
    virtual ~Calculator() = default;
};

struct HeavyCalculator : Calculator {
    int compute(int n) override {
        std::cout << "[Heavy] Вычисление для n=" << n << "...
";
        int sum = 0;
        for (int i = 1; i <= n; ++i) sum += i;
        return sum;
    }
};

struct CachingProxy : Calculator {
    CachingProxy() : real_(std::make_unique<HeavyCalculator>()) {}

    int compute(int n) override {
        auto it = cache_.find(n);
        if (it != cache_.end()) {
            std::cout << "[Cache] Хит для n=" << n << "
";
            return it->second;
        }
        int result = real_->compute(n);
        cache_[n] = result;
        return result;
    }
private:
    std::unique_ptr<HeavyCalculator> real_;
    std::unordered_map<int, int> cache_;
};

int main() {
    CachingProxy calc;
    std::cout << "Результат: " << calc.compute(100) << "
";
    std::cout << "Результат: " << calc.compute(100) << "
";
    std::cout << "Результат: " << calc.compute(50)  << "
";
}
//6
#include <iostream>
#include <string>
#include <unordered_map>

struct API {
    virtual std::string request(
        const std::string& token,
        const std::string& endpoint) = 0;
    virtual ~API() = default;
};

struct RealAPI : API {
    std::string request(const std::string&,
                        const std::string& ep) override {
        return "[RealAPI] Ответ для: " + ep;
    }
};

struct APIGatewayProxy : API {
    explicit APIGatewayProxy(int limit = 5)
        : real_(std::make_unique<RealAPI>()), limit_(limit) {}

    std::string request(const std::string& token,
                        const std::string& ep) override {
        if (token != "valid-token") {
            return "[Gateway] 401 Unauthorized";
        }
        if (++calls_[ep] > limit_) {
            return "[Gateway] 429 Too Many Requests";
        }
        auto resp = real_->request(token, ep);
        std::cout << "[Log] " << ep << " вызван " << calls_[ep] << " раз
";
        return resp;
    }
private:
    std::unique_ptr<RealAPI> real_;
    std::unordered_map<std::string, int> calls_;
    int limit_;
};

int main() {
    APIGatewayProxy gw(3);
    for (int i = 0; i < 4; ++i) {
        std::cout << gw.request("valid-token", "/data") << "
";
    }
    std::cout << gw.request("bad", "/data") << "
";
}
//7
#include <iostream>
#include <string>
#include <unordered_set>

struct FileSystem {
    virtual bool deleteFile(
        const std::string& path,
        const std::string& user) = 0;
    virtual ~FileSystem() = default;
};

struct RealFileSystem : FileSystem {
    bool deleteFile(const std::string& path,
                    const std::string&) override {
        std::cout << "[FS] Удалён: " << path << "
";
        return true;
    }
};

struct ProtectedFileSystem : FileSystem {
    ProtectedFileSystem()
        : real_(std::make_unique<RealFileSystem>()),
          systemFiles_{"/etc/passwd", "/etc/hosts", "/bin/bash"} {}

    bool deleteFile(const std::string& path,
                    const std::string& user) override {
        std::cout << "[Log] Попытка удаления: " << path
                  << " пользователем: " << user << "
";
        if (systemFiles_.count(path)) {
            std::cout << "[Protected] Запрещено: системный файл
";
            return false;
        }
        if (user != "root" && path.rfind("/var", 0) == 0) {
            std::cout << "[Protected] Нет прав для /var
";
            return false;
        }
        return real_->deleteFile(path, user);
    }
private:
    std::unique_ptr<RealFileSystem> real_;
    std::unordered_set<std::string> systemFiles_;
};

int main() {
    ProtectedFileSystem fs;
    fs.deleteFile("/tmp/trash.log", "alice");
    fs.deleteFile("/etc/passwd", "alice");
    fs.deleteFile("/var/log/app.log", "bob");
    fs.deleteFile("/var/log/app.log", "root");
}
//8
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct Texture {
    virtual void bind() = 0;
    virtual ~Texture() = default;
};

struct RealTexture : Texture {
    explicit RealTexture(const std::string& f) : file_(f) {
        std::cout << "[GPU] Загрузка текстуры: " << f << "
";
    }
    void bind() override {
        std::cout << "[GPU] Bind: " << file_ << "
";
    }
    const std::string& file() const { return file_; }
private:
    std::string file_;
};

struct TextureProxy : Texture {
    explicit TextureProxy(const std::string& f) : file_(f) {}

    void bind() override {
        if (!real_) {
            auto it = cache_.find(file_);
            if (it != cache_.end()) {
                real_ = it->second;
            } else {
                real_ = std::make_shared<RealTexture>(file_);
                cache_[file_] = real_;
            }
        }
        ++uses_;
        real_->bind();
        std::cout << "[Proxy] Использований: " << uses_ << "
";
    }

    static void clearCache() { cache_.clear(); }
private:
    std::string file_;
    std::shared_ptr<RealTexture> real_;
    int uses_ = 0;
    inline static std::unordered_map<
        std::string,
        std::shared_ptr<RealTexture>> cache_;
};

int main() {
    TextureProxy t1("wall.png"), t2("wall.png"), t3("sky.png");
    t1.bind(); t2.bind(); t1.bind(); t3.bind();
}
//9
#include <iostream>
#include <string>

struct Video {
    virtual void play() = 0;
    virtual ~Video() = default;
};

struct RealVideo : Video {
    RealVideo(const std::string& f, int minAge)
        : file_(f), minAge_(minAge) {
        std::cout << "[Video] Загрузка: " << f << "
";
    }
    void play() override {
        std::cout << "[Video] Воспроизведение: " << file_ << "
";
    }
    int minAge() const { return minAge_; }
private:
    std::string file_;
    int minAge_;
};

struct VideoProxy : Video {
    VideoProxy(const std::string& f, int minAge, int userAge)
        : file_(f), minAge_(minAge), userAge_(userAge) {}

    void play() override {
        if (userAge_ < minAge_) {
            std::cout << "[Proxy] Доступ запрещён: требуется " 
                      << minAge_ << "+
";
            return;
        }
        if (!real_) {
            real_ = std::make_unique<RealVideo>(file_, minAge_);
        }
        real_->play();
    }
private:
    std::string file_;
    int minAge_, userAge_;
    std::unique_ptr<RealVideo> real_;
};

int main() {
    VideoProxy child("movie18.mp4", 18, 15);
    child.play();

    VideoProxy adult("movie18.mp4", 18, 25);
    adult.play();
    adult.play();
}
//10
#include <iostream>
#include <string>

struct BankAccount {
    virtual bool withdraw(double amount, const std::string& pin) = 0;
    virtual bool deposit(double amount) = 0;
    virtual double balance() const = 0;
    virtual ~BankAccount() = default;
};

struct RealBankAccount : BankAccount {
    explicit RealBankAccount(double init) : balance_(init) {}

    bool withdraw(double amount, const std::string&) override {
        if (amount > balance_) return false;
        balance_ -= amount;
        return true;
    }
    bool deposit(double amount) override {
        balance_ += amount;
        return true;
    }
    double balance() const override { return balance_; }
private:
    double balance_;
};

struct SecureBankProxy : BankAccount {
    SecureBankProxy(double init, std::string pin,
                    double maxOp = 10000.0)
        : real_(std::make_unique<RealBankAccount>(init)),
          pin_(std::move(pin)), maxOp_(maxOp) {}

    bool withdraw(double amount, const std::string& pin) override {
        std::cout << "[Log] Снятие: " << amount << "
";
        if (pin != pin_) {
            std::cout << "[Secure] Неверный PIN
"; return false;
        }
        if (amount > maxOp_) {
            std::cout << "[Secure] Превышен лимит " << maxOp_ << "
";
            return false;
        }
        bool ok = real_->withdraw(amount, pin);
        std::cout << "[Log] " << (ok ? "Успешно" : "Недостаточно средств")
                  << ". Баланс: " << real_->balance() << "
";
        return ok;
    }
    bool deposit(double amount) override {
        std::cout << "[Log] Пополнение: " << amount << "
";
        return real_->deposit(amount);
    }
    double balance() const override { return real_->balance(); }
private:
    std::unique_ptr<RealBankAccount> real_;
    std::string pin_;
    double maxOp_;
};

int main() {
    SecureBankProxy acc(50000.0, "1234", 10000.0);
    acc.deposit(5000.0);
    acc.withdraw(3000.0, "0000");
    acc.withdraw(3000.0, "1234");
    acc.withdraw(15000.0, "1234");
}
//11
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <stdexcept>

struct RemoteService {
    virtual std::string fetch(const std::string& url) = 0;
    virtual ~RemoteService() = default;
};

struct RealRemoteService : RemoteService {
    std::string fetch(const std::string& url) override {
        return R"({"status":"ok","data":"payload"})";
    }
};

struct RemoteServiceProxy : RemoteService {
    RemoteServiceProxy(int latencyMs = 200, double failRate = 0.1)
        : real_(std::make_unique<RealRemoteService>()),
          latency_(latencyMs), failRate_(failRate) {}

    std::string fetch(const std::string& url) override {
        std::cout << "[Proxy] HTTP GET " << url << "
";
        std::cout << "[Proxy] Задержка: " << latency_ << "ms
";
        std::this_thread::sleep_for(
            std::chrono::milliseconds(latency_));

        if ((rand() % 100) < static_cast<int>(failRate_ * 100)) {
            std::cout << "[Proxy] Ошибка соединения!
";
            return "{"error":"connection refused"}";
        }
        auto resp = real_->fetch(url);
        std::cout << "[Proxy] Ответ получен
";
        return resp;
    }
private:
    std::unique_ptr<RealRemoteService> real_;
    int latency_;
    double failRate_;
};

int main() {
    RemoteServiceProxy svc(100, 0.0);
    auto r = svc.fetch("https://api.example.com/data");
    std::cout << "Данные: " << r << "
";
}
//12
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>

struct Resource {
    virtual void use() = 0;
    virtual ~Resource() = default;
};

struct RealResource : Resource {
    static int activeCount;
    RealResource() { ++activeCount; std::cout << "[Res] Создан
"; }
    ~RealResource() { --activeCount; std::cout << "[Res] Удалён
"; }
    void use() override { std::cout << "[Res] Используется
"; }
};
int RealResource::activeCount = 0;

struct SmartProxy : Resource {
    SmartProxy() {
        real_ = std::make_unique<RealResource>();
        lastUse_ = std::chrono::steady_clock::now();
    }

    void use() override {
        lastUse_ = std::chrono::steady_clock::now();
        real_->use();
        std::cout << "[Smart] Активных объектов: "
                  << RealResource::activeCount << "
";
    }

    bool isExpired(int ttlSeconds = 2) const {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            now - lastUse_).count();
        return elapsed >= ttlSeconds;
    }

    void checkExpiry(int ttlSeconds = 2) {
        if (real_ && isExpired(ttlSeconds)) {
            std::cout << "[Smart] TTL истёк. Освобождение.
";
            real_.reset();
        }
    }
private:
    std::unique_ptr<RealResource> real_;
    std::chrono::steady_clock::time_point lastUse_;
};

int main() {
    SmartProxy p;
    p.use();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    p.checkExpiry(2);
}
//13
#include <iostream>
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

struct User { int id; std::string name; std::string email; };

struct UserRepository {
    virtual std::optional<User> findById(int id) = 0;
    virtual ~UserRepository() = default;
};

struct DatabaseRepository : UserRepository {
    explicit DatabaseRepository(std::vector<User> data)
        : data_(std::move(data)) {}

    std::optional<User> findById(int id) override {
        std::cout << "[DB] Запрос пользователя id=" << id << "
";
        for (const auto& u : data_)
            if (u.id == id) return u;
        return std::nullopt;
    }
private:
    std::vector<User> data_;
};

struct CachedUserRepository : UserRepository {
    explicit CachedUserRepository(
        std::unique_ptr<UserRepository> repo)
        : inner_(std::move(repo)) {}

    std::optional<User> findById(int id) override {
        if (auto it = cache_.find(id); it != cache_.end()) {
            std::cout << "[Cache] Хит для id=" << id << "
";
            return it->second;
        }
        auto result = inner_->findById(id);
        if (result) cache_[id] = *result;
        return result;
    }
private:
    std::unique_ptr<UserRepository> inner_;
    std::unordered_map<int, User> cache_;
};

int main() {
    std::vector<User> db = {{1,"Алиса","alice@mail.ru"},
                             {2,"Боб","bob@mail.ru"}};
    CachedUserRepository repo(
        std::make_unique<DatabaseRepository>(std::move(db)));

    auto u1 = repo.findById(1);
    auto u2 = repo.findById(1);  // кеш
    auto u3 = repo.findById(2);
    if (u1) std::cout << "Найден: " << u1->name << "
";
}
//14
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <atomic>

struct SharedResource {
    virtual void access(const std::string& who) = 0;
    virtual ~SharedResource() = default;
};

struct RealSharedResource : SharedResource {
    void access(const std::string& who) override {
        std::cout << "[Resource] " << who << " работает
";
    }
};

struct ThreadSafeProxy : SharedResource {
    ThreadSafeProxy()
        : real_(std::make_unique<RealSharedResource>()),
          busy_(false) {}

    void access(const std::string& who) override {
        std::unique_lock<std::mutex> lock(mtx_);
        if (busy_) {
            std::cout << "[Proxy] " << who
                      << " заблокирован — ресурс занят
";
            return;
        }
        busy_ = true;
        lock.unlock();

        real_->access(who);

        std::lock_guard<std::mutex> g(mtx_);
        busy_ = false;
    }
private:
    std::unique_ptr<RealSharedResource> real_;
    std::mutex mtx_;
    bool busy_;
};

int main() {
    ThreadSafeProxy proxy;
    proxy.access("Поток-1");
    proxy.access("Поток-2");
    proxy.access("Поток-3");
}
//15
#include <iostream>
#include <string>

struct Service {
    virtual void call(const std::string& msg) = 0;
    virtual ~Service() = default;
};

struct RealService : Service {
    void call(const std::string& msg) override {
        std::cout << "[Service] " << msg << "
";
    }
};

struct RateLimitProxy : Service {
    RateLimitProxy(int maxCalls = 5)
        : real_(std::make_unique<RealService>()),
          max_(maxCalls), count_(0) {}

    void call(const std::string& msg) override {
        if (count_ >= max_) {
            std::cout << "Too many requests
";
            return;
        }
        ++count_;
        real_->call(msg);
    }

    void reset() { count_ = 0; }
private:
    std::unique_ptr<RealService> real_;
    int max_, count_;
};

int main() {
    RateLimitProxy svc(5);
    for (int i = 1; i <= 7; ++i) {
        svc.call("Запрос #" + std::to_string(i));
    }
}
//16
#include <iostream>
#include <string>
#include <memory>

struct Service {
    virtual void execute(const std::string& user) = 0;
    virtual ~Service() = default;
};

struct RealService : Service {
    void execute(const std::string&) override {
        std::cout << "[Service] Бизнес-логика выполнена
";
    }
};

// Protection Proxy
struct AccessProxy : Service {
    AccessProxy(std::unique_ptr<Service> s,
                const std::string& allowedRole,
                const std::string& role)
        : inner_(std::move(s)),
          allowed_(allowedRole), role_(role) {}

    void execute(const std::string& user) override {
        if (role_ != allowed_) {
            std::cout << "[AccessProxy] Нет прав для " << user << "
";
            return;
        }
        inner_->execute(user);
    }
private:
    std::unique_ptr<Service> inner_;
    std::string allowed_, role_;
};

// Logging Decorator
struct LoggingDecorator : Service {
    explicit LoggingDecorator(std::unique_ptr<Service> s)
        : inner_(std::move(s)) {}

    void execute(const std::string& user) override {
        std::cout << "[Log] -> " << user << " вызывает execute()
";
        inner_->execute(user);
        std::cout << "[Log] <- завершено
";
    }
private:
    std::unique_ptr<Service> inner_;
};

int main() {
    // Stack: Logging -> AccessProxy -> RealService
    auto chain = std::make_unique<LoggingDecorator>(
        std::make_unique<AccessProxy>(
            std::make_unique<RealService>(), "admin", "admin"));
    chain->execute("Алиса");

    auto denied = std::make_unique<LoggingDecorator>(
        std::make_unique<AccessProxy>(
            std::make_unique<RealService>(), "admin", "user"));
    denied->execute("Боб");
}
//17
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

struct Service {
    virtual void call() = 0;
    virtual ~Service() = default;
};

struct DatabaseService : Service {
    void call() override { std::cout << "[DB] Запрос
"; }
};
struct FileService : Service {
    void call() override { std::cout << "[File] Чтение
"; }
};
struct NetworkService : Service {
    void call() override { std::cout << "[Net] Запрос
"; }
};

struct LogProxy : Service {
    LogProxy(std::string name, std::unique_ptr<Service> s)
        : name_(std::move(name)), inner_(std::move(s)) {}

    void call() override {
        std::cout << "[Proxy:" << name_ << "] До
";
        inner_->call();
        std::cout << "[Proxy:" << name_ << "] После
";
    }
private:
    std::string name_;
    std::unique_ptr<Service> inner_;
};

struct ProxyFactory {
    static std::unique_ptr<Service> create(const std::string& type) {
        if (type == "database")
            return std::make_unique<LogProxy>(
                "DB", std::make_unique<DatabaseService>());
        if (type == "file")
            return std::make_unique<LogProxy>(
                "File", std::make_unique<FileService>());
        if (type == "network")
            return std::make_unique<LogProxy>(
                "Net", std::make_unique<NetworkService>());
        throw std::invalid_argument("Unknown type: " + type);
    }
};

int main() {
    auto db  = ProxyFactory::create("database");
    auto net = ProxyFactory::create("network");
    db->call();
    net->call();
}
//18
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

struct FSNode {
    virtual void remove(const std::string& user) = 0;
    virtual std::string name() const = 0;
    virtual ~FSNode() = default;
};

struct File : FSNode {
    explicit File(std::string n) : name_(std::move(n)) {}
    void remove(const std::string& user) override {
        std::cout << "[File] Удалён " << name_
                  << " пользователем " << user << "
";
    }
    std::string name() const override { return name_; }
private:
    std::string name_;
};

struct Folder : FSNode {
    explicit Folder(std::string n) : name_(std::move(n)) {}
    void add(std::shared_ptr<FSNode> node) {
        children_.push_back(std::move(node));
    }
    void remove(const std::string& user) override {
        for (auto& c : children_) c->remove(user);
    }
    std::string name() const override { return name_; }
private:
    std::string name_;
    std::vector<std::shared_ptr<FSNode>> children_;
};

struct ProtectedFolderProxy : FSNode {
    ProtectedFolderProxy(std::shared_ptr<Folder> f,
                         std::unordered_set<std::string> admins)
        : folder_(std::move(f)), admins_(std::move(admins)) {}

    void remove(const std::string& user) override {
        if (!admins_.count(user)) {
            std::cout << "[Protected] " << user
                      << " не может удалить папку " << folder_->name() << "
";
            return;
        }
        folder_->remove(user);
    }
    std::string name() const override { return folder_->name(); }
private:
    std::shared_ptr<Folder> folder_;
    std::unordered_set<std::string> admins_;
};

int main() {
    auto f1 = std::make_shared<File>("readme.md");
    auto f2 = std::make_shared<File>("secret.key");
    auto folder = std::make_shared<Folder>("config");
    folder->add(f1); folder->add(f2);

    ProtectedFolderProxy proxy(folder, {"root", "admin"});
    proxy.remove("bob");
    proxy.remove("root");
}
//19
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

// Задача 5 переработана с shared_ptr и weak_ptr
struct Calculator {
    virtual double compute(double x) = 0;
    virtual ~Calculator() = default;
};

struct ExpensiveCalculator : Calculator {
    double compute(double x) override {
        std::cout << "[Calc] Вычисление для x=" << x << "
";
        double result = 0;
        for (int i = 1; i <= 1000; ++i)
            result += x / i;
        return result;
    }
};

struct SharedCacheProxy : Calculator {
    // Разделяемый кеш между несколькими Proxy
    using Cache = std::unordered_map<double, double>;

    explicit SharedCacheProxy(std::shared_ptr<Cache> cache = nullptr)
        : real_(std::make_unique<ExpensiveCalculator>()),
          cache_(cache ? cache : std::make_shared<Cache>()) {}

    double compute(double x) override {
        if (auto it = cache_->find(x); it != cache_->end()) {
            std::cout << "[Cache] Хит для x=" << x << "
";
            return it->second;
        }
        double result = real_->compute(x);
        (*cache_)[x] = result;
        return result;
    }

    std::shared_ptr<Cache> sharedCache() { return cache_; }
private:
    std::unique_ptr<ExpensiveCalculator> real_;
    std::shared_ptr<Cache> cache_;
};

int main() {
    auto p1 = std::make_shared<SharedCacheProxy>();
    // p2 разделяет кеш с p1
    auto p2 = std::make_shared<SharedCacheProxy>(p1->sharedCache());

    p1->compute(3.14);
    p2->compute(3.14);  // кеш из p1!
    p2->compute(2.71);
    p1->compute(2.71);  // кеш из p2!
}
//20
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
#include <optional>

struct CloudStorage {
    virtual bool upload(const std::string& user,
                        const std::string& name,
                        const std::string& data) = 0;
    virtual std::optional<std::string>
        download(const std::string& user,
                 const std::string& name) = 0;
    virtual ~CloudStorage() = default;
};

struct RealCloudStorage : CloudStorage {
    bool upload(const std::string&,
                const std::string& name,
                const std::string& data) override {
        std::cout << "[Cloud] Загружен файл: " << name << "
";
        files_[name] = data;
        return true;
    }
    std::optional<std::string> download(
        const std::string&,
        const std::string& name) override {
        std::cout << "[Cloud] Скачивание: " << name << "
";
        auto it = files_.find(name);
        if (it != files_.end()) return it->second;
        return std::nullopt;
    }
private:
    std::unordered_map<std::string, std::string> files_;
};

struct CloudStorageProxy : CloudStorage {
    CloudStorageProxy(
        std::unordered_set<std::string> validTokens,
        size_t maxUploadBytes = 1024)
        : real_(std::make_unique<RealCloudStorage>()),
          tokens_(std::move(validTokens)),
          maxSize_(maxUploadBytes) {}

    bool upload(const std::string& user,
                const std::string& name,
                const std::string& data) override {
        log("UPLOAD", user, name);
        if (!tokens_.count(user)) {
            std::cout << "[Proxy] 401: неавторизован
";
            return false;
        }
        if (data.size() > maxSize_) {
            std::cout << "[Proxy] 413: файл слишком большой ("
                      << data.size() << " > " << maxSize_ << ")
";
            return false;
        }
        return real_->upload(user, name, data);
    }

    std::optional<std::string> download(
        const std::string& user,
        const std::string& name) override {
        log("DOWNLOAD", user, name);
        if (!tokens_.count(user)) {
            std::cout << "[Proxy] 401: неавторизован
";
            return std::nullopt;
        }
        // Ленивый кеш
        if (auto it = cache_.find(name); it != cache_.end()) {
            std::cout << "[Cache] Хит: " << name << "
";
            return it->second;
        }
        auto result = real_->download(user, name);
        if (result) cache_[name] = *result;
        return result;
    }

private:
    void log(const std::string& op,
             const std::string& user,
             const std::string& file) {
        std::cout << "[Log] " << op << " | user=" << user
                  << " | file=" << file << "
";
    }

    std::unique_ptr<RealCloudStorage> real_;
    std::unordered_set<std::string> tokens_;
    std::unordered_map<std::string, std::string> cache_;
    size_t maxSize_;
};

int main() {
    CloudStorageProxy storage({"alice-token","bob-token"}, 50);

    storage.upload("alice-token", "notes.txt", "Привет мир");
    storage.upload("hacker", "virus.exe", "...");
    storage.upload("bob-token", "big.bin", std::string(100, 'X'));

    storage.download("alice-token", "notes.txt");
    storage.download("alice-token", "notes.txt"); // кеш
    storage.download("unknown", "notes.txt");
}


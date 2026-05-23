//1
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Внутреннее состояние (разделяемое)
struct Flyweight {
    explicit Flyweight(std::string key) : key_(std::move(key)) {
        std::cout << "[Flyweight] Создан: " << key_ << "
";
    }
    void operation(const std::string& extrinsic) const {
        std::cout << "[FW:" << key_ << "] внешнее=" << extrinsic << "
";
    }
    const std::string& key() const { return key_; }
private:
    std::string key_; // внутреннее состояние
};

struct FlyweightFactory {
    std::shared_ptr<Flyweight> get(const std::string& key) {
        auto it = pool_.find(key);
        if (it != pool_.end()) return it->second;
        auto fw = std::make_shared<Flyweight>(key);
        pool_[key] = fw;
        return fw;
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> pool_;
};

// Контекст — хранит внешнее состояние + ссылку на flyweight
struct Context {
    Context(std::shared_ptr<Flyweight> fw, std::string ext)
        : fw_(std::move(fw)), ext_(std::move(ext)) {}
    void draw() const { fw_->operation(ext_); }
private:
    std::shared_ptr<Flyweight> fw_;
    std::string ext_;
};

int main() {
    FlyweightFactory factory;

    std::vector<Context> objects;
    for (auto& key : {"A","B","A","C","B","A"}) {
        objects.emplace_back(factory.get(key), "ctx-" + std::string(key));
    }

    for (auto& o : objects) o.draw();

    std::cout << "Flyweight-объектов в пуле: " << factory.count()
              << " (объектов всего: " << objects.size() << ")
";
}
//2
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Внутреннее (разделяемое): модель, цвет, двигатель
struct CarType {
    std::string model, color, engine;

    CarType(std::string m, std::string c, std::string e)
        : model(std::move(m)), color(std::move(c)), engine(std::move(e)) {}

    void info(double x, double y, double speed) const {
        std::cout << model << "/" << color << "/" << engine
                  << " @ (" << x << "," << y << ") v=" << speed << "
";
    }
};

struct CarTypeFactory {
    std::shared_ptr<CarType> get(const std::string& model,
                                  const std::string& color,
                                  const std::string& engine) {
        std::string key = model + "|" + color + "|" + engine;
        auto it = pool_.find(key);
        if (it != pool_.end()) return it->second;
        auto ct = std::make_shared<CarType>(model, color, engine);
        pool_[key] = ct;
        std::cout << "[Factory] Создан тип: " << key << "
";
        return ct;
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<CarType>> pool_;
};

// Контекст — хранит внешнее состояние: координаты, скорость
struct Car {
    Car(std::shared_ptr<CarType> type, double x, double y, double speed)
        : type_(std::move(type)), x_(x), y_(y), speed_(speed) {}

    void render() const { type_->info(x_, y_, speed_); }
    void move(double dx, double dy) { x_ += dx; y_ += dy; }
private:
    std::shared_ptr<CarType> type_; // внутреннее
    double x_, y_, speed_;          // внешнее
};

int main() {
    CarTypeFactory factory;
    auto t1 = factory.get("BMW", "red", "V8");
    auto t2 = factory.get("BMW", "red", "V8"); // переиспользование
    auto t3 = factory.get("Audi", "blue", "V6");

    std::vector<Car> cars;
    cars.emplace_back(t1, 0, 0, 60);
    cars.emplace_back(t2, 100, 50, 80);  // тот же тип!
    cars.emplace_back(t3, 200, 100, 90);

    for (auto& c : cars) c.render();
    std::cout << "Типов: " << factory.count()
              << ", машин: " << cars.size() << "
";
}
//3
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct Glyph {
    inline static int created = 0;

    explicit Glyph(std::string font, int size)
        : font_(std::move(font)), size_(size) {
        ++created;
        std::cout << "[Glyph] #" << created
                  << " создан: " << font_ << " " << size_ << "pt
";
    }
    void draw(char ch, int x, int y) const {
        std::cout << "'" << ch << "' [" << font_ << " " << size_
                  << "pt] @ (" << x << "," << y << ")
";
    }
    static int totalCreated() { return created; }
private:
    std::string font_;
    int size_;
};

struct GlyphFactory {
    std::shared_ptr<Glyph> get(const std::string& font, int size) {
        std::string key = font + std::to_string(size);
        auto it = cache_.find(key);
        if (it != cache_.end()) return it->second;
        auto g = std::make_shared<Glyph>(font, size);
        cache_[key] = g;
        return g;
    }
    int poolSize() const { return static_cast<int>(cache_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<Glyph>> cache_;
};

struct Character {
    Character(std::shared_ptr<Glyph> g, char ch, int x, int y)
        : glyph_(std::move(g)), ch_(ch), x_(x), y_(y) {}
    void render() const { glyph_->draw(ch_, x_, y_); }
private:
    std::shared_ptr<Glyph> glyph_;
    char ch_; int x_, y_;
};

int main() {
    GlyphFactory factory;
    std::vector<Character> text;

    // 10 символов, но только 2 уникальных стиля
    for (int i = 0; i < 5; ++i)
        text.emplace_back(factory.get("Arial", 12), 'A'+i, i*10, 0);
    for (int i = 0; i < 5; ++i)
        text.emplace_back(factory.get("Arial", 14), 'a'+i, i*10, 20);

    for (auto& c : text) c.render();

    std::cout << "
Создано flyweight: " << Glyph::totalCreated()
              << "
В пуле: " << factory.poolSize()
              << "
Символов: " << text.size() << "
";
}
//4
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct TextureData {
    explicit TextureData(std::string name) : name_(std::move(name)) {
        std::cout << "[Texture] Загружена: " << name_
                  << "  адрес: " << this << "
";
    }
    const std::string& name() const { return name_; }
private:
    std::string name_;
};

struct TextureFactory {
    std::shared_ptr<TextureData> get(const std::string& name) {
        auto it = pool_.find(name);
        if (it != pool_.end()) return it->second;
        auto t = std::make_shared<TextureData>(name);
        pool_[name] = t;
        return t;
    }
private:
    std::unordered_map<std::string,
                       std::shared_ptr<TextureData>> pool_;
};

int main() {
    TextureFactory factory;

    auto t1 = factory.get("grass.png");
    auto t2 = factory.get("water.png");
    auto t3 = factory.get("grass.png"); // должен переиспользоваться
    auto t4 = factory.get("grass.png"); // тоже

    std::cout << "
--- Адреса объектов ---
";
    std::cout << "t1 (grass): " << t1.get() << "
";
    std::cout << "t2 (water): " << t2.get() << "
";
    std::cout << "t3 (grass): " << t3.get() << "
";
    std::cout << "t4 (grass): " << t4.get() << "
";

    std::cout << "
t1 == t3? " << (t1.get() == t3.get() ? "ДА (переиспользован)" : "НЕТ") << "
";
    std::cout << "t1 == t4? " << (t1.get() == t4.get() ? "ДА (переиспользован)" : "НЕТ") << "
";
    std::cout << "t1 == t2? " << (t1.get() == t2.get() ? "ДА" : "НЕТ (разные)") << "
";
}
//5
#include <iostream>
#include <string>
#include <vector>

// ПЛОХО: всё состояние внутри каждого объекта
struct SoldierBad {
    // Одинаковые у всех — дублируются!
    std::string model   = "soldier_model_data_..."; // ~1 KB
    std::string texture = "soldier_texture_data_."; // ~4 KB
    std::string animation = "run_walk_attack_idle."; // ~2 KB
    // Уникальные
    float x, y, z;
    int health;
    SoldierBad(float x, float y, int hp) : x(x), y(y), z(0), health(hp) {}
};

// ХОРОШО: Flyweight разделяет общие данные
struct SoldierType {
    std::string model     = "soldier_model_data_..."; // ~1 KB
    std::string texture   = "soldier_texture_data_."; // ~4 KB
    std::string animation = "run_walk_attack_idle.";  // ~2 KB
};

struct SoldierGood {
    const SoldierType* type; // только указатель — 8 байт
    float x, y, z;
    int health;
    SoldierGood(const SoldierType* t, float x, float y, int hp)
        : type(t), x(x), y(y), z(0), health(hp) {}
};

int main() {
    const int N = 1000;

    // Плохой вариант
    size_t badSize = sizeof(SoldierBad) * N;
    std::cout << "=== Без Flyweight ===
";
    std::cout << "sizeof(SoldierBad) = " << sizeof(SoldierBad) << " байт
";
    std::cout << "1000 объектов = " << badSize / 1024 << " KB
";

    // Хороший вариант
    SoldierType sharedType; // один на всех
    size_t goodSize = sizeof(SoldierType) + sizeof(SoldierGood) * N;
    std::cout << "
=== С Flyweight ===
";
    std::cout << "sizeof(SoldierType) = " << sizeof(SoldierType) << " байт (один!)
";
    std::cout << "sizeof(SoldierGood) = " << sizeof(SoldierGood) << " байт
";
    std::cout << "1000 объектов = " << goodSize / 1024 << " KB
";

    std::cout << "
Экономия: ~" << (badSize - goodSize) / 1024 << " KB
";
    std::cout << "Коэффициент: "
              << static_cast<double>(badSize) / goodSize << "x
";
}
//6
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Flyweight: внутреннее состояние
struct TreeType {
    std::string name, texture, model;

    TreeType(std::string n, std::string tex, std::string mod)
        : name(std::move(n)), texture(std::move(tex)), model(std::move(mod)) {
        std::cout << "[TreeType] Создан: " << name << "
";
    }

    void draw(int x, int y, float height) const {
        std::cout << name << "[" << texture << "] @ ("
                  << x << "," << y << ") h=" << height << "
";
    }
};

struct TreeFactory {
    std::shared_ptr<TreeType> get(const std::string& name,
                                   const std::string& texture,
                                   const std::string& model) {
        auto it = pool_.find(name);
        if (it != pool_.end()) return it->second;
        auto t = std::make_shared<TreeType>(name, texture, model);
        pool_[name] = t;
        return t;
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> pool_;
};

// Context: внешнее состояние
struct Tree {
    Tree(std::shared_ptr<TreeType> type, int x, int y, float h)
        : type_(std::move(type)), x_(x), y_(y), height_(h) {}
    void draw() const { type_->draw(x_, y_, height_); }
private:
    std::shared_ptr<TreeType> type_;
    int x_, y_;
    float height_;
};

int main() {
    TreeFactory factory;
    std::vector<Tree> forest;

    // Создаём лес: 6 деревьев, 3 типа
    auto oak  = factory.get("Oak",  "oak_tex.png",  "oak.obj");
    auto pine = factory.get("Pine", "pine_tex.png", "pine.obj");
    auto birch= factory.get("Birch","birch_tex.png","birch.obj");

    for (int i = 0; i < 2; ++i) forest.emplace_back(oak,  i*10, i*5,  5.0f+i);
    for (int i = 0; i < 2; ++i) forest.emplace_back(pine, i*20, i*10, 8.0f+i);
    for (int i = 0; i < 2; ++i) forest.emplace_back(birch,i*15, i*7,  6.0f+i);

    for (auto& t : forest) t.draw();
    std::cout << "
Типов деревьев: " << factory.count()
              << ", деревьев в лесу: " << forest.size() << "
";
}
//7
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Flyweight: шрифт, размер, цвет
struct CharacterStyle {
    std::string font;
    int size;
    std::string color;

    CharacterStyle(std::string f, int s, std::string c)
        : font(std::move(f)), size(s), color(std::move(c)) {}

    void apply(char ch, int pos) const {
        std::cout << "'" << ch << "' [" << font << " "
                  << size << "pt " << color << "] pos=" << pos << "
";
    }
};

struct StyleFactory {
    std::shared_ptr<CharacterStyle> get(
            const std::string& font, int size,
            const std::string& color) {
        std::string key = font + std::to_string(size) + color;
        auto it = styles_.find(key);
        if (it != styles_.end()) return it->second;
        auto s = std::make_shared<CharacterStyle>(font, size, color);
        styles_[key] = s;
        std::cout << "[Style] Создан: " << key << "
";
        return s;
    }
    int count() const { return static_cast<int>(styles_.size()); }
private:
    std::unordered_map<std::string,
        std::shared_ptr<CharacterStyle>> styles_;
};

// Context: символ + позиция
struct Character {
    Character(std::shared_ptr<CharacterStyle> style,
              char ch, int pos)
        : style_(std::move(style)), ch_(ch), pos_(pos) {}
    void render() const { style_->apply(ch_, pos_); }
private:
    std::shared_ptr<CharacterStyle> style_;
    char ch_;
    int pos_;
};

int main() {
    StyleFactory factory;
    std::vector<Character> doc;

    auto normal = factory.get("Arial", 12, "black");
    auto bold   = factory.get("Arial", 14, "black");
    auto red    = factory.get("Arial", 12, "red");

    std::string text = "Hello";
    for (int i = 0; i < (int)text.size(); ++i) {
        auto style = (i % 3 == 0) ? bold : (i % 3 == 1) ? red : normal;
        doc.emplace_back(style, text[i], i);
    }

    for (auto& c : doc) c.render();
    std::cout << "
Стилей: " << factory.count()
              << ", символов: " << doc.size() << "
";
}
//8
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

struct TileType {
    std::string name, texture;
    bool passable;
    int moveCost;

    TileType(std::string n, std::string t, bool p, int c)
        : name(std::move(n)), texture(std::move(t)),
          passable(p), moveCost(c) {
        std::cout << "[TileType] Создан: " << name << "
";
    }

    void render(int x, int y) const {
        std::cout << name << "[" << texture << "] @ ("
                  << x << "," << y << ")"
                  << (passable ? "" : " BLOCKED") << "
";
    }
};

struct TileFactory {
    std::shared_ptr<TileType> get(const std::string& name) {
        auto it = pool_.find(name);
        if (it != pool_.end()) return it->second;
        if (name == "grass")
            return pool_[name] = std::make_shared<TileType>(
                "grass","grass.png", true, 1);
        if (name == "water")
            return pool_[name] = std::make_shared<TileType>(
                "water","water.png", false, 99);
        if (name == "sand")
            return pool_[name] = std::make_shared<TileType>(
                "sand","sand.png",  true, 2);
        return pool_[name] = std::make_shared<TileType>(
                "stone","stone.png", true, 3);
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<TileType>> pool_;
};

struct Tile {
    Tile(std::shared_ptr<TileType> type, int x, int y)
        : type_(std::move(type)), x_(x), y_(y) {}
    void render() const { type_->render(x_, y_); }
private:
    std::shared_ptr<TileType> type_;
    int x_, y_;
};

int main() {
    TileFactory factory;
    // Карта 4x4
    std::vector<std::string> layout = {
        "grass","water","grass","sand",
        "water","grass","stone","grass",
        "sand","stone","grass","water",
        "grass","grass","sand","grass"
    };
    std::vector<Tile> map;
    for (int i = 0; i < (int)layout.size(); ++i)
        map.emplace_back(factory.get(layout[i]), i%4, i/4);

    for (auto& t : map) t.render();
    std::cout << "
Типов тайлов: " << factory.count()
              << ", тайлов: " << map.size() << "
";
}
//9
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Flyweight: текстура, тип эффекта
struct ParticleType {
    std::string texture, effect;

    ParticleType(std::string t, std::string e)
        : texture(std::move(t)), effect(std::move(e)) {
        std::cout << "[ParticleType] Создан: " << effect << "
";
    }
    void render(float x, float y, float vx, float vy, float life) const {
        std::cout << effect << "[" << texture << "] @ ("
                  << x << "," << y << ") v=(" << vx << "," << vy
                  << ") life=" << life << "
";
    }
};

struct ParticleFactory {
    std::shared_ptr<ParticleType> get(const std::string& tex,
                                       const std::string& effect) {
        std::string key = tex + "|" + effect;
        auto it = pool_.find(key);
        if (it != pool_.end()) return it->second;
        auto p = std::make_shared<ParticleType>(tex, effect);
        pool_[key] = p;
        return p;
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<ParticleType>> pool_;
};

// Context: внешнее состояние
struct Particle {
    Particle(std::shared_ptr<ParticleType> type,
             float x, float y, float vx, float vy, float life)
        : type_(std::move(type)),
          x_(x), y_(y), vx_(vx), vy_(vy), life_(life) {}

    void update(float dt) {
        x_ += vx_ * dt;
        y_ += vy_ * dt;
        life_ -= dt;
    }
    bool alive() const { return life_ > 0; }
    void render() const { type_->render(x_, y_, vx_, vy_, life_); }
private:
    std::shared_ptr<ParticleType> type_;
    float x_, y_, vx_, vy_, life_;
};

int main() {
    ParticleFactory factory;
    std::vector<Particle> particles;

    auto fire  = factory.get("fire.png",  "fire");
    auto smoke = factory.get("smoke.png", "smoke");
    auto spark = factory.get("spark.png", "spark");

    for (int i = 0; i < 3; ++i)
        particles.emplace_back(fire,  (float)i, 0.f, 0.1f, 0.5f, 2.0f-i*0.3f);
    for (int i = 0; i < 2; ++i)
        particles.emplace_back(smoke, (float)i, 1.f, -0.1f,0.3f, 3.0f-i*0.5f);
    particles.emplace_back(spark, 1.f, 0.5f, 0.8f, 0.2f, 0.5f);

    for (auto& p : particles) p.render();
    std::cout << "
Типов частиц: " << factory.count()
              << ", частиц: " << particles.size() << "
";
}
//10
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Flyweight: иконка (разделяется между всеми кнопками)
struct Icon {
    std::string name, imagePath;
    int width, height;

    Icon(std::string n, std::string path, int w, int h)
        : name(std::move(n)), imagePath(std::move(path)),
          width(w), height(h) {
        std::cout << "[Icon] Загружена: " << name << " "
                  << width << "x" << height << "
";
    }
    void draw(int x, int y) const {
        std::cout << "[Icon:" << name << "] @ (" << x << "," << y << ")
";
    }
};

struct IconFactory {
    std::shared_ptr<Icon> get(const std::string& name,
                               const std::string& path,
                               int w = 32, int h = 32) {
        auto it = icons_.find(name);
        if (it != icons_.end()) return it->second;
        auto icon = std::make_shared<Icon>(name, path, w, h);
        icons_[name] = icon;
        return icon;
    }
    int count() const { return static_cast<int>(icons_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<Icon>> icons_;
};

// Context: кнопка
struct Button {
    Button(std::shared_ptr<Icon> icon,
           std::string label, int x, int y)
        : icon_(std::move(icon)),
          label_(std::move(label)), x_(x), y_(y) {}

    void render() const {
        icon_->draw(x_, y_);
        std::cout << "  [Button: " << label_ << "]
";
    }
    const void* iconPtr() const { return icon_.get(); }
private:
    std::shared_ptr<Icon> icon_;
    std::string label_;
    int x_, y_;
};

int main() {
    IconFactory factory;
    std::vector<Button> toolbar;

    auto save  = factory.get("save",  "icons/save.png");
    auto open  = factory.get("open",  "icons/open.png");
    auto close = factory.get("close", "icons/close.png");

    // Несколько кнопок с одинаковой иконкой
    toolbar.emplace_back(save,  "Save",     10,  10);
    toolbar.emplace_back(save,  "Save As",  50,  10);
    toolbar.emplace_back(open,  "Open",     90,  10);
    toolbar.emplace_back(close, "Close",    130, 10);
    toolbar.emplace_back(close, "Close All",170, 10);

    for (auto& b : toolbar) b.render();

    std::cout << "
Иконок в памяти: " << factory.count()
              << ", кнопок: " << toolbar.size() << "
";
    std::cout << "Save кнопки одна иконка? "
              << (toolbar[0].iconPtr() == toolbar[1].iconPtr()
                  ? "ДА" : "НЕТ") << "
";
}
//11
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

struct Mesh {
    std::string name;
    std::vector<float> vertices; // имитируем геометрию

    explicit Mesh(const std::string& n) : name(n) {
        std::cout << "[GPU] Загрузка модели: " << n << "... ";
        // Имитация загрузки
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        vertices.resize(1000, 0.0f); // ~4 KB условно
        std::cout << "OK
";
    }
};

struct ModelCache {
    std::shared_ptr<Mesh> load(const std::string& name) {
        auto it = cache_.find(name);
        if (it != cache_.end()) {
            hits_++;
            std::cout << "[Cache] HIT: " << name << "
";
            return it->second;
        }
        misses_++;
        auto mesh = std::make_shared<Mesh>(name);
        cache_[name] = mesh;
        return mesh;
    }

    void stats() const {
        std::cout << "
--- Статистика ---
"
                  << "В кеше: " << cache_.size() << " моделей
"
                  << "Попаданий: " << hits_ << "
"
                  << "Промахов: "  << misses_ << "
";
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> cache_;
    int hits_ = 0, misses_ = 0;
};

struct SceneObject {
    SceneObject(std::shared_ptr<Mesh> mesh, float x, float y, float z)
        : mesh_(std::move(mesh)), x_(x), y_(y), z_(z) {}
    void render() const {
        std::cout << "[Render] " << mesh_->name
                  << " @ (" << x_ << "," << y_ << "," << z_ << ")
";
    }
private:
    std::shared_ptr<Mesh> mesh_;
    float x_, y_, z_;
};

int main() {
    ModelCache cache;
    std::vector<SceneObject> scene;

    for (auto& name : {"tree.obj","rock.obj","tree.obj",
                        "grass.obj","rock.obj","tree.obj"}) {
        scene.emplace_back(cache.load(name),
                           (float)(rand()%100),
                           0.f,
                           (float)(rand()%100));
    }

    for (auto& o : scene) o.render();
    cache.stats();
}
//12
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

struct Mesh {
    std::string name;
    std::vector<float> vertices; // имитируем геометрию

    explicit Mesh(const std::string& n) : name(n) {
        std::cout << "[GPU] Загрузка модели: " << n << "... ";
        // Имитация загрузки
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        vertices.resize(1000, 0.0f); // ~4 KB условно
        std::cout << "OK
";
    }
};

struct ModelCache {
    std::shared_ptr<Mesh> load(const std::string& name) {
        auto it = cache_.find(name);
        if (it != cache_.end()) {
            hits_++;
            std::cout << "[Cache] HIT: " << name << "
";
            return it->second;
        }
        misses_++;
        auto mesh = std::make_shared<Mesh>(name);
        cache_[name] = mesh;
        return mesh;
    }

    void stats() const {
        std::cout << "
--- Статистика ---
"
                  << "В кеше: " << cache_.size() << " моделей
"
                  << "Попаданий: " << hits_ << "
"
                  << "Промахов: "  << misses_ << "
";
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> cache_;
    int hits_ = 0, misses_ = 0;
};

struct SceneObject {
    SceneObject(std::shared_ptr<Mesh> mesh, float x, float y, float z)
        : mesh_(std::move(mesh)), x_(x), y_(y), z_(z) {}
    void render() const {
        std::cout << "[Render] " << mesh_->name
                  << " @ (" << x_ << "," << y_ << "," << z_ << ")
";
    }
private:
    std::shared_ptr<Mesh> mesh_;
    float x_, y_, z_;
};

int main() {
    ModelCache cache;
    std::vector<SceneObject> scene;

    for (auto& name : {"tree.obj","rock.obj","tree.obj",
                        "grass.obj","rock.obj","tree.obj"}) {
        scene.emplace_back(cache.load(name),
                           (float)(rand()%100),
                           0.f,
                           (float)(rand()%100));
    }

    for (auto& o : scene) o.render();
    cache.stats();
}
//13
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

struct Material {
    std::string name, shader;
    float roughness, metallic;

    Material(std::string n, std::string s, float r, float m)
        : name(std::move(n)), shader(std::move(s)),
          roughness(r), metallic(m) {
        std::cout << "[Material] Создан: " << name << "
";
    }
};

// Хранилище flyweight-объектов через несколько STL-контейнеров
struct MaterialLibrary {
    // unordered_map для быстрого поиска по имени
    std::unordered_map<std::string, std::shared_ptr<Material>> byName;
    // map для упорядоченного перебора
    std::map<float, std::vector<std::shared_ptr<Material>>> byRoughness;

    std::shared_ptr<Material> get(const std::string& name,
                                   const std::string& shader,
                                   float roughness, float metallic) {
        auto it = byName.find(name);
        if (it != byName.end()) return it->second;

        auto mat = std::make_shared<Material>(name, shader, roughness, metallic);
        byName[name] = mat;
        byRoughness[roughness].push_back(mat);
        return mat;
    }

    void printByRoughness() const {
        std::cout << "
--- Материалы по roughness ---
";
        for (auto& [r, mats] : byRoughness) {
            for (auto& m : mats)
                std::cout << "  r=" << r << " " << m->name << "
";
        }
    }
};

struct Mesh {
    std::shared_ptr<Material> material;
    float x, y, z;
    Mesh(std::shared_ptr<Material> m, float x, float y, float z)
        : material(std::move(m)), x(x), y(y), z(z) {}
};

int main() {
    MaterialLibrary lib;

    auto metal  = lib.get("Metal",  "pbr", 0.2f, 0.9f);
    auto wood   = lib.get("Wood",   "pbr", 0.8f, 0.0f);
    auto glass  = lib.get("Glass",  "pbr", 0.1f, 0.0f);
    auto metal2 = lib.get("Metal",  "pbr", 0.2f, 0.9f); // переиспользование

    std::vector<Mesh> scene;
    for (int i = 0; i < 4; ++i) scene.emplace_back(metal, (float)i, 0, 0);
    for (int i = 0; i < 3; ++i) scene.emplace_back(wood,  (float)i, 1, 0);
    for (int i = 0; i < 2; ++i) scene.emplace_back(glass, (float)i, 2, 0);

    lib.printByRoughness();
    std::cout << "Материалов: " << lib.byName.size()
              << ", мешей: " << scene.size() << "
";
    std::cout << "metal == metal2? "
              << (metal.get() == metal2.get() ? "ДА" : "НЕТ") << "
";
}
//14
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

struct Material {
    std::string name, shader;
    float roughness, metallic;

    Material(std::string n, std::string s, float r, float m)
        : name(std::move(n)), shader(std::move(s)),
          roughness(r), metallic(m) {
        std::cout << "[Material] Создан: " << name << "
";
    }
};

// Хранилище flyweight-объектов через несколько STL-контейнеров
struct MaterialLibrary {
    // unordered_map для быстрого поиска по имени
    std::unordered_map<std::string, std::shared_ptr<Material>> byName;
    // map для упорядоченного перебора
    std::map<float, std::vector<std::shared_ptr<Material>>> byRoughness;

    std::shared_ptr<Material> get(const std::string& name,
                                   const std::string& shader,
                                   float roughness, float metallic) {
        auto it = byName.find(name);
        if (it != byName.end()) return it->second;

        auto mat = std::make_shared<Material>(name, shader, roughness, metallic);
        byName[name] = mat;
        byRoughness[roughness].push_back(mat);
        return mat;
    }

    void printByRoughness() const {
        std::cout << "
--- Материалы по roughness ---
";
        for (auto& [r, mats] : byRoughness) {
            for (auto& m : mats)
                std::cout << "  r=" << r << " " << m->name << "
";
        }
    }
};

struct Mesh {
    std::shared_ptr<Material> material;
    float x, y, z;
    Mesh(std::shared_ptr<Material> m, float x, float y, float z)
        : material(std::move(m)), x(x), y(y), z(z) {}
};

int main() {
    MaterialLibrary lib;

    auto metal  = lib.get("Metal",  "pbr", 0.2f, 0.9f);
    auto wood   = lib.get("Wood",   "pbr", 0.8f, 0.0f);
    auto glass  = lib.get("Glass",  "pbr", 0.1f, 0.0f);
    auto metal2 = lib.get("Metal",  "pbr", 0.2f, 0.9f); // переиспользование

    std::vector<Mesh> scene;
    for (int i = 0; i < 4; ++i) scene.emplace_back(metal, (float)i, 0, 0);
    for (int i = 0; i < 3; ++i) scene.emplace_back(wood,  (float)i, 1, 0);
    for (int i = 0; i < 2; ++i) scene.emplace_back(glass, (float)i, 2, 0);

    lib.printByRoughness();
    std::cout << "Материалов: " << lib.byName.size()
              << ", мешей: " << scene.size() << "
";
    std::cout << "metal == metal2? "
              << (metal.get() == metal2.get() ? "ДА" : "НЕТ") << "
";
}
//15
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// ВАЖНО: Flyweight должен быть НЕИЗМЕНЯЕМЫМ (immutable)!

struct BulletType {
    std::string name;
    mutable float damage; // ОПАСНО: mutable в flyweight!
    std::string texture;

    BulletType(std::string n, float d, std::string t)
        : name(std::move(n)), damage(d), texture(std::move(t)) {}
};

struct BulletFactory {
    std::shared_ptr<BulletType> get(const std::string& name,
                                     float damage,
                                     const std::string& tex) {
        auto it = pool_.find(name);
        if (it != pool_.end()) return it->second;
        auto bt = std::make_shared<BulletType>(name, damage, tex);
        pool_[name] = bt;
        return bt;
    }
private:
    std::unordered_map<std::string, std::shared_ptr<BulletType>> pool_;
};

struct Bullet {
    std::shared_ptr<BulletType> type;
    float x, y, vx, vy;
    void show() const {
        std::cout << type->name << " dmg=" << type->damage
                  << " @ (" << x << "," << y << ")
";
    }
};

int main() {
    BulletFactory factory;
    auto pistolType = factory.get("Pistol", 25.f, "bullet.png");

    std::vector<Bullet> bullets;
    for (int i = 0; i < 5; ++i)
        bullets.push_back({pistolType, (float)i, 0, 1, 0});

    std::cout << "=== До изменения ===
";
    for (auto& b : bullets) b.show();

    // ОШИБКА: изменяем общий flyweight-объект!
    std::cout << "
[!] Меняем damage через одну пулю...
";
    bullets[0].type->damage = 999.f; // ЛОМАЕТ ВСЕ ПУЛИ!

    std::cout << "
=== После изменения (все поломаны!) ===
";
    for (auto& b : bullets) b.show();

    std::cout << "
=== Правильное решение ===
";
    std::cout << "damage - это ВНЕШНЕЕ состояние пули,
"
              << "его нужно хранить в Context (Bullet),
"
              << "а не в Flyweight (BulletType)!
";
}
//16
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct Texture {
    std::string name, path;
    explicit Texture(std::string n, std::string p)
        : name(std::move(n)), path(std::move(p)) {
        std::cout << "[Texture] Загружена: " << name << "
";
    }
};

// Абстрактная фабрика flyweight
struct TextureFactory {
    virtual ~TextureFactory() = default;
    virtual std::shared_ptr<Texture> create(const std::string& name) = 0;

    std::shared_ptr<Texture> get(const std::string& name) {
        auto it = pool_.find(name);
        if (it != pool_.end()) {
            std::cout << "[Pool] HIT: " << name << "
";
            return it->second;
        }
        auto t = create(name);
        pool_[name] = t;
        return t;
    }
    int count() const { return static_cast<int>(pool_.size()); }
protected:
    std::unordered_map<std::string, std::shared_ptr<Texture>> pool_;
};

// Конкретная фабрика — Factory Method
struct DiskTextureFactory : TextureFactory {
    std::shared_ptr<Texture> create(const std::string& name) override {
        return std::make_shared<Texture>(name, "/textures/" + name);
    }
};

struct NetworkTextureFactory : TextureFactory {
    std::shared_ptr<Texture> create(const std::string& name) override {
        return std::make_shared<Texture>(name, "http://cdn.game.io/" + name);
    }
};

struct Sprite {
    std::shared_ptr<Texture> tex;
    float x, y;
    void draw() const {
        std::cout << "[Sprite] " << tex->name
                  << " @ (" << x << "," << y << ")
";
    }
};

int main() {
    DiskTextureFactory factory;

    std::vector<Sprite> scene;
    for (auto& name : {"hero.png","enemy.png","hero.png",
                        "tree.png","enemy.png","hero.png"}) {
        scene.push_back({factory.get(name),
                         (float)(rand()%200), (float)(rand()%200)});
    }

    for (auto& s : scene) s.draw();
    std::cout << "
Текстур в пуле: " << factory.count()
              << ", спрайтов: " << scene.size() << "
";
}
//17
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct TextureData {
    std::string name;
    std::vector<uint8_t> pixels; // имитация данных

    explicit TextureData(const std::string& n) : name(n) {
        std::cout << "[GPU] Загрузка текстуры: " << n << "
";
        pixels.resize(1024, 255); // имитируем 1 KB
    }
    void bind() const {
        std::cout << "[GPU] Bind: " << name << "
";
    }
};

// Proxy: ленивая загрузка
struct LazyTextureProxy {
    explicit LazyTextureProxy(std::string name)
        : name_(std::move(name)) {}

    void bind() {
        if (!data_) {
            data_ = std::make_shared<TextureData>(name_);
        }
        data_->bind();
    }

    bool loaded() const { return data_ != nullptr; }
    std::shared_ptr<TextureData> getData() { bind(); return data_; }
    const std::string& name() const { return name_; }
private:
    std::string name_;
    std::shared_ptr<TextureData> data_;
};

// Flyweight Factory: переиспользует уже загруженные Proxy
struct TextureManager {
    std::shared_ptr<LazyTextureProxy> get(const std::string& name) {
        auto it = proxies_.find(name);
        if (it != proxies_.end()) {
            std::cout << "[FW] Переиспользован proxy: " << name << "
";
            return it->second;
        }
        auto proxy = std::make_shared<LazyTextureProxy>(name);
        proxies_[name] = proxy;
        std::cout << "[FW] Создан proxy: " << name
                  << " (не загружен пока)
";
        return proxy;
    }
    int count() const { return static_cast<int>(proxies_.size()); }
private:
    std::unordered_map<std::string,
        std::shared_ptr<LazyTextureProxy>> proxies_;
};

struct Mesh {
    std::shared_ptr<LazyTextureProxy> texture;
    float x, y;
    void render() {
        std::cout << "[Mesh] @ (" << x << "," << y << ") -> ";
        texture->bind();
    }
};

int main() {
    TextureManager mgr;

    // Proxy создаётся без загрузки
    auto t1 = mgr.get("rock.png");
    auto t2 = mgr.get("grass.png");
    auto t3 = mgr.get("rock.png"); // flyweight: тот же proxy

    std::cout << "
--- Рендеринг ---
";
    std::vector<Mesh> scene = {
        {t1, 0, 0}, {t2, 5, 0}, {t3, 10, 0}, {t1, 15, 0}
    };
    for (auto& m : scene) m.render();

    std::cout << "
Proxy в менеджере: " << mgr.count()
              << ", мешей: " << scene.size() << "
";
    std::cout << "rock.png загружена? "
              << (t1->loaded() ? "ДА" : "НЕТ") << "
";
}
//18
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Flyweight
struct MeshData {
    std::string name;
    std::vector<float> verts;
    explicit MeshData(std::string n) : name(std::move(n)) {
        verts.resize(300, 0.f);
        std::cout << "[Mesh] Загружен: " << name << "
";
    }
};

struct MeshFactory {
    std::shared_ptr<MeshData> get(const std::string& name) {
        auto it = pool_.find(name);
        if (it != pool_.end()) return it->second;
        auto m = std::make_shared<MeshData>(name);
        pool_[name] = m;
        return m;
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<MeshData>> pool_;
};

// Composite
struct SceneNode {
    virtual void render(int depth = 0) const = 0;
    virtual ~SceneNode() = default;
};

struct Object3D : SceneNode {
    Object3D(std::shared_ptr<MeshData> mesh, float x, float y)
        : mesh_(std::move(mesh)), x_(x), y_(y) {}

    void render(int depth = 0) const override {
        std::string pad(depth * 2, ' ');
        std::cout << pad << "[Obj] " << mesh_->name
                  << " @ (" << x_ << "," << y_ << ")
";
    }
private:
    std::shared_ptr<MeshData> mesh_;
    float x_, y_;
};

struct Group : SceneNode {
    std::string name;
    std::vector<std::shared_ptr<SceneNode>> children;

    explicit Group(std::string n) : name(std::move(n)) {}

    void add(std::shared_ptr<SceneNode> node) {
        children.push_back(std::move(node));
    }
    void render(int depth = 0) const override {
        std::string pad(depth * 2, ' ');
        std::cout << pad << "[Group: " << name << "]
";
        for (auto& c : children) c->render(depth + 1);
    }
};

int main() {
    MeshFactory factory;

    auto treeMesh = factory.get("tree.obj");
    auto rockMesh = factory.get("rock.obj");
    auto grassMesh= factory.get("grass.obj");

    auto scene = std::make_shared<Group>("Scene");

    auto forest = std::make_shared<Group>("Forest");
    for (int i = 0; i < 3; ++i)
        forest->add(std::make_shared<Object3D>(
            treeMesh, (float)i*5, 0));

    auto rocks = std::make_shared<Group>("Rocks");
    for (int i = 0; i < 2; ++i)
        rocks->add(std::make_shared<Object3D>(
            rockMesh, (float)i*3, 2));

    scene->add(forest);
    scene->add(rocks);
    scene->add(std::make_shared<Object3D>(grassMesh, 0, 5));

    scene->render();
    std::cout << "
Flyweight-мешей: " << factory.count()
              << ", всего объектов: 6
";
}
//19
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

// Задача 6 (игровой лес) переработана с shared_ptr/weak_ptr
// weak_ptr позволяет автоматически удалять неиспользуемые типы

struct TreeType {
    std::string name, texture, model;

    TreeType(std::string n, std::string t, std::string m)
        : name(std::move(n)), texture(std::move(t)), model(std::move(m)) {
        std::cout << "[TreeType] Создан: " << name << "
";
    }
    ~TreeType() {
        std::cout << "[TreeType] Удалён: " << name << "
";
    }
    void draw(int x, int y, float h) const {
        std::cout << name << " @ (" << x << "," << y << ") h=" << h << "
";
    }
};

// Фабрика с weak_ptr: автоматически удаляет неиспользуемые типы
struct WeakTreeFactory {
    std::shared_ptr<TreeType> get(const std::string& name,
                                   const std::string& texture,
                                   const std::string& model) {
        auto it = pool_.find(name);
        if (it != pool_.end()) {
            if (auto sp = it->second.lock()) {
                std::cout << "[Factory] Переиспользован: " << name << "
";
                return sp;
            }
        }
        auto t = std::make_shared<TreeType>(name, texture, model);
        pool_[name] = t; // слабая ссылка — не удерживает
        return t;
    }

    void cleanup() {
        for (auto it = pool_.begin(); it != pool_.end();) {
            if (it->second.expired()) {
                std::cout << "[Factory] Очистка: " << it->first << "
";
                it = pool_.erase(it);
            } else ++it;
        }
    }

    int activeCount() const {
        int n = 0;
        for (auto& [k, w] : pool_) if (!w.expired()) ++n;
        return n;
    }
private:
    std::unordered_map<std::string, std::weak_ptr<TreeType>> pool_;
};

struct Tree {
    std::shared_ptr<TreeType> type;
    int x, y; float height;
    void draw() const { type->draw(x, y, height); }
};

int main() {
    WeakTreeFactory factory;

    std::cout << "=== Создаём лес ===
";
    {
        auto oak  = factory.get("Oak",  "oak.png",  "oak.obj");
        auto pine = factory.get("Pine", "pine.png", "pine.obj");

        std::vector<Tree> forest = {
            {factory.get("Oak","oak.png","oak.obj"),  0,0,5.f},
            {pine, 10,0,8.f},
            {factory.get("Oak","oak.png","oak.obj"), 20,0,6.f}
        };
        for (auto& t : forest) t.draw();
        std::cout << "Активных типов: " << factory.activeCount() << "
";
    }
    // oak и pine вышли из scope — shared_ptr обнулены если нет forest
    std::cout << "
=== После scope ===
";
    factory.cleanup();
    std::cout << "Активных типов: " << factory.activeCount() << "
";
}
//20
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iomanip>

// ===== Flyweight: разделяемые ресурсы =====
struct GameResource {
    std::string model, texture, animation, sound;

    GameResource(std::string m, std::string t,
                 std::string a, std::string s)
        : model(std::move(m)), texture(std::move(t)),
          animation(std::move(a)), sound(std::move(s)) {
        std::cout << "[Resource] Загружен: " << model << "
";
    }

    void render(float x, float y, float dir, int hp) const {
        std::cout << std::fixed << std::setprecision(1)
                  << model << " @ (" << x << "," << y << ")"
                  << " dir=" << dir << " hp=" << hp << "
";
    }
};

// ===== Фабрика ресурсов =====
struct ResourceFactory {
    std::shared_ptr<GameResource> get(const std::string& type) {
        auto it = pool_.find(type);
        if (it != pool_.end()) return it->second;

        std::shared_ptr<GameResource> r;
        if (type == "Tree")
            r = std::make_shared<GameResource>(
                "tree.fbx","tree_diffuse.png","sway.anim","wind.wav");
        else if (type == "Rock")
            r = std::make_shared<GameResource>(
                "rock.fbx","rock_normal.png","idle.anim","none");
        else if (type == "Grass")
            r = std::make_shared<GameResource>(
                "grass.fbx","grass_ao.png","wind.anim","rustle.wav");
        else // NPC
            r = std::make_shared<GameResource>(
                "npc.fbx","npc_skin.png","walk.anim","voice.wav");

        pool_[type] = r;
        return r;
    }
    int count() const { return static_cast<int>(pool_.size()); }
private:
    std::unordered_map<std::string, std::shared_ptr<GameResource>> pool_;
};

// ===== Context: уникальное состояние объекта =====
struct WorldObject {
    WorldObject(std::shared_ptr<GameResource> res,
                float x, float y, float dir,
                int hp, std::string state)
        : resource_(std::move(res)),
          x_(x), y_(y), dir_(dir),
          hp_(hp), state_(std::move(state)) {}

    void update(float dx, float dy) { x_ += dx; y_ += dy; }
    void takeDamage(int dmg) { hp_ = std::max(0, hp_ - dmg); }

    void render() const { resource_->render(x_, y_, dir_, hp_); }

    bool alive() const { return hp_ > 0; }
private:
    std::shared_ptr<GameResource> resource_; // flyweight
    // внешнее состояние:
    float x_, y_, dir_;
    int hp_;
    std::string state_;
};

int main() {
    ResourceFactory factory;
    std::vector<WorldObject> world;
    world.reserve(1000);

    const std::vector<std::string> types = {"Tree","Rock","Grass","NPC"};
    const std::vector<int> hpMap = {100, 200, 50, 150};

    for (int i = 0; i < 1000; ++i) {
        int idx = i % 4;
        world.emplace_back(
            factory.get(types[idx]),
            (float)(rand() % 500),
            (float)(rand() % 500),
            (float)(rand() % 360),
            hpMap[idx],
            "idle"
        );
    }

    // Симуляция нескольких кадров
    for (auto& obj : world) obj.update(0.1f, 0.05f);
    world[5].takeDamage(50);

    // Вывести первые 5
    std::cout << "=== Первые 5 объектов ===
";
    for (int i = 0; i < 5; ++i) world[i].render();

    // Статистика
    std::cout << "
=== Статистика ===
";
    std::cout << "Игровых объектов: " << world.size() << "
";
    std::cout << "Flyweight-ресурсов: " << factory.count() << "
";

    size_t withFW = sizeof(WorldObject) * world.size()
                  + sizeof(GameResource) * factory.count();
    size_t withoutFW = (sizeof(GameResource) + 32) * world.size();
    std::cout << "Память с Flyweight:    "
              << withFW / 1024 << " KB
";
    std::cout << "Память без Flyweight: ~"
              << withoutFW / 1024 << " KB
";
    std::cout << "Экономия: ~"
              << (withoutFW - withFW) / 1024 << " KB
";
}

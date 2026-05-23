//1
#include <iostream>
#include <string>

class Enemy {
private:
    int hp;
    int damage;
    float speed;
public:
    Enemy(int h, int d, float s) : hp(h), damage(d), speed(s) {}

    Enemy* clone() const {
        return new Enemy(hp, damage, speed);
    }

    void print() const {
        std::cout << "Enemy: HP=" << hp << ", Damage=" << damage << ", Speed=" << speed << "\n";
    }

    friend class EnemyFactory;
};

int main() {
    Enemy original(100, 20, 5.0f);

    Enemy* copy1 = original.clone();
    Enemy* copy2 = original.clone();
    Enemy* copy3 = original.clone();

    copy1->print();
    copy2->print();
    copy3->print();

    delete copy1;
    delete copy2;
    delete copy3;
    return 0;
}
//2
int main() {
    Enemy original(100, 20, 5.0f);
    Enemy* copy = original.clone();

    copy->hp = 50; 

    std::cout << "Original: ";
    original.print(); 
    std::cout << "Copy: ";
    copy->print();  

    delete copy;
    return 0;
}
//3
class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual ~Prototype() = default;
};

class Enemy : public Prototype {
    // реализация clone()
};
//
class Enemy {
public:
    Enemy* clone() const { /* простая реализация */ }
};
//4
class Weapon {
private:
    std::string name;
    int damage;
    double price;
public:
    Weapon(const std::string& n, int d, double p)
        : name(n), damage(d), price(p) {}

    Weapon* clone() const {
        return new Weapon(name, damage, price);
    }

    void setDamage(int d) { damage = d; }
    void setPrice(double p) { price = p; }
    void setName(const std::string& n) { name = n; }

    void print() const {
        std::cout << name << ": " << damage << " dmg, $" << price << "\n";
    }
};

int main() {
    Weapon legendarySword("Legendary Sword", 100, 1000.0);

    for (int i = 0; i < 5; ++i) {
        Weapon* copy = legendarySword.clone();
        copy->setDamage(100 + i * 10);
        copy->setPrice(1000 + i * 50);
        copy->setName("Copy Sword #" + std::to_string(i + 1));
        copy->print();
        delete copy;
    }
    return 0;
}
//5
class NPC {
private:
    std::string name;
    int level;
    std::string faction;
public:
    NPC(const std::string& n, int l, const std::string& f)
        : name(n), level(l), faction(f) {}

    NPC* clone() const {
        return new NPC(name, level, faction);
    }

    void print() const {
        std::cout << name << " (Lv" << level << ") - " << faction << "\n";
    }
};

int main() {
    NPC templateNPC("Guard", 5, "City Guard");
    std::vector<NPC*> army;

    for (int i = 0; i < 10; ++i) {
        NPC* soldier = templateNPC.clone();
        soldier->name = "Guard #" + std::to_string(i + 1);
        army.push_back(soldier);
    }

    for (auto npc : army) {
        npc->print();
        delete npc;
    }
    return 0;
}
//6
class ShallowCopy {
private:
    int* data;
public:
    ShallowCopy(int value) {
        data = new int(value);
    }

    ShallowCopy* clone() const {
        return new ShallowCopy(*this); 
    }

    ~ShallowCopy() { delete data; }
};
//7
class DeepCopy {
private:
    int* data;
public:
    DeepCopy(int value) : data(new int(value)) {}

    DeepCopy(const DeepCopy& other) {
        data = new int(*other.data);
    }

    DeepCopy* clone() const override {
        return new DeepCopy(*this);
    }

    ~DeepCopy() { delete data; }
};
//8
class Character {
private:
    std::string name;
    std::vector<std::string> inventory;
public:
    Character(const std::string& n) : name(n) {}

    void addItem(const std::string& item) {
        inventory.push_back(item);
    }

    Character* clone() const {
        Character* copy = new Character(name);
        copy->inventory = inventory; // vector автоматически делает deep copy
        return copy;
    }

    void printInventory() const {
        std::cout << name << "'s inventory: ";
        for (const auto& item : inventory) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
};

//9
class Weapon {
private:
    std::string type;
    int damage;
public:
    Weapon(const std::string& t, int d) : type(t), damage(d) {}
    Weapon* clone() const { return new Weapon(type, damage); }

};

class Player {
private:
    std::string name;
    int hp;
    std::vector<std::string> inventory;
    Weapon* weapon;
public:
    Player(const std::string& n, int h, Weapon* w)
        : name(n), hp(h), weapon(w->clone()) {}

    Player* clone() const {
        Player* copy = new Player(name, hp, weapon);
        copy->inventory = inventory;
        return copy;
    }

};
//10
~Player() {
    delete weapon;
}

~Weapon() {

}
//11
clone();
    }
    Enemy* createSkeleton() const { return skeletonTemplate->clone(); }
    Enemy* createMage() const { return mageTemplate->clone(); }

    ~EnemyFactory() {
        delete zombieTemplate;
        delete skeletonTemplate;
        delete mageTemplate;
    }
};

int main() {
    EnemyFactory factory;
    std::vector<Enemy*> enemies;

    enemies.push_back(factory.createZombie());
    enemies.push_back(factory.createSkeleton());
    enemies.push_back(factory.createMage());

    for (auto enemy : enemies) {
        enemy->print();
        delete enemy;
    }
    return 0;
}
//12
#include <map>

class PrototypeRegistry {
private:
    std::map<std::string, Enemy*> prototypes;
public:
    void registerPrototype(const std::string& key, Enemy* prototype) {
        prototypes[key] = prototype;
    }

    Enemy* create(const std::string& key) const {
        auto it = prototypes.find(key);
        if (it != prototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }

    ~PrototypeRegistry() {
        for (auto& pair : prototypes) {
            delete pair.second;
        }
    }
};

int main() {
    PrototypeRegistry registry;
    registry.registerPrototype("zombie", new Enemy(150, 15, 2.0f));
    registry.registerPrototype("skeleton", new Enemy(80, 25, 4.0f));

    Enemy* zombie = registry.create("zombie");
    zombie->print();
    delete zombie;
    return 0;
}
//13
class Spawner {
private:
    PrototypeRegistry& registry;
    int spawnInterval;
public:
    Spawner(PrototypeRegistry& reg, int interval)
        : registry(reg), spawnInterval(interval) {}

    void spawnEnemies(int count, const std::string& type) {
        std::cout << "Spawning " << count << " " << type << "(s)...\n";
        for (int i = 0; i < count; ++i) {
            Enemy* enemy = registry.create(type);
            if (enemy) {
                std::cout << "Spawned enemy #" << i + 1 << "\n";
                enemy->print();
                delete enemy;
            }
        }
    }
};

int main() {
    PrototypeRegistry registry;
    registry.registerPrototype("zombie", new Enemy(150, 15, 2.0f));

    Spawner spawner(registry, 5);
    spawner.spawnEnemies(3, "zombie");
    return 0;
}
//14
class Spell : public Prototype {
public:
    virtual void cast() = 0;
};

class Fireball : public Spell {
public:
    Fireball* clone() const override {
        return new Fireball(*this);
    }
    void cast() override {
        std::cout << "Fireball: BOOM!\n";
    }
};

class IceBlast : public Spell {
public:
    IceBlast* clone() const override {
        return new IceBlast(*this);
    }
    void cast() override {
        std::cout << "IceBlast: Freezing everything!\n";
    }
};

class PoisonCloud : public Spell {
public:
    PoisonCloud* clone() const override {
        return new PoisonCloud(*this);
    }
    void cast() override {
        std::cout << "PoisonCloud: Toxic mist spreads!\n";
    }
};
int main() {
    std::vector<Spell*> spells;
    spells.push_back(new Fireball());
    spells.push_back(new IceBlast());

    std::vector<Spell*> clonedSpells;
    for (auto spell : spells) {
        clonedSpells.push_back(spell->clone());
    }

    for (auto spell : clonedSpells) {
        spell->cast();
        delete spell;
    }
    for (auto spell : spells) delete spell;
    return 0;
}
//15
class Room {
private:
    int width, height;
    std::string description;
public:
    Room(int w, int h, const std::string& desc)
        : width(w), height(h), description(desc) {}

    Room* clone() const {
        return new Room(width, height, description);
    }

    void print() const {
        std::cout << "Room: " << width << "x" << height
                  << " - " << description << "\n";
    }
};

class LevelGenerator {
private:
    Room* roomTemplate;
public:
    LevelGenerator(Room* templateRoom) : roomTemplate(templateRoom) {}

    std::vector<Room*> generateMap(int roomCount) {
        std::vector<Room*> map;
        for (int i = 0; i < roomCount; ++i) {
            Room* room = roomTemplate->clone();
            room->description = "Generated Room #" + std::to_string(i + 1);
            map.push_back(room);
        }
        return map;
    }
};

int main() {
    Room templateRoom(10, 8, "Starting Room");
    LevelGenerator generator(&templateRoom);

    auto levelMap = generator.generateMap(5);
    for (auto room : levelMap) {
        room->print();
        delete room;
    }
    return 0;
}
//16
class Weapon : public Prototype {
protected:
    std::string name;
    int damage;
public:
    Weapon(const std::string& n, int d) : name(n), damage(d) {}
    virtual ~Weapon() = default;
};

class BasicWeapon : public Weapon {
public:
    BasicWeapon(const std::string& n, int d) : Weapon(n, d) {}
    BasicWeapon* clone() const override {
        return new BasicWeapon(*this);
    }
};

class WeaponDecorator : public Weapon {
protected:
    Weapon* wrapped;
public:
    WeaponDecorator(Weapon* w) : wrapped(w), Weapon(w->name, w->damage) {}
};

class FireWeapon : public WeaponDecorator {
public:
    FireWeapon(Weapon* w) : WeaponDecorator(w) {
        name = "Fire " + name;
        damage += 10;
    }
    FireWeapon* clone() const override {
        return new FireWeapon(wrapped->clone());
    }
};

int main() {
    Weapon* sword = new BasicWeapon("Sword", 20);
    Weapon* fireSword = new FireWeapon(sword);
    Weapon* clonedFireSword = fireSword->clone();

    clonedFireSword->print(); 
    delete sword;
    delete fireSword;
    delete clonedFireSword;
    return 0;
}
//17
class CloneCharacterCommand {
private:
    Character* character;
public:
    CloneCharacterCommand(Character* ch) : character(ch) {}

    Character* execute() const {
        return character->clone();
    }
};

int main() {
    Character player("Hero", 100);
    CloneCharacterCommand cloneCmd(&player);

    Character* clone = cloneCmd.execute();
    clone->print();
    delete clone;
    return 0;
}
//18
class GameFacade {
private:
    PrototypeRegistry registry;
    LevelGenerator levelGen;
    std::vector<Enemy*> enemies;
    std::vector<Character*> characters;

public:
    GameFacade() : levelGen(nullptr) {}

    void initialize() {
        registry.registerPrototype("zombie", new Enemy(150, 15, 2.0f));
        registry.registerPrototype("skeleton", new Enemy(80, 25, 4.0f));
        registry.registerPrototype("mage", new Enemy(70, 40, 3.0f));

        Room* roomTemplate = new Room(10, 8, "Starting Room");
        levelGen = LevelGenerator(roomTemplate);
    }

    void spawnEnemies(const std::string& enemyType, int count) {
        for (int i = 0; i < count; ++i) {
            Enemy* enemy = registry.create(enemyType);
            if (enemy) {
                enemies.push_back(enemy);
                std::cout << "Spawned " << enemyType << " #" << i + 1 << "\n";
            }
        }
    }

    void generateLevel(int roomCount) {
        auto levelMap = levelGen.generateMap(roomCount);
        std::cout << "Generated level with " << roomCount << " rooms\n";

        for (auto room : levelMap) {
            delete room;
        }
    }

    void startGame() {
        initialize();
        spawnEnemies("zombie", 3);
        spawnEnemies("skeleton", 2);
        generateLevel(5);

        std::cout << "Game started!\n";
    }

    ~GameFacade() {
        for (auto enemy : enemies) delete enemy;
        for (auto character : characters) delete character;
    }
};

int main() {
    GameFacade game;
    game.startGame();
    return 0;
}
//19
#include <memory>

class EnemyUnique {
private:
    int hp;
    int damage;
    float speed;
public:
    EnemyUnique(int h, int d, float s) : hp(h), damage(d), speed(s) {}

    // Возвращаем unique_ptr вместо сырого указателя
    std::unique_ptr<EnemyUnique> clone() const {
        return std::make_unique<EnemyUnique>(hp, damage, speed);
    }

    void print() const {
        std::cout << "Enemy: HP=" << hp << ", Damage=" << damage << ", Speed=" << speed << "\n";
    }

    friend class EnemyFactoryUnique;
};

class EnemyFactoryUnique {
public:
    static std::unique_ptr<EnemyUnique> createZombie() {
        return std::make_unique<EnemyUnique>(150, 15, 2.0f);
    }

    static std::unique_ptr<EnemyUnique> createSkeleton() {
        return std::make_unique<EnemyUnique>(80, 25, 4.0f);
    }
};
int main() {
    auto original = EnemyFactoryUnique::createZombie();
    auto copy = original->clone();

    original->print();
    copy->print();

    return 0; 
}
//20
#include <map>
#include <string>
#include <vector>

// Базовый класс для всех игровых объектов
class GameObject {
public:
    virtual ~GameObject() = default;
    virtual std::unique_ptr<GameObject> clone() const = 0;
    virtual void interact() = 0;
};

// Класс врага
class Enemy : public GameObject {
private:
    std::string name;
    int hp;
    int damage;
public:
    Enemy(const std::string& n, int h, int d) : name(n), hp(h), damage(d) {}

    std::unique_ptr<GameObject> clone() const override {
        return std::make_unique<Enemy>(name, hp, damage);
    }

    void interact() override {
        std::cout << "Enemy " << name << " attacks for " << damage << " damage!\n";
    }
};

// Класс предмета
class Item : public GameObject {
private:
    std::string name;
    int value;
public:
    Item(const std::string& n, int v) : name(n), value(v) {}

    std::unique_ptr<GameObject> clone() const override {
        return std::make_unique<Item>(name, value);
    }

    void interact() override {
        std::cout << "Item " << name << " picked up! Value: " << value << "\n";
    }
};

// Класс заклинания
class Spell : public GameObject {
private:
    std::string name;
    int manaCost;
public:
    Spell(const std::string& n, int m) : name(n), manaCost(m) {}

    std::unique_ptr<GameObject> clone() const override {
        return std::make_unique<Spell>(name, manaCost);
    }

    void interact() override {
        std::cout << "Spell " << name << " cast! Mana cost: " << manaCost << "\n";
    }
};

// Registry для хранения прототипов
class GameObjectRegistry {
private:
    std::map<std::string, std::unique_ptr<GameObject>> prototypes;
public:
    void registerPrototype(const std::string& key, std::unique_ptr<GameObject> prototype) {
        prototypes[key] = std::move(prototype);
    }

    std::unique_ptr<GameObject> create(const std::string& key) const {
        auto it = prototypes.find(key);
        if (it != prototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }
};

// Использование
int main() {
    GameObjectRegistry registry;

    // Регистрируем прототипы
    registry.registerPrototype("zombie", std::make_unique<Enemy>("Zombie", 150, 15));
    registry.registerPrototype("fireball", std::make_unique<Spell>("Fireball", 20));
    registry.registerPrototype("health_potion", std::make_unique<Item>("Health Potion", 50));

    // Создаём объекты через клонирование
    auto zombie = registry.create("zombie");
    auto fireball = registry.create("fireball");
    auto potion = registry.create("health_potion");

    // Взаимодействуем с объектами
    zombie->interact();
    fireball->interact();







//1 
#include <iostream>

class Animal {
public:
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof!\n";
    }
};

class Cat : public Animal {
public:
    void speak() override {
        std::cout << "Meow!\n";
    }
};

class AnimalFactory {
public:
    static Animal* create(int type) {
        if (type == 1) return new Dog();
        else if (type == 2) return new Cat();
        return nullptr;
    }
};
//2
int main() {
    Animal* animal = AnimalFactory::create(1); // Создаём собаку
    if (animal) {
        animal->speak(); // Выводим "Woof!"
        delete animal;
    }
    return 0;
}
//3
class Bird : public Animal {
public:
    void speak() override {
        std::cout << "Tweet!\n";
    }
};

// В AnimalFactory добавляем:
if (type == 3) return new Bird();
//4
int type;
std::cin >> type;
Animal* animal;
if (type == 1) animal = new Dog();
else if (type == 2) animal = new Cat();
// Логика разбросана по коду
//5
Animal* animal = AnimalFactory::create(5); // Неизвестный тип
if (!animal) {
    std::cout << "Unknown animal type!\n";
} else {
    animal->speak();
    delete animal;
}
//6
class Transport {
public:
    virtual void move() = 0;
    virtual ~Transport() = default;
};

class Car : public Transport {
public:
    void move() override { std::cout << "Driving\n"; }
};

class Bike : public Transport {
public:
    void move() override { std::cout << "Riding\n"; }
};

class TransportFactory {
public:
    static Transport* create(int type) {
        if (type == 1) return new Car();
        else if (type == 2) return new Bike();
        return nullptr;
    }
};
//7
class Payment {
public:
    virtual void process(double amount) = 0;
    virtual ~Payment() = default;
};

class Card : public Payment {
public:
    void process(double amount) override {
        std::cout << "Paid " << amount << " by card\n";
    }
};

class Cash : public Payment {
public:
    void process(double amount) override {
        std::cout << "Paid " << amount << " in cash\n";
    }
};

class PaymentFactory {
public:
    static Payment* create(const std::string& type) {
        if (type == "card") return new Card();
        else if (type == "cash") return new Cash();
        return nullptr;
    }
};
//8
class Document {
public:
    virtual void open() = 0;
    virtual ~Document() = default;
};

class PDFDocument : public Document {
public:
    void open() override { std::cout << "Opening PDF\n"; }
};

class DOCDocument : public Document {
public:
    void open() override { std::cout << "Opening DOC\n"; }
};

class DocumentFactory {
public:
    static Document* create(const std::string& format) {
        if (format == "pdf") return new PDFDocument();
        else if (format == "doc") return new DOCDocument();
        return nullptr;
    }
};
//9
class A { /* ... */ };
class B { /* ... */ };

class ComplexFactory {
public:
    static A* create(int value) {
        if (value < 10) return new A();
        else if (value == 10) return new B();
        return nullptr;
    }
};
//10
class Enemy { /* ... */ };
class Zombie : public Enemy { /* ... */ };
class Vampire : public Enemy { /* ... */ };

class EnemyFactory {
public:
    static Enemy* create(int type, int level) {
        if (type == 1 && level < 5) return new Zombie();
        else if (type == 2 && level >= 5) return new Vampire();
        return nullptr;
    }
};
//11
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

class Creator {
public:
    virtual Product* create() = 0;
    virtual ~Creator() = default;
};
//12
class DogFactory : public Creator {
public:
    Product* create() override {
        return new Dog(); // Dog наследуется от Product
    }
};

class CatFactory : public Creator {
public:
    Product* create() override {
        return new Cat(); // Cat наследуется от Product
    }
};
//13
Creator* factory = new DogFactory();
Product* product = factory->create();
product->use();
delete product;
delete factory;
//14
class Fish : public Product { /* ... */ };

class FishFactory : public Creator {
public:
    Product* create() override {
        return new Fish();
    }
};
//15
class Animal {
public:
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() override { std::cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() override { std::cout << "Meow!\n"; }
};

class Bird : public Animal {
public:
    void speak() override { std::cout << "Tweet!\n"; }
};

class AnimalFactory {
public:
    static Animal* create(int type) {
        if (type == 1) return new Dog();
        else if (type == 2) return new Cat();
        else if (type == 3) return new Bird();
        return nullptr;
    }
};
//16
class Enemy {
public:
    virtual void attack() = 0;
    virtual ~Enemy() = default;
};

class Zombie : public Enemy {
public:
    void attack() override { std::cout << "Zombie bites!\n"; }
};

class Vampire : public Enemy {
public:
    void attack() override { std::cout << "Vampire bites!\n"; }
};

class EnemyFactory {
public:
    static Enemy* create(int type) {
        if (type == 1) return new Zombie();
        else if (type == 2) return new Vampire();
        return nullptr;
    }
};
//17
class UIElement {
public:
    virtual void render() = 0;
    virtual ~UIElement() = default;
};

class Button : public UIElement {
public:
    void render() override { std::cout << "Drawing button\n"; }
};

class TextBox : public UIElement {
public:
    void render() override { std::cout << "Drawing text box\n"; }
};

class UIFactory {
public:
    static UIElement* create(const std::string& type) {
        if (type == "button") return new Button();
        else if (type == "textbox") return new TextBox();
        return nullptr;
    }
};
//18
class UIElement {
public:
    virtual void render() = 0;
    virtual ~UIElement() = default;
};

class Button : public UIElement {
public:
    void render() override { std::cout << "Drawing button\n"; }
};

class TextBox : public UIElement {
public:
    void render() override { std::cout << "Drawing text box\n"; }
};

class UIFactory {
public:
    static UIElement* create(const std::string& type) {
        if (type == "button") return new Button();
        else if (type == "textbox") return new TextBox();
        return nullptr;
    }
};
//19
#include <vector>
#include <list>
#include <memory>

class Container {
public:
    virtual void add(int value) = 0;
    virtual size_t size() const = 0;
    virtual ~Container() = default;
};

class VectorContainer : public Container {
private:
    std::vector<int> data;
public:
    void add(int value) override { data.push_back(value); }
    size_t size() const override { return data.size(); }
};

class ListContainer : public Container {
private:
    std::list<int> data;
public:
    void add(int value) override { data.push_back(value); }
    size_t size() const override { return data.size(); }
};

class ContainerFactory {
public:
    static Container* create(const std::string& type) {
        if (type == "vector") return new VectorContainer();
        else if (type == "list") return new ListContainer();
        return nullptr;
    }
};
//20
#include <memory>

class AnimalFactory {
public:
    static std::unique_ptr<Animal> create(int type) {
        switch (type) {
            case 1: return std::make_unique<Dog>();
            case 2: return std::make_unique<Cat>();
            case 3: return std::make_unique<Bird>();
            default: return nullptr;
        }
    }
};




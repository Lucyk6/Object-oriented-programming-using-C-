#include <iostream>
#include <string>
using namespace std;

// 1
class Text {
public:
    virtual string render() = 0;
    virtual ~Text() {}
};

//2
class TextDecorator : public Text {
protected:
    Text* wrapped;
public:
    TextDecorator(Text* t) : wrapped(t) {}
};

// 3
class PlainText : public Text {
private:
    string value;
public:
    PlainText(const string& v) : value(v) {}

    string render() override {
        return value;
    }
};

// 4
class BoldDecorator : public TextDecorator {
public:
    BoldDecorator(Text* t) : TextDecorator(t) {}

    string render() override {
        return "<b>" + wrapped->render() + "</b>";
    }
};

class ItalicDecorator : public TextDecorator {
public:
    ItalicDecorator(Text* t) : TextDecorator(t) {}

    string render() override {
        return "<i>" + wrapped->render() + "</i>";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "2.Проверка обёртки:\n";
    Text* text1 = new PlainText("Hello");
    Text* bold1 = new BoldDecorator(text1);
    cout << bold1->render() << endl; 

    cout << "3. Цепочка декораторов:\n";
    Text* text2 = new PlainText("World");
    Text* bold2 = new BoldDecorator(text2);
    Text* boldItalic = new ItalicDecorator(bold2);
    cout << boldItalic->render() << endl;

    cout << "4. Порядок применения:\n";
    Text* order1 = new ItalicDecorator(new BoldDecorator(new PlainText("Order1")));
    cout << "Жирный на Курсив: " << order1->render() << endl;
    Text* order2 = new BoldDecorator(new ItalicDecorator(new PlainText("Order2")));
    cout << "Курсив на  Жирный: " << order2->render() << endl;
    delete order1;
    delete order2;
    delete boldItalic;
    delete bold1;

    return 0;
}
//5
#include <iostream>
#include <string>
using namespace std;

class Text {
public:
    virtual string render() = 0;
    virtual ~Text() {}
};

class PlainText : public Text {
private:
    string value;
public:
    PlainText(const string& v) : value(v) {}

    string render() override {
        return value;
    }
};

class BoldText : public Text {
private:
    string value;
public:
    BoldText(const string& v) : value(v) {}

    string render() override {
        return "<b>" + value + "</b>";
    }
};

class ItalicText : public Text {
private:
    string value;
public:
    ItalicText(const string& v) : value(v) {}

    string render() override {
        return "<i>" + value + "</i>";
    }
};

class BoldItalicText : public Text {
private:
    string value;
public:
    BoldItalicText(const string& v) : value(v) {}

    string render() override {
        return "<b><i>" + value + "</i></b>";
    }
};

int main() {

    Text* plain = new PlainText("Обычный текст");
    Text* bold = new BoldText("Жирный текст");
    Text* italic = new ItalicText("Курсивный текст");

    cout << plain->render() << endl;
    cout << bold->render() << endl;
    cout << italic->render() << endl;

    Text* boldItalic = new BoldItalicText("Жирный и курсивный");
    cout << boldItalic->render() << endl;

    delete plain;
    delete bold;
    delete italic;
    delete boldItalic;

    return 0;
}
//6
#include <iostream>
#include <string>
using namespace std;

class Text {
public:
    virtual string render() = 0;
    virtual ~Text() {}
};

class PlainText : public Text {
private:
    string value;
public:
    PlainText(const string& v) : value(v) {}
    string render() override { return value; }
};


class BoldDecorator : public Text {
private:
    Text* wrapped;
public:
    BoldDecorator(Text* t) : wrapped(t) {}
    ~BoldDecorator() { delete wrapped; }
    string render() override {
        return "<b>" + wrapped->render() + "</b>";
    }
};

class ItalicDecorator : public Text {
private:
    Text* wrapped;
public:
    ItalicDecorator(Text* t) : wrapped(t) {}
    ~ItalicDecorator() { delete wrapped; }
    string render() override {
        return "<i>" + wrapped->render() + "</i>";
    }
};
//7
class UnderlineDecorator : public Text {
private:
    Text* wrapped;
public:
    UnderlineDecorator(Text* t) : wrapped(t) {}
    ~UnderlineDecorator() { delete wrapped; }
    string render() override {
        return "<u>" + wrapped->render() + "</u>";
    }
};
//8

int main() {
    Text* boldItalic = new ItalicDecorator(new BoldDecorator(new PlainText("Текст")));
    cout << "Курсив + жирный: " << boldItalic->render() << endl;
    Text* combo = new UnderlineDecorator(boldItalic);
    cout << "Комбинация: " << combo->render() << endl;

    delete combo;
    return 0;
}

//9
class Coffee {
public:
    virtual double getCost() = 0;
    virtual string getDescription() = 0;
    virtual ~Coffee() {}
};

class SimpleCoffee : public Coffee {
public:
    double getCost() override { return 100; }
    string getDescription() override { return "Простой кофе"; }
};

class MilkDecorator : public Coffee {
private:
    Coffee* coffee;
public:
    MilkDecorator(Coffee* c) : coffee(c) {}
    ~MilkDecorator() { delete coffee; }
    double getCost() override { return coffee->getCost() + 30; }
    string getDescription() override {
        return coffee->getDescription() + ", молоко";
    }
};

class SugarDecorator : public Coffee {
private:
    Coffee* coffee;
public:
    SugarDecorator(Coffee* c) : coffee(c) {}
    ~SugarDecorator() { delete coffee; }
    double getCost() override { return coffee->getCost() + 10; }
    string getDescription() override {
        return coffee->getDescription() + ", сахар";
    }
};
//10
int main() {
    Coffee* coffee = new SugarDecorator(new MilkDecorator(new SimpleCoffee()));
    cout << coffee->getDescription() << " — " << coffee->getCost() << " руб.\n";
    delete coffee;
}

//11-15
#include <iostream>
#include <string>
using namespace std;

class Order {
public:
    virtual double calculateTotal() = 0;
    virtual string getDetails() = 0;
    virtual ~Order() {}
};

class BasicOrder : public Order {
private:
    double basePrice;
public:
    BasicOrder(double price) : basePrice(price) {}

    double calculateTotal() override {
        return basePrice;
    }

    string getDetails() override {
        return "Базовый заказ";
    }
};

class DeliveryDecorator : public Order {
private:
    Order* order;
    double deliveryCost;
public:
    DeliveryDecorator(Order* o, double cost) : order(o), deliveryCost(cost) {}
    ~DeliveryDecorator() { delete order; }


    double calculateTotal() override {
        return order->calculateTotal() + deliveryCost;
    }

    string getDetails() override {
        return order->getDetails() + ", доставка (+ " + to_string(deliveryCost) + " руб.)";
    }
};

class PackagingDecorator : public Order {
    Order* order;
public:
    PackagingDecorator(Order* o) : order(o) {}
    ~PackagingDecorator() { delete order; }

    double calculateTotal() override {
        return order->calculateTotal() + 50.0;
    }

    string getDetails() override {
        return order->getDetails() + ", упаковка (+50 руб.)";
    }
};

class DiscountDecorator : public Order {
private:
    Order* order;
    double discountPercent;
public:
    DiscountDecorator(Order* o, double percent) : order(o), discountPercent(percent) {}
    ~DiscountDecorator() { delete order; }

    double calculateTotal() override {
        double total = order->calculateTotal();
        return total - (total * discountPercent / 100);
    }

    string getDetails() override {
        return order->getDetails() + ", скидка " + to_string(discountPercent) + "%";
    }
};

class LoggingDecorator : public Order {
private:
    Order* order;
public:
    LoggingDecorator(Order* o) : order(o) {}
    ~LoggingDecorator() { delete order; }

    double calculateTotal() override {
        cout << "LOG: Вызов calculateTotal() для '" << order->getDetails() << "'" << endl;
        double result = order->calculateTotal();
        cout << "LOG: Результат calculateTotal(): " << result << " руб." << endl;
        return result;
    }

    string getDetails() override {
        cout << "LOG: Вызов getDetails()" << endl;
        return order->getDetails();
    }
};

class CachingDecorator : public Order {
private:
    Order* order;
    mutable double cachedTotal;
    mutable bool isCached;
public:
    CachingDecorator(Order* o) : order(o), isCached(false) {}
    ~CachingDecorator() { delete order; }
    double calculateTotal() override {
        if (!isCached) {
            cachedTotal = order->calculateTotal();
            isCached = true;
            cout << "CACHE: Результат закэширован\n";
        }
        else {
            cout << "CACHE: Использован закэшированный результат\n";
        }
        return cachedTotal;
    }
    string getDetails() override { return order->getDetails(); }
};

int main() {
    cout << "11. Базовый заказ + доставка + упаковка:\n";
    Order* order1 = new PackagingDecorator(
        new DeliveryDecorator(new BasicOrder(1000), 200)
    );
    cout << order1->getDetails() << endl;
    cout << "Итоговая стоимость: " << order1->calculateTotal() << " руб.\n\n";

    cout << "12. Заказ со скидкой:\n";
    Order* order2 = new DiscountDecorator(order1, 15);
    cout << order2->getDetails() << endl;
    cout << "Итоговая стоимость со скидкой: " << order2->calculateTotal() << " руб.\n\n";


    cout << "13. Заказ с логированием:\n";
    Order* order3 = new LoggingDecorator(order2);

    string details = order3->getDetails();
    double total = order3->calculateTotal();

    cout << "Финальный результат:\n";
    cout << details << endl;
    cout << "Итоговая стоимость с логированием: " << total << " руб.\n";

 
    delete order3;
    return 0;
}
//16
#include <iostream>
#include <string>
using namespace std;

class Character {
public:
    virtual int getDamage() = 0;
    virtual int getSpeed() = 0;
    virtual ~Character() {}
};

class BaseCharacter : public Character {
public:
    int getDamage() override { return 10; }
    int getSpeed() override { return 5; }
};

class DamageBuff : public Character {
private:
    Character* character;
    int bonusDamage;
public:
    DamageBuff(Character* c, int bonus) : character(c), bonusDamage(bonus) {}
    ~DamageBuff() { delete character; }

    int getDamage() override {
        return character->getDamage() + bonusDamage;
    }

    int getSpeed() override {
        return character->getSpeed();
    }
};

class SpeedBuff : public Character {
private:
    Character* character;
    int bonusSpeed;
public:
    SpeedBuff(Character* c, int bonus) : character(c), bonusSpeed(bonus) {}
    ~SpeedBuff() { delete character; }

    int getDamage() override {
        return character->getDamage();
    }

    int getSpeed() override {
        return character->getSpeed() + bonusSpeed;
    }
};

//17
void applyDynamicBuffs(Character*& character) {
    int choice;
    cout << "Выберите баффы (0 — закончить):\n";
    cout << "1 — +10 урона\n2 — +3 скорости\n";

    while (true) {
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            character = new DamageBuff(character, 10);
        }
        else if (choice == 2) {
            character = new SpeedBuff(character, 3);
        }
    }
}
//18
#include <vector>

class BuffChain {
private:
    vector<Character*> chain;
public:
    BuffChain(Character* base) {
        chain.push_back(base);
    }

    void addBuff(Character* buff) {
        chain.back() = buff;
        chain.push_back(buff);
    }

    Character* getFinalCharacter() {
        return chain.back();
    }

    ~BuffChain() {
        for (auto* ch : chain) delete ch;
    }
};

//19
#include <memory>

class SmartCharacter : public Character {
private:
    shared_ptr<Character> character;
public:
    SmartCharacter(shared_ptr<Character> c) : character(c) {}

    int getDamage() override {
        return character->getDamage();
    }

    int getSpeed() override {
        return character->getSpeed();
    }
};
    auto base = make_shared<BaseCharacter>();
    auto buffed = make_shared<DamageBuff>(base, 15);

//20
class Message {
public:
    virtual string getContent() = 0;
    virtual ~Message() {}
};

class SimpleMessage : public Message {
private:
    string content;
public:
    SimpleMessage(const string& c) : content(c) {}

    string getContent() override { return content; }
};

class EncryptionDecorator : public Message {
private:
    shared_ptr<Message> message;
public:
    EncryptionDecorator(shared_ptr<Message> m) : message(m) {}

    string getContent() override {
        string encrypted = message->getContent();

        for (char& c : encrypted) c = c + 1;
        return "ENC[" + encrypted + "]";
    }
};

class CompressionDecorator : public Message {
private:
    shared_ptr<Message> message;
public:
    CompressionDecorator(shared_ptr<Message> m) : message(m) {}

    string getContent() override {
        string compressed = message->getContent();
        return "COMPR[" + compressed.substr(0, 5) + "...(" +
            to_string(compressed.length()) + ")]";
    }
};

class LoggingDecorator : public Message {
private:
    shared_ptr<Message> message;
public:
    LoggingDecorator(shared_ptr<Message> m) : message(m) {}

    string getContent() override {
        cout << "LOG: Получение содержимого сообщения\n";
        string content = message->getContent();
        cout << "LOG: Получено: " << content << endl;
        return content;
    }
};
//16-20
int main() {

    Character* hero = new BaseCharacter();
    cout << "Базовый персонаж: урон " << hero->getDamage()
        << ", скорость " << hero->getSpeed() << endl;

    hero = new DamageBuff(hero, 20);
    hero = new SpeedBuff(hero, 8);
    cout << "После бафов: урон " << hero->getDamage()
        << ", скорость " << hero->getSpeed() << endl;

    auto msg = make_shared<SimpleMessage>("Секретное сообщение");
    auto encrypted = make_shared<EncryptionDecorator>(msg);
    auto compressed = make_shared<CompressionDecorator>(encrypted);
    auto logged = make_shared<LoggingDecorator>(compressed);

    cout << logged->getContent() << endl;

    delete hero; 
    return 0;
}

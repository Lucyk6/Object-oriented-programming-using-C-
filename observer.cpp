//1
#include <iostream>
#include <vector>

struct Observer {
    virtual void update() = 0;
};

struct ConcreteObserver : Observer {
    void update() override { std::cout << "Notified!\n"; }
};

struct Subject {
    std::vector<Observer*> obs;
    void add(Observer* o) { obs.push_back(o); }
    void notify() { for (auto o : obs) o->update(); }
};

int main() {
    Subject s;
    ConcreteObserver o1;
    s.add(&o1);
    s.notify();
}
//2
int main() {
    Subject s;
    ConcreteObserver o1, o2, o3;
    s.add(&o1); s.add(&o2); s.add(&o3);
    s.notify(); 
}
//3
struct Observer {
    virtual void update(int value) = 0;
};

struct ValueDisplay : Observer {
    void update(int v) override
    { std::cout << "Value: " << v << "\n"; }
};
//4
class Data : public Subject {
    int value;
public:
    void setValue(int v) {
        value = v;
        notify(); 
    }
};
//5
struct TaskA : Observer 
{ void update() override 
{ std::cout << "Step 1\n"; } };
struct TaskB : Observer 
{ void update() override 
{ std::cout << "Step 2\n"; } };

int main() {
    Subject s;
    TaskA a; TaskB b;
    s.add(&a); s.add(&b);
    s.notify(); 
}
//6
struct Button : Subject {};
struct SaveAction : Observer 
{ void update() override 
{ std::cout << "Saved.\n"; } };
struct PrintAction : Observer 
{ void update() override 
{ std::cout << "Printed.\n"; } };

int main() {
    Button btn;
    SaveAction save;
    btn.add(&save);
    btn.notify(); 
}
//7
struct ConsoleLog : Observer
{ void update() override 
{ std::cout << "Log to console\n"; }
};
struct FileLog : Observer
{ void update() override 
{ std::cout << "Log to file (mock)\n"; }
};
//8
struct TempSensor : Subject {
    void setTemp(float t) { notify(); }
};
//9
struct User : Observer {
    std::string name;
    User(std::string n) : name(n) {}
    void update() override { std::cout << name << " got message!\n"; }
};
//10
struct SoundEffect : Observer { void update() override { std::cout << "Play 'Ouch!' sound\n"; } };
struct VisualEffect : Observer { void update() override { std::cout << "Screen shake\n"; } };
//11
#include <algorithm>
struct Subject {
    std::vector<Observer*> obs;
    void add(Observer* o) { obs.push_back(o); }
    void remove(Observer* o) {
        obs.erase(std::remove(obs.begin(), obs.end(), o), obs.end());
    }
};
//12
int main() {
    Subject s; ConcreteObserver o1;
    s.add(&o1);
    s.remove(&o1);
    s.notify();
}
//13
void add(Observer* o) {
    if (std::find(obs.begin(), obs.end(), o) == obs.end()) {
        obs.push_back(o);
    }
}
//14
void clear() { obs.clear(); }
//15
enum Event { LOGIN, LOGOUT };
struct Observer { virtual void onEvent(Event e) = 0; };
//16
struct SortStrategy { virtual void sort() = 0; };
struct SortManager : Observer {
    SortStrategy* strategy;
    void update() override { strategy->sort(); }
};
//17
struct ObserverFactory {
    static Observer* create(std::string type) {
        if (type == "console") return new ConsoleLog();
        return nullptr;
    }
};
//18
#include <algorithm>
void notify() {
    std::for_each(obs.begin(), obs.end(), [](Observer* o) { o->update(); });
}
//19
#include <functional>

struct SubjectLambda {
    std::vector<std::function<void(int)>> observers;
    void subscribe(std::function<void(int)> f) { observers.push_back(f); }
    void notify(int val) { for (auto& f : observers) f(val); }
};

int main() {
    SubjectLambda s;
    s.subscribe([](int v) { std::cout << "Lambda got: " << v; });
    s.notify(42);
}
//20
#include <map>
#include <string>
#include <functional>

class EventManager {
    std::map<std::string, std::vector<std::function<void()>>> listeners;
public:
    void subscribe(std::string event, std::function<void()> f) {
        listeners[event].push_back(f);
    }
    void emit(std::string event) {
        for (auto& f : listeners[event]) f();
    }
};

int main() {
    EventManager em;
    em.subscribe("click", []() { std::cout << "Click detected!\n"; });
    em.emit("click");
}




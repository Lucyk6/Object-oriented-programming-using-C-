1
#include <iostream>
#include <memory>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute() const = 0;
};

class ConcreteStrategyA : public Strategy
{
    void execute() const override
    {
        std::cout << "Strategy A\n";
    }
};

class ConcreteStrategyB : public Strategy {
    void execute() const override 
    { 
        std::cout << "Strategy B\n"; 
    }
};

class Context {
    Strategy* strategy;
public:
    void setStrategy(Strategy* s) 
    { 
        strategy = s;
    }
    void run()
    {
        strategy->execute();
    }
};

int main() {
    Context ctx;
    ConcreteStrategyA s1;
    ctx.setStrategy(&s1);
    ctx.run();
    return 0;
}
2
int main() {
    Context ctx;
    ConcreteStrategyA s1;
    ConcreteStrategyB s2;

    ctx.setStrategy(&s1);
    ctx.run(); 

    ctx.setStrategy(&s2);
    ctx.run(); 
    return 0;
}
3
void Context::run() {
    strategy->execute(); 
}
4
 До:
void run(int type) {
    if (type == 1) std::cout << "A";
    else if (type == 2) std::cout << "B";
}
5
struct MathStrategy {
    virtual int calculate(int a, int b) = 0;
};

struct Add : MathStrategy 
{
    int calculate(int a, int b)
        override 
    { return a + b; } 
};
struct Sub : MathStrategy
{ 
    int calculate(int a, int b) override
    { return a - b; } 
};

int main() {
    Add add;
    std::cout << add.calculate(10, 5); 
}
6
#include <vector>
#include <algorithm>

struct SortStrategy {
    virtual void sort(std::vector<int>& v) = 0;
};

struct BubbleSort : SortStrategy {
    void sort(std::vector<int>& v) override { }
};

struct QuickSort : SortStrategy {
    void sort(std::vector<int>& v) override { std::sort(v.begin(), v.end()); }
};
7
int main() {
    std::vector<int> data = { 3, 1, 2 };
    QuickSort qs;
    BubbleSort bs;

    SortStrategy* current = &qs;
    current->sort(data);
}
8 
struct SearchStrategy {
    virtual int find(const std::vector<int>& v, int val) = 0;
};
struct LinearSearch : SearchStrategy {
    int find(const std::vector<int>& v, int val) override { return 0; /*...*/ }
};
9
struct Filter {
    virtual bool check(int n) = 0;
};
struct Even : Filter { bool check(int n) override { return n % 2 == 0; } };
struct Positive : Filter { bool check(int n) override { return n > 0; } };
10
#include <string>

struct StringCase {
    virtual void transform(std::string& s) = 0;
};
struct Upper : StringCase {
    void transform(std::string& s) 
 override 
 { 
 for (auto& c : s) c = toupper(c);
 }
};
11
struct Payment
{ 
	virtual void pay(int amount) = 0;
};
struct CreditCard : Payment 
{ void pay(int a) 
override
{ std::cout << "Card: " << a; }
};
struct Cash : Payment 
{ 
	void pay(int a) 
		override

	{ std::cout << "Cash: " << a; } 
};
12
struct Discount 
{ 
	virtual double apply(double price) = 0; 
};
struct Percent : Discount 
{ double apply(double p)
  override 
{
	return p * 0.9; 
} 
};
struct Fixed : Discount
{ 
	double apply(double p)
		override 
	{ return p - 100; }
};
13
struct Logger  
{ 
	virtual void log(std::string msg) = 0;
};
struct ConsoleLog : Logger
{ 
	void log(std::string m)
		override { std::cout << m; } 
};
14
struct Behavior 
{ 
	virtual void act() = 0;
};
struct Aggressive : Behavior
{ 
	void act() override 
	{ std::cout << "Attack!"; }
};
struct Defensive : Behavior 
{ 
	void act() override
	{ 
		std::cout << "Block!"; }
};
15
struct Move 
{ 
	virtual void go() = 0;
};
struct Walk : Move 
{ 
	void go() override
	{ std::cout << "Speed 5"; } 
};
struct Run : Move 
{ void go() override
{ 
	std::cout << "Speed 15"; 
} 
};
16
class Context {
    Strategy* s;
public:
    Context(Strategy* init_s) : s(init_s) {}
};
17
class Context {
public:
    void executeWith(Strategy* s)  
    { s->execute(); }
};
18
#include <functional>
#include <vector>

int main() {
    std::vector<std::function<void()>> strategies;
    strategies.push_back([]()
        { std::cout << "Strategy 1"; });
    strategies[0]();
}
19
#include <memory>

class Context {
    std::unique_ptr<Strategy> strategy;
public:
    void setStrategy(std::unique_ptr<Strategy> s) { strategy = std::move(s); }
};

int main() {
    Context ctx;
    ctx.setStrategy(std::make_unique<ConcreteStrategyA>());
}
20
template <typename T>
class GenericContext {
    T strategy;
public:
    void run() { strategy.execute(); }
};

struct FastStrategy { void execute() { std::cout << "Fast\n"; } };

int main() {
    GenericContext<FastStrategy> ctx;
    ctx.run();
}



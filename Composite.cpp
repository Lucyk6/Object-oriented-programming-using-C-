//1
#include <iostream>
#include <vector>
#include <string>

class Component {
public:
    virtual void operation() = 0;
    virtual ~Component() = default;
};

class Leaf : public Component {
private:
    std::string name;
public:
    Leaf(const std::string& n) : name(n) {}
    void operation() override {
        std::cout << "Leaf: " << name << "\n";
    }
};

class Composite : public Component {
private:
    std::vector<Component*> children;
    std::string name;
#public:
    Composite(const std::string& n) : name(n) {}
    void add(Component* component) {
        children.push_back(component);
    }
    void operation() override {
        std::cout << "Composite: " << name << " contains:\n";
        for (auto child : children) {
            child->operation();
        }
    }
};

//2
int main() {
    Composite root("Root");
    Leaf leaf1("Leaf1");
    Leaf leaf2("Leaf2");
    Composite composite("Composite");
    Leaf leaf3("Leaf3");
    Leaf leaf4("Leaf4");

    composite.add(&leaf3);
    composite.add(&leaf4);
    root.add(&leaf1);
    root.add(&leaf2);
    root.add(&composite);

    root.operation();
    return 0;
}

//3
class Component {
#public:
    virtual void display(int depth = 0) = 0;
    // ...
};

class Leaf : public Component {
#public:
    void display(int depth) override {
        std::cout << std::string(depth * 2, ' ') << "- " << name << "\n";
    }
};

class Composite : public Component {
#public:
    void display(int depth) override {
        std::cout << std::string(depth * 2, ' ') << "+ " << name << "\n";
        for (auto child : children) {
            child->display(depth + 1);
        }
    }
};
//4
class Composite : public Component {
#private:
    std::vector<Component*> children;
#public:
    void remove(Component* component) {
        auto it = std::find(children.begin(), children.end(), component);
        if (it != children.end()) {
            children.erase(it);
        }
    }
    // ...
};

//5
class Component {
#public:
    virtual int count() = 0;
};

class Leaf : public Component {
#public:
    int count() override { return 1; }
};

class Composite : public Component {
#public:
    int count() override {
        int total = 1; // сам Composite
        for (auto child : children) {
            total += child->count();
        }
        return total;
    }
};

//6
class Component {
#public:
    virtual int count() = 0;
};

class Leaf : public Component {
#public:
    int count() override { return 1; }
};

class Composite : public Component {
#public:
    int count() override {
        int total = 1; // сам Composite
        for (auto child : children) {
            total += child->count();
        }
        return total;
    }
};

//7
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Базовый интерфейс компонента
class UIComponent {
public:
    virtual void render() = 0;
    virtual std::string getName() const = 0;
    virtual ~UIComponent() = default;
};

// Листовые компоненты (элементы без детей)
class Button : public UIComponent {
private:
    std::string name;
public:
    Button(const std::string& n) : name(n) {}
    void render() override {
        std::cout << "Rendering Button: " << name << "\n";
    }
    std::string getName() const override { return name; }
};

class Label : public UIComponent {
private:
    std::string text;
public:
    Label(const std::string& t) : text(t) {}
    void render() override {
        std::cout << "Rendering Label: " << text << "\n";
    }
    std::string getName() const override { return text; }
};

class TextField : public UIComponent {
private:
    std::string placeholder;
public:
    TextField(const std::string& p) : placeholder(p) {}
    void render() override {
        std::cout << "Rendering TextField: " << placeholder << "\n";
    }
    std::string getName() const override { return placeholder; }
};

// Составные компоненты (контейнеры)
class Panel : public UIComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<UIComponent>> children;
public:
    Panel(const std::string& n) : name(n) {}

    void add(std::shared_ptr<UIComponent> component) {
        children.push_back(component);
    }

    void remove(const std::string& componentName) {
        auto it = std::remove_if(children.begin(), children.end(),
            [&componentName](const auto& component) {
                return component->getName() == componentName;
            });
        children.erase(it, children.end());
    }

    void render() override {
        std::cout << "Panel: " << name << " contains:\n";
        for (const auto& child : children) {
            child->render();
        }
    }

    std::string getName() const override { return name; }
};

class Window : public UIComponent {
private:
    std::string title;
    std::vector<std::shared_ptr<UIComponent>> components;
public:
    Window(const std::string& t) : title(t) {}

    void

//8
class GameComponent : public Component {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
};

// Листовые элементы
class Player : public GameComponent {
private:
    std::string name;
public:
    Player(const std::string& n) : name(n) {}
    void update() override { std::cout << "Player " << name << " updating\n"; }
    void draw() override { std::cout << "Drawing player: " << name << "\n"; }
};

class Enemy : public GameComponent { /* реализация */ };
class Item : public GameComponent { /* реализация */ };

// Составные элементы
class Scene : public GameComponent {
private:
    std::string sceneName;
    std::vector<std::shared_ptr<GameComponent>> objects;
public:
    Scene(const std::string& name) : sceneName(name) {}

    void add(std::shared_ptr<GameComponent> obj) {
        objects.push_back(obj);
    }

    void update() override {
        std::cout << "Scene " << sceneName << " updating:\n";
        for (auto& obj : objects) obj->update();
    }

    void draw() override {
        std::cout << "Scene " << sceneName << " drawing:\n";
        for (auto& obj : objects) obj->draw();
    }
};

class EnemyGroup : public GameComponent {
private:
    std::vector<std::shared_ptr<Enemy>> enemies;
public:
    void addEnemy(std::shared_ptr<Enemy> enemy) {
        enemies.push_back(enemy);
    }

    void update() override { /* обновление всех врагов */ }
    void draw() override { /* отрисовка всех врагов */ }
};
//9
class HTMLNode : public Component {
public:
    virtual void render() = 0;
    virtual std::string getHTML() const = 0;
};

// Листовые узлы
class ButtonNode : public HTMLNode {
private:
    std::string label;
public:
    ButtonNode(const std::string& l) : label(l) {}
    void render() override { std::cout << "<button>" << label << "</button>\n"; }
    std::string getHTML() const override {
        return "<button>" + label + "</button>";
    }
};

class ImageNode : public HTMLNode { /* реализация */ };
class TextNode : public HTMLNode { /* реализация */ };

// Составные узлы
class DivNode : public HTMLNode {
private:
    std::vector<std::shared_ptr<HTMLNode>> children;
    std::string id;
public:
    DivNode(const std::string& i) : id(i) {}

    void addChild(std::shared_ptr<HTMLNode> child) {
        children.push_back(child);
    }

    void render() override {
        std::cout << "<div id=\"" << id << "">\n";
        for (auto& child : children) child->render();
        std::cout << "</div>\n";
    }

    std::string getHTML() const override {
        std::string html = "<div id=\"" + id + "">";
        for (auto& child : children) html += child->getHTML();
        html += "</div>";
        return html;
    }
};

class BodyNode : public HTMLNode { /* реализация */ };

//10
class OrganizationComponent : public Component {
public:
    virtual size_t getEmployeeCount() const = 0;
    virtual double getTotalSalary() const = 0;
};

// Листовой компонент
class Employee : public OrganizationComponent {
private:
    std::string name;
    double salary;
public:
    Employee(const std::string& n, double s) : name(n), salary(s) {}
    size_t getEmployeeCount() const override { return 1; }
    double getTotalSalary() const override { return salary; }

    void display(int depth = 0) const {
        std::cout << std::string(depth * 2, ' ') << "- " << name
                  << " (Salary: $" << salary << ")\n";
    }
};

// Составные компоненты
class Department : public OrganizationComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<OrganizationComponent>> units;
public:
    Department(const std::string& n) : name(n) {}

    void addUnit(std::shared_ptr<OrganizationComponent> unit) {
        units.push_back(unit);
    }
//11
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class FileSystemComponent {
public:
    virtual size_t getSize() const = 0;
    virtual void display(int depth = 0) const = 0;
    virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
private:
    std::string name;
    size_t size;
public:
    File(const std::string& n, size_t s) : name(n), size(s) {}

    size_t getSize() const override { return size; }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "- " << name
                  << " (" << size << " bytes)\n";
    }
};

class Folder : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
public:
    Folder(const std::string& n) : name(n) {}

    void add(std::shared_ptr<FileSystemComponent> component) {
        children.push_back(component);
    }

    size_t getSize() const override {
        size_t total = 0;
        for (const auto& child : children) {
            total += child->getSize();
        }
        return total;
    }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "+ " << name
                  << " (Total: " << getSize() << " bytes)\n";
        for (const auto& child : children) {
            child->display(depth + 1);
        }
    }
};

//12
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class FileSystemComponent {
public:
    virtual size_t getSize() const = 0;
    virtual void display(int depth = 0) const = 0;
    virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
private:
    std::string name;
    size_t size;
public:
    File(const std::string& n, size_t s) : name(n), size(s) {}

    size_t getSize() const override { return size; }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "- " << name
                  << " (" << size << " bytes)\n";
    }
};

class Folder : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
public:
    Folder(const std::string& n) : name(n) {}

    void add(std::shared_ptr<FileSystemComponent> component) {
        children.push_back(component);
    }

    size_t getSize() const override {
        size_t total = 0;
        for (const auto& child : children) {
            total += child->getSize();
        }
        return total;
    }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "+ " << name
                  << " (Total: " << getSize() << " bytes)\n";
        for (const auto& child : children) {
            child->display(depth + 1);
        }
    }
};
auto found = root->find("report.docx");
if (found) {
    std::cout << "Found: " << found->getName() << "\n";
} else {
    std::cout << "Not found\n";
}

//13
auto world = std::make_shared<World>("Earth");
auto continent = std::make_shared<Continent>("Europe");
auto country = std::make_shared<Country>("France");
auto region = std::make_shared<Region>("Île-de-France");
auto city = std::make_shared<City>("Paris");
auto building = std::make_shared<Building>("Eiffel Tower");

city->add(building);
region->add(city);
country->add(region);
continent->add(country);
world->add(continent);

world->display(0);

//14
void dfs(FileSystemComponent* root) {
    root->display(0);

    if (auto folder = dynamic_cast<Folder*>(root)) {
        for (const auto& child : folder->getChildren()) {
            dfs(child.get());
        }
    }
}
#include <queue>

void bfs(FileSystemComponent* root) {
    std::queue<FileSystemComponent*> queue;
    queue.push(root);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        current->display(0);

        if (auto folder = dynamic_cast<Folder*>(current)) {
            for (const auto& child : folder->getChildren()) {
                queue.push(child.get());
            }
        }
    }
}

//15
class GameComponent : public Component {
#public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual int getObjectCount() const = 0;
};

// Уровни вложенности
class World : public GameComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<GameComponent>> regions;
#public:
    World(const std::string& n) : name(n) {}

    void addRegion(std::shared_ptr<GameComponent> region) {
        regions.push_back(region);
    }

    void update() override {
        std::cout << "World " << name << " updating\n";
        for (auto& region : regions) region->update();
    }

    void render() override {
        std::cout << "Rendering world: " << name << "\n";
        for (auto& region : regions) region->render();
    }

    int getObjectCount() const override {
        int count = 1; // сам World
        for (const auto& region : regions) {
            count += region->getObjectCount();
        }
        return count;
    }
};

class Region : public GameComponent { /* реализация */ };
class City : public GameComponent { /* реализация */ };
class Building : public GameComponent { /* реализация */ };

// Создание сложной карты
int main() {
    auto world = std::make_shared<World>("Fantasy World");

    auto region1 = std::make_shared<Region>("Forest Region");
    auto city1 = std::make_shared<City>("Elven City");
    auto building1 = std::make_shared<Building>("Magic Tower");

    city1->add(building1);
    region1->add(city1);
    world->addRegion(region1);

    std::cout << "Total objects in world: "
              << world->getObjectCount() << "\n";

    world->render();
    world->update();

    return 0;
}

//16
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Базовый компонент для GUI
class UIComponent {
public:
    virtual void render() = 0;
    virtual ~UIComponent() = default;
};

// Листовые компоненты
class Button : public UIComponent {
private:
    std::string label;
public:
    Button(const std::string& l) : label(l) {}
    void render() override {
        std::cout << "[Button: " << label << "]";
    }
};

class Panel : public UIComponent {
private:
    std::vector<std::shared_ptr<UIComponent>> children;
    std::string name;
public:
    Panel(const std::string& n) : name(n) {}

    void add(std::shared_ptr<UIComponent> component) {
        children.push_back(component);
    }

    void render() override {
        std::cout << "Panel " << name << " contains:\n";
        for (const auto& child : children) {
            child->render();
            std::cout << "\n";
        }
    }
};

// Декораторы
class Decorator : public UIComponent {
protected:
    std::shared_ptr<UIComponent> wrapped;
public:
    Decorator(std::shared_ptr<UIComponent> w) : wrapped(w) {}
};

class BorderDecorator : public Decorator {
private:
    int thickness;
public:
    BorderDecorator(std::shared_ptr<UIComponent> w, int t)
        : Decorator(w), thickness(t) {}

    void render() override {
        std::cout << "Border(" << thickness << "px): ";
        wrapped->render();
    }
};

class ShadowDecorator : public Decorator {
private:
    std::string color;
public:
    ShadowDecorator(std::shared_ptr<UIComponent> w, const std::string& c)
        : Decorator(w), color(c) {}

    void render() override {
        std::cout << "Shadow(" << color << "): ";
        wrapped->render();
    }
};

//17
class Renderer {
public:
    virtual void renderButton(const std::string& label) = 0;
    virtual void renderPanel(const std::string& name) = 0;
    virtual ~Renderer() = default;
};

// Конкретные реализации рендереров
class OpenGLRenderer : public Renderer {
public:
    void renderButton(const std::string& label) override {
        std::cout << "OpenGL: Rendering button '" << label << "'\n";
    }
    void renderPanel(const std::string& name) override {
        std::cout << "OpenGL: Rendering panel '" << name << "'\n";
    }
};

class VulkanRenderer : public Renderer { /* реализация */ };

// Компоненты с поддержкой разных рендереров (Composite)
class UIElement {
protected:
    std::shared_ptr<Renderer> renderer;
public:
    UIElement(std::shared_ptr<Renderer> r) : renderer(r) {}
    virtual void draw() = 0;
};

class ButtonElement : public UIElement {
private:
    std::string label;
public:
    ButtonElement(std::shared_ptr<Renderer> r, const std::string& l)
        : UIElement(r), label(l) {}
    void draw() override { renderer->renderButton(label); }
};

class PanelElement : public UIElement {
private:
    std::string name;
    std::vector<std::shared_ptr<UIElement>> children;
public:
    PanelElement(std::shared_ptr<Renderer> r, const std::string& n)
        : UIElement(r), name(n) {}

    void addChild(std::shared_ptr<UIElement> child) {
        children.push_back(child);
    }

    void draw() override {
        renderer->renderPanel(name);
        for (auto& child : children) child->draw();
    }
};

//18
#include <functional>

// Команды
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class UpdateCommand : public Command {
private:
    std::function<void()> action;
public:
    UpdateCommand(std::function<void()> a) : action(a) {}
    void execute() override { action(); }
};

class RenderCommand : public Command { /* реализация */ };
class DeleteCommand : public Command { /* реализация */ };

// Компонент с поддержкой команд
class GameObject {
protected:
    std::string name;
    std::vector<std::shared_ptr<Command>> commands;
public:
    GameObject(const std::string& n) : name(n) {}

    void addCommand(std::shared_ptr<Command> cmd) {
        commands.push_back(cmd);
    }

    virtual void applyCommands() {
        for (auto& cmd : commands) cmd->execute();
    }

    virtual void update() = 0;
    virtual void render() = 0;
};

class Scene : public GameObject {
private:
    std::vector<std::shared_ptr<GameObject>> objects;
public:
    Scene(const std::string& n) : GameObject(n) {}

    void addObject(std::shared_ptr<GameObject> obj) {
        objects.push_back(obj);
    }

    void applyCommands() override {
        GameObject::applyCommands();
        for (auto& obj : objects) obj->applyCommands();
    }

    void update() override { /* реализация */ }
    void render() override { /* реализация */ }
};

//19
class FileSystemComponent {
public:
    virtual size_t getSize() const = 0;
    virtual void display(int depth = 0) const = 0;
    virtual std::shared_ptr<FileSystemComponent> find(const std::string& name) = 0;
    virtual ~FileSystemComponent() = default;
};

class File : public FileSystemComponent {
private:
    std::string name;
    size_t size;
public:
    File(const std::string& n, size_t s) : name(n), size(s) {}

    size_t getSize() const override { return size; }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "- " << name
                  << " (" << size << " bytes)\n";
    }

    std::shared_ptr<FileSystemComponent> find(const std::string& searchName) override {
        return (name == searchName) ?
            std::static_pointer_cast<FileSystemComponent>(
                std::shared_ptr<File>(this)) : nullptr;
    }
};

class Folder : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
public:
    Folder(const std::string& n) : name(n) {}

    void add(std::shared_ptr<FileSystemComponent> component) {
        children.push_back(component);
    }

    size_t getSize() const override {
        size_t total = 0;
        for (const auto& child : children) total += child->getSize();
        return total;
    }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "+
//20
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// Общий интерфейс компонента (требование 1)
class MenuComponent {
public:
    virtual void display(int depth = 0) const = 0;
    virtual int count() const = 0;
    virtual std::shared_ptr<MenuComponent> find(const std::string& name) = 0;
    virtual bool remove(const std::string& name) = 0;
    virtual ~MenuComponent() = default;
};

// Листовой компонент — пункт меню (MenuItem)
class MenuItem : public MenuComponent {
private:
    std::string name;
    std::string action;
#public:
    MenuItem(const std::string& n, const std::string& a = "")
        : name(n), action(a) {}

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "- " << name << "\n";
    }

    int count() const override { return 1; }

    std::shared_ptr<MenuComponent> find(const std::string& searchName) override {
        return (name == searchName) ?
            std::static_pointer_cast<MenuComponent>(
                std::make_shared<MenuItem>(*this)) : nullptr;
    }

    bool remove(const std::string&) override { return false; } // Листовой элемент не может удалять
};

// Составной компонент — меню (Menu)
class Menu : public MenuComponent {
private:
    std::string name;
    // Хранение детей через базовый тип (требование 2)
    std::vector<std::shared_ptr<MenuComponent>> children; // Использование умных указателей (требование 5)
#public:
    Menu(const std::string& n) : name(n) {}

    void add(std::shared_ptr<MenuComponent> component) {
        children.push_back(component);
    }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "+ " << name << "\n";
        for (const auto& child : children) {
            child->display(depth + 1); // Рекурсивный вызов (требование 3)
        }
    }

    int count() const override {
        int total = 1; // Сам Menu
        for (const auto& child : children) {
            total += child->count(); // Рекурсивный подсчёт (требование 3)
        }
        return total;
    }

    std::shared_ptr<MenuComponent> find(const std::string& searchName) override {
        if (name == searchName) return std::static_pointer_cast<MenuComponent>(shared_from_this());

        for (auto& child : children) {
            auto result = child->find(searchName);
            if (result) return result;
        }
        return nullptr;
    }

    bool remove(const std::string& targetName) override {
        // Используем STL для поиска и удаления (требование 4)
        auto it = std::find_if(children.begin(), children.end(),
            [&targetName](const auto& component) {
                return component->find(targetName) != nullptr;
            });

        if (it != children.end()) {
            children.erase(it);
            return true;
        }

        // Рекурсивный поиск в подменю
        for (auto& child : children) {
            if (auto menu = std::dynamic_pointer_cast<Menu>(child)) {
                if (menu->remove(targetName)) return true;
            }
        }
        return false;
    }
};
int main() {
    auto mainMenu = std::make_shared<Menu>("Main Menu");

    mainMenu->add(std::make_shared<MenuItem>("File"));
    mainMenu->add(std::make_shared<MenuItem>("Edit"));

    auto viewMenu = std::make_shared<Menu>("View");
    viewMenu->add(std::make_shared<MenuItem>("Zoom In"));
    viewMenu->add(std::make_shared<MenuItem>("Zoom Out"));

    auto themesMenu = std::make_shared<Menu>("Themes");
    themesMenu->add(std::make_shared<MenuItem>("Light"));
    themesMenu->add(std::make_shared<MenuItem>("Dark"));

    viewMenu->add(themesMenu);
    mainMenu->add(viewMenu);

    mainMenu->add(std::make_shared<MenuItem>("Help"));

    std::cout << "=== MENU STRUCTURE ===\n";
    mainMenu->display(0);

    std::cout << "\nTotal menu items: " << mainMenu->count() << "\n";

    auto found = mainMenu->find("Themes");
    if (found) {
        std::cout << "Found: Themes menu\n";
    } else {
        std::cout << "Themes not found\n";
    }

    std::cout << "\nRemoving 'Zoom Out'...\n";
    if (mainMenu->remove("Zoom Out")) {
        std::cout << "'Zoom Out' removed successfully\n";
    }

    std::cout << "\n=== UPDATED MENU ===\n";
    mainMenu->display(0);
    std::cout << "New total count: " << mainMenu->count() << "\n";

    return 0;
}

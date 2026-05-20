#include <iostream>
using namespace std;
//1
//class Command
//{
//public:
//    virtual void execute() = 0;
//};
//
//class HelloCommand
//{
//public:
//    void print()
//    {
//        cout << "Hello\n";
//    }
//};
//2
class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class Light
{
public:
    void turnOn()
    {
        cout << "Light ON\n";
    }

    void turnOff()
    {
        cout << "Light OFF\n";
    }
};

class TurnOnCommand : public Command
{
private:
    Light* light;

public:
    TurnOnCommand(Light* l) : light(l) {}

    void execute() override
    {
        light->turnOn();
    }
};

class TurnOffCommand : public Command
{
private:
    Light* light;

public:
    TurnOffCommand(Light* l) : light(l) {}

    void execute() override
    {
        light->turnOff();
    }
};

class RemoteControl
{
private:
    Command* command;

public:
    void setCommand(Command* c)
    {
        command = c;
    }

    void pressButton()
    {
        command->execute();
    }
};

int main()
{
    Light lamp;

    TurnOnCommand on(&lamp);
    TurnOffCommand off(&lamp);

    RemoteControl remote;

    remote.setCommand(&on);
    remote.pressButton();

    remote.setCommand(&off);
    remote.pressButton();

    return 0;
}
//3
class Button
{
    Command* command;

public:
    void setCommand(Command* c)
    {
        command = c;
    }

    void press()
    {
        command->execute();
    }
};
class Button
{
    Command* command;

public:
    void setCommand(Command* c)
    {
        command = c;
    }

    void press()
    {
        command->execute();
    }
};
//4

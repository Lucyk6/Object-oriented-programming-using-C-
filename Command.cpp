#include <iostream>
using namespace std;
//1
class Command {
public:
	virtual void execute() = 0;

	virtual ~Command() = default;

};

class HelloCommand :Command {
	void execute() override {
		std::cout << "hello mir\n";
	}

};
//2
class Light {
public:
	void turnOn() {
		cout << "truned on" << endl;
	}
	void turnOff() {
		cout << "truned off" << endl;
	}
};
class TurnedOnCommand : public Command {
private:
	Light* light;
public:
	TurnedOnCommand(Light* l) : light(l) {}
	void execute() override {
		light->turnOn();
	}
};

//3
class Button {
private:
	Command* command;
public:
	Button() : command(nullptr) {}

	void setCommand(Command* c) {
		command = c;
	}
	void press() {
		if (command != nullptr) {
			command->execute();
		}

	}
};
//4
class TurnOffCommand : public Command {
private:
	Light* light;
public:
	TurnOffCommand(Light* l) : light(l) {}
	void execute() override {
		light->turnOff();
	}
};

//5
class Light {
public:
	void turnOn() {
		std::cout << "Light ON\n";
	}

	void turnOff() {
		std::cout << "Light OFF\n";
	}

	void blink() {
		std::cout << "Light is blinking!\n";
	}
};
class BlinkCommand : public Command {
private:
	Light* light;

public:
	BlinkCommand(Light* l) : light(l) {}

	void execute() override {
		light->blink();
	}
};
int main() {
	Light light;

	TurnedOnCommand  onCmd(&light);
	TurnOffCommand offCmd(&light);
	BlinkCommand   blinkCmd(&light);

	Button button1;
	Button button2;
	Button button3;

	button1.setCommand(&onCmd);
	button2.setCommand(&offCmd);
	button3.setCommand(&blinkCmd);

	std::cout << "Pressing button 1 (Turn On):\n";
	button1.press();

	std::cout << "Pressing button 2 (Turn Off):\n";
	button2.press();

	std::cout << "Pressing button 3 (Blink):\n";
	button3.press();

	return 0;
}
//6
class Player {
private:
	int x, y;
public:

	Player() : x(0), y(0) {}
	void moveUp()
	{
		y++;
		cout << "Player moved up to (" << x << ", " << y << ")\n";
	}
	void moveDown()
	{
		y--;
		cout << "Player moved down to (" << x << ", " << y << ")\n";
	}
	void moveLeft()
	{
		x--;
		cout << "Player moved left to (" << x << ", " << y << ")\n";
	}
	void moveRight()
	{
		x++;
		cout << "Player moved right to (" << x << ", " << y << ")\n";
	}
};
class MoveUpCommand : public Command {
private:
	Player* player;
public:
	MoveUpCommand(Player* p) : player(p) {}
	void execute() override { player->moveUp(); }
};

class MoveDownCommand : public Command {
private:
	Player* player;
public:
	MoveDownCommand(Player* p) : player(p) {}
	void execute() override { player->moveDown(); }

};

class MoveLeftCommand : public Command {
private:
	Player* player;
public:
	MoveLeftCommand(Player* p) :player(p) {}
	void execute() override { player->moveLeft(); }

};
class MoveRightCommand : public Command {
private:
	Player* player;
public:
	MoveRightCommand(Player* p) :player(p) {}
	void execute() override { player->moveRight(); }

};
int main() {
	Player player;

	Command* upCmd = new MoveUpCommand(&player);
	Command* downCmd = new MoveDownCommand(&player);
	Command* leftCmd = new MoveLeftCommand(&player);
	Command* rightCmd = new MoveRightCommand(&player);

	upCmd->execute();
	rightCmd->execute();
	downCmd->execute();
	leftCmd->execute();

	delete upCmd;
	delete downCmd;
	delete leftCmd;
	delete rightCmd;
}
//7
class Hero {
private:
	double health;
	double attack_power;
	bool is_defending;

public:
	Hero(double h = 100.0, double ap = 20.0)
		: health(h), attack_power(ap), is_defending(false) {}

	void takeDamage(double damage) {
		if (!is_defending) {
			health -= damage;
		}
		else {
			health -= (damage / 2); 
		}
		cout << "Hero takes " << damage << " damage. Health: " << health << endl;
	}

	void attack(Hero& target) {
		cout << "Hero attacks with power " << attack_power << "!" << endl;
		target.takeDamage(attack_power);
	}

	void heal() {
		health += 20;
		cout << "Hero heals +20 HP. Health: " << health << endl;
	}

	void setDefending(bool state) {
		is_defending = state;
		if (state) {
			cout << "Defense mode activated!" << endl;
		}
		else {
			cout << "Defense mode deactivated." << endl;
		}
	}

	bool isDefending() const { return is_defending; }
	double getHealth() const { return health; }
};
//8
class SmartHome {
public:
    void turnOnLight() { std::cout << "Light turned ON\n"; }
    void turnOffLight() { std::cout << "Light turned OFF\n"; }
    void turnOnAC() { std::cout << "AC turned ON\n"; }
    void openDoor() { std::cout << "Door opened\n"; }
};

class TurnOnLightCommand : public Command {
private:
    SmartHome* home;
public:
    TurnOnLightCommand(SmartHome* h) : home(h) {}
    void execute() override { home->turnOnLight(); }
};

class TurnOffLightCommand : public Command {
private:
    SmartHome* home;
public:
    TurnOffLightCommand(SmartHome* h) : home(h) {}
    void execute() override { home->turnOffLight(); }
};

class TurnOnACCommand : public Command {
private:
    SmartHome* home;
public:
    TurnOnACCommand(SmartHome* h) : home(h) {}
    void execute() override { home->turnOnAC(); }
};

class OpenDoorCommand : public Command {
private:
    SmartHome* home;
public:
    OpenDoorCommand(SmartHome* h) : home(h) {}
    void execute() override { home->openDoor(); }
};
//9
class FileSystem {
public:
    void createFile(const std::string& name) {
        std::cout << "File '" << name << "' created\n";
    }
    void deleteFile(const std::string& name) {
        std::cout << "File '" << name << "' deleted\n";
    }
    void renameFile(const std::string& oldName, const std::string& newName) {
        std::cout << "File '" << oldName << "' renamed to '" << newName << "'\n";
    }
};

class CreateFileCommand : public Command {
private:
    FileSystem* fs;
    std::string filename;
public:
    CreateFileCommand(FileSystem* f, const std::string& name)
        : fs(f), filename(name) {}
    void execute() override { fs->createFile(filename); }
};

class DeleteFileCommand : public Command {
private:
    FileSystem* fs;
    std::string filename;
public:
    DeleteFileCommand(FileSystem* f, const std::string& name)
        : fs(f), filename(name) {}
    void execute() override { fs->deleteFile(filename); }
};

class RenameFileCommand : public Command {
private:
    FileSystem* fs;
    std::string oldName, newName;
public:
    RenameFileCommand(FileSystem* f, const std::string& old, const std::string& nw)
        : fs(f), oldName(old), newName(nw) {}
    void execute() override { fs->renameFile(oldName, newName); }
};
//10
#include <queue>

int main() {
    FileSystem fs;
    std::queue<Command*> taskQueue;

    taskQueue.push(new CreateFileCommand(&fs, "document.txt"));
    taskQueue.push(new RenameFileCommand(&fs, "document.txt", "report.txt"));
    taskQueue.push(new DeleteFileCommand(&fs, "report.txt"));

    while (!taskQueue.empty()) {
        Command* cmd = taskQueue.front();
        taskQueue.pop();
        cmd->execute();
        delete cmd; // Освобождаем память
    }

    return 0;
}
//11
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class MoveRightCommand : public Command {
private:
    Player* player;
    int prevX;
public:
    MoveRightCommand(Player* p) : player(p), prevX(p->getX()) {}
    
    void execute() override {
        player->moveRight();
    }
    
    void undo() override {
        player->setPosition(prevX, player->getY());
        std::cout << "Undo: Player moved back to (" << prevX << ", " << player->getY() << ")\n";
    }
};
//12-13
#include <stack>

class CommandManager {
private:
    std::stack<Command*> history;
    std::stack<Command*> redoStack; 

public:
    void executeCommand(Command* cmd) {
        cmd->execute();
        history.push(cmd);
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undoLastCommand() {
        if (!history.empty()) {
            Command* lastCmd = history.top();
            history.pop();
            lastCmd->undo();
            redoStack.push(lastCmd);
        } else {
            std::cout << "No commands to undo\n";
        }
    }

    void redoLastCommand() {
        if (!redoStack.empty()) {
            Command* redoCmd = redoStack.top();
            redoStack.pop();
            redoCmd->execute();
            history.push(redoCmd);
        } else {
            std::cout << "No commands to redo\n";
        }
    }
};
//15
std::stack<Command*> redoStack;

void undoLastCommand() {
    if (!history.empty()) {
        Command* lastCmd = history.top();
        history.pop();
        lastCmd->undo();
        redoStack.push(lastCmd);
    }
}

void redoLastCommand() {
    if (!redoStack.empty()) {
        Command* redoCmd = redoStack.top();
        redoStack.pop();
        redoCmd->execute();
        history.push(redoCmd);
    }
}
//16
class MacroCommand : public Command {
private:
    std::vector<Command*> commands;
public:
    void addCommand(Command* cmd) {
        commands.push_back(cmd);
    }

    void execute() override {
        for (auto cmd : commands) {
            cmd->execute();
        }
    }

    void undo() override {
        for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
            (*it)->undo();
        }
    }
};

int main() {
    Player player;
    MacroCommand macroCmd;

    macroCmd.addCommand(new MoveUpCommand(&player));
    macroCmd.addCommand(new MoveRightCommand(&player));

    CommandManager manager;
    manager.executeCommand(&macroCmd); 

    return 0;
}
//17
class LoggedCommand : public Command {
private:
    Command* wrappedCommand;
    std::string name;
public:
    LoggedCommand(Command* cmd, const std::string& cmdName)
        : wrappedCommand(cmd), name(cmdName) {}

    void execute() override {
        std::cout << "Executing: " << name << "\n";
        wrappedCommand->execute();
    }

    void undo() override {
        std::cout << "Undoing: " << name << "\n";
        wrappedCommand->undo();
    }
};
LoggedCommand loggedAttack(new AttackCommand(&player, &enemy), "Attack");
//18
#include <memory>

class Button {
private:
    std::unique_ptr<Command> command;
public:
    template<typename T, typename... Args>
    void setCommand(Args&&... args) {
        command = std::make_unique<T>(std::forward<Args>(args)...);
    }

    void press() {
        if (command) {
            command->execute();
        }
    }
};

main
Button button;
button.setCommand<MoveUpCommand>(&player);
button.press();
//19
class CommandFactory {
public:
    static Command* createCommand(const std::string& type, Hero* hero, Hero* target = nullptr) {
        if (type == "attack" && target) {
            return new AttackCommand(hero, target);
        } else if (type == "heal") {
            return new HealCommand(hero);
        } else if (type == "defend") {
            return new DefendCommand(hero);
        } else {
            throw std::invalid_argument("Unknown command type");
        }
    }
};

Hero player, enemy;
Command* attackCmd = CommandFactory::createCommand("attack", &player, &enemy);
//20
#include <map>
#include <vector>

int main() {
    Player player;
    CommandManager manager;
    std::map<char, Command*> keyCommands;

    keyCommands['w'] = new MoveUpCommand(&player);
    keyCommands['s'] = new MoveDownCommand(&player);
    keyCommands['a'] = new MoveLeftCommand(&player);
    keyCommands['d'] = new MoveRightCommand(&player);

    char input;
    while (true) {
        std::cin >> input;
        switch (input) {
            case 'w': case 's': case 'a': case 'd':
                manager.executeCommand(keyCommands[input]);
                break;
            case 'u':
                manager.undoLastCommand();
                break;
            case 'q':
                return 0;
            default:
                std::cout << "Unknown command\n";
        }
    }

    // Освобождение памяти
    for (auto& pair : keyCommands) {
        delete pair.second;
    }
    return 0;
}


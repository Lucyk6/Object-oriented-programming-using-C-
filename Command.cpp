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

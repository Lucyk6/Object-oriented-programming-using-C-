#include <iostream>
#include <vector>
using namespace std;
class Component {
public:
	virtual void operation() = 0;

	virtual  ~Component() {}
};

class Leaf : public Component {
public :
	void operation() override
	{
		cout << "Leaf operation\n";

	}
};

class Composite : public Component {
private:
	vector <Component*> children;
public:
	void add (Component* component)
	{
		children.push_back(component);

	}

	void operation() {
		for (Component* child : children) 
		{
			child->operation();
		}
	}
};

#include <stdio.h>

class A
{
	public:
		void display();
		virtual void show();
};

void A::display()
{
	printf("This is display of class A\n");
}

void A::show()
{
	printf("This is show of class A\n");
}

class B : public A
{
	public:
		void display();
		virtual void show(); // Note that class B needn't overload show.
		                     // Virtual func are for run time polymorphism
		void show(int);
		void get();
};

void B::display()
{
	printf("This is display of class B\n");
}


void B::show()
{
	printf("This is show of class B\n");
}


void B::show(int x)
{
	printf("Value of x is %d\n", x);
}

void B::get()
{
	printf("This is get method of B\n");
}

int main()
{
	A a;
	B b;
	A &refa = a;
	A &refb = b;

	refa.display();  // call display() associated with type of refa
	refb.display();  // call display() associated with type of refb
	refa.show();	// call show() associated with object being referred
	refb.show();    // call show() associated with object being referred
	b.show(20);
	// refb.get(); //  error: 'class A' has no member named 'get'
	return 1;
}

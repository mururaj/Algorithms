#include <iostream>
using namespace std;

class A
{
	public:
	A()
	{
		// initialize the member variables
		x = 0;
		y = 0;
	}

	void display();

	void operator++();
	void operator++(int);

	private:
		int x, y;
};

// A simple display method to output the member vars
void A::display()
{
	cout<<"x ="<<x<< " y="<<y<<"\n";
}

// overloading prefix ++ to auto increment member vars
void A::operator++()
{
	++x;
	++y;
}

// overloading postfix ++ to auto increment member vars
void A::operator++(int)
{
	x++;
	y++;
}

int main()
{
	A obj1;
	obj1.display();
	++obj1;
	obj1++;
	obj1.display();
}

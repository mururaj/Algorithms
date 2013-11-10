#include <iostream>

using namespace std;

class A
{
	public:
	A()
	{
		x = 0;
		y = 0;
	}

	A(int m,int n)
	{
		x = m;
		y = n;
	}

	void display();

	A operator+(A);

	private:
		int x,y;
};

// display member vars
void A::display()
{
	cout<<"x="<<x<<" y="<<y;
}

// overloading + operator
A A::operator+(A obj)
{
	A newObj;
	
	newObj.x = x + obj.x;
	newObj.y = y + obj.y;

	return newObj;
}

int main()
{
	A obj1(100,100), obj2(50,50);
	
	// overloading +
	A obj3 = obj1 + obj2;

	obj3.display();
	
	return 0;
}

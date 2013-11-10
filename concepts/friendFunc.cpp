#include <stdio.h>

class B;

class A
{
	public:
		A()
		{
			mydata = 10;
		}
		friend int display(A a, B b);
	private:
		int mydata;
};

class B
{
	public:
		B()
		{
			mydata = 20;
		}
		friend int display(A a, B b);
	private:
		int mydata;
};

int display(A a, B b)
{
	printf("%d %d\n",a.mydata,b.mydata);
}

int main()
{
	A a;
	B b;
	display(a,b);
	// printf("%d", a.mydata); 'int A::mydata' is private
	return 1;
}

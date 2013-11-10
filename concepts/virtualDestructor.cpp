#include <stdio.h>

class A
{
	public:
		~A()
		{
			printf("Destructor of A being called\n");
		}
};

class B : public A
{
	public:
		~B()
		{
			printf("Destructor of B being called\n");
		}
};

class C 
{
	public:
		virtual ~C()
		{
			printf("Destructor of C being called\n");
		}
};

class D : public C
{
	public:
		virtual ~D()
		{
			printf("Destructor of D being called\n");
		}
};

int main()
{
	A *refb = new B();
	C *refd = new D();
	delete refb;  // Call destructor of A (only base class)
	delete refd;  // Call destructor of D & C (both derived,base class)
	return 0;
}

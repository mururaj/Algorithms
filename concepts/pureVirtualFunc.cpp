#include <stdio.h>

// Class A has pure virtual function
// It is treated as abstract class
class A
{
	public:
		virtual void show() = 0;
};

// Class B derving A must redefine the pure virtual functions
// of A. If not, B will also be treated as abstract class
class B : public A
{
	public:
		// void show(); if not redefined, it will be considered as pure virtual within B
	    // B must redefine show
		void show();
	    void display();
};

void B::show()
{
	printf("Class B is redefining pure virtual function\n");
}

void B::display()
{
	printf("Class B has its own display function\n");
}

int main()
{
	A *aobj1;
	// A aobj2; Not allowed Not that objects can't be instantiated for abstract class
	/*
	 error: cannot declare variable 'aobj2' to be of abstract type 'A'
	 because the following virtual functions are pure within 'A':
	  virtual void A::show()
	*/

	B bobj;
	aobj1 = & bobj;
	
	aobj1->show();
	bobj.show();
	((B *)aobj1)->display(); // typecast base class obj to access derived class method

	return 0;
}

#include <stdio.h>

class myClass
{
	public:
		int i;
		myClass() { i=100; }
		void doSomething() { printf("I do something \n"); }
		void doNothing() volatile { printf("I do nothing \n"); }
		void doMore() volatile { 
			// doSomething(); Error calling non volatile function
			doNothing();
			printf("I do something more \n"); }
		void touchVar() const {
			// i = 100; constant function can't modify member variables
			printf("value of i is %d \n",i);
		}
};
int main()
{
	myClass myObj;
	myObj.doMore();
	myObj.touchVar();
	return 1;
}

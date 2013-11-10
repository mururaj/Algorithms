#include <iostream>

using namespace std;

template <class T>
void display(T a,T b) 
{
	cout<<"a="<<a<<" b="<<b<<"\n";
}

template <class T,class P>
void sum(T a,P b)
{
	cout<<"a+b ="<<a+b<<"\n";
}

int main()
{
	int x = 10, y = 20;
	float p = 1.1, q = 2.2;
	char m = 'a', n = 'b';

	display(x,y);
	display(p,q);
	display(m,n);

	sum(x,p);

	return 0;
}

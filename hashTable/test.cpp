#include <iostream>

using namespace std;

class A
{
	public:
		A(int mySize) : size(mySize)
		{
			myArray = new int[mySize];
			myArray[0] = 10;			
		}
		
		void display() const
		{
			cout<<size<<"\n";
		}

	private:
		const int size;
		int *myArray;
};

int main()
{
	const int size = 2;
	int a[size] = { 10, 11 };

	cout<<a[0]<<" "<<a[1]<<"\n";

	A b(10);

	b.display();

	return 1;
}

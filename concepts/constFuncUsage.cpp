#include <stdio.h>

class Demo
{
	public:
		int getData () const;
	    int printData () const;
		int setData(int);
	private:
		int mydata;
};

int Demo::getData() const
{
	// mydata = mydata+100; // error: assignment of data-member 'Demo::mydata' in read-only structure
	// setData(50); // const function can't call non const function(s)
	printData(); // const function can call any const functions
	return mydata;
}

int Demo::setData(int data)
{
	return (mydata = data);
}

int Demo:: printData() const
{
	printf("%d",mydata);
	return 1;
}

int main()
{
	Demo d;
	d. setData(100);
	printf("%d",d.getData());	
	return 0;
}

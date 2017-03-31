template <class T>
class GenStack
{
public:
	GenStack();
	GenStack(int maxSize);
	~GenStack();
	
	void push(T data);
	T pop();
	T peek();
	
	int isFull();
	int isEmpty();
	
	int top;
	int max;
	T *myArray;
};

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

template <class T>
GenStack<T>::GenStack(){}

template <class T>
GenStack<T>::GenStack(int maxSize)
{
	myArray = new T[maxSize];
	max = maxSize;
	top = -1;
}

template <class T>
GenStack<T>::~GenStack()
{
	delete myArray;
}

template <class T>
void GenStack<T>::push(T data) 
{
	//IF FULL ALLOCATE MORE SPACE
	if (top == max-1)
	{
		//create a temp array to hold the current stack data
		T *t1 = new T[max];

		for (int i = 0; i < max; ++i)
		{
			t1[i] = myArray[i];
		}

		//recreate the member variable array at twice its current size
		myArray = new T[max*2];

		//refill it with its old values
		for (int i = 0; i < max; ++i)
		{
			myArray[i] = t1[i];
		}

		//set the new maximum size to be twice as large
		max = max * 2;

	}

	//if not full, push as usual
	myArray[++top] = data;
}

template <class T>
T GenStack<T>::pop()
{
	if (top != -1)
		return myArray[top--];

	//in the case that you try to pop off an empty stack, return
	else
	{
		cout << "Error - attempt to pop off an empty stack." << endl;
		return 0;
	}
}

template <class T>
T GenStack<T>::peek()
{
	return myArray[top];
}

template <class T>
int GenStack<T>::isFull()
{
	return (top == max-1);
}

template <class T>
int GenStack<T>::isEmpty()
{
	return (top == -1);
}
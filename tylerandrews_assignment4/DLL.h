#include "ListNode.h"

template <class T>
class DLL
{
	//private:

	public:
		DLL();
		~DLL();
		T removeFront();
		void insertBack(T d);
		unsigned int getSize();
		void printList();
        bool isEmpty();

		ListNode<T> *front;
		ListNode<T> *back;
		unsigned int size;
};

template <class T>
DLL<T>::DLL()
{
	size = 0;
	front = NULL;
	back = NULL;
}

template <class T>
DLL<T>::~DLL(){};

template <class T>
unsigned int DLL<T>::getSize()
{
	return size;
}

template <class T>
void DLL<T>::insertBack(T d)
{
	ListNode<T> *node = new ListNode<T>(d);

	// IF LIST IS EMPTY
	if (size == 0)
	{
		front = node;
	}

	else
	{
		back->next = node;
		node->prev = back;
	}

	back = node;
	//node = back;
	++size;
}

template <class T>
T DLL<T>::removeFront()
{

	ListNode<T> *oldFront = front;

    T oldData = oldFront->data;

    // IF THERE IS ONLY ONE ELEMENT
	if (front->next == NULL)
	{
        front = NULL;
        back = NULL;
	}

    // MORE THAN ONE ELEMENT
	else
	{
		front->next->prev = NULL;

        front = front->next;
	}

	delete oldFront;

	size--;

	return oldData;
}

template <class T>
void DLL<T>::printList()
{
	ListNode<T> *current = front;

	while (true)
	{
		if (current->next == NULL)
		{
			break;
		}

		cout << current->data << endl;
		current = current->next;
	}
}

template <class T>
bool DLL<T>::isEmpty()
{
    return (size == 0);
}

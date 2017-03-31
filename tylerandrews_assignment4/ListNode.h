#include <iostream>

using namespace std;

template <class T>
class ListNode
{
	public:
		ListNode();
		~ListNode();
		ListNode(T data);

        T data;
        ListNode<T> *next;
        ListNode<T> *prev;
};

template <class T>
ListNode<T>::ListNode(){};

template <class T>
ListNode<T>::~ListNode()
{
	if (next != NULL)
	{
		next = NULL;
		prev = NULL;

		delete next;
	}
}

template <class T>
ListNode<T>::ListNode(T data)
{
	data = data;
	next = NULL;
	prev = NULL;
}

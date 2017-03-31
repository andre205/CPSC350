#include "DLL.h"

template <class T>
class Queue
{
	private:
		DLL<T> queueList;
		int queueSize;
	public:
		Queue(){};
		~Queue();

		void enqueue(T data)
		{
			queueList.insertBack(data);
		}

		T dequeue()
		{
			return queueList.removeFront();
		}
		
		T peek()
		{
			return queueList.getFront();
		}

		bool isEmpty()
		{
			return queueList.isEmpty();
		}
		
		int getSize()
		{
			return queueList.getSize();
		}

		
};

#include "Error.h"

template<class T>
class NODE
{
public:	
	NODE *pNext{};
	T data{};
	NODE() = default;
	NODE(const T & item) : data(item) {}
};

template<class T>
class Stack
{
public:
	Stack() = default;
	~Stack();
	T Peek() const;
	T Pop() const;
	void Push(const T &);
	bool StackEmpty() const;
private:
	mutable NODE<T> *pTop{};
};

template<class T>
Stack<T>::~Stack()
{
	while (pTop != nullptr)
	{
		NODE<T> *pTemp = pTop->pNext;
		delete pTop;
		pTop = pTemp;
	}
}

template<class T>
void Stack<T>::Push(const T & item)
{
	NODE<T> *pTemp = pTop;
	pTop = new NODE<T>(item);
	pTop->pNext = pTemp;
}

template<class T>
T Stack<T>::Peek() const
{
	if (pTop == nullptr)
	{
		throw Error(empty_st);
	}
	return pTop->data;
}

template<class T>
T Stack<T>::Pop() const
{
	if (pTop == nullptr)
	{
		throw Error(empty_st);
	}
	NODE<T> *pTemp = pTop->pNext;
	T temp = pTop->data;
	delete pTop;
	pTop = pTemp;
	return temp;
}

template<class T>
bool Stack<T>::StackEmpty() const
{
	return pTop == nullptr;
}


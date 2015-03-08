#pragma once
template <typename T>
class UStack
{
public:
	UStack(int capacity = 64);
	~UStack(void);
	void Push(T item);
	void Pop();
	void Clear();
	T Peek() const;
	 
private:
	T * data;
	int marker;
	int size;
	int capacity;
};

template <typename T>
T UStack<T>::Peek() const
{
	return data[marker - 1];
}

template <typename T>
void UStack<T>::Clear()
{
	marker = 0;
	size = 0;
}

template <typename T>
void UStack<T>::Pop()
{
	if (marker > 0)
	{
		marker--;
	}
	else
	{
		Debug::Logger::Log("Stack is empty, failed to pop.");
	}
}

template <typename T>
void UStack<T>::Push(T item)
{
	if (marker < capacity)
	{
		data[marker++] = item;
	}
	else
	{
		Debug::Logger::Log("Stack is full, failed to push item on stack.");
	}
}

template <typename T>
UStack<T>::UStack(int cap ):
	marker(0),
	size(0),
	capacity(cap)
{
	data = static_cast<T*> (::operator new (sizeof(T )* cap));
	
}

template <typename T>
UStack<T>::~UStack(void)
{
}

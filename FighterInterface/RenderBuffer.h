#pragma once

template <typename T>
class RenderBuffer
{
public:
	RenderBuffer(int capacity);
	~RenderBuffer(void);

	void Add(T val);
	void Clear();
	void AddRange(T * values, int count);
	T * GetData() {return data;}
	inline int GetMarkerPosition() { return mPosition; }
	inline int GetCapacity(){ return mCapacity; }

private:
	int mPosition;
	int mCapacity;
	T * data;
	char * mTextureName; 
};

template <typename T>
RenderBuffer<T>::RenderBuffer(int capacity = 1000)
	:mPosition(0),
	mCapacity(capacity)
{
	data = new T[capacity];
}  

template <typename T>
RenderBuffer<T>::~RenderBuffer(void)
{
}

template <typename T>
void RenderBuffer<T>::AddRange(T * values, int count)
{
	if (mPosition + count >= mCapacity)
	{
		//error
	}
	else
	{
		memcpy(data + mPosition, values, sizeof(T) * count);
		mPosition += count;
	}
}

template <typename T>
void RenderBuffer<T>::Clear()
{
	mPosition = 0;
}

template <typename T>
void RenderBuffer<T>::Add(T val)
{
	data[mPosition] = val;
	mPosition++;
}


#include <iostream>
#include <stdlib.h>
#ifndef DARRAY_H
#define DARRAY_H

template<typename T>
class DArray final
{
private:
	T* array;
	int capacity;
	int DEFAULT_CAPACITY = 8;
	int length;

public:
	class Iterator {
	private:
		int current;
		DArray* arr;
		bool isForward;
		int direction;
	public:
		Iterator(DArray* array, bool isForward) {
			this->isForward = isForward;
			current = isForward ? 0 : array -> size()-1;
			arr = array;
			direction = isForward ? 1 : -1;
		}

		const T& get() const {
			return (*arr)[current];
		};

		void next() {
			current += direction;
		};

		void set(const T& value) {
			(*arr)[current] = value;
		}

		bool hasNext() const {
			if (isForward) return (current + 1) < arr -> size();
			else return (current - 1) >= 0;
		}

		Iterator& operator++() { current += direction; return *this; };
		Iterator operator++(int d) { Iterator buff = *this; current += direction; return buff; };

		Iterator& operator--() { current -= direction; return *this; };
		Iterator operator--(int d) { Iterator buff = *this; current -= direction; return buff; };
	};

	DArray();
	DArray(int capacity);
	DArray(const DArray& other);
	DArray(DArray<T>&& other) noexcept;
	~DArray();

	void resize(int newSize);
	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	int size();

	Iterator iterator() {
		return Iterator(this, true);
	};

	Iterator reverseIterator() {
		return Iterator(this, false);
	};

	T& operator [](int index)
	{
		return array[index];
	};

	template<typename T>
	DArray& operator=(const DArray& other)
	{
		if (this != &other)
		{
			capacity = other.capacity;
			length = other.length;
			array = (T*)malloc(sizeof(T) * capacity);
			for (int i = 0; i < length; i++) {
				new(array + i) T(other.array[i]);
			}
		}
		return *this;
	};

	template<typename T>
	DArray& operator=(DArray&& other) noexcept
	{
		for (int i = 0; i < length; i++) {
			array[i].~T();
		}
		free(array);

		capacity = other.capacity;
		length = other.length;
		array = other.array;

		other.array = nullptr;
		other.capacity = DEFAULT_CAPACITY;
		other.length = 0;

		return *this;
	};
};

template<typename T>
DArray<T>::DArray()
{
	this->capacity = 8;
	this->length = 0;
	array = (T*)malloc(sizeof(T) * capacity);
}

template<typename T>
DArray<T>::DArray(int capacity)
{
	this->capacity = capacity;
	this->length = 0;
	array = (T*)malloc(sizeof(T) * capacity);
}

template<typename T>
DArray<T>::DArray(const DArray& other)
{
	capacity = other.capacity;
	length = other.length;
	array = (T*)malloc(sizeof(T) * capacity);
	for (int i = 0; i < length; i++) {
		new(array + i) T(other.array[i]);
	}
}

template<typename T>
DArray<T>::DArray(DArray&& other) noexcept
{
	capacity = other.capacity;
	length = other.length;
	free(array);
	array = other.array;
	other.length = 0;
	other.capacity = 8;
	other.array = nullptr;
}

template<typename T>
void DArray<T>::resize(int newSize)
{
	T* newArray = (T*)malloc(sizeof(T) * newSize);

	for (int i = 0; i < capacity; i++) {
		new(newArray + i) T(std::move(array[i]));
		array[i].~T();
	}
	free(array);

	capacity = newSize;
	array = newArray;
	newArray = nullptr;
}

template<typename T>
int DArray<T>::insert(const T& value)
{
	if (length == capacity) {
		this->resize(capacity * 2);
	}
	new(array + length) T(value);
	length += 1;
	return length - 1;
}

template<typename T>
int DArray<T>::insert(int index, const T& value)
{
	if (index < 0 || index >= length) {
		return -1;
	}
	if (length == capacity) {
		this->resize(capacity * 2);
	}
	for (int i = length; i >= index; i--) {
		new(array + i + 1) T(std::move(array[i]));
	}
	new(array + index) T(value);
	length += 1;
	return index;
}

template<typename T>
void DArray<T>::remove(int index)
{
	if (index < 0 || index > length) {
		return;
	}
	for (int i = index; i < length - 1; i++) {
		array[i].~T();
		new(array + i) T(std::move(array[i + 1]));
	}
	array[length - 1].~T();
	length -= 1;
}

template<typename T>
int DArray<T>::size()
{
	return length;
}

template<typename T>
DArray<T>::~DArray()
{
	for (int i = 0; i < length; i++) {
		array[i].~T();
	}
	free(array);
}


#endif
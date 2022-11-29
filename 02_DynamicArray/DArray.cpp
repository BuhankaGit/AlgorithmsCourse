#include "DArray.h"

template<typename T>
DArray<T>::DArray()
{
	this -> capacity = 8;
	this -> length = 0;
	array = (T*)malloc(sizeof(T) * capacity);
}

template<typename T>
DArray<T>::DArray(int capacity)
{
	this -> capacity = capacity;
	this -> length = 0;
	array = (T*)malloc(sizeof(T) * capacity);
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
		this -> resize(capacity * 2);
	}
	new(array + length) T(value); 
	length += 1;
	return length - 1;
}

template<typename T>
int DArray<T>::insert(int index, const T& value)
{
	if (index < 0 && index >= capacity) {
		return -1;
	}
	if (length == capacity) {
		this -> resize(capacity *2);
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
	if (index < 0 && index > length) {
		return;
	}
	for (int i = index; i < length; i++) {
		new(array + i) T(std::move(array[i+1]));
	}
	length -= 1;
}

template<typename T>
int DArray<T>::size()
{
	return length;
}

template<typename T>
int DArray<T>::getCapacity()
{
	return capacity;
}

template<typename T>
void DArray<T>::showData()
{
	std::cout << this->size() << std::endl;
	std::cout << this->capacity << std::endl;
	for (int i = 0; i < length; i++) {
		std::cout << array[i] << std::endl;
	}
}

template<typename T>
DArray<T>::~DArray()
{
	free(array);
}


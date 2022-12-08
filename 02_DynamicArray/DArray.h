#pragma once
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
	int length;

public:
	class Iterator {
	private:
		int current;
		DArray* arr;
		bool isForward;
	public:
		Iterator(DArray* array, bool isForward) {
			this->isForward = isForward;
			current = isForward ? 0 : array -> size()-1;
			arr = array;
		}

		const T& get() const {
			return (*arr)[current];
		};

		void next() {
			int direction = isForward ? 1 : -1;
			current += direction;
		};

		void set(const T& value) {
			(*arr)[current] = value;
		}

		bool hasNext() const {
			if (isForward) return (current + 1) < arr -> size();
			else return (current - 1) >= 0;
		}
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
		other.capacity = 8;
		other.length = 0;

		return *this;
	};
};

#include "DArray.cpp"


#endif
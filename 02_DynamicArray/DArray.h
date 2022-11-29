#include <iostream>
#include <stdlib.h>

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
		T* first;
		T* last;
		T* current;
		bool isForward;
	public:
		Iterator(T* start, T* end, bool isForward) {
			this->isForward = isForward;
			if (isForward) {
				first = current = start;
				last = end;
			}
			else {
				first = start;
				last = current = end;
			}
		}

		const T& get() const {
			return *current;
		};

		void next() {
			int direction = isForward ? 1 : -1;
			current += direction;
		};

		void set(const T& value) {
			*current = value;
		}

		bool hasNext() const {
			T edgeEl;
			if (isForward) {
				return current != last;
			}
			else {
				return  current != first;
			}
		}
	};

	DArray();
	DArray(int capacity);

	void resize(int newSize);
	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	Iterator iterator() {
		return Iterator(array, array + length - 1, true);
	};
	Iterator reverseIterator() {
		return Iterator(array, array + length - 1, false);
	};

	T& operator [](int index)
	{
		return array[index];
	};

	DArray& operator =(const DArray& second)
	{
		if (this != &second)
		{
			capacity = second.capacity;
			length = second.length;
			free(array);
			array = second.array;
		}
		return *this;
	};
	int size();
	int getCapacity();
	//DEBUG
	void showData();
	~DArray();
};


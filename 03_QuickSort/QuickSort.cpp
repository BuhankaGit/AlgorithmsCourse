#include <iostream>
#include <random>

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    int optimSize = 4;
    while (first < last)
    {
        if (last - first < optimSize)
        {
            insertion(first, last, comp);
            return;
        }
        else {
            T* medium = first + (last - first) / 2;
            if(comp(*last, *first)) std::swap(*last, *first);
            if(comp(*medium, *first)) std::swap(*medium, *first);
            if(comp(*last, *medium)) std::swap(*last, *medium);
            
            T* q = partition(first, last, comp);

            if (q - first < last - q)
            {
                sort(first, q, comp);
                first = q + 1;
            }
            else 
            {
                sort(q + 1, last, comp);
                last = q - 1;
            }
        }
    }
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp)
{
    T v = *(first + (last - first) / 2);
    T* i = first;
    T* j = last;
    while (i <= j)
    {
        while (comp(*i, v))
        {
            i++;
        }
        while (comp(v, *j))
        {
            j--;
        }
        if (i >= j) {
            break;
        }
        std::swap(*(i++), *(j--));
    }
    std::swap(v, *i);
    return i;
}

template<typename T, typename Compare>
void insertion(T* first, T* last, Compare comp)
{
    for (T* i = first + 1; i <= last; i++)
    {
        T* j = i - 1;
        T temp = *i;
        while (comp(temp, *j) && (j != first))
        {
            *(j + 1) = std::move(*j);
            j--;
        }

        if ((j == first) && comp(temp, *j))
        {
            *(j + 1) = std::move(*j);
            *j = temp;
        }
        else
        {
            *(j + 1) = temp;
        }
    }
}

int main()
{
    std::default_random_engine gen;
    std::uniform_int_distribution<int> distr(-1000, 1000);

    const int size_arr = 1000;
    int arr[size_arr];
    for (int i = 0; i < size_arr; ++i)
        arr[i] = distr(gen);

    sort(arr, arr + 999, [](int a, int b) { return a > b; });
    for (auto i = arr; i <= arr + 999; i++)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}
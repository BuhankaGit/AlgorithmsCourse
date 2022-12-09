#include <iostream>
#include <random>

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    int optimSize = 10;
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
                last = q;
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
    while (true)
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
    return j;
}

template<typename T, typename Compare>
void insertion(T* first, T* last, Compare comp)
{
    for (T* i = first + 1; i <= last; i++)
    {
        T* j = i - 1;
        T temp = *i;

        while (j >= first && comp(temp, *(j)))
        {
            *(j + 1) = std::move(*j);
            j--;
        }
        *(j + 1) = std::move(temp);
    }
}

int main()
{
    exit(0);
}
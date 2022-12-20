#include <iostream>
#include <random>
#include <chrono>
#include <string>

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    int optimSize = 42;
    while (first < last)
    {
        if (last - first < optimSize)
        {
            insertion(first, last, comp);
            return;
        }
        else {
            T* medium = first + (last - first) / 2;
            if (comp(*last, *first)) std::swap(*last, *first);
            if (comp(*medium, *first)) std::swap(*medium, *first);
            if (comp(*last, *medium)) std::swap(*last, *medium);

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
{\
    
    /**
    std::default_random_engine gen;
    std::uniform_int_distribution<int> distr(-1000, 1000);

    for (int size = 2; size <= 100; size++)
    {
        std::vector<int> test_qs(size);
        std::vector<int> test_is(size);
        for (int i = 0; i < size; ++i)
        {
            test_qs[i] = distr(gen);
            test_is[i] = test_qs[i];
        }
        auto begin = std::chrono::high_resolution_clock::now();
        sort(&test_qs[0], &test_qs[size - 1], [](int a, int b) { return a < b; });
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - begin;
        std::cout << std::to_string(diff.count() * 10000.0) << " ";
        auto begin2 = std::chrono::high_resolution_clock::now();
        insertion(&test_is[0], &test_is[size - 1], [](int a, int b) { return a < b; });
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end2 - begin2;
        std::cout << std::to_string(diff2.count() * 10000.0) << std::endl;
    }
    **/

    return 0;
}
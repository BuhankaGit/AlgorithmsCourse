#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "..\QuickSort.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3Tests
{
	TEST_CLASS(IntSort)
	{
	public:
		
		TEST_METHOD(AscendingOrder)
		{
			int arr[15]{5, 9, 0, 1, 3, 4, 5, 3, 6, 7, 3, 5 ,7, 5 ,3};
			sort(arr, arr + 14, [](int a, int b) { return a < b; });
			Assert::IsTrue((arr[0] == 0) && (arr[14] == 9));
		}
		TEST_METHOD(DescendingOrder)
		{
			int arr[15]{ 5, 9, 0, 1, 3, 4, 5, 3, 6, 7, 3, 5 ,7, 5 ,3 };
			sort(arr, arr + 14, [](int a, int b) { return a > b; });
			Assert::IsTrue((arr[0] == 9) && (arr[14] == 0));
		}
		TEST_METHOD(OneElementArray)
		{
			int arr[1]{ 5 };
			sort(arr, arr, [](int a, int b) { return a < b; });
			Assert::IsTrue((arr[0] == 5));
		}
		TEST_METHOD(BigArraySort)
		{
			std::default_random_engine gen;
			std::uniform_int_distribution<int> distr(-50000, 50000);

			const int size_arr = 50000;
			int* arr = new int[size_arr];
			for (int i = 0; i < size_arr; ++i)
			{
				arr[i] = distr(gen);
			}

			sort(arr, arr + 49999, [](int a, int b) { return a < b; });
			Assert::IsTrue(arr[3000] < arr[3001]);
		}
	};

	TEST_CLASS(CharSort)
	{
	public:

		TEST_METHOD(AscendingOrder)
		{
			char arr[15]{ 'm', 'r', 's', 'w', 'e', 'd', 'o', 'k', 'g', 't', 'y', 's' ,'d', 'w' ,'q'};
			sort(arr, arr + 14, [](char a, char b) { return a < b; });
			Assert::IsTrue((arr[0] == 'd') && (arr[14] == 'y'));
		}
		TEST_METHOD(DescendingOrder)
		{
			char arr[15]{ 'm', 'r', 's', 'w', 'e', 'd', 'o', 'k', 'g', 't', 'y', 's' ,'d', 'w' ,'q' };
			sort(arr, arr + 14, [](char a, char b) { return a > b; });
			Assert::IsTrue((arr[0] == 'y') && (arr[14] == 'd'));
		}
	};
	TEST_CLASS(StringSort)
	{
	public:

		TEST_METHOD(AscendingOrder)
		{
			std::string arr[5]{"Test", "String", "Abc", "Xyz", "Develop"};
			sort(arr, arr + 4, [](std::string a, std::string b) { return a.compare(b) > 0; });
			Assert::IsTrue((arr[0].compare("Xyz") == 0) && (arr[4].compare("Abc") == 0));
		}
		TEST_METHOD(DescendingOrder)
		{
			std::string arr[5]{ "Test", "String", "Abc", "Xyz", "Develop" };
			sort(arr, arr + 4, [](std::string a, std::string b) { return a.compare(b) < 0; });
			Assert::IsTrue((arr[0].compare("Abc") == 0) && (arr[4].compare("Xyz") == 0));
		}
	};
}

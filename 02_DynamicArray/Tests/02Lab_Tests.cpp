#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "..\DArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

DArray<int> createDArray() {
	DArray<int> d(1);
	d.insert(1);
	return d;
}

namespace DArrayTests
{
	TEST_CLASS(DArrayCreationTest)
	{
	public:
		TEST_METHOD(ConstructorWithNParams)
		{
			DArray<int> d;
			Assert::IsTrue(d.size() == 0);
		}
		TEST_METHOD(ConstructorWithExactSize)
		{
			DArray<int> d(10);
			Assert::IsTrue(d.size() == 0);
		}
		TEST_METHOD(CopyConstructor)
		{
			DArray<int> f(2);
			f.insert(1);
			DArray<int> t(f);
			Assert::IsTrue(t[0] == 1);
		}
		TEST_METHOD(MoveConstructor)
		{
			DArray<int> t = createDArray();
			Assert::IsTrue(t[0] == 1);
		}
	};

	TEST_CLASS(DArrayInsertionTest)
	{
	public:
		TEST_METHOD(PushBack)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(1);
			Assert::IsTrue(d[1] == 1);
		}
		TEST_METHOD(InsertSizeChanging)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(1);
			Assert::IsTrue(d.size() == 2);
		}
		TEST_METHOD(InsertIntoSpecificPosition)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(1, 2);
			Assert::IsTrue(d[1] == 2);
		}
		TEST_METHOD(InsertWithResizing)
		{
			DArray<int> d(2);
			d.insert(0);
			d.insert(1);
			d.insert(2);
			Assert::IsTrue(d[2] == 2);
		}
		TEST_METHOD(CheckPushBackIndex)
		{
			DArray<int> d;
			d.insert(0);
			int test = d.insert(0);
			Assert::IsTrue(test == 1);
		}
		TEST_METHOD(CheckInsertionIndex)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(0);
			int test = d.insert(1, 0);
			Assert::IsTrue(test == 1);
		}
		TEST_METHOD(InsertOutOfRange)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(0);
			int test = d.insert(5, 0);
			Assert::IsTrue(test == -1);
		}
	};

	TEST_CLASS(DArrayRemoveTest)
	{
	public:
		TEST_METHOD(BasicRemove)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(2);
			d.remove(1);
			Assert::IsTrue(d[1] == 2);
		}
		TEST_METHOD(RemoveLastElement)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(2);
			d.remove(2);
			Assert::IsTrue(d.size() == 2);
		}
		TEST_METHOD(RemoveFirstElement)
		{
			DArray<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(2);
			d.remove(0);
			Assert::IsTrue(d[0] == 1);
		}
	};

	TEST_CLASS(DArrayIteratorTest)
	{
	public:
		TEST_METHOD(IteratorGet)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.iterator();
			Assert::IsTrue(it.get() == 1);
		}
		TEST_METHOD(ReverseIteratorGet)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			Assert::IsTrue(it.get() == 2);
		}
		TEST_METHOD(IteratorSet)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.iterator();
			it.set(5);
			Assert::IsTrue(d[0] == 5);
		}
		TEST_METHOD(IteratorNext)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.iterator();
			it.next();
			Assert::IsTrue(it.get() == 2);
		}
		TEST_METHOD(ReverseIteratorNext)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			it.next();
			Assert::IsTrue(it.get() == 1);
		}
		TEST_METHOD(IteratorHasNext)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			it.next();
			Assert::IsFalse(it.hasNext());
		}
		TEST_METHOD(ReverseIteratorHasNext)
		{
			DArray<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			it.next();
			Assert::IsFalse(it.hasNext());
		}
	};
	TEST_CLASS(DArrayStringTest)
	{
	public:
		TEST_METHOD(StringInsert)
		{
			DArray<std::string> d;
			d.insert("Test");
			Assert::IsTrue(d[0].compare("Test") == 0);
		}
		TEST_METHOD(StringInsertWithResize)
		{
			DArray<std::string> d(2);
			d.insert("Test");
			d.insert("Test1");
			d.insert("Test2");
			Assert::IsTrue(d[2].compare("Test2") == 0);
		}
		TEST_METHOD(StringRemove)
		{
			DArray<std::string> d;
			d.insert("Test");
			d.insert("Test1");
			d.remove(0);
			Assert::IsTrue(d[0].compare("Test1") == 0);
		}
		TEST_METHOD(StringIterator)
		{
			DArray<std::string> d(4);
			d.insert("Test");
			d.insert("Test1");
			d.insert("Test2");
			auto it = d.iterator();
			it.next();
			Assert::IsTrue(it.get().compare("Test1") == 0);
		}
		TEST_METHOD(StringReverseIterator)
		{
			DArray<std::string> d(4);
			d.insert("Test");
			d.insert("Test1");
			d.insert("Test2");
			d.insert("Test3");
			auto it = d.reverseIterator();
			it.next();
			Assert::IsTrue(it.get().compare("Test2") == 0);
		}
	};
}

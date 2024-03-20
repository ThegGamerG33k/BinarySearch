#include <gtest/gtest.h>
#include <linked_list.h>

#define EXECUTE_LINKED_LIST_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS


TEST(LinkedListTests, InitiallyEmpty)
{
	ssuds::LinkedList<float> slist1;
	EXPECT_EQ(slist1.size(), 0);
}


// Tests many of the low-level operations we need for most other tests
TEST(LinkedListTests, FoundationalItems)
{
	ssuds::LinkedList<int> slist1;
	EXPECT_NO_THROW(slist1.append(10));
	EXPECT_NO_THROW(slist1.append(11));
	EXPECT_NO_THROW(slist1.append(12));
	ASSERT_EQ(slist1.size(), 3);
	EXPECT_EQ(slist1[0], 10);
	EXPECT_EQ(slist1[1], 11);
	EXPECT_EQ(slist1[2], 12);
	EXPECT_THROW(slist1[3], std::out_of_range);
	slist1.clear();
	EXPECT_EQ(slist1.size(), 0);
}

// Test to make sure grow is properly being handled
TEST(LinkedListTests, ManyAppends)
{
	const int num = 1000;
	const int base = 10;
	ssuds::LinkedList<int> s;
	for (int i = 0; i < num; i++)
		EXPECT_NO_THROW(s.append(i + base));
	EXPECT_EQ(s.size(), num);
	for (int i = 0; i < num; i++)
		EXPECT_EQ(s[i], i + base);
}

TEST(LinkedListTests, Insert)
{
	ssuds::LinkedList<int> s;
	s.insert(10, 0);
	s.insert(15, 1);
	s.insert(9, 0);
	s.insert(14, 2);
	s.insert(11, 2);
	s.insert(12, 3);
	s.insert(13, 4);
	s.insert(16, 7);
	for (unsigned int i = 0; i <= 7; i++)
		EXPECT_EQ(s[i], 9 + i);
	
	EXPECT_EQ(s.size(), 8);
}

TEST(LinkedListTests, StringStream)
{
	ssuds::LinkedList<int> s;
	std::stringstream ss;
	ss << s;
	EXPECT_EQ(ss.str(), "[]");
	s.append(5);
	ss.str("");
	ss << s;
	EXPECT_EQ(ss.str(), "[5]");
	s.append(6);
	s.append(7);
	s.append(8);
	ss.str("");
	ss << s;
	EXPECT_EQ(ss.str(), "[5, 6, 7, 8]");
}

TEST(LinkedListTests, CopyAndEqual)
{
	ssuds::LinkedList<int> s;
	s.append(5);
	s.append(6);
	s.append(7);

	ssuds::LinkedList<int> t(s);
	EXPECT_EQ(t.size(), s.size());
	for (int i = 0; i < 3; i++)
		EXPECT_EQ(s[i], t[i]);

	ssuds::LinkedList<int> u = s;
	EXPECT_EQ(u.size(), s.size());
	for (int i = 0; i < 3; i++)
		EXPECT_EQ(s[i], u[i]);

	s.append(8);
	s[0] = 12;
	EXPECT_NE(t.size(), s.size());
	EXPECT_NE(u.size(), s.size());
	EXPECT_EQ(s[0], 12);
	EXPECT_EQ(t[0], 5);

	t.append(9);
	EXPECT_EQ(t.size(), s.size());
	EXPECT_EQ(t[3], 9);
	EXPECT_EQ(s[3], 8);

	t = s;
	EXPECT_EQ(t.size(), s.size());
	for (int i = 0; i < 4; i++)
		EXPECT_EQ(t[i], s[i]);
}

TEST(LinkedListTests, Find)
{
	ssuds::LinkedList<int> a;
	ssuds::LinkedList<int>::LinkedListIterator Li_normal, Li_test;
	a.append(5);
	a.append(6);
	a.append(5);
	a.append(7);
	a.append(5);
	a.append(5);
	a.append(8);
	a.append(9);

	Li_normal = a.begin();
	Li_test = a.find(5);
	EXPECT_EQ(Li_normal, Li_test);
	++Li_normal;
	++Li_normal;
	Li_test = a.find(5, Li_test + 1);
	EXPECT_EQ(Li_normal, Li_test);
	++Li_normal;
	++Li_normal;
	Li_test = a.find(5, Li_test + 1);
	EXPECT_EQ(Li_normal, Li_test);
	++Li_normal;
	Li_test = a.find(5, Li_test + 1);
	EXPECT_EQ(Li_normal, Li_test);

	// No more to find -- make sure we note that
	Li_test = a.find(5, Li_test + 1);
	EXPECT_EQ(Li_test, a.end());

	// Value that isn't there at all
	Li_test = a.find(100);
	EXPECT_EQ(Li_test, a.end());
}


TEST(LinkedListTests, Remove)
{
	ssuds::LinkedList<int> a;
	ssuds::LinkedList<int>::LinkedListIterator it;
	a.append(5);
	a.append(6);
	a.append(5);
	a.append(7);
	a.append(5);
	a.append(5);
	a.append(8);
	a.append(9);

	EXPECT_EQ(a.size(), 8);

	// Remove the first 5 -- it should refer to the 6 now
	it = a.remove(a.begin());
	EXPECT_EQ(*it, 6);
	EXPECT_EQ(a.size(), 7);

	// Remove the first element (now a 6).  it should refer to the (old second/new first) 5
	it = a.remove(it);
	EXPECT_EQ(*it, 5);
	EXPECT_EQ(a.size(), 6);

	// List should now be [5, 7, 5, 5, 8, 9]
	it = a.begin() + 5;		// refers now to the 9
	it = a.remove(it);
	EXPECT_EQ(it, a.end());
	EXPECT_EQ(a.size(), 5);
}


TEST(LinkedListTests, RemoveAll)
{
	ssuds::LinkedList<int> a;
	a.append(5);
	a.append(6);
	a.append(5);
	a.append(7);
	a.append(5);
	a.append(5);
	a.append(8);
	a.append(9);

	EXPECT_EQ(a.size(), 8);
	EXPECT_EQ(a.remove_all(5), 4);
	EXPECT_EQ(a.size(), 4);
	EXPECT_EQ(a[0], 6);
	EXPECT_EQ(a[1], 7);
	EXPECT_EQ(a[2], 8);
	EXPECT_EQ(a[3], 9);
}


TEST(LinkedListTests, EmptyManualIteration)
{
	ssuds::LinkedList<int> slist1;
	ssuds::LinkedList<int>::LinkedListIterator it = slist1.begin();
	ssuds::LinkedList<int>::LinkedListIterator it_end = slist1.end();
	ASSERT_EQ(it, it_end);
}


TEST(LinkedListTests, ManualIteration)
{
	ssuds::LinkedList<std::string> slist2;
	slist2.append("A");
	slist2.append("B");
	slist2.append("C");
	slist2.append("D");
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist2.end();
	std::string val1, val2, val3, val4;
	ASSERT_NE(it, it_end);
	val1 = *it;
	++it;
	EXPECT_EQ(val1, "A");
	val2 = *it;
	++it;
	val3 = *it;
	++it;
	val4 = *it;
	++it;
	EXPECT_EQ(val2, "B");
	EXPECT_EQ(val3, "C");
	EXPECT_EQ(val4, "D");
	EXPECT_EQ(it, it_end);
}

TEST(LinkedListTests, ReverseIteration)
{
	ssuds::LinkedList<std::string> slist2;
	slist2.append("A");
	slist2.append("B");
	slist2.append("C");
	slist2.append("D");
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist2.rbegin();
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist2.rend();
	std::string val1, val2, val3, val4;
	ASSERT_NE(it, it_end);
	val1 = *it;
	++it;
	EXPECT_EQ(val1, "D");
	val2 = *it;
	++it;
	val3 = *it;
	++it;
	val4 = *it;
	++it;
	EXPECT_EQ(val2, "C");
	EXPECT_EQ(val3, "B");
	EXPECT_EQ(val4, "A");
	EXPECT_EQ(it, it_end);

	// Make sure r/not-r object interact right
	it = slist2.rbegin();
	it_end = slist2.rend();
	ssuds::LinkedList<std::string>::LinkedListIterator fit = slist2.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator fit_end = slist2.end();
	EXPECT_NE(it, fit_end);
	EXPECT_NE(it_end, fit);
}

TEST(LinkedListTests, PrettyIteration)
{
	ssuds::LinkedList<std::string> slist2;
	slist2.append("A");
	slist2.append("B");
	slist2.append("C");
	slist2.append("D");
	int i = 0;
	for (std::string s : slist2)
	{
		if (i == 0)
			EXPECT_EQ(s, "A");
		else if (i == 1)
			EXPECT_EQ(s, "B");
		else if (i == 2)
			EXPECT_EQ(s, "C");
		else
			EXPECT_EQ(s, "D");
		i++;
	}
}



TEST(LinkedListTests, CopyConstructor)
{
	ssuds::LinkedList<std::string> slist2;
	slist2.append("A");
	slist2.append("B");
	slist2.append("C");
	slist2.append("D");

	ssuds::LinkedList<std::string> slist_copy1 = slist2;
	ssuds::LinkedList<std::string> slist_copy2(slist2);
	ASSERT_EQ(slist_copy1.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	slist2.remove(slist2.begin());
	EXPECT_EQ(slist_copy1.size(), 4);

	// Same thing, really, but just to make sure...
	ASSERT_EQ(slist_copy2.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	EXPECT_EQ(slist_copy2.size(), 4);
}


TEST(LinkedListTests, Assignment)
{
	ssuds::LinkedList<std::string> slist2;
	slist2.append("A");
	slist2.append("B");
	slist2.append("C");
	slist2.append("D");

	ssuds::LinkedList<std::string> slist3;
	slist3.append("X");
	ASSERT_EQ(slist3.size(), 1);
	ASSERT_EQ(slist3[0], "X");
	slist3 = slist2;
	ASSERT_EQ(slist3.size(), 4);
	EXPECT_EQ(slist3[0], "A");
	EXPECT_EQ(slist3[1], "B");
	EXPECT_EQ(slist3[2], "C");
	EXPECT_EQ(slist3[3], "D");
	slist2.remove(slist2.begin());
	EXPECT_EQ(slist3.size(), 4);
}


TEST(LinkedListTests, InitializerListConstructor)
{
	ssuds::LinkedList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(test.size(), 8);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 9);
	EXPECT_EQ(test[3], 3);
	EXPECT_EQ(test[4], 1);
	EXPECT_EQ(test[5], 2);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 0);
}


ssuds::LinkedList<float> move_func()
{
	ssuds::LinkedList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	return result;
}

TEST(LinkedListTests, MoveConstructor)
{
	ssuds::LinkedList<float> my_arr = move_func();
	ASSERT_EQ(my_arr.size(), 2);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 4.2f);
	my_arr.remove(my_arr.begin());
	EXPECT_EQ(my_arr.size(), 1);
}


TEST(LinkedListTests, SimpleIterator)
{
	ssuds::LinkedList<int> a;
	ssuds::LinkedList<int>::LinkedListIterator it = a.begin();
	EXPECT_EQ(it, a.end());
	a.append(14);
	it = a.begin();
	++it;
	EXPECT_EQ(it, a.end());
}

#endif
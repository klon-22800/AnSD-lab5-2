#include <gtest/gtest.h>
#include <hash_table/hash_table.h>

using namespace std;
using namespace hash_table;

TEST(Functions_test, constuct) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.print();
	a.get_stat();
	EXPECT_EQ(a.get_size(), 4);
}

TEST(Functions_test, operator_assigment) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.print();
	HashTable<int, int> b = a;
	b.print();
	EXPECT_EQ(a.get_size(), b.get_size());
}

TEST(Functions_test, remake) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.print();
	a.get_stat();
	a.remake(3);
	a.print();
	a.get_stat();
}

TEST(Functions_test, insert_or_assign) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.insert_or_assign(3, 5);
	int res = *a.search(3);
	EXPECT_EQ(res, 5);
}

TEST(Functions_test, contains) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.insert_or_assign(3, 5);
	bool res = a.contains(5);
	EXPECT_EQ(true, res);
}

TEST(Functions_test, search) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.insert_or_assign(3, 5);
	int res = *a.search(3);
	EXPECT_EQ(res, 5);
}

TEST(Functions_test, erase_true) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.insert_or_assign(3, 5);
	bool res = a.erase(3);
	EXPECT_EQ(res, true);
}

TEST(Functions_test, erase_false) {
	HashTable<int, int>a(2);
	a.insert(1, 1);
	a.insert(2, 1);
	a.insert(3, 1);
	a.insert_or_assign(3, 5);
	bool res = a.erase(4);
	EXPECT_EQ(res, false);
}

TEST(Functions_test, count) {
	HashTable<int, int>a(10);
	for (int i = 0; i < 800; i++) {
		a.insert(i, i);
	}
	int res = a.count(21);
	EXPECT_EQ(res, 2);
}

TEST(Functions_test, pearson_hash_compare_true) {
	int a = Pearson_hash("hello");
	bool res = hash_compare("hello", a);
	EXPECT_EQ(true, res);
}

TEST(Functions_test, pearson_hash_compare_false) {
	int a = Pearson_hash("hello");
	bool res = hash_compare("bye", a);
	EXPECT_EQ(false, res);
}
#include <gtest/gtest.h>
#include <hash_table/hash_table.h>

using namespace std;
using namespace hash_table;

TEST(Functions_test, sum_test) {
    HashTable<int,int> a(10);
    a.insert(1, 1);
    a.insert(2, 1);
    a.insert(3, 1);
    a.insert(4, 1);
    a.insert(5, 1);
    a.insert(6, 1);
    a.insert(7, 1);
    a.insert(8, 1);
    a.insert(9, 1);
    a.insert(10, 1);
    a.insert(11, 1);
    a.insert(12, 1);
    a.insert(13, 1);
    a.erase(2);
    a.remake();
    a.print();

    int b = Pearson_hash("Hello");
    cout << hash_compare("Hello", b);
    
}
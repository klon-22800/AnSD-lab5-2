#include<iostream>
#include<hash_table/hash_table.h>

using namespace std;
using namespace hash_table;

int h(int key) {
	int hash = key;

	// ��������� ��������� ��������� �� ���� � ������� XOR
	hash = (hash ^ 61) ^ (hash >> 16);

	// ����� ����� �����
	hash *= 9;
	hash ^= hash >> 4;

	// ��������� �� ������� �����
	hash *= 0x27d4eb2d;

	// ������������� ������������ ���-���� � ������� �������������� �������� XOR � ������
	hash ^= hash >> 15;

	// ������ ������� �� ������� �� ������ ���-�������
	return hash % 10;
}

int main(){
    int a = 5;
    int b = 5;
    cout << h(1);
	cout << h(2);
	cout << h(3);
	cout << h(4);
	cout << h(5);
	cout << h(6);
	cout << h(7);
	cout << h(8);
	cout << h(9);
	cout << h(10);
}
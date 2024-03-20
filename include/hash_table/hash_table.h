#pragma once
#include<iostream>
#include<vector>
#include<exception>
#include <random>
#include<cmath>
#include<string>

using namespace std; 

namespace hash_table {
	int random(int a, int b) {
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(a, b);
		return distribution(generator);
	}

	template<typename K, typename T>
	class HashTable {
	private:
		template<typename K, typename T>
		class Node {
		public:
			K _key;
			T _val;
			Node* _next;
			bool _is_empty;

			Node() {
				_is_empty = true;
				_key = {};
				_val = {};
				_next = nullptr;
			}

			Node(K key, T val) {
				_is_empty = false;
				_key = key;
				_val = val;
				_next = nullptr;
			}

			~Node() = default;

			void print() {
				cout << "Key: " << _key<<" ";
				cout << "Val: " << _val << " ";
			}
		};

		vector<Node<K, T>> _table;
		size_t _count;
		size_t _size;

		size_t h(K key) {
			int hash = key;
			hash = (hash ^ 61) ^ (hash >> 16);
			hash *= 9;
			hash ^= hash >> 4;
			hash *= 0x27d4eb2d;
			hash ^= hash >> 15;
			return hash % _size;
		}
	public:
		HashTable() {
			_count = 0;
			_size = 0;
			_table.resize(0);
		}

		HashTable(size_t size) {
			_count = 0;
			_size = size;
			_table.resize(size);
		}

		HashTable(const HashTable& other) {
			_count = 0;
			_size = other._size;
			_table.resize(_size);
			size_t n = other._table.size();
			for (int i = 0; i < n; i++) {
				if (!other._table[i]._is_empty) {
					insert(other._table[i]._key, other._table[i]._val);
					auto ptr = other._table[i]._next;
					while (ptr) {
						insert(ptr->_key, ptr->_val);
						ptr = ptr->_next;
					}
				}
			}

		}
		
		void clear() {
			size_t n = _table.size();
			for (int i = 0; i < n; i++) {
				if (!_table[i]._is_empty) {
					auto ptr = _table[i]._next;
					while (ptr) {
						auto tmp = ptr;
						ptr = ptr->_next;
						delete tmp;
					}
				}
			}
			_table.erase(_table.begin(), _table.end());
		}
		~HashTable() {
			clear();
		}

		bool insert(K key, T val) {
			if (search(key))
				return false;
			size_t index = h(key);
			if (_table[index]._is_empty) {
				_table[index] = Node(key, val);
				_count++;
				return true;
			}
			else {
				Node<K, T>* ptr = &_table[index];
				while (ptr->_next) {
					ptr = ptr->_next;
				}
				ptr->_next = new Node(key, val);
				_count++;
				return true;
			}
		}

		void insert_or_assign(K key, T val) {
			if (search(key)) {
				erase(key);
				insert(key, val);
				_count++;
			}
			else {
				insert(key, val);
				_count++;
			}
		}

		bool erase(K key) {
			if (search(key)) {
				size_t index = h(key);
				if (_table[index]._key == key) {
					if (_table[index]._next) {
						_table[index] = *_table[index]._next;
						_count--;
						return true;
					}
					else {
						_table[index]._key = {};
						_table[index]._val = {};
						_table[index]._is_empty = true;
						_count--;
						return true;
					}
				}
				else {
					Node<K, T>* ptr = &_table[index];
					while (ptr->_next) {
						if (ptr->_next->_key == key) {
							ptr->_next = ptr->_next->_next;
							_count--;
							return true;
						}
						ptr = ptr->_next;
					}
					return false;
				}
			}
		}

		T* search(K key) {
			size_t index = h(key);
			if (_table[index]._is_empty) {
				return nullptr;
			}
			else {
				Node<K, T>* ptr = &_table[index];
				while (ptr) {
					if (ptr->_key == key) {
						return &ptr->_val;
					}
					ptr = ptr->_next;
				}
				return nullptr;
			}
		}
		void print() {
			size_t n = _table.size();
			for (int i = 0; i < n; i++) {
				if (!_table[i]._is_empty) {
					_table[i].print();
					auto ptr = _table[i]._next;
					while (ptr) {
						ptr->print();
						ptr = ptr->_next;
					}
					cout << endl;
				}
			}
		}

		void remake() {
			HashTable<K, T> tmp(*this);
			clear();
			_table.resize(2 * _size);
			_size = 2 * _size;
			_count = 0;
			size_t n = tmp._table.size();
			for (int i = 0; i < n; i++) {
				if (!tmp._table[i]._is_empty) {
					insert(tmp._table[i]._key, tmp._table[i]._val);
					auto ptr = tmp._table[i]._next;
					while (ptr) {
						insert(ptr->_key, ptr->_val);
						ptr = ptr->_next;
					}
				}
			}
		}
	};

	unsigned char Pearson_hash(string str) {
		static const unsigned char T[256] = {
			 98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
			 61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
			 90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
			237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
			123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
			 59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
			197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
			 39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
			154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
			133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
			189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
			183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, 
			221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, 
			  3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, 
			238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, 
			 43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239  
		};
		unsigned char hash = 0;
		for (char c : str) {
			hash = T[hash ^ static_cast<unsigned char>(c)];
		}
		return hash;
	}
	bool hash_compare(string str, int hash) {
		int str_hash = Pearson_hash(str);
		if (str_hash == hash) {
			return true;
		}
		return false;
	}
}
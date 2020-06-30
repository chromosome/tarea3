#ifndef TEST_HPP
#define TEST_HPP

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <ctime>

#include "hash.hpp"
#include "utils.hpp"
#include "binary_tree.hpp"
#include "open_addressing.hpp"
#include "separate_chaining.hpp"

using namespace std;
template <typename K, typename V>
using sc_table = separate_chaining_hash_table<K, V>;
template <typename K, typename V>
using oa_table = open_addressing_hash_table<K, V>;

namespace test {

void init () {
	srand(time(nullptr));
}

static char alphabet[] = {
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"_"
	};

template<typename T>
T random ();

template<>
name_type random () {
	int len = rand()%15 + 5;
	string s(len, ' ');

	for (int i = 0; i < len; ++i) {
		s[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
	}

	return s;
}

template<>
id_type random () {
	return rand()%numeric_limits<unsigned long long>::max();
}

template <template <typename, typename> typename T>
void query_by_id (vector<vector<string>> data) {
	T<id_type, id_tuple> cont = 
		make_container<T, id_type, id_tuple>(data);

	auto ids = [&data] {
		vector<id_type> ids;
		for (const auto& reg: data)
			ids.push_back((id_type) stold(reg[1]));
		return ids;
	}();

	int count = 1'000'000;
	for (int i = 1000; i <= count; i+=1000) {
		cout << i << ": ";
		profile( [&cont, &ids, &i] {
				for (int j = 0, k = 0; j < i; ++j, ++k) {
					if (k >= ids.size())
						k = 0;
					cont.find(ids[k]);
				}
			}
		);
	}
}

template <template <typename, typename> typename T>
void query_by_name (vector<vector<string>> data) {
	T<name_type, name_tuple> cont = 
		make_container<T, name_type, name_tuple>(data);

	auto names = [&data] {
		vector<name_type> names;
		for (const auto& reg: data)
			names.push_back(reg[2]);
		return names;
	}();

	int count = 1'000'000;
	for (int i = 1000; i <= count; i+=1000) {
		cout << i << ": ";
		profile( [&cont, &names, &i] {
				for (int j = 0, k = 0; j < i; ++j, ++k) {
					if (k >= names.size())
						k = 0;
					cont.find(names[k]);
				}
			}
		);
	}
}

template <template <typename, typename> typename T>
void query_by_id_not_in (vector<vector<string>> data) {
	T<id_type, id_tuple> cont = 
		make_container<T, id_type, id_tuple>(data);

	int size = 1'000'000;
	auto ids = [&cont, &size] {
		vector<id_type> ids;
		for (int i = 0; i < size; ++i) {
			id_type id = random<id_type>();
			while (cont.find(id) != cont.not_found())
				id = random<id_type>();
			ids.push_back(id);
		}
		return ids;
	}();

	for (int i = 1000; i <= size; i+=1000) {
		cout << i << ": ";
		profile( [&cont, &ids, &i] {
				for (int j = 0; j < i; ++j)
					cont.find(ids[j]);
			}
		);
	}
}

template <template <typename, typename> typename T>
void query_by_name_not_in (vector<vector<string>> data) {
	T<name_type, name_tuple> cont = 
		make_container<T, name_type, name_tuple>(data);

	int size = 1'000'000;
	auto names = [&cont, &size] {
		vector<name_type> names;
		for (int i = 0; i < size; ++i) {
			string s = random<name_type>();
			while (cont.find(s) != cont.not_found())
				s = random<name_type>();
			names.push_back(s);
		}
		return names;
	}();

	for (int i = 1000; i <= size; i+=1000) {
		cout << i << ": ";
		profile( [&cont, &names, &i] {
				for (int j = 0; j < i; ++j)
					cont.find(names[j]);
			}
		);
	}
}

template <template <typename, typename> typename T>
void scalability_by_id (vector<vector<string>> data) {
	time_insertion<T, id_type, id_tuple>(data);
}

template <template <typename, typename> typename T>
void scalability_by_name (vector<vector<string>> data) {
	time_insertion<T, name_type, name_tuple>(data);
}

template <template <typename, typename> typename T>
void size_by_id (vector<vector<string>> data) {
	// T<id_type, id_tuple> cont = 
	// 	make_container<T, id_type, id_tuple>(data);

	// cout << cont.size()/(1024.*1024.) << endl;
	weigh_insertion<T, id_type, id_tuple>(data);
}

template <template <typename, typename> typename T>
void size_by_name (vector<vector<string>> data) {
	// T<name_type, name_tuple> cont = 
	// 	make_container<T, name_type, name_tuple>(data);

	// cout << cont.size()/(1024.*1024.) << endl;
	weigh_insertion<T, name_type, name_tuple>(data);
}

} // namespace test

#endif

#ifndef UTILS_HPP
#define UTILS_HPP

#include <functional>
#include <fstream>
#include <sstream>
#include <utility>
#include <chrono>
#include <string>
#include <vector>
#include <tuple>

using namespace std;
using id_type	 = unsigned long long;
using name_type	 = string;
using id_tuple	 = tuple<string,  name_type, int, int, int, string>;
using name_tuple = tuple<string,    id_type, int, int, int, string>;

vector<vector<string>> read_data(string filename) {
	vector<vector<string>> data;

	ifstream input(filename);
	string line;

	getline(input, line);
	while (getline(input, line)) {
		stringstream line_stream(line);
		string field;

		vector<string> fields;
		while (getline(line_stream, field, ','))
			fields.push_back(field);

		data.push_back(fields);
	}

	return data;
}

template<typename K, typename V>
pair<K, V> make_pair (vector<string>& fields);

template<>
pair<id_type, id_tuple> 
make_pair <id_type, id_tuple> (vector<string>& fields) {
	return make_pair<id_type, id_tuple>(
			(id_type) stold(fields[1]),
			{
					  fields[0],
					  fields[2],
				stoi (fields[3]),
				stoi (fields[4]),
				stoi (fields[5]),
					  fields[6]
			}
		);
}

template<>
pair<name_type, name_tuple> 
make_pair <name_type, name_tuple> (vector<string>& fields) {
	return make_pair<name_type, name_tuple>(
			move(fields[2]),
			{
								 fields[0] ,
				(id_type) stold (fields[1]),
						  stoi  (fields[3]),
						  stoi  (fields[4]),
						  stoi  (fields[5]),
								 fields[6]
			}
		);
}

template<template<typename, typename> typename T, typename K, typename V>
void time_insertion (vector<vector<string>> data) {
	T<K, V> cont;

	int insertions = 0;

	auto start = chrono::steady_clock::now();
	auto end   = chrono::steady_clock::now();
	for (auto& reg: data) {
		cont.insert(make_pair<K, V>(reg));
	
		insertions++;
		switch (insertions) {
			case 1000:
				end = chrono::steady_clock::now();
				cout << chrono::
						duration_cast<chrono::nanoseconds>(end-start)
						.count()/1e6
					 // << " ms"
					 << endl;
				break;
			case 5000:
				end = chrono::steady_clock::now();
				cout << chrono::
						duration_cast<chrono::nanoseconds>(end-start)
						.count()/1e6
					 // << " ms"
					 << endl;
				break;
			case 10000:
				end = chrono::steady_clock::now();
				cout << chrono::
						duration_cast<chrono::nanoseconds>(end-start)
						.count()/1e6
					 // << " ms"
					 << endl;
				break;
			case 15000:
				end = chrono::steady_clock::now();
				cout << chrono::
						duration_cast<chrono::nanoseconds>(end-start)
						.count()/1e6
					 // << " ms"
					 << endl;
				break;
			case 20000:
				end = chrono::steady_clock::now();
				cout << chrono::
						duration_cast<chrono::nanoseconds>(end-start)
						.count()/1e6
					 // << " ms"
					 << endl;
				break;
			default:
				break;
		}
	}
}

template<template<typename, typename> typename T, typename K, typename V>
void weigh_insertion (vector<vector<string>> data) {
	T<K, V> cont;

	int insertions = 0;
	for (auto& reg: data) {
		cont.insert(make_pair<K, V>(reg));
	
		insertions++;
		switch (insertions) {
			case 1000:
				cout << 1000 << ": " << cont.size()/(1024.*1024.) << endl;
				break;
			case 5000:
				cout << 5000 << ": " << cont.size()/(1024.*1024.) << endl;
				break;
			case 10000:
				cout << 10000 << ": " << cont.size()/(1024.*1024.) << endl;
				break;
			case 15000:
				cout << 15000 << ": " << cont.size()/(1024.*1024.) << endl;
				break;
			case 20000:
				cout << 20000 << ": " << cont.size()/(1024.*1024.) << endl;
				break;
			default:
				break;
		}
	}
}

template<template<typename, typename> typename T, typename K, typename V>
T<K, V> make_container (string filename) {
	T<K, V> cont;

	ifstream input(filename);
	string line;

	getline(input, line);

	int inserted_count = 0;
	int not_inserted_count = 0;
	while(getline(input, line)) {
		stringstream line_stream(line);
		string field;

		vector<string> fields;
		while (getline(line_stream, field, ','))
			fields.push_back(field);

		bool inserted = cont.insert(
			make_pair<K, V>(fields)
		);
		if (inserted)
			inserted_count++;
		else
			not_inserted_count++;
	}

	cout << "inserted count: " << inserted_count << endl;
	cout << "not inserted count: " << not_inserted_count << endl;

	return cont;
}

template<template<typename, typename> typename T, typename K, typename V>
T<K, V> make_container (vector<vector<string>> data) {
	T<K, V> cont;

	int inserted_count = 0;
	int not_inserted_count = 0;

	for (auto& reg: data)
		cont.insert(make_pair<K, V>(reg));

	return cont;
}

void profile (function<void(void)> f) {
	auto start = chrono::steady_clock::now();
	f();
	auto end = chrono::steady_clock::now();

	cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()/1e6
		 // << " ms"
		 << endl;
}

template<typename T, unsigned N, unsigned Last>
struct tuple_printer {
	static void print (ostream& out, const T& value) {
		out << get<N>(value) << ", ";
		tuple_printer<T, N+1, Last>::print(out, value);
	}
};

template<typename T, unsigned N>
struct tuple_printer <T, N, N> {
	static void print (ostream& out, const T& value) {
		out << get<N>(value);
	}
};

template<typename... Args>
ostream& operator << (ostream& out, const tuple<Args...>& value) {
	out << "(";
	tuple_printer<tuple<Args...>, 0, sizeof...(Args)-1>::print(out, value);
	out << ")";
	return out;
}

#endif

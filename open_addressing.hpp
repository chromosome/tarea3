#ifndef OPEN_ADDRESSING_HPP
#define OPEN_ADDRESSING_HPP

#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include "hash.hpp"

using namespace std;

template <typename K, typename V>
class open_addressing_hash_table
{
	vector<pair<K, V>> buckets;
	size_t bucket_count;
	size_t items_count = 0;
	double load_factor = 0.0;
	const V ITEM_NOT_FOUND;

	void resize () {
		bucket_count *= 2;
		bucket_count = hash_table::next_prime(bucket_count);

		rehash();
	}

	void rehash () {
		auto buckets_copy(buckets);
		buckets.clear();
		buckets.resize(bucket_count);

		items_count = 0;
		for (const auto& p: buckets_copy)
			if (p.second != ITEM_NOT_FOUND)
				insert(p);
	}

public:
	open_addressing_hash_table() 
	: buckets(vector<pair<K, V>>(10))
	, bucket_count(buckets.size())
	, ITEM_NOT_FOUND(V())
	{}

	bool insert (pair<K, V> p) {
		K key = p.first;
		size_t size = bucket_count;
		auto h = hash_table::hash(key, size);

		auto h_i = h;
		for (int i = 0; 
			buckets[h_i].second != ITEM_NOT_FOUND; 
			++i, h_i = hash_table::hash(h+i, size)) {

			if (key == buckets[h_i].first)
				return false;
		}

		buckets[h_i] = p;

		items_count++;
		load_factor = (double)items_count/(double)bucket_count;
		if (load_factor >= 0.5)
			resize();

		return true;
	}

	const V& find (K key) {
		size_t size = bucket_count;
		auto h = hash_table::hash(key, size);

		auto h_i = h;
		for (int i = 0; 
			buckets[h_i].second != ITEM_NOT_FOUND; 
			++i, h_i = hash_table::hash(h+i, size)) {

			if (key == buckets[h_i].first)
				return buckets[h].second;
		}

		return ITEM_NOT_FOUND;
	}

	void print () {
		for (const auto& p: buckets) {
			print_pair(p);
			cout << endl;
		}
	}

	void print_pair (const pair<K, V>& p) {
		cout << "{ "<< p.first << ": " << p.second << " }";
	}

	const size_t& capacity () { return bucket_count; }
	const V& not_found() { return ITEM_NOT_FOUND; }

	size_t size () { 
		cout << buckets.size()*(sizeof(pair<K, V>))/(1024.*1024.) << ", ";
		size_t s = 0;
		for (const auto& p: buckets)
			if (p.second != ITEM_NOT_FOUND)
				s += sizeof(p);
		// cout << s/(1024.*1024.) << " MB" << endl;
		// cout << sizeof(buckets[0]) << endl; 
		return s;
	}
};

#endif

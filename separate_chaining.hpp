#ifndef SEPARATE_CHAINING_HPP
#define SEPARATE_CHAINING_HPP

#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include "hash.hpp"

using namespace std;

template <typename K, typename V>
class separate_chaining_hash_table
{
	vector<list<pair<K, V>>> buckets;
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
		for (const auto& bucket: buckets_copy) {
			for (const auto& p: bucket) {
				insert(p);
			}
		}
	}

public:
	separate_chaining_hash_table() 
	: buckets(vector<list<pair<K, V>>>(11))
	, bucket_count(buckets.size())
	, ITEM_NOT_FOUND(V())
	{}

	bool insert (pair<K, V> p) {
		K key = p.first;
		size_t size = bucket_count;
		auto h = hash_table::hash(key, size);

		// Busca en la lista correspondiente a la hash
		auto& bucket = buckets[h];
		auto it = find_if(bucket.begin(), bucket.end(),
			[&key] (const pair<K, V>& e) { return e.first == key; });

		if (it == bucket.end()) {
			bucket.insert(bucket.begin(), p);
			items_count++;
			load_factor = (double)items_count/(double)bucket_count;
			if (load_factor >= 0.9)
				resize();
		}
		else
			return false;

		return true;
	}

	const V& find (K key) {
		size_t size = bucket_count;
		auto h = hash_table::hash(key, size);

		// Busca en la lista correspondiente a la hash
		auto& bucket = buckets[h];
		auto it = find_if(bucket.begin(), bucket.end(),
			[&key] (const pair<K, V>& e) { return e.first == key; });

		if (it != bucket.end())
			return it->second;
		else
			return ITEM_NOT_FOUND;
	}

	void print () {
		for (const auto& bucket: buckets) {
			for (const auto& p: bucket)
				print_pair(p);
			if (!bucket.empty())
				cout << endl;
		}
	}

	void print_pair (const pair<K, V>& p) {
		cout << "{ "<< p.first << ": " << p.second << " } ";
	}

	size_t size () {
		size_t s = 0;
		for (const auto& bucket: buckets) {
			if (bucket.size() > 0) {
				for (const auto& p: bucket)
					s += sizeof(p);
			}
			s += sizeof(bucket);
		}
		s += sizeof(buckets);
		return s;
	}

	const size_t& capacity() { return bucket_count; }
	const V& not_found() { return ITEM_NOT_FOUND; }
};

#endif

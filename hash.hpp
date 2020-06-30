#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

namespace hash_table {

static char alphabet_lookup[128] = 
{
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
	 0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,  0,  0,  0,  0, 36,
	 0, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,  0,  0,  0,  0,  0 
};

static int primes_lookup[] = 
{
	11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437
};

// primes = vector<int> { 
// 	 2,  3,  5,  7, 11,
// 	13, 17, 19, 23, 29,
// 	31, 37, 41, 43, 47,
// 	53, 59, 61, 67, 71,
// 	73, 79, 83, 89, 97 
// };

// bool is_prime (int x) {
// 	for (const auto& p: primes)
// 		if (p*p > x) {
// 			primes.push_back(x);
// 			cout << p << endl;
// 			return true;
// 		}
// 		else if (x%p == 0)
// 			return false;
// }

// void print_limits () {
// 	cout << "type\tlowest()\tmin()\t\tmax()\n\n";
	
// 		cout << "unsigned long long\t"
// 			 << +numeric_limits<unsigned long long>::lowest() << '\t' << '\t'
// 			 << +numeric_limits<unsigned long long>::min() << '\t' << '\t'
// 			 << +numeric_limits<unsigned long long>::max() << '\n';
// 		cout << "unsigned int\t"
// 			 << numeric_limits<unsigned int>::lowest() << '\t'
// 			 << numeric_limits<unsigned int>::min() << '\t'
// 			 << numeric_limits<unsigned int>::max() << '\n';
// 		cout << "float\t"
// 			 << numeric_limits<float>::lowest() << '\t'
// 			 << numeric_limits<float>::min() << '\t'
// 			 << numeric_limits<float>::max() << '\n';
// 		cout << "double\t"
// 			 << numeric_limits<double>::lowest() << '\t'
// 			 << numeric_limits<double>::min() << '\t'
// 			 << numeric_limits<double>::max() << '\n';
// }

const double phi_minus_one = 0.618033988749894848204L;

bool is_prime (int x) {
	if (x < 2) 
		return false;
	if (x == 2) 
		return true;
	if (x % 2 == 0) 
		return false;
	for (int i=3; (i*i) <= x; i+=2)
		if (x % i == 0 ) 
			return false;
	return true;
}

int next_prime (int x) {
	while (!is_prime(++x));
	return x;
}

template <typename K>
unsigned long long fibonacci_hashing (K x, size_t M) {
	// auto W = numeric_limits<unsigned int>::max();
	// auto W = 100;
	long double A = phi_minus_one;
	// cout << A*x << endl;
	// long double tmp;
	// cout << modf(A*x, &tmp) << endl;
	// auto h = A*x - floor(A*x);
	// cout << h << endl;
	return floor(M*(A*x - floor(A*x)));
}

template <typename K>
unsigned long long hash (K key, size_t table_size) {
	unsigned long long digest = key % table_size;
	// unsigned long long digest = fibonacci_hashing(key, table_size);

	return digest;
}

unsigned long long encode (string s) {
	string sample = s.substr(0, 10);

	unsigned long long encoded = 0;
	for (const auto& c: sample)
		encoded = alphabet_lookup[c] + 63*encoded;

	return encoded;
}

template <>
unsigned long long hash <string> (string key, size_t table_size) {
	unsigned long long digest = 0;

	digest = encode(key);
	digest = hash(digest, table_size);

	return digest;
}

} // hash_table
#endif

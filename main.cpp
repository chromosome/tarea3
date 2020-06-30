#include <iostream>

#include "test.hpp"

template <typename K, typename V>
using sc_table = separate_chaining_hash_table<K, V>;
template <typename K, typename V>
using oa_table = open_addressing_hash_table<K, V>;

int main(int argc, char const *argv[])
{
	// TREE -------------------------------------------------------------------
	// auto btree = make_id_tree("universities_followers.csv");
	// auto btree = make_name_tree("universities_followers.csv");

	// std::cout << std::get<5>(std::get<1>(btree.search("yesareli_reyes")->data))
	// 		  << std::endl;


	// binary_tree<int, int> btree;
	// btree.insert(std::pair<int, int>(1, 1));

	// binary_tree<id_type, id_tuple> btree;
	// auto t = id_tuple("pucv_cl", "Sawwy_", 148, 210, 14, "Thu Apr 21 21:14:04 +0000 2011");
	// auto p = std::pair<id_type, id_tuple>(285824050, t);
	// btree.insert(p);
	// auto t2 = id_tuple("asdf", "Sawwy_", 148, 210, 14, "Thu Apr 21 21:14:04 +0000 2011");
	// auto p2 = std::pair<id_type, id_tuple>(285824050, t);
	// btree.insert(p);

	// std::cout << btree.size() << std::endl;
	// btree.print_tree();

	// SEPARATE CHAINNING -----------------------------------------------------
	// separate_chaining_hash_table <int, int> htable;
	// htable.insert(std::pair<int, int>( 0, 9));
	// htable.insert(std::pair<int, int>( 1, 8));
	// htable.insert(std::pair<int, int>( 2, 7));
	// htable.insert(std::pair<int, int>( 3, 6));
	// htable.insert(std::pair<int, int>( 4, 5));
	// htable.insert(std::pair<int, int>( 5, 4));
	// htable.insert(std::pair<int, int>( 6, 3));
	// htable.insert(std::pair<int, int>( 7, 2));
	// htable.insert(std::pair<int, int>( 8, 1));
	// htable.insert(std::pair<int, int>( 9, 0));
	// htable.insert(std::pair<int, int>(10, 9));

	// htable.print_table();
	// cout << htable.find(11) << endl;

	// std::cout << "val: " << htable.find(10) << endl;

	// if (htable.find(10))
	// 	std::cout << "si" << std::endl;
	// else
	// 	std::cout << "no" << std::endl;

	// separate_chaining_hash_table <id_type, id_tuple> htable = 
	// 	make_id_container<separate_chaining_hash_table <id_type, id_tuple>>("universities_followers.csv");
	// auto htable = 
	// 	make_name_container<sc_table<name_type, name_tuple>>(
	// 		"universities_followers.csv"
	// 	);
	// htable.print_table();

	// hash_table::print_limits();
	// hash_table::print_phi();
	// hash_table::fibonacci_hashing(100, 100);

	// OPEN ADDRESSING --------------------------------------------------------
	// oa_table<int, int> htable;
	// htable.insert(std::pair<int, int>(  0, 9));
	// htable.insert(std::pair<int, int>(  1, 8));
	// htable.insert(std::pair<int, int>(  2, 7));
	// htable.insert(std::pair<int, int>(  3, 6));
	// htable.insert(std::pair<int, int>( 13, 6));
	// htable.insert(std::pair<int, int>( 23, 6));
	// htable.insert(std::pair<int, int>( 33, 6));
	// htable.insert(std::pair<int, int>(332, 6));
	// htable.insert(std::pair<int, int>(113, 6));
	// htable.insert(std::pair<int, int>(  4, 5));
	// htable.insert(std::pair<int, int>(  5, 4));
	// htable.insert(std::pair<int, int>(  6, 3));
	// htable.insert(std::pair<int, int>(  7, 2));
	// htable.insert(std::pair<int, int>(  8, 1));
	// htable.insert(std::pair<int, int>(  9, 0));
	// htable.insert(std::pair<int, int>( 10, 9));

	// auto htable = make_name_container<oa_table<name_type, name_tuple>>(
	// 	"universities_followers.csv"
	// );
	// htable.print_table();
	// cout << htable.find("Zaharaisis") << endl;

	// htable.sizes();

	// auto f = [] () {
	// 	// auto htable = make_name_container<oa_table<name_type, name_tuple>>(
	// 	// 	"universities_followers.csv"
	// 	// );
	// 	auto htable = 
	// 	make_container<oa_table, name_type, name_tuple>(
	// 		"universities_followers.csv"
	// 	);
	// };
	// profile(f);

	// time_insertion<oa_table, name_type, name_tuple>(
	// 	"universities_followers.csv"
	// 	);
	// time_insertion<sc_table, name_type, name_tuple>(
	// 	"universities_followers.csv"
	// 	);

	test::init();

	// auto data = read_data("universities_followers.csv");
	// // vector<string> names

	// for (int i = 0; i < 100; ++i) {
	// 	string s = test::random<name_type>();
	// 	// auto s = test::random<id_type>();
	// 	cout << s << endl;
	// }
	auto data = read_data("universities_followers.csv");
	// auto cont = make_container<oa_table, name_type, name_tuple>(data);

	// test::query_by_id<binary_tree>(data);
	// test::scalability_by_id<binary_tree>(data);
	test::size_by_name<binary_tree>(data);
	test::size_by_name<sc_table>(data);
	test::size_by_name<oa_table>(data);

	return 0;
}

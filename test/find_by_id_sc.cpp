#include "../test.hpp"

int main(int argc, char const *argv[])
{
	auto data = read_data("universities_followers.csv");
	test::query_by_id<sc_table>(data);

	return 0;
}

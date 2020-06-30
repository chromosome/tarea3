#include "../test.hpp"

int main(int argc, char const *argv[])
{
	auto data = read_data("universities_followers.csv");
	test::scalability_by_id<oa_table>(data);

	return 0;
}

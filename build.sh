
build() {
	g++ test/find_by_id_bt.cpp -o build/find_by_id_bt
	g++ test/find_by_id_oa.cpp -o build/find_by_id_oa
	g++ test/find_by_id_sc.cpp -o build/find_by_id_sc
	g++ test/find_by_id_not_in_bt.cpp -o build/find_by_id_not_in_bt
	g++ test/find_by_id_not_in_oa.cpp -o build/find_by_id_not_in_oa
	g++ test/find_by_id_not_in_sc.cpp -o build/find_by_id_not_in_sc
	g++ test/scalability_by_id_bt.cpp -o build/scalability_by_id_bt
	g++ test/scalability_by_id_oa.cpp -o build/scalability_by_id_oa
	g++ test/scalability_by_id_sc.cpp -o build/scalability_by_id_sc
	g++ test/find_by_name_bt.cpp -o build/find_by_name_bt
	g++ test/find_by_name_oa.cpp -o build/find_by_name_oa
	g++ test/find_by_name_sc.cpp -o build/find_by_name_sc
	g++ test/find_by_name_not_in_bt.cpp -o build/find_by_name_not_in_bt
	g++ test/find_by_name_not_in_oa.cpp -o build/find_by_name_not_in_oa
	g++ test/find_by_name_not_in_sc.cpp -o build/find_by_name_not_in_sc
	g++ test/scalability_by_name_bt.cpp -o build/scalability_by_name_bt
	g++ test/scalability_by_name_oa.cpp -o build/scalability_by_name_oa
	g++ test/scalability_by_name_sc.cpp -o build/scalability_by_name_sc
	g++ test/size_bt.cpp -o build/size_bt
	g++ test/size_oa.cpp -o build/size_oa
	g++ test/size_sc.cpp -o build/size_sc
}

run_tests() {
	./build/find_by_id_bt > results/find_by_id_bt.txt
	./build/find_by_id_oa > results/find_by_id_oa.txt
	./build/find_by_id_sc > results/find_by_id_sc.txt
	./build/find_by_id_not_in_bt > results/find_by_id_not_in_bt.txt
	./build/find_by_id_not_in_oa > results/find_by_id_not_in_oa.txt
	./build/find_by_id_not_in_sc > results/find_by_id_not_in_sc.txt
	./build/scalability_by_id_bt > results/scalability_by_id_bt.txt
	./build/scalability_by_id_oa > results/scalability_by_id_oa.txt
	./build/scalability_by_id_sc > results/scalability_by_id_sc.txt
	./build/find_by_name_bt > results/find_by_name_bt.txt
	./build/find_by_name_oa > results/find_by_name_oa.txt
	./build/find_by_name_sc > results/find_by_name_sc.txt
	./build/find_by_name_not_in_bt > results/find_by_name_not_in_bt.txt
	./build/find_by_name_not_in_oa > results/find_by_name_not_in_oa.txt
	./build/find_by_name_not_in_sc > results/find_by_name_not_in_sc.txt
	./build/scalability_by_name_bt > results/scalability_by_name_bt.txt
	./build/scalability_by_name_oa > results/scalability_by_name_oa.txt
	./build/scalability_by_name_sc > results/scalability_by_name_sc.txt
	./build/size_bt > results/size_bt.txt
	./build/size_oa > results/size_oa.txt
	./build/size_sc > results/size_sc.txt
}

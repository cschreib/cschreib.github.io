g++ -std=c++11 generate-tests.cpp -lstdc++ -o generate-tests
g++ -std=c++11 check-tests.cpp -lmpfr -lstdc++ -o check-tests

./generate-tests
./blackbox-hypot random_tests.dat random_tests_output.dat
./check-tests random_tests.dat random_tests_output.dat random_tests_output_compare.dat

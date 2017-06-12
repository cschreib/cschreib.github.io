#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

int main(int argc, char* argv[]) {
    float pow_min = -20, pow_max = -17;
    float dp = 0.05;
    // float pow_min = -10, pow_max = 10;
    // float dp = 0.5;
    std::size_t num_per_value = 100;

    std::mt19937 seed(42);
    std::normal_distribution<double> gaussian(0.0, 1.0);

    std::ofstream out("random_tests.dat");
    out.precision(12);
    out << std::scientific;

    std::size_t np = 0;
    for (float p = pow_min; p <= pow_max; p += dp) {
        for (std::size_t i = 0; i < num_per_value; ++i) {
            out << pow(10.0, p)*(1 + 0.05*gaussian(seed)) << " "
                << pow(10.0, p-5)*(1 + 0.05*gaussian(seed)) << "\n";
        }

        ++np;
    }

    std::cout << np << " values" << std::endl;

    return 0;
}

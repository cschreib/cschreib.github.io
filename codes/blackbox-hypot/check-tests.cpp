#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include "mpfr/real.hpp"

using precise_float = mpfr::real<2048>;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "usage: check-tests <input_file> <output_file> <result_file>" << std::endl;
        return 0;
    }

    // Open input file
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "could not open input file " << argv[1] << std::endl;
        return 1;
    }

    // Open black box output file
    std::ifstream bb_out(argv[2]);
    if (!bb_out.is_open()) {
        std::cerr << "could not open black box output file " << argv[2] << std::endl;
        return 1;
    }

    std::ofstream out(argv[3]);
    if (!out.is_open()) {
        std::cerr << "could not create output file " << argv[3] << std::endl;
        return 1;
    }

    // Print values with lots of digits
    out.precision(12);
    out << std::scientific;

    // Read input file line by line
    std::string line, line_out;
    while (std::getline(in, line) && std::getline(bb_out, line_out)) {
        if (line.empty()) continue;

        // Extract two values from each line
        std::stringstream ss(line);
        std::string sa, sb;
        if (!(ss >> sa) || !(ss >> sb)) {
            std::cerr << "could not read values from input file, aborting" << std::endl;
            return 1;
        }

        precise_float a = sa, b = sb;

        // Compute true distance
        // NB: hypot avoids overflows much better than sqrt(a*a + b*b)
        precise_float d = hypot(a, b);

        // Read black box's distance
        std::stringstream ss_out(line_out);
        std::string sdbb;
        if (!(ss_out >> sdbb)) {
            std::cerr << "could not read values from black box output file, aborting" << std::endl;
            std::cerr << "reading line: '" << line_out << "'" << std::endl;
            return 1;
        }

        precise_float dbb = sdbb;

        // Write relative error
        out << (sdbb-d)/d << "\n";
    }

    return 0;
}

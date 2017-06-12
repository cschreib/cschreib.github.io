#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

using simple_float = float;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "usage: black-box-distance <input_file> <output_file>" << std::endl;
        return 0;
    }

    // Open input file
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "could not open input file " << argv[1] << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream out(argv[2]);
    if (!out.is_open()) {
        std::cerr << "could not create output file " << argv[2] << std::endl;
        return 1;
    }

    // Print values with lots of digits
    out.precision(12);
    out << std::scientific;

    // Read input file line by line
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        // Extract two values from each line
        std::stringstream ss(line);
        simple_float a, b;
        if (!(ss >> a) || !(ss >> b)) {
            std::cerr << "could not read values from input file, aborting" << std::endl;
            return 1;
        }

        // Compute distance
        simple_float d = std::sqrt(a*a + b*b);

        // Write output
        out << d << "\n";
    }

    return 0;
}

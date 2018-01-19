# CFraction: C++ class for handling fractions
Just a fun project to help my daughter learning fractions at school at her 4th grade.
## Author
Trinh D.D. Nguyen
## Features
The project is coded purely in C++11, and supports the following features:
- Basic operators: addition (+, +=), subtraction (-, -=), multiplication (*, *=), division (/, /=).
- Relative operator <, <=, >, >=, !=, ==.
- Type casting to int, long, float, double and std::string.
- Input/output directly to std::istream and std::ostream.
- Conversion from string to fraction.
- Toggle auto reduction.
## Note
- **Numerator** and **Denominator** must be an integer. **Denominator** must be non-zero or the class will bail.
- To use the class, simply put this line into your code #include "fraction.hpp" and start using **CFraction**.
- Fractions can be input via **cin** in the format of "numerator/denominator", eg. 1/2, 7/24...
- By default, fraction auto reduction is on. To switch off auto reduction, set **CFraction::autoReduce = false**.
- A test drive is included in the file 'main.cpp'.
- Operator "++" and "--" are not yet implemented.
## Compile
The project has successfully compiled and tested on my macOS using XCode g++ and my Windows using TDM-GCC64. To compile, just type 'make' and hit ENTER. No additional libraries required.
## License
Under MIT license.

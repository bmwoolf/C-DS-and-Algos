// header files
#include <cassert> // assert function
#include <cstdlib> // EXIT_SUCCESS
#include <iomanip> // setw function
#include <iostream> // cout- i think it's console.log()
using namespace std;

double celcius_to_farenheit(double c) {
// precondition: C is no less than -273.15 K
// postcondition: returns value C coverted to F

    const double MINIMUM_CELSIUS = -273.15; // absolute 0
    
    assert(c >= MINIMUM_CELSIUS);
    return (9.0 / 5.0) * c + 32;
}

void setup_cout_fractions(int fraction_digits) {
// precondition: fraction_digits is positive
// postcondition: all double/float numbers printed to cout will be rounded 

    assert(fraction_digits > 0); // basically like an if statement for if the input matches this criteria
    cout.precision(fraction_digits); // show this in the console
    cout.setf(ios::fixed, ios::floatfield); 
    if (fraction_digits == 0) {
        cout.unsetf(ios::showpoint);
    } else {
        cout.setf(ios::showpoint);
    }
}

int main() {
    const char HEADING1[] = "Celcius";
    const char HEADING2[] = "Farenheight";
    const char LABEL1 = 'C';
    const char LABEL2 = 'F';
    const double TABLE_BEGIN = -50.0; // double is int for decimal points (so float in C?), called TABLE_BEGIN (it is capitalized because it is a const)
    const double TABLE_END = 50.0; // double is 64 bit
    const double TABLE_STEP = 10.0; // float is 32 bit
    const int WIDTH = 9; // capitalized because it is a CONST
    const int DIGITS = 1; 

    double value1; // value from column 1
    double value2; // value from column 2

    setup_cout_fractions(DIGITS); // set out the output
    cout << "CONVERSATIONS from" << TABLE_BEGIN << "to " << TABLE_END << endl; // print table data (C -> F)
    cout << HEADING1 << " " << HEADING2 << endl; // print table headings

    for (value1 = TABLE_BEGIN; value1 <= TABLE_END; value1+=TABLE_STEP) {
        value2 = celcius_to_farenheit(value1);
        cout << setw(WIDTH) << value1 << LABEL1 << " ";
        cout << setw(WIDTH) << value2 << LABEL2 << endl;
    }
    
    return EXIT_SUCCESS; // function executes with success/no errors
}

double celcius_to_farenheit(11);
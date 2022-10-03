#include <iostream>
#include "big_integer.h"
using namespace std;


const char* get_boolean_string(bool value) {
    if (value) {
        return "True";
    }
    else {
        return "False";
    }
}

void test_big_integer() {
    BigInteger big_integer;

    // Constructor test
    cout << "[Constructor Test]" << endl;
    cout << "Original BigInteger (integer: 1234567890): " << BigInteger(1234567890) << endl;
    cout << "Original BigInteger (longlong: 123456789012345): " << BigInteger(123456789012345) << endl;
    cout << "Original BigInteger (string: 12345678901234567890): " << BigInteger(string("12345678901234567890")) << endl;
    cout << "Original BigInteger (integer: -1234567890): " << BigInteger(-1234567890) << endl;
    cout << "Original BigInteger (longlong: -123456789012345): " << BigInteger(-123456789012345) << endl;
    cout << "Original BigInteger (string: -12345678901234567890): " << BigInteger(string("-12345678901234567890")) << endl;

    // I&O test
    cout << endl << "[I/O Test]" << endl;
    cout << "Enter a value: ";
    cin >> big_integer;
    cout << "Given value: " << big_integer << endl;

    // Comparison test
    cout << endl << "[Comparison Test]" << endl;
    cout << "(12345678901234567899 > 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("12345678901234567890")) << endl;
    cout << "(12345678901234567899 < 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") < BigInteger("12345678901234567890")) << endl;
    cout << "(12345678901234567899 == 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") == BigInteger("12345678901234567890")) << endl;
    cout << "(12345678901234567890 == 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567890") == BigInteger("12345678901234567890")) << endl;
    cout << "(-12345678901234567899 > 12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("12345678901234567890")) << endl;
    cout << "(12345678901234567899 > -12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
    cout << "(-12345678901234567899 > -12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") > BigInteger("-12345678901234567890")) << endl;
    cout << "(-12345678901234567899 < -12345678901234567890) True -> " << get_boolean_string(BigInteger("-12345678901234567899") < BigInteger("-12345678901234567890")) << endl;

    // Add test
    cout << endl << "[Add Test]" << endl;
    cout << "1234567890 + 1234567899 = 2469135789 -> " << BigInteger(1234567890) + BigInteger(1234567899) << endl;

    // Subtract test
    cout << endl << "[Subtract Test]" << endl;
    cout << "1234567899 - 1234567890 = 9 -> " << BigInteger(12345676899) - BigInteger(12345676890) << endl;
    cout << "1234567890 - 1234567899 = -9 -> " << BigInteger(12345676890) - BigInteger(12345676899) << endl;

    /*
        // Multiply test (Optional)
        cout << endl << "[Multiply Test]" << endl;
        cout << "12345 * 67890 = 838102050 -> " << BigInteger(12345) * BigInteger(67890) << endl;
        cout << "-12345 * 67890 = -838102050 -> " << BigInteger(-12345) * BigInteger(67890) << endl;
        cout << "-12345 * -67890 = 838102050 -> " << BigInteger(-12345) * BigInteger(-67890) << endl;

        // Divide test (Optional)
        cout << endl << "[Divide Test]" << endl;
        cout << "67890 / 12345 = 5 -> " << BigInteger(67890) / BigInteger(12345) << endl;
        cout << "-67890 / 12345 = -5 -> " << BigInteger(-67890) / BigInteger(12345) << endl;
        cout << "-67890 / -12345 = 5 -> " << BigInteger(-67890) / BigInteger(-12345) << endl;

        // Remainder test (Optional)
        cout << endl << "[Remainder Test]" << endl;
        cout << "67890 % 12345 = 6156 -> " << BigInteger(67890) % BigInteger(12345) << endl;
        cout << "-67890 % 12345 = 6180 -> " << BigInteger(-67890) % BigInteger(12345) << endl;
        cout << "-67890 % -12345 = -6165 -> " << BigInteger(-67890) % BigInteger(-12345) << endl;
    */
}

void additional_test_big_integer() {
    // Additional Constructor test
    cout << endl << "[Additional Constructor Test]" << endl;
        // 0 is unique case
    cout << "Original BigInteger (integer: 0): " << BigInteger(0) << endl;
        // INT_MAX & INT_MIN(https://stackoverflow.com/questions/8511598/large-negative-integer-literals)
    cout << "Original BigInteger (integer: 2147483647): " << BigInteger(2147483647) << endl;
    cout << "Original BigInteger (integer: -2147483648): " << BigInteger(-2147483647 - 1) << endl;
        // LLONG_MAX & LLONG_MIN
    cout << "Original BigInteger (longlong: 9223372036854775807): " << BigInteger(9223372036854775807) << endl;
    cout << "Original BigInteger (longlong: -9223372036854775808): " << BigInteger(-9223372036854775807LL - 1) << endl;
        // Padded by 0 combined '-' is easy to make mistake
    cout << "Original BigInteger (string: -0): " << BigInteger(string("-0")) << endl;
    cout << "Original BigInteger (string: 00000000001234567890): " << BigInteger(string("00000000001234567890")) << endl;
    cout << "Original BigInteger (string: -00000000001234567890): " << BigInteger(string("-00000000001234567890")) << endl;

    // Additional Comparison test
    cout << endl << "[Additional Comparison Test]" << endl;
        // "* than or equal to"
    cout << "(12345678901234567899 >= 12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") >= BigInteger("12345678901234567890")) << endl;
    cout << "(12345678901234567899 <= 12345678901234567890) False -> " << get_boolean_string(BigInteger("12345678901234567899") <= BigInteger("12345678901234567890")) << endl;
    cout << "(-12345678901234567899 >= 12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") >= BigInteger("12345678901234567890")) << endl;
    cout << "(12345678901234567899 >= -12345678901234567890) True -> " << get_boolean_string(BigInteger("12345678901234567899") >= BigInteger("-12345678901234567890")) << endl;
    cout << "(-12345678901234567899 >= -12345678901234567890) False -> " << get_boolean_string(BigInteger("-12345678901234567899") >= BigInteger("-12345678901234567890")) << endl;
    cout << "(-12345678901234567899 <= -12345678901234567890) True -> " << get_boolean_string(BigInteger("-12345678901234567899") <= BigInteger("-12345678901234567890")) << endl;

    // Additional Add test
    cout << endl << "[Additional Add Test]" << endl;
        // Same sign
    cout << "123456789 + 999999999 = 1123456788 -> " << BigInteger(123456789) + BigInteger(999999999) << endl;
    cout << "999999999 + 123456789 = 1123456788 -> " << BigInteger(999999999) + BigInteger(123456789) << endl;
        // Opposite sign
    cout << "1234567890 + (-1234567891) = -1 -> " << BigInteger(1234567890) + BigInteger(-1234567891) << endl;
    cout << "-1234567891 + 1234567890 = -1 -> " << BigInteger(-1234567891) + BigInteger(1234567890) << endl;
        // Same absolute value & different signs
    cout << "12345678901234567890 + (-12345678901234567890) = 0 -> " << BigInteger("12345678901234567890") + BigInteger("-12345678901234567890") << endl;
    cout << "-12345678901234567890 + 12345678901234567890 = 0 -> " << BigInteger("-12345678901234567890") + BigInteger("12345678901234567890") << endl;

    // Additional Subtract test
    cout << endl << "[Additional Subtract Test]" << endl;
        // Every digit has borrow
    cout << "876543210 - 999999999 = -123456789 -> " << BigInteger(876543210) - BigInteger(999999999) << endl;
        // Positive - negative
    cout << "1234567890 - (-1234567899) = 2469135789 -> " << BigInteger(12345676890) - BigInteger(-12345676899) << endl;
        // Negative - positive
    cout << "-1234567890 - 1234567899 = -2469135789 -> " << BigInteger(-12345676890) - BigInteger(12345676899) << endl;
        // Negative - negative
    cout << "-1234567890 - (-1234567899) = 9 -> " << BigInteger(-12345676890) - BigInteger(-12345676899) << endl;
}

int main(int argc, char* argv[]) {
    // Test BigInteger class
    test_big_integer();
    additional_test_big_integer();

    return 0;
}
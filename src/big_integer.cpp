#include "big_integer.h"
#include <cstring>
#include <algorithm>

// Identifier
const std::string BigInteger::name = "BigInteger";

// Method
void BigInteger::initialize_properties() {
    this->sign = true;
    this->length = 0;
    this->capacity = 0;
    this->value_string = new char[this->initial_capacity]();
    if (this->value_string != NULL) {
        this->capacity = this->initial_capacity;
        this->length = 0;
    }
}

void BigInteger::doubling_capacity() {
    int new_capacity = this->capacity * 2;
    char* new_value_string = new char[new_capacity]();
    if (new_value_string == NULL) return;

    memcpy(new_value_string, this->value_string, this->length);
    delete[](this->value_string);

    this->capacity = new_capacity;
    this->value_string = new_value_string;
}

BigInteger::COMPARE_RESULT BigInteger::compare_absolute_value(const BigInteger& big_integer) const {
    int start_index = 0;

    int length = this->length;
    int given_length = big_integer.length;

    if (length > given_length) {
        return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
    }
    else if (length < given_length) {
        return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
    }
    else {
        for (int place_index = 0; place_index < length; place_index++) {
            if (this->value_string[place_index + start_index] > big_integer.value_string[place_index + start_index]) {
                return BigInteger::COMPARE_RESULT::COMPARE_LARGER;
            }
            else if (this->value_string[place_index + start_index] < big_integer.value_string[place_index + start_index]) {
                return BigInteger::COMPARE_RESULT::COMPARE_SMALLER;
            }
        }
    }
    return BigInteger::COMPARE_RESULT::COMPARE_EQUAL;
}

// Method (Interface)
BigInteger::BigInteger() {
    this->initialize_properties();
}

BigInteger::BigInteger(int value) {
    this->initialize_properties();

    // value가 0일 경우 자릿수를 구하기 위한 나눗셈 연산이 불가능하므로 예외 처리
    if (value == 0) {
        this->length = 1;
        this->value_string[0] = '0';
        return;
    }

    if (value < 0) {
        this->sign = false;
    }

    // 10으로 나눈 몫이 0이 될 때까지 value_length를 키워가며 value의 자릿수 계산
    int quotient = value;
    int value_length = 0;
    while (quotient != 0) {
        quotient /= 10;
        value_length++;
    }

    char* res_value_string = new char[value_length]();

    // 10으로 나눈 나머지의 절댓값에 '0'을 더하여 value를 빅 엔디언 문자열로 저장
    for (int place_index = 0; place_index < value_length; place_index++) {
        res_value_string[value_length - 1 - place_index] = abs(value % 10) + '0';
        value /= 10;
    }

    for (int place_index = 0; place_index < value_length; place_index++) {
        this->value_string[place_index] = res_value_string[place_index];
        this->length++;
        if (this->length == this->capacity) {
            this->doubling_capacity();
        }
    }

    delete[](res_value_string);
}


BigInteger::BigInteger(long long value) {
    this->initialize_properties();

    // value가 0일 경우 자릿수를 구하기 위한 나눗셈 연산이 불가능하므로 예외 처리
    if (value == 0) {
        this->length = 1;
        this->value_string[0] = '0';
        return;
    }

    if (value < 0) {
        this->sign = false;
    }

    // 10으로 나눈 몫이 0이 될 때까지 value_length를를 키워가며 value의 자릿수 계산
    long long quotient = value;
    int value_length = 0;
    while (quotient != 0) {
        quotient /= 10;
        value_length++;
    }

    char* res_value_string = new char[value_length]();

    // 10으로 나눈 나머지의 절댓값에 '0'을 더하여 value를 빅 엔디언 문자열로 저장
    for (int place_index = 0; place_index < value_length; place_index++) {
        res_value_string[value_length - 1 - place_index] = abs(value % 10) + '0';
        value /= 10;
    }

    for (int place_index = 0; place_index < value_length; place_index++) {
        this->value_string[place_index] = res_value_string[place_index];
        this->length++;
        if (this->length == this->capacity) {
            this->doubling_capacity();
        }
    }

    delete[](res_value_string);
}

BigInteger::BigInteger(std::string value) {
    this->initialize_properties();

    // '-' 부호와 무효한 '0' 문자열을 지워 유효한 문자열 획득
    if (value.front() == '+') {
        value.erase(value.begin());
    }

    if (value.front() == '-') {
        this->sign = false;
        value.erase(value.begin());
    }

    while (value.front() == '0') {
        value.erase(value.begin());
    }

    // value 값이 0일 경우 모든 문자를 지워버렸으므로 예외 처리
    if (value.length() == 0) {
        this->sign = true;
        this->length = 1;
        this->value_string[0] = '0';
        return;
    }

    // value 문자열을 인덱스를 유지하여 빅 엔디언 문자열로 저장
    for (int place_index = 0; place_index < value.length(); place_index++) {
        this->value_string[place_index] = value.at(place_index);
        this->length++;
        if (this->length == this->capacity) {
            this->doubling_capacity();
        }
    }
}

BigInteger::BigInteger(const BigInteger& big_integer) {
    this->initialize_properties();

    char* new_value_string = new char[big_integer.capacity]();
    if (new_value_string != NULL) {
        if (this->value_string != NULL) {
            delete[](this->value_string);
            this->sign = true;
            this->length = 0;
            this->capacity = 0;
        }

        this->value_string = new_value_string;
        memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
        this->sign = big_integer.sign;
        this->length = big_integer.length;
        this->capacity = big_integer.capacity;
    }
}

BigInteger::~BigInteger() {
    if (this->value_string != NULL) {
        delete[](this->value_string);
        this->sign = true;
        this->length = 0;
        this->capacity = 0;
    }
}

std::string BigInteger::get_name() const {
    return name;
}

char* BigInteger::get_string() const {
    return this->value_string;
}

BigInteger& BigInteger::operator = (const BigInteger& big_integer) {
    char* new_value_string = new char[big_integer.capacity]();
    if (new_value_string != NULL) {
        if (this->value_string != NULL) {
            delete[](this->value_string);
            this->sign = true;
            this->length = 0;
            this->capacity = 0;
        }

        this->value_string = new_value_string;
        memcpy(this->value_string, big_integer.get_string(), big_integer.capacity);
        this->sign = big_integer.sign;
        this->length = big_integer.length;
        this->capacity = big_integer.capacity;
    }

    return *this;
}

bool BigInteger::operator == (const BigInteger& big_integer) const {
    if (this->length != big_integer.length) {
        return false;
    }

    if (this->sign != big_integer.sign) {
        return false;
    }

    for (unsigned int place_index = 0; place_index < big_integer.length; place_index++) {
        if (this->value_string[place_index] != big_integer.value_string[place_index]) {
            return false;
        }
    }

    return true;
}

bool BigInteger::operator > (const BigInteger& big_integer) const {
    BigInteger::COMPARE_RESULT compare_result;

    // If sign is the same
    if (this->sign == big_integer.sign) {
        // Compare two absolute values
        compare_result = this->compare_absolute_value(big_integer);

        // Compare two positive values
        if (this->sign) {
            if (compare_result == this->COMPARE_LARGER) {
                return true;
            }
            else {
                return false;
            }
        }
            // Compare two negative values
        else {
            if (compare_result == this->COMPARE_SMALLER) {
                return true;
            }
            else {
                return false;
            }
        }
    }
        // No need to compare
    else {
        if (this->sign) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool BigInteger::operator < (const BigInteger& big_integer) const {
	return (big_integer > *this);
}

bool BigInteger::operator >= (const BigInteger& big_integer) const {
	return !(*this < big_integer);
}

bool BigInteger::operator <= (const BigInteger& big_integer) const {
	return !(*this > big_integer);
}

BigInteger BigInteger::operator + (const BigInteger& big_integer) const {
    BigInteger result;

    BigInteger::COMPARE_RESULT compare_result;
    compare_result = this->compare_absolute_value(big_integer);

    // 피연산자의 부호가 다르며 절댓값은 같은 경우 합은 0
    if (this->sign != big_integer.sign && compare_result == this->COMPARE_EQUAL) {
        result.length = 1;
        result.value_string[0] = '0';
        return result;
    }

    int length = this->length;
    int given_length = big_integer.length;

    char* value_string = new char[length]();
    char* given_value_string = new char[given_length]();
    if (value_string == NULL || given_value_string == NULL) return result;

    memcpy(value_string, this->value_string, length);
    memcpy(given_value_string, big_integer.value_string, given_length);

    // value_string이 팰린드롬수가 아니면 문자열 뒤집기
    bool this_palindrome = true;
    for (int place_index = 0; place_index < length / 2; place_index++) {
        if (value_string[place_index] != value_string[length - 1 - place_index]) {
            this_palindrome = false;
            break;
        }
    }
    if (this_palindrome != true) {
        for (int place_index = 0; place_index < length / 2; place_index++) {
            std::swap(value_string[place_index], value_string[length - 1 - place_index]);
        }
    }

    // given_value_string이 팰린드롬수가 아니면 문자열 뒤집기
    bool bi_palindrome = true;
    for (int place_index = 0; place_index < given_length / 2; place_index++) {
        if (given_value_string[place_index] != given_value_string[given_length - 1 - place_index]) {
            bi_palindrome = false;
            break;
        }
    }
    if (bi_palindrome != true) {
        for (int place_index = 0; place_index < given_length / 2; place_index++) {
            std::swap(given_value_string[place_index], given_value_string[given_length - 1 - place_index]);
        }
    }

    // 절댓값이 크거나 같은 값 기준으로 반복문 검사하기 위해 피연산자를 ge(greater or equal)와 lt(little)로 분류
    // 피연산자의 부호가 다른 + 연산에서도 절댓값이 크거나 같은 값에서 작은 값을 빼도록 하는 것이 용이
    int ge_length = compare_result != this->COMPARE_SMALLER ? length : given_length;
    int lt_length = compare_result != this->COMPARE_SMALLER ? given_length : length;
    char* ge_value_string = compare_result != this->COMPARE_SMALLER ? value_string : given_value_string;
    char* lt_value_string = compare_result != this->COMPARE_SMALLER ? given_value_string : value_string;

    int ge_value = 0;
    int lt_value = 0;

    int res_length = 0;
    char* res_value_string = NULL;

    // 피연산자의 부호가 같은 경우
    if (this->sign == big_integer.sign) {
        // 피연산자의 부호가 같으며 양수(음수)이면 result도 양수(음수)
        result.sign = this->sign ? true : false;
        res_value_string = new char[ge_length + 1]();

        int partial_result = 0;
        bool carry = false;

        // 각 자릿수마다 피연산자의 덧셈과 10이 넘는 자릿수의 올림(carry)을 더해 부호가 같은 + 연산 구현
        for (int place_index = 0; place_index < ge_length; place_index++) {
            ge_value = ge_value_string[place_index] - '0';
            // lt_value_string의 최대 인덱스는 lt_length - 1이므로 이후 lt_value에는 0을 대입
            lt_value = place_index < lt_length ? lt_value_string[place_index] - '0' : 0;

            partial_result = ge_value + lt_value + carry;
            carry = false;
            if (partial_result >= 10) {
                partial_result -= 10;
                carry = true;
            }

            res_value_string[place_index] = partial_result + '0';
        }

        res_length = ge_length;
        // 최상위 digit에서 carry가 발생했을 경우 digit을 확장하여 저장
        if (carry) {
            res_length++;
            res_value_string[res_length - 1] = carry + '0';
            carry = false;
        }
    }
        // 피연산자의 부호가 다르며 절댓값도 다른 경우(같은 경우는 합이 0)
    else {
        // 절댓값이 큰 수가 양수면 절댓값이 작은 수와의 뺄셈도 양수
        if (compare_result == this->COMPARE_LARGER) {
            result.sign = this->sign ? true : false;
        }
        else {
            result.sign = big_integer.sign ? true : false;
        }

        res_value_string = new char[ge_length]();

        int partial_result = 0;
        bool borrow = false;

        // 각 자릿수마다 피연산자의 뺄셈에서 0보다 작은 자릿수의 내림(borrow)을 빼 부호가 다른 + 연산 구현
        for (int place_index = 0; place_index < ge_length; place_index++) {
            ge_value = ge_value_string[place_index] - '0';
            // lt_value_string의 최대 인덱스는 lt_length - 1이므로 이후 lt_value에는 0을 대입
            lt_value = place_index < lt_length ? lt_value_string[place_index] - '0' : 0;

            partial_result = ge_value - lt_value - borrow;
            borrow = false;
            if (partial_result < 0) {
                partial_result += 10;
                borrow = true;
            }

            res_value_string[place_index] = partial_result + '0';
        }

        res_length = ge_length;
        // 뺄셈의 결과로 만들어진 무효한 '0' 문자열 제거
        for (int place_index = 0; place_index < ge_length; place_index++) {
            if (res_value_string[ge_length - 1 - place_index] != '0') {
                break;
            }
            res_length--;
        }
    }

    // 덧셈 결과를 문자열 뒤집기하여 저장
    for (int place_index = 0; place_index < res_length; place_index++) {
        result.value_string[place_index] = res_value_string[res_length - 1 - place_index];
        result.length++;
        if (result.length == result.capacity) {
            result.doubling_capacity();
        }
    }

    delete[](value_string);
    delete[](given_value_string);
    delete[](res_value_string);

    return result;
}

BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
    BigInteger result;
    BigInteger minus_big_integer = big_integer;

    // 오른쪽 피연산자의 부호를 반대로 변경
    minus_big_integer.sign = !big_integer.sign;

    result = *this + minus_big_integer;
    return result;
}

BigInteger BigInteger::operator * (const BigInteger& big_integer) const {
    /* Implement if you want */
    BigInteger result;

    return result;
}

BigInteger BigInteger::operator / (const BigInteger& big_integer) const {
    /* Implement if you want */
    BigInteger result;

    return result;
}

BigInteger BigInteger::operator % (const BigInteger& big_integer) const {
    /* Implement if you want */
    BigInteger result;

    return result;
}

std::ostream& operator << (std::ostream& out, const BigInteger& big_integer) {
    // Print minus sign
    if (!big_integer.sign) {
        out << std::string("-");
    }

    // Print values
    out << std::string(big_integer.get_string(), big_integer.length);
    return out;
}

std::istream& operator >> (std::istream& in, BigInteger& big_integer) {
    std::string input_string;
    in >> input_string;
    big_integer = BigInteger(input_string);

    return in;
}
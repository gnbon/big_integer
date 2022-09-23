#include "big_integer.h"


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
	delete(this->value_string);

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
	/* Should be implemented */
}

BigInteger::BigInteger(int value) {
	/* Should be implemented */
}

BigInteger::BigInteger(long long value) {
	/* Should be implemented */
}

BigInteger::BigInteger(std::string value) {
	/* Should be implemented */
}

BigInteger::BigInteger(const BigInteger& big_integer) {
	this->initialize_properties();

	char* new_value_string = new char[big_integer.capacity]();
	if (new_value_string != NULL) {
		if (this->value_string != NULL) {
			delete(this->value_string);
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
		delete(this->value_string);
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
			delete(this->value_string);
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
	return !(big_integer < *this);
}

bool BigInteger::operator <= (const BigInteger& big_integer) const {
	return !(big_integer > *this);
}

BigInteger BigInteger::operator + (const BigInteger& big_integer) const {
	/* Should be implemented */
	BigInteger result;

	return result;
}

BigInteger BigInteger::operator - (const BigInteger& big_integer) const {
	/* Should be implemented */
	BigInteger result;

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

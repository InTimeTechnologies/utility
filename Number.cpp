#include "Number.h"

// Dependencies | std
#include <limits>
//#include <stdexcept>

// class Number

// Static | public

// Properties
const char Number::MAX_DIGIT_COUNT = 18;
const char Number::MAX_WHOLE_DIGIT_COUNT = 10;
const char Number::MAX_DECIMAL_DIGIT_COUNT = 8;

// Functions
bool Number::s_isAdditionSafe(const Number& a, const Number& b) {
	// Positive underflow: a - b < LLONG_MIN
	if (b.value > 0LL && a.value > std::numeric_limits<long long>::max() - b.value)
		return true;

	// Negative overflow: a - b > LLONG_MAX
	if (b.value < 0LL && a.value < std::numeric_limits<long long>::min() - b.value)
		return true;

	return false; // Safe
}
bool Number::s_isSubtractionSafe(const Number& a, const Number& b) {
	// Positive underflow: a - b < LLONG_MIN
	if (b.value > 0LL && a.value < std::numeric_limits<long long>::min() + b.value)
		return false;

	// Negative overflow: a - b > LLONG_MAX
	if (b.value < 0LL && a.value > std::numeric_limits<long long>::max() + b.value)
		return false;

	return true; // Safe
}
bool Number::s_isMultiplicationSafe(const Number& a, const Number& b) {
	// Handle 0 early — always safe
	if (a.value == 0 || b.value == 0)
		return true;

	// Check for overflow or underflow
	if (a.value > 0) {
		if (b.value > 0) {
			return a.value <= std::numeric_limits<long long>::max() / b.value;
		}
		else {
			return b.value >= std::numeric_limits<long long>::min() / a.value;
		}
	}
	else {
		if (b.value > 0) {
			return a.value >= std::numeric_limits<long long>::min() / b.value;
		}
		else {
			return a.value == 0 || b.value >= std::numeric_limits<long long>::max() / a.value;
		}
	}
}
bool Number::s_isDivisionSafe(const Number& a, const Number& b) {
	// Division by zero is always unsafe
	if (b.value == 0)
		return false;

	// Special case: LLONG_MIN / -1 causes overflow
	if (a.value == std::numeric_limits<long long>::min() && b.value == -1)
		return false;

	return true; // Safe division
}

// Object | public

// Constructor / Destructor
Number::Number(long long value) : value(value) {

}
Number::Number(const std::string& string) {
	setValue(string);
}

// Setters
bool Number::setValue(const std::string& value) {
	// Counters
	char wholeDigitCount = 0;
	char decimalDigitCount = 0;
	bool decimalPointPresent = false;
	bool hasSign = false;

	// Count whole and decimal digits and decimal points for string validation
	for (size_t i = 0; i < value.size(); i++) {
		char c = value[i];

		if (std::isdigit(c)) {
			if (decimalPointPresent)
				decimalDigitCount++;
			else
				wholeDigitCount++;
		}
		else if (c == '.') {
			if (decimalPointPresent)
				return false; // Fail: multiple decimal points
			decimalPointPresent = true;
		}
		else if (i == 0 && c == '-') {
			hasSign = true;
		}
		else {
			return false; // Fail: character is not valid
		}

		if (wholeDigitCount > MAX_WHOLE_DIGIT_COUNT || decimalDigitCount > MAX_DECIMAL_DIGIT_COUNT)
			return false; // Fail: string exceeds maximum number of whole / decimal digits
	}

	// Convert string to Number format
	std::string wholePart = value.substr(0, wholeDigitCount + (long long)hasSign); // Retrieve whole portion
	std::string decimalPart = value.substr(value.size() - decimalDigitCount, decimalDigitCount); // Retrieve decimal portion
	std::string trailingZeroes = std::string(MAX_DECIMAL_DIGIT_COUNT - decimalDigitCount, '0'); // Add trailing zeroes

	this->value = std::stoll(wholePart + decimalPart + trailingZeroes); // Convert to long long

	// Return success
	return true;
}
bool Number::setValue(float value) {
	return setValue(std::to_string(value));
}
bool Number::setValue(double value) {
	return setValue(std::to_string(value));
}

// Functions
std::string Number::to_string() const {
	std::string string = std::to_string(value);
	if (string.size() == 8)
		string = "0." + string;
	else if (string.size() > 8)
		string.insert(string.end() - 8, '.');
	return string;
}
bool Number::isSigned() const {
	return value < 0LL ? true : false;
}

// Operators
Number Number::operator+(const Number& other) const {
	return Number(value + other.value);
}
Number Number::operator-(const Number& other) const {
	return Number(value - other.value);
}
Number Number::operator*(const Number& other) const {
	if (other.value == 0LL)
		return Number();

	long long thisWholePart = value / 100000000LL;
	long long thisDecimalPart = value % 100000000LL;

	long long otherWholePart = other.value / 100000000LL;
	long long otherDecimalPart = other.value % 100000000LL;

	long long resultWholePart = thisWholePart * otherWholePart;
	long long resultDecimalPart = 0LL;
	if (other.value != 0LL)
		resultDecimalPart = thisWholePart * otherDecimalPart + otherWholePart * thisDecimalPart + (thisDecimalPart * otherDecimalPart) / 100000000LL;

	long long result = resultWholePart * 100000000LL + resultDecimalPart;

	return Number(result);
}
Number Number::operator/(const Number& other) const {
	if (other.value == 0LL) {
		// Division by zero is undefined, so return a default-constructed Number (0.0).
		return Number();
	}

	// Find the common scale for both numbers
	long long commonScale = 100000000LL;

	// Convert both numbers to the common scale
	long long thisScaled = value * (100000000LL / commonScale);
	long long otherScaled = other.value * (100000000LL / commonScale);

	// Perform the division
	long long resultScaled = (thisScaled * commonScale) / otherScaled;

	return Number(resultScaled);
}
Number& Number::operator+=(const Number& other) {
	value += other.value;
	return *this;
}
Number& Number::operator-=(const Number& other) {
	value -= other.value;
	return *this;
}
Number& Number::operator*=(const Number& other) {
	value = (*this * other).value;
	return *this;
}
Number& Number::operator/=(const Number& other) {
	value = (*this / other).value;
	return *this;
}
Number& Number::operator=(const Number& other) {
	if (this != &other)
		value = other.value;
	return *this;
}
bool Number::operator==(const Number& other) const {
	return value == other.value;
}
bool Number::operator<(const Number& other) const {
	return value < other.value;
}
bool Number::operator>(const Number& other) const {
	return value > other.value;
}
bool Number::operator<=(const Number& other) const {
	return value <= other.value;
}
bool Number::operator>=(const Number& other) const {
	return value >= other.value;
}
bool Number::operator!=(const Number& other) const {
	return value != other.value;
}

// Operators | Conversions
Number& Number::operator=(const std::string& value) {
	setValue(value);
	return *this;
}
Number& Number::operator=(float value) {
	setValue(value);
	return *this;
}
Number& Number::operator=(double value) {
	setValue(value);
	return *this;
}
Number& Number::operator=(long long value) {
	this->value = value;
	return *this;
}

// Convenience operators
Number::operator std::string() const {
	return to_string();
}
Number::operator float() const {
	return std::stof(to_string());
}
Number::operator double() const {
	return std::stod(to_string());
}
Number::operator long long() const {
	return value;
}

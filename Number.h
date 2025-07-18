#pragma once

// Dependencies | std
#include <string>

struct Number {
	// Static

	// Properties
	static const char MAX_DIGIT_COUNT;
	static const char MAX_WHOLE_DIGIT_COUNT;
	static const char MAX_DECIMAL_DIGIT_COUNT;

	// Functions
	static bool s_isAdditionSafe(const Number& a, const Number& b);
	static bool s_isSubtractionSafe(const Number& a, const Number& b);
	static bool s_isMultiplicationSafe(const Number& a, const Number& b);
	static bool s_isDivisionSafe(const Number& a, const Number& b);

	// Object

	// Properties
	long long value = 0LL;

	// Constructor / Destructor
	Number() = default;
	Number(long long value);
	Number(const std::string& string);
	~Number() = default;

	// Setters
	bool setValue(const std::string& value);
	bool setValue(float value);
	bool setValue(double value);

	// Functions
	std::string to_string() const;
	bool isSigned() const;

	// Operators
	Number operator+(const Number& other) const;
	Number operator-(const Number& other) const;
	Number operator*(const Number& other) const;
	Number operator/(const Number& other) const;
	Number& operator+=(const Number& other);
	Number& operator-=(const Number& other);
	Number& operator*=(const Number& other);
	Number& operator/=(const Number& other);
	Number& operator=(const Number& other);
	bool operator==(const Number& other) const;
	bool operator<(const Number& other) const;
	bool operator>(const Number& other) const;
	bool operator<=(const Number& other) const;
	bool operator>=(const Number& other) const;
	bool operator!=(const Number& other) const;

	// Operators | Conversions
	Number& operator=(const std::string& value);
	Number& operator=(float value);
	Number& operator=(double value);
	Number& operator=(long long value);

	// Convenience operators
	operator std::string() const;
	operator float() const;
	operator double() const;
	operator long long() const;
};

// Notes
/*
 * long long range: [-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807]
 * long long range as decimal: [-92,233,720,368.54775808, 92,233,720,368.54775807]
 */

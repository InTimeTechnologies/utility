#pragma once

template <typename T> struct Range {
	// Properties
	T x0{};
	T x1{};

	// Constructor / Destructor
	Range() = default;
	Range(T value) : x0(value), x1(value) {}
	Range(T x0, T x1) : x0(x0), x1(x1) {}

	// Getters
	T getRange() const {
		return x1 - x0;
	}

	// Operators | comparison
	bool operator==(const Range& other) const {
		return x0 == other.x0 && x1 == other.x1;
	}
	bool operator!=(const Range& other) const {
		return x0 != other.x0 || x1 != other.x1;
	}
	bool operator<(const Range& other) const {
		return x1 < other.x0;
	}
	bool operator>(const Range& other) const {
		return x0 > other.x1;
	}
	bool operator<=(const Range& other) const {
		return x1 <= other.x0;
	}
	bool operator>=(const Range& other) const {
		return x0 >= other.x1;
	}

	// Functions
	bool overlaps(const Range& other) const {
		return !(x1 < other.x0 || x0 > other.x1);
	}
	bool inside(const Range& other) const {
		return x0 <= other.x1 && x1 >= other.x0;
	}
	void merge(const Range& other) {
		x0 = x0 < other.x0 ? x0 : other.x0;
		x1 = x1 > other.x1 ? x1 : other.x1;
	}
	Range getMerge(const Range& other) const {
		return Range{ x0 < other.x0 ? x0 : other.x0, x1 > other.x1 ? x1 : other.x1 };
	}
};

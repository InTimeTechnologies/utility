/******************************************************************************
 * Filename:    Range.h
 * Author:      Christophr Barrios Agosto
 * Date:        August 2, 2025
 * Description: This header defines the Rangee template class.
 *              It is a simple rane class with the comparison operators
 *              overloaded. So that std::set<Range> can properly order the
 *              ranges in the BinaryRangeTree class.s
 *
 * Usage:
 *     Range<int> range{ -5, 10 };
 *     range.getRange();
 *     range.x0;
 *     range.x1;
 *
 * License:     MIT License
 ******************************************************************************/

#pragma once

// Forward declarations
template <typename T> class BinaryRangeTree;

template <typename T> class Range {
	// Friends
	friend class BinaryRangeTree<T>;

	// Object
	private:
		// Properties
		T x0{};
		T x1{};

	public:
		// Constructor / Destructor
		Range() = default;
		Range(T value) : x0(value), x1(value) {
			if (x0 > x1)
				std::swap(x0, x1);
		}
		Range(T x0, T x1) : x0(x0), x1(x1) {
			if (this->x0 > this->x1)
				std::swap(this->x0, this->x1);
		}

		// Getters
		T getX0() const {
			return x0;
		}
		T getX1() const {
			return x1;
		}
		T getRange() const {
			return x1 - x0;
		}

		// Setters
		void setX0(T x0) {
			if (x0 > x1)
				x1 = x0;
			else
				this->x0 = x0;
		}
		void setX1(T x1) {
			if (x1 < x0)
				x0 = x1;
			else
				this->x1 = x1;
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

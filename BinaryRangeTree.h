/******************************************************************************
 * Filename:    BinaryRangeTree.h
 * Author:      Chris Barrios Agosto
 * Date:        August 2, 2025
 * Description: This header defines the BinaryRangeTree template class.
 *              It uses std::set to store ordered, non-overlapping integral ranges.
 *              Provides efficient insertions and deletions with auto-merging logic.
 *
 * Usage:
 *     BinaryRangeTree<int> rangeTree;
 *     rangeTree.push(5); // Adds value 5
 *     rangeTree.pop({5, 10}); // Removes range 5-10
 *
 * License:     MIT License
 ******************************************************************************/

#pragma once

// Dependencies | std
#include <set>
#include <type_traits>
#include <istream>
#include <ostream>

// Dependencies | utility
#include "Range.h"

template <typename T> class BinaryRangeTree {
	// Static assert:
	static_assert(std::is_integral<T>::value, "BinaryRangeTree requires an integral type."); 
	
	// Object
	private:
		// Properties
		std::set<Range<T>> ranges{};

	public:
		// Constructor / Destructor
		BinaryRangeTree() = default;
		BinaryRangeTree(const Range<T>& range) : ranges(std::set<Range<T>>{ range }) {}
		BinaryRangeTree(const std::set<Range<T>>& ranges) {
			for (const Range<int>& range : ranges)
				this->ranges.insert(range);
		}
		BinaryRangeTree(std::set<Range<T>>&& ranges) {
			for (const Range<int> range : ranges)
				this->ranges.insert(range);
			ranges.clear();
		}

		// Getters
		std::set<Range<T>> getRanges() const {
			return ranges;
		}

		// Setters
		void setRanges(const std::set<Range<T>>& ranges) {
			this->ranges.clear();
			for (Range<T> range : ranges)
				push(range);
		}

		// Functions
		bool push(T value) {
			return push({ value, value });
		}
		bool push(const Range<T>& range) {
			Range<T> newRange{ range };
			std::pair<std::set<Range<T>>::iterator, bool> result = ranges.insert(newRange);

			if (result.second == false)
				return false;

			typename std::set<Range<T>>::iterator newNode = result.first;
			typename std::set<Range<T>>::iterator prev = newNode;
			typename std::set<Range<T>>::iterator next = std::next(newNode);
			bool merged = false;

			if (prev != ranges.begin()) {
				--prev;
				if (prev->x1 + 1 == newRange.x0) {
					newRange.x0 = prev->x0;
					ranges.erase(prev);
					merged = true;
				}
			}
			if (next != ranges.end()) {
				if (next->x0 - 1 == newRange.x1) {
					newRange.x1 = next->x1;
					ranges.erase(next);
					merged = true;
				}
			}

			if (merged) {
				if (ranges.size() == 1) {
					ranges.clear();
					ranges.insert(newRange);
				}
				else {
					typename std::set<Range<T>>::iterator hintIterator = newNode;
					if (newNode != ranges.begin()) {
						hintIterator--;
					}
					else if (newNode != std::prev(ranges.end())) {
						hintIterator++;
					}

					ranges.erase(newNode);
					ranges.insert(hintIterator, newRange);
				}
			}

			return true;
		}
		bool pop(T value) {
			return pop({ value, value });
		}
		bool pop(const Range<T>& rangeToRemove) {
			typename std::set<Range<T>>::iterator iteratorToRemove = ranges.lower_bound(rangeToRemove);

			if (iteratorToRemove == ranges.end())
				return false;

			if (*iteratorToRemove == rangeToRemove) {
				ranges.erase(iteratorToRemove);
				return true;
			}

			Range<T> currentRange = *iteratorToRemove;
			if (rangeToRemove.inside(*iteratorToRemove)) {
				typename std::set<Range<T>>::iterator hintIterator = iteratorToRemove;
				typename std::set<Range<T>>::iterator prev = ranges.end();
				typename std::set<Range<T>>::iterator next = ranges.end();
				if (iteratorToRemove != ranges.begin()) {
					prev = std::prev(iteratorToRemove);
					hintIterator = prev;
				}
				if (std::next(iteratorToRemove) != ranges.end()) {
					next = std::next(iteratorToRemove);
					hintIterator = next;
				}

				ranges.erase(iteratorToRemove);

				bool createLeftNode{ currentRange.x0 < rangeToRemove.x0 };
				bool createRightNode{ currentRange.x1 > rangeToRemove.x1 };
				if (createLeftNode)
					ranges.insert(hintIterator, { currentRange.x0, rangeToRemove.x0 - 1 });
				if (createRightNode)
					ranges.insert(hintIterator, { rangeToRemove.x1 + 1, currentRange.x1 });

				return true;
			}

			return false;
		}
		bool popLeast(T* value) {
			typename std::set<Range<T>>::iterator leastIterator = ranges.begin();
			if (leastIterator == ranges.end())
				return false;
			if (value != nullptr)
				*value = leastIterator->x0;

			if (leastIterator->x0 == leastIterator->x1) {
				ranges.erase(leastIterator);
				return true;
			}

			typename std::set<Range<T>>::iterator hintIterator = std::next(leastIterator) == ranges.end() ? std::next(leastIterator) : ranges.end();
			Range<T> newRange{ leastIterator->x0 + 1, leastIterator->x1 };
			ranges.erase(leastIterator);
			if (hintIterator == ranges.end())
				ranges.insert(newRange);
			else
				ranges.insert(hintIterator, newRange);

			return true;
		}
		bool popGreatest(T* value) {
			if (ranges.size() == 0ULL)
				return false;

			typename std::set<Range<T>>::iterator greatestIterator = std::prev(ranges.end());
			if (value != nullptr)
				*value = greatestIterator->x1;

			if (greatestIterator->x0 == greatestIterator->x1) {
				ranges.erase(greatestIterator);
				return true;
			}

			typename std::set<Range<T>>::iterator hintIterator = greatestIterator == ranges.begin() ? ranges.end() : std::prev(greatestIterator);
			Range<T> newRange{ greatestIterator->x0, greatestIterator->x1 - 1 };
			ranges.erase(greatestIterator);
			if (hintIterator == ranges.end())
				ranges.insert(newRange);
			else
				ranges.insert(hintIterator, newRange);

			return true;
		}
		void clear() {
			ranges.clear();
		}
};

// Operators | std::ostream <<
template <typename T>
std::ostream& operator<<(std::ostream& ostream, const BinaryRangeTree<T>& binaryRangeTree) {
	std::set<Range<T>> set = binaryRangeTree.getRanges();
	ostream << "[";
	for (typename std::set<Range<T>>::iterator iterator = set.begin(); iterator != set.end(); iterator++) {
		ostream << *iterator;
		if (iterator != std::prev(set.end()))
			ostream << ", ";
	}
	return ostream << "]";
}

// Operators | std::istream >>
template <typename T>
std::istream& operator>>(std::istream& istream, BinaryRangeTree<T>& binaryRangeTree) {
	std::set<Range<T>> set{};
	char c{ 0 };
	Range<T> range{};

	istream >> std::ws >> c;
	if (c != '[') {
		istream.setstate(std::ios::failbit);
		return istream;
	}

	while (true) {
		istream >> range;
		if (!istream)
			break;
		set.insert(range);

		istream >> std::ws >> c;
		if (c == ']') {
			break; // done reading
		}
		else if (c != ',') {
			istream.setstate(std::ios::failbit);
			break;
		}
	}

	binaryRangeTree.setRanges(set);

	return istream;
}

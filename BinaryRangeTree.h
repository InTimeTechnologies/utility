#pragma once

// Dependencies | std
#include <set>

// Dependencies | sandbox
#include "Range.h"

class BinaryIntRangeTree {
	private:
		// Properties
		std::set<IntRange> ranges{};

	public:
		// Constructor / Destructor
		BinaryIntRangeTree() = default;
		BinaryIntRangeTree(const IntRange& range);
		BinaryIntRangeTree(const std::set<IntRange>& ranges);

		// Getters
		std::set<IntRange> getRanges() const;

		// Functions
		bool push(int value);
		bool push(const IntRange& range);
		bool pop(int value);
		bool pop(const IntRange& range);
		bool popLeast(int& value);
		bool popGreatest(int& value);
};


/*
class BinaryIntRangeTree {
	public:
		// Struct
		class Node {
			public:
				// Properties
				BinaryIntRangeTree* owner{ nullptr };
				Node* parent{ nullptr };
				Node* left{ nullptr };
				Node* right{ nullptr };

				int least{ 0 };
				int greatest{ 0 };

				// Functions
				Node* getLeftmost() const;
				Node* getRightmost() const;
				Node* unlinkParent();
				Node* unlinkLeft();
				Node* unlinkRight();
				Node* unlink();
				bool linkParent(Node* node);
				bool linkLeft(Node* node);
				bool linkRight(Node* node);
				bool overlaps(Node* other);

			public:
				// Constructor / Destructor
				Node() = default;
				Node(int least, int greatest);
				Node(const Node& other);
				~Node();

				// Operators | assignment
				Node& operator=(const Node& other);
				Node& operator=(Node&& other) noexcept;

				// Operators | comparison
				bool operator<(const Node& other);
				bool operator>(const Node& other);
				bool operator==(const Node& other);
				bool operator<=(const Node& other);
				bool operator>=(const Node& other);

				// Getters
				int getLeast() const;
				int getGreatest() const;
				int getRange() const;

				// Functions
				bool isLeft() const;
				bool isRight() const;
				bool isRoot() const;
				bool hasParent() const;
				bool has(int value) const;
		};

	// Object
	private:
		// Properties
		Node* root{ nullptr };

	public:
		// Constructor / Destructor
		BinaryIntRangeTree() = default;
		BinaryIntRangeTree(int least, int greatest);
		~BinaryIntRangeTree();

		// Getters
		bool push(int value);
		bool pop(int value);
		bool has(int value);
		unsigned int count() const;

};
*/
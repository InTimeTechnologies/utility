#include "BinaryRangeTree.h"

// class BinaryIntRangeTree

// Object | public

// Constructor / Destructor
BinaryIntRangeTree::BinaryIntRangeTree(const IntRange& range) : ranges({ range }) {}
BinaryIntRangeTree::BinaryIntRangeTree(const std::set<IntRange>& ranges) : ranges(ranges) {}

// Getters
std::set<IntRange> BinaryIntRangeTree::getRanges() const {
	return ranges;
}

// Functions
bool BinaryIntRangeTree::push(int value) {
	return push({ value, value });
}
bool BinaryIntRangeTree::push(const IntRange& range) {
	IntRange newRange{ range };
	std::pair<std::set<IntRange>::iterator, bool> result = ranges.insert(newRange);

	if (result.second == false)
		return false;

	std::set<IntRange>::iterator newNode = result.first;
	std::set<IntRange>::iterator prev = newNode;
	std::set<IntRange>::iterator next = std::next(newNode);
	bool merged = false;

	if (prev != ranges.begin()) {
		--prev;
		if (prev->greatest + 1 == newRange.least) {
			newRange.least = prev->least;
			ranges.erase(prev);
			merged = true;
		}
	}
	if (next != ranges.end()) {
		if (next->least - 1 == newRange.greatest) {
			newRange.greatest = next->greatest;
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
			std::set<IntRange>::iterator hintIterator = newNode;
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
bool BinaryIntRangeTree::pop(int value) {
	return pop({ value, value });
}
bool BinaryIntRangeTree::pop(const IntRange& range) {
	if (ranges.size() == 0)
		return false;

	
}


/*
#include "BinaryRangeTree.h"

// class BinaryIntRangeTree::Node

// Object | private

// Functions
BinaryIntRangeTree::Node* BinaryIntRangeTree::Node::getLeftmost() const {
	if (left == nullptr)
		return nullptr;

	Node* leftmostNode{ left };
	while (leftmostNode->left != nullptr)
		leftmostNode = leftmostNode->left;

	return leftmostNode;
}
BinaryIntRangeTree::Node* BinaryIntRangeTree::Node::getRightmost() const {
	if (right == nullptr)
		return nullptr;

	Node* rightmostNode{ right };
	while (rightmostNode->right != nullptr)
		rightmostNode = rightmostNode->right;

	return rightmostNode;
}
BinaryIntRangeTree::Node* BinaryIntRangeTree::Node::unlinkParent() {
	if (parent != nullptr)
		if (isLeft())
			parent->left = nullptr;
		else
			parent->right = nullptr;
	Node* oldParent = parent;
	parent = nullptr;
	return oldParent;
}
BinaryIntRangeTree::Node* BinaryIntRangeTree::Node::unlinkLeft() {
	if (left != nullptr)
		left->parent = nullptr;
	left = nullptr;
	return nullptr;
}
BinaryIntRangeTree::Node* BinaryIntRangeTree::Node::unlinkRight() {
	if (right != nullptr)
		right->parent = nullptr;
	right = nullptr;
	return nullptr;
}
BinaryIntRangeTree::Node* BinaryIntRangeTree::Node::unlink() {
	Node* oldParent = unlinkParent();
	Node* oldLeft = unlinkLeft();
	Node* oldRight = unlinkRight();

	return nullptr;
}
bool BinaryIntRangeTree::Node::linkParent(Node* other) {
	if (parent != nullptr) {
		if (other < parent && parent->left == nullptr) {
			parent = other;
			other->left = this;
		}
		else if (other > parent && parent->right == nullptr) {
			parent = other;
			other->right = this;
		}
	}
	return false;
}
bool BinaryIntRangeTree::Node::linkLeft(Node* node) {

	return false;
}
bool BinaryIntRangeTree::Node::linkRight(Node* node) {

	return false;
}
bool BinaryIntRangeTree::Node::overlaps(Node* other) {
	if (other == nullptr)
		return false;
	if (other == this)
		return true;
	return !(greatest < other->least || least > other->greatest);
}

// Object | public

// Constructor / Destructor
BinaryIntRangeTree::Node::Node(int least, int greatest) : least(least), greatest(greatest) {}
BinaryIntRangeTree::Node::Node(const Node& other) : least(other.least), greatest(other.greatest) {}
BinaryIntRangeTree::Node::~Node() {
	if (left != nullptr) {

	}
	else if (right != nullptr) {

	}
	else {

	}

	if (parent != nullptr) {
		if (isLeft())
			parent->left = nullptr;
		else
			parent->right = nullptr;
	}
}

// Operator | assignment
BinaryIntRangeTree::Node& BinaryIntRangeTree::Node::operator=(const Node& other) {
	if (&other != this) {
		least = other.least;
		greatest = other.greatest;
	}

	return *this;
}
BinaryIntRangeTree::Node& BinaryIntRangeTree::Node::operator=(Node&& other) noexcept {
	if (&other != this) {
		least = other.least;
		greatest = other.greatest;

		other.least = 0;
		other.greatest = 0;
	}

	return *this;
}
bool BinaryIntRangeTree::Node::operator<(const Node& other) {
	return greatest < other.least;
}
bool BinaryIntRangeTree::Node::operator>(const Node& other) {
	return least > other.greatest;
}
bool BinaryIntRangeTree::Node::operator==(const Node& other) {
	return least == other.least && greatest == other.greatest;
}
bool BinaryIntRangeTree::Node::operator<=(const Node& other) {
	return greatest <= other.least;
}
bool BinaryIntRangeTree::Node::operator>=(const Node& other) {
	return least >= other.greatest;
}

// Getters
int BinaryIntRangeTree::Node::getLeast() const {
	return least;
}
int BinaryIntRangeTree::Node::getGreatest() const {
	return greatest;
}
int BinaryIntRangeTree::Node::getRange() const {
	return greatest - least;
}

// Functions
bool BinaryIntRangeTree::Node::isLeft() const {
	return parent == nullptr ? false : parent->left == this;
}
bool BinaryIntRangeTree::Node::isRight() const {
	return parent == nullptr ? false : parent->right == this;
}
bool BinaryIntRangeTree::Node::isRoot() const {
	return parent == nullptr;
}
bool BinaryIntRangeTree::Node::hasParent() const {
	return parent != nullptr;
}
bool BinaryIntRangeTree::Node::has(int value) const {
	if (value >= least && value <= greatest)
		return true;
	return left->has(value) || right->has(value) ? true : false;
}

// class BinaryRangeTree

// Object | public

// Constructor / Destructor
BinaryIntRangeTree::BinaryIntRangeTree(int least, int greatest) : root(new Node{ least, greatest }) {

}

// Functions
bool BinaryIntRangeTree::push(int value) {
	if (root == nullptr)
		return false;

	
}
bool BinaryIntRangeTree::pop(int value) {
	return true;
}
bool BinaryIntRangeTree::has(int value) {
	if (root == nullptr)
		return false;
	
	Node* node = root;
	return true;
}
unsigned int BinaryIntRangeTree::count() const {
	return 0U;
}
*/

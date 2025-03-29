#include "AVLTree.h"

#include <algorithm>
#include <cstddef>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

AVLTree::AVLTree() = default;

AVLTree::AVLTree(const AVLTree& other)
{
	copy(other);
}

AVLTree::~AVLTree()
{
	delete m_root;
}

bool AVLTree::insert(const std::string& key, int value)
{
	return insert(key, value, m_root);
}

bool AVLTree::insert(const std::string& key, const int& value, Node*& root)
{
	// No duplicate was found and no change in order required
	if (!root)
	{
		root = new Node(key, value);
		m_size++;
		return true;
	}

	// First: insert key-value pair
	if (root->m_key < key)
	{
		if (!insert(key, value, root->m_right))
		{
			return false;
		}
	}
	else if (root->m_key > key)
	{
		if (!insert(key, value, root->m_left))
		{
			return false;
		}
	}
	else
	{
		// Key matches a key-value pair, don't insert
		return false;
	}

	// Update height
	root->m_height = 1 + std::max(getHeight(root->m_left), getHeight(root->m_right));
	m_height = getHeight(m_root);

	// Second: rebalance the tree
	rebalance(root);

	return true;
}


bool AVLTree::remove(const std::string& key)
{
	return remove(key, m_root);
}

bool AVLTree::remove(const std::string& key, Node* root)
{
	// Base case where removal wasn't found
	if (!root)
	{
		return false;
	}

	if (root->m_key == key)
	{
		// Case 1: Leaf Node removal
		if (!root->m_left && !root->m_right)
		{
			if (!root->m_parent)
			{
				m_root = nullptr;
			}
			else if (root->m_parent->m_left == root)
			{
				root->m_parent->m_left = nullptr;
			}
			else if (root->m_parent->m_right == root)
			{
				root->m_parent->m_right = nullptr;
			}

			// Free memory and decrement size
			delete root;
			m_size--;
			return true;
		}
		// Case 2: Node with only 1 child
		else if (!root->m_left || !root->m_right)
		{
			Node* child = root->m_left ? root->m_left : root->m_right;

			// // Update pointers
			if (!root->m_parent)
			{
				m_root = child;
			}
			else if (root->m_parent->m_left == root)
			{
				root->m_parent->m_left = child;
			}
			else if (root->m_parent->m_right == root)
			{
				root->m_parent->m_right = child;
			}

			// Update parent for the child to the root's parent
			if (child)
			{
				child->m_parent = root->m_parent;
			}	

			// Remove active pointers (child) before deletion
			root->m_left = nullptr;
			root->m_right = nullptr;

			// Free memory and decrement size
			delete root;
			m_size--;
			return true;
		}
		// Case 3: Node with two children
		else
		{

		}
	}

	if (root->m_key > key)
	{
		return remove(key, root->m_left);
	}
	else
	{
		return remove(key, root->m_right);
	}
}


bool AVLTree::contains(const std::string& key) const
{
	return contains(key, m_root);
}

bool AVLTree::contains(const std::string& key, const Node* root) const
{
	// Base case where key wasn't found
	if (!root)
	{
		return false;
	}

	if (root->m_key == key)
	{
		return true;
	}

	if (key < root->m_key)
	{
		return contains(key, root->m_left);
	}
	else
	{
		return contains(key, root->m_right);
	}
}

std::optional<int> AVLTree::get(const std::string& key) const
{
	return get(key, m_root);
}

std::optional<int> AVLTree::get(const std::string& key, Node* const& root) const
{
	if (!root)
	{
		return std::nullopt;
	}

	if (root->m_key == key)
	{
		return root->m_data;
	}

	if (key < root->m_key)
	{
		return get(key, root->m_left);
	}
	else
	{
		return get(key, root->m_right);
	}
}

int& AVLTree::get_value(const std::string& key, Node* const& root)
{
	if (!root)
	{
		throw std::runtime_error("Invalid key, can't return reference to nullptr Node.");
	}

	if (root->m_key == key)
	{
		return root->m_data;
	}

	if (root->m_key > key)
	{
		return get_value(key, root->m_left);
	}
	else
	{
		return get_value(key, root->m_right);
	}
}

std::vector<int> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const
{
	std::vector<int> rangeVector;

	findRange(lowKey, highKey, rangeVector, m_root);

	return rangeVector;
}

void AVLTree::findRange(const std::string& lowKey, const std::string& highKey,
						std::vector<int>& rangeVector, const Node* root)
{
	// Nullptr reached, stop recursion
	if (!root)
	{
		return;
	}

	// Check if key is in range, if so add to vector
	if (root->m_key >= lowKey && root->m_key <= highKey)
	{
		rangeVector.push_back(root->m_data);
	}

	// Recursively calls function until reaches nullptr
	findRange(lowKey, highKey, rangeVector, root->m_left);
	findRange(lowKey, highKey, rangeVector, root->m_right);
}

std::vector<std::string> AVLTree::keys() const
{
	std::vector<std::string> result;

	inorderTraversal(m_root, result);

	return result;
}

size_t AVLTree::size() const
{
	return m_size;
}

size_t AVLTree::getHeight() const
{
	return m_height;
}

int AVLTree::getHeight(Node* node)
{
	return node ? node->m_height : 0;
}


int& AVLTree::operator[](const std::string& key)
{
	return get_value(key, m_root);
}

void AVLTree::operator=(const AVLTree& other)
{
	copy(other);
}

void AVLTree::rebalance(Node* node)
{
	int balance = getBalance(node);

	// Prevent segfault from trying to access nullptr
	if (node)
	{
		rebalance(node->m_parent);
	}
}

void AVLTree::updateHeight()
{
	// Get current height of subtrees, or -1 if null
	int leftHeight, rightHeight = -1;
	if (m_root->m_left)
	{
		leftHeight = m_root->m_left->m_height;
	}

	if (m_root->m_right)
	{
		rightHeight = m_root->m_right->m_height;
	}

	// Assign height with calculated node height
	m_height = ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
}

void AVLTree::rotateRight(Node* node)
{
	Node* parent = node->m_parent;
	Node* left = node->m_left;
	Node* leftRight = node->m_right;

	node->m_left = leftRight;
	left->m_right = node;

	if (node->m_parent)
	{
	}
}

void AVLTree::rotateLeft(Node* node)
{
	Node* parent = node->m_parent;
	Node* left = node->m_left;
	Node* right = node->m_right;
}

int AVLTree::getBalance(const Node* node)
{
	return node ? getHeight(node->m_left) - getHeight(node->m_right) : 0;
}

void AVLTree::treePrint(std::ostream& os, Node* const& root, int depth)
{
	if (!root)
	{
		return;
	}

	treePrint(os, root->m_right, depth + 1);

	for (size_t i = 0; i < depth; i++)
	{
		os << "    ";
	}

	os << "<" << root->m_key << ": " << root->m_data << ">\n";

	treePrint(os, root->m_left, depth + 1);
}

void AVLTree::inorderTraversal(Node* node, std::vector<std::string>& result) const
{
	// Prevents seg fault
	if (!node)
	{
		return;
	}

	// Recursively calls traversal until reaches nullptr
	inorderTraversal(node->m_left, result);
	result.push_back(node->m_key);
	inorderTraversal(node->m_right, result);
}

void AVLTree::copy(const AVLTree& other)
{
	// Self-assignment
	if (this == &other)
	{
		return;
	}

	delete m_root;
	m_size = other.m_size;
	m_height = other.m_height;
	m_root = new Node(*other.m_root);
}

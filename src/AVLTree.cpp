#include "AVLTree.h"

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

AVLTree::AVLTree() = default;

AVLTree::AVLTree(const AVLTree& other)
{
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
		return false;
	}
	// Update height
	root->m_height = 1 + std::max(getHeight(root->m_left), getHeight(root->m_right));
	m_height = getHeight(m_root);

	// Rebalance the tree
	rebalance(root);
	return true;
}


[[nodiscard]] bool AVLTree::remove(const std::string& key) const
{
	return false;
}

[[nodiscard]] bool AVLTree::contains(const std::string& key) const
{
	return contains(key, m_root);
}

[[nodiscard]] bool AVLTree::contains(const std::string& key, const Node* root) const
{
	// Base base where key wasn't found
	if (!root)
	{
		return false;
	}
	else if (root->m_key == key)
	{
		return true;
	}

	if (root->m_left && root->m_left->m_key < key)
	{
		return contains(key, root->m_right);
	}
	else if (root->m_right && root->m_right->m_key > key)
	{
		return contains(key, root->m_left);
	}
}


[[nodiscard]] std::optional<int> AVLTree::get(const std::string& key) const
{

	// Base case where key wasn't found in tree
	return std::nullopt;
}

[[nodiscard]] std::vector<std::string> AVLTree::findRange(const std::string& lowKey,
														  const std::string& highKey) const
{
	std::vector<std::string> keysVector;

	findRange(lowKey, highKey, keysVector, m_root);

	return keysVector;
}

void AVLTree::findRange(const std::string& lowKey, const std::string& highKey,
						std::vector<std::string>& keysVector, const Node* root) const
{
	// Nullptr reached, stop recursion
	if (!root)
	{
		return;
	}

	// Check if key is in range, if so add to vector
	if (root->m_key >= lowKey && root->m_key <= highKey)
	{
		keysVector.push_back(root->m_key);
	}

	// Recursively calls function until reaches nullptr
	findRange(lowKey, highKey, keysVector, root->m_left);
	findRange(lowKey, highKey, keysVector, root->m_right);
}

[[nodiscard]] std::vector<std::string> AVLTree::keys() const
{
	std::vector<std::string> result;

	inorderTraversal(m_root, result);

	return result;
}

[[nodiscard]] size_t AVLTree::size() const
{
	return m_size;
}

[[nodiscard]] size_t AVLTree::getHeight() const
{
	return m_height;
}

int AVLTree::getHeight(Node* node)
{
	return node ? node->m_height : 0;
}


int& AVLTree::operator[](const std::string& key)
{
	Node* current = m_root;

	while (current)
	{
		if (current->m_key == key)
		{
			return current->m_data;
		}

		// Check value of key for direction
		if (key < current->m_key)
		{
			current = current->m_left;
		}
		else
		{
			current = current->m_right;
		}
	}
}

void AVLTree::operator=(const AVLTree& other)
{
}

void AVLTree::rebalance(Node* node)
{
	int balance = getBalance(node);
	if (node == nullptr)
	{
		return;
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

int AVLTree::getBalance(Node* node) const
{
	return node ? getHeight(node->m_left) - getHeight(node->m_right) : 0;
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

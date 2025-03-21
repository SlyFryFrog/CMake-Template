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
}

bool AVLTree::insert(const std::string& key, int value)
{
	// Skip traversing tree
	if (m_root == nullptr)
	{
		m_root = new Node(key, value);
	}

	Node* current = m_root;

	while (current != nullptr)
	{
	}

	// Base case where key is already present
	return false;
}

[[nodiscard]] bool AVLTree::remove(const std::string& key) const
{
	// Base case where key wasn't found in tree
	return false;
}

[[nodiscard]] bool AVLTree::contains(const std::string& key) const
{
	Node* current = m_root;

	while (current != nullptr)
	{
		if (current->m_key == key)
		{
			return true;
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

	// Base case where key wasn't found in tree
	return false;
}

[[nodiscard]] std::optional<int> AVLTree::get(const std::string& key) const
{
	Node* current = m_root;

	while (current != nullptr)
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

	// Base case where key wasn't found in tree
	return std::nullopt;
}

[[nodiscard]] std::vector<std::string> AVLTree::findRange(const std::string& lowKey,
														  const std::string& highKey) const
{
}

[[nodiscard]] std::vector<std::string> AVLTree::keys() const
{
}

[[nodiscard]] size_t AVLTree::size() const
{
	return m_size;
}

[[nodiscard]] size_t AVLTree::getHeight() const
{
	return m_height;
}

int& AVLTree::operator[](const std::string& key)
{
	Node* current = m_root;

	while (current != nullptr)
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

void AVLTree::rotate(Node* anchorNode)
{
	
}

void AVLTree::update_height()
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

int AVLTree::get_balance() const
{
	int leftBalance, rightBalance = -1;

	if (m_root->m_left)
	{
		leftBalance = m_root->m_left->m_height;
	}

	if (m_root->m_right)
	{
		rightBalance = m_root->m_right->m_height;
	}

	return leftBalance - rightBalance;
}

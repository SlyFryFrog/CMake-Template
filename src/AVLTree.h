#pragma once

#include <cstddef>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

class AVLTree
{
	struct Node
	{
		Node* m_left{};
		Node* m_right{};
		Node* m_parent{};
		int m_height{};
		int m_data;
		std::string m_key;

		Node(const std::string& key, int data) : m_data(data), m_key(key)
		{
		}

		~Node()
		{
			delete m_left;
			delete m_right;
		}
	};

	Node* m_root{};
	size_t m_size{};
	size_t m_height{};

public:
	/**
	 * @brief Initializes AVLTree with null root Node and height and size of 0.
	 */
	AVLTree();

	/**
	 * @brief Creates a copy of another AVLTree when constructing objects.
	 *
	 * @param other AVLTree being copied.
	 */
	AVLTree(const AVLTree& other);

	/**
	 * @brief Destroy the AVLTree object and free all memory.
	 */
	~AVLTree();

	bool insert(const std::string& key, int value);
	bool insert(const std::string& key, const int& value, Node*& root);

	[[nodiscard]] bool remove(const std::string& key) const;
	[[nodiscard]] bool contains(const std::string& key) const;
	[[nodiscard]] bool contains(const std::string& key, Node* root) const;

	[[nodiscard]] std::optional<int> get(const std::string& key) const;
	[[nodiscard]] std::vector<std::string> findRange(const std::string& lowKey,
													 const std::string& highKey) const;
	[[nodiscard]] std::vector<std::string> keys() const;

	/**
	 * @brief Returns the number of elements stored in the tree.
	 *
	 * @return size_t Number of Nodes in tree.
	 */
	[[nodiscard]] size_t size() const;

	/**
	 * @brief Get the height of the tree (root has height of 0).
	 *
	 * @return size_t Height of tree.
	 */
	[[nodiscard]] size_t getHeight() const;

	static int getHeight(Node* node);
	

	int& operator[](const std::string& key);
	void operator=(const AVLTree& other);

	friend std::ostream& operator<<(std::ostream& os, const AVLTree& avlTree)
	{
		return os;
	}

private:
	void rebalance(Node* node);
	void update_height();

	void rotate_right(Node* node);
	void rotate_left(Node* node);
	void inorderTraversal(Node* node, std::vector<std::string>& result) const;

	[[nodiscard]] int get_balance() const;
};

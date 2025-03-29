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

		/**
		 * @brief Creates a new instance of Node with a key-value pair.
		 *
		 * @param key Identifier for the Node.
		 * @param data Data associated with and stored at the key.
		 */
		Node(const std::string& key, int data) : m_data(data), m_key(key)
		{
		}

		/**
		 * @brief Recursively creates a deep copy of each Node from the starting point of the Node
		 * passed into the constructor.
		 *
		 * @param other Root of the Nodes being deep copied.
		 */
		Node(const Node& other) :
			m_data(other.m_data),
			m_key(other.m_key),
			m_height(other.m_height),
			m_parent(other.m_parent ? new Node(*other.m_parent) : nullptr),
			m_left(other.m_left ? new Node(*other.m_left) : nullptr),
			m_right(other.m_right ? new Node(*other.m_right) : nullptr)
		{
		}

		/**
		 * @brief Recursively called delete on all children (left and right).
		 */
		~Node()
		{
			delete m_left;
			delete m_right;
		}

		/**
		 * @brief Compares the keys of two Nodes.
		 *
		 * @param other Node being compared to.
		 * @return true Both keys are the same.
		 * @return false The keys are different.
		 */
		bool operator==(const Node*& other) const
		{
			return m_key == other->m_key;
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

	[[nodiscard]] bool remove(const std::string& key);
	bool remove(const std::string& key, Node* root);

	/**
	 * @brief Iterates through the tree until it finds the key or reaches a nullptr.
	 * Operates in log_2(n).
	 *
	 * @param key Key of the element being searched for.
	 * @return true Key was found.
	 * @return false Key was not found.
	 */
	[[nodiscard]] bool contains(const std::string& key) const;

	/**
	 * @brief Recursive method implementation of contains. Calls itself until it reaches a Node
	 * containing the key or nullptr.
	 * Operates in log_2(n)
	 *
	 * @param key Key being searched for.
	 * @param root Current Node being searched from.
	 * @return true root contains the key.
	 * @return false root doesn't contain the key and is nullptr.
	 */
	[[nodiscard]] bool contains(const std::string& key, const Node* root) const;

	/**
	 * @brief Returns the value of a key stored in the tree. If an invalid key is passed, an error
	 * may be thrown.
	 *
	 * @param key Identifier being compared against and searched for in the tree.
	 * @return std::optional<int> Value of the {key, value} pair.
	 */
	[[nodiscard]] std::optional<int> get(const std::string& key) const;

	[[nodiscard]] std::vector<int> findRange(const std::string& lowKey,
											 const std::string& highKey) const;
	static void findRange(const std::string& lowKey, const std::string& highKey,
						  std::vector<int>& rangeVector, const Node* root);

	/**
	 * @brief Iterates through the tree and adds all keys in-order.
	 *
	 * @return std::vector<std::string> Keys in the form of an in-order vector.
	 */
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
	[[nodiscard]] std::optional<int> get(const std::string& key, Node* const& root) const;
	static int& get_value(const std::string& key, Node* const& root);

	/**
	 * @brief Creates a deep copy of another tree and frees all currently allocated memory.
	 *
	 * @param other Tree being deep copied.
	 */
	void operator=(const AVLTree& other);

	/**
	 * @brief Prints the current layout of the tree.
	 *
	 * @param os Stream being printed to.
	 * @param tree Tree being printed.
	 * @return std::ostream& Modified ostream with the tree elements printed.
	 */
	friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree)
	{
		if (!tree.m_root)
		{
			os << "null";
		}
		else
		{
			// Append new line for clarity
			os << "\n";
			treePrint(os, tree.m_root);
		}

		return os;
	}

	const Node* getNode(const std::string& key)
	{
		return getNode(key, m_root);
	}

	const Node* getNode(const std::string& key, Node* const& root)
	{
		if (root->m_key == key)
		{
			return root;
		}

		if (root->m_key > key)
		{
			return getNode(key, root->m_left);
		}
		else
		{
			return getNode(key, root->m_right);
		}
	}

private:
	void rebalance(Node* node);
	void updateHeight();

	void rotateRight(Node* node);
	void rotateLeft(Node* node);
	void inorderTraversal(Node* node, std::vector<std::string>& result) const;

	/**
	 * @brief Parses through the tree from right to left. Returns std::ostream& with tree displayer
	 * from left (root) to right (leaf). Some visual difficulties may occur when printing larger
	 * datasets.
	 *
	 * @param os Stream being written to.
	 * @param root Base from which the function will traverse recursively.
	 * @param depth Current depth of the root.
	 */
	static void treePrint(std::ostream& os, Node* const& root, int depth = 0);

	static int getBalance(const Node* node);

	Node*& getSuccessor(Node*& root);

	/**
	 * @brief Creates a deep copy of a given tree and frees all currently allocated memory.
	 *
	 * @param other Tree being deep copied.
	 */
	void copy(const AVLTree& other);
};

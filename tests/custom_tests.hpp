#pragma once

#include <iostream>
#include <string>

#include "AVLTree.h"
#include "flora_test.hpp"

FLORA_TEST(Insertion, InsertionWithoutBalance)
{
	AVLTree tree;

	tree.insert("B", 'B');
	tree.insert("C", 'C');
	tree.insert("A", 'A');

	// Checks if insertions go to correct branch
	FLORA_ASSERT(tree.getNode("B")->m_left->m_key == "A" &&
				 tree.getNode("B")->m_right->m_key == "C");
}

FLORA_TEST(Removal, RemovalWithoutBalance)
{
	AVLTree tree;

	tree.insert("A", 'A');
	tree.insert("B", 'B');
	tree.remove("A");

	FLORA_ASSERT(!tree.contains("A") && tree.contains("B"));
}

FLORA_TEST(Removal, RemovalWithBalance)
{
	AVLTree tree;

    tree.insert("F", 'F');
    tree.insert("G", 'G');
	tree.insert("A", 'A');
	tree.insert("B", 'B');
	tree.insert("B", 'C');
	tree.remove("A");
}

FLORA_TEST(Contains, ContainsKey)
{
    AVLTree tree;

	tree.insert("A", 'A');
	tree.insert("B", 'B');
	tree.insert("B", 'C');
	FLORA_ASSERT(tree.contains("A") && tree.contains("B") && tree.contains("C"));

	tree.remove("A");
	
    FLORA_ASSERT(!tree.contains("A") && tree.contains("B") && tree.contains("C"), tree);
}
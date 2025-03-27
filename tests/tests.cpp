#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include "AVLTree.h"

using namespace std;

int main()
{
	AVLTree tree;
	bool insertResult;
	insertResult = tree.insert("F", 'F');
	insertResult = tree.remove("F");
	std::cout << insertResult;
	std::cout << tree;
	insertResult = tree.insert("F", 'F'); // false, no duplicates allowed
	std::cout << insertResult;
	insertResult = tree.insert("K", 'K');
	std::cout << insertResult;
	insertResult = tree.insert("X", 'X'); // single rotate left
	std::cout << insertResult;
	AVLTree tree_2;
	tree_2.remove("A");
	tree_2.insert("A", 2);
	tree_2.remove("B");
	std::cout << "\n" << tree_2 << "\n";

	tree_2 = tree;
	// tree_2.remove("F");

	insertResult = tree.insert("C", 'C');
	insertResult = tree.insert("A", 'A'); // single rotate right
	cout << endl << endl;
	cout << tree << endl;

	insertResult = tree.insert("D", 'D'); // double rotate right
	cout << endl << endl;
	cout << tree << endl;

	insertResult = tree.insert("R", 'R'); // double rotate left
	cout << endl << endl;
	cout << tree << endl;

	insertResult = tree.insert("V", 'V');
	insertResult = tree.insert("A", 'A'); // false, duplicate
	insertResult = tree.insert("Z", 'Z');
	insertResult = tree.insert("M", 'M');
	insertResult = tree.insert("D", 'D'); // false, duplicate
	cout << endl << endl;
	cout << tree << endl;

	// // size and getHeight
	cout << "tree size: " << tree.size() << endl;		 // 10
	cout << "tree height: " << tree.getHeight() << endl; // 3
	cout << endl;
	//
	//    // contains
	bool containsResult;
	containsResult = tree.contains("F"); // true
	std::cout << containsResult << "\n";
	containsResult = tree.contains("N"); // false
	std::cout << containsResult << "\n";
	for (const auto& val : tree.findRange("A", "F"))
	{
		std::cout << val << "\n";
	}

	int data = tree.get("F").value();
	std::cout << data;

	cout << tree_2 << endl;
	// cout << tree << endl;

	//
	//    // get
	//    optional<int> getResult;
	//
	//    getResult = tree.get("A"); // 65
	//    cout << "A: " << getResult.value() << endl;
	//
	//    getResult = tree.get("C"); // 67
	//    cout << "C: " << getResult.value() << endl;
	//
	//    getResult = tree.get("Q"); // getResult has no value
	//    cout << "Q: " << getResult.has_value() << endl; // print 0
	//    cout << endl;
	//
	//    // findRange
	//    vector<int> rangeTest = tree.findRange("D", "W");
	//    // 70 68 82 75 77 86
	//    for (auto val: rangeTest) {
	//        cout << val << " ";
	//    }
	//    cout << endl << endl;
	//
	//    // operator[]
	//    tree["A"] = 108;
	//    cout << tree << endl;
	//    cout << endl;
	//
	//    // remove
	//    bool removeResult;
	//    removeResult= tree.remove("A"); // "A" is a leaf
	//    cout << endl << endl;
	//    cout << tree << endl;
	//
	//    removeResult = tree.remove("C"); // "C" has one child, single rotate left
	//    cout << endl << endl;
	//    cout << tree << endl;
	//
	//    removeResult = tree.remove("F"); // "F" has two children
	//    cout << endl << endl;
	//    cout << tree << endl;
	//
	//    removeResult = tree.remove("V");
	//    removeResult = tree.remove("X");
	//    removeResult = tree.remove("Z"); // double rotate right
	//    cout << endl << endl;
	//    cout << tree << endl;

	return 0;
}

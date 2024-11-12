// main.cpp
#include <iostream>
#include <memory>
#include "TreeZipper.h"

using namespace std;

int main() {
    // Create the root node of the tree
    auto root = make_shared<TreeNode>(1);
    TreeZipper zipper(root);
    // Add children to the root
    zipper.addLeft(2);
    zipper.addRight(3);

    // Move to the left child and add a child to it
    zipper.goLeft();
    zipper.addLeft(4);

    // Move up to the root, then go right
    zipper.goUp();
    zipper.goRight();
    zipper.addRight(5);

    // Print values to verify the tree structure
    cout << "Root value: " << zipper.getValue() << endl;
    zipper.goLeft();
    cout << "Left child value: " << zipper.getValue() << endl;
    zipper.goRight();
    cout << "Left-Left child value: " << zipper.getValue() << endl;

    return 0;
}

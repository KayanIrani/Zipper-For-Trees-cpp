// TreeZipper.cpp
#include "TreeZipper.h"
#include <iostream>

using namespace std;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

Context::Context(shared_ptr<TreeNode> p, Direction d) : parent(p), dir(d) {}

TreeZipper::TreeZipper(shared_ptr<TreeNode> root) : focus(root) {}

bool TreeZipper::goLeft() {
    if (!focus->left)
    {
        cout<<"The Left Child is Empty"<<endl;
        return false;
    }
    context.push(Context(focus, LEFT));
    focus = focus->left;
    return true;
}

bool TreeZipper::goRight() {
    if (!focus->right)
    {
        cout<<"The Right Child is Empty"<<endl;
        return false;
    }
    context.push(Context(focus, RIGHT));
    focus = focus->right;
    return true;
}

bool TreeZipper::goUp() {
    if (context.empty())
    {
        cout<<"You're at the root node"<<endl;
        return false;
    }
    Context ctx = context.top();
    context.pop();
    focus = ctx.parent;
    return true;
}

void TreeZipper::update(int newValue) {
    focus->value = newValue;
}

int TreeZipper::getValue() const {
    return focus->value;
}

void TreeZipper::addLeft(int value) {
    if (!focus->left) {
        focus->left = make_shared<TreeNode>(value);
    } else {
        cout << "Left child already exists.\n";
    }
}

void TreeZipper::addRight(int value) {
    if (!focus->right) {
        focus->right = make_shared<TreeNode>(value);
    } else {
        cout << "Right child already exists.\n";
    }
}

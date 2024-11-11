// TreeZipper.h
#ifndef TREEZIPPER_H
#define TREEZIPPER_H

#include <memory>
#include <stack>

using namespace std;

struct TreeNode {
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    TreeNode(int val);
};

enum Direction { LEFT, RIGHT };

struct Context {
    shared_ptr<TreeNode> parent;
    Direction dir;
    Context(shared_ptr<TreeNode> p, Direction d);
};

class TreeZipper {
public:
    TreeZipper(shared_ptr<TreeNode> root);
    
    bool goLeft();
    bool goRight();
    bool goUp();
    
    void update(int newValue);
    int getValue() const;
    
    void addLeft(int value);
    void addRight(int value);

private:
    shared_ptr<TreeNode> focus;
    stack<Context> context;
};

#endif // TREEZIPPER_H

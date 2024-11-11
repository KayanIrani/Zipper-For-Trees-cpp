#include <iostream>
#include <memory>
#include <stack>

using namespace std;

struct TreeNode {
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

enum Direction { LEFT, RIGHT };

struct Context {
    shared_ptr<TreeNode> parent;
    Direction dir;
    Context(shared_ptr<TreeNode> p, Direction d) : parent(p), dir(d) {}
};

class TreeZipper {
public:
    TreeZipper(shared_ptr<TreeNode> root) : focus(root) {}

    bool goLeft() {
        if (!focus->left) return false;
        context.push(Context(focus, LEFT));
        focus = focus->left;
        return true;
    }

    bool goRight() {
        if (!focus->right) return false;
        context.push(Context(focus, RIGHT));
        focus = focus->right;
        return true;
    }

    bool goUp() {
        if (context.empty()) return false;
        Context ctx = context.top();
        context.pop();
        focus = ctx.parent;
        return true;
    }

    void update(int newValue) {
        focus->value = newValue;
    }

    int getValue() const {
        return focus->value;
    }

    void addLeft(int value) {
        if (!focus->left) {
            focus->left = make_shared<TreeNode>(value);
        } else {
            cout << "Left child already exists.\n";
        }
    }

    void addRight(int value) {
        if (!focus->right) {
            focus->right = make_shared<TreeNode>(value);
        } else {
            cout << "Right child already exists.\n";
        }
    }

private:
    shared_ptr<TreeNode> focus;
    stack<Context> context;
};

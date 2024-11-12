// DirectoryZipper.h
#ifndef MYDIRECTORY_H
#define MYDIRECTORY_H

#include <memory>
#include <stack>
#include <vector>

using namespace std;

struct DirectoryTree {
    string folderName;
    vector<shared_ptr<DirectoryTree>> subDirectories;
    DirectoryTree(string val);
};


struct Context {
    shared_ptr<DirectoryTree> parent;
    vector<string> path;
    Context(shared_ptr<DirectoryTree> p, vector<string> d);
};

class DirectoryZipper {
public:
    DirectoryZipper(shared_ptr<DirectoryTree> root);

    bool goToChild(string childName);
    bool goUp();

    void update(string newValue);
    string getValue() const;

    void addChild(string name);

    void recursiveDelete(shared_ptr<DirectoryTree> tempFocus);

    void removeRecursiveDirectory(string name);

//
//private:
    shared_ptr<DirectoryTree> focus;
    stack<Context> context;
    vector<string> fullPath;

};

#endif // MYDIRECTORY_H

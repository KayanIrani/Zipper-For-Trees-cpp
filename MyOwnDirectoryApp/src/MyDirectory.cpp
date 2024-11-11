// DirectoryZipper.cpp
#include "MyDirectory.h"
#include <iostream>

using namespace std;

DirectoryTree::DirectoryTree(string n) : folderName(n){}

Context::Context(shared_ptr<DirectoryTree> p, vector<string> d) : parent(p), path(d) {}

DirectoryZipper::DirectoryZipper(shared_ptr<DirectoryTree> root) : focus(root) {}
vector<string> fullPath;

bool DirectoryZipper::goToChild(string childName) {
    for (const auto& subDir:focus->subDirectories)
    {
        if (subDir->folderName == childName)
        {
            fullPath.push_back(focus->folderName);

            context.push(Context(focus, fullPath));
            focus = subDir;
            return true;
        } 
    }
    cout << "Child directory not found: " << childName << endl;
    return false;
}

bool DirectoryZipper::goUp() {
    if (context.empty())
    {
        cout<<"You're at the root directory"<<endl;
        return false;
    }
    Context ctx = context.top();
    context.pop();
    fullPath = ctx.path;
    focus = ctx.parent;
    return true;
}

void DirectoryZipper::update(string newValue) {
    focus->folderName = newValue;
}

string DirectoryZipper::getValue() const {
    return focus->folderName;
}

void DirectoryZipper::addChild(string value) {
    for (const auto& subDir:focus->subDirectories)
    {
        if (subDir->folderName == value)
        {
            cout<<"Folder Already Exists"<<endl;
            return;
        }
    }
    focus->subDirectories.push_back(make_shared<DirectoryTree>(value));

}

// DirectoryZipper.cpp
#include "MyDirectory.h"
#include <iostream>
#include <algorithm>
using namespace std;

DirectoryTree::DirectoryTree(string n) : folderName(n){}

Context::Context(shared_ptr<DirectoryTree> p, vector<string> d) : parent(p), path(d) {}

DirectoryZipper::DirectoryZipper(shared_ptr<DirectoryTree> root) : focus(root) {}

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

void DirectoryZipper::recursiveDelete(shared_ptr<DirectoryTree> tempFocus)
{
    // Recursively delete all subdirectories in tempFocus
    for (auto& subDir : tempFocus->subDirectories) {
        recursiveDelete(subDir);  // Recursively delete child directories
    }
    tempFocus->subDirectories.clear();  // Clear all subdirectories
}

void DirectoryZipper::removeRecursiveDirectory(string childName) {
    if (childName.empty())
    {
        char ip;
        if (focus->subDirectories.empty())
        {
            cout<<"Are you sure you wish to delete " << focus->folderName<<endl;
            cout<<"Press Y[y] to delete" <<endl;
            cin>>ip;   
            if (ip == 'Y' || ip == 'y')
            {
                cout<<"Deleting "<<focus->folderName<< endl;
                if (!context.empty())
                {
                    Context ctx = context.top();
                    context.pop();
                    focus = ctx.parent;
                    fullPath = ctx.path;
                }
            }
            else
            {
                cout<<"Delete Action Stopped ..." <<endl;
            }
        }
        else
        {
            cout<<focus->folderName<<" contains other folders as well\nAre you sure you wish to delete all folders inside it recursively " << endl;
            cout<<"Press Y[y] to delete" <<endl;
            cin>>ip;
            if (ip == 'Y' || ip == 'y')
            {
                cout<<"Deleting all folders under "<< focus->folderName<<endl;
                if (!context.empty())
                {
                    Context ctx = context.top();
                    context.pop();
                    recursiveDelete(focus);
                    auto it = remove_if(
                        ctx.parent->subDirectories.begin(),
                        ctx.parent->subDirectories.end(),
                        [this](const shared_ptr<DirectoryTree>& dir) 
                        { 
                            return dir == focus; 
                        }
                    );
                    ctx.parent->subDirectories.erase(it, ctx.parent->subDirectories.end()); 
                    focus = ctx.parent;
                    fullPath = ctx.path;
                }
            }
            else
            {
                cout<<"Delete Action Stopped ..." <<endl;
            }   
        }
    }
    else{
        auto it = find_if(
            focus->subDirectories.begin(),
            focus->subDirectories.end(),
            [&childName](const shared_ptr<DirectoryTree>& dir)
            { 
                return dir->folderName == childName; 
            }
        );

        if (it != focus->subDirectories.end()) 
        {
            recursiveDelete(*it); 
            focus->subDirectories.erase(it); 
            cout << "Deleted directory: " << childName << endl;
        }
        else
        {
            cout<<"Directory "<<childName<<" doesn't exist"<<endl;
        }
}
}

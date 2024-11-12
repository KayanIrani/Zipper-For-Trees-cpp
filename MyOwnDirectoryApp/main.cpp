#include <algorithm>
#include <memory>
#include "MyDirectory.h"
#include <iostream>
#include <sstream>
using namespace std;
class DirectoryFunctions{
public:
    DirectoryZipper ZipDirector; // Member variable

    DirectoryFunctions() : ZipDirector(make_shared<DirectoryTree>("Home")) {}

    pair<string, string> parseCommand(const string& prompt)
    {
        istringstream iss(prompt);
        string command, argument;
        iss >> command;
        getline(iss, argument);
        argument.erase(0, argument.find_first_not_of(" "));  // Trim leading spaces
        return {command, argument};
    }

    void cd(const string& directory)
    {
        if (directory == "..")
        {
            if (ZipDirector.goUp())
            {
                cout<< "Moved to Previous Directory";
            }
        }
        else if (ZipDirector.goToChild(directory))
        {
            cout << "Moved to directory: " << ZipDirector.getValue() << endl;
        }
        else
        {
            cout << "Directory '" << directory << "' not found." << endl;
        }
    }

void mkdir(const string& directory) {
    if (!directory.empty()) {
        ZipDirector.addChild(directory);
        cout << "Directory '" << directory << "' created." << endl;
    } else {
        cout << "Error: No directory name provided for mkdir." << endl;
    }
}

void rmdir(const string& directory) {
    if (!directory.empty()) {
        ZipDirector.removeRecursiveDirectory(directory);
        cout << "Directory '" << directory << "' removed." << endl;
    } else {
        cout << "Error: No directory name provided for rmdir." << endl;
    }
}

void ls() {
    cout << "Listing directories under " << ZipDirector.getValue() << ":" << endl;
    for (const auto& subDir : ZipDirector.focus->subDirectories) {
        cout << subDir->folderName << " ";
    }
    cout << endl;
}

void dir() {
    cout << "Current directory: " << ZipDirector.getValue() << endl;
    string path;
    for (auto i: ZipDirector.fullPath)
    {
        path += (i + '/');
    }
    if (ZipDirector.focus->folderName != "Home")
    {
        path += ZipDirector.focus->folderName;
        cout<< "Entire Path is : "<< path<<endl;
    }
}


void understandPrompt(const string& prompt) {
    if (prompt.empty()) {
        cout << "Empty command." << endl;
        return;
    }

    auto [command, argument] = parseCommand(prompt);

    if (command == "cd") {
        cd(argument);
    } else if (command == "mkdir") {
        mkdir(argument);
    } else if (command == "rmdir") {
        rmdir(argument);
    } else if (command == "ls") {
        ls();
    } else if (command == "dir") {
        dir();
    } else {
        cout << "Command not recognized: " << command << endl;
    }
}

};

int main() {

    DirectoryFunctions D = DirectoryFunctions();
    cout<<"Welcome To Our directory Navigation using Zippers on Trees"<<endl;
    D.ZipDirector.addChild("dev");
    D.ZipDirector.addChild("user");
    D.ZipDirector.addChild("wow");
    string prompt;
    while(true)
    {
        cout <<endl<< "> ";
        getline(cin, prompt);
        if (prompt == "exit")
        {
            break;
        }
        D.understandPrompt(prompt);

    }

    return 0;
}

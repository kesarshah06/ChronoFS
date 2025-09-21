#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>
#include "helper.h"
#include "filesystem.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Filesystem fs;
    File* current_open_file = nullptr;
    cout << "   Welcome to the Time Traveling File System\n";
    cout << "   List of valid commands is given below\n";
    helper();

    while (true) {
        string line;
        getline(cin, line);  
        stringstream ss(line);
        string op;
        ss >> op;

        transform(op.begin(), op.end(), op.begin(), ::toupper);

        if (op == "CREATE") {
            string name; if (!(ss >> name)) { 
                cout << "ERROR : No filename given.\n"; 
                continue; 
            }
            fs.create(name);
        }

        else if (op == "OPEN") {
            string name; if (!(ss >> name)) { cout << "ERROR : No filename given.\n"; continue; }
            File* f = fs.file_sys.getFile(name);
            if (!f) { cout << "ERROR : File with given name doesn't exist\n"; continue; }
            current_open_file = f;
            cout << "File " << name << " is now open.\n";
        }

        else if (op == "CLOSE") {
            if (!current_open_file) cout << "ERROR : No file is currently open.\n";
            else { 
                cout << "File " << current_open_file->file_name << " is now closed.\n"; 
                current_open_file = nullptr; 
            }
        }

        else if (op == "READ") {
            string name;
            if (current_open_file) {
                name = current_open_file->file_name;
            } else {
                if (!(ss >> name)) {
                    cout << "ERROR : No filename given.\n";
                    continue;
                }
            }
            fs.read(name);
        }

        else if (op == "INSERT" || op == "UPDATE" || op == "SNAPSHOT") {
            string name;
            if (current_open_file) {
                name = current_open_file->file_name;
            } else {
                if (!(ss >> name)) {
                    cout << "ERROR : No filename given.\n";
                    continue;
                }
            }
            File* f = fs.file_sys.getFile(name);
            if (!f) {
                cout << "ERROR : File with given name doesn't exist\n";
                continue; 
            }
            string content; 
            getline(ss, content);
            content.erase(0, content.find_first_not_of(" \t\n\r\f\v"));
            content.erase(content.find_last_not_of(" \t\n\r\f\v") + 1);

            if (content.empty()) { 
                cout << "ERROR : Empty string detected, type 'YES' to continue or input new content:\n"; 
                getline(cin, content); 
                if(content=="YES") content = ""; 
            }

            if (op == "INSERT") fs.insert(name, content);
            if (op == "UPDATE") fs.update(name, content);
            if (op == "SNAPSHOT") fs.snapshot(name, content);
        }

        else if(op == "RENAME"){
            string name;
            if (current_open_file) {
                name = current_open_file->file_name;
            } else {
                if (!(ss >> name)) {
                    cout << "ERROR : No filename given.\n";
                    continue;
                }
            }
            File* f = fs.file_sys.getFile(name);
            if (!f) {
                cout << "ERROR : File with given name doesn't exist\n";
                continue; 
            }
            string name2;
            ss >> name2; 
            if (name2.empty()) { 
                cout << "ERROR : File name can't be empty\n"; 
            }
            else fs.rename(name, name2);

        }

        else if (op == "ROLLBACK") {
            string name;
            if (current_open_file) {
                name = current_open_file->file_name;
            } else {
                if (!(ss >> name)) {
                    cout << "ERROR : No filename given.\n";
                    continue;
                }
            }
            File* f = fs.file_sys.getFile(name);
            if (!f) {
                cout << "ERROR : File with given name doesn't exist\n";
                continue;  
            }
            string id;
            getline(ss, id);  
            id.erase(0, id.find_first_not_of(" \t\n\r\f\v")); 
            id.erase(id.find_last_not_of(" \t\n\r\f\v") + 1); 

            if (id.empty()) {
                fs.rollback(name);
            } else {
                if (all_of(id.begin(), id.end(), ::isdigit)) {
                    fs.rollback(name, stoi(id));
                } else {
                    cout << "ERROR : INVALID INDEX TO ROLLBACK TO\n";
                }
            }
        }

        else if (op == "HISTORY" || op == "PRINT") {
            string name;
            if (current_open_file) {
                name = current_open_file->file_name;
            } else {
                if (!(ss >> name)) {
                    cout << "ERROR : No filename given.\n";
                    continue;
                }
            }
            File* f = fs.file_sys.getFile(name);
            if (!f) {
                cout << "ERROR : File with given name doesn't exist\n";
                continue;  
            }
            if(op=="HISTORY") fs.history(name);
            else fs.printFile(name);
        }

        else if (op == "RECENT_FILES"){
            string id;
            getline(ss, id);  
            id.erase(0, id.find_first_not_of(" \t\n\r\f\v")); 
            id.erase(id.find_last_not_of(" \t\n\r\f\v") + 1); 

            if (id.empty()) {
                fs.recent_files(-1);
            } else {
                if (all_of(id.begin(), id.end(), ::isdigit)) {
                    fs.recent_files(stoi(id));
                } else {
                    cout << "ERROR : INVALID NUMBER OF FILES TO PRINT\n";
                }
            }
        }
        else if (op == "BIGGEST_TREES"){
            string id;
            getline(ss, id);  
            id.erase(0, id.find_first_not_of(" \t\n\r\f\v")); 
            id.erase(id.find_last_not_of(" \t\n\r\f\v") + 1); 

            if (id.empty()) {
                fs.biggest_trees(-1);
            } else {
                if (all_of(id.begin(), id.end(), ::isdigit)) {
                    fs.biggest_trees(stoi(id));
                } else {
                    cout << "ERROR : INVALID NUMBER OF FILES TO PRINT\n";
                }
            }
        }
        else if(op == "LS") fs.ls();
        else if(op == "DELETE"){
            string name;
            if (current_open_file) {
                name = current_open_file->file_name;
                fs.deleteF(name);
                cout << "Current open file is deleted and closed.\n";
                current_open_file = nullptr;

            } else {
                if (!(ss >> name)) {
                    cout << "ERROR : No filename given.\n";
                    continue;
                }
                fs.deleteF(name);
            }
        }
        else if(op == "HELP") helper();
        else if (op == "EXIT") break;
        else { 
            cout << "\nINVALID COMMAND\n"; 
            helper(); 
        }
    }
}

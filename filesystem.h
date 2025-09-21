#pragma once
#include "filemap.h"
#include "heaps.h"
#include "helper.h"

using namespace std;


class Filesystem{
public:
    FileMap file_sys;
    RecentHeap rh;
    BiggestTree bt;

    void create(string name){
        if(file_sys.getFile(name)){
            cout << "ERROR : The File System already contains this file" << "\n";
            return;
        }
        File* f = new File(name);
        file_sys.push(f);
        rh.push(f);
        bt.push(f);
        cout << "File with name " << name << " is created" << "\n";
    }

    void insert(string name, string con){
        File* curr = file_sys.getFile(name);
        if(!curr){ cout << "ERROR : File with given name doesn't exist" << "\n"; return; } 
        Version* av = curr->active_version;
        if(av->snapshot_timestamp != 0){
            Version* nv = new Version(curr->total_versions, av->content + " " + con);
            curr->version_map.push(curr->total_versions, nv);
            av->children.push_back(nv);
            nv->parent = av;
            curr->active_version = nv;
            curr->total_versions++;
            cout << "The current active version is snapshotted and the content is inserted to the new version" << "\n";
        } else {
            av->content += " " + con;
            cout << "The content is inserted to the active version" << "\n";
        }
        curr->last_mod = time(nullptr);
        rh.resort(curr);
        bt.resort(curr);
    }

    void read(string name){
        File* curr = file_sys.getFile(name);
        if(!curr){ 
            cout << "ERROR : File with given name doesn't exist" << "\n"; 
            return; 
        } 
        cout << "Content of active version: " << curr->active_version->content << "\n";
    }

    void update(string name, string con){
        File* curr = file_sys.getFile(name);
        Version* av = curr->active_version;
        if(av->snapshot_timestamp != 0){
            Version* nv = new Version(curr->total_versions, con);
            curr->version_map.push(curr->total_versions, nv);
            av->children.push_back(nv);
            nv->parent = av;
            curr->active_version = nv;
            curr->total_versions++;
            cout << "The current active version is snapshotted and the content is updated to the new version" << "\n";
        } else {
            av->content = con;
            cout << "Content of active version is updated" << "\n";
        }
        curr->last_mod = time(nullptr);
        rh.resort(curr);
        bt.resort(curr);
    }

    void snapshot(string name, string msg){
        File* curr = file_sys.getFile(name);
        Version* av = curr->active_version;
        if(av->snapshot_timestamp != 0){
            cout << "ERROR : Current active version is already snapshotted" << "\n";
            return;
        }
        av->snapshot_timestamp = time(nullptr);
        av->message = msg;
        curr->last_mod = time(nullptr);
        rh.resort(curr);
        bt.resort(curr);
        cout << "The current active version is snapshotted" << "\n";
    }

    void rollback(string name, int id = -1){
        File* curr = file_sys.getFile(name); 
        if(id == -1){
            if(curr->active_version->parent){
                curr->active_version = curr->active_version->parent;
                curr->last_mod = time(nullptr);
                rh.resort(curr);
                bt.resort(curr);
                cout << "Rolled back to parent version\n";
            } else cout << "ERROR : Active version has no parent\n";
        } else {
            Version* new_av = curr->version_map.getVer(id);
            if(new_av) {
                curr->active_version = new_av;
                curr->last_mod = time(nullptr);
                rh.resort(curr);
                bt.resort(curr);
                cout << "Rolled back to version ID: " << id << "\n";
            } else cout << "ERROR : Version with given id doesn't exist\n";
        }
    }

    void history(string name){
        File* curr = file_sys.getFile(name); 
        Version* v = curr->active_version;
        vector<Version*> temp;
        while(v){
            temp.push_back(v);
            v = v->parent;
        }
        for(int i = temp.size() - 1; i >= 0; i--){
            if(temp[i]->snapshot_timestamp != 0){
                cout << "ID :" << temp[i]->version_id 
                    << " TIME :" << Time(temp[i]->snapshot_timestamp) 
                    << " MESSAGE :" << temp[i]->message << "\n";
            } else {
                cout << "Version ID : " << temp[i]->version_id 
                    << " is not snapshotted.\n";
            }
        }
    }


    void recent_files(int n){
        vector<File*> files = rh.heap;  
        sort(files.begin(), files.end(), [](File* a, File* b){ return a->last_mod > b->last_mod; });
        if(n == -1){
            n = files.size();
        }
        else if(n > files.size()){
            cout << "ERROR : THERE ARE ONLY " << files.size() << " FILES IN THE FILE SYSTEM...\n";
            n = files.size();
        }
        cout << "THE LATEST " << n << " MODIFIED FILES: \n";
        for(int i=0; i<n ; i++){
            cout << "NAME : " << files[i]->file_name << " LAST MODIFIED : " << Time(files[i]->last_mod) << "\n";
        }
    }

    void biggest_trees(int n){
        vector<File*> files = bt.heap;  
        sort(files.begin(), files.end(), [](File* a, File* b){ return a->total_versions > b->total_versions; });
        if(n == -1){
            n = files.size();
        }
        else if(n > files.size()){
            cout << "ERROR : THERE ARE ONLY " << files.size() << " FILES IN THE FILE SYSTEM...\n";
            n = files.size();
        }
        cout << "THE TOP " << n << " FILES BY SIZE: \n";
        for(int i=0; i<n ; i++){
            cout << "NAME : " << files[i]->file_name << " TOTAL VERSIONS : " << files[i]->total_versions << "\n";
        }
    }

    void printVersion(Version* v, int depth = 0) {
        for (int i = 0; i < depth; i++) cout << "    ";
        cout << "ID: " << v->version_id << " || Content: " << v->content;
        if (v->snapshot_timestamp) cout << " || Message: " << v->message;
        cout << "\n";
        for (auto child : v->children) printVersion(child, depth + 1);
    }

    void printFile(string name){
        File* curr = file_sys.getFile(name);
        if(!curr){ cout << "ERROR : File with given name doesn't exist" << "\n"; return; } 
        printVersion(curr->root, 0);
    }

    void rename(string name, string name2){

        if (file_sys.getFile(name2)) {
            cout << "ERROR : Target filename already exists\n";
            return;
        }

        file_sys.changeKey(name, name2); 
        File* curr = file_sys.getFile(name2); 
        rh.resort(curr);
        cout << "File renamed from " << name << " to " << name2 << "\n";

        
    }

    void ls() {
        vector<File*> files = file_sys.getAllFiles();
        if (files.empty()) {
            cout << "ERROR : No files found in filesystem.\n";
            return;
        }
        cout << "Files in filesystem:\n";
        for (auto f : files) {
            cout << " - " << f->file_name << "\n";
        }
    }

    void deleteF(string name) {
        File* curr = file_sys.getFile(name);
        if (!curr) {
            cout << "ERROR : File with given name doesn't exist\n";
            return;
        }

        rh.removeFromHeap(curr);
        bt.removeFromHeap(curr);

        file_sys.removeF(name);
        delete curr;
        cout << "File " << name << " deleted from filesystem\n";
    }

};
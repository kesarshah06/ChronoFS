#pragma once
#include "hashmap.h"

using namespace std;

class FileMap {
    HashMap map;
public:
    void push(File* f){ 
        map.insert(f->file_name, f); 
    }

    File* getFile(string key){
        return map.get(key); 
    }

    void changeKey(const string &name, const string &name2){ 
        map.change_key(name, name2); 
    }

    vector<File*> getAllFiles() { 
        return map.getAllF();  
    }

    bool removeF(string key){ 
        return map.removek(key); 
    }
};
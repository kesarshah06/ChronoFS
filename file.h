#pragma once
#include "version.h"

using namespace std;


class File {
public:
    string file_name;
    time_t last_mod;
    int total_versions;
    Version* root;
    Version* active_version;
    VersionMap version_map;
    File(string name) {
        file_name = name;
        root = new Version(0, "");
        active_version = root;
        total_versions = 1;
        version_map.push(0, root);
        root->message = "0th index Root File";
        root->snapshot_timestamp = time(nullptr);
        last_mod = time(nullptr);
    }
    ~File() { delete root; }   
    void change_name(string name){
        file_name = name;
        last_mod = time(nullptr);
    }
};
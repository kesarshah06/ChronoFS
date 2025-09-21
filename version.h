#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>
using namespace std;

struct Version {
    int version_id;
    string content;
    string message;
    time_t created_timestamp;
    time_t snapshot_timestamp;
    Version* parent; //parent of the given version
    vector<Version*> children; //vector for all the children of a given versions
    Version(int id, string con) { //constructor
        version_id = id;
        content = con;
        parent = nullptr;
        snapshot_timestamp = 0;
        created_timestamp = time(nullptr);
    }
    ~Version() { //destructor
        for (auto child : children) delete child;
    }
};

class VersionMap {
    vector<Version*> map;
public:
    void push(int key, Version* val) {
        if (key >= (int)map.size()) map.resize(key + 1, nullptr); //if the vector is already full we resize it to store new version at given key
        map[key] = val; //otherwise there is an open slot at the index = key and we assign it to map
    }
    Version* getVer(int key) {
        if (key < 0 || key >= (int)map.size()) return nullptr; //if no key exists in the map return nullptr
        return map[key];
    }
};
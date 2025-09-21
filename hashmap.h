#pragma once
#include "file.h"

using namespace std;

struct Node {
    string key;
    File* file;
    Node* next;
    Node(string k, File* f) : key(k), file(f), next(nullptr) {}
};

class HashMap {
private:
    Node** bkt;
    int capacity;
    int size;

    long long hashF(string key) {   
        long long hashValue = 0;
        for (char ch : key) hashValue = (hashValue * 37) + ch;
        return hashValue;
    }

public:

    HashMap(int cap = 100) : capacity(cap), size(0){
        bkt = new Node*[capacity]();
    }

    ~HashMap(){

        for (int i = 0; i < capacity; ++i) {
            Node* curr = bkt[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }

        delete[] bkt;

    }

    void insert(string key, File* value){

        int ind = hashF(key) % capacity;
        Node* curr = bkt[ind];

        while (curr) {
            if (curr->key == key){ 
                curr->file = value; 
                return; 
            }
            curr = curr->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = bkt[ind];
        bkt[ind] = newNode;
        size++;
    }

    File* get(string key){

        int ind = hashF(key) % capacity;
        Node* current = bkt[ind];
        while (current) {
            if (current->key == key) return current->file;
            current = current->next;
        }
        return nullptr;
    }

    void change_key(string name1, string name2){

        int idx = hashF(name1) % capacity;
        Node* prev = nullptr;
        Node* curr = bkt[idx];

        while (curr && curr->key != name1){ 
            prev = curr; 
            curr = curr->next; 
        }

        if (!curr) return;

        if (prev) prev->next = curr->next;
        else bkt[idx] = curr->next;

        if (curr->file) curr->file->change_name(name2);
        curr->key = name2;
        int newI = hashF(name2) % capacity;
        curr->next = bkt[newI];
        bkt[newI] = curr;
    }

    vector<File*> getAllF(){

        vector<File*> result;
        for (int i = 0; i < capacity; ++i) {
            Node* curr = bkt[i];
            while (curr){ 
                result.push_back(curr->file); 
                curr = curr->next; 
            }
        }
        return result;
    }

    bool removek(string key){

        int ind = hashF(key) % capacity;
        Node* curr = bkt[ind]; Node* prev = nullptr;
        while (curr) {
            if (curr->key == key) {
                if (prev) prev->next = curr->next;
                else bkt[ind] = curr->next;
                delete curr; 
                size--; 
                return true; 
            }
            prev = curr; curr = curr->next;
        }
        return false; 
    }
};

class IndexMap {

    struct NodeI{
        string key;
        int value;
        NodeI* next;
        NodeI(string k, int v): key(k), value(v), next(nullptr) {}
    };

    NodeI** bkt;
    int capacity;

public:
    IndexMap(int cap=200): capacity(cap) {
        bkt = new NodeI*[capacity]();
    }

    ~IndexMap(){
        for(int i=0;i<capacity;i++){
            NodeI* c=bkt[i];
            while(c){NodeI* t=c;c=c->next;delete t;}
        }
        delete[] bkt;
    }

    long long hashF(const string& key){
        long long h=0; 
        for(char c: key) h = h * 37 + c;
        return h % capacity;
    }

    void put(const string& k,int v){

        int idx=hashF(k);
        NodeI* c=bkt[idx];
        while(c){ 
            if(c->key==k){
                c->value=v;
                return;
            } 
            c=c->next; 
        }
        NodeI* n=new NodeI(k,v);
        n->next=bkt[idx]; bkt[idx]=n;

    }
    bool get(const string& k,int &v){
        int ind = hashF(k);
        NodeI* c = bkt[ind];
        while(c){ 
            if(c->key == k){
                v = c->value;
                return true;
            } 
            c = c->next; 
        }
        return false;
    }
    void erase(const string& k){
        int idx=hashF(k);
        NodeI* c = bkt[idx], *p = nullptr;
        while(c){
            if(c->key==k){ 
                if(p) p->next = c->next; 
                else bkt[idx] = c->next; 
                delete c; 
                return; 
            }
            p = c;
            c = c->next;
        }
    }
};
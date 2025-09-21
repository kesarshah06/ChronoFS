#pragma once
#include "hashmap.h"

using namespace std;

class RecentHeap{
public:
    vector<File*> heap;
    IndexMap index;
    RecentHeap(): index(200) {}
    void swapNodes(int i,int j){ //to change the indices of files when we heapify it so that they are resorted
        swap(heap[i],heap[j]);
        index.put(heap[i]->file_name,i);
        index.put(heap[j]->file_name,j);
    }
    void heapifyUp(int i){ 
        while(i>0){
            int p=(i-1)/2;
            if(heap[i]->last_mod > heap[p]->last_mod){ 
                swapNodes(i,p); 
                i=p; 
            }
            else break;
        }
    }
    void heapifyDown(int i){
        int n=heap.size();
        while(true){
            int p=i; int l=2*i+1, r=2*i+2;
            if(l<n && heap[l]->last_mod > heap[p]->last_mod) p=l;
            if(r<n && heap[r]->last_mod > heap[p]->last_mod) p=r;
            if(p!=i){swapNodes(i,p); i=p;} else break;
        }
    }
    void resort(File* f){ //after a certain operation resorting the heap
        int i; 
        if(!index.get(f->file_name,i)) return;
        heapifyUp(i); heapifyDown(i);
    }
    void push(File* f){ //pushing a file in heap
        heap.push_back(f);
        int i=heap.size()-1;
        index.put(f->file_name,i);
        heapifyUp(i);
    }
    void pop(){ //popping a file from heap
        if(!heap.size()) return;
        index.erase(heap[0]->file_name);
        if(heap.size()==1){heap.pop_back();return;}
        heap[0]=heap.back();
        index.put(heap[0]->file_name,0);
        heap.pop_back();
        heapifyDown(0);
    }
    void removeFromHeap(File* f) { //removing a file from heap for delete
        int n = heap.size();
        for (int i = 0; i < n; i++) {
            if (heap[i] == f) {
                heap[i] = heap.back();
                heap.pop_back();
                if (i < heap.size()) {
                    heapifyDown(i);
                    heapifyUp(i);
                }
                break;
            }
        }
    }

};

class BiggestTree{
public:
    vector<File*> heap;
    IndexMap index;
    BiggestTree(): index(200) {}
    void swapNodes(int i,int j){
        swap(heap[i],heap[j]);
        index.put(heap[i]->file_name,i);
        index.put(heap[j]->file_name,j);
    }
    void heapifyUp(int i){
        while(i>0){
            int p=(i-1)/2;
            if(heap[i]->total_versions > heap[p]->total_versions){ swapNodes(i,p); i=p; }
            else break;
        }
    }
    void heapifyDown(int i){
        int n=heap.size();
        while(true){
            int p=i; int l=2*i+1, r=2*i+2;
            if(l<n && heap[l]->total_versions > heap[p]->total_versions) p=l;
            if(r<n && heap[r]->total_versions > heap[p]->total_versions) p=r;
            if(p!=i){swapNodes(i,p); i=p;} else break;
        }
    }
    void resort(File* f){
        int i; if(!index.get(f->file_name,i)) return;
        heapifyUp(i); heapifyDown(i);
    }
    void push(File* f){
        heap.push_back(f);
        int i=heap.size()-1;
        index.put(f->file_name,i);
        heapifyUp(i);
    }
    void pop(){
        if(!heap.size()) return;
        index.erase(heap[0]->file_name);
        if(heap.size()==1){heap.pop_back();return;}
        heap[0]=heap.back();
        index.put(heap[0]->file_name,0);
        heap.pop_back();
        heapifyDown(0);
    }
    void removeFromHeap(File* f) {
        int n = heap.size();
        for (int i = 0; i < n; i++) {
            if (heap[i] == f) {
                heap[i] = heap.back();
                heap.pop_back();
                if (i < heap.size()) {
                    heapifyDown(i);
                    heapifyUp(i);
                }
                break;
            }
        }
    }

};
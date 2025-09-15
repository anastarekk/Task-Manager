



#ifndef HEAP_H
#define HEAP_H
#include"BST.h"
#include<iostream>
using namespace std;
template <class T>
class Heap {
private:
    T* arr;
    int capacity;
    int size;
    int parent(int i) {
        return((i-1)/2);
    }
    int left(int i) {
        return 2*i + 1;
    }
    int right(int i) {
        return 2*i + 2;
    }
    void heapifyUp(int i) {
        while (i>0 && arr[i]<arr[parent(i)]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }
    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);
        if (l < size && arr[l] < arr[smallest] ) {
            smallest = l;
        }
        if (r < size && arr[r] < arr[smallest] ) {
            smallest = r;
        }
        if (smallest != i) {
            swap(arr[i],arr[smallest]);
            heapifyDown(smallest);
        }
    }
public:
    Heap(int n) {
        capacity = n;
        size = 0;
        arr = new T[capacity];
    }
    ~Heap() {
        delete[] arr;
    }
    void insert(T val) {

        arr[size++] = val;
        heapifyUp(size-1);
    }
    void sort() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }

        for (int i = size - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            int tempSize = size;
            size = i;
            heapifyDown(0);
            size = tempSize;
        }
    }

    void displaySortedAscending() {
        int n = size-1;
        for (int i = n; i>=0;i--) {
            cout<<arr[i]<<endl;
        }
    }
    bool empty() {
        return size == 0;
    }
    void displayReport() {
        const int max = 50;
        string categories[max];
        int count = 0;
        int counts[max] = {0};
        for (int i = 0; i<size;i++) {
            string temp = arr[i].getCategory();
            bool found = false;
            for (int j = 0; j < count;j++) {
                if (categories[j] == temp) {
                    counts[j]++;
                    found = true;
                    break;
                }
            }
            if (!found && count < max) {
                categories[count] = temp;
                counts[count] = 1;
                count++;
            }
        }
        for (int i = 0; i<count;i++) {
            cout << categories[i] << " = " << counts[i] << endl;
        }
        }
};
#endif //HEAP_H

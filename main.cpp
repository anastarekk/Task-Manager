
#include<iostream>
#include"BST.h"
#include "Heap.h"
#include<fstream>
using namespace std;


int main() {
    const int max = 100;
    BST<Task> tasks;
    ifstream file("input.txt");
    if (!file) {
        cout<<"cannot open file!"<<endl;
    }
    else {
        int size;
        file>>size;
        file.ignore();
        Task arr[size];
        for (int i = 0;i<size;i++) {
            string desc;
            int dur;
            string cat;
            getline(file, desc);
            file >> dur;
            file.ignore(); 
            getline(file, cat);
            arr[i].setDesc(desc);
            arr[i].setDuration(dur);
            arr[i].setCategory(cat);

        }
        for (int i = 0;i<size;i++) {
            tasks.insert(arr[i]);
        }
    }



    Heap<Task> completed(max);


while (true) {
    cout<<"1. Insert a task "<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"2. Display all" <<endl;
    cout<<"-------------------------"<<endl;
    cout<<"3. Search for a task"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"4. Remove a task"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"5. Display more than"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"6. Display less than"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"7. Mark a task as completed by task duration and description"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"8. Display all completed tasks and the number of tasks completed per category"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"9.Exit"<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"Enter number of option:"<<endl;
    int choice;
    cin>>choice;
    cin.ignore();

    switch (choice) {
        case 1: {
            Task obj;
            cout<<"Enter tasks description:"<<endl;
            string desc;
            getline(cin,desc);
            obj.setDesc(desc);
            cout<<"Enter duration:"<<endl;
            int dur;
            cin>>dur;
            cin.ignore();
            obj.setDuration(dur);
            cout<<"Enter Category:"<<endl;
            string cat;
            getline(cin,cat);
            obj.setCategory(cat);
            tasks.insert(obj);
            cout<<"Task inserted!"<<endl;
            break;
        }
        case 2: {
            tasks.inOrder();
            break;
        }
        case 3:{
            cout<<"Enter the duration:"<<endl;
            int temp;
            cin>>temp;
            cin.ignore();
            tasks.search(temp);
            break;
        }
        case 4: {
            cout<<"Enter the duration:"<<endl;
            int temp2;
            cin>>temp2;
            cin.ignore();
            tasks.Delete(temp2);
            break;
        }
        case 5: {
            cout<<"Enter the duration more than:"<<endl;
            int temp3;
            cin>>temp3;
            cin.ignore();
            tasks.displayMore(temp3);
            break;
        }
        case 6: {
            cout<<"Enter the duration less than:"<<endl;
            int temp4;
            cin>>temp4;
            cin.ignore();
            tasks.displayLess(temp4);
            break;
        }
         case 7: {
            cout<<"Task duration:"<<endl;
            int temp;
            cin>>temp;
            cin.ignore();
            cout<<"Task description:"<<endl;
            string desc;
            getline(cin,desc);
            Task deleted;
            if (tasks.DeleteByDesc(temp,desc,deleted)) {
                cout<<deleted<<endl;
                completed.insert(deleted);
                cout<<"This task is removed!"<<endl;

            }
            else {
                cout<<"No matching tasks found!"<<endl;
            }
            break;
        }
        case 8: {
            completed.sort();
            completed.displaySortedAscending();
            completed.displayReport();
            break;
        }
        case 9: {
            return false;
        }
        default: {
            cout<<"Please Enter A Valid Choice"<<endl;
        }


    }
}


     return 0;
}


#ifndef BST_H
#define BST_H
#include<iostream>
#include<string>
using namespace std;

class Task{
private:
    string desc;
    int duration;
    string category;
public:
    Task() {
        desc = "";
        duration = 0;
        category = "";
    }
    Task(string d, int time, string cat) {
        desc = d;
        duration = time;
        category = cat;
    }
    int getDuration() const {
        return duration;
    }
    string getDesc() const{
        return desc;
    }
    string getCategory() const{
        return category;
    }

    void setDuration(int d) {
        duration = d;
    }
    void setDesc(string description) {
        desc = description;
    }
    void setCategory(string cat) {
        category = cat;
    }

    friend ostream& operator<<(ostream& os,const Task& obj);

    bool operator< (const Task& obj) const {
        return duration < obj.duration;
    }
    bool operator> (const Task& obj) const {
        return duration > obj.duration;
    }
    bool operator<= (const Task& obj) const {
        return duration <= obj.duration;
    }
    bool operator>= (const Task& obj) const {
        return duration >= obj.duration;
    }
    bool operator== (const Task& obj) const {
        return duration == obj.duration;
    }
    bool operator!= (const Task& obj) const {
        return duration != obj.duration;
    }
    bool operator< (const int& obj) const {
        return duration < obj;
    }
    bool operator> (const int& obj) const {
        return duration > obj;
    }
    bool operator<= (const int& obj) const {
        return duration <= obj;
    }
    bool operator>= (const int& obj) const {
        return duration >= obj;
    }
    bool operator== (const int& obj) const {
        return duration == obj;
    }
    bool operator!= (const int& obj) const {
        return duration != obj;
    }
};



ostream& operator<<(ostream& os,const Task& obj) {
    os<<"["<<obj.desc<<","<<obj.duration<<","<<obj.category<<"]"<<endl;
    return os;
}
template <class T>
class Node {
    T item;
    Node<T>* right;
    Node<T>* left;
public:
    Node() {
        left  = right = nullptr;
    }
    Node(const T & el,Node<T>* Right = nullptr, Node<T>* Left = nullptr) {
        item = el;
        right = Right;
        left = Left;
    }
    T getKey() {
        return item;
    }

    void setKey(T elem) {
        item = elem;
    }

    Node<T>* getLeft() {
        return left;
    }
    Node<T>* getRight() {
        return right;
    }

    void setLeft(Node<T>* n) {
        left = n;
    }
    void setRight(Node<T>* n) {
        right = n;
    }
};
template <class T>
class BST {
private:
    Node<T>* root;
    int count = 0;
public:
    BST() {
        root = nullptr;
    }
    ~BST() {
        clearBST();
    }
    void clearBST() {
        destroy(root);
        root = nullptr;
    }

    void destroy(Node<T>* node) {
        if (node){
            destroy(node->getLeft());
            destroy(node->getRight());
            delete node;
        }
    }

    bool isEmpty() {
        return root == 0;
    }

    void visit(Node<T>* node) {
        cout<<endl<<node->getKey();
    }

    void insert(const T& item) {
        Node<T>* newNode = new Node<T>(item);
        if (root == nullptr) {
            root = newNode;
            count++;
            return;

        }

        Node<T>* current = root;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            prev = current;
            if (item <= current->getKey()) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }

        if (item <= prev->getKey()) {
            prev->setLeft(newNode);
        } else {
            prev->setRight(newNode);
        }
        count++;
    }

    void printInOrder(Node<T>* node) {
        if (node) {
            printInOrder(node->getLeft());
            visit(node);
            printInOrder(node->getRight());
        }
    }
    void inOrder() {
        if (root == nullptr) {
            cout<<"Empty Task List!"<<endl;
            return;
        }
        printInOrder(root);
    }
    void search(int dur) {
        if (root == nullptr) {
            cout<<"Empty Task List!"<<endl;
            return;
        }
        Node<T>* temp = root;
        while (temp != nullptr) {
            if (temp->getKey() == dur) {
                visit(temp);
                if (temp->getLeft() != nullptr) {
                    temp = temp->getLeft();
                }
                else {
                    return;
                }
            }
            else if (temp->getKey()>dur) {
                temp = temp->getLeft();
            }
            else {
                temp = temp->getRight();
            }
        }
    }
    Node<T>* deleteNode(Node<T>* root,const T& val) {
        if (!root) {
            cout<<"Task not found!"<<endl;
            return nullptr;
        }
        if (root->getKey() > val) {
            root->setLeft(deleteNode(root->getLeft(), val));
        }
        else if (root->getKey() < val) {
            root->setRight(deleteNode(root->getRight(), val));
        }
        else {
            if (!root->getLeft()) {
                Node<T>* temp = root->getRight();
                delete root;
                return temp;
            }
            else if (!root->getRight()) {
                Node<T>* temp = root->getLeft();
                delete root;
                return temp;
            }
            Node<T>* succ = root->getRight();
            while (succ->getLeft()) {
                succ = succ->getLeft();
            }
            root->setKey(succ->getKey());
            root->setRight(deleteNode(root->getRight(), succ->getKey()));
        }
        return root;
    }
    bool found(int dur) {
        Node<T>* temp = root;
        while (temp != nullptr) {
            if (temp->getKey() == dur) {
                return true;

            }
            else if (temp->getKey()>dur) {
                temp = temp->getLeft();
            }
            else {
                temp = temp->getRight();
            }
        }
        return false;
    }
    Node<T>* deleteNode(Node<T>* root, int val) {
        Task temp("", val, "");
        return deleteNode(root, temp);
    }

    void Delete(int val) {
        root = deleteNode(root,val);
        if (found(val)) {
            Delete(val);
        }
        else {
            return;
        }
    }
    void displayMoreHelper(Node<T>* node, int dur) {
        if (node == nullptr) return;
        if (node->getKey() >= dur) {
            displayMoreHelper(node->getLeft(), dur);
            visit(node);
            displayMoreHelper(node->getRight(), dur);
        } else {
            displayMoreHelper(node->getRight(), dur);
        }
    }

    void displayMore(int dur) {
        if (root == nullptr) {
            cout << "Empty Task List!" << endl;
            return;
        }
        displayMoreHelper(root, dur);
    }
    void displayLessHelper(Node<T>* node, int dur) {
        if (node == nullptr) return;
        if (node->getKey() <= dur) {
            displayLessHelper(node->getLeft(), dur);
            visit(node);
            displayLessHelper(node->getRight(), dur);
        } else {
            displayLessHelper(node->getLeft(), dur);
        }
    }
    void displayLess(int dur) {
        if (root == nullptr) {
            cout << "Empty Task List!" << endl;
            return;
        }
        displayLessHelper(root, dur);
    }
    string toLower(string s) {
        string result = s;
        for (char &c:result) {
            c = tolower(c);
        }
        return result;
    }
    Node<T>* deleteNodeByDesc(Node<T>* root, const T& val, bool& found, T& deletedTask) {
        if (!root) {
            return nullptr;
        }
        if (root->getKey() > val) {
            root->setLeft(deleteNodeByDesc(root->getLeft(), val,found,deletedTask));
        }
        else if (root->getKey() < val) {
            root->setRight(deleteNodeByDesc(root->getRight(), val,found,deletedTask));
        }
        else {
            string a = toLower(root->getKey().getDesc());
            string b = toLower(val.getDesc());
            if (a.find(b) != string::npos) {
                found = true;
                deletedTask = root->getKey();
            if (!root->getLeft()) {
                    Node<T>* temp = root->getRight();
                    delete root;
                    return temp;
                }
            else if (!root->getRight()) {

                    Node<T>* temp = root->getLeft();
                    delete root;
                    return temp;

            }

                Node<T>* succ = root->getRight();
                while (succ->getLeft()) {
                    succ = succ->getLeft();
                }
                root->setKey(succ->getKey());
                root->setRight(deleteNodeByDesc(root->getRight(), succ->getKey(),found,deletedTask));
            }
            else {
                root->setLeft(deleteNodeByDesc(root->getLeft(), val,found,deletedTask));
            }
        }
        return root;
    }
    Node<T>* deleteNodeByDesc(Node<T>* root, const int val,const string desc, bool& found, T& deletedTask) {
        Task temp(desc, val, "");
        return deleteNodeByDesc(root, temp,found,deletedTask);
    }

    bool DeleteByDesc(int val,string desc, T& deletedTask) {
        bool foundAny = false;
        bool found = true;
        while (found) {
            found = false;
            root = deleteNodeByDesc(root, val, desc, found, deletedTask);
            if (found) foundAny = true;
        }
        return foundAny;
    }
    int getSize() {
        return count;
    }
    bool Empty() {
        return root == nullptr;
    }
};
#endif //BST_H

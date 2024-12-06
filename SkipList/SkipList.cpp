#include <bits/stdc++.h>
using namespace std;
const int INF = 0xfffff;
template <class T>
class Node{
public:
    T data;
    vector<Node*> next;
    Node(T data, int level = 0): next(level+1, nullptr){
        this->data = data;
    }
    ~Node(){
        for (auto n:next) {
            delete n;
        }
    }
};

template <class T>
class SkipList{
private:
    Node<T>* root;
    int height;
    int maxNumberOfLevel;
public:
    SkipList(int height){
        srand(time(0));
        root = new Node<T>(T(), height);
        this->height = 0;
        this->maxNumberOfLevel = height;
    }
    void insert(T data){
        int newLevel = 0;
        // Deciding the level of inserting node on the basis of coin toss probability
        while (newLevel < maxNumberOfLevel and (rand() % 2)){ // rand()%2 for coin toss
            newLevel++;
        }
        if (height < newLevel){
            root->next.resize(newLevel + 1, nullptr);
            height = newLevel;
        }
        vector<Node<T>*> Update(height + 1, nullptr); // To store the update node at each level
        Node<T>* current = root;
        for (int i = height; i >= 0; i--){
            // Finding the place for the inserting data
            while (current->next[i] and current->next[i]->data < data){
                current = current->next[i];
            }
            Update[i] = current;
        }

        current = current->next[0];
        if (current == nullptr or current->data != data){
            Node<T>* newNode = new Node<T>(data, height);
            for (int i = 0; i <= newLevel; i++){
                newNode->next[i] = Update[i]->next[i];
                Update[i]->next[i] = newNode;  // To insert the value at each level
            }
            cout<<"Element "<<data<<" inserted successfully.\n";
        }else{
            cout<<"Element "<<data<<" already exists.\n";  // Incase if value already exists
        }
    }
    void remove(T data){
        if (!this->search(data)){
            cout<<"Element "<<data<<" does not even exist.\n";
            return;
        }

        Node<T>* current = root;
        vector<Node<T>*> update(height + 1, nullptr); // To store the update node at each level
        for (int i = height; i >= 0; --i) {
            while (current->next[i] && current->next[i]->data < data){
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0]; // The node to be removed
//        int toBeRemovedHeight = 0;
//        for (int i = height; i >= 0; --i) {
//            if (current->next[i]){
//                ++toBeRemovedHeight;
//            }
//        }

        for (int i = 0; i <= height; ++i) {
            if (update[i]->next[i] && update[i]->next[i]->data == data){
                update[i]->next[i] = current->next[i];
                current->next[i] = nullptr;
            }
        }
    }
    bool search(T data){
        Node<T>* current = root;

        for (int i = height; i >= 0; --i) {
            if (current->data == data){
                return true;
            }
            while (current->next[i] && current->next[i]->data <= data){
                current = current->next[i];
            }
//            if (current->next[i] == nullptr or current->next[i]->data > data){
//                continue;
//            }else{
//                current = current->next[i];
//            }
        }
        return current->data == data;
    }
    void print(){
        cout << "skip List:"<< endl;
        for (int i = height; i >= 0; i--){
            Node<T>* current = root->next[i];

            cout<< "Level " <<i<< ": ";

            while (current != nullptr){
                cout << current->data << " ";
                current = current->next[i];
            }
            cout<<"\n";
        }
    }
};

int main() {
    SkipList<int> skipList(3);
    skipList.insert(1);
    skipList.print();
    cout<<"-------------------\n";
    skipList.insert(2);
    skipList.print();
    cout<<"-------------------\n";
    skipList.insert(3);
    skipList.print();
    cout<<"-------------------\n";
    skipList.insert(7);
    skipList.print();
    cout<<"-------------------\n";
    skipList.insert(5);
    skipList.print();
    cout<<"-------------------\n";
    skipList.insert(6);
    skipList.print();
    cout<<"-------------------\n";
    skipList.insert(10);
    skipList.print();
    for (int i = 1; i < 11; ++i) {
        if (skipList.search(i)){
            cout<<"Found: "<<i<<endl;
        }
    }
    //--------------------------------
    skipList.remove(7);
    cout<<"After removing 7:\n";
    skipList.print();
    skipList.remove(2);
    cout<<"After removing 2:\n";
    skipList.print();
    skipList.insert(4);
    cout<<"Insert 4:\n";
    skipList.print();
    skipList.remove(5);
    cout<<"After removing 5:\n";
    skipList.print();
}
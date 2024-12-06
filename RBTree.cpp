#include <iostream>
using namespace std;

enum COLOR { RED, BLACK };
template<typename T>
class Node {
public:
    T data;
    COLOR color;
    Node *left, *right, *parent;

    Node(T data) : data(data),parent(NULL),left(NULL),right(NULL),color(RED) {
    }

    Node *getUncle() {
        if (parent == NULL or parent->parent == NULL)
            return NULL;

        if (parent->isLeft())
            return parent->parent->right;
        else
            return parent->parent->left;
    }

    bool isLeft() { return this == parent->left; }

    Node *brother() {
        if (parent == NULL)
            return NULL;

        if (isLeft())
            return parent->right;

        return parent->left;
    }

    void moveDown(Node *nParent) {
        if (parent != NULL) {
            if (isLeft()) {
                parent->left = nParent;
            } else {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool redChild() {
        return (left != NULL and left->color == RED) or
               (right != NULL and right->color == RED);
    }

    template<typename U>
    friend class RBTree;

};
template<typename T>
class RBTree {
    Node<T> *root;
    void rotate(Node<T> *x,char direction) {
        if (direction=='l') {
            Node<T> *nParent = x->right;
            if (x == root)
                root = nParent;
            x->moveDown(nParent);
            x->right = nParent->left;
            if (nParent->left != NULL)
                nParent->left->parent = x;
            nParent->left = x;
        }
        else {
            Node<T> *nParent = x->left;
            if (x == root)
                root = nParent;
            x->moveDown(nParent);
            x->left = nParent->right;
            if (nParent->right != NULL)
                nParent->right->parent = x;
            nParent->right = x;
        }
    }

    void swapColors(Node<T> *x1, Node<T> *x2) {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node<T> *u, Node<T> *v) {
        int temp;
        temp = u->data;
        u->data = v->data;
        v->data = temp;
    }
    void fixInsertion(Node<T> *x) {
        if (x == root) {
            x->color = BLACK;
            return;
        }
        Node<T> *parent = x->parent, *grandparent = parent->parent,
                *uncle = x->getUncle();
        if (parent->color != BLACK) {
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixInsertion(grandparent);
            } else {
                if (parent->isLeft()) {
                    if (x->isLeft()) {
                        swapColors(parent, grandparent);
                    } else {
                        rotate(parent,'l');
                        swapColors(x, grandparent);
                    }
                    rotate(grandparent,'r');
                } else {
                    if (x->isLeft()) {
                        rotate(parent,'r');
                        swapColors(x, grandparent);
                    } else {
                        swapColors(parent, grandparent);
                    }
                    rotate(grandparent,'l');
                }
            }
        }
    }

    Node<T> *successor(Node<T> *x) {
        Node<T> *temp = x;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    Node<T> *replace(Node<T> *x) {
        if (x->left != NULL and x->right != NULL)
            return successor(x->right);
        if (x->left == NULL and x->right == NULL)
            return NULL;
        if (x->left != NULL)
            return x->left;
        else
            return x->right;
    }
    void deleteNode(Node<T> *v) {
        Node<T> *u = replace(v);
        bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
        Node<T> *parent = v->parent;
        if (u == NULL) {
            if (v == root) {
                root = NULL;
            } else {
                if (uvBlack) {
                    fixDoubleBlack(v);
                } else {
                    if (v->brother() != NULL)
                        v->brother()->color = RED;
                }
                if (v->isLeft()) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left == NULL or v->right == NULL) {
            if (v == root) {
                v->data = u->data;
                v->left = v->right = NULL;
                delete u;
            } else {
                if (v->isLeft()) {
                    parent->left = u;
                } else {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack) {
                    fixDoubleBlack(u);
                } else {
                    u->color = BLACK;
                }
            }
            return;
        }
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node<T> *x) {
        if (x == root)
            return;

        Node<T> *sibling = x->brother(), *parent = x->parent;
        if (sibling == NULL) {
            fixDoubleBlack(parent);
        } else {
            if (sibling->color == RED) {
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isLeft()) {
                    rotate(parent,'r');
                } else {
                    rotate(parent,'l');
                }
                fixDoubleBlack(x);
            } else {
                if (sibling->redChild()) {
                    if (sibling->left != NULL and sibling->left->color == RED) {
                        if (sibling->isLeft()) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rotate(parent,'r');
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            rotate(sibling,'r');
                            rotate(parent,'l');
                        }
                    } else {
                        if (sibling->isLeft()) {
                            // left right
                            sibling->right->color = parent->color;
                            rotate(sibling,'l');
                            rotate(parent,'r');
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            rotate(parent,'l');
                        }
                    }
                    parent->color = BLACK;
                } else {
                    // 2 black children
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }
    void inorder(Node<T> *x) {
        if (x == NULL)
            return;
        inorder(x->left);
        cout << x->data << " Color "<<x->color<<endl;
        inorder(x->right);
    }

public:
    RBTree() { root = NULL; }

    Node<T> *getRoot() { return root; }
    Node<T> *search(int n) {
        Node<T> *temp = root;
        while (temp != NULL) {
            if (n < temp->data) {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            } else if (n == temp->data) {
                break;
            } else {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }
        return temp;
    }
    void insert(int n) {
        Node<T> *newNode = new Node(n);
        if (root == NULL) {
            newNode->color = BLACK;
            root = newNode;
        } else {
            Node<T> *temp = search(n);
            if (temp->data == n) {
                return;
            }
            newNode->parent = temp;
            if (n < temp->data)
                temp->left = newNode;
            else
                temp->right = newNode;
            fixInsertion(newNode);
        }
    }
    void remove(int n) {
        if (root == NULL)
            return;
        Node<T> *v = search(n), *u;
        if (v->data != n) {
            cout << "No node found to delete with value:" << n << endl;
            return;
        }
        deleteNode(v);
    }
    void printInOrder() {
        if (root == NULL)
            cout << "Tree is empty" << endl;
        else
            inorder(root);
        cout << endl;
    }

};

int main() {
    RBTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);



    tree.remove(4);

    tree.printInOrder();
    return 0;
}
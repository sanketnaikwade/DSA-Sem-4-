//============================================================================
// Name        : assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int v) {
        data = v;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    Node *root;
    BST() {
        root = nullptr;
    }

    void insert(int data) {
        Node *newnode = new Node(data);
        if (root == nullptr) {
            root = newnode;
            return;
        }
        Node *current = root;
        while (true) {
            if (current->data > data) {
                if (current->left == nullptr) {
                    current->left = newnode;
                    return;
                }
                else {
                    current = current->left;
                }
            }
            else {
                if (current->right == nullptr) {
                    current->right = newnode;
                    return;
                }
                else {
                    current = current->right;
                }
            }
        }
    }

    void inorder(Node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    bool search(Node *root, int key) {
        if (root == nullptr) return false;
        if (root->data == key) return true;
        if (root->data > key) return search(root->left, key);
        else return search(root->right, key);
    }

    int longest(Node *root) {
        if (root == nullptr) return 0;
        int lmax = longest(root->left);
        int rmax = longest(root->right);
        return 1 + max(lmax, rmax);
    }

    int mini(Node *root) {
        if (root == nullptr) return -1;
        while (root->left) {
            root = root->left;
        }
        return root->data;
    }

    int maxi(Node *root) {
        if (root == nullptr) return -1;
        while (root->right) {
            root = root->right;
        }
        return root->data;
    }

    void mirror(Node *root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    Node* findMin(Node* root) {
        while (root->left != nullptr) root = root->left;
        return root;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            // Case 1: No child
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            // Case 2: One child
            else if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Two children
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    void menu() {
        int choice, value;
        do {
            cout << "\nBinary Search Tree Menu:\n";
            cout << "1. Insert\n";
            cout << "2. Inorder Traversal\n";
            cout << "3. Search\n";
            cout << "4. Find Minimum\n";
            cout << "5. Find Maximum\n";
            cout << "6. Find Height\n";
            cout << "7. Mirror Tree\n";
            cout << "8. Delete Node\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> value;
                    insert(value);
                    break;
                case 2:
                    cout << "Inorder Traversal: ";
                    inorder(root);
                    cout << endl;
                    break;
                case 3:
                    cout << "Enter value to search: ";
                    cin >> value;
                    if (search(root, value)) cout << "Found\n";
                    else cout << "Not Found\n";
                    break;
                case 4:
                    cout << "Minimum value: " << mini(root) << endl;
                    break;
                case 5:
                    cout << "Maximum value: " << maxi(root) << endl;
                    break;
                case 6:
                    cout << "Height of tree: " << longest(root) << endl;
                    break;
                case 7:
                    mirror(root);
                    cout << "Tree mirrored!\n";
                    break;
                case 8:
                    cout << "Enter value to delete: ";
                    cin >> value;
                    root = deleteNode(root, value);
                    cout << "Deleted successfully!\n";
                    break;
                case 9:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice, try again.\n";
            }
        } while (choice != 9);
    }
};

int main() {
    BST tree;
    tree.menu();
    return 0;
}
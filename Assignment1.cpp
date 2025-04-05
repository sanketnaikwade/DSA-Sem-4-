#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    int data;
    node *left, *right;

    node(int v) {
        data = v;
        left = nullptr;
        right = nullptr;
    }
};

class bt {
public:
    node *root;

    bt() {
        root = nullptr;
    }

    void insert(int data) {
        node *newnode = new node(data);
        if (root == nullptr) {
            root = newnode;
            return;
        }

        node *temp = root;
        while (true) {
            char direction;
            cout << "Enter the direction you want to move (l/r): ";
            cin >> direction;

            if (direction == 'l') {
                if (temp->left == nullptr) {
                    temp->left = newnode;
                    return;
                } else {
                    temp = temp->left;
                }
            } else if (direction == 'r') {
                if (temp->right == nullptr) {
                    temp->right = newnode;
                    return;
                } else {
                    temp = temp->right;
                }
            } else {
                cout << "Invalid direction! Enter 'l' or 'r'." << endl;
            }
        }
    }

    // 🔹 Recursive Traversals (Not in Menu)
    void inorder(node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void preorder(node *root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(node *root) {
        if (root == nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    // 🔹 Non-Recursive (Iterative) Traversals
    void iterativeInorder(node *root) {
        stack<node *> st;
        node *current = root;
        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
            current = st.top();
            st.pop();
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }

    void iterativePreorder(node *root) {
        if (root == nullptr) return;
        stack<node *> st;
        st.push(root);
        while (!st.empty()) {
            node *current = st.top();
            st.pop();
            cout << current->data << " ";
            if (current->right) st.push(current->right);
            if (current->left) st.push(current->left);
        }
        cout << endl;
    }

    void iterativePostorder(node *root) {
        if (root == nullptr) return;
        stack<node *> st1, st2;
        st1.push(root);
        while (!st1.empty()) {
            node *current = st1.top();
            st1.pop();
            st2.push(current);
            if (current->left) st1.push(current->left);
            if (current->right) st1.push(current->right);
        }
        while (!st2.empty()) {
            cout << st2.top()->data << " ";
            st2.pop();
        }
        cout << endl;
    }

    // 🔹 Other Functions
    int height(node *root) {
        if (root == nullptr) return -1;
        int lmax = height(root->left);
        int rmax = height(root->right);
        return 1 + max(lmax, rmax);
    }

    int countLeaves(node *root) {
        if (root == nullptr) return 0;
        int count = 0;
        stack<node *> st;
        st.push(root);
        while (!st.empty()) {
            node *current = st.top();
            st.pop();
            if (current->left == nullptr && current->right == nullptr) {
                count++;
            }
            if (current->left) st.push(current->left);
            if (current->right) st.push(current->right);
        }
        return count;
    }

    int countNodes(node *root) {
        if (root == nullptr) return 0;
        int count = 0;
        stack<node *> st;
        st.push(root);
        while (!st.empty()) {
            node *current = st.top();
            st.pop();
            count++;
            if (current->left) st.push(current->left);
            if (current->right) st.push(current->right);
        }
        return count;
    }

    int countInternalNodes(node *root) {
        return countNodes(root) - countLeaves(root);
    }

    void eraseRecursive(node *node) {
        if (node != nullptr) {
            eraseRecursive(node->left);
            eraseRecursive(node->right);
            delete node;
        }
    }

    void eraseNonRecursive(node *nnode) {
        if (nnode != nullptr) {
            stack<node *> st;
            st.push(nnode);
            while (!st.empty()) {
                node *temp = st.top();
                st.pop();

                if (temp->left) st.push(temp->left);
                if (temp->right) st.push(temp->right);

                delete temp;
            }
            root = nullptr;
        }
    }

    node *copyTree(node *copynode) {
        if (copynode != nullptr) {
            node *temp = new node(copynode->data);
            temp->left = copyTree(copynode->left);
            temp->right = copyTree(copynode->right);
            return temp;
        }
        return nullptr;
    }
};

int main() {
    bt tree;
    int choice, val;

    do {
        cout << "\nBinary Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Iterative Inorder\n";
        cout << "3. Iterative Preorder\n";
        cout << "4. Iterative Postorder\n";
        cout << "5. Count Nodes\n";
        cout << "6. Count Leaves\n";
        cout << "7. Count Internal Nodes\n";
        cout << "8. Tree Height\n";
        cout << "9. Copy Tree\n";
        cout << "10. Erase Tree (Recursive)\n";
        cout << "11. Erase Tree (Non-Recursive)\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                cout << "Iterative Inorder: ";
                tree.iterativeInorder(tree.root);
                break;
            case 3:
                cout << "Iterative Preorder: ";
                tree.iterativePreorder(tree.root);
                break;
            case 4:
                cout << "Iterative Postorder: ";
                tree.iterativePostorder(tree.root);
                break;
            case 5:
                cout << "Total Nodes: " << tree.countNodes(tree.root) << endl;
                break;
            case 6:
                cout << "Total Leaf Nodes: " << tree.countLeaves(tree.root) << endl;
                break;
            case 7:
                cout << "Total Internal Nodes: " << tree.countInternalNodes(tree.root) << endl;
                break;
            case 8:
                cout << "Tree Height: " << tree.height(tree.root) << endl;
                break;
            case 9: {
                bt copy;
                copy.root = tree.copyTree(tree.root);
                cout << "Tree copied successfully.\n";
                break;
            }
            case 10:
                tree.eraseRecursive(tree.root);
                tree.root = nullptr;
                cout << "Tree erased recursively.\n";
                break;
            case 11:
                tree.eraseNonRecursive(tree.root);
                cout << "Tree erased non-recursively.\n";
                break;
            case 12:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 12);

    return 0;
}
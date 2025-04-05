#include <iostream>
using namespace std;

class Node
{
public:
    int info;
    Node *left, *right;
    bool lthread, rthread;
    Node(int val) : info(val), left(NULL), right(NULL), lthread(true), rthread(true) {}  // Initially true threads
};

class ThreadedBST
{
    Node *root;

public:
    ThreadedBST() { root = NULL; }

    void insert(int ikey)
    {
        Node *ptr = root, *par = NULL;
        while (ptr != NULL)
        {
            if (ikey == ptr->info)
            {
                cout << "Duplicate Key" << endl;
                return;
            }
            par = ptr;
            if (ikey < ptr->info)
            {
                if (!ptr->lthread)
                    ptr = ptr->left;  // Go left if the thread is false
                else
                    break;
            }
            else
            {
                if (!ptr->rthread)
                    ptr = ptr->right;  // Go right if the thread is false
                else
                    break;
            }
        }

        Node *tmp = new Node(ikey);
        if (par == NULL)
        {
            root = tmp;  // If the tree is empty, the new node becomes the root
        }
        else if (ikey < par->info)
        {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false; // After adding a left child, change lthread to false
            par->left = tmp;
        }
        else
        {
            tmp->left = par;
            tmp->right = par->right;
            par->rthread = false; // After adding a right child, change rthread to false
            par->right = tmp;
        }
    }

    Node *inorderSuccessor(Node *ptr)
    {
        if (ptr->rthread)
            return ptr->right;
        ptr = ptr->right;
        while (!ptr->lthread)
            ptr = ptr->left;
        return ptr;
    }

    void inorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        Node *ptr = root;
        while (!ptr->lthread)
            ptr = ptr->left;  // Traverse to the leftmost node
        while (ptr != NULL)
        {
            cout << ptr->info << " ";
            ptr = inorderSuccessor(ptr);  // Get the next inorder successor
        }
        cout << endl;
    }

    void preorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        Node *ptr = root;
        while (ptr != NULL)
        {
            cout << ptr->info << " ";
            if (!ptr->lthread)  // Follow the left child if lthread is false
                ptr = ptr->left;
            else if (!ptr->rthread)  // Follow the right child if rthread is false
                ptr = ptr->right;
            else
            {
                while (ptr != NULL && ptr->rthread)  // Move to the right if rthread is true
                    ptr = ptr->right;
                if (ptr != NULL)
                    ptr = ptr->right;
            }
        }
        cout << endl;
    }

    // Case A: Deleting a node with no children
    Node* caseA(Node* par, Node* ptr)
    {
        if (par == NULL)
        {
            root = NULL;  // Root node
        }
        else if (par->left == ptr)
        {
            par->lthread = true;
            par->left = ptr->left;  // Link back to predecessor or NULL
        }
        else
        {
            par->rthread = true;
            par->right = ptr->right;  // Link back to successor or NULL
        }
        delete ptr;
        return root;
    }

    // Case B: Deleting a node with one child
    Node* caseB(Node* par, Node* ptr)
    {
        Node* child = (ptr->lthread == false) ? ptr->left : ptr->right;
        if (par == NULL)
        {
            root = child;  // Root node has one child
        }
        else if (par->left == ptr)
        {
            par->lthread = false;
            par->left = child;
        }
        else
        {
            par->rthread = false;
            par->right = child;
        }
        delete ptr;
        return root;
    }

    // Case C: Deleting a node with two children
    Node* caseC(Node* par, Node* ptr)
    {
        // Find inorder successor (smallest node in the right subtree)
        Node* succ = inorderSuccessor(ptr);
        ptr->info = succ->info;  // Replace the node's info with the successor's info
        if (succ->rthread == true)
        {
            caseA(par, succ);  // Remove successor node
        }
        else
        {
            caseB(par, succ);  // Remove successor node with one child
        }
        return root;
    }

    // Deletion function
    Node* delThreadedBST(int dkey)
    {
        Node *par = NULL, *ptr = root;
        bool found = false;

        // Search for the node to be deleted
        while (ptr != NULL)
        {
            if (dkey == ptr->info)
            {
                found = true;
                break;
            }
            par = ptr;
            if (dkey < ptr->info)
            {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            }
            else
            {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        if (!found)
        {
            cout << "dkey not present in tree\n";
            return root;
        }

        // Two children
        if (ptr->lthread == false && ptr->rthread == false)
            root = caseC(par, ptr);
        // Only left child
        else if (ptr->lthread == false)
            root = caseB(par, ptr);
        // Only right child
        else if (ptr->rthread == false)
            root = caseB(par, ptr);
        // No child
        else
            root = caseA(par, ptr);

        return root;
    }
};

int main()
{
    ThreadedBST tbst;
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Delete Node\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            tbst.insert(value);
            break;
        case 2:
            cout << "Inorder Traversal: ";
            tbst.inorder();
            break;
        case 3:
            cout << "Preorder Traversal: ";
            tbst.preorder();
            break;
        case 4:
            int dkey;
            cout << "Enter value to delete: ";
            cin >> dkey;
            tbst.delThreadedBST(dkey);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 5);
    return 0;
}
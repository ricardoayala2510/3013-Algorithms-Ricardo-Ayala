#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class Bst {
private:
    Node *root;

    void _insert(Node *&sub_root, int x) {
        if (sub_root == nullptr) {
            sub_root = new Node(x);
        } else {
            if (x < sub_root->data) {
                _insert(sub_root->left, x);
            } else {
                _insert(sub_root->right, x);
            }
        }
    }

    void _print(Node *root) {
        if (!root) return;
        _print(root->right);
        cout << root->data << " ";
        _print(root->left);
    }

    // Recursive delete helper 
    void _delete(Node*& sub_root, int x) {
        // Base case: reached null node or tree is empty
        if (sub_root == nullptr) return;

        // Search for the node to delete
        if (x < sub_root->data) {
            _delete(sub_root->left, x);  // Recursively search left subtree
        } else if (x > sub_root->data) {
            _delete(sub_root->right, x); // Recursively search right subtree
        } else {
            // Node found - handle 3 deletion cases

            // Case 1: No children (leaf node)
            if (sub_root->left == nullptr && sub_root->right == nullptr) {
                delete sub_root;        // Free memory
                sub_root = nullptr;     // Update parent's pointer to null
            }

            // Case 2: One child
            else if (sub_root->left == nullptr) {
                Node* temp = sub_root;  // Store node to delete
                sub_root = sub_root->right; // Bypass node (connect parent to right child)
                delete temp;            // Free memory
            } else if (sub_root->right == nullptr) {
                Node* temp = sub_root;  // Store node to delete
                sub_root = sub_root->left;  // Bypass node (connect parent to left child)
                delete temp;            // Free memory
            }

            // Case 3: Two children
            else {
                // Find inorder successor (smallest in right subtree)
                Node* successor = findMin(sub_root->right);
                
                // Copy successor's data to current node
                sub_root->data = successor->data;
                
                // Delete the successor node (now contains duplicate value)
                _delete(sub_root->right, successor->data); // Will be Case 1 or 2
            }
        }
    }

    // Helper to find minimum value node in a subtree
    Node* findMin(Node* node) {
        // Traverse left until last left node is found
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;  // Return leftmost node (minimum value)
    }

public:
    Bst() : root(nullptr) {}

    void insert(int x) {
        _insert(root, x);
    }

    void deleteNode(int x) {
        _delete(root, x);
    }

    bool search() { return false; }

    void print() {
        _print(root);
    }

};

int main() {
    Bst tree;
    
    // Insert test values
    tree.insert(8);
    tree.insert(3);
    tree.insert(1);
    tree.insert(11);
    tree.insert(7);
    tree.insert(15);

    // Test deletions
    cout << "Before deletions: ";
    tree.print();  // Output: 15 11 8 7 3 1

    tree.deleteNode(3);
    cout << "\nAfter deleting 3: ";
    tree.print();  // Output: 15 11 8 7 1

    tree.deleteNode(8);
    cout << "\nAfter deleting 8: ";
    tree.print();  // Output: 15 11 7 1

    return 0;
}

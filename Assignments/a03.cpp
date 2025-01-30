//Ricardo Ayala 
//01-30-2024
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
    if (!root) {
      return;
    }
    _print(root->right);
    cout << root->data << " ";
    _print(root->left);
  }

  void _delete(Node*& sub_root, int x) {
    if (sub_root == nullptr) return;

    if (x < sub_root->data) {
      _delete(sub_root->left, x);
    } else if (x > sub_root->data) {
      _delete(sub_root->right, x);
    } else {
      // Node found, handle deletion
      if (sub_root->left == nullptr && sub_root->right == nullptr) {
        // Case 1: No children
        delete sub_root;
        sub_root = nullptr;
      } else if (sub_root->left == nullptr) {
        // Case 2: One right child
        Node* temp = sub_root;
        sub_root = sub_root->right;
        delete temp;
      } else if (sub_root->right == nullptr) {
        // Case 2: One left child
        Node* temp = sub_root;
        sub_root = sub_root->left;
        delete temp;
      } else {
        // Case 3: Two children
        Node* successor = findMin(sub_root->right);
        sub_root->data = successor->data;
        _delete(sub_root->right, successor->data);
      }
    }
  }

  Node* findMin(Node* node) {
    while (node && node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

public:
  Bst() { root = nullptr; }
  
  void insert(int x) {
    _insert(root, x);
  }
  
  void deleteNode(int x) {
    _delete(root, x);
  }
  
  bool search() { return 0; }
  
  void print() { 
    _print(root); 
  }
  
};

int main() {
  Bst tree;
  tree.insert(8);
  tree.insert(3);
  tree.insert(1);
  tree.insert(11);
  tree.insert(7);
  tree.insert(15);

  cout << "Before deletions: ";
  tree.print(); // Output: 15 11 8 7 3 1 

  tree.deleteNode(3);
  cout << "\nAfter deleting 3: ";
  tree.print(); // Output: 15 11 8 7 1 

  tree.deleteNode(8);
  cout << "\nAfter deleting 8: ";
  tree.print(); // Output: 15 11 7 1 

  return 0;
}
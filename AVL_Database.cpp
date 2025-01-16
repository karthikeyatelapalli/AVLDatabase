/* 

Description: Here This code uses an AVL tree structure to provide a basic Database Management System (DBMS) for effective record management. 
Records can be added, updated, searched for, and deleted using the system's features, which happens in O(log n) time. Through rotations, 
the AVL tree keeps itself balanced by making sure there is never a height difference greater than one between subtrees. All these 
activities are handled by the IndexedDatabase class, which keeps the database in a balanced state and makes record retrieval and 
manipulation efficient.
*/

#include "AVL_Database.hpp"
#include <algorithm>
#include <iostream>


// This is the constructor for the Record class
Record::Record(const std::string& k, int v) : key(k), value(v) {}

// This is the constructor for the AVLNode class
AVLNode::AVLNode(Record* r) : record(r), left(nullptr), right(nullptr), height(1) {}

// This is the constructor for the AVLTree class, initializing the root to nullptr
AVLTree::AVLTree() : root(nullptr) {}

// This is the function to get the height of a given node
int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

// This is the function to calculate the balance factor of a given node
int AVLTree::balance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// This is the getter function for the root node
AVLNode* AVLTree::getRoot() const {
    return root;
}

// This is the setter function to update the root node
void AVLTree::newRoot(AVLNode* rootUpdate) {
    root = rootUpdate;
}

// This is the function to perform a right rotation to balance the tree
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    if (y == nullptr || y->left == nullptr) { //if y is null or the left node is missing, there is nothing to rotate
        return y;
    }
    AVLNode* temp_A = y->left;   //assign temp variables for rotation; temp_A will be the new root
    AVLNode* temp_B = temp_A->right;
    temp_A->right = y;
    y->left = temp_B;

    // Here we update the heights of the nodes involved in the rotation
    y->height = std::max(height(y->left), height(y->right)) + 1;
    temp_A->height = std::max(height(temp_A->left), height(temp_A->right)) + 1;

    return temp_A;
}

// This is the function to perform a left rotation to balance the tree
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    if (x == nullptr || x->right == nullptr) {  //check that the node & right child exist (no rotation possible otherwise)
        return x;
    }
    AVLNode* temp_A = x->right;  //rotate using temp variables; temp_A will become the new root
    AVLNode* temp_B = temp_A->left;
    temp_A->left = x;
    x->right = temp_B;

    // Here we update the heights of the nodes involved in the rotation
    x->height = std::max(height(x->left), height(x->right)) + 1;
    temp_A->height = std::max(height(temp_A->left), height(temp_A->right)) + 1;

    return temp_A;
}

// This is the function to insert a new record into the AVL tree
void AVLTree::insert(Record* record) {
    root = insertHelper(root, record);
}

// This is the helper function to recursively insert a record into the tree
AVLNode* AVLTree::insertHelper(AVLNode* node, Record* record) {
    if (node == nullptr) {
        return new AVLNode(record);
    }
    if (record->value < node->record->value) { //determine where to enter the node
        node->left = insertHelper(node->left, record);
    }
    else if (record->value > node->record->value) {
        node->right = insertHelper(node->right, record);
    }
    else {
        return node;
    }

    // Here we update the height of the current node
    node->height = std::max(height(node->left), height(node->right)) + 1;
    // Here we check the balance factor of the current node
    int bal = balance(node);

    // Rotation cases to maintain the AVL tree balance
    //LL
    if (bal > 1 && record->value < node->left->record->value) {
        return rotateRight(node);
    }
    //LR
    if (bal > 1 && record->value > node->left->record->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    //RL
    if (bal < -1 && record->value < node->right->record->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    //RR
    if (bal < -1 && record->value > node->right->record->value) {
        return rotateLeft(node);
    }
    return node;    //reached end 
}

// This is the function to search for a record in the AVL tree by key and value
Record* AVLTree::search(const std::string& key, int value) {
    AVLNode* cur = root;
    while (cur != nullptr) {
        if (value == cur->record->value && key == cur->record->key) {
            return cur->record;
        }
        else if (value > cur->record->value) {
            cur = cur->right;
        }
        else {
            cur = cur->left;
        }
    }
    return new Record("", 0);
}

// This is the function to delete a record from the AVL tree
void AVLTree::deleteNode(const std::string& key, int value) {
    root = deleteNodeHelper(root, key, value);
}

// This is the helper function to recursively delete a node from the tree
AVLNode* AVLTree::deleteNodeHelper(AVLNode* root, const std::string& key, int value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->record->value) {    //node still has left parent
        root->left = deleteNodeHelper(root->left, key, value);
    }
    else if (value > root->record->value) {   //node still has right parent
        root->right = deleteNodeHelper(root->right, key, value);
    }
    else {   //node can be deleted
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == nullptr) { // No child case
                temp = root;
                root = nullptr;
            }
            else { // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }
            delete temp;
        }
        else { // Two children case
            AVLNode* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->record = temp->record;
            root->right = deleteNodeHelper(root->right, temp->record->key, temp->record->value);
        }
    }

    if (root == nullptr) {
        return root;
    }

    // Here we update the height of the current node
    root->height = std::max(height(root->left), height(root->right)) + 1;
    // Here we check the balance factor of the current node
    int bal = balance(root);

    // Adjust balance with rotation cases
    //LL
    if (bal > 1 && balance(root->left) >= 0) {
        return rotateRight(root);
    }
    //LR
    if (bal > 1 && balance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    //RL
    if (bal < -1 && balance(root->right) <= 0) {
        return rotateLeft(root);
    }
    //RR
    if (bal < -1 && balance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// This is the helper function to recursively perform in-order traversal of the tree
void AVLTree::inorderHelper(AVLNode* node, std::vector<Record*>& vec) const {
    if (node == nullptr) return;
    inorderHelper(node->left, vec);
    vec.push_back(node->record);
    inorderHelper(node->right, vec);
}

// This is the function to perform an in-order traversal and return the records
std::vector<Record*> AVLTree::inorderTraversal() const {
    std::vector<Record*> vec;
    inorderHelper(root, vec);
    return vec;
}

// This is the constructor for the IndexedDatabase class, initializing the record count to 0
IndexedDatabase::IndexedDatabase() : inv(0) {}

// This is the function to insert a new record into the database
void IndexedDatabase::insert(Record* record) {
    inv++; //update record count (insertion -> +1)
    index.insert(record);
}

// This is the function to search for a record in the database by key and value
Record* IndexedDatabase::search(const std::string& key, int value) {
    return index.search(key, value);
}

// This is the function to delete a record from the database
void IndexedDatabase::deleteRecord(const std::string& key, int value) {
    Record* temp = index.search(key, value);
    if (temp->key != "") {
        index.deleteNode(key, value);
        inv--;    //update record count (deletion -> -1)
    }
}

// This is the function to perform a range query on the records in the database
std::vector<Record*> IndexedDatabase::rangeQuery(int start, int end) {
    std::vector<Record*> result;
    std::vector<Record*> inorder = index.inorderTraversal();
    for (auto& record : inorder) {
        if (record->value >= start && record->value <= end) {
            result.push_back(record);
        }
    }
    return result;
}

// This is the function to find the k nearest records to a given key in the database
std::vector<Record*> IndexedDatabase::findKNearestKeys(int key, int k) {
    std::vector<std::pair<int, Record*>> distances;
    std::vector<Record*> inorder = index.inorderTraversal();

    for (auto& record : inorder) {
        int diff = abs(record->value - key);
        distances.push_back({diff, record});
    }

    // Here we sort the records by their distance to the given key
    std::sort(distances.begin(), distances.end(), [](const std::pair<int, Record*>& a, const std::pair<int, Record*>& b) {
        return a.first < b.first;
    });

    // Here we collect the k nearest records
    std::vector<Record*> result;
    for (int i = 0; i < k && i < distances.size(); ++i) {
        result.push_back(distances[i].second);
    }

    // Here we reverse the result to get the order correct
    std::reverse(result.begin(), result.end());

    return result;
}

// This is the function to perform an in-order traversal of the database
std::vector<Record*> IndexedDatabase::inorderTraversal() {
    return index.inorderTraversal();
}

// This is the recursive helper function to clear the database
void IndexedDatabase::clearDatabaseRecur(AVLNode* cur) {
    if (cur == nullptr) {
        return;
    }
    clearDatabaseRecur(cur->left);  //iterate through database recursively in the left and right direction
    clearDatabaseRecur(cur->right);
    delete cur->record; //actual deletion
    delete cur;
}

// This is the function to clear the entire database
void IndexedDatabase::clearDatabase() {
    clearDatabaseRecur(index.getRoot());    //getRoot method to simplify clearing process
    index.newRoot(nullptr);
    inv = 0; //update record counter (database cleared -> no more records)
}

// This is the function to count the number of records in the database
int IndexedDatabase::countRecords() {
    return inv;
}

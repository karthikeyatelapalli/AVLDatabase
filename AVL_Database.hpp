
#ifndef AVL_DATABASE_HPP
#define AVL_DATABASE_HPP

#include <string>
#include <vector>
#include <queue>

// This is the class which is representing a single record in the database
class Record {
public:
    std::string key;  // This is the key for the record
    int value;        // This is the value associated with the key

    // This is the constructor to initialize a Record object
    Record(const std::string& k, int v);
};

// This is the class for representing a node in the AVL tree
class AVLNode {
public:
    Record* record;  // This is the pointer to the record stored in this node
    AVLNode* left;   // This is the pointer to the left child node
    AVLNode* right;  // This is the pointer to the right child node
    int height;      // This is the height of the node in the tree

    // This is the constructor to initialize an AVLNode with a given record
    AVLNode(Record* r);
};

// This is the class representing the AVL tree itself
class AVLTree {
private:
    AVLNode* root;  // This is the pointer to the root node of the AVL tree

    // This is the helper function to get the height of a node
    int height(AVLNode* node);

    // This is the helper function to calculate the balance factor of a node
    int balance(AVLNode* node);

    // Here we do right rotation to balance the tree
    AVLNode* rotateRight(AVLNode* y);

    // Here we do left rotation to balance the tree
    AVLNode* rotateLeft(AVLNode* x);

    // This is the recursive helper function to insert a record into the tree
    AVLNode* insertHelper(AVLNode* node, Record* record);

    // This is the recursive helper function to delete a node from the tree
    AVLNode* deleteNodeHelper(AVLNode* root, const std::string& key, int value);

    // This is the recursive helper function for in-order traversal
    void inorderHelper(AVLNode* node, std::vector<Record*>& vec) const;

public:
    // This is the constructor to initialize an empty AVL tree
    AVLTree();

    // This is the public function to insert a record into the tree
    void insert(Record* record);

    // This is the public function to search for a record by key and value
    Record* search(const std::string& key, int value);

    // This is the public function to delete a record from the tree
    void deleteNode(const std::string& key, int value);

    // This is the getter for the root node
    AVLNode* getRoot() const;

    // This is the setter to update the root node
    void newRoot(AVLNode* rootUpdate);

    // This is the public function to perform an in-order traversal of the tree
    std::vector<Record*> inorderTraversal() const;
};

// This is the class representing the indexed database using an AVL tree
class IndexedDatabase {
private:
    AVLTree index;  // This is the AVL tree used for indexing records
    int inv;        // This is the counter for the number of records in the database

public:
    // This is the constructor to initialize an empty database
    IndexedDatabase();

    // This is the public function to insert a record into the database
    void insert(Record* record);

    // This is the public function to search for a record by key and value
    Record* search(const std::string& key, int value);

    // This is the public function to delete a record from the database
    void deleteRecord(const std::string& key, int value);

    // This is the public function to perform a range query on the records
    std::vector<Record*> rangeQuery(int start, int end);

    // This is the public function to find the k nearest records to a given key
    std::vector<Record*> findKNearestKeys(int key, int k);

    // This is the public function to perform an in-order traversal of the database
    std::vector<Record*> inorderTraversal();

    // This is the public function to clear the entire database
    void clearDatabase();

    // This is the recursive helper function to clear the database
    void clearDatabaseRecur(AVLNode* cur);

    // This is the public function to count the number of records in the database
    int countRecords();
};

#endif // AVL_DATABASE_HPP

#pragma once

#include <cstddef>
#include <iostream>

template<class T>
class BinarySearchTree {
private:
    struct Node {
        T _value;
        Node* _left;
        Node* _right;

        Node(const T& value = T()) 
            : _value(value), _left(nullptr), _right(nullptr) {}
    };

    Node* _root;    
    size_t _size;

    Node* search(Node* node, const T& value) const; 
    Node* addTo(Node* node, const T& value);
    Node* deleteTree(Node* root, const T& value, bool& wasDeleted);
    Node* minimum(Node* node) const;
    void destroy(Node* node);
    void print(Node* node, std::ostream& out) const;
    void copyTree(Node* root, Node* otherRoot);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& copy);
    BinarySearchTree(BinarySearchTree<T>&& copy);
    BinarySearchTree& operator=(const BinarySearchTree<T>& copy);
    BinarySearchTree& operator=(BinarySearchTree<T>&& copy);
    ~BinarySearchTree();

    void add(const T& value);
    void remove(const T& value);
    void printTree(std::ostream& out = std::cout) const;
    bool find(const T& value) const;
    void clear();

    size_t size() const;
};

template<class T>    
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::search(
                                                        Node* node,
                                                        const T& value) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->_value < value) {
        return search(node->_right, value);
    }
    else if (node->_value > value){
        return search(node->_left, value); 
    }
    return node;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::addTo(Node* node,
                                                            const T& value)
{
    if (node == nullptr) {
        return new Node(value);
    }
    else if (node->_value < value) {
        node->_right = addTo(node->_right, value);
    }
    else if (node->_value >= value) {
        node->_left = addTo(node->_left, value);
    }
    return node;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::deleteTree(
                                                            Node* root, 
                                                            const T& value,
                                                            bool& wasDeleted)
{
    if (root == nullptr) {
        return nullptr;
    }
    else if (root->_value < value) {
        root->_right = deleteTree(root->_right, value, wasDeleted);
    }
    else if (root->_value > value) {
        root->_left = deleteTree(root->_left, value, wasDeleted);
    }
    else if (root->_left != nullptr && root->_right != nullptr) {
        root->_value = (minimum(root->_right))->_value;        
        root->_right = deleteTree(root->_right, root->_value, wasDeleted);
    }
    else {
        Node* newRoot = nullptr;
        if (root->_left != nullptr) {
            newRoot = root->_left;
        }
        else if (root->_right != nullptr) {
            newRoot = root->_right;
        }
        delete[] root;
        root = newRoot;
        wasDeleted = true;
    }
    return root;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::minimum(
                                                            Node* node) const
{
    if (node->_left == nullptr) {
        return node;
    }
    return minimum(node->_left);
}

template<class T>    
void BinarySearchTree<T>::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->_left);
    destroy(node->_right);
    delete[] node;
}

template<class T>
void BinarySearchTree<T>::print(Node* node, std::ostream& out) const {
    if (node != nullptr) {
        print(node->_left, out);
        out << node->_value << " ";
        print(node->_right, out);
    }
}

template<class T>
void BinarySearchTree<T>::copyTree(Node* root, Node* otherRoot) {
    root->_value = otherRoot->_value;
    root->_left = nullptr;
    root->_right = nullptr;
    if (otherRoot->_left != nullptr) {
        root->_left = new Node();
        copyTree(root->_left, otherRoot->_left);
    }
    if (otherRoot->_right != nullptr) {
        root->_right = new Node();
        copyTree(root->_right, otherRoot->_right);
    }
}

template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    _size = 0;
    _root = nullptr;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& copy)
{
    _size = copy.size();
    _root = nullptr;
    if (copy.size() > 0) {
        _root = new Node();
        copyTree(_root, copy._root);
    }
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& copy) {
    _size = copy.size();
    _root = copy._root;
    copy._root = nullptr;
    copy._size = 0;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(
        const BinarySearchTree<T>& copy)
{
    this->clear();
    _size = copy.size();
    _root = nullptr;
    if (copy.size() > 0) {
        _root = new Node();
        copyTree(_root, copy._root);
    }

    return *this;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& copy) {
    this->clear();
    _size = copy.size();
    _root = copy._root;
    copy._root = nullptr;
    copy._size = 0;

    return *this;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    this->clear();
}

template<class T>
void BinarySearchTree<T>::add(const T& value) {
    if (_root == nullptr) {
        _root = new Node(value);
    }
    else {
        addTo(_root, value);
    }
    _size++;
}

template<class T>
void BinarySearchTree<T>::remove(const T& value) {
    bool wasDeleted = false;
    _root = deleteTree(_root, value, wasDeleted); // returns the new root
    if (wasDeleted) {
        _size--;
    }
}

template<class T>
void BinarySearchTree<T>::printTree(std::ostream& out) const {
    print(_root, out);
}

template<class T>
bool BinarySearchTree<T>::find(const T& value) const {
    Node* node = search(_root, value);
    
    return !(node == nullptr);
}

template<class T>
void BinarySearchTree<T>::clear() {
    destroy(_root);
    _size = 0;
    _root = nullptr;
}

template<class T>
size_t BinarySearchTree<T>::size() const {
    return _size;
}

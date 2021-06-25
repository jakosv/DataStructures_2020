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

    Node* _search(Node* node, const T& value) const; 
    Node* _addTo(Node* node, const T& value);
    Node* _deleteTree(Node* root, const T& value, bool& wasDeleted);
    Node* _minimum(Node* node) const;
    void _destroy(Node* node);
    void _printTree(Node* node, std::ostream& out) const;
    void _copyTree(Node* root, Node* otherRoot);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& copy);
    BinarySearchTree(BinarySearchTree<T>&& copy) noexcept;
    BinarySearchTree& operator=(const BinarySearchTree<T>& copy);
    BinarySearchTree& operator=(BinarySearchTree<T>&& copy) noexcept;
    ~BinarySearchTree();

    void add(const T& value);
    void remove(const T& value);
    void print(std::ostream& out = std::cout) const;
    bool find(const T& value) const;
    void clear();

    size_t size() const;
};

template<class T>    
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_search(
                                                        Node* node,
                                                        const T& value) const
{
    if (node == nullptr) {
        return nullptr;
    }
    else if (node->_value < value) {
        return _search(node->_right, value);
    }
    else if (node->_value > value){
        return _search(node->_left, value); 
    }
    return node;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_addTo(Node* node,
                                                            const T& value)
{
    if (node == nullptr) {
        return new Node(value);
    }
    else if (node->_value < value) {
        node->_right = _addTo(node->_right, value);
    }
    else if (node->_value >= value) {
        node->_left = _addTo(node->_left, value);
    }
    return node;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_deleteTree(
                                                            Node* root, 
                                                            const T& value,
                                                            bool& wasDeleted)
{
    if (root == nullptr) {
        return nullptr;
    }
    else if (root->_value < value) {
        root->_right = _deleteTree(root->_right, value, wasDeleted);
    }
    else if (root->_value > value) {
        root->_left = _deleteTree(root->_left, value, wasDeleted);
    }
    else if (root->_left != nullptr && root->_right != nullptr) {
        root->_value = (_minimum(root->_right))->_value;        
        root->_right = _deleteTree(root->_right, root->_value, wasDeleted);
    }
    else {
        Node* newRoot = nullptr;
        if (root->_left != nullptr) {
            newRoot = root->_left;
        }
        else if (root->_right != nullptr) {
            newRoot = root->_right;
        }
        delete root;
        root = newRoot;
        wasDeleted = true;
    }
    return root;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_minimum(
                                                            Node* node) const
{
    if (node->_left == nullptr) {
        return node;
    }
    return _minimum(node->_left);
}

template<class T>    
void BinarySearchTree<T>::_destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    _destroy(node->_left);
    _destroy(node->_right);
    delete node;
}

template<class T>
void BinarySearchTree<T>::_printTree(Node* node, std::ostream& out) const {
    if (node != nullptr) {
        _printTree(node->_left, out);
        out << node->_value << " ";
        _printTree(node->_right, out);
    }
}

template<class T>
void BinarySearchTree<T>::_copyTree(Node* root, Node* otherRoot) {
    root->_value = otherRoot->_value;
    root->_left = nullptr;
    root->_right = nullptr;
    if (otherRoot->_left != nullptr) {
        root->_left = new Node();
        _copyTree(root->_left, otherRoot->_left);
    }
    if (otherRoot->_right != nullptr) {
        root->_right = new Node();
        _copyTree(root->_right, otherRoot->_right);
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
        _copyTree(_root, copy._root);
    }
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& copy) noexcept {
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
        _copyTree(_root, copy._root);
    }

    return *this;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& copy) 
                                                                    noexcept
{
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
        _addTo(_root, value);
    }
    _size++;
}

template<class T>
void BinarySearchTree<T>::remove(const T& value) {
    bool wasDeleted = false;
    _root = _deleteTree(_root, value, wasDeleted); // returns the new root
    if (wasDeleted) {
        _size--;
    }
}

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const {
    _printTree(_root, out);
}

template<class T>
bool BinarySearchTree<T>::find(const T& value) const {
    Node* node = _search(_root, value);
    
    return !(node == nullptr);
}

template<class T>
void BinarySearchTree<T>::clear() {
    _destroy(_root);
    _size = 0;
    _root = nullptr;
}

template<class T>
size_t BinarySearchTree<T>::size() const {
    return _size;
}

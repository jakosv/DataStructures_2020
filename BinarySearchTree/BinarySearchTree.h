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
        Node* _parent;

        Node(const T& value = T(), Node* parent = nullptr) 
            : _value(value), 
              _left(nullptr), 
              _right(nullptr),
              _parent(parent) {}
    };

    Node* _root;    
    size_t _size;

    Node* _search(Node* node, const T& value) const; 
    Node* _addTo(Node* node, const T& value, Node* parent);
    Node* _deleteTree(Node* root, const T& value, Node* parent, 
                                                            bool& wasDeleted);
    Node* _minimum(Node* node) const;
    Node* _maximum(Node* node) const;
    Node* _next(const T& value) const;
    Node* _prev(const T& value) const;
    void _destroy(Node* node);
    void _printTree(Node* node, std::ostream& out) const;
    void _copyTree(Node* root, Node* otherRoot);

public:
    struct Iterator {
    public:
        Iterator(Node* ptr = nullptr);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        const T& operator*() const;
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
    private:
        Node* _ptr;

        Node* _maximum(Node* node) const;
        Node* _minimum(Node* node) const;
    };

    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& copy);
    BinarySearchTree(BinarySearchTree<T>&& copy) noexcept;
    BinarySearchTree& operator=(const BinarySearchTree<T>& copy);
    BinarySearchTree& operator=(BinarySearchTree<T>&& copy) noexcept;
    ~BinarySearchTree();

    void add(const T& value);
    void remove(const T& value);
    void print(std::ostream& out = std::cout) const;
    Iterator find(const T& value) const;
    void clear();

    size_t size() const;

    Iterator begin();
    Iterator end() noexcept;
};


/* Private methods */

template<class T>    
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_search(
                                            Node* node, const T& value) const
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
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_addTo(
                                    Node* node, const T& value, Node* parent)
{
    if (node == nullptr) {
        return new Node(value, parent);
    }
    else if (node->_value < value) {
        node->_right = _addTo(node->_right, value, node);
    }
    else if (node->_value >= value) {
        node->_left = _addTo(node->_left, value, node);
    }
    return node;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_deleteTree(
                    Node* root, const T& value, Node* parent, bool& wasDeleted)
{
    if (root == nullptr) {
        return nullptr;
    }
    else if (root->_value < value) {
        root->_right = _deleteTree(root->_right, value, root, wasDeleted);
    }
    else if (root->_value > value) {
        root->_left = _deleteTree(root->_left, value, root, wasDeleted);
    }
    else if (root->_left != nullptr && root->_right != nullptr) {
        root->_value = (_minimum(root->_right))->_value;        
        root->_right = _deleteTree(root->_right, root->_value, root,
                                                                wasDeleted);
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
        newRoot->_parent = parent;
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
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_maximum(
                                                            Node* node) const
{
    if (node->_right == nullptr) {
        return node;
    }
    return _maximum(node->_right);
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_next(
                                                        const T& value) const
{
    Node* current = _root, successor = nullptr;
    while (current != nullptr) {
        if (current->_value > value) {
            successor = current;
            current = current->_left;
        }
        else {
            current = current->_right;
        }
    }
    return successor;
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::_prev(
                                                        const T& value) const
{
    Node* current = _root, successor = nullptr;
    while (current != nullptr) {
        if (current->_value < value) {
            successor = current;
            current = current->_right;
        }
        else {
            current = current->_left;
        }
    }
    return successor;
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
    root->_left = nullptr;
    root->_right = nullptr;
    if (otherRoot->_left != nullptr) {
        root->_left = new Node(otherRoot->_left->_value, root);
        _copyTree(root->_left, otherRoot->_left);
    }
    if (otherRoot->_right != nullptr) {
        root->_right = new Node(otherRoot->_right->_value, root);
        _copyTree(root->_right, otherRoot->_right);
    }
}


/* Public methods */

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
        _root = new Node(copy._root->_value);
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
        _root = new Node(copy._root->_value);
        _copyTree(_root, copy._root);
    }

    return *this;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(
                                        BinarySearchTree<T>&& copy) noexcept
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
        _addTo(_root, value, nullptr);
    }
    _size++;
}

template<class T>
void BinarySearchTree<T>::remove(const T& value) {
    bool wasDeleted = false;
    _root = _deleteTree(_root, value, nullptr, wasDeleted); // returns new root
    if (wasDeleted) {
        _size--;
    }
}

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const {
    _printTree(_root, out);
}

template<class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::find(
                                                    const T& value) const
{
    Node* node = _search(_root, value);
    
    return Iterator(node);
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


template<class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin() {
    if (_root == nullptr) {
        return nullptr;
    }
    else if (_root->_left == nullptr) {
        return _root;
    }
    return Iterator(_minimum(_root->_left));
}

template<class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::end() noexcept
{
    return Iterator(nullptr);
}


/* Iterator methods */

template<class T>
BinarySearchTree<T>::Iterator::Iterator(BinarySearchTree<T>::Node* ptr) 
    : _ptr(ptr) {}
        

template<class T>       
BinarySearchTree<T>::Iterator::Iterator(
                                const BinarySearchTree<T>::Iterator& other)
{
    _ptr = other._ptr;
}

template<class T>       
typename BinarySearchTree<T>::Iterator& 
    BinarySearchTree<T>::Iterator::operator=(
                                const BinarySearchTree<T>::Iterator& other)
{
    _ptr = other._ptr;

    return *this;
}

template<class T>       
const T& BinarySearchTree<T>::Iterator::operator*() const {
    return _ptr->_value;
}

template<class T>
bool BinarySearchTree<T>::Iterator::operator!=(
                            const BinarySearchTree<T>::Iterator& other) const
{
    return (this->_ptr != other._ptr);
}

template<class T>
bool BinarySearchTree<T>::Iterator::operator==(
                            const BinarySearchTree<T>::Iterator& other) const
{
    return !(*this != other); 
}

template<class T>
typename BinarySearchTree<T>::Iterator& 
                                BinarySearchTree<T>::Iterator::operator++()
{
    if (_ptr == nullptr) {
        return *this;
    }

    if (_ptr->_right != nullptr) {
        _ptr = _minimum(_ptr->_right);
        return *this;
    }

    Node* parent = _ptr->_parent;
    while (parent != nullptr && parent->_right == _ptr) {
        _ptr = parent;
        parent = parent->_parent;
    }
    _ptr = parent;

    return *this;
}

template<class T>
typename BinarySearchTree<T>::Iterator 
                            BinarySearchTree<T>::Iterator::operator++(int)
{
    Iterator oldIter = *this;
    ++(*this);
    return oldIter;
}

template<class T>
typename BinarySearchTree<T>::Iterator& 
                                BinarySearchTree<T>::Iterator::operator--()
{
    if(_ptr == nullptr) {
        return *this;
    }

    if (_ptr->_left != nullptr) {
        _ptr = _maximum(_ptr->_left);
        return *this;
    }

    Node* parent = _ptr->_parent;
    while (parent != nullptr && parent->_left == _ptr) {
        _ptr = parent;
        parent = _ptr->_parent;
    }
    _ptr = parent;

    return *this;
}

template<class T>
typename BinarySearchTree<T>::Iterator 
                            BinarySearchTree<T>::Iterator::operator--(int)
{
    Iterator oldIter = *this;
    --(*this);
    return oldIter;
}

template<class T>
typename BinarySearchTree<T>::Node* 
        BinarySearchTree<T>::Iterator::_maximum(
                                    BinarySearchTree<T>::Node* node) const
{
    if (node->_right == nullptr) {
        return node;
    }
    return _maximum(node->_right);

}

template<class T>
typename BinarySearchTree<T>::Node* 
        BinarySearchTree<T>::Iterator::_minimum(
                                    BinarySearchTree<T>::Node* node) const
{
    if (node->_left == nullptr) {
        return node;
    }
    return _minimum(node->_left);
}

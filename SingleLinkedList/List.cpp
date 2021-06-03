#include "List.h"

#include <stdexcept>

template<typename T>
List<T>::Node::Node(const T& value, List<T>::Node* next)
    : value(value), next(next) {}
    
template<typename T>
std::ostream& operator<< (std::ostream& output, 
                          const typename List<T>::Node& node)
{
    output << node.value;
    return output;
}

template<typename T>
std::istream& operator>>(std::istream& input, typename List<T>::Node& node) {
    input >> node.value; 
    return input;
}


template<typename T>
List<T>::List() {
    _head = nullptr;
    _size = 0;
}

template<typename T>
List<T>::List(const T& value) {
    _head = new List<T>::Node(value);
    _size = 1;
}

template<typename T>
List<T>::List(const List<T>& list) {
    _size = list.size();
    _head = nullptr;
    if (_size > 0) {
        List<T>::Node* temp = list._head;
        List<T>::Node* tempNew = new List<T>::Node(temp->value);
        List<T>::Node* nextNew = nullptr; 
        _head = tempNew;
        temp = temp->next;
        while (temp != nullptr) {
            nextNew = new List<T>::Node(temp->value); 
            tempNew->next = nextNew;
            tempNew = nextNew;
            temp = temp->next;
        }
    }
}

template<typename T>
List<T>::List(List<T>&& list) {
    _size = list.size();
    _head = list._head;
    list._head = nullptr;
    list._size = 0;
}


template<typename T>
List<T>::~List() {
    this->clear();
}


template<typename T>
List<T>& List<T>::operator=(const List<T>& list) {
    this->clear();

    _size = list.size();
    _head = nullptr;
    if (_size > 0) {
        List<T>::Node* temp = list._head;
        List<T>::Node* tempNew = new List<T>::Node(temp->value);
        List<T>::Node* nextNew = nullptr; 
        _head = tempNew;
        temp = temp->next;
        while (temp != nullptr) {
            nextNew = new List<T>::Node(temp->value); 
            tempNew->next = nextNew;
            tempNew = nextNew;
            temp = temp->next;
        }
    }

    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& list) {
    this->clear();
    _size = list.size();
    _head = list._head;
    list._head = nullptr;
    list._size = 0;

    return *this;
}


template<typename T>
T& List<T>::at(size_t idx) {
    if (idx >= size()) {
        throw std::out_of_range("At out of range of list");
    }

    size_t tempPos = 0;
    List<T>::Node* temp = _head; 
    while (tempPos < idx) {
        temp = temp->next;
        tempPos++;
    }
    return temp->value;
}

template<typename T>
const T& List<T>::at(size_t idx) const {
    if (idx >= size()) {
        throw std::out_of_range("At out of range of list");
    }

    size_t tempPos = 0;
    List<T>::Node* temp = _head; 
    while (tempPos < idx) {
        temp = temp->next;
        tempPos++;
    }
    return temp->value;
}

template<typename T>
T& List<T>::operator[](size_t idx) {
    return this->at(idx);
}

template<typename T>
const T& List<T>::operator[](size_t idx) const {
    return this->at(idx);
}


template<typename T>
void List<T>::pushBack(const T& value) {
    this->insert(size(), value);
}

template<typename T>
void List<T>::pushFront(const T& value) {
    List<T>::Node* newNode = new List<T>::Node(value, _head);
    _head = newNode;
    _size++;
}

template<typename T>
void List<T>::insert(size_t pos, const T& value) {
    if (pos > size()) {
        throw std::out_of_range("Insert out of range of list");
    }
    
    if (pos == 0) {
        this->pushFront(value);
        return;
    }
    size_t tempPos = 1;
    List<T>::Node* temp = _head;
    while (tempPos < pos) {
        temp = temp->next;   
        ++tempPos;
    }

    List<T>::Node* newNode = new List<T>::Node(value, temp->next);
    temp->next = newNode;
    ++_size;
}


template<typename T>
void List<T>::insert(const typename List<T>::Iterator& it, const T& value) {
    if (it.getPtr() == nullptr) {
        throw std::out_of_range("Insert out of range of list");
    }
    this->insert(it.getIndex(), value);
}


template<typename T>
void List<T>::popBack() {
    this->erase(size() - 1);
}

template<typename T>
void List<T>::popFront() {
    if (size() == 0) {
        throw std::out_of_range("popFront out of range");
    }

    List<T>::Node* deleted = _head;
    _head = _head->next;
    delete deleted;
    --_size;
}

template<typename T>
void List<T>::erase(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("erase out of range");
    }

    if (pos == 0) {
        this->popFront();
        return;
    }
    size_t tempPos = 1;
    List<T>::Node* temp = _head->next;
    List<T>::Node* prev = _head;
    while (tempPos < pos) {
        prev = temp;
        temp = temp->next;   
        ++tempPos;
    }
    
    prev->next = temp->next;
    delete temp;
    --_size;
}

template<typename T>
void List<T>::erase(const typename List<T>::Iterator& it) {
    if (it.getPtr() == nullptr) {
        throw std::out_of_range("erase out of range");
    }
    this->erase(it.getIndex());
}


template<typename T>
void List<T>::forEach(void (*func)(T&)) {
    List<T>::Node* temp = _head;
    while (temp != nullptr) {
        func(temp->value);
        temp = temp->next;
    }
}

template<typename T>
void List<T>::map(T (*func)(T)) {
    List<T>::Node* temp = _head;
    while (temp != nullptr) {
        temp->value = func(temp->value);
        temp = temp->next;
    }
}

template<typename T>
void List<T>::reverse() {
    List<T>::Node* prev = nullptr;
    List<T>::Node* temp = _head;
    while (temp != nullptr) {
        List<T>::Node* saveNext = temp->next; 
        temp->next = prev; 
        prev = temp;
        temp = saveNext; 
    }
    _head = prev;
}

template<typename T>
List<T> List<T>::reversed() const {
    List<T> newList = *this;
    newList.reverse();
    return newList;
}

template<typename T>
void List<T>::clear() {
    while (_head != nullptr) {
        this->popFront();
    }
    _size = 0;
}

template<typename T>
size_t List<T>::size() const {
    return _size;
}


template<typename T>
List<T>::Iterator::Iterator(List<T>::Node* ptr, size_t idx) 
    : _ptr(ptr), _idx(idx) {}

template<typename T>
List<T>::Iterator::Iterator(const Iterator& other)
    : _ptr(other._ptr), _idx(other._idx) {}


template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& other) {
    _ptr = other._ptr;
    _idx = other._idx;

    return *this;
}

template<typename T>
T& List<T>::Iterator::operator*() const {
    return _ptr->value;
}

template<typename T>
bool List<T>::Iterator::operator!=(const typename List<T>::Iterator& other) const {
    return (this->_ptr != other._ptr);
}

template<typename T>
bool List<T>::Iterator::operator==(const typename List<T>::Iterator& other) const {
    return !(*this != other);
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    this->_ptr = this->_ptr->next;
    this->_idx++;
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
size_t List<T>::Iterator::getIndex() const {
    return this->_idx;
}

template<typename T>
typename List<T>::Node* List<T>::Iterator::getPtr() const {
    return _ptr;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(_head, 0);
}

template<typename T>
typename List<T>::Iterator List<T>::end() noexcept {
    return Iterator(nullptr, -1); 
}

template class List<int>;
template class List<float>;
template class List<double>;
template class List<char>;
template class List<char*>;

#pragma once

#include "../BinarySearchTree/BinarySearchTree.h"

#include <cstddef>
#include <iostream>

template<class T, template<class> class Container = BinarySearchTree>
class Set {
private:
    Container<T> _container;
    size_t _size;
public:
    struct Iterator {
    public:
        Iterator(const typename Container<T>::Iterator& 
                                    iter = typename Container<T>::Iterator());
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
        typename Container<T>::Iterator _iter;
    };

    Set() = default;
    Set(const Set<T, Container>& other);
    Set(Set<T, Container>&& other) noexcept;
    Set& operator=(const Set<T, Container>& other);
    Set& operator=(Set<T, Container>&& other) noexcept;

    ~Set() = default;

    void add(const T& value);
    void remove(const T& value); 
    void print();

    size_t size() const;
    bool isEmpty() const;

    Iterator begin();
    Iterator end() noexcept;
};

template<class T, template<class> class Container>
Set<T, Container>::Set(const Set<T, Container>& other)
    : _container(other._container) {}

template<class T, template<class> class Container>
Set<T, Container>::Set(Set<T, Container>&& other) noexcept
    : _container(std::move(other._container)) {}

template<class T, template<class> class Container>
Set<T, Container>& Set<T, Container>::operator=(const Set<T, Container>& other) {
    _container = other._container; 
}

template<class T, template<class> class Container>
Set<T, Container>& Set<T, Container>::operator=(
                                        Set<T, Container>&& other) noexcept
{
    _container = std::move(other._container); 
}

template<class T, template<class> class Container>
void Set<T, Container>::add(const T& value) {
    if (_container.find(value) == _container.end()) {
        _container.add(value);
    }
}
    
template<class T, template<class> class Container>
void Set<T, Container>::remove(const T& value) {
    _container.remove(value);
}

template<class T, template<class> class Container>
size_t Set<T, Container>::size() const {
    return _container.size();
}

template<class T, template<class> class Container>
bool Set<T, Container>::isEmpty() const {
    return (this->size() == 0);
}

template<class T, template<class> class Container>
void Set<T, Container>::print() {
    _container.print();
}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator Set<T, Container>::begin() {
    return Iterator(_container.begin());
}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator Set<T, Container>::end() noexcept {
    return Iterator(_container.end());
}


/* Iterator methods */
template<class T, template<class> class Container>
Set<T, Container>::Iterator::Iterator(
                                    const typename Container<T>::Iterator&iter)
    : _iter(iter) {}

template<class T, template<class> class Container>
Set<T, Container>::Iterator::Iterator(const Iterator& other)
    : _iter(other._iter) {}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator& Set<T, Container>::Iterator::operator=(
                                                    const Iterator& other)
{
    _iter = other._iter;

    return *this;
}

template<class T, template<class> class Container>
const T& Set<T, Container>::Iterator::operator*() const {
    return *_iter;
}

template<class T, template<class> class Container>
bool Set<T, Container>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template<class T, template<class> class Container>
bool Set<T, Container>::Iterator::operator==(const Iterator& other) const {
    return (_iter == other._iter);
}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator& Set<T, Container>::Iterator::operator++() 
{
    ++(_iter);
    return *this;
}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator 
                            Set<T, Container>::Iterator::operator++(int)
{
    Iterator oldIter = *this;
    ++(*this);
    return oldIter;
}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator& Set<T, Container>::Iterator::operator--()
{
    --(_iter);
    return *this;
}

template<class T, template<class> class Container>
typename Set<T, Container>::Iterator Set<T, Container>::Iterator::operator--(int) {
    Iterator oldIter = *this;
    --(*this);
    return oldIter;
}

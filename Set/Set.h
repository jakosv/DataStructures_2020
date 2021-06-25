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
    Set() = default;
    Set(const Set<T, Container>& other);
    Set(Set<T, Container>&& other) noexcept;
    Set& operator=(const Set<T, Container>& other);
    Set& operator=(Set<T, Container>&& other) noexcept;

    ~Set() = default;

    void add(const T& value);
    void remove(const T& value); 

    size_t size() const;
    bool isEmpty() const;
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
Set<T, Container>& Set<T, Container>::operator=(Set<T, Container>&& other) noexcept {
    _container = std::move(other._container); 
}

template<class T, template<class> class Container>
void Set<T, Container>::add(const T& value) {
    _container.add(value);
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

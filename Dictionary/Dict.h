#pragma once

#include "../BinarySearchTree/BinarySearchTree.h"
#include "../Pair/Pair.h"

#include <cstddef>
#include <iostream>

template<class KeyType, class ValueType, 
                            template<class> class Container = BinarySearchTree>
class Dict {
private:
    Container< Pair<KeyType, ValueType> > _container;
public:
    struct Iterator {
    public:
        Iterator(const typename Container<Pair<KeyType, ValueType>>::Iterator&
                iter = typename Container<Pair<KeyType, ValueType>>::Iterator());
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        const Pair<KeyType, ValueType>& operator*() const;
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
    private:
        typename Container<Pair<KeyType, ValueType>>::Iterator _iter;
    };

    Dict() = default;
    Dict(const Dict& other);
    Dict(Dict&& other);
    Dict& operator=(const Dict& other);
    Dict& operator=(Dict&& other);
    ~Dict() = default;

    const ValueType& operator[](const KeyType& key);

    void addKey(const KeyType& key);
    void setValue(const KeyType& key, const ValueType& value);
    void removeKey(const KeyType& key);
    const ValueType& get(const KeyType& key);
    bool hasKey(const KeyType& key);

    size_t size() const;
    void clear();

    Iterator begin();
    Iterator end() noexcept;
};


template<class KeyType, class ValueType, template<class> class Container>
Dict<KeyType, ValueType, Container>::Dict(const Dict& other) {
    _container = other._container;
}

template<class KeyType, class ValueType, template<class> class Container>
Dict<KeyType, ValueType, Container>::Dict(Dict&& other) {
    _container = std::move(other._container);
}

template<class KeyType, class ValueType, template<class> class Container>
Dict<KeyType, ValueType, Container>& Dict<KeyType, ValueType,
                                    Container>::operator=(const Dict& other)
{
    _container = other._container;
    return *this;
}

template<class KeyType, class ValueType, template<class> class Container>
Dict<KeyType, ValueType, Container>& Dict<KeyType, ValueType, 
                                        Container>::operator=(Dict&& other)
{
    _container = std::move(other._container);
    return *this;
}


template<class KeyType, class ValueType, template<class> class Container>
void Dict<KeyType, ValueType, Container>::addKey(const KeyType& key) {
    if (!hasKey(key)) {
        Pair<KeyType, ValueType> val(key);
        _container.add(val);
    }
}

template<class KeyType, class ValueType, template<class> class Container>
void Dict<KeyType, ValueType, Container>::removeKey(const KeyType& key) {
    Pair<KeyType, ValueType> val(key);
    _container.remove(val);
}

template<class KeyType, class ValueType, template<class> class Container>
void Dict<KeyType, ValueType, Container>::setValue(
                                const KeyType& key, const ValueType& value)
{
    Pair<KeyType, ValueType> val(key);
    if (!hasKey(key)) {
        val.value = value;
        _container.add(val);
    }
    else {
        _container.remove(val);
        val.value = value;
        _container.add(val);
    }
}

template<class KeyType, class ValueType, template<class> class Container>
const ValueType& Dict<KeyType, ValueType, Container>::operator[](
                                                        const KeyType& key)
{
    return get(key);
}


template<class KeyType, class ValueType, template<class> class Container>
const ValueType& Dict<KeyType, ValueType, Container>::get(
                                                    const KeyType& key)
{
    Pair<KeyType, ValueType> val(key);
    if (!hasKey(key)) {
        _container.add(val);
    }
    return (*_container.find(val)).value;
}

template<class KeyType, class ValueType, template<class> class Container>
bool Dict<KeyType, ValueType, Container>::hasKey(const KeyType& key) {
    Pair<KeyType, ValueType> val(key);
    typename Container<Pair<KeyType, ValueType>>::Iterator it = 
                                                        _container.find(val);
    bool has = (it != _container.end());
    return has;
}

template<class KeyType, class ValueType, template<class> class Container>
void Dict<KeyType, ValueType, Container>::clear() {
    _container.clear();
}

template<class KeyType, class ValueType, template<class> class Container>
size_t Dict<KeyType, ValueType, Container>::size() const {
    return _container.size();
}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator 
                                Dict<KeyType, ValueType, Container>::begin()
{
    return Iterator(_container.begin());
}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator
                        Dict<KeyType, ValueType, Container>::end() noexcept
{
    return Iterator(_container.end());
}


/* Iterator methods */
template<class KeyType, class ValueType, template<class> class Container>
Dict<KeyType, ValueType, Container>::Iterator::Iterator(
        const typename Container<Pair<KeyType, ValueType>>::Iterator& iter)
    : _iter(iter) {}

template<class KeyType, class ValueType, template<class> class Container>
Dict<KeyType, ValueType, Container>::Iterator::Iterator(const Iterator& other)
    : _iter(other._iter) {}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator& 
                    Dict<KeyType, ValueType, Container>::Iterator::operator=(
                                                const Iterator& other)
{
    _iter = other._iter;
}

template<class KeyType, class ValueType, template<class> class Container>
const Pair<KeyType, ValueType>& 
            Dict<KeyType, ValueType, Container>::Iterator::operator*() const 
{
    return *(_iter);
}

template<class KeyType, class ValueType, template<class> class Container>
bool Dict<KeyType, ValueType, Container>::Iterator::operator!=(
                                                const Iterator& other) const
{
    return (_iter != other._iter);
}

template<class KeyType, class ValueType, template<class> class Container>
bool Dict<KeyType, ValueType, Container>::Iterator::operator==(
                                                const Iterator& other) const
{
    return (_iter == other._iter);
}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator& 
                    Dict<KeyType, ValueType, Container>::Iterator::operator++()
{
    ++(_iter);
    return *this;
}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator
                Dict<KeyType, ValueType, Container>::Iterator::operator++(int) 
{
    Iterator oldIter(_iter);
    ++(*this);
    return oldIter;
}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator& 
                Dict<KeyType, ValueType, Container>::Iterator::operator--() 
{
    --(_iter);
    return *this;
}

template<class KeyType, class ValueType, template<class> class Container>
typename Dict<KeyType, ValueType, Container>::Iterator 
            Dict<KeyType, ValueType, Container>::Iterator::operator--(int)
{
    Iterator oldIter(_iter);
    --(*this);
    return oldIter;
}

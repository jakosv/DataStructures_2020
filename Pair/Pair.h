#pragma once

#include <iostream>

template<class KeyType, class ValueType>
class Pair {
public:
    KeyType key;
    ValueType value;

    Pair(const KeyType& key = KeyType(), const ValueType& value = ValueType());
    Pair(const Pair& other);
    Pair(Pair&& other);
    Pair& operator=(const Pair& other);
    Pair& operator=(Pair&& other);
    ~Pair() = default;

    bool operator==(const Pair& other);
    bool operator!=(const Pair& other);
    bool operator<(const Pair& other);
    bool operator<=(const Pair& other);
    bool operator>(const Pair& other);
    bool operator>=(const Pair& other);
};


template<class KeyType, class ValueType>
Pair<KeyType, ValueType>::Pair(const KeyType& key, const ValueType& value)
    : key(key), value(value) {}

template<class KeyType, class ValueType>
Pair<KeyType, ValueType>::Pair(const Pair& other) {
    key = other.key;
    value = other.value;
}

template<class KeyType, class ValueType>
Pair<KeyType, ValueType>::Pair(Pair&& other) {
    key = std::move(other.key);
    value = std::move(other.value);
}

template<class KeyType, class ValueType>
Pair<KeyType, ValueType>& Pair<KeyType, ValueType>::operator=(const Pair& other)
{
    key = other.key;
    value = other.value;
    return *this;
}

template<class KeyType, class ValueType>
Pair<KeyType, ValueType>& Pair<KeyType, ValueType>::operator=(Pair&& other)
{
    key = std::move(other.key);
    value = std::move(other.value);
    return *this;
}


template<class KeyType, class ValueType>
bool Pair<KeyType, ValueType>::operator==(const Pair& other) {
    return (key == other.key);
}

template<class KeyType, class ValueType>
bool Pair<KeyType, ValueType>::operator!=(const Pair& other) {
    return !(*this == other);
}

template<class KeyType, class ValueType>
bool Pair<KeyType, ValueType>::operator<(const Pair& other) {
    return key < other.key;
}

template<class KeyType, class ValueType>
bool Pair<KeyType, ValueType>::operator<=(const Pair& other) {
    return (*this < other || *this == other);
}

template<class KeyType, class ValueType>
bool Pair<KeyType, ValueType>::operator>(const Pair& other) {
    return !(*this <= other);
}

template<class KeyType, class ValueType>
bool Pair<KeyType, ValueType>::operator>=(const Pair& other) {
    return !(*this < other);
}


template<class KeyType, class ValueType>
std::ostream& operator<<(std::ostream& out, 
                                        const Pair<KeyType, ValueType>& pair)
{
    out << pair.key << " " << pair.value;
    return out;
}

template<class KeyType, class ValueType>
std::istream& operator>>(std::istream& in, Pair<KeyType, ValueType>& pair) 
{
    in >> pair.key >> pair.value;
    return in;
}

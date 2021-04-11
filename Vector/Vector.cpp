#include "Vector.h"

#include <stdexcept>

Vector::Vector(const size_t size) {
    _size = size;
    _data = nullptr;
    if (_size > 0) {
        _data = new ValueType[size];
    }
}

Vector::Vector(Vector& vector) {
    _size = vector.size();
    _data = nullptr;
    if (_size > 0) {
        _data = new ValueType[_size];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = vector[i];
        }
    }
}

Vector::Vector(Vector&& vector) noexcept {
    _size = vector.size();
    _data = vector._data;
    vector._size = 0;
    vector._data = nullptr; 
}


Vector::~Vector() {
    _size = 0;
    delete[] _data;
}


ValueType& Vector::at(const size_t idx) {
    if (idx >= size()) {
        throw std::out_of_range("Out of range");
    }
    return _data[idx];
}

const ValueType& Vector::at(const size_t idx) const {
    if (idx >= size()) {
        throw std::out_of_range("Out of range");
    }
    return _data[idx];
}

ValueType& Vector::operator[](const size_t idx) {
    return _data[idx];
}

const ValueType& Vector::operator[](const size_t idx) const {
    return _data[idx];
}


void Vector::insert(const ValueType& value, const size_t idx) {
    if (idx > size()) {
        throw std::out_of_range("Out of range");
    }

    ValueType* newData = new ValueType[size() + 1];
    for (size_t i = 0; i < size() + 1; i++) {
        if (i < idx) {
            newData[i] = this->at(i);
        }
        else if (i > idx){
            newData[i] = this->at(i - 1);
        }
    }
    newData[idx] = value;
    _size = _size + 1;
    delete[] _data;
    _data = newData;
}

void Vector::pushBack(const ValueType& value) {
    this->insert(value, size());
}

void Vector::pushFront(const ValueType& value) {
    this->insert(value, 0);
}


void Vector::clear() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
}

void Vector::erase(const size_t idx) {
    this->erase(idx, 1);
}
    
void Vector::erase(const size_t idx, const size_t len) {
    if (idx >= size()) {
        throw std::out_of_range("Out of range in erase");
    }

    size_t realLen = len;
    if (idx + len  - 1 >= size()) {
        realLen = size() - idx;
    }
    size_t newSize = size() - realLen;
    ValueType* newData = new ValueType[newSize];
    for (size_t i = 0; i < idx; i++) {
        newData[i] = this->at(i);
    }
    for (size_t i = idx; i < newSize; i++) {
        newData[i] = this->at(i + realLen);
    }
    _size = newSize;
    delete[] _data;
    _data = newData;
}
    
void Vector::popBack() {
    if (size() == 0) {
        throw std::out_of_range("popBack from empty vector");
    }
    this->erase(size() - 1);
}


size_t Vector::size() const {
    return _size;
}


size_t Vector::find(const ValueType& value) const {
    size_t res = -1;
    for (size_t i = 0; i < size(); ++i) {
        if (this->at(i) == value) {
            res = i;
        }
    }
    return res;
}

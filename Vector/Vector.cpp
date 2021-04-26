#include "Vector.h"

#include <stdexcept>

Vector::Vector(const size_t size) {
    _size = size;
    _capacity = 1;
    if (_size > 0) {
        _capacity = _size * ResizeFactor;
    }
    _data = new ValueType[_capacity];
}

Vector::Vector(Vector& vector) {
    _size = vector.size();
    _capacity = vector._capacity;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = vector[i];
    }
}

Vector::Vector(Vector&& vector) noexcept {
    _size = vector.size();
    _capacity = vector._capacity;
    _data = vector._data;
    vector._size = 0;
    vector._data = nullptr; 
    vector._capacity = 0;
}


Vector::~Vector() {
    _size = 0;
    _capacity = 0;
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


void Vector::insert(const size_t idx, const ValueType& value) {
    if (idx > size()) {
        throw std::out_of_range("Insert out of range");
    }

    bool reallocation = false;
    ValueType* data = _data;
    if (_size == _capacity) {
        reallocation = true;
        _capacity *= ResizeFactor;
        data = new ValueType[_capacity];
        for (size_t i = 0; i < idx; i++) {
            data[i] = this->at(i);
        }
    }
    for (int i = size(); i > idx; i--) {
        data[i] = this->at(i - 1);
    }
    if (reallocation) {
        delete[] _data;
        _data = data;
    }
    _size = _size + 1;
    this->at(idx) = value;
}

void Vector::pushBack(const ValueType& value) {
    this->insert(size(), value);
}

void Vector::pushFront(const ValueType& value) {
    this->insert(0, value);
}


void Vector::clear() {
    delete[] _data;
    _size = 0;
    _capacity = 1;
    _data = new ValueType[_capacity];
}

void Vector::erase(const size_t idx) {
    this->erase(idx, 1);
}
    
void Vector::erase(const size_t idx, const size_t len) {
    if (idx >= size()) {
        throw std::out_of_range("Out of range in erase");
    }

    size_t realLen = len;
    if (idx + len - 1 >= size()) {
        realLen = size() - idx;
    }
    size_t newSize = size() - realLen;
    bool reallocation = false;
    ValueType* data = _data;

    if (1.0 * newSize / _capacity <= SizeFactor) {
        reallocation = true;
        _capacity /= ResizeFactor;
        data = new ValueType[_capacity];
        for (size_t i = 0; i < idx; i++) {
            data[i] = this->at(i);
        }
    }
    for (size_t i = idx; i < newSize; i++) {
        data[i] = this->at(i + realLen);
    }

    if (reallocation) {
        delete[] _data;
        _data = data;
    }
    _size = newSize;
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


Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

ValueType& Vector::Iterator::operator*() {
    return *_ptr;
}

ValueType* Vector::Iterator::operator->() {
    return _ptr;
}

// prefix
Vector::Iterator& Vector::Iterator::operator++() {
    _ptr++;
    return *this;
}

// postfix
Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) {
    return _ptr != other._ptr;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) {
    return !(*this != other);
}

std::ptrdiff_t Vector::Iterator::operator-(const Vector::Iterator& other) {
    return _ptr - other._ptr;
}

Vector::Iterator Vector::begin() {
    return Vector::Iterator(&_data[0]);
}

Vector::Iterator Vector::end() noexcept {
    return Vector::Iterator(&_data[size()]);
}

#pragma once

#include <cstddef>

#include "IVector.h"

const size_t ResizeFactor = 2;
const double SizeFactor = 1.0 / (ResizeFactor * ResizeFactor);

class Vector: public IVector {
private:
    size_t _capacity;
    size_t _size;
    ValueType* _data;
public:
    
    struct Iterator {
    public:
        Iterator(ValueType* ptr);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);

        ValueType& operator*() const;
        // prefix
        Iterator& operator++();
        // postfix
        Iterator operator++(int);
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;
        std::ptrdiff_t operator-(const Iterator& other) const;

        ValueType* getPtr() const;
    private:
        ValueType* _ptr;
    };
    
    Iterator begin() const;
    Iterator end() const noexcept;

    Vector(const size_t size = 0);
    Vector(Vector& vector);
    Vector(Vector&& vector) noexcept;

    ~Vector();

    ValueType& at(const size_t idx) override;
    const ValueType& at(const size_t idx) const override;
    ValueType& operator[](const size_t idx) override;
    const ValueType& operator[](const size_t idx) const override;

    void pushBack(const ValueType& value) override;
    void pushFront(const ValueType& value) override;
    void insert(const size_t idx, const ValueType& value) override;
    void insert(const Iterator& it, const ValueType& value);
    
    void clear() override;
    void erase(const size_t idx) override;
    void erase(const size_t idx, const size_t len) override;
    void erase(const Iterator& it);
    void popBack() override;
    
    size_t size() const override;
    
    size_t find(const ValueType& value) const override;
};

#pragma once

#include <cstddef>

#include "IVector.h"

class Vector: public IVector {
private:
    size_t _size;
    ValueType* _data;
public:
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
    void insert(const ValueType& value, const size_t idx) override;
    
    void clear() override;
    void erase(const size_t idx) override;
    void erase(const size_t idx, const size_t len) override;
    void popBack() override;
    
    size_t size() const override;
    
    size_t find(const ValueType& value) const override;
};

#pragma once

#include "StackImplementation.h"
#include "../SingleLinkedList/List.h"

class ListStack : public StackImplementation {
public:
    ListStack();
    ListStack(const ListStack& copyListStack);
    ListStack& operator=(const ListStack& copyListStack);
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;
    ~ListStack() = default;
private:
    List<ValueType> _list; 
};

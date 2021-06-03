#include "ListStack.h"

ListStack::ListStack() : _list() {}

ListStack::ListStack(const ListStack& copyListStack) 
    : _list(copyListStack._list) {}

ListStack& ListStack::operator=(const ListStack& copyListStack) {
    this->_list = copyListStack._list;

    return *this;
}

void ListStack::push(const ValueType& value) {
    _list.pushFront(value); 
}

void ListStack::pop() {
    _list.popFront();
}

const ValueType& ListStack::top() const {
    return _list[0];
}

bool ListStack::isEmpty() const {
    return (_list.size() == 0);
}

size_t ListStack::size() const {
    return _list.size();
}

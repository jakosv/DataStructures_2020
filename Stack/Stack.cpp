#include "Stack.h"
#include "ListStack.h"
#include "StackImplementation.h"

#include <stdexcept>

Stack::Stack(StackContainer container) {
    switch (container) {
        case StackContainer::List:
            _pimpl = new ListStack();
            break;
        
        case StackContainer::Vector:
            break;

        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}
Stack::Stack(const ValueType* valueArray, const size_t arraySize,
        StackContainer container)
{
    switch (container) {
        case StackContainer::List:
            _pimpl = new ListStack();
            break;
        
        case StackContainer::Vector:
            break;

        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(const Stack& copyStack) {
    switch (copyStack._containerType) {
        case StackContainer::List:
            _pimpl = new ListStack(
                    *static_cast<ListStack*>(copyStack._pimpl));
            break;
        
        case StackContainer::Vector:
            break;

        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }

    _containerType = copyStack._containerType;
}
    
Stack& Stack::operator=(const Stack& copyStack) {
    delete _pimpl;

    Stack copy(copyStack);
    _pimpl = copy._pimpl;
    _containerType = copy._containerType;

    return *this;
}

Stack::~Stack() {
    delete _pimpl;
}

void Stack::push(const ValueType& value) {
    _pimpl->push(value);
}

void Stack::pop() {
    _pimpl->pop();
}

const ValueType& Stack::top() const {
    return _pimpl->top();
}

bool Stack::isEmpty() const {
    return _pimpl->isEmpty();
}

size_t Stack::size() const {
    return _pimpl->size();
}


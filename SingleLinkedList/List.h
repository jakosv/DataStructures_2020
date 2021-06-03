#pragma once

#include "IList.h"
#include <sstream>

template<typename T>
class List: public IList<T> {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& value, Node* next = nullptr);
    };

    Node* _head;
    size_t _size;

public:
    struct Iterator {
    public:
        Iterator(Node* ptr, size_t idx = 0);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        T& operator*() const;
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);

        size_t getIndex() const;
        Node* getPtr() const;
    private:
        Node* _ptr;
        size_t _idx;
    };

    Iterator begin();
    Iterator end() noexcept;

    List();
    List(const T& value);
    List(const List& list);
    List(List&& list);

    ~List();

    List& operator=(const List& list);
    List& operator=(List&& list);

    T& at(size_t idx) override;
    const T& at(size_t idx) const override;
    T& operator[](size_t idx) override;
    const T& operator[](size_t idx) const override;

    void pushBack(const T& value) override;
    void pushFront(const T& value) override;
    void insert(size_t pos, const T& value) override; 
    void insert(const Iterator& it, const T& value); 

    void popBack() override;
    void popFront() override;
    void erase(size_t pos) override;
    void erase(const Iterator& it);

    void forEach(void (*func)(T&));
    void map(T (*func)(T));
    void reverse() override;
    List reversed() const;

    void clear() override;

    size_t size() const override;
};

#include <cstdlib>

template<typename T>
class IList {
public:
    virtual T& at(size_t idx) = 0;
    virtual const T& at(size_t idx) const = 0;
    virtual T& operator[](size_t idx) = 0;
    virtual const T& operator[](size_t idx) const = 0;

    virtual void pushBack(const T& value) = 0;
    virtual void pushFront(const T& value) = 0;
    virtual void insert(size_t pos, const T& value) = 0; 

    virtual void popBack() = 0;
    virtual void popFront() = 0;
    virtual void erase(size_t pos) = 0;

    virtual void reverse() = 0;

    virtual void clear() = 0;
    virtual size_t size() const = 0;

};

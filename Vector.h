#ifndef FT_CONTAINERS_VECTOR_H
#define FT_CONTAINERS_VECTOR_H

#include <iostream>
#include <assert.h>

template <class T, class Allocator = std::allocator<T> >
class Vector {
private:
    T *arr;
    size_t size;
    size_t capacity;
public:
    Vector(const Allocator& alloc = Allocator()) : size(0), capacity(0){} //default - read about allocators
    Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : size(), capacity(count) {
        assert(sz > 0)
    }

};



#endif

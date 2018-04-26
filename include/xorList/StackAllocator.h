#pragma once
#include <memory>
#include "BufferManager.h"

template <typename T>
class StackAllocator{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    template <typename U>
    struct rebind{
        using other = StackAllocator<U>;
    };

    StackAllocator();
    StackAllocator(const StackAllocator& other);
    ~StackAllocator() = default;
    pointer allocate(size_t size);
    void deallocate(pointer p, size_t n);
private:
    std::shared_ptr<BufferManager<T>> bufferManager;
};

#include "StackAllocator.ipp"
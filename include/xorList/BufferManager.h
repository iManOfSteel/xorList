#pragma once
#include <memory>
#include "xorList/Buffer.h"
template <typename T>
class BufferManager{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    BufferManager();
    pointer allocate(size_t size);
    ~BufferManager();
private:
    size_t curPos;
    Buffer<T>* buffer;
};

#include "BufferManager.ipp"
#pragma once
#include <memory>

template <typename T>
class BufferManager{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    BufferManager();
    pointer allocate(size_t size);
private:
    const size_t maxBufferSize = 100;
    size_t curPos;
    std::shared_ptr<T> buffer;
};

#include "BufferManager.ipp"
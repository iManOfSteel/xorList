#pragma once

#include <memory>

template<typename T>
class Buffer {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    Buffer (Buffer* prev=nullptr):
            prev(prev),
            buffer(std::shared_ptr<T>(static_cast<pointer>(operator new(sizeof(T) * maxBufferSize)))) {};
    ~Buffer() {
        while (prev) {
            Buffer* tmp = prev->prev;
            prev->prev = NULL;
            delete prev;
            prev = tmp;
        }
    }
    static const size_t maxBufferSize = 30000;
    Buffer* prev;
    std::shared_ptr<T> buffer;
};
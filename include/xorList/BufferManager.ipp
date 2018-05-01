#pragma once
#include "BufferManager.h"
#include <iostream>

template <typename T>
BufferManager<T>::BufferManager() {
    curPos = 0;
    buffer = std::shared_ptr<T>(static_cast<pointer>(operator new(sizeof(T) * maxBufferSize)));
}

template<typename T>
typename BufferManager<T>::pointer BufferManager<T>::allocate(size_t size) {
    if(size + curPos > maxBufferSize) {
        buffer = std::shared_ptr<T>(buffer, static_cast<pointer>(operator new(sizeof(T) * maxBufferSize)));
        curPos = 0;
    }
    curPos += size;
    return buffer.get() + (curPos - size);
}
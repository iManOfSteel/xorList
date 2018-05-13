#pragma once
#include "BufferManager.h"
#include "Buffer.h"
#include <iostream>

template <typename T>
BufferManager<T>::BufferManager() {
    curPos = 0;
    buffer = new Buffer<T>();
}

template<typename T>
BufferManager<T>::~BufferManager() {
    delete buffer;
}

template<typename T>
typename BufferManager<T>::pointer BufferManager<T>::allocate(size_t size) {
    if(size + curPos > buffer->maxBufferSize) {
        buffer = new Buffer<T>(buffer);
        curPos = 0;
    }
    curPos += size;
    return buffer->buffer + (curPos - size);
}
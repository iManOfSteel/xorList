#pragma once
#include "StackAllocator.h"

template <typename T>
StackAllocator<T>::StackAllocator() {
    bufferManager = std::make_shared<BufferManager<T>>();
}

template <typename T>
StackAllocator<T>::StackAllocator(const StackAllocator &other) {
    bufferManager = other.bufferManager;
}

template <typename T>
typename StackAllocator<T>::pointer StackAllocator<T>::allocate(size_t size) {
    return bufferManager->allocate(size);
}

template <typename T>
void StackAllocator<T>::deallocate(StackAllocator<T>::pointer p, size_t n) {}
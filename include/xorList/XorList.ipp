#pragma once
#include "XorList.h"

template<typename T, typename Allocator>
XorList<T, Allocator>::XorList(const Allocator& alloc):
        alloc(XorList<T, Allocator>::ItemAllocator()), _size(0), first(nullptr), last(nullptr) {}

template<typename T, typename Allocator>
XorList<T, Allocator>::XorList(size_t count, const T &value, const Allocator &alloc):
        alloc(XorList<T, Allocator>::ItemAllocator()), _size(0), first(nullptr), last(nullptr) {
    for (size_t i = 0; i < count; ++i)
        push_back(value);
}


template<typename T, typename Allocator>
XorList<T, Allocator>::XorList(const XorList &other) {
    *this = other;
}


template<typename T, typename Allocator>
XorList<T, Allocator>::XorList(XorList &&other): alloc(other.alloc), first(other.first),
                                                 last(other.last), _size(other.size()) {}

template<typename T, typename Allocator>
XorList<T, Allocator>::~XorList() {
    while(_size)
        pop_back();
}

template<typename T, typename Allocator>
XorList<T, Allocator>& XorList<T, Allocator>::operator=(const XorList& other) {
    alloc(other.alloc);
    _size = 0;
    first = last = nullptr;
    for (XorList<T, Allocator>::const_iterator it = other.cbegin(); it != other.cend(); ++it)
        push_back(*it);
    return *this;
}

template<typename T, typename Allocator>
XorList<T, Allocator>& XorList<T, Allocator>::operator=(XorList&& other) {
    alloc(other.alloc);
    first = other.first;
    last = other.last;
    _size = other.size();
    return (*this);
}

template<typename T, typename Allocator>
size_t XorList<T, Allocator>::size() const {
    return _size;
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::push_back(const T &val) {
    item *loc = alloc.allocate(1);
    if (_size)
        last = last->insert_after(val, loc, reinterpret_cast<item*>(last->ptr));
    else
        first = last = new(loc) item(val, nullptr, nullptr);
    _size++;
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::push_back(T&& val) {
    item *loc = alloc.allocate(1);
    if (_size)
        last = last->insert_after(std::move(val), loc, reinterpret_cast<item*>(last->ptr));
    else
        first = last = new(loc) item(std::move(val), nullptr, nullptr);
    _size++;
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::push_front(const T &val) {
    item *loc = alloc.allocate(1);
    if (_size)
        first = first->insert_before(val, loc, nullptr);
    else
        first = last = new(loc) item(val, nullptr, nullptr);
    _size++;
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::push_front(T&& val) {
    item *loc = alloc.allocate(1);
    if (_size)
        first = first->insert_before(std::move(val), loc, nullptr);
    else
        first = last = new(loc) item(std::move(val), nullptr, nullptr);
    _size++;
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::pop_back() {
    item* newLast = last->other(nullptr);
    if (newLast)
        newLast->ptr ^= reinterpret_cast<uintptr_t>(last);
    last->~XorListItem();
    alloc.deallocate(last, 1);
    if (first == last)
        first = newLast;
    last = newLast;
    _size--;
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::pop_front() {
    item* newFirst = first->other(nullptr);
    if (newFirst)
        newFirst->ptr ^= reinterpret_cast<uintptr_t>(first);
    first->~XorListItem();
    alloc.deallocate(first, 1);
    if (first == last)
        last = newFirst;
    first = newFirst;
    _size--;
}

template<typename T, typename Allocator>
typename XorList<T, Allocator>::iterator XorList<T, Allocator>::begin() {
    return XorList<T, Allocator>::iterator(nullptr, first);
}

template<typename T, typename Allocator>
typename XorList<T, Allocator>::iterator XorList<T, Allocator>::end() {
    return XorList<T, Allocator>::iterator(last, nullptr);
}

template<typename T, typename Allocator>
typename XorList<T, Allocator>::const_iterator XorList<T, Allocator>::cbegin() const {
    return XorList<T, Allocator>::const_iterator(nullptr, first);
}

template<typename T, typename Allocator>
typename XorList<T, Allocator>::const_iterator XorList<T, Allocator>::cend() const {
    return XorList<T, Allocator>::const_iterator(last, nullptr);
}


template<typename T, typename Allocator>
void XorList<T, Allocator>::insert_before(XorList::iterator it, const T &val) {
    item *loc = alloc.allocate(1);
    if(it == begin())
        push_front(val);
    else
        it.cur->insert_before(val, loc, it.prev);
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::insert_before(XorList::iterator it, T&& val) {
    item *loc = alloc.allocate(1);
    if(it == begin())
        push_front(std::move(val));
    else it.cur->insert_before(std::move(val), loc, it.prev);
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::insert_after(XorList::iterator it, const T &val) {
    item *loc = alloc.allocate(1);
    if(it == --end())
        push_back(val);
    else it.cur->insert_after(val, loc, it.prev);
}

template<typename T, typename Allocator>
void XorList<T, Allocator>::insert_after(XorList::iterator it, T&& val) {
    item *loc = alloc.allocate(1);
    if(it == --end())
        push_back(std::move(val));
    else it.cur->insert_after(std::move(val), loc, it.prev);
}

template <typename T, typename Allocator>
void XorList<T, Allocator>::erase(XorList::iterator it) {
    if(it == begin())
        pop_front();
    else if(it == --end())
        pop_back();
    else{
        item *prev = it.prev;
        item *next = it.cur->other(prev);
        item *cur = it.cur;
        prev->ptr ^= reinterpret_cast<uintptr_t>(cur) ^ reinterpret_cast<uintptr_t>(next);
        next->ptr ^= reinterpret_cast<uintptr_t>(cur) ^ reinterpret_cast<uintptr_t>(prev);
        delete it.cur;
    }

}
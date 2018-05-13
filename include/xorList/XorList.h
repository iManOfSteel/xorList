#pragma once
#include "XorListItem.h"
#include "XorListIterator.h"
#include <memory>

template<typename T, typename Allocator>
class XorList {
public:
    using iterator = XorListIterator<T>;
    using const_iterator = XorListIterator<const T>;
    using item  = XorListItem<T>;
    using ItemAllocator = typename Allocator::template rebind<item>::other;
    explicit XorList(const Allocator& alloc = Allocator());
    XorList(size_t count, const T& value = T(), const Allocator& alloc = Allocator());
    XorList(const XorList& other);
    XorList(XorList&& other);
    ~XorList();
    XorList& operator=(const XorList& other);
    XorList& operator=(XorList&& other);
    size_t size() const;
    void push_back(const T& val);
    void push_back(T&& val);
    void push_front(const T& val);
    void push_front(T&& val);
    void pop_back();
    void pop_front();
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    void insert_before(iterator it, const T& val);
    void insert_before(iterator it, T&& val);
    void insert_after(iterator it, const T& val);
    void insert_after(iterator it, T&& val);
    void erase(iterator it);

private:
    item *first, *last;
    ItemAllocator alloc;
    size_t _size;
};

#include "XorList.ipp"
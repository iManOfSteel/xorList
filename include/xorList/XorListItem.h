#pragma once

template <typename T>
class XorListItem {
public:
    XorListItem(const T& value, XorListItem* prev, XorListItem* next);
    XorListItem(T&& value, XorListItem* prev, XorListItem* next);
    ~XorListItem();
    void insert_update(XorListItem* prev, XorListItem* newItem);
    XorListItem* insert_before(const T& val, XorListItem* loc, XorListItem* prev = nullptr);
    XorListItem* insert_before(T&& val, XorListItem* loc, XorListItem* prev = nullptr);
    XorListItem* insert_after(const T& val, XorListItem* loc, XorListItem* prev = nullptr);
    XorListItem* insert_after(T&& val, XorListItem* loc, XorListItem* prev = nullptr);
    XorListItem* other(XorListItem* p) const;
    T value;
    uintptr_t ptr;
};

#include "XorListItem.ipp"
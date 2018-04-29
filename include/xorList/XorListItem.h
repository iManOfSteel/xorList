#pragma once

template <typename T>
class XorListItem{
public:
    XorListItem(const T& value, XorListItem* prev, XorListItem* next);
    XorListItem(T&& value, XorListItem* prev, XorListItem* next);
    ~XorListItem();
    XorListItem* insert_before(const T& val, XorListItem* loc, XorListItem* prev = NULL);
    XorListItem* insert_before(T&& val, XorListItem* loc, XorListItem* prev = NULL);
    XorListItem* insert_after(const T& val, XorListItem* loc, XorListItem* prev = NULL);
    XorListItem* insert_after(T&& val, XorListItem* loc, XorListItem* prev = NULL);
    XorListItem* other(XorListItem* p) const;
    T value;
    uintptr_t ptr;
};

#include "XorListItem.ipp"
#pragma once
#include "XorListItem.h"
#include <utility>

template <typename T>
XorListItem<T>::XorListItem(const T& value, XorListItem* prev, XorListItem* next):
        value(value),
        ptr(reinterpret_cast<uintptr_t>(prev)^reinterpret_cast<uintptr_t>(next)) {}

template <typename T>
XorListItem<T>::XorListItem(T&& value, XorListItem* prev, XorListItem* next):
        value(std::move(value)),
        ptr(reinterpret_cast<uintptr_t>(prev)^reinterpret_cast<uintptr_t>(next)) {}

template <typename T>
XorListItem<T>::~XorListItem() {}


template<typename T>
void XorListItem<T>::insert_update(XorListItem *another, XorListItem *newItem) {
    if (another != NULL)
        another->ptr ^= reinterpret_cast<uintptr_t>(this)^reinterpret_cast<uintptr_t>(newItem);
    ptr ^= reinterpret_cast<uintptr_t>(another) ^ reinterpret_cast<uintptr_t>(newItem);
}

template <typename T>
XorListItem<T>* XorListItem<T>::insert_before(const T& val, XorListItem* loc, XorListItem *prev) {
    XorListItem * newItem = new(loc) XorListItem(val, prev, this);
    insert_update(prev, newItem);
    return newItem;
}

template <typename T>
XorListItem<T>* XorListItem<T>::insert_before(T&& val, XorListItem* loc, XorListItem *prev) {
    XorListItem * newItem = new(loc) XorListItem(std::move(val), prev, this);
    insert_update(prev, newItem);
    return newItem;
}

template <typename T>
XorListItem<T>* XorListItem<T>::insert_after(const T& val, XorListItem* loc, XorListItem *prev) {
    XorListItem * newItem = new(loc) XorListItem(val, this, other(prev));
    insert_update(other(prev), newItem);
    return newItem;
}

template <typename T>
XorListItem<T>* XorListItem<T>::insert_after(T&& val, XorListItem* loc, XorListItem *prev) {
    XorListItem * newItem = new(loc) XorListItem(std::move(val), this, other(prev));
    insert_update(other(prev), newItem);
    return newItem;
}

template <typename T>
XorListItem<T>* XorListItem<T>::other(XorListItem *p) const {
    return reinterpret_cast<XorListItem*>(reinterpret_cast<uintptr_t>(p)^ptr);
}
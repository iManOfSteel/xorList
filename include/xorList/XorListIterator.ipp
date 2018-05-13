#pragma once
#include "XorListIterator.h"

template <typename T>
XorListIterator<T>::XorListIterator(XorListItem<T> *prev, XorListItem<T> *cur):
        prev(prev), cur(cur) {}

template <typename T>
XorListIterator<T>::XorListIterator(const XorListIterator &other):
        prev(other.prev), cur(other.cur) {}

template <typename T>
XorListIterator<T>& XorListIterator<T>::operator=(const XorListIterator &other) {
    prev = other.prev;
    cur = other.cur;
}

template <typename T>
bool XorListIterator<T>::operator==(const XorListIterator &other) const {
    return cur == other.cur;
}

template <typename T>
bool XorListIterator<T>::operator!=(const XorListIterator &other) const {
    return cur != other.cur;
}

template <typename T>
typename XorListIterator<T>::reference XorListIterator<T>::operator*() {
    return cur->value;
}

template <typename T>
typename XorListIterator<T>::pointer XorListIterator<T>::operator->() {
    return &(cur->value);
}

template <typename T>
XorListIterator<T>& XorListIterator<T>::operator--() {
    cur = prev->other(cur);
    std::swap(cur, prev);
    return *this;
}

template <typename T>
XorListIterator<T> XorListIterator<T>::operator--(int) {
    XorListIterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
XorListIterator<T>& XorListIterator<T>::operator++() {
    prev = cur->other(prev);
    std::swap(cur, prev);
    return *this;
}

template <typename T>
XorListIterator<T> XorListIterator<T>::operator++(int) {
    XorListIterator temp = *this;
    ++(*this);
    return temp;
}
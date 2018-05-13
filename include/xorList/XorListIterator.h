#pragma once
#include <iterator>
#include "XorListItem.h"
#include "XorList.h"

template <typename T>
class XorListIterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    XorListIterator(XorListItem<T>* prev, XorListItem<T>* cur);
    XorListIterator(const XorListIterator& other);
    ~XorListIterator() = default;
    XorListIterator<T>& operator=(const XorListIterator& other);
    bool operator==(const XorListIterator& other) const;
    bool operator!=(const XorListIterator& other) const;
    reference operator*();
    pointer operator->();
    XorListIterator& operator--();
    XorListIterator operator--(int);
    XorListIterator& operator++();
    XorListIterator operator++(int);
private:
    XorListItem<T> *prev, *cur;
    template <typename U, typename Allocator>
    friend class XorList;
};

#include "XorListIterator.ipp"
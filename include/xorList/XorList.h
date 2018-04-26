#pragma once

template<typename T, typename Allocator>
class XorList{
public:
    explicit XorList(Allocator alloc = Allocator());
    XorList(size_t count, const T& value = T(), const Allocator& alloc = Allocator());
    XorList(const XorList& other);
    XorList(XorList&& other);
    ~XorList();
    XorList& operator=(const XorList& other);
    XorList& operator=(XorList&& other);
    size_t size();

};
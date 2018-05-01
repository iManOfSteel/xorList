#include "xorList/StackAllocator.h"
#include "xorList/XorList.h"
#include <list>
#include <iostream>
#include <vector>
#include <memory>

int main(){
    StackAllocator<double> alloc;
    XorList<int, StackAllocator<int>> list;
    for(int i = 0; i < 100000; i++)
        list.push_back(i);
    for(auto it = list.begin(); it!= list.end(); it++)
        std::cout << (*it) << ' ';
    auto it = list.begin();
    it++;
    it++;
    list.insert_before(list.begin(), 2);
    std::cout << std::endl;
    for(auto it = list.begin(); it!= list.end(); it++)
        std::cout << (*it) << ' ';
    return 0;
}
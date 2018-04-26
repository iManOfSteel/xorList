#include "xorList/StackAllocator.h"
#include <list>
#include <iostream>
#include <vector>

int main(){
    std::list<int, std::allocator<int>> def;
    std::list<int, StackAllocator<int>> my;
    int t = clock();
    for(int i = 0; i < 10000; i++)
        def.emplace_back(i);
    std::cout << clock() - t << std::endl;
    t = clock();
    for(int i = 0; i < 10000; i++)
        my.emplace_back(i);
    std::cout << clock() - t << std::endl;
    return 0;
}
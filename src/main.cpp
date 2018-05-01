#include "xorList/StackAllocator.h"
#include "xorList/XorList.h"
#include <list>
#include <iostream>
#include <vector>
#include <memory>

int main(){
    XorList<int, std::allocator<int>> my;
    std::list<int, std::allocator<int>> def;
    int N = 100000;
    int t = clock();
    for(int i = 0; i < N; i++)
        my.push_back(i);
    for(int i = 0; i < N; i++)
        my.pop_back();
    std::cout << clock() - t << std::endl;
    t = clock();
    for(int i = 0; i < N; i++)
        def.push_back(i);
    for(int i = 0; i < N; i++)
        def.pop_back();
    std::cout << clock() - t << std::endl;
    return 0;
}
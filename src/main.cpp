#include "xorList/StackAllocator.h"
#include "xorList/XorList.h"
#include <list>
#include <iostream>
#include <vector>
#include <memory>

int main(){
    std::list<int, StackAllocator<int>> my;
    std::list<int, std::allocator<int>> def;
    int N = 100000;
    int t = clock();
    for(int i = 0; i < N; i++)
        my.push_back(i);
    for(int i = 0; i < N; i++)
        my.pop_back();
    std::cout << clock() - t << std::endl;
    my.push_back(2);
    my.erase(my.begin());
    t = clock();
    for(int i = 0; i < N; i++)
        def.push_back(i);
    for(int i = 0; i < N; i++)
        def.pop_back();
    std::cout << clock() - t << std::endl;
    return 0;
}
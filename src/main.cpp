#include <iostream>
#include "factorial.h"
#include "CustomAllocator.hpp"
#include "SinglyLinkedList.hpp"
#include <map>

const int size = 10;

int main() {
    // Создание std::map
    std::map<int, int> defaultAllocMap;
    for(int i = 0; i < size; i++){
        defaultAllocMap[i] = factorialCalc(i);
    }

    std::cout << "Default allocator MAP" << std::endl;

    // Вывод результата
    for(auto [num, factorial] : defaultAllocMap){
        std::cout << "number: " << num << " " << "factorial: " <<  factorial << std::endl;
    }

    // Создание std::map с custom allocator
    std::map<int, int, std::less<>, CustomPoolAllocator<std::pair<const int,int>, 10>> customAllocatorMap;

    for(int i = 0; i < size; i++) {
        customAllocatorMap[i] = factorialCalc(i);
    }

    std::cout << "Custom allocator MAP" << std::endl;

    // Вывод результата с custom allocator
    for(auto [num, factorial] : customAllocatorMap){
        std::cout << "number: " << num << " " << "factorial: " <<  factorial << std::endl;
    }

    // Создание SinglyLinkedList c default allocator
    SinglyLinkedList<int> singly_list;
    for(int i = 0; i < size; i++) {
        singly_list.push_back(i);
    }

    // Вывод SinglyLinkedList c default allocator
    for(const auto &it : singly_list){
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    // Создание SinglyLinkedList c CustomPoolAllocator
    SinglyLinkedList<int, CustomPoolAllocator<int, 10>> singly_list_custom_alloc;
    for(int i = 0; i < size; i++) {
        singly_list_custom_alloc.push_back(i);
    }

    // Вывод SinglyLinkedList c default allocator
    for(const auto &it : singly_list_custom_alloc){
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    std::cout << "End" << std::endl;
    return 0;
}

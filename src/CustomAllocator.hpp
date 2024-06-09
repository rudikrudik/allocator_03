#pragma once

#include <array>

template<class T, signed S>
class CustomPoolAllocator {
public:
    typedef T value_type;
    static constexpr int size = sizeof(T) * S;

    CustomPoolAllocator() : memory_block(0) {};
    ~CustomPoolAllocator() = default;

    template<class TA>
    constexpr explicit CustomPoolAllocator(const CustomPoolAllocator<TA, S> &other) noexcept;

    T* allocate (std::size_t n);
    void deallocate (T* p, std::size_t n);

    template <class TA>
    struct rebind {using other = CustomPoolAllocator<TA, S>;};

    // Перегрузка операторов
    template<class TA>
    constexpr bool operator == (const CustomPoolAllocator<TA, S>& a) noexcept;
    template<class TA>
    constexpr bool operator != (const CustomPoolAllocator<TA, S>& a) noexcept;

private:
    std::array<value_type, S> memory;
    size_t memory_block = 0;

};

// Реализация методов
template<class T, signed S>
template<class TA>
constexpr CustomPoolAllocator<T,S>::CustomPoolAllocator(const CustomPoolAllocator<TA, S> &other) noexcept {}

template<class T, signed S>
T* CustomPoolAllocator<T, S>::allocate(std::size_t n) {
    if (memory_block + n > S)
        throw std::bad_alloc();

    T* current_pointer = &memory[memory_block];
    memory_block += n;
    return current_pointer;
}

template<class T, signed S>
void CustomPoolAllocator<T, S>::deallocate(T*, std::size_t n){
    memory_block -= n;
}

template<class T, signed int S>
template<class TA>
constexpr bool CustomPoolAllocator<T, S>::operator==(const CustomPoolAllocator<TA, S> &a) noexcept {
    return true;
}

template<class T, signed int S>
template<class TA>
constexpr bool CustomPoolAllocator<T, S>::operator!=(const CustomPoolAllocator<TA, S> &a) noexcept {
    return false;
}

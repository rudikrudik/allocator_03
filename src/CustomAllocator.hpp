#pragma once

template<class T, signed S>
class CustomPoolAllocator {
public:
    typedef T value_type;
    static signed int position;
    static constexpr int size = sizeof(T) * S;
    void* data = ::operator new(size);
    //char (*pchar)[10] = new char[dim][10];
    //void* data = ::operator new(size);
    //static uint8_t data[size];

    CustomPoolAllocator() noexcept = default;
    ~CustomPoolAllocator() = default;

    template<class TA, signed SA>
    constexpr explicit CustomPoolAllocator(const CustomPoolAllocator<TA, SA> &other) noexcept;

    T* allocate (std::size_t n);
    void deallocate (T* p, std::size_t n);

    template <class TA>
    struct rebind {using other = CustomPoolAllocator<TA, S>;};

    // Перегрузка операторов
    template<class TA, signed UA>
    constexpr bool operator == (const CustomPoolAllocator<TA, UA>& a) noexcept;
    template<class TA, signed UA>
    constexpr bool operator != (const CustomPoolAllocator<TA, UA>& a) noexcept;

};

// Реализация методов
template<class T, signed S>
template<class TA, signed SA>
constexpr CustomPoolAllocator<T,S>::CustomPoolAllocator(const CustomPoolAllocator<TA, SA> &other) noexcept {}

template<class T, signed S>
T* CustomPoolAllocator<T, S>::allocate(std::size_t n) {
    std::cout << "Allocated elem" << std::endl;
    if (sizeof(T)*position > size)
        throw std::bad_alloc();

    int current = position;
    position += static_cast<int>(n);
    return reinterpret_cast<T*>(data) + current;
}

template<class T, signed S>
[[maybe_unused]] void CustomPoolAllocator<T, S>::deallocate(T*, std::size_t){}

template<class T, signed int S>
template<class TA, signed int UA>
constexpr bool CustomPoolAllocator<T, S>::operator==(const CustomPoolAllocator<TA, UA> &a) noexcept {
    return true;
}

template<class T, signed int S>
template<class TA, signed int UA>
constexpr bool CustomPoolAllocator<T, S>::operator!=(const CustomPoolAllocator<TA, UA> &a) noexcept {
    return false;
}

template <class T, signed int S>
int CustomPoolAllocator<T, S>::position = 0;
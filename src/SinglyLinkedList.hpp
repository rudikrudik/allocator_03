#pragma once

template <typename T, class Allocator = std::allocator<T>>
class SinglyLinkedList{
public:
    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList<T, Allocator> &other);
    ~SinglyLinkedList() = default;

    int size() const;
    void push_back(T data);
    void insert(int position, T data);
    void erase(int position);
    // Перегрузка операторов
    T& operator[](int element);
    SinglyLinkedList<T, Allocator>& operator=(const SinglyLinkedList<T, Allocator> &rhs);

private:
    class Node{
    public:

        Node *pNext;
        T data;

        Node(T data, Node *pNext = nullptr){
            this->data = data;
            this->pNext = pNext;
        };

    };

    int s_size;
    Node *head;
    Allocator allocator;

public:
    class Iterator {
    public:
        Iterator(Node *node);
        ~Iterator() = default;

        bool operator!=(const Iterator &other) const;
        Iterator operator++();
        T& operator*();
    private:
        Node *current;

    };

    Iterator begin() const;
    Iterator end() const;
};

// Реализация методов
template <typename T, class Allocator>
SinglyLinkedList<T, Allocator>::SinglyLinkedList(): s_size{0}, head{nullptr} {}

template <typename T, class Allocator>
SinglyLinkedList<T, Allocator>::SinglyLinkedList(const SinglyLinkedList<T, Allocator> &other) : SinglyLinkedList<T, Allocator>() {
    this->s_size = other.s_size;
    Node *temp = nullptr;
    for(Node *p = other.head;  p!= nullptr; p = p->pNext){
        Node *new_item = new Node(p->data);
        if(!head){
            head = new_item;
        }
        else{
            temp->pNext = new_item;
        }
        temp = new_item;
    }
}

template <typename T, class Allocator>
int SinglyLinkedList<T, Allocator>::size() const {return s_size;}

template <typename T, class Allocator>
void SinglyLinkedList<T, Allocator>::push_back(T data) {
    typename Allocator::template rebind<Node>::other nodeAlloc;
    Node *node = nodeAlloc.allocate(1);

    if(head == nullptr){
        head = new(node) Node(data);
    }
    else{
        Node *current = this->head;
        while(current->pNext != nullptr){
            current = current->pNext;
        }
        current->pNext = new(node) Node(data);
    }
    s_size++;
}

template <typename T, class Allocator>
void SinglyLinkedList<T, Allocator>::insert(int position, T data) {
    if(position < 0 || (position >= s_size && head != nullptr )){
        return;
    }

    if(position > s_size -1){
        return push_back(data);
    }

    Node *current = this->head;
    Node *newData = new Node(data);

    if(position == 0){
        head = newData;
        head->pNext = current;
    }
    else{
        while(position - 1){
            current = current->pNext;
            position--;
        }
        newData->pNext = current->pNext;
        current->pNext = newData;
    }
    s_size++;
}

template <typename T, class Allocator>
void SinglyLinkedList<T, Allocator>::erase(int position) {
    Node *prev = this->head;

    if(position < 0 || position >= s_size){
        return;
    }

    if(position == 0){
        head = prev->pNext;
    }
    else {
        for (int i = 0; i < position - 1; i++) {
            prev = prev->pNext;
        }

        Node *temp = prev->pNext;
        prev->pNext = temp->pNext;
        delete temp;

    }
    s_size--;
}

template <typename T, class Allocator>
T& SinglyLinkedList<T, Allocator>::operator[](int element){
    if(element < 0){
        return head->data;
    }

    Node *current = this->head;

    if(element >= s_size){
        element = s_size -1;
    }

    while(element){
        current = current->pNext;
        element--;
    }
    return current->data;
}

template <typename T, class Allocator>
SinglyLinkedList<T, Allocator>& SinglyLinkedList<T, Allocator>::operator=(const SinglyLinkedList<T, Allocator> &rhs) {
    SinglyLinkedList<T, Allocator> temp{rhs};
    Node *temp_data = head;
    int temp_size = s_size;

    head = temp.head;
    s_size = temp.s_size;

    temp.head = temp_data;
    temp.s_size = temp_size;

    return *this;
}

// Реализация методов итератора

template<typename T, class Allocator>
SinglyLinkedList<T, Allocator>::Iterator::Iterator(Node *node) {
    current = node;
}

template<typename T, class Allocator>
typename SinglyLinkedList<T, Allocator>::Iterator SinglyLinkedList<T, Allocator>::begin() const {
    return Iterator(this->head);
}

template<typename T, class Allocator>
typename SinglyLinkedList<T, Allocator>::Iterator SinglyLinkedList<T, Allocator>::end() const {
    return Iterator(nullptr);
}


template<typename T, class Allocator>
bool SinglyLinkedList<T, Allocator>::Iterator::operator!=(const Iterator &other) const {
    return current != other.current;
}

template<typename T, class Allocator>
typename SinglyLinkedList<T, Allocator>::Iterator SinglyLinkedList<T, Allocator>::Iterator::operator++() {
    current = current->pNext;
    return *this;
}

template<typename T, class Allocator>
T& SinglyLinkedList<T, Allocator>::Iterator::operator*() {
    return current->data;
}
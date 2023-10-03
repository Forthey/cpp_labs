#pragma once
#include <iostream>


template <typename Data>
class List
{
public:
    explicit List();

    void pushBack(const Data& data);
    Data popBack(bool& popSuccessFul);
    void pushFront(const Data& data);
    Data popFront(bool& popSuccessFul);
    Data popAt(const int index, bool& popSuccessFul);

    size_t length();
    void display(std::ostream out);
    void clear();

    void operator+=(const Data& data);
    Data& operator[](const int index);

    ~List();
private:
    class ListElement {
    public:
        explicit ListElement(Data data, ListElement* next) : data(data), next(next) {};
        Data data;
        ListElement* next;
    } *head;
    size_t len;
};

template class List<int>;
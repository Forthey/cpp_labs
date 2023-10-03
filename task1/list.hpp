#pragma once
#include <iostream>


/*
 * Class List declaration
 */ 
template <typename Data>
class List
{
public:
    explicit List();

    bool pushBack(const Data& data);
    bool pushFront(const Data& data);
    bool popBack();
    bool popBack(Data& oldData);
    bool popFront();
    bool popFront(Data& oldData);
    bool popAt(const size_t index);
    bool popAt(const size_t index, Data& oldData);

    size_t length();
    void display(std::ostream &out);
    size_t find(const Data& data);
    void clear();

    List<Data>& operator<<(const Data& data);
    List<Data>& operator>>(const Data& data);
    Data& operator[](const size_t index);

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


/*
 * Class List's functions definition
 */
template<typename Data>
List<Data>::List() {
    head = nullptr;
    len = 0;
}

template<typename Data>
List<Data>::~List() {
    clear();
}

template<typename Data>
bool List<Data>::pushBack(const Data& data) {
    ListElement* newListElement = new ListElement(data, nullptr);

    if (newListElement == nullptr)
        return false;

    len++;

    if (head == nullptr) {
        head = newListElement;
        return true;
    }

    ListElement* listElement = head;

    while (listElement->next != nullptr)
        listElement = listElement->next;
    listElement->next = newListElement;


    return true;
}

template<typename Data>
bool List<Data>::pushFront(const Data& data) {
    ListElement* newListElement = new ListElement(data, head);

    if (newListElement == nullptr)
        return false;

    len++;

    head = newListElement;

    return true;
}

template<typename Data>
bool List<Data>::popBack(Data& oldData) {
    if (head == nullptr) {
        return false;
    }

    ListElement* listElement = head;
    ListElement* previousListElement = nullptr;

    for (int i = 0; i < len; i++) {
        previousListElement = listElement;
        listElement = listElement->next;
    }

    oldData = listElement->data;
    delete listElement;

    if (previousListElement != nullptr)
        previousListElement->next = nullptr;
    else
        head = nullptr;

    len--;

    return true;
}

template<typename Data>
bool List<Data>::popBack() {
    Data tmp;
    return popBack(tmp);
}

template<typename Data>
bool List<Data>::popFront(Data& oldData) {
    if (head == nullptr)
        return false;

    ListElement* oldElement = head;
    oldData = oldElement->data;
    head = head->next;

    delete oldElement;

    len--;

    return true;
}

template<typename Data>
bool List<Data>::popFront() {
    Data tmp;
    return popFront(tmp);
}

template<typename Data>
bool List<Data>::popAt(const size_t index, Data& oldData) {
    if (head == nullptr)
        return false;

    if (index >= len)
        index = len - 1;

    ListElement* listElement = head;
    ListElement* previousListElement = nullptr;

    for (int i = 0; i < index; i++)
        listElement = listElement->next;

    return true;
}

template<typename Data>
bool List<Data>::popAt(const size_t index) {
    Data tmp;
    return popAt(index, tmp);
}


template<typename Data>
size_t List<Data>::length() {
    return len;
}

template<typename Data>
void List<Data>::display(std::ostream &out) {
    ListElement* element = head;

    if (len == 0) {
        out << "<Empty list>" << std::endl;
    }

    for (int i = 0; i < len && element != nullptr; i++) {
        out << element->data << " ";
        element = element->next;
    }
    out << std::endl;
}
template<typename Data>
size_t List<Data>::find(const Data& data) {
    ListElement* listElement = head;
    size_t index;

    for (index = 0; index < len; index++) {
        if (listElement->data == data)
            break;
        listElement = listElement->next;
    }

    return index;
}

template<typename Data>
void List<Data>::clear() {
    while (popFront());
}


template<typename Data>
List<Data>& List<Data>::operator<<(const Data& data) {
    pushBack(data);

    return *this;
}

template<typename Data>
List<Data>& List<Data>::operator>>(const Data& data) {
    bool tmp;
    data = popBack(tmp);

    return *this;
}

template<typename Data>
Data& List<Data>::operator[](const size_t index) {
    if (index >= len)
        index = len - 1;

    ListElement* listElement = head;
    for (int i = 0; i < index; i++)
        listElement = listElement->next;

    return listElement->data;
}
#include "list.hpp"

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
void List<Data>::pushBack(const Data& data) {
    ListElement* newListElement = new ListElement(data, nullptr);

    if (newListElement == nullptr)
        return;

    if (head == nullptr) {
        head = newListElement;
        return;
    }

    ListElement* listElement = head;

    while (listElement->next != nullptr)
        listElement = listElement->next;
    listElement->next = newListElement;

    len++;
}

template<typename Data>
Data List<Data>::popBack(bool &popSuccessFul) {
    if (head == nullptr) {
        popSuccessFul = false;
        return Data();
    }

    ListElement* listElement = head;
    ListElement* previousListElement = nullptr;

    while (listElement->next != nullptr) {
        previousListElement = listElement;
        listElement = listElement->next;
    }

    Data data = listElement->data;
    delete listElement;

    if (previousListElement != nullptr)
        previousListElement->next = nullptr;
    else
        head = nullptr;

    popSuccessFul = true;
    len--;

    return data;
}

template<typename Data>
void List<Data>::pushFront(const Data& data) {

}

template<typename Data>
Data List<Data>::popFront(bool& popSuccessFul) {
    if (head == nullptr)
        popSuccessFul = false;
}

template<typename Data>
Data List<Data>::popAt(const int index, bool& popSuccessFul) {
    if (head == nullptr)
        popSuccessFul = false;
}


template<typename Data>
size_t List<Data>::length() {
    return len;
}

template<typename Data>
void List<Data>::display(std::ostream out) {
    ListElement* element = head;

    if (len == 0)
    for (int i = 0; i < len && element != nullptr; i++) {
        out << element->data << " ";
        element = element->next;
    }
    out << std::endl;
}

template<typename Data>
void List<Data>::clear() {

}


template<typename Data>
void List<Data>::operator+=(const Data& data) {

}

template<typename Data>
Data& List<Data>::operator[](const int index) {

}
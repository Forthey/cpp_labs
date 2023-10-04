#pragma once
#include <iostream>
#include <string>

namespace Alg {
    template<typename Data>
    int defaultCompareFunc(const Data &data1, const Data &data2) {
        return data1 - data2;
    }
   
    template<typename Data>
    void defaultDisplayFunc(std::ostream &out, const Data &data) {
        out << data;
    }

    template<typename Data>
    Data defaultParseFunc(std::istream& in) {
        Data data;
        in >> data;
        return data;
    }

    /*
     * Class List declaration
     */
    template <typename Data>
    class List {
    public:
        explicit List();

        List<Data>& pushBack(const Data& data);
        List<Data>& pushFront(const Data& data);
        List<Data>& popBack();
        List<Data>& popBack(Data& oldData);
        List<Data>& popFront();
        List<Data>& popFront(Data& oldData);
        List<Data>& popAt(size_t index);
        List<Data>& popAt(size_t index, Data& oldData);

        void clear();
        bool empty();

        size_t length();

        void display(std::ostream& out = std::cout, void(&displayFunc)(std::ostream &, const Data &) = defaultDisplayFunc);
        List<Data>& read(const size_t size, std::istream& in = std::cin, Data(&parseFunc)(std::istream&) = defaultParseFunc);

        size_t find(const Data& data);
        // List<Data>& findAll(const Data& data);
        Data& min(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc);
        Data& max(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc);
        List<Data>& sort(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc);

        List<Data>& operator<<(const Data& data);
        List<Data>& operator>>(const Data& data);
        Data& operator[](size_t index);

        ~List();
    private:
        class ListElement {
        public:
            explicit ListElement(Data data, ListElement* next) : data(data), next(next) {};
            Data data;
            ListElement* next;
        } *head;

        size_t len;

        Data& min(int(&compareFunc)(const Data&, const Data&), size_t a, size_t b);
        Data& max(int(&compareFunc)(const Data&, const Data&), size_t a, size_t b);
        void swap(Data& data1, Data& data2);
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
    List<Data>& List<Data>::pushBack(const Data& data) {
        ListElement* newListElement = new ListElement(data, nullptr);

        if (newListElement == nullptr)
            return *this;

        if (head == nullptr) {
            head = newListElement;
            len++;
            return *this;
        }

        ListElement* listElement = head;


        for (size_t i = 0; i < len - 1; i++)
            listElement = listElement->next;
        listElement->next = newListElement;

        len++;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushFront(const Data& data) {
        ListElement* newListElement = new ListElement(data, head);

        if (newListElement == nullptr)
            return *this;

        len++;

        head = newListElement;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::popBack(Data& oldData) {
        if (len == 0)
            return *this;

        ListElement* listElement = head;
        ListElement* previousListElement = nullptr;

        for (size_t i = 0; i < len - 1; i++) {
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

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::popBack() {
        Data tmp;
        return popBack(tmp);
    }

    template<typename Data>
    List<Data>& List<Data>::popFront(Data& oldData) {
        if (head == nullptr)
            return *this;;

        ListElement* oldElement = head;
        oldData = oldElement->data;
        head = head->next;

        delete oldElement;

        len--;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::popFront() {
        Data tmp;
        return popFront(tmp);
    }

    template<typename Data>
    List<Data>& List<Data>::popAt(size_t index, Data& oldData) {
        if (head == nullptr)
            return *this;

        if (index >= len)
            index = len - 1;

        ListElement* listElement = head;
        ListElement* previousListElement = nullptr;

        for (size_t i = 0; i < index; i++)
            listElement = listElement->next;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::popAt(size_t index) {
        Data tmp;
        return popAt(index, tmp);
    }


    template<typename Data>
    size_t List<Data>::length() {
        return len;
    }

    template<typename Data>
    void List<Data>::display(std::ostream& out, void(&displayFunc)(std::ostream&, const Data&)) {
        ListElement* element = head;

        if (len == 0) {
            out << "<Empty list>" << std::endl;
        }

        for (size_t i = 0; i < len && element != nullptr; i++) {
            displayFunc(out, element->data);
            out << std::endl;
            element = element->next;
        }
        out << std::endl;
    }

    template<typename Data>
    List<Data>& List<Data>::read(const size_t size, std::istream& in, Data(&parseFunc)(std::istream&)) {
        std::string dataAsString;
        for (size_t i = 0; i < size; i++) {
            *this << parseFunc(in);
        }

        return *this;
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
    Data& List<Data>::min(int(&compareFunc)(const Data&, const Data&)) {
        return min(compareFunc, 0, len);
    }

    template<typename Data>
    Data& List<Data>::max(int(&compareFunc)(const Data&, const Data&)) {
        return max(compareFunc, 0, len);
    }

    template<typename Data>
    Data& List<Data>::min(int(&compareFunc)(const Data&, const Data&), size_t a, size_t b) {
        if (len == 0 || a >= b)
            throw std::runtime_error("Cannot find the max element of an empty list");

        ListElement* listElement = head;
        for (size_t i = 0; i < a; i++)
            listElement = listElement->next;
        Data* min = &listElement->data;
        listElement = listElement->next;

        for (size_t i = a + 1; i < b; i++) {
            if (compareFunc(listElement->data, *min) < 0)
                min = &listElement->data;
            listElement = listElement->next;
        }

        return *min;
    }

    template<typename Data>
    Data& List<Data>::max(int(&compareFunc)(const Data&, const Data&), size_t a, size_t b) {
        if (len == 0 || a >= b)
            throw std::runtime_error("Cannot find the max element of an empty list");

        ListElement* listElement = head;
        for (size_t i = 0; i < a; i++)
            listElement = listElement->next;
        Data* max = &listElement->data;
        listElement = listElement->next;

        for (size_t i = a + 1; i < b; i++) {
            if (compareFunc(listElement->data, *max) > 0)
                max = &listElement->data;
            listElement = listElement->next;
        }

        return *max;
    }

    template<typename Data>
    void List<Data>::swap(Data& data1, Data& data2) {
        Data tmp = data1;
        data1 = data2;
        data2 = tmp;
    }

    template<typename Data>
    List<Data>& List<Data>::sort(int(&compareFunc)(const Data&, const Data&)) {
        if (len == 0)
            return *this;

        // Selection sort
        ListElement* listElement = head;

        for (size_t i = 1; i < len; i++) {
            swap(listElement->data, min(compareFunc, i, len));
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    void List<Data>::clear() {
        while (!popFront().empty());
    }

    template<typename Data>
    bool List<Data>::empty() {
        return len == 0;
    }


    template<typename Data>
    List<Data>& List<Data>::operator<<(const Data& data) {
        return pushBack(data);
    }

    template<typename Data>
    List<Data>& List<Data>::operator>>(const Data& data) {
        return popBack(data);
    }

    template<typename Data>
    Data& List<Data>::operator[](size_t index) {
        if (index >= len)
            index = len - 1;

        ListElement* listElement = head;
        for (size_t i = 0; i < index; i++)
            listElement = listElement->next;

        return listElement->data;
    }
}
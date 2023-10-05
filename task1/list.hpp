#pragma once
#include <iostream>
#include <string>

namespace Alg {

    /*
     * Default functions
     */


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
        List(const List<Data> &list);

        List<Data>& pushBack(const Data& data);
        List<Data>& pushBack(const List<Data>& list);
        List<Data>& pushFront(const Data& data);
        List<Data>& pushFront(const List<Data>& list);
        List<Data>& pushAt(size_t index, const Data& data);
        List<Data>& pushAt(size_t index, const List<Data>& list);
        List<Data>& pushSorted(const Data& data, int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc);
        List<Data>& pushSorted(const List<Data>& list, int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc);

        List<Data>& popBack();
        List<Data>& popBack(Data& oldData);
        List<Data>& popFront();
        List<Data>& popFront(Data& oldData);
        List<Data>& popAt(size_t index);
        List<Data>& popAt(size_t index, Data& oldData);

        void clear();

        bool empty() const;
        size_t length() const;
        bool sorted(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc) const;

        void display(std::ostream& out = std::cout, void(&displayFunc)(std::ostream &, const Data &) = defaultDisplayFunc) const;
        List<Data>& read(const size_t size, std::istream& in = std::cin, Data(&parseFunc)(std::istream&) = defaultParseFunc);
        List<Data>& readSorted(const size_t size, std::istream& in = std::cin, int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc, Data(&parseFunc)(std::istream&) = defaultParseFunc);

        size_t find(const Data& data) const;
        // List<Data>& findAll(const Data& data);
        Data& min(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc) const;
        Data& max(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc) const;
        List<Data>& sort(int(&compareFunc)(const Data&, const Data&) = defaultCompareFunc);

        List<Data>& operator<<(const Data& data);
        List<Data>& operator<<(const List<Data>& list);
        List<Data>& operator>>(const Data& data);
        List<Data> operator+(const List<Data>& list) const;
        Data& operator[](size_t index) const;

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
     * Class List's functions definitions
     */


    template<typename Data>
    List<Data>::List() {
        head = nullptr;
        len = 0;
    }

    template<typename Data>
    List<Data>::List(const List<Data> &list) {
        head = nullptr;
        len = 0;
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            pushBack(listElement->data);
            listElement = listElement->next;
        }
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
    List<Data>& List<Data>::pushBack(const List<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            (*this).pushBack(listElement->data);
            listElement = listElement->next;
        }

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
    List<Data>& List<Data>::pushFront(const List<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            (*this).pushAt(i, listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushAt(size_t index, const Data& data) {
        if (head == nullptr) {
            return pushBack(data);
        }

        if (index >= len) {
            index = len - 1;
        }

        if (index == 0) {
            return pushFront(data);
        }

        ListElement* listElement = head;
        for (size_t i = 0; i < index - 1; i++) {
            listElement = listElement->next;
        }

        ListElement* newListElement = new ListElement(data, listElement->next);
        if (newListElement == nullptr)
            return *this;

        listElement->next = newListElement;
        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushAt(size_t index, const List<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            (*this).pushAt(i + index, listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushSorted(const Data& data, int(&compareFunc)(const Data&, const Data&)) {
        if (head == nullptr) {
            return pushBack(data);
        }

        ListElement* listElement = head;
        for (size_t i = 0; i < len; i++) {
            if (compareFunc(listElement->data, data) < 0) {
                return pushAt(i, data);
            }
        }

        return pushBack(data);
    }

    template<typename Data>
    List<Data>& List<Data>::pushSorted(const List<Data>& list, int(&compareFunc)(const Data&, const Data&)) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            pushSorted(listElement->data, compareFunc);
            listElement = listElement->next;
        }
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

        if (len == 1)
            return popFront(oldData);

        ListElement* listElement = head;

        for (size_t i = 0; i < index - 1; i++) 
            listElement = listElement->next;

        ListElement* oldElement = listElement->next;
        listElement->next = oldElement->next;

        delete oldElement;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::popAt(size_t index) {
        Data tmp;
        return popAt(index, tmp);
    }


    template<typename Data>
    void List<Data>::clear() {
        while (!popFront().empty());
    }

    template<typename Data>
    bool List<Data>::empty() const {
        return len == 0;
    }

    template<typename Data>
    size_t List<Data>::length() const {
        return len;
    }

    template<typename Data>
    bool List<Data>::sorted(int(&compareFunc)(const Data&, const Data&)) const {
        ListElement* listElement = head;
        for (size_t i = 0; i < len - 1; i++) {
            if (compareFunc(listElement->data, listElement->next->data) > 0) {
                return false;
            }
            listElement = listElement->next;
        }
        return true;
    }

    template<typename Data>
    void List<Data>::display(std::ostream& out, void(&displayFunc)(std::ostream&, const Data&)) const {
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
        for (size_t i = 0; i < size; i++) {
            *this << parseFunc(in);
        }
        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::readSorted(const size_t size, std::istream& in,int(&compareFunc)(const Data&, const Data&), Data(&parseFunc)(std::istream&)) {
        for (size_t i = 0; i < size; i++) {
            Data data = parseFunc(in);
            pushSorted(data, compareFunc);
        }
        return *this;
    }

    template<typename Data>
    size_t List<Data>::find(const Data& data) const {
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
    Data& List<Data>::min(int(&compareFunc)(const Data&, const Data&)) const {
        return min(compareFunc, 0, len);
    }

    template<typename Data>
    Data& List<Data>::max(int(&compareFunc)(const Data&, const Data&)) const {
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

        for (size_t i = 0; i < len; i++) {
            swap(listElement->data, min(compareFunc, i, len));
            listElement = listElement->next;
        }

        return *this;
    }


    template<typename Data>
    List<Data>& List<Data>::operator<<(const Data& data) {
        return pushBack(data);
    }

    template<typename Data>
    List<Data>& List<Data>::operator<<(const List<Data>& list) {
        return pushBack(list);
    }

    template<typename Data>
    List<Data>& List<Data>::operator>>(const Data& data) {
        return popBack(data);
    }

    template<typename Data>
    List<Data> List<Data>::operator+(const List<Data>& list) const {
        List<Data> resultList(*this);
        resultList.pushBack(list);
        return resultList;
    }

    template<typename Data>
    Data& List<Data>::operator[](size_t index) const {
        if (index >= len)
            index = len - 1;

        ListElement* listElement = head;
        for (size_t i = 0; i < index; i++)
            listElement = listElement->next;

        return listElement->data;
    }
}
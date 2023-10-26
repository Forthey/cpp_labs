#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Alg {
    /*
     * Default functions
     */

    template<typename Data>
    int defaultCompareFunction(const Data &data1, const Data &data2) {
        return data1 - data2;
    }
   
    template<typename Data>
    void defaultDisplayFunction(std::ostream &out, const Data &data) {
        out << data;
    }

    /*
     * Class List declaration
     */

    template <typename Data>
    class List {
        class ListElement {
        public:
            explicit ListElement(Data data, ListElement* next) : data(data), next(next) {};
            Data data;
            ListElement* next;
        } *head = nullptr;

        class cachedElement {
        public:
            ListElement* element = nullptr;
            size_t index = 0;
        };

        cachedElement cached;

        size_t length = 0;

        Data& min(int(*compareFunction)(const Data&, const Data&), size_t a, size_t b);
        Data& max(int(*compareFunction)(const Data&, const Data&), size_t a, size_t b);
        void swap(Data& data1, Data& data2);
    public:
        explicit List();
        List(const std::vector<Data>& array);
        List(const List<Data> &list);

        List<Data>& pushBack(const Data& data);
        List<Data>& pushBack(const List<Data>& list);
        List<Data>& pushFront(const Data& data);
        List<Data>& pushFront(const List<Data>& list);
        List<Data>& pushAt(size_t index, const Data& data);
        List<Data>& pushAt(size_t index, const List<Data>& list);
        List<Data>& pushSorted(const Data& data, int(*compareFunction)(const Data&, const Data&) = defaultCompareFunction);
        List<Data>& pushSorted(const List<Data>& list, int(*compareFunction)(const Data&, const Data&) = defaultCompareFunction);

        List<Data>& popBack();
        List<Data>& popBack(Data& oldData);
        List<Data>& popFront();
        List<Data>& popFront(Data& oldData);
        List<Data>& popAt(size_t index);
        List<Data>& popAt(size_t index, Data& oldData);
        void clear();
        void resize(size_t newSize);

        bool empty() const;
        size_t size() const;
        bool sorted(int(*compareFunction)(const Data&, const Data&) = defaultCompareFunction) const;

        void display(std::ostream& out = std::cout, void(*displayFunction)(std::ostream &, const Data &) = defaultDisplayFunction) const;
      
        size_t find(const Data& data) const;

        Data& min(int(*compareFunction)(const Data&, const Data&) = defaultCompareFunction) const;
        Data& max(int(*compareFunction)(const Data&, const Data&) = defaultCompareFunction) const;
        List<Data>& sort(int(*compareFunction)(const Data&, const Data&) = defaultCompareFunction);

        List<Data>& operator<<(const Data& data);
        List<Data>& operator<<(const List<Data>& list);
        List<Data>& operator>>(const Data& data);
        List<Data>& operator=(const List<Data>& list);
        List<Data> operator+(const List<Data>& list) const;
        Data& operator[](size_t index);

        ~List();
    };


    /*
     * Class List's functions definitions
     */


    template<typename Data>
    List<Data>::List() {
    }

    template<typename Data>
    List<Data>::List(const List<Data> &list) {
        *this = list;
    }
    template<typename Data>
    List<Data>::List(const std::vector<Data>& array) {
        for (const Data& element : array) {
            pushBack(element);
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
            length++;
            return *this;
        }

        ListElement* listElement = head;

        for (size_t i = 0; i < length - 1; i++)
            listElement = listElement->next;
        listElement->next = newListElement;

        length++;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushBack(const List<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.length; i++) {
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

        length++;

        head = newListElement;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushFront(const List<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.length; i++) {
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

        if (index >= length) {
            index = length - 1;
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

        length++;

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushAt(size_t index, const List<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.length; i++) {
            (*this).pushAt(i + index, listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::pushSorted(const Data& data, int(*compareFunction)(const Data&, const Data&)) {
        if (head == nullptr) {
            return pushBack(data);
        }

        ListElement* listElement = head;
        for (size_t i = 0; i < length; i++) {
            if (compareFunction(listElement->data, data) > 0) {
                return pushAt(i, data);
            }
            listElement = listElement->next;
        }

        return pushBack(data);
    }

    template<typename Data>
    List<Data>& List<Data>::pushSorted(const List<Data>& list, int(*compareFunction)(const Data&, const Data&)) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.length; i++) {
            pushSorted(listElement->data, compareFunction);
            listElement = listElement->next;
        }
        return *this;
    }

    template<typename Data>
    List<Data>& List<Data>::popBack(Data& oldData) {
        if (length == 0)
            return *this;

        ListElement* listElement = head;
        ListElement* previousListElement = nullptr;

        for (size_t i = 0; i < length - 1; i++) {
            previousListElement = listElement;
            listElement = listElement->next;
        }

        oldData = listElement->data;
        delete listElement;

        if (previousListElement != nullptr)
            previousListElement->next = nullptr;
        else
            head = nullptr;

        length--;

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

        length--;

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

        if (index >= length)
            index = length - 1;

        if (length == 1)
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
    void List<Data>::resize(size_t newSize) {
        if (length > newSize) {
            while (length != newSize) {
                popBack();
            }
        }
        else {
            while (length != newSize)
            {
                pushBack(Data());
            }
        }
    }

    template<typename Data>
    bool List<Data>::empty() const {
        return length == 0;
    }

    template<typename Data>
    size_t List<Data>::size() const {
        return length;
    }

    template<typename Data>
    bool List<Data>::sorted(int(*compareFunction)(const Data&, const Data&)) const {
        ListElement* listElement = head;
        for (size_t i = 0; i < length - 1; i++) {
            if (compareFunction(listElement->data, listElement->next->data) > 0) {
                return false;
            }
            listElement = listElement->next;
        }
        return true;
    }

    template<typename Data>
    void List<Data>::display(std::ostream& out, void(*displayFunction)(std::ostream&, const Data&)) const {
        ListElement* element = head;

        if (length == 0) {
            out << "<Empty list>" << std::endl;
        }

        for (size_t i = 0; i < length && element != nullptr; i++) {
            displayFunction(out, element->data);
            out << std::endl;
            element = element->next;
        }
        out << std::endl;
    }


    template<typename Data>
    size_t List<Data>::find(const Data& data) const {
        ListElement* listElement = head;
        size_t count = 0;

        for (size_t index = 0; index < length; index++) {
            if (listElement->data == data)
                count++;
            listElement = listElement->next;
        }

        return count;
    }

    template<typename Data>
    Data& List<Data>::min(int(*compareFunction)(const Data&, const Data&)) const {
        return min(compareFunction, 0, length);
    }

    template<typename Data>
    Data& List<Data>::max(int(*compareFunction)(const Data&, const Data&)) const {
        return max(compareFunction, 0, length);
    }

    template<typename Data>
    Data& List<Data>::min(int(*compareFunction)(const Data&, const Data&), size_t a, size_t b) {
        if (length == 0 || a >= b)
            throw std::runtime_error("Cannot find the max element of an empty list");

        ListElement* listElement = head;
        for (size_t i = 0; i < a; i++)
            listElement = listElement->next;
        Data* min = &listElement->data;
        listElement = listElement->next;

        for (size_t i = a + 1; i < b; i++) {
            if (compareFunction(listElement->data, *min) < 0)
                min = &listElement->data;
            listElement = listElement->next;
        }

        return *min;
    }

    template<typename Data>
    Data& List<Data>::max(int(*compareFunction)(const Data&, const Data&), size_t a, size_t b) {
        if (length == 0 || a >= b)
            throw std::runtime_error("Cannot find the max element of an empty list");

        ListElement* listElement = head;
        for (size_t i = 0; i < a; i++)
            listElement = listElement->next;
        Data* max = &listElement->data;
        listElement = listElement->next;

        for (size_t i = a + 1; i < b; i++) {
            if (compareFunction(listElement->data, *max) > 0)
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
    List<Data>& List<Data>::sort(int(*compareFunction)(const Data&, const Data&)) {
        if (length == 0)
            return *this;

        // Selection sort
        ListElement* listElement = head;

        for (size_t i = 0; i < length; i++) {
            swap(listElement->data, min(compareFunction, i, length));
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
    List<Data>& List<Data>::operator=(const List<Data>& list) {
        clear();

        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.length; i++) {
            pushBack(listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    List<Data> List<Data>::operator+(const List<Data>& list) const {
        List<Data> resultList(*this);
        resultList.pushBack(list);
        return resultList;
    }

    template<typename Data>
    Data& List<Data>::operator[](size_t index) {
        if (index >= length)
            index = length - 1;
        ListElement* listElement = head;
        if (cached.element == nullptr || cached.index > index) {
            for (size_t i = 0; i < index; i++) {
                listElement = listElement->next;
            }
        }
        else {
            listElement = cached.element;
            for (size_t i = cached.index; i < index; i++) {
                listElement = listElement->next;
            }
        }

        cached.element = listElement;
        cached.index = index;

        return listElement->data;
    }
}
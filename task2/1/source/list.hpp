#pragma once
#include <iostream>
#include <string>

namespace Alg {
    /*
     * Default functions
     */

    template<typename Data>
    int defaultCompareFunc(const Data& data1, const Data& data2) {
        return data1 - data2;
    }

    template<typename Data>
    void defaultDisplayFunc(std::ostream& out, const Data& data) {
        out << data;
    }

    template<typename Data>
    Data defaultParseFunc(std::istream& in) {
        Data data;
        in >> data;
        return data;
    }

    /*
     * Class SelfOrganizingList declaration
     */


    template <typename Data>
    class SelfOrganizingList {
        class ListElement {
        public:
            explicit ListElement(Data data, ListElement* next, ListElement* prev) : data(data), next(next), prev(prev), accessCount(0) {};
            Data data;
            ListElement* next;
            ListElement* prev;
            size_t accessCount;
        } *head, *tail;

        int(&compareFunc)(const Data&, const Data&);
        size_t len;

        Data& min(size_t a, size_t b);
        Data& max(size_t a, size_t b);
        void swap(Data& data1, Data& data2);
        void swap(size_t& data1, size_t& data2);
        void tangle(ListElement* left, ListElement* right);
        void increasePriority(ListElement* listElement);
    public:
        explicit SelfOrganizingList();
        explicit SelfOrganizingList(int(&compareFunc)(const Data&, const Data&));
        SelfOrganizingList(const SelfOrganizingList<Data>& SelfOrganizingList);

        SelfOrganizingList<Data>& push(const Data& data);
        SelfOrganizingList<Data>& push(const SelfOrganizingList<Data>& list);
        SelfOrganizingList<Data>& pushFrontForced(const Data& data);
        SelfOrganizingList<Data>& pushFrontForced(const SelfOrganizingList<Data>& list);
        SelfOrganizingList<Data>& pushForced(size_t index, const Data& data);
        SelfOrganizingList<Data>& pushForced(size_t index, const SelfOrganizingList<Data>& list);
        SelfOrganizingList<Data>& pushSorted(const Data& data);
        SelfOrganizingList<Data>& pushSorted(const SelfOrganizingList<Data>& list);

        SelfOrganizingList<Data>& popBack();
        SelfOrganizingList<Data>& popBack(Data& oldData);
        SelfOrganizingList<Data>& popFront();
        SelfOrganizingList<Data>& popFront(Data& oldData);
        SelfOrganizingList<Data>& popAt(size_t index);
        SelfOrganizingList<Data>& popAt(size_t index, Data& oldData);

        void resetPriority();
        void clear();

        bool empty() const;
        size_t length() const;
        bool sorted() const;

        void display(std::ostream& out = std::cout, void(&displayFunc)(std::ostream&, const Data&) = defaultDisplayFunc) const;
        SelfOrganizingList<Data>& read(const size_t size, std::istream& in = std::cin, Data(&parseFunc)(std::istream&) = defaultParseFunc);
        SelfOrganizingList<Data>& read(std::istream& in = std::cin, Data(&parseFunc)(std::istream&) = defaultParseFunc);
        SelfOrganizingList<Data>& readSorted(const size_t size, std::istream& in = std::cin, Data(&parseFunc)(std::istream&) = defaultParseFunc);
        SelfOrganizingList<Data>& readSorted(std::istream& in = std::cin, Data(&parseFunc)(std::istream&) = defaultParseFunc);

        Data& at(size_t index);
        size_t find(const Data& data);
        SelfOrganizingList<Data> findAll(const Data& data, int(&ruleFunc)(const Data&, const Data&) = defaultCompareFunc);

        Data& min();
        Data& max();
        SelfOrganizingList<Data>& sort();

        SelfOrganizingList<Data>& operator<<(const Data& data);
        SelfOrganizingList<Data>& operator<<(const SelfOrganizingList<Data>& list);
        SelfOrganizingList<Data>& operator>>(const Data& data);

        SelfOrganizingList<Data> operator+(const SelfOrganizingList<Data>& list) const;
        SelfOrganizingList<Data>& operator=(const SelfOrganizingList<Data>& list);
        Data& operator[](size_t index);

        ~SelfOrganizingList();
    };


    /*
     * Class SelfOrganizingList's functions definitions
     */


    template<typename Data>
    SelfOrganizingList<Data>::SelfOrganizingList() :compareFunc(defaultCompareFunc), head(nullptr), tail(nullptr), len(0) {}

    template<typename Data>
    SelfOrganizingList<Data>::SelfOrganizingList(int(&compareFunc)(const Data&, const Data&)) : compareFunc(compareFunc), head(nullptr), tail(nullptr), len(0) {}

    template<typename Data>
    SelfOrganizingList<Data>::SelfOrganizingList(const SelfOrganizingList<Data>& list) : compareFunc(list.compareFunc), head(nullptr), tail(nullptr), len(0) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            push(listElement->data);
            listElement = listElement->next;
        }
    }

    template<typename Data>
    SelfOrganizingList<Data>::~SelfOrganizingList() {
        clear();
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::push(const Data& data) {
        ListElement* newListElement = new ListElement(data, nullptr, nullptr);

        if (newListElement == nullptr)
            return *this;

        len++;
        if (head == nullptr) {
            head = newListElement;
            tail = newListElement;   
            return *this;
        }
        tangle(tail, newListElement);
        tail = newListElement;

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::push(const SelfOrganizingList<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            (*this).push(listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::pushFrontForced(const Data& data) {
        ListElement* newListElement = new ListElement(data, nullptr, nullptr);

        if (newListElement == nullptr)
            return *this;

        len++;

        if (head == nullptr) {
            head = newListElement;
            tail = newListElement;
            return *this;
        }

        newListElement->accessCount = head->accessCount;
        tangle(newListElement, head);
        head = newListElement;

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::pushFrontForced(const SelfOrganizingList<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            (*this).pushAt(i, listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::pushForced(size_t index, const Data& data) {
        if (head == nullptr) {
            return push(data);
        }
        if (index >= len - 1) {
            return push(data);
        }
        if (index == 0) {
            return pushFrontForced(data);
        }

        ListElement* newListElement = new ListElement(data, nullptr, nullptr);
        if (newListElement == nullptr)
            return *this;
        ListElement* listElement = nullptr;

        if (index < len / 2) {
            listElement = head;
            for (size_t i = 0; i < index; i++) {
                listElement = listElement->next;
            }

            newListElement->accessCount = listElement->accessCount;
            tangle(listElement->prev, newListElement);
            tangle(newListElement, listElement);
        }
        else {
            listElement = tail;
            for (size_t i = len - 1; i > index; i--) {
                listElement = listElement->prev;
            }

            newListElement->accessCount = listElement->accessCount;
            tangle(listElement->prev, newListElement);
            tangle(newListElement, listElement);
        }

        len++;

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::pushForced(size_t index, const SelfOrganizingList<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            (*this).pushAt(i + index, listElement->data);
            listElement = listElement->next;
        }

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::pushSorted(const Data& data) {
        if (head == nullptr) {
            return push(data);
        }

        ListElement* listElement = head;
        for (size_t i = 0; i < len; i++) {
            if (compareFunc(listElement->data, data) > 0) {
                return pushForced(i, data);
            }
            listElement = listElement->next;
        }

        return push(data);
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::pushSorted(const SelfOrganizingList<Data>& list) {
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            pushSorted(listElement->data, compareFunc);
            listElement = listElement->next;
        }
        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::popBack(Data& oldData) {
        if (len == 0)
            return *this;

        ListElement *oldElement = tail;
        tangle(tail->prev, nullptr);
        tail = tail->prev;
        oldData = oldElement->data;
        delete oldElement;

        if (tail == nullptr) {
            head = nullptr;
        }

        len--;

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::popBack() {
        Data tmp;
        return popBack(tmp);
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::popFront(Data& oldData) {
        if (head == nullptr)
            return *this;;

        ListElement* oldElement = head;
        tangle(nullptr, head->next);
        head = head->next;
        oldData = oldElement->data;

        delete oldElement;

        len--;

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::popFront() {
        Data tmp;
        return popFront(tmp);
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::popAt(size_t index, Data& oldData) {
        if (head == nullptr)
            return *this;

        if (index >= len - 1) {
            return popBack(oldData);
        }
        if (len == 1) {
            return popFront(oldData);
        }

        ListElement* listElement = nullptr;
        ListElement* oldElement = nullptr;

        if (index < len / 2) {
            listElement = head;
            for (size_t i = 0; i < index; i++)
                listElement = listElement->next;

            oldElement = listElement;
            tangle(oldElement->prev, oldElement->next);
        }
        else {
            listElement = tail;
            for (size_t i = len - 1; i > index; i--) {
                listElement = listElement->prev;
            }

            oldElement = listElement;
            tangle(oldElement->prev, oldElement->next);
        }

        oldData = oldElement->data;
        delete oldElement;

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::popAt(size_t index) {
        Data tmp;
        return popAt(index, tmp);
    }

    template<typename Data>
    void SelfOrganizingList<Data>::resetPriority() {
        ListElement* listElement = head;

        for (size_t i = 0; i < len; i++) {
            listElement->accessCount = 0;
            listElement = listElement->next;
        }
    }

    template<typename Data>
    void SelfOrganizingList<Data>::clear() {
        Data tmp;
        while (!popFront(tmp).empty());
    }

    template<typename Data>
    bool SelfOrganizingList<Data>::empty() const {
        return len == 0;
    }

    template<typename Data>
    size_t SelfOrganizingList<Data>::length() const {
        return len;
    }

    template<typename Data>
    bool SelfOrganizingList<Data>::sorted() const {
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
    void SelfOrganizingList<Data>::display(std::ostream& out, void(&displayFunc)(std::ostream&, const Data&)) const {
        ListElement* element = head;

        if (len == 0) {
            return;
        }

        for (size_t i = 0; i < len && element != nullptr; i++) {
            displayFunc(out, element->data);
            out << "\n";
            element = element->next;
        }
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::read(const size_t size, std::istream& in, Data(&parseFunc)(std::istream&)) {
        for (size_t i = 0; i < size; i++) {
            *this << parseFunc(in);
        }
        in.eof();
        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::readSorted(const size_t size, std::istream& in, Data(&parseFunc)(std::istream&)) {
        for (size_t i = 0; i < size; i++) {
            Data data = parseFunc(in);
            pushSorted(data, compareFunc);
        }
        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::read(std::istream& in, Data(&parseFunc)(std::istream&)) {
        if (in.eof())
            return *this;

        do {
            *this << parseFunc(in);
        } while (!in.eof());

        return *this;
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::readSorted(std::istream& in, Data(&parseFunc)(std::istream&)) {
        if (in.eof())
            return *this;

        do {
            Data data = parseFunc(in);
            pushSorted(data, compareFunc);
        } while (!in.eof());

        return *this;
    }

    template<typename Data>
    Data& SelfOrganizingList<Data>::at(size_t index) {
        if (index >= len)
            index = len - 1;

        ListElement* listElement = head;
        for (size_t i = 0; i < index; i++)
            listElement = listElement->next;

        increasePriority(listElement);

        return listElement->data;
    }

    template<typename Data>
    size_t SelfOrganizingList<Data>::find(const Data& data) {
        ListElement* listElement = head;
        size_t index;

        for (index = 0; index < len; index++) {
            if (listElement->data == data)
                break;
            listElement = listElement->next;
        }

        increasePriority(listElement);

        return index;
    }

    template<typename Data>
    SelfOrganizingList<Data> SelfOrganizingList<Data>::findAll(const Data& data, int(&ruleFunc)(const Data&, const Data&)) {
        SelfOrganizingList<Data> allFoundElements(compareFunc);

        ListElement* listElement = head;
        for (size_t i = 0; i < len; i++) {
            if (ruleFunc(data, listElement->data) == 0) {
                allFoundElements.push(listElement->data);
            }
            listElement = listElement->next;
        }

        return SelfOrganizingList<Data>(allFoundElements);
    }

    template<typename Data>
    Data& SelfOrganizingList<Data>::min() {
        return min(compareFunc, 0, len);
    }

    template<typename Data>
    Data& SelfOrganizingList<Data>::max() {
        return max(compareFunc, 0, len);
    }

    template<typename Data>
    Data& SelfOrganizingList<Data>::min(size_t a, size_t b) {
        if (len == 0 || a >= b)
            throw std::runtime_error("Cannot find the max element of an empty SelfOrganizingList");

        ListElement* listElement = head;
        for (size_t i = 0; i < a; i++)
            listElement = listElement->next;

        ListElement* minElement = listElement;
        listElement = listElement->next;

        for (size_t i = a + 1; i < b; i++) {
            if (compareFunc(listElement->data, minElement->data) < 0)
                minElement = listElement;
            listElement = listElement->next;
        }

        increasePriority(minElement);
        return minElement->data;
    }

    template<typename Data>
    Data& SelfOrganizingList<Data>::max(size_t a, size_t b) {
        if (len == 0 || a >= b)
            throw std::runtime_error("Cannot find the max element of an empty SelfOrganizingList");

        ListElement* listElement = head;
        for (size_t i = 0; i < a; i++)
            listElement = listElement->next;
        ListElement *maxElement = listElement;
        listElement = listElement->next;

        for (size_t i = a + 1; i < b; i++) {
            if (compareFunc(listElement->data, maxElement->data) > 0)
                maxElement = listElement;
            listElement = listElement->next;
        }

        increasePriority(maxElement);
        return maxElement->data;
    }

    template<typename Data>
    void SelfOrganizingList<Data>::swap(Data& data1, Data& data2) {
        Data tmp = data1;
        data1 = data2;
        data2 = tmp;
    }

    template<typename Data>
    void SelfOrganizingList<Data>::swap(size_t& data1, size_t& data2) {
        size_t tmp = data1;
        data1 = data2;
        data2 = tmp;
    }

    template<typename Data>
    void SelfOrganizingList<Data>::tangle(ListElement* left, ListElement* right) {
        if (left != nullptr) {
            left->next = right;
        }
        if (right != nullptr) {
            right->prev = left;
        }
    }

    template<typename Data>
    void SelfOrganizingList<Data>::increasePriority(ListElement* listElement) {
        listElement->accessCount++;
        while (listElement->prev != nullptr && compareFunc(listElement->data, listElement->prev->data) >= 0) {
            swap(listElement->data, listElement->prev->data);
            swap(listElement->accessCount, listElement->prev->accessCount);
            listElement = listElement->prev;
        }
    }

    template<typename Data>
    SelfOrganizingList<Data>& SelfOrganizingList<Data>::sort() {
        if (len == 0)
            return *this;

        // Selection sort
        ListElement* listElement = head;
        for (size_t i = 0; i < len; i++) {
            swap(listElement->data, min(compareFunc, i, len));
            listElement->accessCount = 0;
            listElement = listElement->next;
        }

        return *this;
    }


    template<typename Data>
    inline SelfOrganizingList<Data>& SelfOrganizingList<Data>::operator<<(const Data& data) {
        return push(data);
    }

    template<typename Data>
    inline SelfOrganizingList<Data>& SelfOrganizingList<Data>::operator<<(const SelfOrganizingList<Data>& list) {
        return push(list);
    }

    template<typename Data>
    inline SelfOrganizingList<Data>& SelfOrganizingList<Data>::operator>>(const Data& data) {
        return popBack(data);
    }

    template<typename Data>
    inline SelfOrganizingList<Data> SelfOrganizingList<Data>::operator+(const SelfOrganizingList<Data>& list) const {
        SelfOrganizingList<Data> resultList(*this);
        resultList.push(list);
        return resultList;
    }

    template<typename Data>
    inline SelfOrganizingList<Data>& SelfOrganizingList<Data>::operator=(const SelfOrganizingList<Data>& list)
    {
        clear();
        ListElement* listElement = list.head;
        for (size_t i = 0; i < list.len; i++) {
            push(listElement->data);
            listElement = listElement->next;
        }
        return *this;
    }

    template<typename Data>
    inline Data& SelfOrganizingList<Data>::operator[](size_t index) {
        return at(index);
    }
}
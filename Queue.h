#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <class T>
class Queue
{
private:
    struct Node;

    Node* m_head;
    Node** m_tail;
    int m_size;
public:
    class EmptyQueue;
    class Iterator;
    class ConstIterator;

    Queue() : m_head(nullptr), m_tail(&m_head), m_size(0) {}
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    ~Queue();
    void pushBack(const T&);
    T& front();
    const T& front() const;
    void popFront();
    int size() const;
    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;
};

template <class T>
struct Queue<T>::Node
{
    T m_data;
    Node* m_next;
};

template <class T>
class Queue<T>::EmptyQueue : public std::exception {
public:
    const char* what() const noexcept override {
        return "Queue is empty";
    }
};

template <class T>
class Queue<T>::Iterator
{
private:
    Node* m_node;
public:
    Iterator(Node* node) : m_node(node) {}

    class InvalidOperation : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Invalid operation on queue iterator";
        }
    };

    T& operator*() {
        if (m_node == nullptr) {
            throw InvalidOperation();
        }
        return m_node->m_data;
    }

    Iterator& operator++() {
        if (m_node == nullptr) {
            throw InvalidOperation();
        }
        m_node = m_node->m_next;
        return *this;
    }

    bool operator==(const Iterator& other) const {
        return m_node == other.m_node;
    }
    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};

template <class T>
class Queue<T>::ConstIterator
{
private:
    const Node* node;
public:
    ConstIterator(const Node* node) : node(node) {}

    class InvalidOperation : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Invalid operation on const queue iterator";
        }
    };

    const T& operator*() {
        if (node == nullptr) {
            throw InvalidOperation();
        }
        return node->m_data;
    }

    ConstIterator& operator++() {
        if (node == nullptr) {
            throw InvalidOperation();
        }
        node = node->m_next;
        return *this;
    }

    bool operator==(const ConstIterator& other) const {
        return node == other.node;
    }
    bool operator!=(const ConstIterator& other) const {
        return !(*this == other);
    }
};

template <class T>
Queue<T>::~Queue() {
    // Free all the nodes associated with this queue.
    for (Node* node = m_head; node != nullptr; ) {
        Node* next = node->m_next;
        delete node;
        // Moving the pointer inside of the for so the deleted node is not
        // accessed after it is deleted.
        node = next;
    }
}

template <class T>
void Queue<T>::pushBack(const T& data) {
    *this->m_tail = new Node { data, nullptr };
    this->m_tail = &(*this->m_tail)->m_next;
    this->m_size++;
}

template <class T>
T& Queue<T>::front() {
    if (m_head == nullptr) {
        throw EmptyQueue();
    }
    return m_head->m_data;
}

template <class T>
const T& Queue<T>::front() const {
    if (m_head == nullptr) {
        throw EmptyQueue();
    }
    return m_head->m_data;
}

template <class T>
void Queue<T>::popFront() {
    if (m_head == nullptr) {
        throw EmptyQueue();
    }
    Node* oldHead = m_head;
    m_head = m_head->m_next;
    delete oldHead;
    this->m_size--;

    // If the queue is now empty, we need to update the tail pointer.
    if (m_head == nullptr) {
        m_tail = &m_head;
    }
}

template <class T>
int Queue<T>::size() const {
    return this->m_size;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(m_head);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(m_head);
}
template <class T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(nullptr);
}
template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
    return ConstIterator(nullptr);
}

template <class T, class F>
Queue<T> filter(const Queue<T>& queue, F filterFunction) {
    Queue<T> out;
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
        if (filterFunction(*it)) {
            out.pushBack(*it);
        }
    }
    return out;
}

template <class T, class F>
void transform(Queue<T>& queue, F transformation) {
    for (typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it) {
        transformation(*it);
    }
}

template <class T>
static void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        Queue<T> copy(other);
        swap(m_head, copy.m_head);
        swap(m_tail, copy.m_tail);
        swap(m_size, copy.m_size);
    }
    return *this;
}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : Queue() {
    for (typename Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it) {
        this->pushBack(*it);
    }
}

#endif

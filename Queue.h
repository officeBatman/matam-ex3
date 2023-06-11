#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <class T>
class Queue
{
private:
    struct Node;

    Node* m_head;
    Node* m_tail;
    int m_size;

    template <class U>
    static void swap(U& a, U& b);

public:
    class EmptyQueue;
    class Iterator;
    class ConstIterator;

    Queue() : m_head(nullptr), m_tail(nullptr), m_size(0) {}
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    ~Queue();
    /*
     * Pushes a new element to the back of the queue.
     */
    void pushBack(const T&);
    /*
     * Returns a mutable reference to the front element of the queue.
     * Throws EmptyQueue if the queue is empty.
     */
    T& front();
    /*
     * Returns an immutable reference to the front element of the queue.
     * Throws EmptyQueue if the queue is empty.
     */
    const T& front() const;
    /*
     * Removes the front element of the queue.
     * Throws EmptyQueue if the queue is empty.
     */
    void popFront();
    /*
     * Returns the number of elements in the queue.
     */
    int size() const;
    /*
     * Returns an iterator to the beginning of the queue.
     */
    Iterator begin();
    /*
     * Returns an immutable iterator to the beginning of the queue.
     */
    ConstIterator begin() const;
    /*
     * Returns an iterator to the end of the queue.
     */
    Iterator end();
    /*
     * Returns an immutable iterator to the end of the queue.
     */
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
    while (this->size() > 0) {
        this->popFront();
    }
}

template <class T>
void Queue<T>::pushBack(const T& data) {
    Node* node = new Node { data, nullptr };
    if (this->m_tail != nullptr) {
        this->m_tail->m_next = node;
        this->m_tail = node;
    } else {
        // If tail == nullptr, then head == nullptr.
        this->m_head = this->m_tail = node;
    }
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
        m_tail = nullptr;
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

/*
 * Filters the elements of the queue using the given filter function/lambda.
 */
template <class T, class F>
Queue<T> filter(const Queue<T>& queue, F& filterFunction) {
    Queue<T> out;
    for (const T& element : queue) {
        if (filterFunction(element)) {
            out.pushBack(element);
        }
    }
    return out;
}

/*
 * Transforms the elements of the queue using the given transformation function/lambda.
 */
template <class T, class F>
void transform(Queue<T>& queue, F& transformation) {
    for (T& element : queue) {
        transformation(element);
    }
}

template <class T>
template <class U>
void Queue<T>::swap(U& a, U& b) {
    U temp = a;
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
    for (const T& element : other) {
        try {
            this->pushBack(element);
        } catch (const std::bad_alloc&) {
            // If an error has occured, we need to free the memory.
            while (this->size() > 0) {
                this->popFront();
            }
            throw;
        }
    }
}

#endif

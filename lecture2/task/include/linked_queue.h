//
// Created by MohamedBakr on 10/7/2026.
//

#ifndef TASK_LINKED_QUEUE_H
#define TASK_LINKED_QUEUE_H
#include <stdexcept>

template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;

    QueueNode(const T& value) : data(value), next(nullptr) {}
};


template <typename T>
class LinkedQueue {
    QueueNode<T>* frontNode;
    QueueNode<T>* rearNode;
    int count;

public:
    LinkedQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;



    void enqueue(T value) {
        QueueNode<T>* new_node = new QueueNode<T>(value);
        if (rearNode == nullptr)
            frontNode = rearNode = new_node;
        else{
            rearNode->next = new_node;
            rearNode = new_node;
        }
        ++count;
    }

    void dequeue() {
        if (isEmpty()) return;
        QueueNode<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        --count;
    }

    T peek () const {
        if (isEmpty()) throw std::out_of_range("LinkedQueue::peek called on an empty queue");
        return frontNode->data;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return count;
    }
};
#endif //TASK_LINKED_QUEUE_H

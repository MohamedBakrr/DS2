//
// Created by MohamedBakr on 10/7/2026.
//

#ifndef TASK_LINKED_QUEUE_H
#define TASK_LINKED_QUEUE_H
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;

    QueueNode(T value) : data(value), next(nullptr) {}
};


template <typename T>
class LinkedQueue {
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int count;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), count(0) {}
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T value) {
        QueueNode<T>* new_node = new QueueNode<T>(value);
        if (rear == nullptr)
            front = rear = new_node;
        else{
            rear->next = new_node;
            rear = new_node;
        }
        ++count;
    }

    void dequeue() {
        if (isEmpty()) return;
        QueueNode<T>* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        --count;
    }

    T peek () const {
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int size() const {
        return count;
    }
};
#endif //TASK_LINKED_QUEUE_H

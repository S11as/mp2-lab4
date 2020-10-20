//
// Created by Kirill on 10/20/2020.
//

#ifndef QUEUELIB_QUEUE_H
#define QUEUELIB_QUEUE_H

#include <stdexcept>
#include <fstream>

using namespace std;

template<class T>
class TQueue {
public:
    T **arr = nullptr;
    int size = 1;
    int front = -1;
    int back = -1;
    int count = 0;
public:
    explicit TQueue(int size = 1);

    TQueue(const TQueue<T> &queue);

    ~TQueue();

    TQueue<T> &operator=(const TQueue<T> &queue);

    void push(T item);

    T pop();

    bool is_empty();

    bool is_full();

    T get_max();

    T get_least();

    template<class T1>
    friend istream &operator>>(istream &istream, TQueue<T1> &queue);

    template<class T1>
    friend ostream &operator<<(ostream &ostream, const TQueue<T1> &queue);

    static TQueue<T> &load(const char *name);

    void save(const char *name);
};

template<class T>
TQueue<T>::TQueue(int size) {
    if (size <= 0)
        throw std::range_error("Wrong queue size");
    this->size = size;
    this->arr = new T *[size];
    for (int i = 0; i < this->size; ++i) {
        this->arr[i] = 0;
    }
}

template<class T>
TQueue<T>::TQueue(const TQueue<T> &queue) {
    if (this->size != queue.size) {
        delete[] this->arr;
        this->size = queue.size;
        this->arr = new T *[queue.size];
    }
    this->front = queue.front;
    this->back = queue.back;
    for (int i = 0; i < this->size; ++i) {
        this->arr[i] = new T(*queue.arr[i]);
    }
}

template<class T>
TQueue<T> &TQueue<T>::operator=(const TQueue<T> &queue) {
    if (this == &queue)
        return *this;
    this->size = queue.size;
    this->front = queue.front;
    this->back = queue.back;
    this->count = queue.count;
    delete[] this->arr;
    this->arr = new T *[queue.size];
    return *this;
}

template<class T>
void TQueue<T>::push(T item) {
    if (this->is_full()) {
        throw std::overflow_error("Queue overflow");
    }
    if (this->back == -1)
        this->front = 0;
    this->back = (this->back + 1) % this->size;
    this->count++;
    this->arr[this->back] = new T(item);
}

template<class T>
T TQueue<T>::pop() {
    if (this->is_empty()) {
        throw std::overflow_error("Queue is empty. Cant pop any value");
    }
    T res = *this->arr[this->front];
    delete arr[this->front];
    arr[this->front] = 0;

    this->count--;
    if (count == 0) {
        this->front = -1;
        this->back = -1;
    }

    this->front = (this->front + 1) % this->size;
    return res;
}

template<class T>
TQueue<T>::~TQueue() {
    delete[] this->arr;
    this->arr = nullptr;
}

template<class T>
bool TQueue<T>::is_empty() {
    return this->count == 0;
}

template<class T>
bool TQueue<T>::is_full() {
    return this->count == this->size;
}

template<class T>
T TQueue<T>::get_max() {
    if (this->is_empty())
        throw std::range_error("queue is empty");

    int index = this->front;
    T max = *this->arr[index];
    for (int i = 1; i < this->count; ++i) {
        index = (this->front + 1) % this->size;
        T elem = *this->arr[index];
        if (elem > max)
            max = elem;
    }
    return max;
}

template<class T>
T TQueue<T>::get_least() {
    if (this->is_empty())
        throw std::range_error("queue is empty");

    int index = this->front;
    T least = *this->arr[index];
    for (int i = 1; i < this->count; ++i) {
        index = (this->front + 1) % this->size;
        T elem = *this->arr[index];
        if (elem < least)
            least = elem;
    }
    return least;
}

template<class T1>
istream &operator>>(istream &istream, TQueue<T1> &queue) {
    for (int i = 0; i < queue.size; ++i) {
        T1 elem;
        istream >> elem;
        queue.arr[i] = new T1(elem);
    }
    queue.count = queue.size;
    queue.front = 0;
    queue.back = queue.size - 1;
    return istream;
}

template<class T1>
ostream &operator<<(ostream &ostream, const TQueue<T1> &queue) {
    int index = queue.front;
    for (int i = 0; i < queue.count; ++i) {
        T1 elem = *queue.arr[index];
        ostream << elem << " ";
        index = (queue.front + 1) % queue.size;
    }
    ostream << "\n";
    return ostream;
}

template<class T>
TQueue<T> &TQueue<T>::load(const char *name) {
    std::ifstream file;
    file.open(name, std::fstream::in);
    if (!file.is_open())
        throw "Cant open such file";
    int size;
    file >> size;
    TQueue *queue = new TQueue(size);
    file >> queue->count;
    queue->front = 0;
    queue->back = queue->count - 1;
    file >> *queue;
    file.close();
    return *queue;
}

template<class T>
void TQueue<T>::save(const char *name) {
    fstream file;
    file.open(name, fstream::out);
    if (!file.is_open())
        throw "Cant open such file";
    file << this->size << " " << this->count << " " << "\n" << *this;
    file.close();
}


#endif //QUEUELIB_QUEUE_H

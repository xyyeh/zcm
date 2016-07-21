#include "util/Common.hpp"

template<class T, size_t N>
class ExpiringQueue
{
public:
    bool isEmpty();
    bool isFull();
    size_t getSize();
    void dequeue();
    void enqueue(u64 utime);
    T& first();
    T& last();

private:
    T queue[N];
    int front = 0;  // front: the next index to dequeue
    int back = 0;   // back-1: the last index enqueued
    bool full = false; // when front == back: the queue coul};
};

template<class T, size_t N>
inline bool ExpiringQueue<T,N>::isEmpty()
{
    return !full && front == back;
}

template<class T, size_t N>
inline bool ExpiringQueue<T,N>::isFull()
{
    return full;
}

template<class T, size_t N>
inline size_t ExpiringQueue<T,N>::getSize()
{
    if (isFull()) {
        return N;
    } else if (front <= back) {
        return back - front;
    } else { /* front > back */
        return N - (front - back);
    }
}

template<class T, size_t N>
void ExpiringQueue<T,N>::dequeue()
{
    assert(!isEmpty());
    front = (front+1) % N;
    full = false;
}

template<class T, size_t N>
void ExpiringQueue<T,N>::enqueue(u64 utime)
{
    assert(!isFull());
    queue[back] = utime;
    back = (back+1) % N;
    if(front == back)
        full = true;
}

template<class T, size_t N>
T& ExpiringQueue<T,N>::last()
{
    assert(!isEmpty());
    int i = back - 1;
    if(i < 0)
        i = N - 1;
    return queue[i];
}

template<class T, size_t N>
T& ExpiringQueue<T,N>::first()
{
    assert(!isEmpty());
    return queue[front];
}

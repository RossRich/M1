#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using std::cout;
using std::endl;

struct Box {
  uint8_t *data;
  uint16_t size;
};

template <typename T>
class Queue {
private:
  uint32_t front;
  uint32_t rear;
  uint32_t mSize;
  uint32_t mCapacity;
  T **array;

public:
  Queue(uint32_t capacity) {
    front = 0;
    mSize = 0;
    mCapacity = capacity;
    rear = capacity - 1;
    array = new T *[capacity];
  }

  ~Queue() { delete[] array; }

  inline bool isFull() { return mSize == mCapacity; }
  inline bool isEmpty() { return mSize == 0; }
  inline uint32_t size() { return mSize; }

  void enqueue(T *item) {
    if (isFull())
      return;

    rear++;
    if (rear >= mCapacity)
      rear = 0;

    array[rear] = item;

    mSize++;

    stats();
  }

  T *dequeue() {
    if (isEmpty())
      return nullptr;

    T *tItem = array[front];

    front++;
    if (front >= mCapacity)
      front = 0;

    mSize--;

    stats();

    return tItem;
  }

  void stats() {
    cout << "===" << endl;
    cout << "Size: " << size() << endl;
    cout << "isFull: " << isFull() << endl;
    cout << "isEmpty: " << isEmpty() << endl;
    cout << "Rear: " << rear << endl;
    cout << "Front: " << front << endl;
  }
};

void free(Box *item) {
  if (item == nullptr)
    return;

  cout << item->data << endl;
  cout << item->size << endl;
}

int main(int argc, char const *argv[]) {

  Queue<Box> q(5);

  q.stats();

  uint8_t aa[] = "Hello world";
  const char ab[] = "Hello world2";
  const char ac[] = "Hello world3";

  Box *b1 = new Box;
  Box *b2 = new Box;
  Box *b3 = new Box;

  b1->data = aa;
  b1->size = std::strlen((const char *)aa);

  b2->data = (uint8_t *)ab;
  b2->size = std::strlen(ab);

  b3->data = (uint8_t *)ac;
  b3->size = std::strlen(ac);

  q.enqueue(b1);
  q.enqueue(b2);
  q.enqueue(b3);

  free(q.dequeue());
  free(q.dequeue());
  free(q.dequeue());

  delete b1;
  delete b2;
  delete b3;


  return 0;
}

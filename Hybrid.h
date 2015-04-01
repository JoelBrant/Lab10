#if !defined (HYBRID_H)
#define HYBRID_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;
#include "SortedListDoublyLinked.h"
#include "DoubleNode.h"

template < class T >
class Hybrid
{

   private:
      SortedListDoublyLinked<T>* sldl;
      QueueLinked< DoubleNode<T> >* q;

   public:
      Hybrid(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~Hybrid();

      bool isEmpty();
      void enqueue(T* item);
      T* dequeue();
      ListDoublyLinkedIterator<T>* iterator();

};

template < class T >
Hybrid<T>::Hybrid(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   q = new QueueLinked< DoubleNode<T> >();
   sldl = new SortedListDoublyLinked<T>(comp_items, comp_keys);
}

template < class T >
Hybrid<T>::~Hybrid()
{
   delete q;
   delete sldl;
}

template < class T >
bool Hybrid<T>::isEmpty()
{
    return q->isEmpty();
}

template < class T >
ListDoublyLinkedIterator<T>* Hybrid<T>::iterator() 
{
   return sldl->iterator();
}
//DO THIS
//complete the implementation for the Hybrid ADT in two different ways
//as outlined in the Lab 10 description
//simply comment the first implementation out when working on the second implementation
//use the getKey method to dequeue/remove

// Slow Methods
/* template < class T >
   T* Hybrid<T>::dequeue() 
   {
      T* item = q->dequeue();
      String* key = item->getKey();
      sldl->remove(key);
      return item;
   }

   template < class T >
   void Hybrid<T>::enqueue(T* item) 
   {
      sldl->add(item);
      q->enqueue(item);
   }
*/

// Fast Methods
template < class T >
void Hybrid<T>::enqueue(T* item) 
{
   DoubleNode<T>* node = sldl->addDN(item);
   q->enqueue(node);
}

template < class T >
T* Hybrid<T>::dequeue() 
{
   DoubleNode<T>* node = q->dequeue();
   sldl->remove(node);
}

#endif

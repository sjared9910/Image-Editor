#ifndef _NODE
#define _NODE

template<typename ItemType>
class Node
{
 public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
  void setItem(const ItemType& anItem);
  void setNext(Node<ItemType>* nextNodePtr);
  const ItemType& getItem() const;
  Node<ItemType>* getNext() const;

private:
 ItemType item; // A data item
 Node<ItemType>* next; // Pointer to next node
}; // end Node

#include "Node.txx"
#endif

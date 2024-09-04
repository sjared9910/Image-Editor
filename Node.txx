#include "Node.hpp"

//default constructor
template<typename ItemType>
Node<ItemType>::Node() : next(nullptr)
{}

//parameterized constructor
template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{}

//parameterized constructor
template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) : item(anItem), next(nextNodePtr)
{}

//set item
template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
}

//set next
template<typename ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
  next = nextNodePtr;
}

//get item
template<typename ItemType>
const ItemType& Node<ItemType>::getItem() const
{
  return item;
}

//get next
template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
  return next;
}

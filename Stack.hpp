#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

#include "abstract_stack.hpp"
#include "Node.hpp"

template<typename T>
class Stack: public AbstractStack<T>
{  
public:
  //Stack constructor, makes an empty stack
  Stack();

  //Stack destructor
  virtual ~Stack();
  
  //copy constructor
  Stack(const Stack& rhs );

  //assignment operator
  Stack& operator=( Stack rhs ) noexcept;

  //Number of items in stack
  std::size_t size() const;

  //Determines if stack is empty
  bool isEmpty() const;

  //Pushes a new item to the top of the stack
  bool push(const T& newItem);

  //removes top item from stack and decreases size
  bool pop();

  //shows top item in stack, if empty throws an error
  const T& peek() const throw(std::range_error);

  //removes and shows top item in stack, if empty throws an error
  T peekPop() throw(std::range_error);

  //Deletes all items in stack
  void clear();

  //swaps two stacks
  void swap(Stack& lhs, Stack& rhs);
  
private:
  //size of stack
  std::size_t n;

  //entries
  Node<T> * topPtr;
};

#include "Stack.txx"
#endif


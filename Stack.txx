#include "Stack.hpp"
#include <utility> //for swap
#include <iostream>

//Stack constructor 
template<typename T >
Stack< T >::Stack()
{
	n = 0;	//size of stack
	topPtr = nullptr;	//top of stack
}

//Stack destructor
template<typename T >
Stack< T >::~Stack()
{
	//pops each variable in stack
	while (!isEmpty())
	{
		pop();
	}
	//size is set to 0
	n = 0;
}

//Make a copy of the parameter.It is also used by the operator= in the copy - swap paradigm.
template<typename T >
Stack< T >::Stack(const Stack< T >& rhs)
{
	//sets size
	n = rhs.size();

	//head of the stack
	Node<T>* origChainPtr = rhs.topPtr;

	//if the original stack is empty
	if (origChainPtr == nullptr)
	{
		topPtr = nullptr;
	}
	else
	{
		//copies first node
		topPtr = new Node<T>(origChainPtr->getItem(), origChainPtr->getNext());
		//copies the remaining nodes
		origChainPtr = origChainPtr->getNext();
		Node<T>* newChainPtr = topPtr;

		while (origChainPtr != nullptr)
		{
			//gets next item from original list
			Node<T>* newNodePtr = new Node<T>(origChainPtr->getItem(), origChainPtr->getNext());
			//advances pointer to next item in stack
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		//end of list
		newChainPtr->setNext(nullptr);
	}
}

//This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
template<typename T >
Stack < T >& Stack< T >::operator= (Stack< T > rhs) noexcept
{
	//copies list
	swap(*this, rhs);
	//returns copied list
	return *this;
}

//Returns the number of items on the stack.
template<typename T >
std::size_t Stack< T >::size() const
{
	//returns n stack size
	return n;
}

//Determines whether this stack is empty.
template<typename T >
bool Stack< T >::isEmpty() const
{
	//if the stack size is 0 and head is null stack is empty
	if (n == 0 && topPtr == nullptr)
	{
		return true;
	}
	return false;
}

//Pushes a new entry onto the top of the stack.
template<typename T >
bool Stack< T >::push(const T& newItem)
{
	//check to see if n is lower than maximum unsigned long long
	if (n < 18446744073709551615)
	{
		//creates new node at top pointer
		Node<T>* newNode = new Node<T>(newItem, topPtr);
		topPtr = newNode;

		//sets new node to null for next push
		newNode = nullptr;

		//size is incremented
		n++;
		return true;
	}
	return false;
}

//Pops the top item off of the stack. The stack size is decreased by 1.
template<typename T >
bool Stack< T >::pop()
{
	//result variable
	bool test = false;

	//if the list isnt empty
	if (!isEmpty())
	{
		//duplicates top
		Node<T>* deleteNode = topPtr;
		topPtr = topPtr->getNext();
		//deletes top node
		deleteNode->setNext(nullptr);
		delete deleteNode;
		deleteNode = nullptr;
		//size is decremented
		n--;
		//successful pop
		test = true;
	}
	return test;
}

//Returns the top item off of the stack without removing it. The stack size stays the same.
template<typename T >
const T& Stack< T >::peek() const throw (std::range_error)
{
	//if the stack isnt empty, the top item is returned
	if (!isEmpty())
	{
		return topPtr->getItem();
	}
	//if list is empty an execption is sent
	else
	{
		throw std::range_error("peek empty stack");
	}
}

//Removes the top item of the stack and returns it.
template<typename T >
T Stack< T >::peekPop() throw (std::range_error)
{
	//if the stack isnt empty
	if (!isEmpty())
	{
		//top item is loaded into variable
		T send = topPtr->getItem();
		//top variable is popped
		pop();
		//variable is returned
		return send;
	}
	//if list is empty an execption is sent
	else
	{
		throw std::range_error("peek empty stack");
	}
}

//Deletes all entries on the stack.
template<typename T >
void Stack< T >::clear()
{
	//pops each variable in stack
	while (!isEmpty())
	{
		pop();
	}
}

//This is the swap method. It will swap the internals of the two stacks.
template<typename T >
void Stack< T >::swap(Stack< T >& lhs, Stack< T >& rhs)
{
	//swaps lhs and rhs
	std::swap(lhs.n, rhs.n);
	std::swap(lhs.topPtr, rhs.topPtr);
}

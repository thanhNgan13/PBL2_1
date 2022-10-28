#include "Node.h"
template<typename T>
Node<T>::Node()
{
	next = nullptr;
}

template<typename T>
Node<T>::Node(T val)
{
	data = val;
	next = nullptr;
}

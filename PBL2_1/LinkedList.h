#pragma once
#include "Node.h"
template<typename T>
class LinkedList
{
private:
	Node<T>* head;
	int size;
public:
	const static int SORT_ASC = 0;
	const static int SORT_DESC = 1;
	LinkedList();
	void Insert(T);
	void Delete(T);
	void Delete();
	Node<T>* Search(T);
	void Display();

	int getCount();
	T getData();
	Node<T>* getNode();
	Node<T>* getNode(int index);

	bool isEmpty();

};


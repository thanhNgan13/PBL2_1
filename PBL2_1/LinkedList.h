#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node();
	explicit Node(T val);
};
template<typename T>
inline Node<T>::Node() {
	next = nullptr;
}

template<typename T>
inline Node<T>::Node(T val)
{
	data = val;
	next = nullptr;
}

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

template<typename T>
inline LinkedList<T>::LinkedList()
{
	head = nullptr;
	size = 0;
}

template<typename T>
inline void LinkedList<T>::Insert(T value)
{
	auto* newNode = new Node<T>(value);
	if (head == nullptr) {
		head = newNode;
		size++;
		return;
	}
	Node<T>* current = head;
	Node<T>* temp;
	do {
		temp = current;
		current = current->next;
	} while (current != nullptr);
	temp->next = newNode;
	size++;
}

template<typename T>
inline void LinkedList<T>::Delete(T value)
{
	Node<T>* current = head;
	Node<T>* prev = nullptr;
	if (current != nullptr && current->data == value) {
		head = current->next;
		delete current;
		size--;
		return;
	}
	else {
		while (current != NULL && current->data != value)
		{
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
		delete current;
		size--;
		return;
	}
}

template<typename T>
inline void LinkedList<T>::Delete()
{
	Node<T>* current = head;
	do {
		Node<T>* temp = current;
		current = current->next;
		delete temp;
	} while (current != nullptr);
	head = nullptr;
	size = 0;
}

template<typename T>
inline Node<T>* LinkedList<T>::Search(T value)
{
	Node<T>* current = head;
	while (current != nullptr) {
		if (current->data == value) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

template<typename T>
inline void LinkedList<T>::Display()
{
	Node<T>* current = head;
	wcout << L"Kích thước " << size << endl;
	while (current != nullptr)
	{
		wcout << current->data << endl;
		current = current->next;
	}
	wcout << endl;
}

template<typename T>
inline int LinkedList<T>::getCount()
{
	return this->size;
}

template<typename T>
inline T LinkedList<T>::getData()
{
	return this->head->data;
}

template<typename T>
inline Node<T>* LinkedList<T>::getNode()
{
	return this->head;
}

template<typename T>
inline Node<T>* LinkedList<T>::getNode(int index)
{
	Node<T>* current = head;
	int i = 0;
	do {
		if (i++ == index) {
			break;
		}
		current = current->next;
	} while (current != nullptr);
	return current;

}


template<typename T>
inline bool LinkedList<T>::isEmpty()
{
	if (this->size == 0) {
		return true;
	}
	return false;
}



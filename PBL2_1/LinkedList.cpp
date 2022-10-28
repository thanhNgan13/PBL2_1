#include "LinkedList.h"
#include <iostream>
using namespace std;

template<typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	size = 0;
}

template<typename T>
void LinkedList<T>::Insert(T value)
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
void LinkedList<T>::Delete(T value)
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
void LinkedList<T>::Delete()
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
Node<T>* LinkedList<T>::Search(T value)
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
void LinkedList<T>::Display()
{
	Node<T>* current = head;
	//wcout << L"Kích thước " << size << endl;
	while (current != nullptr)
	{
		wcout << current->data << endl;
		current = current->next;
	}
	wcout << endl;
}

template<typename T>
int LinkedList<T>::getCount()
{
	return this->size;
}

template<typename T>
T LinkedList<T>::getData()
{
	return this->head->data;
}

template<typename T>
Node<T>* LinkedList<T>::getNode()
{
	return this->head;
}

template<typename T>
Node<T>* LinkedList<T>::getNode(int index)
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
bool LinkedList<T>::isEmpty()
{
	if (this->size == 0) {
		return true;
	}
	return false;
}
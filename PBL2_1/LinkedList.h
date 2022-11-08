﻿#pragma once
#include <iostream>
#include "Header.h"
using namespace std;
inline void gotoxy1(short x, short y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };
	SetConsoleCursorPosition(h, c);
}

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
public:
	Node<T>* head;
	int size;
	const static int SORT_ASC = 0;
	const static int SORT_DESC = 1;
	LinkedList();
	void Insert(T);
	void Delete(T);
	void Delete();
	Node<T>* Search(T);
	void Display();

	T randomValue();

	int getCount() const;
	T getData() const;
	Node<T>* getNode() const;
	Node<T>* getNode(int index) const;
	Node<T>* getTail() const;
	
	void Sort(int order);

	bool isEmpty() const;

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
	}
	else {
		newNode->next = head;
		head = newNode;
	}

	size++;
}

template<typename T>
inline void LinkedList<T>::Delete(T value)
{
	Node<T>* current = head;
	Node<T>* prev = nullptr;
	if (current == nullptr) {
		wcerr << L"Danh sách rỗng không thể xóa!" << endl;
	}
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
	if (head == nullptr) {
		return;
	}
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
	if (current == nullptr) {
		wcout << L"Nothing!";
	}
	//wcout << L"Kích thước " << size << endl;
	int y = 6;
	while (current != nullptr)
	{
		gotoxy1(68, y);
		wcout << current->data;
		current = current->next;
		y++;
	}
	wcout << endl;
}

template<typename T>
inline T LinkedList<T>::randomValue()
{
	if (head == nullptr) {
		return T();
	}
	srand(time(NULL));
	T result = head->data;
	Node<T>* current = head;
	int n;
	for (n = 2; current != nullptr; n++) {
		if (rand() % n == 0)
			result = current->data;
		current = current->next;
	}
	return result;
}




template<typename T>
inline int LinkedList<T>::getCount() const
{
	return this->size;
}

template<typename T>
inline T LinkedList<T>::getData() const
{
	return this->head->data;
}

template<typename T>
inline Node<T>* LinkedList<T>::getNode() const
{
	return this->head;
}

template<typename T>
inline Node<T>* LinkedList<T>::getNode(int index) const
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
inline Node<T>* LinkedList<T>::getTail() const
{
	Node<T>* current = head;
	while (current != nullptr && current->next != nullptr)
		current = current->next;

	return current;
}

template<typename T>
inline void LinkedList<T>::Sort(int order)
{
	Node<T>* tmpPtr = head;
	Node<T>* tmpNxt = nullptr;

	if (tmpPtr == nullptr) {
		wcerr << L"Không thể xóa bởi vì danh sách rỗng!" << endl;
		return;
	}

	tmpNxt = head->next;

	T tmp;

	while (tmpNxt != nullptr) {
		while (tmpNxt != tmpPtr) {
			if (order == SORT_ASC) {
				if (tmpNxt->data < tmpPtr->data) {
					tmp = tmpPtr->data;
					tmpPtr->data = tmpNxt->data;
					tmpNxt->data = tmp;
				}
			}
			else if (order == SORT_DESC) {
				if (tmpNxt->data > tmpPtr->data) {
					tmp = tmpPtr->data;
					tmpPtr->data = tmpNxt->data;
					tmpNxt->data = tmp;
				}
			}
			else {
				wcerr << L"Giá trị yêu cầu sort không hợp lệ" << endl;
				return;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

template<typename T>
inline bool LinkedList<T>::isEmpty() const
{
	if (this->size == 0) {
		return true;
	}
	return false;
}


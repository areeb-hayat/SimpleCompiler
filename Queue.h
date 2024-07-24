#pragma once
#include<iostream>
#include<conio.h>
using namespace std;

template <class T>
class Node
{
public:
	T data;
	Node* next;

	Node()
	{
		//data = 0;
		next = NULL;
	}

	Node(T d, Node* n)
	{
		data = d;
		next = n;
	}

	Node(T d)
	{
		data = d;
		next = NULL;
	}

};

template <class T>
class Queue
{
public:
	Node<T>* front;
	Node<T>* rear;

	Queue()
	{
		front = NULL;
		rear = NULL;
	}

	bool isEmpty()
	{
		if (front == NULL)
			return true;
		return false;
	}

	bool found(T d) {
		Node <T>* temp = new Node<T>;
		temp = front;
		while (temp)
		{
			if (d == temp->data)
				return true;
			temp = temp->next;
		}
		return false;
	}

	void enqueue(T d) {
		Node <T>* n = new Node<T>;
		n->data = d;
		n->next = NULL;
		if (front == NULL)
		{
			front = n;
			rear = n;
		}
		else
		{
			rear->next = n;
			rear = n;
		}
	}

	T dequeue()
	{
		Node <T>* temp = new Node<T>;
		temp = front;
		front = front->next;
		T t = temp->data;
		delete temp;
		return t;
	}

	void deleteat(T val)
	{
		Node<T>* temp;
		temp = front;
		if (temp->data == val)
		{
			front = temp->next;
			delete temp;
			return;
		}
		while (temp)
		{
			if ((temp->next)->data == val)
			{
				Node <T>* temp2;
				temp2 = temp->next;
				temp->next = (temp->next)->next;
				delete temp2;
				break;
			}
			temp = temp->next;
		}
	}

	T Front()
	{
		return front->data;
	}

	void print()
	{
		Node <T>* temp = new Node<T>;
		temp = front;
		if (!front)
			return;
		if (temp == front)
		{
			cout << temp->data << " -> ";
			//return;
		}
		temp = temp->next;
		while (temp->next != NULL)
		{
			cout << temp->data << " -> ";
			temp = temp->next;
		}
		cout << temp->data;
		cout << endl << endl;
	}
};

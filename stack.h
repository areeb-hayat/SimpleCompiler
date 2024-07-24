#pragma once
#include<iostream>
#include<iomanip>
#include<string>
#include<conio.h>
#include <fstream>
using namespace std;

template <class T>
class node
{
public:
	T val;
	node* next;

	node()
	{
		next = NULL;
	}
};

template <class T>
class stack
{
public:
	node<T>* top;
	int size;

	stack()
	{
		top = NULL;
		size = 0;
	}

	bool isEmpty()
	{
		if (top == NULL)
			return true;
		return false;
	}

	~stack()
	{
		node<T>* temp;
		for (int i = 0; i < size; i++)
		{
			if (top->next)
			{
				temp = top;
				top = top->next;
				delete temp;
			}
		}
		delete top;
		size = 0;
	}

	void push(const T valItem)
	{
		node<T>* temp = new node<T>;
		temp->val = valItem;
		temp->next = top;
		top = temp;
		size++;
	}

	T pop()
	{
		T data;
		bool emp = isEmpty();
		if (top/* && top->next*/)
		{
			node<T>* temp;
			temp = top;
			top = top->next;
			size--;
			data = temp->val;
			return data;
			//delete temp;
		}
		return NULL;
	}

	int sizeofstack()
	{
		return size;
	}

	node<T>* Peek()
	{
		return top;
	}

	void clear()
	{
		delete* this;
	}

	void print()
	{
		if (isEmpty())
			return;
		cout << endl;
		cout << top->val;
		node<T>* temp = new node<T>;
		temp = top;
		for (int i = 1; i < size; i++)
		{
			if (temp->next)
			{
				temp = temp->next;
				cout << endl << temp->val;
			}
		}
		cout << endl << endl;
	}
};


//bool validate(string path)
//{
//	ifstream my_file(path, ios::in);
//	string str;
//	stack<char> obj;
//	while (getline(my_file, str))
//	{
//		int i = 0;
//		while (str[i] != '\0')
//		{
//			if ((str[i] == '{') || (str[i] == '}'))
//				obj.push(str[i]);
//			i++;
//		}
//	}
//
//	int count1 = 0, count2 = 0;
//	char c;
//	for (int i = 0; i < obj.size; i++)
//	{
//		c = obj.pop();
//		if (c == '{')
//			count1++;
//		else if (c == '}')
//			count2++;
//	}
//
//	if (count1 == count2)
//		return false;
//	else
//		return true;
//}

template <class T>
class MinStack {
public:
	stack<T> s;
	stack<T> aux;

	void push(int data) // push element in main stack, push element in aux stack if it satisfies the
	{
		node<T>* temp = new node<T>;
		temp->val = data;
		temp->next = s.top;
		s.top = temp;
		s.size++;
		if ((aux.isEmpty()) || (data <= aux.top->val))
		{
			node<T>* temp1 = new node<T>;
			temp1->val = data;
			temp1->next = aux.top;
			aux.top = temp1;
			aux.size++;
		}
	}
	void pop()
	{
		if (aux.top->val == s.top->val)
		{
			aux.pop();
		}
		s.pop();
	}
	int top()
	{
		return s.top->val;
	}
	int size()
	{
		return s.size;
	}
	bool isEmpty()
	{
		if (s.isEmpty())
			return true;
		else
			return false;
	}
	int getMin()
	{
		return aux.top->val;
	}
};
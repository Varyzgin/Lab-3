#pragma once
#include <iostream>
using namespace std;
template <class T>
class TStack
{
	T* mas;
	int size;
	int pos;
public:
	TStack(int _size = 1000);
	TStack(const TStack& TS);
	~TStack();
	TStack& operator=(const TStack& TS);
	bool operator==(const TStack& TS);
	bool operator!=(const TStack& TS);
	bool Empty();
	bool Full();
	void Push(T El);
	T Pop();
	T Top();
	void Clear();
	friend ostream& operator<<(ostream& ost, const TStack& TS) {
		for (int i = TS.pos1; i >= 0; i--)
			ost << TS.mas[i] << ' ';
		ost << "/ ";
		for (int i = TS.pos2; i < TS.size; i++)
			ost << TS.mas[i] << ' ';
		return ost;
	}
};

template <class T>
TStack<T>::TStack(int _size) {
	size = _size;
	mas = new T[size];
	pos = -1;
}
template <class T>
TStack<T>::TStack(const TStack& TS) {
	size = TS.size;
	mas = new T[size];
	pos = TS.pos;
	for (int i = 0; i <= pos; i++) {
		mas[i] = TS.mas[i];
	}
}
template <class T>
TStack<T>::~TStack() {
	delete[] mas;
}
template <class T>
TStack<T>&TStack<T>::operator=(const TStack& TS) {
	if (size != TS.size)
	{
		delete[] mas;
		size = TS.size;
		mas = new T[size];
	}
	pos = TS.pos;
	for (int i = 0; i <= pos; i++) {
		mas[i] = TS.mas[i];
	}
	return *this;
}
template <class T>
bool TStack<T>::operator==(const TStack& TS) {
	if (size != TS.size)
		return false;
	for (int i = 0; i <= pos; i++)
		if (mas[i] != TS.mas[i])
			return false;
	return true;
}
template <class T>
bool TStack<T>::operator!=(const TStack& TS) {
	return !operator==(TS);
}
template <class T>
bool TStack<T>::Empty() { // проверка на пустоту
	if (pos == -1)
		return true;
	else
		return false;
}
template <class T>
bool TStack<T>::Full() { // проверка на полноту стека
	if (pos == size - 1)
		return true;
	else
		return false;
}
template <class T>
void TStack<T>::Push(T El) { // положить элемент в стека
	if (Full()) throw "Stack full";
	pos++;
	mas[pos] = El;
}
template <class T>
T TStack<T>::Pop() { // изъять
	if (Empty()) throw "Stack empty";
	T El = mas[pos];
	pos--;
	return El;
}
template <class T>
T TStack<T>::Top() { // отсканить
	if (Empty()) throw "Stack empty";
	T El = mas[pos];
	return El;
}
template <class T>
void TStack<T>::Clear() { // очистить
	pos = -1;
}
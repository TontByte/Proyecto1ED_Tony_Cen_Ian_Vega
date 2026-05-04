/*
Clase HeapPriorityQueue elaborada en clase
Utilizada para el atributo pCola en la clase Area
Tiene como funcion organizar los tiquetes que entran en cada area
*/

#pragma once
#include <iostream>
#include <stdexcept>
#include "PriorityQueue.h"
#include "Pair.h"
#include "MinHeap.h"
#include "Util.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> { //agregar que crezca x2 cuando llega al limite
private:
	MinHeap<Pair<int, E>>* pairs;

public:
	HeapPriorityQueue(int max = DEFAULT_MAX) {
		pairs = new MinHeap<Pair<int, E>>(max);
	}
	~HeapPriorityQueue() {
		delete pairs;
	}

	void insert(E element, int priority) {
		Pair<int, E> p(priority, element);
		pairs->insert(p);
	}

	E min() {
		Pair<int, E> p = pairs->first();
		return p.value;
	}

	E removeMin() {
		Pair<int, E> p = pairs->removeFirst();
		return p.value;
	}

	void clear() {
		pairs->clear();
	}

	int getSize() {
		return pairs->getSize();
	}

	bool isEmpty() {
		return pairs->isEmpty();
	}

	void print() {
		pairs->print();
	}

};


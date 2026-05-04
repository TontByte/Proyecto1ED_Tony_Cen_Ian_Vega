#pragma once
#include <iostream>
#include <stdexcept>
#include "Area.h"
#include "ArrayList.h"

using std::cout;
using std::runtime_error;
using std::endl;

class AreaManager{
private:
	ArrayList<Area>* areas;

public:
	AreaManager() {
		areas = new ArrayList<Area>();
	}

	~AreaManager() {
		delete areas;
	}

	bool createArea(string descripcion, string codigo, int cantV) {
		Area a()
		areas->insert()
	}

};


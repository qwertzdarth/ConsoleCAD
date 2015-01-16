// ConsoleCAD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConsoleBuffer.h"
#include "Colors.h"
#include "Shapes.h"
#include "ShapeContainer.h"
#include <sstream>

using namespace std;

void draw_cool_things() {
	ShapeContainer* sc = new ShapeContainer(107, 50);
	Shape* circ = (Shape*)new Circle(11, 11, '*', RED, false, 10);
	Shape* rect = (Shape*)new Rectangle(26, 1, '#', LIGHTMAGENTA, false, 20, 20);
	Shape* l1 = (Shape*)new Line(51, 1, '\\', LIGHTBLUE, false, 20, 20);
	Shape* l2 = (Shape*)new Line(51, 21, '/', LIGHTBLUE, false, 20, -20);
	Shape* tri = (Shape*)new Triangle(76, 21, 'A', LIGHTGREEN, false, 15, -20, 30, 0);
	Shape* tex = (Shape*)new Text(96, 23, ' ', WHITE, false, "\x0A9 Sony Inc.");

	sc->add(circ, "ps_circle");
	sc->add(rect, "ps_rect");
	sc->add(l1, "ps_x1");
	sc->add(l2, "ps_x2");
	sc->add(tri, "ps_triangle");
	sc->add(tex, "ps_sonyinc");

	for (int r = 11; r > 9; r--) {
		Shape* sg_circ_outer = (Shape*)new Circle(13, 36, '*', DARKGRAY, false, r);
		sc->add(sg_circ_outer, "sg_outer_" + to_string(r));
	}

	for (int r = 9; r > 0; r--) {
		Shape* sg_circ = (Shape*)new Circle(13, 36, '*', LIGHTBLUE, false, r);
		sc->add(sg_circ, "sg_" + to_string(r));
	}

	Shape* text1 = (Shape*)new Text(7, 49, ' ', WHITE, false, "Stargate SG-1");
	sc->add(text1, "sg_text");

	sc->draw();
}
 
int _tmain(int argc, _TCHAR* argv[])
{
	for (;;) {
		string input;
		getline(cin, input);

		vector<string>* str_arr = new vector<string>();
		istringstream iss(input);

		

		do {
			string sub;
			iss >> sub;
			str_arr->push_back(sub);
		} while (iss);

		for (auto & element : *str_arr) {
			cout << element << endl;
		}

		cout << input << endl;
	}

	cin.ignore();
	return 0;
}


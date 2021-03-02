#include <iostream>
#include <fstream>
#include <vector>
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Box.H"

using namespace std;

void getMatrix()
{
	int n, m;
	double c;
	vector<double> matrice;
	ifstream input;
	string fileName("..\\outputGA\\outputMatrice.txt");

	input.open(fileName.c_str());

	if (input.is_open())
	{
		input >> n;
		input >> m;

		for (int i = 0; i < n * m * n * m; i++)
		{
			input >> c;
			matrice.push_back(c);
		}
		input.close();

		for (int i = 0; i < n * m * n * m; i++)
		{
			cout << matrice[i];
			if ((i % 12) == 11)
				cout << endl;
		}
	}
	else
	{
		cout << "file non letto" << endl;
	}

}

int main()
{
	//getMatrix();
	Fl_Window* window = new Fl_Window(340, 180);
	/*Fl_Box* box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD + FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_SHADOW_LABEL);*/
	window->end();
	window->show();
	return Fl::run();
}
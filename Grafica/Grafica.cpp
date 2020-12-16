#include <iostream>
#include <fstream>
#include <vector>
#include "FL\Fl_Button.H"

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
	getMatrix();
}
#include <datiInput/datiInput.h>

Dati::Dati(const char* path)
{
	elementi = 1;
	unsigned int c;
	double d;
	ifstream input;
	input.open(path);

	if (input.is_open())
	{
		//inizializza dimensione
		input >> c;
		dim.push_back(c);
		input >> c;
		dim.push_back(c);

		elementi = dim[0] * dim[1];

		//inizializza popolazione
		for (int i = 0; i < elementi; i++)
		{
			input >> d;
			popolazione.push_back(d);
		}

		//inizializza spostamenti
		for (int i = 0; i < elementi*elementi; i++)
		{
			input >> d;
			spostamenti.push_back(d);
		}

		//inizializza binari
		for (int i = 0; i < elementi*elementi; i++)
		{
			input >> c;
			binari.push_back(c);
		}

		input.close();
	}
	else
	{
		cout << "file non letto" << endl;
	}
}

vector<unsigned int> Dati::getDim() const
{
	return dim;
}

vector<double> Dati::getPopolazione() const
{
	return popolazione;
}

vector<double> Dati::getSpostamenti() const
{
	return spostamenti;
}

vector<bool> Dati::getBinari() const
{
	return binari;
}

void Dati::printPopolazione()
{
	for (int i = 0; i <elementi; i++)
	{
		cout << popolazione[i];
		if ((i % dim[1]) == (dim[1]-1))
			cout << endl;
	}
}

void Dati::printSpostamenti()
{
	for (int i = 0; i < elementi*elementi; i++)
	{
		cout << popolazione[i];
		if ((i % elementi) == (elementi - 1))
			cout << endl;
	}
}

void Dati::printBinari()
{
	for (int i = 0; i < elementi * elementi; i++)
	{
		cout << popolazione[i];
		if ((i % elementi) == (elementi - 1))
			cout << endl;
	}
}
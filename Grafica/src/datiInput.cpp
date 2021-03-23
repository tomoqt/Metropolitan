#include <datiInput/datiInput.h>

Dati::Dati(const char* path)
{
	elementi = 1;
	totPopolazione = 0;
	maxPop = 0;
	minPop = LLONG_MAX;
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
			totPopolazione += d;
			popolazione.push_back(d);
			if (d > maxPop)
				maxPop = d;
			if (d < minPop)
				minPop = d;
		}

		//inizializza spostamenti
		for (int i = 0; i < elementi; i++)
		{
			double maxSpos = 0;
			double minSpos = 1;
			
			for(int j = 0; j < elementi; j++)
			{
				input >> d;
				spostamenti.push_back(d);
				if (d > maxSpos)
					maxSpos = d;
				if (d < minSpos && i != j)
					minSpos = d;
			}
			minSpostamenti.push_back(minSpos);
			maxSpostamenti.push_back(maxSpos);
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

double Dati::getTotPopolazione() const
{
	return totPopolazione;
}

double Dati::getMaxPop() const
{
	return maxPop;
}

double Dati::getMinPop() const
{
	return minPop;
}

vector<double> Dati::getMaxSpos() const
{
	return maxSpostamenti;
}

vector<double> Dati::getMinSpos() const
{
	return minSpostamenti;
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
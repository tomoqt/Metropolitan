#ifndef DATI_INPUT_H
#define DATI_INPUT_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Dati
{
public:
	Dati(const char* path);
	vector<unsigned int> getDim() const;
	vector<double> getPopolazione() const;
	vector<double> getSpostamenti() const;
	vector<bool> getBinari() const;
	double getTotPopolazione() const;
	double getMaxPop() const;
	double getMinPop() const;
	vector<double> getMaxSpos() const;
	vector<double> getMinSpos() const;
	void printPopolazione();
	void printSpostamenti();
	void printBinari();

private:
	int elementi;
	vector<unsigned int> dim;
	vector<double> popolazione;
	vector<double> spostamenti;
	vector<bool> binari;
	double totPopolazione;
	double maxPop;
	double minPop;
	vector<double> maxSpostamenti;
	vector<double> minSpostamenti;
};
#endif
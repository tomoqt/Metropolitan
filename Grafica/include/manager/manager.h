#ifndef MANAGER_H
#define MANAGER_H

#include <datiInput/datiInput.h>

class Global
{
public:
	Global(const char* path);
	const vector<double>& getNodesVector() const;
	vector<double>& getNodesVector();
	int getActivatedNode() const;
	void setActivatedNode(int x);
	bool getRailwayStatus() const;
	void setRailwayStatus(bool status);
	Dati getDati() const;
	int getRaws() const;
	int getColumns() const;

private:
	vector<double> nodes;
	int activatedNode;
	bool railwayStatus;
	Dati dati;
};

#endif
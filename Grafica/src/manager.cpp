#include <manager/manager.h>

Global::Global(const char* path) : activatedNode(-1), dati(path)
{

}

const vector<double>& Global::getNodesVector() const
{
	return nodes;
}

vector<double>& Global::getNodesVector()
{
	return nodes;
}

int Global::getActivatedNode() const
{
	return activatedNode;
}

void Global::setActivatedNode(int x)
{
	activatedNode = x;
}

Dati Global::getDati() const
{
	return dati;
}

int Global::getRaws() const
{
	return dati.getDim()[0];
}

int Global::getColumns() const
{
	return dati.getDim()[1];
}

#include "ruutu.h"


Ruutu::Ruutu(int sarake, int rivi)
{
	_sarake = sarake;
	_rivi = rivi;
}


int Ruutu::getRivi()
{
	return _rivi;
}


int Ruutu::getSarake()
{
	return _sarake;
}


void Ruutu::setRivi(int rivi) 
{
	_rivi = rivi;
}


void Ruutu::setSarake(int sarake) 
{
	_sarake = sarake;
}

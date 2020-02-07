#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
#include <iostream>
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/


	
}

Siirto lisaaSiirto(Ruutu& alkuRuutu, Ruutu& loppuRuutu, int x, int y, const char* nimi)
{
	loppuRuutu.setRivi(y + 2);
	loppuRuutu.setSarake(x);
	Siirto siirto = Siirto(alkuRuutu, loppuRuutu);
	std::wcout << nimi << " " << siirto.getAlkuruutu().getSarake() + 1 << ", " << siirto.getAlkuruutu().getRivi() + 1 <<
		" : " << siirto.getLoppuruutu().getSarake() + 1 << ", " << siirto.getLoppuruutu().getRivi() + 1 << std::endl;

	return siirto;
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

	Ruutu* loppuRuutu = new Ruutu(0,0);
	if(vari == 0)
	{
		if(y == 1) // Valkoinen sotilas, ei ole liikkunut
			if(asema->_lauta[y + 2][x] == NULL) // Kaksoisaskel
				lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y+2, "Sotilas"));
		
		if(asema->_lauta[y + 1][x] == NULL) // Yksi askel
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y + 1, "Sotilas"));

		if(asema->_lauta[y + 1][x + 1] != NULL && asema->_lauta[y + 1][x + 1]->getVari() == 1) // Syönti oikealle
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y + 1, "Sotilas"));
		
		if(asema->_lauta[y + 1][x - 1] != NULL && asema->_lauta[y + 1][x - 1]->getVari() == 1) // Syönti vasemmalle
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x -1, y + 1, "Sotilas"));
	}
	else
	{
		if(y == 6) // Musta sotilas, ei ole liikkunut
			if(asema->_lauta[y - 2][x] == NULL) // Kaksois askel
				lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y - 2, "Sotilas"));

		if(asema->_lauta[y - 1][x] == NULL) // Yksi askel
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y - 1, "Sotilas"));

		if(asema->_lauta[y - 1][x + 1] != NULL && asema->_lauta[y - 1][x + 1]->getVari() == 0) // Syönti oikealle
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y - 1, "Sotilas"));

		if(asema->_lauta[y - 1][x - 1] != NULL && asema->_lauta[y - 1][x - 1]->getVari() == 0) // Syönti vasemmalle
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x -1, y - 1, "Sotilas"));

	}

	delete loppuRuutu;
	delete alkuRuutu;
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}

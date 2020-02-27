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

Siirto lisaaSiirto(Ruutu& alkuRuutu, Ruutu& loppuRuutu, int x, int y, const char* nimi)
{
	loppuRuutu.setRivi(y);
	loppuRuutu.setSarake(x);
	Siirto siirto = Siirto(alkuRuutu, loppuRuutu);
	//std::wcout << nimi << " " << siirto.getAlkuruutu().getSarake() + 1 << ", " << siirto.getAlkuruutu().getRivi() + 1 <<
	//	" : " << siirto.getLoppuruutu().getSarake() + 1 << ", " << siirto.getLoppuruutu().getRivi() + 1 << std::endl;


	return siirto;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();
	Ruutu* loppuRuutu = new Ruutu(0, 0);

	const char* nimi = "";
	if(asema->_lauta[alkuRuutu->getRivi()][alkuRuutu->getSarake()]->getKoodi() == VT ||
	   asema->_lauta[alkuRuutu->getRivi()][alkuRuutu->getSarake()]->getKoodi() == MT)
	{
		nimi = "Torni";
	}
	else nimi = "Daami";

	for(int j = 0; j < 4; j++)
	{
		for(int i = 1; i <= 8; i++)
		{
			int tempX = 0;
			int tempY = 0;
			if(j == 0) tempX = x + i, tempY = y;
			if(j == 1) tempX = x - i, tempY = y;
			if(j == 2) tempX = x, tempY = y - i;
			if(j == 3) tempX = x, tempY = y + i;

			Nappula* nappula = asema->_lauta[tempY][tempX];

			if(tempX < 8 && tempX > -1 && tempY < 8 && tempY > -1)
			{
				// Jos edessä ei ole mitään, lisätään uusi siirto
				if(nappula == NULL) lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
				else if(nappula != NULL)
				{
					if(((vari == 0 && nappula->getVari() == 0)) || (vari == 1 && nappula->getVari() == 1)) break; // Jos oma nappula edessä, lopetetaan looppi
					if((vari == 0 && nappula->getVari()) == 1 || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
					{
						lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
						break;
					}
				}
			}
		}
	}
	delete loppuRuutu;
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();
	Ruutu* loppuRuutu = new Ruutu(0, 0);

	const int kood_deltat[8][2] =
	{
		{-1, 2}, {-1, -2}, {1, 2}, {1, -2},
		{-2, 1}, {-2, -1}, {2, 1}, {2, -1}
	};

	for(int d = 0; d < 8; d++)
	{
		int dx = kood_deltat[d][0];
		int dy = kood_deltat[d][1];

		int uusi_x = x + dx;
		int uusi_y = y + dy;

		if(uusi_x < 0 || uusi_x > 7 || uusi_y < 0 || uusi_y > 7)
			continue;

		Nappula* nappula = asema->_lauta[uusi_y][uusi_x];

		if((nappula != NULL && vari == 0 && nappula->getVari() == 0) || (nappula != NULL && vari == 1 && nappula->getVari() == 1))
			continue;

		lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, uusi_x, uusi_y, "Ratsu"));
	}

}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();
	Ruutu* loppuRuutu = new Ruutu(0, 0);

	const char* nimi = "";
	if(asema->_lauta[y][x]->getKoodi() == VL ||
	   asema->_lauta[y][x]->getKoodi() == ML)
	{
		nimi = "Lahetti";
	}
	else nimi = "Daami";

	for(int j = 0; j < 4; j++)
	{
		for(int i = 1; i <= 8; i++)
		{
			int tempX = 0;
			int tempY = 0;
			if(j == 0) tempX = x + i, tempY = y + i;
			if(j == 1) tempX = x - i, tempY = y + i;
			if(j == 2) tempX = x + i, tempY = y - i;
			if(j == 3) tempX = x - i, tempY = y - i;

			Nappula* nappula = asema->_lauta[tempY][tempX];

			if(tempX < 8 && tempX > -1 && tempY < 8 && tempY > -1)
			{
				// Jos edessä ei ole mitään, lisätään uusi siirto
				if(nappula == NULL) lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
				else if(nappula != NULL)
				{
					if(((vari == 0 && nappula->getVari() == 0)) || (vari == 1 && nappula->getVari() == 1)) break; // Jos oma nappula edessä, lopetetaan looppi
					if(( vari == 0 && nappula->getVari()) == 1  || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
					{
						lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
						break;
					}
				}
			}
		}
	}
	
	delete loppuRuutu;
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	this->Lahetti::annaSiirrot(lista, alkuRuutu, asema, vari);
	this->Torni::annaSiirrot(lista, alkuRuutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();
	Ruutu* loppuRuutu = new Ruutu(0, 0);

	for(int j = 0; j < 4; j++)
	{
		int tempX = 0;
		int tempY = 0;
		if(j == 0) tempX = x + 1, tempY = y + 1;
		if(j == 1) tempX = x - 1, tempY = y + 1;
		if(j == 2) tempX = x + 1, tempY = y - 1;
		if(j == 3) tempX = x - 1, tempY = y - 1;

		Nappula* nappula = asema->_lauta[tempY][tempX];

		if(tempX < 8 && tempX > -1 && tempY < 8 && tempY > -1)
		{
			// Jos edessä ei ole mitään, lisätään uusi siirto
			if(nappula == NULL) lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
			else if(nappula != NULL)
			{
				if((vari == 0 && nappula->getVari()) == 1 || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
				{
					lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
				}
			}
		}
	}

	for(int j = 0; j < 4; j++)
	{
		int tempX = 0;
		int tempY = 0;
		if(j == 0) tempX = x + 1, tempY = y;
		if(j == 1) tempX = x - 1, tempY = y;
		if(j == 2) tempX = x, tempY = y - 1;
		if(j == 3) tempX = x, tempY = y + 1;

		Nappula* nappula = asema->_lauta[tempY][tempX];

		if(tempX < 8 && tempX > -1 && tempY < 8 && tempY > -1)
		{
			// Jos edessä ei ole mitään, lisätään uusi siirto
			if(nappula == NULL) lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
			else if(nappula != NULL)
			{
				if((vari == 0 && nappula->getVari()) == 1 || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
					lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
			}
		}

	}

	delete loppuRuutu;
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

		//Ohesta lyönnit
		if(asema->_lauta[y][x - 1] != NULL && asema->_lauta[y][x - 1]->getKoodi() == MS && asema->kaksoisaskelSarakkeella == x-1)
		{
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x - 1, y + 1, "Sotilas"));
			std::wcout << "ohestalyonti\n";
		}
		else if(asema->_lauta[y][x + 1] != NULL && asema->_lauta[y][x + 1]->getKoodi() == MS && asema->kaksoisaskelSarakkeella == x + 1)
		{
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y + 1, "Sotilas"));
			std::wcout << "ohestalyonti\n";
		}

	}
	else
	{
		if(y == 6) // Musta sotilas, ei ole liikkunut
			if(asema->_lauta[y - 2][x] == NULL) // Kaksois askel
				lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y - 2, "Sotilas"));

		if(asema->_lauta[y - 1][x] == NULL) // Yksi askel
		{
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y - 1, "Sotilas"));
		}
			

		if(asema->_lauta[y - 1][x + 1] != NULL && asema->_lauta[y - 1][x + 1]->getVari() == 0) // Syönti oikealle
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y - 1, "Sotilas"));

		if(asema->_lauta[y - 1][x - 1] != NULL && asema->_lauta[y - 1][x - 1]->getVari() == 0) // Syönti vasemmalle
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x -1, y - 1, "Sotilas"));

		//Ohesta lyönnit
		if(asema->_lauta[y][x - 1] != NULL && asema->_lauta[y][x - 1]->getKoodi() == VS && asema->kaksoisaskelSarakkeella == x - 1)
		{
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x - 1, y - 1, "Sotilas"));
			std::wcout << "ohestalyonti\n";
		}
		else if(asema->_lauta[y][x + 1] != NULL && asema->_lauta[y][x + 1]->getKoodi() == VS && asema->kaksoisaskelSarakkeella == x + 1)
		{
			lista.push_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y - 1, "Sotilas"));
			std::wcout << "ohestalyonti\n";
		}

	}

	delete loppuRuutu;
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}

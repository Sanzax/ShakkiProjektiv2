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


void Torni::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

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
				if(nappula == NULL) lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
				else if(nappula != NULL)
				{
					if(((vari == 0 && nappula->getVari() == 0)) || (vari == 1 && nappula->getVari() == 1)) break; // Jos oma nappula edessä, lopetetaan looppi
					if((vari == 0 && nappula->getVari()) == 1 || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
					{
						lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));
						//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
						break;
					}
				}
			}
		}
	}

}


static const int kood_deltat[8][2] =
{
	{-1, 2}, {-1, -2}, {1, 2}, {1, -2},
	{-2, 1}, {-2, -1}, {2, 1}, {2, -1}
};


void Ratsu::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

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

		lista.emplace_back(*alkuRuutu, Ruutu(uusi_x, uusi_y));
		//lista.emplace_back(lisaaSiirto(*alkuRuutu, loppuRuutu, uusi_x, uusi_y, "Ratsu"));
	}

}


void Lahetti::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

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
				if(nappula == NULL) lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
				else if(nappula != NULL)
				{
					if(((vari == 0 && nappula->getVari() == 0)) || (vari == 1 && nappula->getVari() == 1)) break; // Jos oma nappula edessä, lopetetaan looppi
					if(( vari == 0 && nappula->getVari()) == 1  || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
					{
						lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));
						//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, nimi));
						break;
					}
				}
			}
		}
	}
}


void Daami::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	this->Lahetti::annaSiirrot(lista, alkuRuutu, asema, vari);
	this->Torni::annaSiirrot(lista, alkuRuutu, asema, vari);
}


void Kuningas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

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
			if(nappula == NULL) lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
			else if(nappula != NULL)
			{
				if((vari == 0 && nappula->getVari()) == 1 || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
				{
					lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));
					//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
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
			if(nappula == NULL) lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
			else if(nappula != NULL)
			{
				if((vari == 0 && nappula->getVari()) == 1 || (vari == 1 && nappula->getVari() == 0)) // Jos vastustaja edessä syödään se ja lopetetaan looppi
					lista.emplace_back(*alkuRuutu, Ruutu(tempX, tempY));//lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, tempX, tempY, "Kuningas"));
			}
		}

	}
}

/*
void Sotilas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

	Ruutu* loppuRuutu = new Ruutu(0,0);
	if(vari == 0)
	{
		if(y == 1) // Valkoinen sotilas, ei ole liikkunut
			if(asema->_lauta[y + 2][x] == NULL) // Kaksoisaskel
				lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y+2, "Sotilas"));
		
		if(asema->_lauta[y + 1][x] == NULL) // Yksi askel
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y + 1, "Sotilas"));

		if(asema->_lauta[y + 1][x + 1] != NULL && asema->_lauta[y + 1][x + 1]->getVari() == 1) // Syönti oikealle
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y + 1, "Sotilas"));
		
		if(asema->_lauta[y + 1][x - 1] != NULL && asema->_lauta[y + 1][x - 1]->getVari() == 1) // Syönti vasemmalle
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x -1, y + 1, "Sotilas"));

		//Ohesta lyönnit
		if(asema->_lauta[y][x - 1] != NULL && asema->_lauta[y][x - 1]->getKoodi() == MS && asema->kaksoisaskelSarakkeella == x-1)
		{
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x - 1, y + 1, "Sotilas"));
		}
		else if(asema->_lauta[y][x + 1] != NULL && asema->_lauta[y][x + 1]->getKoodi() == MS && asema->kaksoisaskelSarakkeella == x + 1)
		{
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y + 1, "Sotilas"));
		}

	}
	else
	{
		if(y == 6) // Musta sotilas, ei ole liikkunut
			if(asema->_lauta[y - 2][x] == NULL) // Kaksois askel
				lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y - 2, "Sotilas"));

		if(asema->_lauta[y - 1][x] == NULL) // Yksi askel
		{
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x, y - 1, "Sotilas"));
		}
			
		if(asema->_lauta[y - 1][x + 1] != NULL && asema->_lauta[y - 1][x + 1]->getVari() == 0) // Syönti oikealle
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y - 1, "Sotilas"));

		if(asema->_lauta[y - 1][x - 1] != NULL && asema->_lauta[y - 1][x - 1]->getVari() == 0) // Syönti vasemmalle
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x -1, y - 1, "Sotilas"));

		//Ohesta lyönnit
		if(asema->_lauta[y][x - 1] != NULL && asema->_lauta[y][x - 1]->getKoodi() == VS && asema->kaksoisaskelSarakkeella == x - 1)
		{
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x - 1, y - 1, "Sotilas"));
		}
		else if(asema->_lauta[y][x + 1] != NULL && asema->_lauta[y][x + 1]->getKoodi() == VS && asema->kaksoisaskelSarakkeella == x + 1)
		{
			lista.emplace_back(lisaaSiirto(*alkuRuutu, *loppuRuutu, x + 1, y - 1, "Sotilas"));
		}

	}

	delete loppuRuutu;
}
*/

void Sotilas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* alkuRuutu, Asema* asema, int vari)
{
	int x = alkuRuutu->getSarake();
	int y = alkuRuutu->getRivi();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->_lauta[y][x]->getVari();

	if(lahtoruudunNappulanVari == 0) // Valkoinen
	{
		if(y == 1) // Kaksoisaskel
		{
			for(int i = y + 1; i < y + 3; i++)
			{
				if(asema->_lauta[i][x] == NULL) lista.emplace_back(*alkuRuutu, Ruutu(x, i));
				else break;
			}
		}

		if(y == 2 || y == 3 || y == 4 || y == 5 || y == 6) // Perus siirrot
		{
			if(asema->_lauta[y + 1][x] == NULL) // Eteenpäin
			{
				if(y < 6)
					lista.emplace_back(*alkuRuutu, Ruutu(x, y + 1));
				else lisaaSotilaanKorotukset(&Siirto(*alkuRuutu, Ruutu(x, y + 1)), lista, asema);
			}

			if(x + 1 < 8) // viistoon oikealle
			{
				if(asema->_lauta[y + 1][x + 1] != NULL)
				{
					tuloruudunNappulanVari = asema->_lauta[y + 1][x + 1]->getVari();
					if(lahtoruudunNappulanVari != tuloruudunNappulanVari)
					{
						if(y < 6) lista.emplace_back(*alkuRuutu, Ruutu(x + 1, y + 1));
						else lisaaSotilaanKorotukset(&Siirto(*alkuRuutu, Ruutu(x + 1, y + 1)), lista, asema);
					}
				}
			}
			if(x - 1 > -1) // Viistoon vasemmalle
			{
				if(asema->_lauta[y + 1][x - 1] != NULL)
				{
					tuloruudunNappulanVari = asema->_lauta[y + 1][x - 1]->getVari();
					if(lahtoruudunNappulanVari != tuloruudunNappulanVari)
					{
						if(y < 6) lista.emplace_back(*alkuRuutu, Ruutu(x - 1, y + 1));
						else lisaaSotilaanKorotukset(&Siirto(*alkuRuutu, Ruutu(x - 1, y + 1)), lista, asema);
					}
				}
			}
		}
	}
	else if(lahtoruudunNappulanVari == 1) // Musta
	{
		if(y == 6) // Kaksoisaskel
		{
			for(int i = y - 1; i > y - 3; i--)
			{
				if(asema->_lauta[i][x] == NULL) lista.emplace_back(*alkuRuutu, Ruutu(x, i));
				else break;
			}
		}

		if(y == 5 || y == 4 || y == 3 || y == 2 || y == 1) // Perus siirrot
		{
			if(asema->_lauta[y - 1][x] == NULL) // Eteenpäin
			{
				if(y > 1)
					lista.emplace_back(*alkuRuutu, Ruutu(x, y - 1));
				else lisaaSotilaanKorotukset(&Siirto(*alkuRuutu, Ruutu(x, y - 1)), lista, asema);
			}

			if(x + 1 < 8) // viistoon oikealle
			{
				if(asema->_lauta[y - 1][x + 1] != NULL)
				{
					tuloruudunNappulanVari = asema->_lauta[y - 1][x + 1]->getVari();
					if(lahtoruudunNappulanVari != tuloruudunNappulanVari)
					{
						if(y > 1) lista.emplace_back(*alkuRuutu, Ruutu(x + 1, y - 1));
						else lisaaSotilaanKorotukset(&Siirto(*alkuRuutu, Ruutu(x + 1, y - 1)), lista, asema);
					}
				}
			}
			if(x - 1 > -1) // Viistoon vasemmalle
			{
				if(asema->_lauta[y - 1][x - 1] != NULL)
				{
					tuloruudunNappulanVari = asema->_lauta[y - 1][x - 1]->getVari();
					if(lahtoruudunNappulanVari != tuloruudunNappulanVari)
					{
						if(y > 1) lista.emplace_back(*alkuRuutu, Ruutu(x - 1, y - 1));
						else lisaaSotilaanKorotukset(&Siirto(*alkuRuutu, Ruutu(x - 1, y - 1)), lista, asema);
					}
				}
			}
		}
	}

	if(asema->kaksoisaskelSarakkeella != -1) //Ohesta lyönnit
	{
		if(vari == 0 && y == 4)
			if(asema->_lauta[4][asema->kaksoisaskelSarakkeella] && asema->_lauta[4][asema->kaksoisaskelSarakkeella]->getKoodi() == MS)
				lista.emplace_back(*alkuRuutu, Ruutu(asema->kaksoisaskelSarakkeella, 5));
		if(vari == 1 && y == 3)
			if(asema->_lauta[3][asema->kaksoisaskelSarakkeella] && asema->_lauta[3][asema->kaksoisaskelSarakkeella]->getKoodi() == VS)
				lista.emplace_back(*alkuRuutu, Ruutu(asema->kaksoisaskelSarakkeella, 2));
	}

}

void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::vector<Siirto>& lista, Asema* asema) 
{
	if(siirto->getLoppuruutu().getRivi() == 7)
	{
		// valkea korottaa
		siirto->_miksikorotetaan = asema->vd;
		lista.emplace_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->vt;
		lista.emplace_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->vl;
		lista.emplace_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->vr;
		lista.emplace_back(ratsuksi);
	}
	else if(siirto->getLoppuruutu().getRivi() == 0)
	{
		// musta korottaa
		siirto->_miksikorotetaan = asema->md;
		lista.emplace_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->mt;
		lista.emplace_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->ml;
		lista.emplace_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->mr;
		lista.emplace_back(ratsuksi);
	}
}

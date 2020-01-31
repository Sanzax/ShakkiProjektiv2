#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{

	//Saa unicode shakkinappulat toimimaan printf kanssa:
	//SetConsoleOutputCP(65001);
	//printf(q);
	//char q[] = "King: \xE2\x99\x94.\n";

	//Saa unicode shakkinappulat toimimaan cout:n kanssa:
	_setmode(_fileno(stdout), _O_U16TEXT);

	/*
		Kaksinkertainen for silmukka joka k�y asema-olion laudan l�pi ja jos
		siin� on nappula olio, niin kysyt��n sen nimi
		ja tulostetaan se muussa tapauksessa tulostetaan 2 tyhj�� v�lily�nti�.
		Parillisuuteen perustuen v�rj�t��n jokatoisen "ruudun" taustav�ri
	*/

	for(int y = 7; y >= 0; y--)
	{
		// Tulosta numerot sivulle
		std::wcout << y + 1;
		for(int x = 0; x < 8; x++)
		{
			//V�rj�� ruudukko
			if(y % 2 == 0)
			{
				if(x % 2 == 0) std::wcout << "\33[0;30;100m";
				else std::wcout << "\33[0;30;47m";
			}
			else
			{
				if(x % 2 == 0) std::wcout << "\33[0;30;47m";
				else std::wcout << "\33[0;30;100m";
			}

			//Tulosta nappula tai tyhj�
			if(_asema->_lauta[y][x]) std::wcout << _asema->_lauta[y][x]->getUnicode() << " ";
			else std::wcout << "  ";

			//Resetoi v�ri muutokset
			std::wcout << "\033[0m";
		}
		//Rivin vaihto kun rivi loppuu
		std::wcout << std::endl;
	}
	//Tulosta kirjaimet
	std::wcout << " A B C D E F G H";
}


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	std::string syote;
	char nappula;
	std::string aloitusKoordinaatti;
	std::string lopetusKoordinaatti;
	bool lyhytLinna = false;
	bool pitkaLinna = false;

	while (true) {
		std::cout << "Anna siirto" << std::endl;
		std::cin >> syote;
		nappula = syote[0];

		if (syote == "O-O") {
			lyhytLinna = true;
			break;
		}
		else if (syote == "O-O-O") {
			pitkaLinna = true;
			break;
		}

		if ( !(nappula == 'S' || nappula == 'K' || nappula == 'D' || nappula == 'L' || nappula == 'R' || nappula == 'T')) {
			std::cout << "Nappulatyypin sy�te ei ollut kelvollinen" << std::endl;
			continue;
		}


		aloitusKoordinaatti = std::string(1, syote[1]) + std::string(1, syote[2]);
		bool kirjainCheck = false;
		bool numeroCheck = false;

		for (int i = 0; i < 8; i++) {
			if (aloitusKoordinaatti[0] == 'a' + i) {
				break;
			}

			if (i == 7) {
				std::cout << "Aloituskoordinaatin kirjainsy�te ei ollut kelvollinen" << std::endl;
				kirjainCheck = true;
			}

		}

		
		for (int i = 0; i < 8; i++) {
			if ((int)aloitusKoordinaatti[1] == 49 + i) {
				break;
			}

			if (i == 7) {
				std::cout << "Aloituskoordinaatin numerosy�te ei ollut kelvollinen" << std::endl;
				numeroCheck = true;
			}

		}
		
		

		if (kirjainCheck || numeroCheck) {
			continue;
		}

		kirjainCheck = false;
		numeroCheck = false;

		//std::cout << aloitusKoordinaatti << std::endl;

		if (syote[3] != '-') {
			std::cout << "Viivasy�te ei ollut kelvollinen" << std::endl;
			continue;
		}

		lopetusKoordinaatti = std::string(1, syote[4]) + std::string(1, syote[5]);

		for (int i = 0; i < 8; i++) {
			if (lopetusKoordinaatti[0] == 'a' + i) {
				break;
			}

			if (i == 7) {
				std::cout << "Lopetuskoordinaatin kirjainsy�te ei ollut kelvollinen" << std::endl;
				kirjainCheck = true;
			}
		}

		for (int i = 0; i < 8; i++) {
			if ((int)lopetusKoordinaatti[1] == 49 + i) {
				break;
			}

			if (i == 7) {
				std::cout << "Lopetuskoordinaatin numerosy�te ei ollut kelvollinen" << std::endl;
				numeroCheck = true;
			}

		}

		/*
		lopetusKoordinaatti = std::string(1, syote[4]) + std::string(1, syote[5]);
		std::cout << lopetusKoordinaatti << std::endl;
		*/

		if (kirjainCheck || numeroCheck) {
			continue;
		}

		break;
	}

	if (lyhytLinna || pitkaLinna) {
		siirto = Siirto(lyhytLinna,pitkaLinna);
		return siirto;
	}

	int alkuX = aloitusKoordinaatti[0] - 'a';
	std::cout << alkuX << std::endl;
	int alkuY = aloitusKoordinaatti[1] - 49;
	std::cout << alkuY << std::endl;

	int lopetusX = lopetusKoordinaatti[0] - 'a';
	std::cout << lopetusX << std::endl;
	int lopetusY = lopetusKoordinaatti[1] - 49;
	std::cout << lopetusY << std::endl;
	
	siirto = Siirto(Ruutu(alkuX,alkuY), Ruutu(lopetusX,lopetusY));

	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}

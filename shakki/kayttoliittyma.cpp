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
		Kaksinkertainen for silmukka joka käy asema-olion laudan läpi ja jos
		siinä on nappula olio, niin kysytään sen nimi
		ja tulostetaan se muussa tapauksessa tulostetaan 2 tyhjää välilyöntiä.
		Parillisuuteen perustuen värjätään jokatoisen "ruudun" taustaväri
	*/

	for(int y = 7; y >= 0; y--)
	{
		// Tulosta numerot sivulle
		std::wcout << y + 1;
		for(int x = 0; x < 8; x++)
		{
			//Värjää ruudukko
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

			//Tulosta nappula tai tyhjä
			if(_asema->_lauta[y][x]) std::wcout << _asema->_lauta[y][x]->getUnicode() << " ";
			else std::wcout << "  ";

			//Resetoi väri muutokset
			std::wcout << "\033[0m";
		}
		//Rivin vaihto kun rivi loppuu
		std::wcout << std::endl;
	}
	//Tulosta kirjaimet
	std::wcout << " A B C D E F G H";
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}

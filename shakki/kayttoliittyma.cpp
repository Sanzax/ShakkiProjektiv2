#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

//using namespace std;


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
	//_setmode(_fileno(stdout), _O_U16TEXT);

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


bool onkoSyoteVirheellinen(const int arvo, const char* virheIlmoitus)
{
	for(int i = 0; i < 8; i++)
		if(arvo == i) return false;
	std::wcout << virheIlmoitus << std::endl;
	return true;
}

Siirto Kayttoliittyma::annaVastustajanSiirto(std::vector<Siirto>& laillisetSiirrot)
{
	std::string syote;
	char nappula;
	int alkuX, alkuY, loppuX, loppuY;
	char viiva;
	
	bool lyhytLinnaSyote, pitkaLinnaSyote;

	while (true)
	{
		std::wcout << "Anna siirto" << std::endl; //Kysyt��n k�ytt�j�lt� siirtoa
		std::cin >> syote;

		lyhytLinnaSyote = false, pitkaLinnaSyote = false;

#if 1
		if (syote == "O-O") // Jos sy�te on lyhyt tai...
		{
			lyhytLinnaSyote = true;
		}
		else if (syote == "O-O-O")  // ...pitk� linna, asetetaan sopivat flagit
		{							// ja hyp�t��n suoraan siirron luontiin
			pitkaLinnaSyote = true;
		}
#endif

		// Alustetaan koordinaatit sy�tteen mukaan
		nappula = syote[0];

		if(nappula != 'K' && nappula != 'D' && nappula != 'L' && nappula != 'T' && nappula != 'R' && (!lyhytLinnaSyote && !pitkaLinnaSyote))
		{
			alkuX = syote[0] - 'a';	 //alkuX = syote[0] - 'a';
			alkuY = syote[1] - '1';	 //alkuY = syote[1] - '1';
			viiva = syote[2];
			loppuX = syote[3] - 'a'; //loppuX = syote[3] - 'a';
			loppuY = syote[4] - '1'; //loppuY = syote[4] - '1';
		}
		else
		{
			alkuX = syote[1] - 'a';	 //alkuX = syote[0] - 'a';
			alkuY = syote[2] - '1';	 //alkuY = syote[1] - '1';
			viiva = syote[3];
			loppuX = syote[4] - 'a'; //loppuX = syote[3] - 'a';
			loppuY = syote[5] - '1'; //loppuY = syote[4] - '1';

			// Jos Nappula ei ole kelvollinen, kysyt��n siirtoa uudelleen
			if(!(nappula == 'K' || nappula == 'D' || nappula == 'L' || nappula == 'R' || nappula == 'T') && (!lyhytLinnaSyote && !pitkaLinnaSyote))
			{
				std::wcout << "Nappulatyypin sy�te ei ollut kelvollinen" << std::endl;
				continue;
			}
		}

		// Jos viiva ei ole kelvollinen, kysyt��n siirtoa uudelleen
		if(viiva != '-' && (!lyhytLinnaSyote && !pitkaLinnaSyote))
		{
			std::wcout << "Viivasy�te ei ollut kelvollinen" << std::endl;
			continue;
		}

		if (!lyhytLinnaSyote && !pitkaLinnaSyote) {
			// Jos koordinaatit ei ole kelvollisia, kysyt��n siirtoa uudelleen
			bool alkuXCheck = onkoSyoteVirheellinen(alkuX, "Alku koordinaatin kirjain on virheellinen");
			bool alkuYCheck = onkoSyoteVirheellinen(alkuY, "Alku koordinaatin numero on virheellinen");
			bool loppuXCheck = onkoSyoteVirheellinen(loppuX, "Loppu koordinaatin kirjain on virheellinen");
			bool loppuYCheck = onkoSyoteVirheellinen(loppuY, "Loppu koordinaatin numero on virheellinen");
			if ((alkuXCheck || alkuYCheck || loppuXCheck || loppuYCheck))
				continue;
		}

		/* Laittomien siirtojen tarkistus */
#if 1
		bool laillinenSiirtoLoytyi = false;
		auto iter = laillisetSiirrot.begin();
		bool lyhytLinna = false, pitkaLinna = false;
		for (Siirto s : laillisetSiirrot)
		{
			if (s.onkoLyhytLinna() && lyhytLinnaSyote) {
				lyhytLinna = true;
				break;
			}
			else if (s.onkoPitkaLinna() && pitkaLinnaSyote) {
				pitkaLinna = true;
				break;
			}


			//jos lailliset siirrot listalta l�ytyy sy�te joka vastaa pelaajan sy�tett�, niin lopetetaan tarkastelu ja hyv�ksyt��n siirto
			if (s.getAlkuruutu().getSarake() == alkuX && s.getAlkuruutu().getRivi() == alkuY && s.getLoppuruutu().getSarake() == loppuX && s.getLoppuruutu().getRivi() == loppuY) {
				laillinenSiirtoLoytyi = true;
				break;
			}
			iter++;
		}

		//jos annettua sy�tett� ei l�ydy lailliset siirrot listalta, niin kysyt��n siirtoa uudelleen
		if (iter == laillisetSiirrot.end() && !laillinenSiirtoLoytyi) {
			std::wcout << "Laiton siirto" << std::endl;
			continue;
		}
		else if(lyhytLinnaSyote && !lyhytLinna)
		{
			std::wcout << "Laiton linnoitussiirto" << std::endl;
			continue;
		}
		else if(pitkaLinnaSyote && !pitkaLinna){
			std::wcout << "Laiton linnoitussiirto" << std::endl;
			continue;
		}
		
#endif

		break; // Jos sy�te oli kelvollinen l�hdet��n silmukasta
	}
	
	Siirto siirto;

	if (lyhytLinnaSyote || pitkaLinnaSyote) // Jos siirto on linnoitus, tehd��n sen mukainen siirto ja palautetaan se
	{
		siirto = Siirto(lyhytLinnaSyote,pitkaLinnaSyote);
		return siirto;
	}

	// Muuten luodaan siirto koordinaattien mukaan ja palautetaan se
	siirto = Siirto(Ruutu(alkuX, alkuY), Ruutu(loppuX, loppuY));

	Nappula* siirrettava = _asema->_lauta[alkuY][alkuX];

	if(siirrettava != NULL && siirrettava->getKoodi() == VS && siirto.getLoppuruutu().getRivi() == 7)
	{
		while(true)
		{
			std::wcout << "Miksi nappulaksi haluat korottaa?: ";
			std::wstring vastaus;
			std::wcin >> vastaus;
			if(vastaus == L"D") siirto._miksikorotetaan = Asema::vd;
			else if(vastaus == L"T") siirto._miksikorotetaan = Asema::vt;
			else if(vastaus == L"L") siirto._miksikorotetaan = Asema::vl;
			else if(vastaus == L"R") siirto._miksikorotetaan = Asema::vr;
			else continue;

			break;
		}
	}
	else if(siirrettava != NULL && siirrettava->getKoodi() == MS && siirto.getLoppuruutu().getRivi() == 0)
	{
		while(true)
		{
			std::wcout << "Miksi nappulaksi haluat korottaa?: ";
			std::wstring vastaus;
			std::wcin >> vastaus;
			if(vastaus == L"D") siirto._miksikorotetaan = Asema::md;
			else if(vastaus == L"T") siirto._miksikorotetaan = Asema::mt;
			else if(vastaus == L"L") siirto._miksikorotetaan = Asema::ml;
			else if(vastaus == L"R") siirto._miksikorotetaan = Asema::mr;
			else continue;

			break;
		}
	}

	return siirto;
}

int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}


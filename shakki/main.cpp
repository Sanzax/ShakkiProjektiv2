#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"


int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	int lopetus = 100;
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
			  kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	//asema.annaLaillisetSiirrot(lista);

	/*
	Siirto siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
	asema.paivitaAsema(&siirto);
	Kayttoliittyma::getInstance()->piirraLauta();
	*/


	while(lopetus != 0)
	{
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		std::wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);

		std::wcout << "Lailliset siirrot:" << std::endl;
		for(Siirto s : lista)
		{
			if(s.onkoPitkaLinna())
				std::wcout << "Pitkalinna" << std::endl;
			else if(s.onkoLyhytLinna())
				std::wcout << "Lyhytlinna" << std::endl;
			else
				std::wcout << "Siirto: " << s.getAlkuruutu().getSarake() << ", " << s.getAlkuruutu().getRivi() <<
				" : " << s.getLoppuruutu().getSarake() << ", " << s.getLoppuruutu().getRivi() << std::endl;
		}

		if(lista.size() == 0)
		{
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(lista);
		/*
		if (asema.getSiirtovuoro() == koneenVari) {
			//MinMaxPaluu paluu;
			if (koneenVari == 0) {
				//paluu = asema.maxi(3);
			}
			else {
				//paluu = asema.mini(3);
			}
			//siirto = paluu._parasSiirto;
		}
		else {
			/*siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}*/
		asema.paivitaAsema(&siirto);
	}


	return 0;
}

/*
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	asema.annaLaillisetSiirrot(lista);

	Siirto siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
	asema.paivitaAsema(&siirto);
	Kayttoliittyma::getInstance()->piirraLauta();

	/*
	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		if (asema.getSiirtovuoro() == koneenVari) {
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(3);
			}
			else {
				paluu = asema.mini(3);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}
	
	
	return 0;
}
*/
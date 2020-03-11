#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"
#include "Timer.h"
#include <vector>

void tulostaLaillisetSiirrot(Asema& asema)
{
	std::vector<Siirto> siirrot;
	siirrot.reserve(50);
	asema.annaLaillisetSiirrot(siirrot);
	std::wcout << "Lailliset siirrot: \n";
	std::wcout << "{";
	for(Siirto s : siirrot)
		s.tulosta();
	std::wcout << "}\n";
}

int main()
{
	int maksimiSyvyys;
	std::wcout << "Anna syvyys: ";
	std::wcin >> maksimiSyvyys;

	_setmode(_fileno(stdout), _O_U16TEXT);
	int lopetus = 100;
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
			  kysyVastustajanVari());
	std::vector<Siirto> lista;
	system("cls");
	int koneenVari;
	while(true)
	{
		int vari;
		std::wcout << "Anna koneen vari: ";
		std::wcin >> vari;

		if(vari != 0 && vari != 1)
		{
			std::wcout << "Virheellinen vari!" << std::endl;
			continue;
		}

		koneenVari = vari;
		break;
	}
	/*
	while(lopetus != 0)
	{
		lista.clear();
		std::wcout << "\n";
		// Tarkasta onko peli loppu?
		//asema.annaLaillisetSiirrot(lista);

		Siirto siirto;
		Timer ajastin;
		MinMaxPaluu paluu;
		if(asema.getSiirtovuoro() == 0)
		{
			paluu = asema.maxi(maksimiSyvyys);
			if(paluu._evaluointiArvo == 1000000)
			{
				std::wcout << "Peli loppui";
				lopetus = 0;
				continue;
			}
		}
		else
		{
			paluu = asema.mini(maksimiSyvyys);
			if(paluu._evaluointiArvo == 1000000)
			{
				std::wcout << "Peli loppui";
				lopetus = 0;
				continue;
			}
		}

		siirto = paluu._parasSiirto;
		
		system("cls");
		ajastin.stop("Siirron miettimiseen meni");
		std::wcout << "Tehty siirto: "; siirto.tulosta(); std::wcout << std::endl;

		asema.paivitaAsema(&siirto);
		Kayttoliittyma::getInstance()->piirraLauta();

		std::cin.get();
	}*/

	while(lopetus != 0)
	{
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		std::wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if(lista.size() == 0)
		{
			std::wcout << "Peli päättyi\n";
			break;
		}

		/*
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
		}*/

		Siirto siirto;
		if(asema.getSiirtovuoro() == koneenVari) {
#if 1
			tulostaLaillisetSiirrot(asema);
			siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(lista);
#else
			Timer ajastin;
			MinMaxPaluu paluu;
			paluu = asema.minimax(maksimiSyvyys, -INT_MAX, -INT_MIN);
			ajastin.stop("Siirron miettimiseen meni");
			tulostaLaillisetSiirrot(asema);
			siirto = paluu._parasSiirto;
#endif
		}
		else {
#if 1
			tulostaLaillisetSiirrot(asema);
			siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto(lista);
#else
			Timer ajastin;
			MinMaxPaluu paluu;
			paluu = asema.minimax(maksimiSyvyys, -INT_MAX, -INT_MIN);
			ajastin.stop("Siirron miettimiseen meni");
			tulostaLaillisetSiirrot(asema);
			siirto = paluu._parasSiirto;
#endif
		}

		std::wcout << "Tehty siirto: "; siirto.tulosta(); std::wcout << std::endl;

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
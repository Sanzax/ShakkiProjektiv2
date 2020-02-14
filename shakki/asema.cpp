#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include <math.h>

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	_siirtovuoro = 0;
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
			_lauta[i][j] = NULL;

	//// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	//_lauta[0][0] = Asema::vt;
	//_lauta[0][1] = Asema::vr;
	//_lauta[0][2] = Asema::vl;
	//_lauta[0][3] = Asema::vd;
	//_lauta[0][4] = Asema::vk;
	//_lauta[0][5] = Asema::vl;
	//_lauta[0][6] = Asema::vr;
	//_lauta[0][7] = Asema::vt;
	//for (int i = 0; i < 8; i++)
	//	_lauta[1][i] = Asema::vs;

	//_lauta[7][0] = Asema::mt;
	//_lauta[7][1] = Asema::mr;
	//_lauta[7][2] = Asema::ml;
	//_lauta[7][3] = Asema::md;
	//_lauta[7][4] = Asema::mk;
	//_lauta[7][5] = Asema::ml;
	//_lauta[7][6] = Asema::mr;
	//_lauta[7][7] = Asema::mt;

	//
	//for (int i = 0; i < 8; i++)
	//	_lauta[6][i] = Asema::ms;

	//_lauta[0][0] = Asema::vk; //Toimiva tilanne
	//_lauta[3][0] = Asema::mt;

	_lauta[2][1] = Asema::vk;
	_lauta[2][7] = Asema::mt;
}



void Asema::paivitaAsema(Siirto *siirto)
{

	// Kaksoisaskel-lippu on oletusarvoisesti pois päältä.
	// Asetetaan myöhemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna

	if (siirto->onkoLyhytLinna()) {
		//to do
	}


	// onko pitkä linna

	if (siirto->onkoPitkaLinna()) {
		//to do
	}

	// Kaikki muut siirrot


		//Ottaa siirron alkuruudussa olleen nappulan talteen 

	Nappula *siirrettava;

	siirrettava = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];


	//Laittaa talteen otetun nappulan uuteen ruutuun



	// Tarkistetaan oliko sotilaan kaksoisaskel

	if (siirrettava->getKoodi() == VS || siirrettava->getKoodi() == MS) {
		if ((abs(siirto->getAlkuruutu().getSarake() - siirto->getLoppuruutu().getSarake())) == 2) {
			kaksoisaskelSarakkeella = 1; // (asetetaan kaksoisaskel-lippu)
		}
	}

	/*
	// Ohestalyönti on tyhjään ruutuun. Vieressä oleva (sotilas) poistetaan.
	if (kaksoisaskelSarakkeella == 1) {

	}
	*/


	//// Katsotaan jos nappula on sotilas ja rivi on päätyrivi niin ei vaihdeta nappulaa 
	////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittymän laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

	//
	////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta lähtenyt nappula

	//std::wcout << siirto->getalkuruutu().getsarake() << std::endl;
	//std::wcout << siirto->getalkuruutu().getrivi() << std::endl;

	//std::wcout << siirto->getloppuruutu().getsarake() << std::endl;
	//std::wcout << siirto->getloppuruutu().getrivi() << std::endl;

	_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = siirrettava;

	_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = NULL;


	// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille väreille)
	if (siirrettava->getKoodi() == VK) {
		_onkoValkeaKuningasLiikkunut = true;
	}

	else if (siirrettava->getKoodi() == MK) {
		_onkoMustaKuningasLiikkunut = true;
	}

	// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille väreille ja molemmille torneille)

	if (siirrettava->getKoodi() == MT && siirto->getAlkuruutu().getSarake() == 0 && siirto->getAlkuruutu().getRivi() == 7) {
		_onkoMustaDTliikkunut = true;
	}

	else if (siirrettava->getKoodi() == MT && siirto->getAlkuruutu().getSarake() == 7 && siirto->getAlkuruutu().getRivi() == 7) {
		_onkoMustaKTliikkunut = true;
	}

	else if (siirrettava->getKoodi() == VT && siirto->getAlkuruutu().getSarake() == 0 && siirto->getAlkuruutu().getRivi() == 0) {
		_onkoValkeaDTliikkunut = true;
	}

	else if (siirrettava->getKoodi() == VT && siirto->getAlkuruutu().getSarake() == 0 && siirto->getAlkuruutu().getRivi() == 7) {
		_onkoValkeaKTliikkunut = true;
	}

	//päivitetään _siirtovuoro

	_siirtovuoro = (_siirtovuoro == 0) ? 1 : 0;
}



int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro)
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut()
{
	return _onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
Lähetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyvä että kunigas g1 tai b1/c1
Loppupelissä vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla estämässä vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitkiä linjoja daami, torni ja lähetti
*/
double Asema::evaluoi()
{
	return 0;

	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta

	//1. Nappuloiden arvo

	//2. Kuningas turvassa

	//3. Arvosta keskustaa

	// 4. Arvosta linjoja

}


double Asema::laskeNappuloidenArvo(int vari)
{
	return 0;

}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami jäljellä

	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1


}


double Asema::nappuloitaKeskella(int vari)
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa

	//valkeille ydinkeskusta



	//valkeille laitakeskusta



	//mustille ydinkeskusta

	//mustille laitakeskusta

}


double Asema::linjat(int vari)
{
	return 0;

	//valkoiset

	//mustat

}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lisäsin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.

	// Rekursion kantatapaus 1: peli on loppu

	// Rekursion kantatapaus 2: katkaisusyvyydessä

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{



	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{

}

void Asema::annaRaakaSiirrot(std::list<Siirto>& lista)
{
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(_lauta[y][x] != NULL && _lauta[y][x]->getVari() == _siirtovuoro)
			{
				Ruutu alkuRuutu = Ruutu(x, y);
				_lauta[y][x]->annaSiirrot(lista, &alkuRuutu, this, _siirtovuoro);
			}

		}
	}
}

Ruutu Asema::etsiKuninkaanSijainti()
{
	Ruutu kuninkaanSijainti;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(_lauta[y][x] != NULL && ((_lauta[y][x]->getKoodi() == MK && _siirtovuoro == 0) || (_lauta[y][x]->getKoodi() == VK && _siirtovuoro == 1)))
			{
				kuninkaanSijainti = Ruutu(x, y);
			}
			
		}
	}
	return kuninkaanSijainti;
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) 
{
	std::list<Siirto> raakaSiirrot;
	annaRaakaSiirrot(raakaSiirrot);

	std::list<Siirto> laillisetSiirrot;

	for(Siirto s : raakaSiirrot)
	{
		Asema vastustajanVuoroAsema = *this;
		vastustajanVuoroAsema.paivitaAsema(&s);
		vastustajanVuoroAsema.setSiirtovuoro(1);//_siirtovuoro == 0 ? 1 : 0

		Ruutu kuninkaanSijainti = vastustajanVuoroAsema.etsiKuninkaanSijainti();


		std::list<Siirto> vastustajanRaakaSiirrot;
		vastustajanVuoroAsema.annaRaakaSiirrot(vastustajanRaakaSiirrot);

		for(Siirto vs : vastustajanRaakaSiirrot)
		{
			std::wcout <<"Kuninkaan sijainti " << kuninkaanSijainti.getSarake() << ", " << kuninkaanSijainti.getRivi() << std::endl;
			std::wcout << "Vastustajan siirron loppuruutu "<< vs.getLoppuruutu().getSarake() << ", " << vs.getLoppuruutu().getRivi() << std::endl;
			if(!(vs.getLoppuruutu().getRivi() == kuninkaanSijainti.getRivi() && vs.getLoppuruutu().getSarake() == kuninkaanSijainti.getSarake()))
			{
				std::wcout << "Laillinen"  << std::endl;
				laillisetSiirrot.push_back(s);
				break;
			}
		}

	}

	lista = laillisetSiirrot;

}

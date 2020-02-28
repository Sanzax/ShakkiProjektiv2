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

	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoValkeaKuningasLiikkunut = false;

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

	_lauta[0][0] = Asema::vt;
	_lauta[0][4] = Asema::vk;
	_lauta[0][7] = Asema::vt;

	_lauta[7][0] = Asema::mt;
	_lauta[7][4] = Asema::mk;
	_lauta[7][7] = Asema::mt;

	_lauta[5][0] = Asema::ml;

	_lauta[1][2] = Asema::ms;

	//_lauta[7][7] = Asema::mt;
}



void Asema::paivitaAsema(Siirto *siirto)
{
	kaksoisaskelSarakkeella = -1;

	if(siirto->onkoLyhytLinna())
	{
		if(_siirtovuoro == 0)
		{
			_lauta[0][4] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[0][6] = vk; // kuningas uudelle paikalle
			_lauta[0][7] = NULL; // tornin paikalle tyhj‰
			_lauta[0][5] = vt; // torni uudella paikalle
			_onkoValkeaKuningasLiikkunut = true;
			_onkoValkeaKTliikkunut = true;
		}
		if(_siirtovuoro == 1)
		{
			_lauta[7][4] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[7][6] = mk; // kuningas uudelle paikalle
			_lauta[7][7] = NULL; // tornin paikalle tyhj‰
			_lauta[7][5] = mt; // torni uudella paikalle
			_onkoMustaKuningasLiikkunut = true;
			_onkoMustaKTliikkunut = true;
		}
	}

	// onko pitk‰ linna
	else if(siirto->onkoPitkaLinna())
	{
		if(_siirtovuoro == 0)
		{
			_lauta[0][4] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[0][2] = vk; // kuningas uudelle paikalle
			_lauta[0][0] = NULL; // tornin paikalle tyhj‰
			_lauta[0][3] = vt; // torni uudella paikalle
			_onkoValkeaKuningasLiikkunut = true;
			_onkoValkeaDTliikkunut = true;
		}
		if(_siirtovuoro == 1)
		{
			_lauta[7][4] = NULL; // kuninkaan paikalle tyhj‰
			_lauta[7][2] = mk; // kuningas uudelle paikalle
			_lauta[7][0] = NULL; // tornin paikalle tyhj‰
			_lauta[7][3] = mt; // torni uudella paikalle
			_onkoMustaKuningasLiikkunut = true;
			_onkoMustaDTliikkunut = true;
		}

	}
	else
	{
		int alkuX = siirto->getAlkuruutu().getSarake();
		int alkuY = siirto->getAlkuruutu().getRivi();
		int loppuX = siirto->getLoppuruutu().getSarake();
		int loppuY = siirto->getLoppuruutu().getRivi();

		Nappula *siirrettava = _lauta[alkuY][alkuX];

		if(siirrettava != NULL && siirrettava->getKoodi() == VS || siirrettava->getKoodi() == MS)
			if((abs(alkuY - loppuY)) == 2)
			{
				std::wcout << "Kaksoisaskel\n";
				kaksoisaskelSarakkeella = alkuX; // (asetetaan kaksoisaskel-lippu)
				std::wcout << kaksoisaskelSarakkeella << "\n";
			}


		
		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if((_lauta[alkuY][alkuX]->getKoodi() == VS || _lauta[alkuY][alkuX]->getKoodi() == VS) && (alkuX != loppuX) && (_lauta[loppuY][loppuX] == NULL))
			_lauta[alkuY][loppuX] = NULL;


		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula

		_lauta[loppuY][loppuX] = siirrettava;
		_lauta[alkuY][alkuX] = NULL;


		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if(siirrettava != NULL && siirrettava->getKoodi() == VK)
			_onkoValkeaKuningasLiikkunut = true;
		else if(siirrettava != NULL && (siirrettava->getKoodi() == MK))
			_onkoMustaKuningasLiikkunut = true;

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)

		if(siirrettava != NULL && siirrettava->getKoodi() == MT && alkuX == 0 && alkuY == 7)
			_onkoMustaDTliikkunut = true;

		else if(siirrettava != NULL && siirrettava->getKoodi() == MT && alkuX == 7 && alkuY == 7)
			_onkoMustaKTliikkunut = true;

		else if(siirrettava != NULL && siirrettava->getKoodi() == VT && alkuX == 0 && alkuY == 0)
			_onkoValkeaDTliikkunut = true;

		else if(siirrettava != NULL && siirrettava->getKoodi() == VT && alkuX == 0 && alkuY == 7)
			_onkoValkeaKTliikkunut = true;

		
	}
	//p‰ivitet‰‰n _siirtovuoro
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
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi()
{
	return 0;

	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta

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
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰

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


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
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

	// Rekursion kantatapaus 2: katkaisusyvyydess‰

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
	std::list<Siirto> vastustajaSiirrotLista;
	//V‰reitt‰in k‰yd‰‰n l‰pi kaikki ruudut ja niiss‰ olevan nappulan siirrot ker‰t‰‰n vastustajan siirtolistaan
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(this->_lauta[i][j] == NULL)
				continue;
			if(this->_lauta[i][j]->getVari() == vastustajanVari)
				this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(j, i), this, vastustajanVari); // myˆh.sidonta
		}
	}

	// K‰yd‰‰n vastustajaSiirtoLista l‰pi ja jos sielt‰ lˆytyy tarkasteltava ruutu niin tiedet‰‰n sen olevan uhattu
	for(Siirto s : vastustajaSiirrotLista)
	{
		if(ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi())
		{
			return true;
		}
	}
	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{

}

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vastustajanVari)
{
	if(vastustajanVari == 1)
	{
		std::wcout << "valkoinen" << std::endl;
		if(_onkoValkeaKuningasLiikkunut && (_onkoValkeaDTliikkunut || _onkoValkeaKTliikkunut))
			return;

		if(_lauta[0][5] == NULL && _lauta[0][6] == NULL && !onkoRuutuUhattu(&Ruutu(5, 0), vastustajanVari ))
		{
			lista.push_back(Siirto(true, false));
			std::wcout << "l" << std::endl;
		}
		if(_lauta[0][1] == NULL && _lauta[0][2] == NULL && _lauta[0][3] == NULL && !onkoRuutuUhattu(&Ruutu(3, 0), vastustajanVari))
		{
			lista.push_back(Siirto(false, true));
			std::wcout << "p" << std::endl;
		}
	}
	else if(vastustajanVari == 0)
	{
		std::wcout << "musta" << std::endl;
		if(_onkoMustaKuningasLiikkunut && (_onkoMustaDTliikkunut || _onkoMustaKTliikkunut))
			return;

		if(_lauta[7][5] == NULL && _lauta[7][6] == NULL && !onkoRuutuUhattu(&Ruutu(5, 7), vastustajanVari))
		{
			lista.push_back(Siirto(true, false));
		}
		if(_lauta[7][1] == NULL && _lauta[7][2] == NULL && _lauta[7][3] == NULL && !onkoRuutuUhattu(&Ruutu(3, 7), vastustajanVari))
		{
			lista.push_back(Siirto(false, true));
		}
	}
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
	annaLinnoitusSiirrot(raakaSiirrot, _siirtovuoro == 0 ? 1 : 0);

	std::list<Siirto> laillisetSiirrot;
	
	// Suodatetaan siirrot joissa kuningas tulisi uhatuksi
	for(Siirto s : raakaSiirrot)
	{
		Asema vastustajanVuoroAsema = *this;
		vastustajanVuoroAsema.paivitaAsema(&s);
		vastustajanVuoroAsema.setSiirtovuoro(_siirtovuoro == 0 ? 1 : 0);

		Ruutu kuninkaanSijainti = vastustajanVuoroAsema.etsiKuninkaanSijainti();

		std::list<Siirto> vastustajanRaakaSiirrot;
		vastustajanVuoroAsema.annaRaakaSiirrot(vastustajanRaakaSiirrot);

		for(Siirto vs : vastustajanRaakaSiirrot)
		{
			//std::wcout <<"Kuninkaan sijainti " << kuninkaanSijainti.getSarake() << ", " << kuninkaanSijainti.getRivi() << std::endl;
			//std::wcout << "Vastustajan siirron loppuruutu "<< vs.getLoppuruutu().getSarake() << ", " << vs.getLoppuruutu().getRivi() << std::endl;
			if(!(vs.getLoppuruutu().getRivi() == kuninkaanSijainti.getRivi() && vs.getLoppuruutu().getSarake() == kuninkaanSijainti.getSarake()))
			{
				laillisetSiirrot.push_back(s);
				break;
			}
		}
	}



	
	lista = laillisetSiirrot;

}

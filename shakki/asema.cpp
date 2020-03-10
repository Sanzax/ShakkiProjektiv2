#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include <math.h>
#include <algorithm>
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
	
	
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
#if 1	
	_lauta[0][0] = Asema::vt;
	_lauta[0][1] = Asema::vr;
	_lauta[0][2] = Asema::vl;
	_lauta[0][3] = Asema::vd;
	_lauta[0][4] = Asema::vk;
	_lauta[0][5] = Asema::vl;
	_lauta[0][6] = Asema::vr;
	_lauta[0][7] = Asema::vt;
	for (int i = 0; i < 8; i++)
		_lauta[1][i] = Asema::vs;

	_lauta[7][0] = Asema::mt;
	_lauta[7][1] = Asema::mr;
	_lauta[7][2] = Asema::ml;
	_lauta[7][3] = Asema::md;
	_lauta[7][4] = Asema::mk;
	_lauta[7][5] = Asema::ml;
	_lauta[7][6] = Asema::mr;
	_lauta[7][7] = Asema::mt;
	for (int i = 0; i < 8; i++)
		_lauta[6][i] = Asema::ms;
#endif

#if 0 //valkoinen
	_lauta[0][4] = Asema::vk;
	_lauta[1][5] = Asema::vs;
	_lauta[1][6] = Asema::vs;
	_lauta[1][7] = Asema::vs;


	_lauta[2][6] = Asema::md;

	_lauta[7][4] = Asema::mk;
#endif

#if 0
	_lauta[7][4] = Asema::mk;
	_lauta[6][5] = Asema::ms;
	_lauta[6][6] = Asema::ms;
	_lauta[6][7] = Asema::ms;


	_lauta[5][6] = Asema::vd;

	_lauta[0][4] = Asema::vk;
	_lauta[0][3] = Asema::mt;
#endif


	/*
	_lauta[0][0] = Asema::vk;
	//_lauta[0][6] = Asema::mt;
	_lauta[4][4] = Asema::ml;
	_lauta[0][2] = Asema::mt;
	_lauta[2][0] = Asema::mt;
	_lauta[7][7] = Asema::mk;
	_lauta[6][7] = Asema::ms;
	_lauta[7][6] = Asema::ms;
	_lauta[6][6] = Asema::ms;*/




	//_lauta[7][7] = Asema::mk;
	//_lauta[6][7] = Asema::ms;
	//_lauta[6][6] = Asema::ms;

	//_lauta[5][2] = Asema::mt;
	//_lauta[5][5] = Asema::mt;
	//_lauta[0][4] = Asema::vk;

	//_lauta[6][4] = Asema::vs;
	
	
	/*_lauta[7][7] = Asema::vk;
	_lauta[3][3] = Asema::mk;
	_lauta[2][2] = Asema::vr;
	_lauta[2][4] = Asema::vs;
	_lauta[1][1] = Asema::vs;
	_lauta[1][3] = Asema::vs;
	_lauta[1][5] = Asema::vs;*/

	/*_lauta[7][7] = Asema::mk;
	_lauta[3][3] = Asema::vk;
	_lauta[4][2] = Asema::mr;
	_lauta[4][4] = Asema::ms;
	_lauta[5][1] = Asema::ms;
	_lauta[5][3] = Asema::ms;
	_lauta[5][5] = Asema::ms;*/

	//_lauta[7][0] = Asema::ms;
}

void Asema::paivitaAsema(Siirto *siirto)
{
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
		kaksoisaskelSarakkeella = -1;
		int alkuX = siirto->getAlkuruutu().getSarake();
		int alkuY = siirto->getAlkuruutu().getRivi();
		int loppuX = siirto->getLoppuruutu().getSarake();
		int loppuY = siirto->getLoppuruutu().getRivi();

		Nappula *siirrettava = _lauta[alkuY][alkuX];

		if(siirrettava->getKoodi() == VS || siirrettava->getKoodi() == MS)
			if((abs(alkuY - loppuY)) == 2)
			{
				kaksoisaskelSarakkeella = alkuX; // (asetetaan kaksoisaskel-lippu)
			}
		// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
		if((siirrettava->getKoodi() == VS || siirrettava->getKoodi() == VS) && (alkuX != loppuX) && (_lauta[loppuY][loppuX] == NULL))
			_lauta[alkuY][loppuX] = NULL;

		_lauta[loppuY][loppuX] = siirrettava;
		_lauta[alkuY][alkuX] = NULL;

		if(siirto->_miksikorotetaan != NULL)
			_lauta[loppuY][loppuX] = siirto->_miksikorotetaan;

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		if(siirrettava->getKoodi() == VK)
			_onkoValkeaKuningasLiikkunut = true;
		else if((siirrettava->getKoodi() == MK))
			_onkoMustaKuningasLiikkunut = true;

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)
		if(siirrettava->getKoodi() == MT && alkuX == 0 && alkuY == 7) _onkoMustaDTliikkunut = true;
		else if(siirrettava->getKoodi() == MT && alkuX == 7 && alkuY == 7) _onkoMustaKTliikkunut = true;
		else if(siirrettava->getKoodi() == VT && alkuX == 0 && alkuY == 0)_onkoValkeaDTliikkunut = true;
		else if(siirrettava->getKoodi() == VT && alkuX == 0 && alkuY == 7) _onkoValkeaKTliikkunut = true;
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
float Asema::evaluoi()
{
	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta

	//1. Nappuloiden arvo
	float vMateriaali = laskeNappuloidenArvo(0);
	float mMateriaali = laskeNappuloidenArvo(1);

	//2. Kuningas turvassa

	//3. Arvosta keskustaa
	float vKeskusta = nappuloitaKeskella(0);
	float mKeskusta = nappuloitaKeskella(1);


	// 4. Arvosta linjoja

	float vArvo = vMateriaali + vKeskusta;
	float mArvo = mMateriaali + mKeskusta;

	return vArvo - mArvo;
}


float Asema::laskeNappuloidenArvo(int vari)
{
	int arvo = 0;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(_lauta[y][x] == NULL)
				continue;
			if(vari == 0)
			{
				if(_lauta[y][x]->getKoodi() == VS) arvo += 1.0f;
				else if(_lauta[y][x]->getKoodi() == VT) arvo += 5.0f;
				else if(_lauta[y][x]->getKoodi() == VL) arvo += 3.25f;
				else if(_lauta[y][x]->getKoodi() == VR) arvo += 3.0f;
				else if(_lauta[y][x]->getKoodi() == VD) arvo += 9;
			}
			else
			{
				if(_lauta[y][x]->getKoodi() == MS) arvo += 1.0f;
				else if(_lauta[y][x]->getKoodi() == MT) arvo += 5.0f;
				else if(_lauta[y][x]->getKoodi() == ML) arvo += 3.25f;
				else if(_lauta[y][x]->getKoodi() == MR) arvo += 3.0f;
				else if(_lauta[y][x]->getKoodi() == MD) arvo += 9;
			}
		}
	}
	return arvo;
}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	bool onkoDaami = false;
	int upseerit = 0;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(_lauta[y][x] == NULL) continue;
			if(_lauta[y][x]->getKoodi() == MT || _lauta[y][x]->getKoodi() == VT || _lauta[y][x]->getKoodi() == ML || _lauta[y][x]->getKoodi() == VL ||
			   _lauta[y][x]->getKoodi() == MR || _lauta[y][x]->getKoodi() == VR)
				upseerit++;

			if(_lauta[y][x]->getKoodi() == MD || _lauta[y][x]->getKoodi() == VD) 
				onkoDaami = true;
		}
	}

	if(upseerit <= 3 && !onkoDaami)
		return false;

	return true;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰

	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
}

float Asema::nappuloitaKeskella(int vari)
{
	float arvo = 0;

	if(vari == 0)
	{
		if(_lauta[3][2] != NULL && _lauta[3][2]->getKoodi() == VS)
			arvo += .11f;
		if(_lauta[4][2] != NULL && _lauta[4][2]->getKoodi() == VS)
			arvo += .11f;
		if(_lauta[3][5] != NULL && _lauta[3][5]->getKoodi() == VS)
			arvo += .11f;
		if(_lauta[4][5] != NULL && _lauta[4][5]->getKoodi() == VS)
			arvo += .11f;
		if(_lauta[3][2] != NULL && _lauta[3][2]->getKoodi() == VR)
			arvo += .11f;
		if(_lauta[4][2] != NULL && _lauta[4][2]->getKoodi() == VR)
			arvo += .11f;
		if(_lauta[3][5] != NULL && _lauta[3][5]->getKoodi() == VR)
			arvo += .11f;
		if(_lauta[4][5] != NULL && _lauta[4][5]->getKoodi() == VR)
			arvo += .11f;

		if(_lauta[3][3] != NULL && _lauta[3][3]->getKoodi() == VS)
			arvo += .25f;
		if(_lauta[4][3] != NULL && _lauta[4][3]->getKoodi() == VS)
		   arvo += .25f;
		if(_lauta[3][4] != NULL && _lauta[3][4]->getKoodi() == VS)
			arvo += .25f;
		if(_lauta[4][4] != NULL && _lauta[4][4]->getKoodi() == VS)
			arvo += .25f;
		if(_lauta[3][3] != NULL && _lauta[3][3]->getKoodi() == VR)
			arvo += .25f;
		if(_lauta[4][3] != NULL && _lauta[4][3]->getKoodi() == VR)
			arvo += .25f;
		if(_lauta[3][4] != NULL && _lauta[3][4]->getKoodi() == VR)
			arvo += .25f;
		if(_lauta[4][4] != NULL && _lauta[4][4]->getKoodi() == VR)
			arvo += .25f;
	}
	else if(vari == 1)
	{
		if(_lauta[3][2] != NULL && _lauta[3][2]->getKoodi() == MS)
			arvo += .11f;
		if(_lauta[4][2] != NULL && _lauta[4][2]->getKoodi() == MS)
			arvo += .11f;
		if(_lauta[3][5] != NULL && _lauta[3][5]->getKoodi() == MS)
			arvo += .11f;
		if(_lauta[4][5] != NULL && _lauta[4][5]->getKoodi() == MS)
			arvo += .11f;
		if(_lauta[3][2] != NULL && _lauta[3][2]->getKoodi() == MR)
			arvo += .11f;
		if(_lauta[4][2] != NULL && _lauta[4][2]->getKoodi() == MR)
			arvo += .11f;
		if(_lauta[3][5] != NULL && _lauta[3][5]->getKoodi() == MR)
			arvo += .11f;
		if(_lauta[4][5] != NULL && _lauta[4][5]->getKoodi() == MR)
			arvo += .11f;

		if(_lauta[3][3] != NULL && _lauta[3][3]->getKoodi() == MS)
			arvo += .25f;
		if(_lauta[4][3] != NULL && _lauta[4][3]->getKoodi() == MS)
			arvo += .25f;
		if(_lauta[3][4] != NULL && _lauta[3][4]->getKoodi() == MS)
			arvo += .25f;
		if(_lauta[4][4] != NULL && _lauta[4][4]->getKoodi() == MS)
			arvo += .25f;
		if(_lauta[3][3] != NULL && _lauta[3][3]->getKoodi() == MR)
			arvo += .25f;
		if(_lauta[4][3] != NULL && _lauta[4][3]->getKoodi() == MR)
			arvo += .25f;
		if(_lauta[3][4] != NULL && _lauta[3][4]->getKoodi() == MR)
			arvo += .25f;
		if(_lauta[4][4] != NULL && _lauta[4][4]->getKoodi() == MR)
			arvo += .25f;
	}
	return arvo;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa

	//valkeille ydinkeskusta



	//valkeille laitakeskusta



	//mustille ydinkeskusta

	//mustille laitakeskusta

}


float Asema::linjat(int vari)
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

MinMaxPaluu Asema::minimax(int syvyys, float alpha, float beta)
{
	MinMaxPaluu paluuarvo;
	// Generoidaan aseman lailliset siirrot.
	std::vector<Siirto> siirrot;
	siirrot.reserve(50);
	annaLaillisetSiirrot(siirrot);

	// Rekursion kantatapaus 1: peli on loppu
	if(siirrot.empty())
	{
		if(onkoRuutuUhattu(&etsiKuninkaanSijainti(_siirtovuoro), !_siirtovuoro))
			paluuarvo._evaluointiArvo = _siirtovuoro == 0 ? 1 : -1;
		else
			paluuarvo._evaluointiArvo = 0;
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	if(syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s

	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

	if(_siirtovuoro == 0)
	{
		paluuarvo._evaluointiArvo = INT_MIN;
		for(Siirto s : siirrot)
		{
			Asema uusiAsema = *this;
			uusiAsema.paivitaAsema(&s);

			MinMaxPaluu eval = uusiAsema.minimax(syvyys - 1, alpha, beta);

			if(eval._evaluointiArvo > paluuarvo._evaluointiArvo)
			{
				paluuarvo._evaluointiArvo = eval._evaluointiArvo;
				paluuarvo._parasSiirto = s;
			}

			alpha = std::max(alpha, eval._evaluointiArvo);
			if(beta <= alpha)
				break;
		}
	}
	else
	{
		paluuarvo._evaluointiArvo = INT_MAX;
		for(Siirto s : siirrot)
		{
			Asema uusiAsema = *this;
			uusiAsema.paivitaAsema(&s);

			MinMaxPaluu eval = uusiAsema.minimax(syvyys - 1, alpha, beta);

			if(eval._evaluointiArvo < paluuarvo._evaluointiArvo)
			{
				paluuarvo._evaluointiArvo = eval._evaluointiArvo;
				paluuarvo._parasSiirto = s;
			}

			beta = std::min(beta, eval._evaluointiArvo);
			if(beta <= alpha)
				break;
		}
	}

	return paluuarvo;
	/*MinMaxPaluu paluuarvo;
	// Generoidaan aseman lailliset siirrot.
	std::vector<Siirto> siirrot;
	siirrot.reserve(50);
	annaLaillisetSiirrot(siirrot);

	// Rekursion kantatapaus 1: peli on loppu
	if(siirrot.empty())
	{
		if(onkoRuutuUhattu(&etsiKuninkaanSijainti(_siirtovuoro), !_siirtovuoro))
			paluuarvo._evaluointiArvo = _siirtovuoro == 0 ? 1 : -1;
		else
			paluuarvo._evaluointiArvo = 0;
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	if(syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s

	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	paluuarvo._evaluointiArvo = (_siirtovuoro == 0 ? -1000 : 1000);

	for(Siirto s : siirrot)
	{
		Asema uusiAsema = *this;
		uusiAsema.paivitaAsema(&s);

		MinMaxPaluu arvo = uusiAsema.minimax(syvyys - 1, alpha, beta);

		if(_siirtovuoro == 0 && arvo._evaluointiArvo > paluuarvo._evaluointiArvo)
		{
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = s;
		}
		if(_siirtovuoro == 1 && arvo._evaluointiArvo < paluuarvo._evaluointiArvo)
		{
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = s;
		}
	}

	return paluuarvo;*/
}


MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu max;

	if(syvyys == 0)
	{
		max._evaluointiArvo = evaluoi();
		return max;
	}
		
	std::vector<Siirto> siirtoLista;
	siirtoLista.reserve(50);
	annaLaillisetSiirrot(siirtoLista);

	if(siirtoLista.size() == 0)
	{
		max._evaluointiArvo = 1000000.0f;
		return max;
	}

	max._evaluointiArvo = (float)-INT_MAX;

	for(Siirto s : siirtoLista)
	{
		Asema seuraaja = *this;
		seuraaja.paivitaAsema(&s);
		
		MinMaxPaluu score = seuraaja.mini(syvyys-1);
		if(score._evaluointiArvo > max._evaluointiArvo)
		{
			max._evaluointiArvo = score._evaluointiArvo;
			max._parasSiirto = s;
		}
	}

	return max;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu min;

	if(syvyys == 0)
	{
		min._evaluointiArvo = -evaluoi();
		return min;
	}

	std::vector<Siirto> siirtoLista;
	siirtoLista.reserve(50);
	annaLaillisetSiirrot(siirtoLista);

	if(siirtoLista.size() == 0)
	{
		min._evaluointiArvo = 1000000.0f;
		return min;
	}

	min._evaluointiArvo = (float)INT_MAX;

	for(Siirto s : siirtoLista)
	{
		Asema seuraaja = *this;
		seuraaja.paivitaAsema(&s);

		MinMaxPaluu score = seuraaja.maxi(syvyys - 1);
		if(score._evaluointiArvo < min._evaluointiArvo)
		{
			min._evaluointiArvo = score._evaluointiArvo;
			min._parasSiirto = s;
		}
	}

	return min;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::vector<Siirto> vastustajaSiirrotLista;
	vastustajaSiirrotLista.reserve(50);

	//V‰reitt‰in k‰yd‰‰n l‰pi kaikki ruudut ja niiss‰ olevan nappulan siirrot ker‰t‰‰n vastustajan siirtolistaan
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(_lauta[y][x] == NULL)
				continue;
			if(_lauta[y][x]->getVari() == vastustajanVari)
				_lauta[y][x]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(x, y), this, vastustajanVari); // myˆh.sidonta
		}
	}

	// K‰yd‰‰n vastustajaSiirtoLista l‰pi ja jos sielt‰ lˆytyy tarkasteltava ruutu niin tiedet‰‰n sen olevan uhattu
	for(Siirto s : vastustajaSiirrotLista)
		if(ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi())
			return true;
	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::vector<Siirto>& lista, int vari)
{
	// poistaa listasta siirrot jotka viev‰t oman kuninkaan shakkiin
	// k‰yd‰‰n saatua siirtolistaa l‰pi ja jos siell‰ oleva siirto asettaa kuninkaan shakkiin, 
	// niin siirto poistetaan listasta
	Ruutu kuninkaanSijainti = etsiKuninkaanSijainti(_siirtovuoro);


	// Jotta ei jouduta perumaan oikeaan asemaan tehty‰ siirtoa
	Asema testiAsema;
	std::vector<Siirto> siivottuSiirrotLista;
	siivottuSiirrotLista.reserve(50);
	for(Siirto s : lista)
	{
		testiAsema = *this;
		testiAsema.paivitaAsema(&s);
		int x, y;

		// Kuninkaan siirto?
		if(s.onkoLyhytLinna())
		{
			x = 6;
			if(getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else if(s.onkoPitkaLinna())
		{
			x = 2;
			if(getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else
		{
			Nappula* siirtyva = _lauta[s.getAlkuruutu().getRivi()][s.getAlkuruutu().getSarake()];
			if((siirtyva != NULL && siirtyva->getKoodi() == VK) || (siirtyva != NULL && siirtyva->getKoodi() == MK))
			{
				x = s.getLoppuruutu().getSarake();
				y = s.getLoppuruutu().getRivi();
			}
			else
			{
				// Ei ole, kuninkaan sijainti sama kuin ennen siirron s kokeilua
				x = kuninkaanSijainti.getSarake();
				y = kuninkaanSijainti.getRivi();
			}
		}

		// huom !vari
		if(!testiAsema.onkoRuutuUhattu(&Ruutu(x, y), !vari) == true)
		{
			siivottuSiirrotLista.push_back(s);
		}
	}
	lista = siivottuSiirrotLista;
}

void Asema::annaLinnoitusSiirrot(std::vector<Siirto>& lista)
{
	if(_siirtovuoro == 0)
	{
		if(_onkoValkeaKuningasLiikkunut)
			return;

		if(!_onkoValkeaKTliikkunut &&_lauta[0][5] == NULL && _lauta[0][6] == NULL && !onkoRuutuUhattu(&Ruutu(4, 0), !_siirtovuoro) && 
		   !onkoRuutuUhattu(&Ruutu(5, 0), !_siirtovuoro) && !onkoRuutuUhattu(&Ruutu(6, 0), !_siirtovuoro))
			lista.emplace_back(true, false);
		if(!_onkoValkeaDTliikkunut && _lauta[0][1] == NULL && _lauta[0][2] == NULL && _lauta[0][3] == NULL && !onkoRuutuUhattu(&Ruutu(4, 0), !_siirtovuoro) &&
		   !onkoRuutuUhattu(&Ruutu(3, 0), !_siirtovuoro) && !onkoRuutuUhattu(&Ruutu(2, 0), !_siirtovuoro))
			lista.emplace_back(false, true);
	}
	else if(_siirtovuoro == 1)
	{
		if(_onkoMustaKuningasLiikkunut)
			return;

		if(!_onkoMustaKTliikkunut &&_lauta[7][5] == NULL && _lauta[7][6] == NULL && !onkoRuutuUhattu(&Ruutu(4, 7), !_siirtovuoro) &&
		   !onkoRuutuUhattu(&Ruutu(5, 7), !_siirtovuoro) && !onkoRuutuUhattu(&Ruutu(6, 7), !_siirtovuoro))
			lista.emplace_back(true, false);
		if(!_onkoMustaDTliikkunut && _lauta[7][1] == NULL && _lauta[7][2] == NULL && _lauta[7][3] == NULL && !onkoRuutuUhattu(&Ruutu(4, 7), !_siirtovuoro) &&
		   !onkoRuutuUhattu(&Ruutu(3, 7), !_siirtovuoro) && !onkoRuutuUhattu(&Ruutu(2, 7), !_siirtovuoro))
			lista.emplace_back(false, true);
	}
}


void Asema::annaRaakaSiirrot(std::vector<Siirto>& lista)
{
	for(int y = 0; y < 8; y++)
		for(int x = 0; x < 8; x++)
			if(_lauta[y][x] != NULL && _lauta[y][x]->getVari() == _siirtovuoro)
				_lauta[y][x]->annaSiirrot(lista, &Ruutu(x, y), this, _siirtovuoro);
}

Ruutu Asema::etsiKuninkaanSijainti(int vari)
{
	for(int y = 0; y < 8; y++)
		for(int x = 0; x < 8; x++)
		{
			if(_lauta[y][x] != NULL)
			{
				if(vari == 0 && _lauta[y][x]->getKoodi() == VK)
					return Ruutu(x, y);
				else if(vari == 1 && _lauta[y][x]->getKoodi() == MK)
					return Ruutu(x, y);
			}
		}
			
	std::wcout << "Ei lˆytyny kuningasta\n";
	return Ruutu();
}


void Asema::annaLaillisetSiirrot(std::vector<Siirto>& lista)
{
	std::vector<Siirto> raakaSiirrot;
	raakaSiirrot.reserve(50);
	annaRaakaSiirrot(raakaSiirrot);
	annaLinnoitusSiirrot(raakaSiirrot);

	// Suodatetaan siirrot joissa kuningas tulisi uhatuksi

	huolehdiKuninkaanShakeista(raakaSiirrot, _siirtovuoro);

	/*
	std::vector<Siirto> laillisetSiirrot;
	laillisetSiirrot.reserve(50);

	Ruutu kuninkaanSijainti = etsiKuninkaanSijainti(getSiirtovuoro());

	for(Siirto s : raakaSiirrot)
	{
		Asema vastustajanVuoroAsema = *this;
		vastustajanVuoroAsema.paivitaAsema(&s);

		

		if(!vastustajanVuoroAsema.onkoRuutuUhattu(&kuninkaanSijainti, vastustajanVuoroAsema.getSiirtovuoro()))
		{
			laillisetSiirrot.push_back(s);
		}
	}
	*/
	lista = raakaSiirrot;
}

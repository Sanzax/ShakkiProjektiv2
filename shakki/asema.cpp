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

	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL"
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
			_lauta[i][j] = NULL;
	
	
	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
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
		if((siirrettava->getKoodi() == VS || siirrettava->getKoodi() == MS) && (alkuX != loppuX) && (_lauta[loppuY][loppuX] == NULL))
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
		//else if(siirrettava->getKoodi() == VT && alkuX == 0 && alkuY == 7) _onkoValkeaKTliikkunut = true;
		else if (siirrettava->getKoodi() == VT && alkuX == 7 && alkuY == 0) _onkoValkeaKTliikkunut = true;
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

const float materiaaliKerroin = 1;
const float kuningasKerroin = 1;
const float linjaKerroin = 0.05f;
const float keskustaKerroin = 1;

//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta

float Asema::evaluoi()
{
	//1. Nappuloiden arvo
	float vMateriaali = laskeNappuloidenArvo(0) * materiaaliKerroin;
	float mMateriaali = laskeNappuloidenArvo(1) * materiaaliKerroin;

	//2. Kuningas turvassa
	float vKuningasArvo = kuningasTurvassa(0) * kuningasKerroin;
	float mKuningasArvo = kuningasTurvassa(1) * kuningasKerroin;

	//3. Arvosta keskustaa
	float vKeskusta = nappuloitaKeskella(0) * keskustaKerroin;
	float mKeskusta = nappuloitaKeskella(1) * keskustaKerroin;


	// 4. Arvosta linjoja
	float vLinjat = linjat(0) * linjaKerroin;
	float mLinjat = linjat(1) * linjaKerroin;

	float vArvo = vMateriaali + vKeskusta + vLinjat + vKuningasArvo;
	float mArvo = mMateriaali + mKeskusta + mLinjat + mKuningasArvo;

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

float Asema::kuningasTurvassa(int vari)
{
	float valkeaArvo = 0;
	float  mustaArvo = 0;
	if(onkoAvausTaiKeskipeli( 0))
	{
		// Jos lyhell‰ puolella saa lis‰arvoa 2 edellytt‰‰ ett‰ f ja g sotilas  paikallaan 
		if(_lauta[0][6] != NULL && _lauta[1][5] != NULL && _lauta[1][6] != NULL)
		{
			if(_lauta[0][6]->getKoodi() == VK && (_lauta[1][5]->getKoodi() == VS && (_lauta[1][6]->getKoodi() == VS)))
				valkeaArvo += 2;
		}
		// Jos pitk‰ll‰ puolella saa lis‰arvooa 1 edellytt‰‰ ett‰  c ja b sotilas paikallaan
		if(_lauta[0][1] != NULL && _lauta[0][2] != NULL && _lauta[1][1] != NULL && _lauta[2][1] != NULL)
		{
			if(_lauta[0][1]->getKoodi() == VK || _lauta[0][2]->getKoodi() == VK && (_lauta[1][1]->getKoodi() == VS && (_lauta[1][2]->getKoodi() == VS)))
				valkeaArvo += 1;
		}
	}
	if(onkoAvausTaiKeskipeli(1))
	{
		// Jos lyhell‰ puolella saa lis‰arvoa 2 edellytt‰‰ ett‰ f ja g sotilas  paikallaan 
		if(_lauta[7][6] != NULL && _lauta[6][5] != NULL && _lauta[6][6] != NULL)
		{
			if(_lauta[7][6]->getKoodi() == MK && (_lauta[6][5]->getKoodi() == MS && (_lauta[6][6]->getKoodi() == MS)))
				mustaArvo += 2;
		}
		// Jos pitk‰ll‰ puolella saa lis‰arvooa 1 edelytt‰‰ ett‰  c ja b sotilas paikallaan
		if(_lauta[7][1] != NULL && _lauta[7][2] != NULL && _lauta[7][1] != NULL && _lauta[7][1] != NULL)
		{
			if(_lauta[7][1]->getKoodi() == MK || _lauta[7][2]->getKoodi() == MK && (_lauta[7][1]->getKoodi() == MS && (_lauta[7][2]->getKoodi() == MS)))
				mustaArvo += 1;
		}
	}

	if(vari == 0)
		return valkeaArvo;
	else
		return mustaArvo;
}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	int valkeaUpseeriLkm = 0;
	int mustaUpseeriLkm = 0;
	bool valkeaDaami = false;
	bool mustaDaami = false;
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(_lauta[x][y] == NULL) continue;
			int nappulanNimi = _lauta[x][y]->getKoodi();
			//Valkoiset
			if(nappulanNimi == VD)
			{
				valkeaUpseeriLkm += 1;
				valkeaDaami = true;
			}
			if(nappulanNimi == VT || nappulanNimi == VL || nappulanNimi == VR)
				mustaUpseeriLkm += 1;

			//Mustat
			if(nappulanNimi == MD)
			{
				mustaUpseeriLkm += 1;
				mustaDaami = true;
			}
			if(nappulanNimi == MT || nappulanNimi == ML || nappulanNimi == MR)
				mustaUpseeriLkm += 1;
		}
	}
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	if(vari == 0)
	{
		if(mustaUpseeriLkm > 2 || (mustaDaami == true && mustaUpseeriLkm > 1))
			return true;
		else
			return false;
	}
	else
	{
		if(valkeaUpseeriLkm > 2 || (valkeaDaami == true && valkeaUpseeriLkm > 1))
			return true;
		else
			return false;
	}

}

float Asema::nappuloitaKeskella(int vari)
{
	float valkeaKeskella = 0;
	float mustaKeskella = 0;
	//valkeille ydinkeskusta

	if(_lauta[3][3] != NULL && (_lauta[3][3]->getKoodi() == VS || _lauta[3][3]->getKoodi() == VR))
	{
		valkeaKeskella += 0.25;
	}
	if(_lauta[3][4] && (_lauta[3][4]->getKoodi() == VS || _lauta[3][4]->getKoodi() == VR))
	{
		valkeaKeskella += 0.25;
	}
	if(_lauta[4][3] != NULL && (_lauta[4][3]->getKoodi() == VS || _lauta[4][3]->getKoodi() == VR))
	{
		valkeaKeskella += 0.25;
	}
	if(_lauta[4][4] != NULL && (_lauta[4][4]->getKoodi() == VS || _lauta[4][4]->getKoodi() == VR))
	{
		valkeaKeskella += 0.25;
	}
	//valkeille laitakeskusta
	for(int x = 2; x < 6; x++)
	{
		if(_lauta[2][x] != NULL && (_lauta[2][x]->getKoodi() == VS || _lauta[2][x]->getKoodi() == VR))
		{
			valkeaKeskella += 0.11;
		}
		if(_lauta[5][x] != NULL && (_lauta[5][x]->getKoodi() == VS || _lauta[5][x]->getKoodi() == VR))
		{
			valkeaKeskella += 0.11;
		}
	}
	for(int y = 3; y < 5; y++)
	{
		if(_lauta[y][2] != NULL && (_lauta[y][2]->getKoodi() == VS || _lauta[y][2]->getKoodi() == VR))
		{
			valkeaKeskella += 0.11;
		}
		if(_lauta[y][5] != NULL && (_lauta[y][5]->getKoodi() == VS || _lauta[y][5]->getKoodi() == VR))
		{
			valkeaKeskella += 0.11;
		}
	}

	//mustille ydinkeskusta
	if(_lauta[3][3] != NULL && (_lauta[3][3]->getKoodi() == MS || _lauta[3][3]->getKoodi() == MR))
	{
		mustaKeskella += 0.25;
	}
	if(_lauta[3][4] != NULL && (_lauta[3][4]->getKoodi() == MS || _lauta[3][4]->getKoodi() == MR))
	{
		mustaKeskella += 0.25;
	}
	if(_lauta[4][3] != NULL && (_lauta[4][3]->getKoodi() == MS || _lauta[4][3]->getKoodi() == MR))
	{
		mustaKeskella += 0.25;
	}
	if(_lauta[4][4] != NULL && (_lauta[4][4]->getKoodi() == MS || _lauta[4][4]->getKoodi() == MR))
	{
		mustaKeskella += 0.25;
	}
	//mustille laitakeskusta
	for(int x = 2; x < 6; x++)
	{
		if(_lauta[2][x] != NULL && (_lauta[2][x]->getKoodi() == MS || _lauta[2][x]->getKoodi() == MR))
		{
			mustaKeskella += 0.11;
		}
		if(_lauta[5][x] != NULL && (_lauta[5][x]->getKoodi() == MS || _lauta[5][x]->getKoodi() == MR))
		{
			mustaKeskella += 0.11;
		}
	}
	for(int y = 3; y < 5; y++)
	{
		if(_lauta[y][2] != NULL && (_lauta[y][2]->getKoodi() == MS || _lauta[y][2]->getKoodi() == MR))
		{
			mustaKeskella += 0.11;
		}
		if(_lauta[y][5] != NULL && (_lauta[y][5]->getKoodi() == MS || _lauta[y][5]->getKoodi() == MR))
		{
			mustaKeskella += 0.11;
		}
	}
	if(vari == 0)
		return valkeaKeskella;
	else
		return mustaKeskella;

}

float Asema::linjat(int vari)
{
	int valkeaLaillisiaSiirtoja = 0;
	int mustaLaillisiaSiirtoja = 0;
	std::vector<Siirto> valkealista;
	valkealista.reserve(50);
	std::vector<Siirto> mustalista;
	mustalista.reserve(50);
	//valkoiset
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(_lauta[y][x] == NULL)
			{
				continue;
			}
			if(_lauta[y][x]->getKoodi() == VL)
				_lauta[y][x]->annaSiirrot(valkealista, &Ruutu(x, y), this, 0);
			if(_lauta[y][x]->getKoodi() == VT)
				_lauta[y][x]->annaSiirrot(valkealista, &Ruutu(x, y), this, 0);
		}
	}
	//mustat
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(_lauta[y][x] == NULL)
			{
				continue;
			}
			if(_lauta[y][x]->getKoodi() == ML)
				_lauta[y][x]->annaSiirrot(mustalista, &Ruutu(x, y), this, 0);
			if(_lauta[y][x]->getKoodi() == MT)
				_lauta[y][x]->annaSiirrot(mustalista, &Ruutu(x, y), this, 0);
		}
	}
	valkeaLaillisiaSiirtoja = valkealista.size();
	mustaLaillisiaSiirtoja = mustalista.size();

	if(vari == 0)
		return valkeaLaillisiaSiirtoja;
	else
		return mustaLaillisiaSiirtoja;

}

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
	Ruutu kuninkaanSijainti = etsiKuninkaanSijainti(_siirtovuoro);

	Asema testiAsema;
	std::vector<Siirto> siivottuSiirrotLista;
	siivottuSiirrotLista.reserve(50);
	for(Siirto s : lista)
	{
		testiAsema = *this;
		testiAsema.paivitaAsema(&s);
		int x, y;

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
				x = kuninkaanSijainti.getSarake();
				y = kuninkaanSijainti.getRivi();
			}
		}

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

	lista = raakaSiirrot;
}

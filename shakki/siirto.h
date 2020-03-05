#pragma once
#include "ruutu.h"
#include <iostream>
// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell� Nappula-osoittimia ilman,
// ett� nappula.h -tiedostoa t�ytyy includoida.
class Nappula; 


// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestaly�nti).
class Siirto
{
public:
	Siirto(Ruutu, Ruutu);
	Siirto(){}
	Siirto(bool, bool); // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi?
	Ruutu getAlkuruutu() const;
	Ruutu getLoppuruutu() const;
	bool onkoLyhytLinna() const;
	bool onkoPitkaLinna() const;
	Nappula* _miksikorotetaan = 0; 

	bool operator==(const Siirto& s)
	{
		if(_alkuRuutu == s.getAlkuruutu() && _loppuRuutu == s.getLoppuruutu() && _lyhytLinna == s.onkoLyhytLinna() && _pitkaLinna == s.onkoPitkaLinna())
			return true;
		return false;
	}

	void tulosta();


private:
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	bool _lyhytLinna;
	bool _pitkaLinna;
};
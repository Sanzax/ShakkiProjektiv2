#include "siirto.h"


Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu) : _alkuRuutu(alkuRuutu), _loppuRuutu(loppuRuutu), _lyhytLinna(false), _pitkaLinna(false)
{}

Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) : _alkuRuutu(Ruutu()), _loppuRuutu(Ruutu()), _lyhytLinna(lyhytLinna), _pitkaLinna(pitkaLinna)
{}

void Siirto::tulosta()
{
	if(_lyhytLinna)
		std::wcout << "O-O";
	else if(_pitkaLinna)
			std::wcout << "O-O-O";
	else
	{
		std::wcout << (wchar_t)(97 + getAlkuruutu().getSarake()) << getAlkuruutu().getRivi() + 1 << "-" <<
			(wchar_t)(97 + getLoppuruutu().getSarake()) << getLoppuruutu().getRivi() + 1 << ", ";
	}

	
}


Ruutu Siirto::getAlkuruutu() const
{
	return _alkuRuutu;
}


Ruutu Siirto::getLoppuruutu() const
{
	return _loppuRuutu;
}


bool Siirto::onkoLyhytLinna() const
{
	return _lyhytLinna;
}


bool Siirto::onkoPitkaLinna() const
{
	return _pitkaLinna;
}

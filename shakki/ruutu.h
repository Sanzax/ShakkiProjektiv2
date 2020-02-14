#pragma once


// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.
class Ruutu{
public:
	Ruutu(int, int);
	Ruutu() {}
	int getRivi() const;
	int getSarake() const;
	void setRivi(int);
	void setSarake(int);

	bool operator==(const Ruutu& r)
	{
		if(_sarake == r.getSarake() && _rivi == r.getRivi())
			return true;
		return false;
	}

private:
	int _sarake;
	int _rivi;
};

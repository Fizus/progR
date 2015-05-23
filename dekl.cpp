#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

class Data 
{
	public:
		double E, px, py, pz, m;
		Data(double E, double px,double py,double pz);
		double module();
		double product(Data b);
		double cos(Data b);
};
Data::Data(double E, double px, double py, double pz): E(E), px(px), py(py), pz(pz)
{	
	m = pow(E*E - px*px - py*py - pz* pz, 0.5);
}

double Data::module() {return pow(px*px + py*py + pz*pz, 0.5);}

double Data::product(Data b) {return px*b.px + py*b.py + pz*b.pz;}

double Data::cos(Data b){ return product(b)/module()/b.module();}

double mass_inv (vector <Data> b)
{	
	double tab[4]={0};
	for (auto i = b.begin(); i!= b.end(); ++i)
	{	tab[0] += i->E;
		tab[1] += i->px;
		tab[2] += i->py;
		tab[3] += i->pz;
	}
	return pow(tab[0]*tab[0] - tab[1]*tab[1] - tab[2]*tab[2] - tab[3]*tab[3], 0.5);
}

int main()
{


}

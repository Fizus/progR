#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "gnuplot_i.hpp"

using namespace std;

double srednia (vector<double> v)
{
    double s=0.0;
    for(int i=0; i<v.size(); i++)
        s+=v[i];
    s=(double)s/(double)v.size();
    return s;
}

double odchylenie (vector<double> v)
{
    double s=0.0;
    double sr=srednia(v);
    for(int i=0; i<v.size(); i++)
    {
        s+=pow((v[i]-sr), 2);
    }
    s=(double)s/(double)v.size();
    s=sqrt(s);
    
    return s;
}

class histogram
{
    double a,b;
    vector<int>bins;
public:
    histogram (double a,double b, int n, vector<double> dane); //od a do b n kubelkow,
    histogram (double o, int n, vector<double> dane); // o sigma od sredniej, n kubelkow
    int odczyt (int i); // odczytuje i ty kubelek
    void wyrzut (ostream& out); //wypisuje na output
};

void histogram::wyrzut (ostream& out)
{
    for(int i=0; i<bins.size(); i++)
    {
        out << (double)a+(b-a)/(double)bins.size()*((double)i+0.5)<<" "<< bins[i] << endl;
    }
}

histogram::histogram (double o,int n, vector<double> dane)
{
    int k;
    a=srednia(dane)-o*odchylenie(dane);
    b=srednia(dane)+o*odchylenie(dane);
    for(int i=0; i<n; i++)
    {
        bins.push_back(0);
    }
    for(int i=0; i<dane.size(); i++)
    {
        k=(int)((double)(((double)n*(dane[i]-a)/(b-a))));
        if(k<n && k>=0)
            bins[k]++;
    }
}

int histogram::odczyt (int i)
{
    if(i>=0 && i<bins.size() )
        return bins[i];
    else
        return -1;
}

histogram::histogram (double a,double b, int n, vector<double> dane): a(a), b(b)
{
    int k;
    for(int i=0; i<n; i++)
    {
        bins.push_back(0);
    }
    for(int i=0; i<dane.size(); i++)
    {
        k=(int)(((double)((double)n*(dane[i]-a)/(b-a))));
        if(k<n && k>=0)
        bins[k]++;
    }
}

class czytacz // czyta z pliku tekstowego, w ktorym pierwsza linia jest naglowkami
{
    vector< vector<double> > vtekst;
public:
    czytacz(string plik);
    int rozmiar();
    double komorka(int i, int j);
    vector<double> kolumna(int k);
};

vector<double> czytacz::kolumna(int k)
{
    vector<double> column;
    for(int i=0; i<vtekst.size(); i++)
    {
        column.push_back(vtekst[i][k]);
    }
    
    return column;
}

double czytacz::komorka(int i, int j)
{
    return vtekst[i][j];
}

int czytacz::rozmiar()
{
    return vtekst.size();
}

czytacz::czytacz(string plik)
{
    string slinia;
    double liczba;
    ifstream we (plik);
    getline(we,slinia);
    getline(we,slinia);
    while(getline(we,slinia))
    {
        istringstream zrodlo(slinia);
        vector<double>vlinia;
        while(zrodlo>>liczba)
        {
            vlinia.push_back(liczba);
        }
        vtekst.push_back(vlinia);
    }
}

void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}

void plot (vector<double> wartosc, vector<double> liczba_trafien, string nazwa_pliku, string podpis)
{
    Gnuplot g1("histogram");

    g1.savetops(nazwa_pliku);
    g1.set_style("boxes");
    g1.plot_xy(wartosc, liczba_trafien, podpis);

    g1.showonscreen(); // window output
    g1.replot();
    wait_for_key();
}

int main(void)
{
    czytacz dane("tau.data");
    histogram wykres(3,100,dane.kolumna(2));
    ofstream wy("wynik.txt");
    wykres.wyrzut(wy);
    
    return 0;
}

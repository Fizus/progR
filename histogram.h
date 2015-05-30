#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include<vector>
using namespace std;
class histogram
{
    double a,b;
    vector<int>bins;
public:
    histogram (double a,double b, int n, vector<double> dane); //od a do b n kubelkow,
    histogram (double o,int n, vector<double> dane); // o sigma od œredniej, n kubelkow
    int odczyt (int i); // odczytuje i ty kubelek
    void wyrzut1 (vector<double> liczba_trafien); //wypisuje do wektora
    void wyrzut2 (vector<double> srodek);
};

#endif // HISTOGRAM_H

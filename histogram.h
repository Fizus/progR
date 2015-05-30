#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include<vector>
#include<cmath>
using namespace std;
class histogram
{
    double a,b;
    vector<int>bins;
public:
    histogram (double a,double b, int n, vector<double> dane); //od a do b n kubelkow,
    histogram (double o,int n, vector<double> dane); // o sigma od œredniej, n kubelkow
    int odczyt (int i); // odczytuje i ty kubelek
    void wyrzut1 (vector<double>& liczba_trafien); //wypisuje do wektora
    void wyrzut2 (vector<double>& srodek);
};
double srednia (vector<double> v)
{
    double s=0;
    for(int i=0;i<v.size();i++)
        s+=v[i];
    s=(double)s/(double)v.size();
    return s;
}
double odchylenie (vector<double> v)
{
    double s=0;
    double sr=srednia(v);
    for(int i=0;i<v.size();i++)
        s+=(v[i]-sr)*(v[i]-sr);
        s=(double)s/(double)v.size();
        s=sqrt(s);
        return s;
}
histogram::histogram (double o,int n, vector<double> dane)
{
    int k;
    a=srednia(dane)-o*odchylenie(dane);
    b=srednia(dane)+o*odchylenie(dane);
      for(int i=0;i<n;i++)
        bins.push_back(0);
    for(int i=0;i<dane.size();i++)
    {
        k=(int)((double)(((double)n*(dane[i]-a)/(b-a))));
       if(k<n&&k>=0)
        bins[k]++;
    }

}
int histogram::odczyt (int i)
{
    if(i>=0&&i<bins.size())
    return bins[i];
    else return -1;
}
histogram::histogram (double a,double b, int n, vector<double> dane): a(a), b(b)
{
    int k;
    for(int i=0;i<n;i++)
        bins.push_back(0);
    for(int i=0;i<dane.size();i++)
    {
    k=(int)(((double)((double)n*(dane[i]-a)/(b-a))));
       if(k<n&&k>=0)
        bins[k]++;
    }
}
void histogram::wyrzut1 (vector <double>& liczba_trafien)
{
    for(int i=0;i<bins.size();i++)
        liczba_trafien.push_back(bins[i]);
}
void histogram::wyrzut2 (vector <double>& srodek)
{
    double x;
    for(int i=0;i<bins.size();i++)
    {
         x=(double)a+(b-a)/(double)bins.size()*((double)i+0.5);
         srodek.push_back(x);
    }

}
#endif // HISTOGRAM_H

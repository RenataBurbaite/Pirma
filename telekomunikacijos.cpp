//Pagrindiniai telekomunikaciju rodikliai
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;
struct Rysys{
    string tipas;
    int vid;
};
//====================================
struct Metai{
    int m;
    int T[50];
    int maziausia;
};
//======================================
void Skaitymas(Rysys R[], int &s, Metai M[], int &m){
    ifstream fd("Telekomunikacijos.txt");
    fd >> s;
    fd.ignore();
    for(int i = 0; i < s; i++){
        fd >> R[i].tipas;
        fd.ignore();
    }
    m = 0;
    while(!fd.eof()){
        fd >> M[m].m;
        for(int i = 0; i < s; i++)
            fd >> M[m].T[i];
        m++;
    }
    fd.close();
}
//=====================================
bool Dideja(Metai M[], int m, int koks){
    int k = 0;
    for(int i = 0; i < m - 1; i++)
        if(M[i].T[koks] < M[i + 1].T[koks]) k++;
    if(k == m - 1) return true;
    else return false;
}
//========================================
int Maziausia(Metai met, int s){
    int m = 0;
    for(int i = 0; i < s; i++)
        if(met.T[i]< met.T[m]) m = i;
    return m;
}
//==============================================
void Pilnas(Metai M[], int m, int s){
    for(int i = 0; i < m; i++)
        M[i].maziausia = M[i].T[Maziausia(M[i], s)];
}
//=============================================
int Minimumas(Metai M[], int m){
    int mz = 0;
    for(int i = 0; i < m; i++)
        if(M[i].maziausia <= M[mz].maziausia) mz = i;
    return mz;
}
//===============================================
int Vidurkis(Metai M[], int m, int kuris){
    int v = 0;
    for(int i = 0; i < m; i++)
        v = v + M[i].T[kuris];
    return v/m;
}
//===============================================
void VisuVidurkis(Metai M[], int m, Rysys R[], int s){
        for(int i = 0; i < s; i++)
            R[i].vid = Vidurkis(M,m,i);
}
//==============================================
void Rikiavimas(Rysys R[], int s){
    int m; Rysys sukeit;
    for(int i = 0; i < s - 1; i++){
        m = i;
        for(int j = i +1; j < s; j++)
            if(R[j].vid > R[m].vid || (R[j].vid == R[m].vid && R[j].tipas < R[m].tipas)) m = j;
    sukeit = R[i]; R[i] = R[m]; R[m] = sukeit;
    }
}
//============================================
void Salinimas(Rysys R[], int &s, int k){
    for(int i = k; i < s; i++)
        R[i] = R[i + 1];
    s--;
}
//===============================================
void Rasymas(Rysys R[], int s, Metai M[], int m){
    ofstream fr("telekomunikacijosrez.txt");
    for(int i = 0; i < s; i++)
        if(Dideja(M, m, i) == true) fr << R[i].tipas << endl;
    fr<< "------------------------------------------------" << endl;
    Pilnas(M, m, s);
    fr << M[Minimumas(M,m)].m << " " << M[Minimumas(M, m)].maziausia << endl;
    fr<< "------------------------------------------------" << endl;
    VisuVidurkis(M,m,R,s);
    for(int i = 0; i < s; i++)
        fr << R[i].tipas << " " << R[i].vid << endl;
    fr<< "------------------------------------------------" << endl;
    Rikiavimas(R, s);
    for(int i = 0; i < s; i++)
        fr << R[i].tipas << " " << R[i].vid << endl;
    fr<< "------------------------------------------------" << endl;
    int sal;
    if(s % 2 == 0) sal = (s - 1) / 2;
    else sal = (s - 1) / 2 + 1;
    Salinimas(R,s, sal);
    for(int i = 0; i < s; i++)
        fr << R[i].tipas << " " << R[i].vid << endl;
    fr.close();
}
int main()
{
	Metai M[100];
	Rysys R[100];
	int s, m;
	Skaitymas(R, s, M, m);
	Rasymas(R, s, M, m);

        return 0;
}
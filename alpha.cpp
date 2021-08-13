#include <iostream>
#include <string>
#define maxa 100
using namespace std;

string hasil();

int result;

struct a{
    int id[maxa];
    string nama[maxa];
    string hasil[maxa];
}b, c;

string hasil(int hasil){
    string state;
    if (hasil == 1){
        state = "Berhasil";
        return state;
    }
    else {
        state = "Gagal";
        return state;
    }
}

int main(){
    int indexa = 0;

    result = 0;
    b.id[indexa] = 1604064 + indexa;
    b.nama[indexa] = "Lord";
    b.hasil[indexa] = hasil(result);
    indexa++;

    result = 1;
    b.id[indexa] = 1604064 + indexa;
    b.nama[indexa] = "Of";
    b.hasil[indexa] = hasil(result);
    indexa++;

    result = 1;
    b.id[indexa] = 1604064 + indexa;
    b.nama[indexa] = "Rings";
    b.hasil[indexa] = hasil(result);
    indexa++;

    int skl;
    cout << "Masukkan angka: ";
    cin >> skl;

    cout << "\n\n" << skl << endl << endl;

    int i = 0;
    while(!b.hasil[i].empty()){
        cout << "Battle ID: " << b.id[i] << endl;
        cout << "Musuh: " << b.nama[i] << endl;
        cout << "Hasil: " << b.hasil[i] << endl;
        i++;
        cout << "\n";
    }

    /* for (int i = 0; i < maxa; i++){
        if (b.hasil[i].empty()) ;
        else {
            cout << "Battle ID: " << b.id[i] << endl;
            cout << "Musuh: " << b.nama[i] << endl;
            cout << "Hasil: " << b.hasil[i] << endl;
        }
    }
    */

   // #include <unistd.h>
   // sleep(1);
}
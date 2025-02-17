#include <iostream>
using namespace std;


struct Lagu
{
    string judul,genre,durasi,tahun;
};


struct Publisher
{
    string nama;
};

struct Penyanyi
{
    string nama, genre;
    Lagu lagu[10];
    Publisher publisher[10];
};

int main(){
    Penyanyi daftarPenyanyi[100];
    daftarPenyanyi[0].nama = "halo";
    daftarPenyanyi[0].lagu[0].judul = "lol";
    daftarPenyanyi[0].lagu[1].judul = "wkwk"; 
    daftarPenyanyi[1].nama = "halo2";
    daftarPenyanyi[1].lagu[0].judul = "lol2";
    daftarPenyanyi[1].lagu[1].judul = "wkwk2";

    cout<< daftarPenyanyi[0].nama <<endl;
    cout<< daftarPenyanyi[0].lagu[0].judul<<endl;
    cout<< daftarPenyanyi[0].lagu[1].judul<<endl;

    cout<< daftarPenyanyi[1].nama <<endl;
    cout<< daftarPenyanyi[1].lagu[0].judul<<endl;
    cout<< daftarPenyanyi[1].lagu[1].judul<<endl;




}
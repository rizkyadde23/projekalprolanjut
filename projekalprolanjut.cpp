#include <iostream>
#include <string> //tambahan 
using namespace std;

struct Lagu {
    string judul, genre, durasi, tahun;
};

struct Publisher {
    string nama;
};

struct Penyanyi {
    string nama, genre;
    Lagu lagu[100];
    Publisher publisher[10];
};

Penyanyi daftarPenyanyi[100];
int jumlahPenyanyi = 0;

// Fungsi rekursif
void tampilkanLaguRekursif(Penyanyi penyanyi[], int jumlah, int index = 0) {
    if (index >= jumlah) return; // Basis rekursi

    cout << "Artis Ke-" << index + 1 << endl;
    cout << "Nama : " << penyanyi[index].nama << endl;
    for (int j = 0; j < 100 && !penyanyi[index].lagu[j].judul.empty(); j++) {
        cout << "Lagu Ke-" << j + 1 << endl;
        cout << "Judul : " << penyanyi[index].lagu[j].judul << endl;
        cout << "Genre : " << penyanyi[index].lagu[j].genre << endl;
        cout << "Durasi : " << penyanyi[index].lagu[j].durasi << endl;
        cout << "Tahun : " << penyanyi[index].lagu[j].tahun << endl;
    }
    tampilkanLaguRekursif(penyanyi, jumlah, index + 1); // Rekursi ke artis berikutnya
}

// Fungsi sequential search
void cariLaguSequential(Penyanyi penyanyi[], int jumlah, string cariJudul) {
    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        for (int j = 0; j < 100 && !penyanyi[i].lagu[j].judul.empty(); j++) {
            if (penyanyi[i].lagu[j].judul == cariJudul) {
                cout << "Lagu ditemukan!" << endl;
                cout << "Artis  : " << penyanyi[i].nama << endl;
                cout << "Judul  : " << penyanyi[i].lagu[j].judul << endl;
                cout << "Genre  : " << penyanyi[i].lagu[j].genre << endl;
                cout << "Durasi : " << penyanyi[i].lagu[j].durasi << endl;
                cout << "Tahun  : " << penyanyi[i].lagu[j].tahun << endl;
                ditemukan = true;
                return; // Langsung keluar setelah menemukan
            }
        }
    }

    if (!ditemukan) {
        cout << "Lagu tidak ditemukan!" << endl;
    }
}

int main() {
    int inputPenyanyi, inputLagu;

    // Input data
    cout << "Masukkan Berapa Penyanyi yang akan di data: ";
    cin >> inputPenyanyi;
    cin.ignore();
    jumlahPenyanyi += inputPenyanyi;

    for (int i = 0; i < inputPenyanyi; i++) {
        cout << "Artis Ke-" << i + 1 << endl;
        cout << "Masukkan Nama Artis : ";
        getline(cin>>ws, daftarPenyanyi[i].nama);

        cout << "Berapa Lagu Yang Dirilis : ";
        cin >> inputLagu;
        cin.ignore();

        for (int j = 0; j < inputLagu; j++) {
            cout << "Lagu Ke-" << j + 1 << endl;
            cout << "Judul Lagu : ";
            getline(cin>>ws, daftarPenyanyi[i].lagu[j].judul);
            cout << "Genre Lagu : ";
            getline(cin>>ws, daftarPenyanyi[i].lagu[j].genre);
            cout << "Durasi Lagu : ";
            getline(cin>>ws, daftarPenyanyi[i].lagu[j].durasi);
            cout << "Tahun Lagu : ";
            getline(cin>>ws, daftarPenyanyi[i].lagu[j].tahun);
        }
    }

    int pilihan;
    do {
        cout << "\n=== Menu ===" << endl;
        cout << "1. Tampilkan Semua Lagu" << endl;
        cout << "2. Cari Lagu" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanLaguRekursif(daftarPenyanyi, jumlahPenyanyi);
                break;
            case 2: {
                string cariJudul;
                cout << "Masukkan judul lagu yang ingin dicari: ";
                getline(cin>>ws, cariJudul);
                cariLaguSequential(daftarPenyanyi, jumlahPenyanyi, cariJudul);
                break;
            }
            case 3:
                cout << "Keluar dari program..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    } while (pilihan != 3);

    return 0;
}

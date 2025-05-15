#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Lagu {
    string judul, genre, durasi, tahun;
};

struct Penyanyi {
    string nama;
    Lagu lagu;
};


void writeDataCount(fstream &count, int &jumlahPenyanyi){
    count.open("count.txt",ios::in|ios::out);
    count<<jumlahPenyanyi;
    count.close();
}

void writeData(fstream &file, fstream &count,Penyanyi &data,int &jumlahPenyanyi){
    file.open("file.txt",ios::in|ios::out|ios::app);  
    file<<"ARTIS KE-"<<jumlahPenyanyi<<endl;
    file<<"NAMA : "<<data.nama<<endl;
    file<<"JUDUL : "<<data.lagu.judul<<endl;
    file<<"GENRE : "<<data.lagu.genre<<endl;
    file<<"DURASI : "<<data.lagu.durasi<<" menit"<<endl;
    file<<"TAHUN : "<<data.lagu.tahun<<endl;
    file<<endl;
    file.close();
}

// Fungsi input data penyanyi dan lagu
void inputData(fstream &file,fstream &count,Penyanyi &data, int &jumlahPenyanyi) {
    int inputPenyanyi,inputLagu;
    int buffer;
    cout << "Masukkan jumlah penyanyi yang akan didata: ";
    cin >> inputPenyanyi;
    cin.ignore();
    for (int i = jumlahPenyanyi; i < jumlahPenyanyi + inputPenyanyi; i++) {
        buffer = i+1;
        cout << "Artis Ke-" << i+1 << endl;
        cout << "Masukkan Nama Artis : ";
        getline(cin, data.nama);
        cout << "Berapa Lagu Yang Dirilis : ";
        cin >> inputLagu;
        cin.ignore();
        for (int j = 0; j < inputLagu; j++) {
            cout << "Lagu Ke-" << j + 1 << endl;
            cout << "Judul Lagu : ";
            getline(cin, data.lagu.judul);
            cout << "Genre Lagu : ";
            getline(cin, data.lagu.genre);
            cout << "Durasi Lagu : ";
            getline(cin, data.lagu.durasi);
            cout << "Tahun Lagu : ";
            getline(cin, data.lagu.tahun);
            writeData(file,count,data,buffer);
        }
    }
    jumlahPenyanyi += inputPenyanyi;
    writeDataCount(count,jumlahPenyanyi);
}

Penyanyi readData(fstream &file, Penyanyi &data) {
    string temp;
    size_t pos;
    // NO
    if (!getline(file, temp)) return data;
    // NAMA
    if (getline(file, temp)) {
        pos = temp.find(":");
        data.nama = (pos != string::npos && pos + 2 <= temp.size()) ? temp.substr(pos + 2) : "";
    }
    // JUDUL
    if (getline(file, temp)) {
        pos = temp.find(":");
        data.lagu.judul = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 1) : "";
    }
    // GENRE
    if (getline(file, temp)) {
        pos = temp.find(":");
        data.lagu.genre = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 1) : "";
    }
    // DURASI
    if (getline(file, temp)) {
        pos = temp.find(":");
        data.lagu.durasi = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 1) : "";
    }
    // TAHUN
    if (getline(file, temp)) {
        pos = temp.find(":");
        data.lagu.tahun = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 1) : "";
    }
    // Blank line
    getline(file, temp);
    return data;
}

// Fungsi rekursif
void tampilkanLaguRekursif(fstream &file,Penyanyi &data) {
    if (!file)
    {
        return;
    }
    streampos currentPos = file.tellg();
    data = readData(file, data);
    if(file.fail()||file.eof()){
        return;
    }
    cout<<"====================================="<<endl;
    cout<<"Nama Artis  : "<<data.nama<<endl;
    cout<<"Judul Lagu : "<<data.lagu.judul<<endl;
    cout<<"Genre Lagu : "<<data.lagu.genre<<endl;
    cout<<"Durasi Lagu : "<<data.lagu.durasi<<endl;
    cout<<"Tahun Lagu : "<<data.lagu.tahun<<endl;
    tampilkanLaguRekursif(file,data);
}

// Fungsi sequential search
void cariLaguSequential() {
    // bool ditemukan = false;
    // for (int i = 0; i < jumlah; i++) {
    //     for (int j = 0; j < 100 && !penyanyi[i].lagu[j].judul.empty(); j++) {
    //         if (penyanyi[i].lagu[j].judul == cariJudul) {
    //             cout << "Lagu ditemukan!" << endl;
    //             cout << "Artis  : " << penyanyi[i].nama << endl;
    //             cout << "Judul  : " << penyanyi[i].lagu[j].judul << endl;
    //             cout << "Genre  : " << penyanyi[i].lagu[j].genre << endl;
    //             cout << "Durasi : " << penyanyi[i].lagu[j].durasi << endl;
    //             cout << "Tahun  : " << penyanyi[i].lagu[j].tahun << endl;
    //             ditemukan = true;
    //             return;
    //         }
    //     }
    // }

    // if (!ditemukan) {
    //     cout << "Lagu tidak ditemukan!" << endl;
    // }
}

// Fungsi untuk sorting Bubble Sort
// void sortLagu(bool ascending) {
//     for (int i = 0; i < jumlahPenyanyi; i++) {
//         int jumlahLagu = 0;

//         // Hitung jumlah lagu dalam daftar
//         while (!daftarPenyanyi[i].lagu[jumlahLagu].judul.empty()) {
//             jumlahLagu++;
//         }

//         // Bubble Sort untuk mengurutkan lagu
//         for (int j = 0; j < jumlahLagu - 1; j++) {
//             for (int k = 0; k < jumlahLagu - j - 1; k++) {
//                 if ((ascending && daftarPenyanyi[i].lagu[k].judul > daftarPenyanyi[i].lagu[k + 1].judul) ||
//                     (!ascending && daftarPenyanyi[i].lagu[k].judul < daftarPenyanyi[i].lagu[k + 1].judul)) {
//                     swap(daftarPenyanyi[i].lagu[k], daftarPenyanyi[i].lagu[k + 1]);
//                 }
//             }
//         }
//     }

//     cout << "Lagu berhasil diurutkan!" << endl;
//     cout << "=== Daftar Lagu Setelah Diurutkan ===" << endl;
//     tampilkanLaguRekursif(daftarPenyanyi, jumlahPenyanyi);
// }

bool pilih(fstream &file,fstream &count,Penyanyi &data, int &jumlahPenyanyi){
    int pilihan;
    do
    {
        cout<<"Pilihan : ";
        cin>>pilihan;
        if (pilihan<0||pilihan>5)
        {
            cout<<"Invalid Input"<<endl;
        }    
    } while (pilihan<0||pilihan>5);
    
    switch (pilihan) {
            case 1:
                inputData(file,count,data,jumlahPenyanyi);
                break;
            case 2:
                if (jumlahPenyanyi == 0) {
                    cout << "Belum ada data yang dimasukkan!" << endl;
                } else 
                    file.open("file.txt",ios::in|ios::out|ios::app);  
                    tampilkanLaguRekursif(file,data);
                    file.close();
                break;
            case 3: {
                if (jumlahPenyanyi == 0) {
                    cout << "Belum ada data yang dimasukkan!" << endl;
                    break;
                } else
                {
                string cariJudul;
                cout << "Masukkan judul lagu yang ingin dicari: ";
                getline(cin, cariJudul);
                cariLaguSequential();
                }
                break;
            }
            case 4: {
                if (jumlahPenyanyi == 0) {
                    cout << "Belum ada data yang dimasukkan!" << endl;
                    break;
                }
                char order;
                cout << "Urutkan lagu secara (A-Z: 'a' / Z-A: 'z')? ";
                cin >> order;
                cin.ignore();
                //sortLagu(order == 'a' || order == 'A');
                break;
            }
            case 5:
                cout << "Keluar dari program..." << endl;
                exit(0);
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
    }
}

int hitungJumlahPenyanyi(fstream &count) {
    count.open("count.txt", ios::in|ios::out|ios::app);
    int counter = 0;
   while (!count.eof())
   {
    count>>counter;
   }
    count.close();
    return counter;
}

// Tampilan Menu
bool tampilkanMenu(fstream &file, fstream &count,Penyanyi &data) {
    int pilihan;
    int jumlahPenyanyi = hitungJumlahPenyanyi(count);
    do {
        cout << "\n=== Menu ===" << endl;
        cout << "1. Input Data Penyanyi dan Lagu" << endl;
        cout << "2. Tampilkan Semua Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Urutkan Lagu" << endl;
        cout << "5. Keluar" << endl;
        pilih(file,count,data,jumlahPenyanyi);
        // Konfirmasi apakah ingin kembali ke menu
        char lanjut;
        cout << "\nIngin kembali ke menu utama? (y/n): ";
        cin >> lanjut;
        cin.ignore();
        if (lanjut == 'n' || lanjut == 'N') {
            cout << "Keluar dari program..." << endl;
            return false;
        }
    } while (true);
    return true;
}

int main() {
    fstream file;
    fstream count;
    Penyanyi penyanyi;
    while (tampilkanMenu(file,count,penyanyi));
    return 0;
}

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
    count<<jumlahPenyanyi;//Menulis Jumlah Penyanyi Ke File
    count.close();
}


//Fungsi Menulis Data Penyanyi Ke File
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
    //Input Penyanyi Dan Lagunya
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
            writeData(file,count,data,buffer); //Menulis Data Penyanyi Ke File 
        }
    }
    jumlahPenyanyi += inputPenyanyi;
    writeDataCount(count,jumlahPenyanyi); //Menulis Jumlah Penyanyi Yang Sudah Diinput
}

Penyanyi readData(fstream &file, Penyanyi &data) {
    string temp;
    size_t pos;
    // NO
    if (!getline(file, temp)) return data;
    // NAMA
    if (getline(file, temp)) {
        pos = temp.find(":"); //Cari ":" + 2 untuk mendapatkan data 
        data.nama = (pos != string::npos && pos + 2 <= temp.size()) ? temp.substr(pos + 2) : "";
    }
    // JUDUL
    if (getline(file, temp)) {
        pos = temp.find(":");//Cari ":" + 2 untuk mendapatkan data 
        data.lagu.judul = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 2) : "";
    }
    // GENRE
    if (getline(file, temp)) {
        pos = temp.find(":");//Cari ":" + 2 untuk mendapatkan data 
        data.lagu.genre = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 2) : "";
    }
    // DURASI
    if (getline(file, temp)) {
        pos = temp.find(":");//Cari ":" + 2 untuk mendapatkan data 
        data.lagu.durasi = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 2) : "";
    }
    // TAHUN
    if (getline(file, temp)) {
        pos = temp.find(":");//Cari ":" + 2 untuk mendapatkan data 
        data.lagu.tahun = (pos != string::npos && pos + 1 <= temp.size()) ? temp.substr(pos + 2) : "";
    }
    // ENDLINE
    getline(file, temp);
    return data;
}

// Fungsi rekursif
void tampilkanLaguRekursif(fstream &file,Penyanyi &data) {
    if (!file)
    {
        return;
    }
    data = readData(file, data); //Ambil Data Dari File
    if(file.fail()||file.eof()){
        return;
    }
    //Output Data (Pake Penyanyi data karena sebagai parameter )
    cout<<"====================================="<<endl;
    cout<<"Nama Artis  : "<<data.nama<<endl;
    cout<<"Judul Lagu : "<<data.lagu.judul<<endl;
    cout<<"Genre Lagu : "<<data.lagu.genre<<endl;
    cout<<"Durasi Lagu : "<<data.lagu.durasi<<endl;
    cout<<"Tahun Lagu : "<<data.lagu.tahun<<endl;
    tampilkanLaguRekursif(file,data);
}

// Fungsi sequential search
void cariLaguSequential(fstream &file, Penyanyi &data) {
    string name;
    Penyanyi output;
    cout<<"Pencarian Artis : ";
    cin.ignore();
    getline(cin,name);//Input Indikator
    bool found = false;
    int counter = 0;
    file.open("file.txt",ios::in);
    while (!file.eof())
    {
        output = readData(file,data);//Ambil Data Dari File (Pake Penyanyi output karena lebih optimal)
        if (output.nama==name)
        {
            found = true;
            counter++;//Counter Lagu Artis Yang Dicari
            cout<<"Found :"<<endl;
            cout<<"NAMA ARTIS : "<<output.nama<<endl;//Jika Cuma Sekali Tampil Aja Bisa Pake Counter + If Statement
            cout<<"Judul Lagu Ke-"<<counter<<" : "<<output.lagu.judul<<endl;
            cout<<"Judul Lagu Ke-"<<counter<<" : "<<output.lagu.genre<<endl;
            cout<<"Judul Lagu Ke-"<<counter<<" : "<<output.lagu.durasi<<endl;
            cout<<"Judul Lagu Ke-"<<counter<<" : "<<output.lagu.tahun<<endl;
        } 
    }
    file.close();  
    if (!found)
    {
    cout<<"Not Found"<<endl;
    }
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
                cariLaguSequential(file,data);
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

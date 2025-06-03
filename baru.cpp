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
    count.open("count.txt",ios::out);
    count<<jumlahPenyanyi;//Menulis Jumlah Penyanyi Ke File
    count.close();
}


//Fungsi Menulis Data Penyanyi Ke File
void writeData(fstream &file, fstream &count,Penyanyi &data,int &jumlahPenyanyi){
    file.open("file.txt",ios::in|ios::out|ios::app);  
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
    while (true)
    {
        output = readData(file,data);//Ambil Data Dari File (Pake Penyanyi output karena lebih optimal)
        if (file.eof()||file.fail()||output.nama.empty())
        {
        break;
        }
        if (output.nama==name)
        {
            found = true;
            counter++;//Counter Lagu Artis Yang Dicari
            if (counter == 1)
            {
            cout<<"Found :"<<endl;
            cout<<"NAMA ARTIS : "<<output.nama<<endl;
            }
            cout<<"====================================="<<endl;
            cout<<"Judul Lagu Ke-"<<counter<<" : "<<output.lagu.judul<<endl;
            cout<<"Genre Lagu Ke-"<<counter<<" : "<<output.lagu.genre<<endl;
            cout<<"Durasi Lagu Ke-"<<counter<<" : "<<output.lagu.durasi<<endl;
            cout<<"Tahun Lagu Ke-"<<counter<<" : "<<output.lagu.tahun<<endl;
        } 
    }
    cout<<"====================================="<<endl;
    file.close();
    if (!found)
    {
    cout<<"Not Found"<<endl;
    }
}

int readAllLaguToArray(fstream &file, Penyanyi arr[], int &maxSize) {
    file.open("file.txt", ios::in);
    int count = 0;
    Penyanyi temp;
    while (!file.eof() && count < maxSize) {
        temp = readData(file, temp);
        if (file.fail() || temp.nama.empty()) break;
        arr[count++] = temp;
    }
    file.close();
    return count; // jumlah lagu yang berhasil dibaca
}

void bubbleSortLaguArtis(Penyanyi arr[], int &n, bool &ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ascending) {
                if (arr[j].nama > arr[j + 1].nama) {
                    // tukar posisi
                    Penyanyi temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            } else if (arr[j].nama < arr[j + 1].nama) {
                    // tukar posisi
                    Penyanyi temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            
        }
    }
}

void bubbleSortLaguJudul(Penyanyi arr[], int &n, bool &ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ascending) {
                if (arr[j].lagu.judul > arr[j + 1].lagu.judul) {
                    // tukar posisi
                    Penyanyi temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            } else if (arr[j].lagu.judul < arr[j + 1].lagu.judul) {
                    // tukar posisi
                    Penyanyi temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            
        }
    }
}


void tampilkanSortedLagu(Penyanyi arr[], int n) {
    cout << "\n=== Daftar Lagu Setelah Diurutkan ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Nama Artis  : " << arr[i].nama << endl;
        cout << "Judul Lagu  : " << arr[i].lagu.judul << endl;
        cout << "Genre Lagu  : " << arr[i].lagu.genre << endl;
        cout << "Durasi Lagu : " << arr[i].lagu.durasi << endl;
        cout << "Tahun Lagu  : " << arr[i].lagu.tahun << endl;
        cout << "-----------------------------" << endl;
    }
}

void hapusDataArtis(fstream &file, fstream &count, int &jumlahPenyanyi) {
    string namaTarget;
    fstream temp;
    cout << "Masukkan nama artis yang ingin dihapus: ";
    cin.ignore();
    getline(cin, namaTarget);
    file.open("file.txt",ios::in);
    temp.open("temp.txt",ios::out|ios::app);
    string line;
    bool skip = false;
    bool deleted = false;
    while (getline(file, line)) {
        // Deteksi baris nama
        if (line.find("NAMA : ") != string::npos) {
            string nama = line.substr(line.find(":") + 2);
            if (nama == namaTarget) {
                skip = true; // Mulai lewati 6 baris (judul, genre, durasi, tahun, newline)
                deleted = true;
            } else {
                skip = false;
            }
        }

        if (!skip) {
            temp << line << endl;
        }
        // Deteksi akhir 1 blok artis (baris kosong)
        if (line.empty()) {
            skip = false;
        }
    }
    file.close();
    temp.close();
    // Ganti file lama dengan file baru
    remove("file.txt");
    rename("temp.txt", "file.txt");

    //Simpan Data Jumlah Penyanyi
    jumlahPenyanyi -= 1;
    writeDataCount(count, jumlahPenyanyi);
    if (deleted) {
        cout << "Data artis \"" << namaTarget << "\" berhasil dihapus." << endl;
    } else {
        cout << "Data artis \"" << namaTarget << "\" tidak ditemukan." << endl;
    }
}


void menuHapus(fstream &file, fstream &count, int &jumlahPenyanyi){
    int pilihan;
    cout<<"Hapus Data"<<endl;
    cout<<"1. Hapus Artis "<<endl;
    cout<<"2. Hapus Lagu "<<endl;
    cout<<"Masukkan Plihan : ";
    cin>>pilihan;
    if (pilihan==1)
    {
        
        hapusDataArtis(file,count,jumlahPenyanyi); 
    }
    else {

    }
    
}

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
    } while (pilihan<0||pilihan>6);
    
    switch (pilihan) {
            case 1:
                inputData(file,count,data,jumlahPenyanyi);
                break;
            case 2:
                if (jumlahPenyanyi == 0) {
                    cout << "Belum ada data yang dimasukkan!" << endl;
                } else {
                    file.open("file.txt",ios::in);  
                    tampilkanLaguRekursif(file,data);
                    cout<<"====================================="<<endl;
                    file.close();
                }
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
                bool asc = false;
                string order;
                int MAX_LAGU = 100;
                Penyanyi semuaLagu[MAX_LAGU];
                int jumlahLagu = readAllLaguToArray(file, semuaLagu, MAX_LAGU);
                int pilihSort;
                cout<<"Urutkan Berdasarkan : "<<endl;
                cout<<"1. Artis"<<endl;
                cout<<"2. Lagu"<<endl;
                do
                {
                    cout<<"Pilihan : ";
                    cin>>pilihSort;
                    if (pilihSort < 1 || pilihSort > 2)
                    {
                        cout<<"Invalid Input"<<endl;
                    } 
                } while (pilihSort < 1 || pilihSort > 2);
                cin.ignore();
                cout << "Urutkan lagu berdasarkan judul secara (Asc: a || Desc = z)? :";
                do{
                cin >> order;
                    if (order!="a"&&order!="A"&&order!="Z"&&order!="z"){
                        cout<<"Invalid Input..."<<endl;
                    }
                } while (order!="a"&&order!="A"&&order!="Z"&&order!="z");
                if (order == "a" || order == "A")
                {
                  asc = true;  
                } 
                cin.ignore();
                if (pilihSort == 1)
                {
                    bubbleSortLaguArtis(semuaLagu, jumlahLagu, asc);
                }
                else {
                    bubbleSortLaguJudul(semuaLagu, jumlahLagu, asc);
                }
                
                tampilkanSortedLagu(semuaLagu, jumlahLagu);
                break;
            }
            case 5:

                menuHapus(file,count,jumlahPenyanyi);
                break;
            case 6:
                cout << "Keluar dari program..." << endl;
                exit(0);
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
    }
}

int hitungJumlahPenyanyi(fstream &count) {
    count.open("count.txt", ios::in);
    int counter = 0;
    if (count.is_open()) {
        count >> counter;
        count.close();
    }
    return counter;
}


// Tampilan Menu
bool tampilkanMenu(fstream &file, fstream &count,Penyanyi &data) {
    int pilihan;
    int jumlahPenyanyi = hitungJumlahPenyanyi(count);
    do {
        system("cls");
        cout << "\n=========== Menu ===========" << endl;
        cout << "1. Input Data Penyanyi dan Lagu" << endl;
        cout << "2. Tampilkan Semua Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Urutkan Lagu" << endl;
        cout << "5. Hapus Data" << endl;
        cout << "6. Keluar" << endl;
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
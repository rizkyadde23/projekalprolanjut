#include <iostream>
using namespace std;


struct Lagu{
    string judul;
    string tahun;
    string genre;
}song[2];

struct penyanyi{
    string nama;
    double penggemar;
    Lagu song;
}artis[2];

int main(){
    artis[0].nama = "Billie Eilish";
    artis[0].penggemar = 106.5;
    artis[0].song[0].judul = "Birds Of A Feather";
    song[0].tahun = "2024";
    song[0].genre = "Pop";
    song[1].judul = "Wildfower";
    song[1].tahun = "2024";
    song[1].genre = "Pop";

    artis[1].nama = "Kendrick Lamar";
    artis[1].penggemar = 88.9;
    song[0].judul = "Not Like Us";
    song[0].tahun = "2024";
    song[0].genre = "Rap";
    song[1].judul = "Humble";
    song[1].tahun = "2017";
    song[1].genre = "Rap";

    cout<<artis[0].nama<<endl;
    cout<<artis[0].penggemar<<endl;
    cout<<song[0].judul<<endl;
    cout<<song[0].tahun<<endl;
    cout<<song[0].genre<<endl;
    cout<<song[1].judul<<endl;
    cout<<song[1].tahun<<endl;
    cout<<song[1].genre<<endl;

    cout<<artis[1].nama<<endl;
    cout<<artis[1].penggemar<<endl;
    cout<<song[0].judul<<endl;
    cout<<song[0].tahun<<endl;
    cout<<song[0].genre<<endl;
    cout<<song[1].judul<<endl;
    cout<<song[1].tahun<<endl;
    cout<<song[1].genre<<endl;
   

    

}
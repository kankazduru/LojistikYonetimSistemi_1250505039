#ifndef SEHIRGRAFI_H
#define SEHIRGRAFI_H
#include <stdbool.h>

typedef struct KomsuDugum {
    int sehirIndeks;
    int mesafe;
    struct KomsuDugum* sonraki;
} KomsuDugum;

typedef struct {
    char sehirAdi[50];
    KomsuDugum* komsular;
} Sehir;

typedef struct {
    int toplamSehirSayisi;
    Sehir* sehirListesi;
    bool* ziyaretEdildi;
} Graf;

Graf* grafOlustur(int kapasite);
void sehirEkle(Graf* graf, char* ad);
void yolEkle(Graf* graf, int kaynak, int hedef, int mesafe);
void dfsGezinme(Graf* graf, int baslangicIndeksi);
void grafBellekRaporu(Graf* graf);
void grafiTemizle(Graf* graf);

#endif

#ifndef LOJISTIKYONETICI_H
#define LOJISTIKYONETICI_H

#include "SehirGrafi.h"
#include "PaketHash.h"


typedef struct {
    Graf* sehirSistemi;      
    HashTablosu* paketSistemi;
    char firmaAdi[50];
} LojistikYonetici;


LojistikYonetici* sistemBaslat(char* firma, int sehirKapasitesi);

void sistemePaketVeSehirEkle(LojistikYonetici* yonetici, char* paketID, char* sehirAdi);

void lojistikAgiTaramasi(LojistikYonetici* yonetici, int baslangicIndeksi);

void genelBellekRaporu(LojistikYonetici* yonetici);

void sistemiKapat(LojistikYonetici* yonetici);

#endif

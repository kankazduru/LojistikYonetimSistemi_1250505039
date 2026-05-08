#ifndef PAKETHASH_H
#define PAKETHASH_H
#include <stdio.h>
#define TABLO_BOYUTU 10


typedef struct PaketDugumu {
    char paketID[20];          
    char gonderici[50];         
    char alici[50];            
    struct PaketDugumu* sonraki; 
} PaketDugumu;


typedef struct {
    PaketDugumu* dizin[TABLO_BOYUTU];
} HashTablosu;


HashTablosu* hashTablosuOlustur();

int hashFonksiyonuTipB(char* anahtar);

void paketEkle(HashTablosu* tablo, char* id, char* gonderici, char* alici);

PaketDugumu* paketAra(HashTablosu* tablo, char* id);

void hashBellekRaporu(HashTablosu* tablo);

void tabloyuTemizle(HashTablosu* tablo);

#endif

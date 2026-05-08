#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PaketHash.h"

// Hash tablosunu bellekte baslatir
HashTablosu* hashTablosuOlustur() {
    int i; // Degiskeni dongu disinda tanimladik
    HashTablosu* tablo = (HashTablosu*)malloc(sizeof(HashTablosu));
    for (i = 0; i < TABLO_BOYUTU; i++) {
        tablo->dizin[i] = NULL; 
    }
    return tablo;
}

/**
 * NUMARANA OZEL: Tip B Hash Fonksiyonu
 * Son rakam (9) tek oldugu icin: ASCII toplami.
 */
int hashFonksiyonuTipB(char* anahtar) {
    int i; // Degiskeni dongu disinda tanimladik
    int toplam = 0;
    for (i = 0; anahtar[i] != '\0'; i++) {
        toplam += anahtar[i]; 
    }
    return toplam % TABLO_BOYUTU; 
}

/**
 * NUMARANA OZEL: Zincirleme (Chaining) ile Ekleme
 */
void paketEkle(HashTablosu* tablo, char* id, char* gonderici, char* alici) {
    int indeks = hashFonksiyonuTipB(id);
    
    PaketDugumu* yeniPaket = (PaketDugumu*)malloc(sizeof(PaketDugumu));
    strcpy(yeniPaket->paketID, id);
    strcpy(yeniPaket->gonderici, gonderici);
    strcpy(yeniPaket->alici, alici);
    
    // Zincirleme mantigi
    yeniPaket->sonraki = tablo->dizin[indeks];
    tablo->dizin[indeks] = yeniPaket;
    
    printf("Paket %s, Indeks %d konumuna eklendi (Adres: %p)\n", id, indeks, (void*)yeniPaket);
}

// Paket arama fonksiyonu
PaketDugumu* paketAra(HashTablosu* tablo, char* id) {
    int indeks = hashFonksiyonuTipB(id);
    PaketDugumu* temp = tablo->dizin[indeks];
    
    while (temp != NULL) {
        if (strcmp(temp->paketID, id) == 0) {
            return temp; 
        }
        temp = temp->sonraki; 
    }
    return NULL; 
}

/**
 * BELLEK IZLEME RAPORU FONKSIYONU
 */
void hashBellekRaporu(HashTablosu* tablo) {
    int i; // Degiskeni dongu disinda tanimladik
    printf("\n--- HASH TABLOSU BELLEK VE ZINCIRLEME RAPORU ---\n");
    for (i = 0; i < TABLO_BOYUTU; i++) {
        printf("Indeks [%d] (%p): ", i, (void*)&tablo->dizin[i]);
        PaketDugumu* temp = tablo->dizin[i];
        
        if (temp == NULL) {
            printf("BOS\n");
        } else {
            while (temp != NULL) {
                printf("[ID: %s | Adres: %p | Next: %p] -> ", 
                       temp->paketID, (void*)temp, (void*)temp->sonraki);
                temp = temp->sonraki;
            }
            printf("NULL\n");
        }
    }
}

// Bellek temizleme
void tabloyuTemizle(HashTablosu* tablo) {
    int i; // Degiskeni dongu disinda tanimladik
    for (i = 0; i < TABLO_BOYUTU; i++) {
        PaketDugumu* temp = tablo->dizin[i];
        while (temp != NULL) {
            PaketDugumu* silinecek = temp;
            temp = temp->sonraki;
            free(silinecek);
        }
    }
    free(tablo);
}

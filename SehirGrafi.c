#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SehirGrafi.h"

Graf* grafOlustur(int kapasite) {
    int i;
    Graf* graf = (Graf*)malloc(sizeof(Graf));
    graf->toplamSehirSayisi = kapasite;
    graf->sehirListesi = (Sehir*)malloc(kapasite * sizeof(Sehir));
    graf->ziyaretEdildi = (bool*)malloc(kapasite * sizeof(bool));
    
    for (i = 0; i < kapasite; i++) {
        graf->sehirListesi[i].komsular = NULL;
        strcpy(graf->sehirListesi[i].sehirAdi, "Bos");
        graf->ziyaretEdildi[i] = false;
    }
    return graf;
}

void sehirEkle(Graf* graf, char* ad) {
    static int mevcutSehirSayisi = 0;
    if (mevcutSehirSayisi < graf->toplamSehirSayisi) {
        strcpy(graf->sehirListesi[mevcutSehirSayisi].sehirAdi, ad);
        mevcutSehirSayisi++;
    }
}

void yolEkle(Graf* graf, int kaynak, int hedef, int mesafe) {
    KomsuDugum* yeniDugum = (KomsuDugum*)malloc(sizeof(KomsuDugum));
    yeniDugum->sehirIndeks = hedef;
    yeniDugum->mesafe = mesafe;
    yeniDugum->sonraki = graf->sehirListesi[kaynak].komsular;
    graf->sehirListesi[kaynak].komsular = yeniDugum;
}

void dfsGezinme(Graf* graf, int baslangicIndeksi) {
    KomsuDugum* temp;
    graf->ziyaretEdildi[baslangicIndeksi] = true;
    printf("Ziyaret edilen: %s\n", graf->sehirListesi[baslangicIndeksi].sehirAdi);

    temp = graf->sehirListesi[baslangicIndeksi].komsular;
    while (temp != NULL) {
        if (!graf->ziyaretEdildi[temp->sehirIndeks]) {
            dfsGezinme(graf, temp->sehirIndeks);
        }
        temp = temp->sonraki;
    }
}

void grafBellekRaporu(Graf* graf) {
    int i;
    for (i = 0; i < graf->toplamSehirSayisi; i++) {
        printf("Sehir: %s [%p]\n", graf->sehirListesi[i].sehirAdi, (void*)&graf->sehirListesi[i]);
    }
}

void grafiTemizle(Graf* graf) {
    int i;
    for (i = 0; i < graf->toplamSehirSayisi; i++) {
        KomsuDugum* temp = graf->sehirListesi[i].komsular;
        while (temp != NULL) {
            KomsuDugum* sil = temp;
            temp = temp->sonraki;
            free(sil);
        }
    }
    free(graf->sehirListesi);
    free(graf->ziyaretEdildi);
    free(graf);
}

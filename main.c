#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SehirGrafi.h"
#include "PaketHash.h"
#include "LojistikYonetici.h"

void menuGoster() {
    printf("\n--- LOJISTIK YONETIM SISTEMI ---\n");
    printf("1. Yeni Sehir Ekle\n");
    printf("2. Sehirler Arasi Yol Tanýmla\n");
    printf("3. Yeni Paket Kaydet\n");
    printf("4. Paket Sorgula (Hash Table)\n");
    printf("5. Rota Gezginini Calistir (DFS)\n");
    printf("6. Bellek Izleme Raporu Goster\n");
    printf("0. Cikis\n");
    printf("Seciminiz: ");
}

int main() {
    int secim = -1;
    char sehirAdi[50];
    char paketID[20];
    int kaynak, hedef, mesafe;
    
    // HATA COZUMU: Buraya kapasite bilgisi (10) eklendi
    Graf* sehirGrafi = grafOlustur(10); 
    HashTablosu* paketTablosu = hashTablosuOlustur();

    while (secim != 0) {
        menuGoster();
        if (scanf("%d", &secim) != 1) {
            printf("Gecersiz giris!\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch (secim) {
            case 1:
                printf("Eklenecek sehir adini giriniz: ");
                scanf("%s", sehirAdi);
                // HATA COZUMU: sehirAdi parametre olarak eklendi
                sehirEkle(sehirGrafi, sehirAdi); 
                break;
            case 2:
                printf("Kaynak sehir indeksi, Hedef sehir indeksi ve Mesafe giriniz: ");
                scanf("%d %d %d", &kaynak, &hedef, &mesafe);
                yolEkle(sehirGrafi, kaynak, hedef, mesafe);
                break;
            case 3:
                printf("Paket ID, Gonderici ve Alici giriniz: ");
                char gonderici[50], alici[50];
                scanf("%s %s %s", paketID, gonderici, alici);
                paketEkle(paketTablosu, paketID, gonderici, alici);
                break;
            case 4:
                printf("Sorgulanacak Paket ID giriniz: ");
                scanf("%s", paketID);
                paketAra(paketTablosu, paketID);
                break;
            case 5:
                printf("DFS baslangic sehir indeksini giriniz: ");
                int baslangic;
                scanf("%d", &baslangic);
                dfsGezinme(sehirGrafi, baslangic);
                break;
            case 6:
                grafBellekRaporu(sehirGrafi);
                hashBellekRaporu(paketTablosu);
                break;
            case 0:
                printf("Sistemden cikiliyor...\n");
                break;
            default:
                printf("Lutfen 0-6 arasinda bir secim yapiniz.\n");
        }
    }

    grafiTemizle(sehirGrafi);
    tabloyuTemizle(paketTablosu);

    return 0;
}

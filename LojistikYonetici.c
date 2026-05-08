#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LojistikYonetici.h"

// Hibrit sistemi bellekte ilklendirir
LojistikYonetici* sistemBaslat(char* firma, int sehirKapasitesi) {
    LojistikYonetici* yonetici = (LojistikYonetici*)malloc(sizeof(LojistikYonetici));
    strcpy(yonetici->firmaAdi, firma);
    
    // Alt sistemleri oluþtur
    yonetici->sehirSistemi = grafOlustur(sehirKapasitesi); 
    yonetici->paketSistemi = hashTablosuOlustur();         
    
    printf("%s Lojistik Hibrit Sistemi Baslatildi.\n", firma);
    return yonetici;
}

// Hibrit iþlem: Paketi sisteme ekler ve þehirle iliþkilendirir
void sistemePaketVeSehirEkle(LojistikYonetici* yonetici, char* paketID, char* sehirAdi) {
    // Paketi Hash Tablosuna ekle
    paketEkle(yonetici->paketSistemi, paketID, "Gonderici Bilgisi", sehirAdi);
    
    // Þehri graf üzerine ekle
    sehirEkle(yonetici->sehirSistemi, sehirAdi);
    
    printf("Hibrit Kayit Tamamlandi: Paket %s -> Sehir %s\n", paketID, sehirAdi);
}

// NUMARANA OZEL: DFS Taramasý
void lojistikAgiTaramasi(LojistikYonetici* yonetici, int baslangicIndeksi) {
    int i; // HATA COZUMU: i degiskeni dongu disinda tanimlandi
    printf("\n--- %s Lojistik Agi DFS Taramasi Baslatiliyor ---\n", yonetici->firmaAdi);
    
    // Ziyaret dizisini sýfýrla
    for(i = 0; i < yonetici->sehirSistemi->toplamSehirSayisi; i++) {
        yonetici->sehirSistemi->ziyaretEdildi[i] = false;
    }
    
    // SehirGrafi.c içindeki DFS'i çaðýrýr
    dfsGezinme(yonetici->sehirSistemi, baslangicIndeksi);
}

/**
 * ÖDEV GEREKLÝLÝÐÝ: Bellek Ýzleme Raporu
 * En az 5 veri giriþinden sonra bu fonksiyonu çaðýrarak 
 * teknik tabloyu oluþturabilirsin.
 */
void genelBellekRaporu(LojistikYonetici* yonetici) {
    printf("\n======================================================\n");
    printf("        TEKNIK BELLEK IZLEME VE ADRES RAPORU          \n");
    printf("======================================================\n");
    
    // Graf adreslerini ve komþuluk pointerlarýný dök
    grafBellekRaporu(yonetici->sehirSistemi);
    
    // Hash tablosu adreslerini ve zincirleme baðlantýlarýný dök
    hashBellekRaporu(yonetici->paketSistemi);
    
    printf("\n======================================================\n");
}

// Sistemi kapat ve tüm malloc'larý temizle
void sistemiKapat(LojistikYonetici* yonetici) {
    grafiTemizle(yonetici->sehirSistemi);
    tabloyuTemizle(yonetici->paketSistemi);
    free(yonetici);
    printf("Sistem kapatildi ve bellek temizlendi.\n");
}

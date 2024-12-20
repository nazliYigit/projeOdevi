#include <stdio.h>
#include <string.h>
//kodun tamamında kullanmak için sabitleri belirtiyoruz.
#define TOP_OYUNCU 20
#define KAR_UZUN 30

//dizileri tanımlıyoruz.
char adlar[TOP_OYUNCU][KAR_UZUN];
char soyadlar[TOP_OYUNCU][KAR_UZUN];
int macSay[TOP_OYUNCU];
int topİsPas[TOP_OYUNCU];
int topHatPas[TOP_OYUNCU];

//oku fonksiyonu için gerekli parametreleri tanımlama
void oku(char adlar[][KAR_UZUN],char soyadlar[][KAR_UZUN],int macSay[],
          int topHatPas[],int topİsPas[],int *oyuncuSay,
          char ad[],char soyAd[],int hataPas,int isPas ) {

    //girilen veri satırı kadar döngü devam eder.

    for (int i = 0; i < *oyuncuSay; i++) {
        //Koşulla oyuncunun dosyada varlığı kontrol edilir .

        //Oyuncu varsa oyuncunun verilerini yeni girilen verilerle güncelliyoruz.
        if (strcmp(soyadlar[i],soyAd)==0 && strcmp(adlar[i],ad)==0) {
            macSay[i]++;
            topHatPas[i]+=hataPas;
            topİsPas[i]+=isPas;
            return;
        }
    }

    //Girilen oyuncu yeniyse diziye yeni oyuncu verilerini ekliyoruz.
    strcpy(adlar[*oyuncuSay],ad);
    strcpy(soyadlar[*oyuncuSay],soyAd);
    topHatPas[*oyuncuSay]=hataPas;
    topİsPas[*oyuncuSay]=isPas;
    macSay[*oyuncuSay]=1;
    *oyuncuSay=*oyuncuSay+1;
}

//Oyuncu verilerini başka bir dosyada toparlayacak olan fonksiyonu ve gerekli olan parametreleri tanımlıyoruz.
void yaz(char adlar[][KAR_UZUN],char soyadlar[][KAR_UZUN],int macSay[],int topHatPas[],int topİsPas[],int oyunSay) {

    // Toplam verileri kayıt edecek olan dosyayı açıyoruz.
    FILE *dos= fopen("toplam.txt","w");

    //Dosyanın açılma durumunu kontrol ediyoruz.
    if (dos==NULL) {
        printf("Hata dosya olusturulamadi\n");
        return;
    }

    //Dosyadaki farklı oyuncu sayısı kadar döngüyü çalıştırıp açılan dosyaya verileri kaydediyoruz.
    for (int i=0;i<oyunSay;i++) {
        fprintf(dos,"%s  %s  %d %d %d\n",adlar[i],soyadlar[i],macSay[i],topİsPas[i],topHatPas[i]);
    }

    //Doyayı kapatıp program çıktısını veren kod
    fclose(dos);

    printf("Guncel veriler toplam.txt dosyasina yazdirildi\n");

}

//Ana fonksiyonda başta gerekli olan değişkenler tanımlanıyor.
int main() {
    int oyuncuSay=0;
    char ad[50],soyAd[50];
    int hatalıPas,isPas;

    // Hazır dosya okunmak için açılır.
    FILE *dos = fopen("paslar.txt", "r");

    //Dosyanın açılma durumunu kontrol eder.
    if (dos == NULL) {
        printf("paslar.txt dosyasi acilamadi.\n");
        return 1;
    }

    //Dosyadaki verilerin gerekli şartlara uygunluğunu kontrol eder.
    while (fscanf(dos," %s %s %d %d ",ad,soyAd,&hatalıPas,&isPas )==4) {

        //Şartlara uyuyorsa her satırda döngü tekrarlanır ve gerekli fonksiyona girer.
        oku(adlar,soyadlar,macSay,topHatPas,topİsPas,&oyuncuSay,ad,soyAd,hatalıPas,isPas);
    }

    //Dosyayı kapatır.
    fclose(dos);

    //Girilen oyuncu sayısı kontrol edilir.
    if (oyuncuSay > TOP_OYUNCU) {
        printf("Maksimum oyuncu sayisina ulasildi (%d).\n", TOP_OYUNCU);
        return 0;
    }

    //Yeni dosyayı açan fonksiyona yönlendirilir.
    yaz(adlar,soyadlar,macSay,topİsPas,topHatPas,oyuncuSay);

    return 0;

}

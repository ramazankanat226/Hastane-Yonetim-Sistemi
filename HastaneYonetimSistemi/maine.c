#include "stdio.h"          //Giriş çıkış işlemlerini sağlar.
#include "stdlib.h"         //Rastgele sayi üretmeye yarar.
#include "string.h"       //Stringlerde işlem yapmamizi sağlar.
#include "time.h"         //Rastgele sayi üretmeye yarar.
#include "unistd.h"     //usleep fonksiyonunu kullanmamızı sağlar.

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

void yavasYazma();
void hastaKayitEkle();
void yedekle();
void sil(int);
void guncelle(int);
void hastaKayitSil();
void hastaKayitGuncelle();
void hastaKayitGoruntule();
void hastaKayitlariniListele();
int menu();

int main(){
    int secim = menu();
    while (secim != 0){
        switch (secim) {
            case 1:
                hastaKayitEkle();
                break;
            case 2:
                hastaKayitSil();
                break;
            case 3:
                hastaKayitGuncelle();
                break;
            case 4:
                hastaKayitGoruntule();
                break;
            case 5:
                hastaKayitlariniListele();
                break;
            default:

                system("COLOR 0");
                printf("%sYanlis secim yaptiniz!%s\n",RED,RESET);
                usleep(1000000);
                yavasYazma("Ana menuye donuluyor...");
                break;
        }
        secim = menu();
    }

    return 0;
}


FILE *dosya ;
FILE *gecici; //dosya silmek için oluşturuldu.

struct hasta{
    char ad[20],soyad[20],cinsiyet[20],hastalik[20],kanGrubu[20],alerjiler[20];
    int yas,ID;
};

struct hasta h1 ;

// Metni yavaşça yazdırmak için fonksiyon.
void yavasYazma(char metin[]) {
    int i;
    // Metindeki her karakteri yazdırmak için döngü
    for (i = 0; metin[i] != '\0'; i++) {
        system("COLOR 0"); // Terminal rengini ayarlar
        printf("%s%c%s", YELLOW, metin[i], RESET); // Karakteri sarı renkte yazdırır
        usleep(100000); // Mikrosaniye cinsinden bekleme süresi (100000 mikrosaniye = 0.1 saniye)
    }
    usleep(100000); // Ana menü gelmeden biraz daha bekler
}

// Menü arayüzünü yazdırır.
int menu(){
    int secim;
    printf("\n\n                    ------------------------------------\n");
    printf("                    |      HASTANE YONETIM SISTEMI     |\n ");
    printf("                   |                                  | \n");
    printf("                    | 1-Hasta Kayit Ekleme             |\n ");
    printf("                   | 2-Hasta Kayit Silme              |\n ");
    printf("                   | 3-Hasta Kayit Guncelleme         |\n ");
    printf("                   | 4-Hasta Kayit Goruntuleme        |\n ");
    printf("                   | 5-Hasta Kayitlarini Listele      |\n ");
    printf("                   | 0-Cikis                          |\n ");
    printf("                   ------------------------------------\n");
    printf("\nSeciminiz:");
    scanf("%d",&secim);
    return secim;
}

// Hasta ID'si oluşturan fonksiyon.
int idOlusturucu() {
    char satir[100];
    int sayi;
    // "hastalar.txt" dosyasını okuma modunda açar
    if ((dosya = fopen("hastalar.txt", "r")) != NULL) {
        srand(time(NULL)); // Rastgele sayı üretmek için rastgele başlangıç noktası belirler
        sayi = rand() % 90000 + 10000; // 10000 ile 99999 arasında rastgele bir sayı oluşturur

        // Dosyadaki her satırı okur
        while (fgets(satir, sizeof(satir), dosya) != NULL) {
            sscanf(satir, "%d", &h1.ID); // Satırdan ID'yi alır
            // Oluşturulan rastgele sayı, mevcut ID'lerden biriyle çakışırsa
            if (sayi == h1.ID) {
                fclose(dosya); // Dosyayı kapatır
                return idOlusturucu(); // Yeniden ID oluşturmak için fonksiyonu çağırır
            }
        }
        fclose(dosya);
        return sayi; // ID oluşturur ve döndürür
    }
    return 0; // Dosya açılamazsa veya boşsa 0 döndürür
}

// Yeni bir hasta kaydı oluşturan fonksiyon.
void hastaKayitEkle(){
    dosya = fopen("hastalar.txt","a");
    fclose(dosya);
    short kntrl1 =0,kntrl2=0,kntrl3=0; //Hasta bilgilerini kullanıcıdan alma.
    printf ("\nKayit yapilacak hastanin bilgilerini giriniz:\n");

    // Hasta adını alır.
    printf("Ad       :"); getchar(); //Önceki scanfden kalan yeni satır karakterini yok eder.
    fgets(h1.ad,sizeof(h1.ad),stdin);   // Kullanıcıdan boşluklu veri almasını sağlar.
    h1.ad[strlen(h1.ad)-1]= '\0';  // Satır sonundaki '\n' karakterini kaldırır.

    // Hasta soyadını alır.
    printf("Soyad    :");
    fgets(h1.soyad,sizeof(h1.soyad),stdin);
    h1.soyad[strlen(h1.soyad)-1]= '\0';

    // Hasta yaşını alır (doğru bir yaş girilene kadar).
    while(kntrl1==0){
        printf("Yas      :");	scanf(" %d",&h1.yas);
        if(h1.yas >=0){
            kntrl1=1;// Doğru bir yaş girildi, döngüden çıkar
        }
        else{
            system("COLOR 0");
            printf("%sLutfen yasinizi dogru giriniz!%s\n",RED,RESET);
            usleep(2000000);// Hata mesajını belirli bir süre gösterir.

        }
    }

    // Hasta cinsiyetini alır (doğru bir cinsiyet girilene kadar).
    while(kntrl2==0){
        printf("Cinsiyet :");	scanf(" %s",h1.cinsiyet);
        if(strcmpi(h1.cinsiyet,"kadin")==0|| strcmpi(h1.cinsiyet,"erkek")==0){
            kntrl2=1;// Doğru bir cinsiyet girildi, döngüden çıkar.
        }
        else{
            system("COLOR 0");
            printf("%sLutfen cinsiyet olarak erkek ya da kadin giriniz!%s\n",RED,RESET);
            usleep(1000000);// Hata mesajını belirli bir süre gösterir.
        }
    }
    // Hastanın hastalık bilgisini alır.
    printf("Hastalik :"); getchar();// Önceki scanf'ten kalan yeni satır karakterini tüketir.
    fgets(h1.hastalik,sizeof(h1.hastalik),stdin);
    h1.hastalik[strlen(h1.hastalik)-1]= '\0';// Satır sonundaki '\n' karakterini kaldırır

    // Hasta alerji bilgisini alır.
    printf("Alerjiler:");
    fgets(h1.alerjiler,sizeof(h1.alerjiler),stdin);
    h1.alerjiler[strlen(h1.alerjiler)-1]= '\0';// Satır sonundaki '\n' karakterini kaldırır

    while(kntrl3==0){
        printf("Kan Grubu:");	scanf(" %s",h1.kanGrubu);
        strupr(h1.kanGrubu);// Girilen kan grubunu büyük harfe dönüştürür.
        // Doğru bir kan grubu girildi mi kontrol eder
        if(strcmpi(h1.kanGrubu,"ABRH+")==0|| strcmpi(h1.kanGrubu,"ABRH-")==0 || strcmpi(h1.kanGrubu,"ARH-")==0 || strcmpi(h1.kanGrubu,"ARH+")==0 || strcmpi(h1.kanGrubu,"BRH+")==0 || strcmpi(h1.kanGrubu,"BRH-")==0|| strcmpi(h1.kanGrubu,"0RH+")==0 || strcmpi(h1.kanGrubu,"0RH-")==0){
            kntrl3=1;// Doğru bir kan grubu girildi, döngüden çıkar.

        }
        else{
            system("COLOR 0");
            printf("%sLutfen kan grubu olarak \"ABRH+,ABRH-,ARH+,ARH-,BRH+,BRH-,0RH+,0RH-\" bunlardan birini giriniz!%s\n",RED,RESET);
            usleep(2000000);// Hata mesajını belirli bir süre gösterir.
        }
    }

    // Yeni oluşturulan hasta ID'sini alır.
    h1.ID=idOlusturucu();

    // Hasta bilgilerini dosyaya ekler.
    if ((dosya=fopen("hastalar.txt","a"))!=NULL  )
    {
        fprintf(dosya,"%-8d %-15s %-15s %-8d %-12s %-20s %-23s %-12s\n",h1.ID,h1.ad,h1.soyad,h1.yas,h1.cinsiyet,h1.hastalik,h1.alerjiler,h1.kanGrubu);
    }

    // Bilgi mesajlarını ekrana yazdırır.
    system("COLOR 0");
    yavasYazma("Hasta kaydi yapiliyor...");
    printf("\n%sHasta kayit islemi basarili.%s\n",GREEN,RESET);
    usleep(200000); // Mesajın belirli bir süre gösterilmesi için bekler.
    printf("%sHasta ID:%d%s\n",BLUE,h1.ID,RESET);
    usleep(1000000); // Mesajın belirli bir süre gösterilmesi için bekler.
    yavasYazma("Ana menuye donuluyor...");
    fclose(dosya);
}

// Hasta kayıtlarının yedeklenmesini sağlayan fonksiyon.
void yedekle() {
    char satir[200];

    // "yedekKayit.txt" adında bir yedek dosya oluşturma işlemi.
    if ((gecici = fopen("yedekKayit.txt", "w")) != NULL) {
        // Ana hasta kayıtları dosyasını okumak için açma işlemi.
        if ((dosya = fopen("hastalar.txt", "r")) != NULL) {
            // Her satırı ana dosyadan yedek dosyaya kopyalama işlemi.
            while (fgets(satir, sizeof(satir), dosya)) {
                fprintf(gecici, "%s", satir); // Satırları sırayla yedek dosyaya yazar.
            }
            fclose(dosya); // Ana dosyayı kapatma.
        }
        fclose(gecici); // Yedek dosyayı kapatma.
    }

    // Yedek oluşturulduktan sonra orijinal hasta kayıtları dosyasını silme işlemi.
    remove("hastalar.txt");
}

// Hasta kaydının silinmesini sağlayan fonksiyon.
void sil(int id){
    char satir[200];
    // "hastalar.txt" dosyasını yazma modunda aç
    if ((dosya=fopen("hastalar.txt","w"))!=NULL  ){
        // "yedekKayit.txt" dosyasını okuma modunda aç
        if ((gecici=fopen("yedekKayit.txt","r"))!=NULL  ){
            // "gecici" dosyasından satır satır oku
            while (fgets(satir, sizeof(satir), gecici)){
                sscanf(satir, "%d", &h1.ID); // Satırın başındaki kimlik numarasını al
                // Eğer okunan kimlik numarası, silinmek istenen kimlik numarasına eşit değilse
                if(h1.ID==id)
                    continue; // Bu satırı yazma, diğer satırlara geç
                // Eğer okunan kimlik numarası, silinmek istenen kimlik numarasına eşit değilse, bu satırı "dosya" dosyasına yaz
                fprintf(dosya, "%s",satir);
            }
        }
    }
    remove("yedekKayit.txt"); // "yedekKayit.txt" dosyasını kaldır
    fclose(gecici); // "gecici" dosyasını kapat
    fclose(dosya); // "dosya" dosyasını kapat
}

// Silinecek hastayı seçen fonksiyon.
void hastaKayitSil(){
    int sonuc = 0, id;
    char satir[200];

    // Kullanıcıdan silmek istediği hasta ID'sini al
    printf("Silmek istediginiz hasta ID'si: ");
    scanf("%d", &id);

    // "hastalar.txt" dosyasını okuma modunda aç
    if ((dosya = fopen("hastalar.txt", "r")) != NULL){
        // Dosyanın sonuna gelinene kadar döngüyü çalıştır
        while (!feof(dosya)){
            // Satırı oku ve ID'yi al
            fgets(satir, sizeof(satir), dosya);
            sscanf(satir, "%d", &h1.ID);

            // Eğer girilen ID ile okunan ID eşleşirse
            if (id == h1.ID){
                fclose(dosya); // Dosyayı kapat
                yedekle(); // Yedeği al
                sil(id); // Hasta kaydını sil
                sonuc = 1; // Sonuç başarılı olarak işaretle
                break; // Döngüden çık
            }
        }
    }
    fclose(dosya); // Dosyayı kapat

    // Eğer silme işlemi başarısız olursa
    if (sonuc == 0){
        system("COLOR 0");
        printf("%s%d ID'li hasta bulunamadı!%s\n", RED, id, RESET);
    } else {
        system("COLOR 0");
        yavasYazma("Hasta kaydi siliniyor...");
        printf("\n%sSilme islemi basarili.%s\n", GREEN, RESET);
    }

    usleep(1000000);
    yavasYazma("Ana menuye donuluyor...");
}

// Hasta kaydının güncellenmesini sağlayan fonksiyon.
void guncelle(int id2){
    char satir[200];

    // "hastalar.txt" dosyasını yazma modunda aç
    if ((dosya=fopen("hastalar.txt","w")) != NULL){
        // "yedekKayit.txt" dosyasını okuma modunda aç
        if ((gecici=fopen("yedekKayit.txt","r")) != NULL){
            // yedek dosyadan sırayla her satırı oku
            while (fgets(satir, sizeof(satir), gecici)){
                // satırdan hastanın ID'sini oku
                sscanf(satir, "%d", &h1.ID);
                // Eğer ID eşleşirse, yeni bilgileri iste
                if(h1.ID==id2){
                    short kntrl1 = 0, kntrl2 = 0, kntrl3 = 0;
                    printf("Guncellenecek hastanin yeni bilgilerini giriniz:\n");

                    // Yeni ad bilgisini al
                    printf("Ad       :"); getchar();
                    fgets(h1.ad, sizeof(h1.ad), stdin);
                    h1.ad[strlen(h1.ad)-1] = '\0';

                    // Yeni soyad bilgisini al
                    printf("Soyad    :");
                    fgets(h1.soyad, sizeof(h1.soyad), stdin);
                    h1.soyad[strlen(h1.soyad)-1] = '\0';

                    // Yeni yaş bilgisini al
                    while(kntrl1==0){
                        printf("Yas      :"); scanf(" %d",&h1.yas);
                        if(h1.yas >=0){
                            kntrl1=1;
                        }
                        else{
                            system("COLOR 0");
                            printf("%sLutfen yasinizi dogru giriniz!%s\n",RED,RESET);
                            usleep(2000000);
                        }
                    }
                    // Yeni cinsiyet bilgisini al
                    while(kntrl2==0){
                        printf("Cinsiyet :");	scanf(" %s",h1.cinsiyet);
                        if(strcmpi(h1.cinsiyet,"kadin")==0 || strcmpi(h1.cinsiyet,"erkek")==0){
                            kntrl2=1;
                        }
                        else{
                            system("COLOR 0");
                            printf("%sLutfen cinsiyet olarak erkek ya da kadin giriniz!%s\n",RED,RESET);
                            usleep(2000000);
                        }
                    }
                    // Yeni hastalık bilgisini al
                    printf("Hastalik :"); getchar();
                    fgets(h1.hastalik,sizeof(h1.hastalik),stdin);
                    h1.hastalik[strlen(h1.hastalik)-1]= '\0';

                    // Yeni alerji bilgisini al
                    printf("Alerjiler:");
                    fgets(h1.alerjiler,sizeof(h1.alerjiler),stdin);
                    h1.alerjiler[strlen(h1.alerjiler)-1]= '\0';

                    // Yeni kan grubu bilgisini al
                    while(kntrl3==0){
                        printf("Kan Grubu:");	scanf(" %s",h1.kanGrubu);
                        strupr(h1.kanGrubu);
                        if(strcmpi(h1.kanGrubu,"ABRH+")==0|| strcmpi(h1.kanGrubu,"ABRH-")==0 || strcmpi(h1.kanGrubu,"ARH-")==0 || strcmpi(h1.kanGrubu,"ARH+")==0 || strcmpi(h1.kanGrubu,"BRH+")==0 || strcmpi(h1.kanGrubu,"BRH-")==0|| strcmpi(h1.kanGrubu,"0RH+")==0 || strcmpi(h1.kanGrubu,"0RH-")==0){
                            kntrl3=1;
                        }
                        else{
                            system("COLOR 0");
                            printf("%sLutfen kan grubu olarak \"ABRH+,ABRH-,ARH+,ARH-,BRH+,BRH-,0RH+,0RH-\" bunlardan birini giriniz!%s\n",RED,RESET);
                            usleep(2000000);
                        }
                    }
                    // Güncellenmiş bilgileri "hastalar.txt" dosyasına yaz
                    fprintf(dosya,"%-8d %-15s %-15s %-8d %-12s %-20s %-23s %-12s\n",h1.ID,h1.ad,h1.soyad,h1.yas,h1.cinsiyet,h1.hastalik,h1.alerjiler,h1.kanGrubu);
                }
                else{
                    // ID eşleşmediyse, satırı kopyala
                    fprintf(dosya, "%s", satir);
                }
            }
            // Yedek dosyayı sil ve dosyaları kapat
            remove("yedekKayit.txt");
            fclose(gecici);
            fclose(dosya);
        }
    }
}

// Güncellenecek hastayı seçen fonksiyon.
void hastaKayitGuncelle() {
    int sonuc = 0, id2;
    char satir[200];
    printf("Guncellemek istediginiz hasta ID :");
    scanf("%d", &id2);
    // "hastalar.txt" dosyasını okurken
    if ((dosya = fopen("hastalar.txt", "r")) != NULL) { // Buradaki noktalı virgülü silmelisiniz
        // Dosya satır satır okuma
        while (fgets(satir, sizeof(satir), dosya)) {
            sscanf(satir, "%d", &h1.ID);    //String bir ifadeden boşluklara ayırarak veri almamızı sağlar
            // Girilen ID ile eşleşme kontrolü
            if (id2 == h1.ID) {
                fclose(dosya);
                yedekle(); // Güncelleme öncesi yedek alma
                guncelle(id2); // ID'ye göre güncelleme yapma
                sonuc = 1;
                break;
            }
        }
    }
    fclose(dosya);
    // Sonuç kontrolü
    if (sonuc == 0) {
        system("COLOR 0");
        printf("%s%d ID'li hasta yok!%s\n", RED, id2, RESET); // Belirtilen ID'ye sahip hasta yoksa mesaj ver
    } else {
        system("COLOR 0");
        yavasYazma("Guncelleme yapiliyor..."); // Guncelleme işlemi başarılıysa mesaj ver
        printf("\n%sGuncelleme islemi basarili.%s\n", GREEN, RESET);
    }
    usleep(1000000);
    yavasYazma("Ana menuye donuluyor..."); // Ana menüye geri dönüş yapılıyor
}

// Hasta kaydının görüntülenmesini sağlayan fonksiyon.
void hastaKayitGoruntule() {
    int sonuc = 0, id1;
    char satir[200];
    printf("Goruntulemek istediginiz hasta ID:");
    scanf("%d", &id1);
    // "hastalar.txt" dosyasını okurken
    if ((dosya = fopen("hastalar.txt", "r")) != NULL) {
        // Dosya satır satır okuma
        while (fgets(satir, sizeof(satir), dosya)) {
            sscanf(satir, "%d", &h1.ID);

            // Girilen ID ile eşleşme kontrolü
            if (h1.ID == id1) {
                printf("\nKayitli hasta bilgileri;\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-8s %-15s %-15s %-8s %-12s %-20s %-23s %-12s\n", "ID", "Ad", "Soyad", "Yas", "Cinsiyet", "Hastalik", "Alerjiler", "Kan Grubu");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("%s", satir);
                printf("------------------------------------------------------------------------------------------------------------------------\n");

                sonuc = 1;
                break;
            }
        }
    }
    fclose(dosya);
    // Sonuç kontrolü
    if (sonuc == 0) {
        system("COLOR 0");
        printf("%s%d ID'li hasta yok!%s\n", RED, id1, RESET); // Belirtilen ID'ye sahip hasta yoksa mesaj ver
    }
    usleep(3000000);
    yavasYazma("Ana menuye donuluyor..."); // Ana menüye geri dönüş yapılıyor
}

// Hasta kayıtlarının listelenmesini sağlayan fonksiyon.
void hastaKayitlariniListele() {
    char satir[200];
    if ((dosya = fopen("hastalar.txt", "r")) != NULL) {
        fscanf(dosya, "%d", &h1.ID);

        // Hasta ID'si 0 ise kayıtlı hasta bulunamadı
        if (h1.ID == 0) {
            system("COLOR 0");
            printf("%sKayitli hasta bulunamadi!%s\n", RED, RESET);
            fclose(dosya);
        } else {
            fclose(dosya);
            if ((dosya = fopen("hastalar.txt", "r")) != NULL) {
                printf("\nKayitli hastalarin bilgileri;\n\n");
                printf("-----------------------------------------------------------------------------------------------------------------------\n");
                printf("%-8s %-15s %-15s %-8s %-12s %-20s %-23s %-12s\n", "ID", "Ad", "Soyad", "Yas", "Cinsiyet", "Hastalik", "Alerjiler", "Kan Grubu");

                // Dosyayı satır satır okuma ve hastaların bilgilerini listeleyerek ekrana yazdırma
                while (fgets(satir, sizeof(satir), dosya) != NULL) {
                    satir[strlen(satir) - 1] = '\0';
                    printf("-----------------------------------------------------------------------------------------------------------------------\n");
                    printf("%s\n", satir);
                }
                printf("-----------------------------------------------------------------------------------------------------------------------\n");
            }
        }
    }
    usleep(3000000);
    yavasYazma("Ana menuye donuluyor..."); // Ana menüye geri dönüş yapılıyor
    fclose(dosya);
}

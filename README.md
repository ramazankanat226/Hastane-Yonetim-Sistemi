# Hastane Yönetim Sistemi

Bu proje, bir hastane yönetim sistemi simülasyonunu gerçekleştirir. Kullanıcılar hasta kayıtlarını ekleyebilir, silebilir, güncelleyebilir ve görüntüleyebilir. Veriler, dosya sistemine kaydedilir ve silinmeden önce yedeklenir. Uygulama, kullanıcı dostu bir terminal tabanlı arayüz sunar.

## Özellikler

1. **Hasta Kaydı Ekleme**: Kullanıcı yeni bir hasta kaydı ekleyebilir.
2. **Hasta Kaydı Silme**: Kullanıcı, hasta ID'si ile kayıtları silebilir.
3. **Hasta Kaydını Güncelleme**: Kullanıcı, hasta bilgilerini güncelleyebilir.
4. **Hasta Kaydını Görüntüleme**: Kullanıcı, belirli bir hastanın kaydını görüntüleyebilir.
5. **Tüm Hasta Kayıtlarını Listeleme**: Kullanıcı, tüm hasta kayıtlarını listeleyebilir.
6. **Yedekleme**: Hastaların kayıtları, veritabanına kaydedilmeden önce yedeklenir.
7. **Renkli Ekran**: Kullanıcı etkileşimi sırasında hata ve başarı mesajları renkli şekilde gösterilir.

## Gereksinimler

Bu uygulama C dilinde yazılmıştır ve şu kütüphaneleri kullanmaktadır:
- `stdio.h` - Giriş/Çıkış işlemleri
- `stdlib.h` - Rastgele sayılar üretme
- `string.h` - String işlemleri
- `time.h` - Rastgele sayılar için zaman tabanlı fonksiyonlar
- `unistd.h` - Terminalde gecikme sağlamak için `usleep` fonksiyonu

## Kurulum ve Çalıştırma

### 1. C Derleyici İle Çalıştırma

Bu projeyi derlemek ve çalıştırmak için C derleyicisine sahip bir ortam kullanmanız gerekmektedir.

- **Linux/MacOS**:
  1. Terminali açın.
  2. Proje dosyasını içeren klasöre gidin.
  3. Aşağıdaki komutla dosyayı derleyin:
     ```bash
     gcc -o hastaneYonetimSistemi hastaneYonetimSistemi.c
     ```
  4. Programı çalıştırın:
     ```bash
     ./hastaneYonetimSistemi
     ```

- **Windows**:
  1. Windows'ta `gcc` kurulumunu sağlamak için [MinGW](https://osdn.net/projects/mingw/releases/) veya [TDM-GCC](https://jmeubank.github.io/tdm-gcc/) kullanabilirsiniz.
  2. Komut istemcisini açarak, dosya dizinine gidin.
  3. Derleme işlemi:
     ```bash
     gcc -o hastaneYonetimSistemi.exe hastaneYonetimSistemi.c
     ```
  4. Programı çalıştırın:
     ```bash
     ./hastaneYonetimSistemi.exe
     ```

### 2. Dosya Yapısı

Projenin dosya yapısı şu şekildedir:

/HastaneYonetimSistemi 
  - | 
  - |-- hastaneYonetimSistemi.c # Ana kaynak kodu dosyası 
  - |-- hastalar.txt # Hasta bilgilerini depolayan dosya 
  - |-- yedekKayit.txt # Yedek hasta kayıt dosyası


### 3. Veritabanı

Hasta kayıtları `hastalar.txt` dosyasına kaydedilir. Bu dosya aşağıdaki bilgileri içerir:

- **ID**: Hastanın benzersiz kimlik numarası
- **Ad**: Hastanın adı
- **Soyad**: Hastanın soyadı
- **Yaş**: Hastanın yaşı
- **Cinsiyet**: Hastanın cinsiyeti (erkek veya kadın)
- **Hastalık**: Hastanın hastalığı
- **Alerjiler**: Hastanın alerjileri
- **Kan Grubu**: Hastanın kan grubu (örneğin, ABRH+, ARH-, 0RH+ vb.)

### 4. Kullanıcı Arayüzü

Program başladığında kullanıcıya aşağıdaki seçenekler sunulur:

1. **Hasta Kaydı Ekleme**: Yeni bir hasta kaydı ekler.
2. **Hasta Kaydı Silme**: Hasta ID'si ile kayıt silinir.
3. **Hasta Kaydını Güncelleme**: Hasta bilgileri güncellenir.
4. **Hasta Kaydını Görüntüleme**: Hasta kaydı görüntülenir.
5. **Tüm Hasta Kayıtlarını Listeleme**: Kayıtlı tüm hastalar liste olarak görüntülenir.
6. **Çıkış**: Programdan çıkar.

## Fonksiyonlar

### yavasYazma()
Kullanıcıya metinleri yavaşça gösteren fonksiyon.

### hastaKayitEkle()
Yeni hasta kaydı ekler ve hastaların bilgilerini `hastalar.txt` dosyasına kaydeder.

### yedekle()
Hasta kayıtlarını yedek dosyaya kopyalar ve ana dosyayı siler.

### sil()
Bir hastanın kaydını siler.

### guncelle()
Bir hastanın kaydını günceller.

### hastaKayitSil()
Kullanıcının girdiği hasta ID'sine göre kaydı siler.

### hastaKayitGuncelle()
Kullanıcının girdiği hasta ID'sine göre kaydı günceller.

### hastaKayitGoruntule()
Hasta kaydını görüntüler.

### hastaKayitlariniListele()
Tüm hasta kayıtlarını listeler.

## Hata Mesajları ve Renkli Çıktı

- Hatalar kırmızı renkte gösterilir.
- Başarı mesajları yeşil renkte gösterilir.
- Bilgi mesajları sarı renkte gösterilir.



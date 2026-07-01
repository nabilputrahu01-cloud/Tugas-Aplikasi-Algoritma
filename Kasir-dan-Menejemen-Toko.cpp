#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// === STRUKTUR DATA ===
struct operasi {
    string namaBarang, distributorBarang, kategoriBarang, kodeBarang;
    int hargaJual, hargaBeli, jumlahBarang, kodeRak;
};

// === CLASS AWAL (AUTH & PELANGGAN) ===
class awal {
private:
    string username, password;
public:
    void inputAkun() {
        cout << "--- Verifikasi Akun Karyawan ---" << endl;
        cout << "Masukkan Username : " << endl;
        cin >> username;
        cout << "Masukkan Password : " << endl;
        cin >> password;
    }

    int Login(int roleTerpilih) {
        if (roleTerpilih == 1 && username == "Rosyhan" && password == "#111") return 4;
        if (roleTerpilih == 2 && username == "Hadi" && password == "#141") return 2;
        if (roleTerpilih == 3 && username == "Nabil" && password == "#132") return 3;
        return 0;
    }

    void buatAkunPelanggan() {
        string userBaru, passBaru;
        cout << "--- BUAT AKUN BARU PELANGGAN ---" << endl;
        cout << "Masukkan Username Baru : " << endl;
        cin >> userBaru;
        cout << "Masukkan Password Baru : " << endl;
        cin >> passBaru;

        ofstream fileAkun("akun_pelanggan.txt", ios::app);
        if (fileAkun.is_open()) {
            fileAkun << userBaru << " " << passBaru << endl;
            fileAkun.close();
            cout << "[SISTEM]: Akun Berhasil Dibuat!" << endl;
        } else {
            cout << "[SISTEM]: Gagal membuka database." << endl;
        }
        system("pause");
    }
    
    int loginPelanggan() {
        string userLogin, passLogin;
        cout << "--- MASUK AKUN PELANGGAN ---" << endl;
        cout << "Masukkan Username : " << endl;
        cin >> userLogin;
        cout << "Masukkan Password : " << endl;
        cin >> passLogin;

        ifstream fileAkun("akun_pelanggan.txt");
        string userFile, passFile;
        bool ditemukan = false;

        if (fileAkun.is_open()) {
            while (fileAkun >> userFile >> passFile) {
                if (userFile == userLogin && passFile == passLogin) {
                    ditemukan = true;
                    break;
                }
            }
            fileAkun.close();
        }
        return ditemukan ? 1 : 0;
    }

    void ubahAkunPelanggan() {
        string userLama, passLama, userBaru, passBaru;
        cout << "--- UBAH DATA AKUN PELANGGAN ---" << endl;
        cout << "Masukkan Username Lama : " << endl;
        cin >> userLama;
        cout << "Masukkan Password Lama : " << endl;
        cin >> passLama;

        ifstream fileBaca("akun_pelanggan.txt");
        string users[100], passwords[100];
        int jmlAkun = 0;
        bool ditemukan = false;

        if (fileBaca.is_open()) {
            while (fileBaca >> users[jmlAkun] >> passwords[jmlAkun]) {
                if (users[jmlAkun] == userLama && passwords[jmlAkun] == passLama) {
                    ditemukan = true;
                    cout << "[SISTEM]: Verifikasi Berhasil! Masukkan data baru." << endl;
                    cout << "Masukkan Username Baru : " << endl; 
                    cin >> userBaru;
                    cout << "Masukkan Password Baru : " << endl; 
                    cin >> passBaru;
                    users[jmlAkun] = userBaru;
                    passwords[jmlAkun] = passBaru;
                }
                jmlAkun++;
                if (jmlAkun >= 100) break; 
            }
            fileBaca.close();
        } else {
            cout << "[SISTEM]: Database akun belum tersedia." << endl;
            system("pause");
            return;
        }

        if (ditemukan) {
            ofstream fileTulis("akun_pelanggan.txt");
            for (int i = 0; i < jmlAkun; i++) {
                fileTulis << users[i] << " " << passwords[i] << endl;
            }
            fileTulis.close();
            cout << "[SISTEM]: Data Akun Berhasil Diperbarui!" << endl;
        } else {
            cout << "[SISTEM]: Akun tidak ditemukan!" << endl;
        }
        system("pause");
    }
};

// === CLASS ADMIN KASIR ===
class AdminKasir {
public:
    void jalankanKasir() {
        system("cls");
        string nama[100];
        int harga[100], jumlah[100];
        int jumlahBarang, total = 0, diskon = 0;
        string pilihan;
        float persen;
        string tanggal, namaKasir;

        cout << "Selamat Datang Admin Kasir." << endl;
        cin.ignore();
        cout << "Masukkan nama kasir: " << endl; 
        getline(cin, namaKasir);
        cout << "Masukkan tanggal (contoh: 11/05/2026): " << endl; 
        getline(cin, tanggal);
        cout << "Masukkan jumlah jenis barang: " << endl; 
        cin >> jumlahBarang;

        for (int i = 0; i < jumlahBarang; i++) {
            cin.ignore();
            cout << "Barang ke-" << i + 1 << endl;
            cout << "Nama barang   : " << endl; 
            getline(cin, nama[i]);
            cout << "Harga barang  : " << endl; 
            cin >> harga[i];
            cout << "Jumlah beli   : " << endl; 
            cin >> jumlah[i];
            total += harga[i] * jumlah[i];
        }

        cout << "Apakah ada diskon? (ya/tidak): " << endl; 
        cin >> pilihan;
        if (pilihan == "ya" || pilihan == "YA") {
            cout << "Masukkan persen diskon (%) : " << endl; 
            cin >> persen;
            diskon = total * (persen / 100);
        }

        int bayar, kembalian;
        cout << "Masukkan uang bayar: " << endl; 
        cin >> bayar;
        kembalian = bayar - (total - diskon);

        cout << "========================================" << endl;
        cout << "            TOKO TIGA" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Tanggal: " << tanggal << endl;
        cout << "Kasir  : " << namaKasir << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < jumlahBarang; i++) {
            cout << nama[i] << endl;
            cout << jumlah[i] << " x " << harga[i] << "    " << harga[i] * jumlah[i] << endl;
        }
        cout << "----------------------------------------" << endl;
        cout << "TOTAL      : " << total << endl;
        cout << "DISKON     : " << diskon << endl;
        cout << "BAYAR      : " << total - diskon << endl;
        cout << "UANG       : " << bayar << endl;
        cout << "KEMBALIAN  : " << kembalian << endl;
        cout << "========================================" << endl;
        system("pause");
    }
};

// === CLASS ADMIN KEUANGAN ===
class AdminKeuangan {
private:
    string sumber[100];
    string tanggalMasuk[100];
    double jumlahMasuk[100];
    int jmlMasuk;

    void pemasukan() {
        cout << "=== INPUT PEMASUKAN ===" << endl;
        cout << "Sumber pemasukan : " << endl; 
        cin >> sumber[jmlMasuk];
        cout << "Tanggal          : " << endl; 
        cin >> tanggalMasuk[jmlMasuk];
        cout << "Jumlah           : " << endl; 
        cin >> jumlahMasuk[jmlMasuk];
        jmlMasuk++;
        cout << "Berhasil disimpan!" << endl;
        system("pause");
    }

    void liatpemasukan() {
        cout << "=== DATA PEMASUKAN ===" << endl;
        if (jmlMasuk == 0) {
            cout << "Belum ada data!" << endl;
        } else {
            for (int i = 0; i < jmlMasuk; i++) {
                cout << "Data ke-" << i + 1 << " | " << sumber[i] << " | " << tanggalMasuk[i] << " | Rp " << jumlahMasuk[i] << endl;
            }
        }
        system("pause");
    }

    void pengeluaran() { cout << "Fitur Belum Tersedia" << endl; system("pause"); }
    void liatpengeluaran() { cout << "Fitur Belum Tersedia" << endl; system("pause"); }
    void keuntungan() { cout << "Fitur Belum Tersedia" << endl; system("pause"); }

public:
    AdminKeuangan() {
        jmlMasuk = 0;
    }

    void jalankanKeuangan() {
        int PilihMK;
        do {
            system("cls");
            cout << "Selamat Datang Admin Keuangan." << endl;
            cout << "1. Input Pemasukan" << endl;
            cout << "2. Input Pengeluaran" << endl;
            cout << "3. Lihat Pemasukan" << endl;
            cout << "4. Lihat Pengeluaran" << endl;
            cout << "5. Keuntungan" << endl;
            cout << "6. Keluar" << endl;
            cout << "Pilihan : " << endl; 
            cin >> PilihMK;

            switch (PilihMK) {
                case 1: pemasukan(); break;
                case 2: pengeluaran(); break;
                case 3: liatpemasukan(); break;
                case 4: liatpengeluaran(); break;
                case 5: keuntungan(); break;
            }
        } while (PilihMK != 6);
    }
};

// === CLASS ADMIN GUDANG ===
class AdminGudang {
private:
    int strToInt(string s) {
        int num = 0;
        for (size_t i = 0; i < s.length(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
            }
        }
        return num;
    }

    int loadData(operasi barang[]) {
        ifstream filebaca("Data Gudang.txt");
        string line;
        int count = 0;
        if (!filebaca.is_open()) return 0;

        while (getline(filebaca, line)) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                string value = line.substr(pos + 2);
                
                if (!value.empty() && value[value.length() - 1] == '\r') {
                    value.erase(value.length() - 1);
                }

                if (line.find("Nama Barang") != string::npos) barang[count].namaBarang = value;
                else if (line.find("Kategori Barang") != string::npos) barang[count].kategoriBarang = value;
                else if (line.find("Kode Barang") != string::npos) barang[count].kodeBarang = value;
                else if (line.find("Harga Jual Barang") != string::npos) barang[count].hargaJual = strToInt(value);
                else if (line.find("Jumlah Barang") != string::npos) barang[count].jumlahBarang = strToInt(value);
                else if (line.find("Nomor Rak") != string::npos) barang[count].kodeRak = strToInt(value);
            }
            if (line.find("---------------------------------") != string::npos) {
                count++;
                if (count >= 1000) break; 
            }
        }
        filebaca.close();
        return count;
    }


    void saveData(operasi barang[], int totalData) {
        ofstream filemasuk("Data Gudang.txt"); 
        if (filemasuk) {
            for (int i = 0; i < totalData; i++) {
                filemasuk << "Nama Barang\t\t: " << barang[i].namaBarang << endl;
                filemasuk << "Kategori Barang\t\t: " << barang[i].kategoriBarang << endl;
                filemasuk << "Kode Barang\t\t: " << barang[i].kodeBarang << endl;
                filemasuk << "Harga Jual Barang\t: " << barang[i].hargaJual << endl;
                filemasuk << "Jumlah Barang\t\t: " << barang[i].jumlahBarang << endl;
                filemasuk << "Nomor Rak\t\t: " << barang[i].kodeRak << endl;
                filemasuk << "---------------------------------" << endl;
            }
            filemasuk.close();
        }
    }


    void BarangMasuk() {
        system("cls");
        operasi totalBarang[1000];
        int jumlahData = loadData(totalBarang); 
        
        int jumlahRakInput;
        cout << "=== Sistem Penyimpanan Barang ===" << endl;
        cout << "Berapa banyak rak yang ingin Anda isi? : " << endl; 
        cin >> jumlahRakInput;

        int r = 1;              
        int rakTerproses = 0;   

        while (rakTerproses < jumlahRakInput) {
            if (jumlahData >= 1000) {
                cout << "[PERINGATAN]: Kapasitas penyimpanan database penuh!" << endl;
                break;
            }

            const int slotPerRak = 10;
            int filledSlots = 0;

            for (int i = 0; i < jumlahData; i++) {
                if (totalBarang[i].kodeRak == r) {
                    filledSlots++;
                }
            }
            int emptySlots = slotPerRak - filledSlots;

            system("cls");
            cout << ">>> MEMERIKSA DATA KETERSEDIAAN RAK <<<" << endl;
            cout << "Status Rak " << r << " saat ini : " << endl;
            cout << "- Slot Terisi : " << filledSlots << " / 10" << endl;
            cout << "- Slot Kosong : " << emptySlots << " slot tersedia" << endl;
            cout << "----------------------------------------" << endl;

            if (emptySlots <= 0) {
                cout << "[ALERT]: Rak " << r << " sudah penuh!" << endl;
                cout << "Sistem otomatis mengalihkan pengecekan ke rak berikutnya." << endl;
                system("pause");
                r++; 
                continue; 
            }

            cout << "1. Lanjut mengisi sisa slot di Rak " << r << endl;
            cout << "2. Pindah/Lewati ke Rak Selanjutnya" << endl;
            cout << "Pilihan tindakan: " << endl;
            int pilRak;
            cin >> pilRak;

            if (pilRak == 2) {
                r++; 
                continue; 
            }

            int counter = filledSlots; 
            system("cls");
            cout << ">>> PENGISIAN RAK KE-" << r << " DIMULAI <<<" << endl;
            
            while (counter < slotPerRak) {
                if (jumlahData >= 1000) {
                    cout << "[PERINGATAN]: Kapasitas memori gudang penuh!" << endl;
                    break;
                }
                cout << "[Rak " << r << "] Mengisi Slot ke-" << counter + 1 << "/" << slotPerRak << endl;
                cin.ignore();
                cout << "Nama Barang          : " << endl; 
                getline(cin, totalBarang[jumlahData].namaBarang);
                cout << "Distributor Barang   : " << endl; 
                getline(cin, totalBarang[jumlahData].distributorBarang);
                cout << "Kategori Barang      : " << endl; 
                getline(cin, totalBarang[jumlahData].kategoriBarang);
                cout << "Kode Barang          : " << endl; 
                cin >> totalBarang[jumlahData].kodeBarang;
                cout << "Harga Beli Barang    : Rp. " << endl; 
                cin >> totalBarang[jumlahData].hargaBeli;
                cout << "Harga Jual Barang    : Rp. " << endl; 
                cin >> totalBarang[jumlahData].hargaJual;
                cout << "Jumlah Barang        : " << endl; 
                cin >> totalBarang[jumlahData].jumlahBarang;
                
                totalBarang[jumlahData].kodeRak = r; 
                jumlahData++;
                counter++;

                if (counter < slotPerRak) {
                    int lanjut;
                    cout << "Lanjut ke slot berikutnya di Rak " << r << "? (1.Ya / 2.Selesaikan Rak Ini): " << endl; 
                    cin >> lanjut;
                    if (lanjut != 1) break; 
                }
            }
            
            cout << "\n[SISTEM]: Proses input data pada Rak " << r << " selesai." << endl;
            rakTerproses++;
            r++; 
            if (rakTerproses < jumlahRakInput) { system("pause"); }
        }
        
        saveData(totalBarang, jumlahData); 
        cout << "Seluruh pembaruan data rak berhasil disimpan ke database." << endl;
        system("pause");
    }


    void cariBarang() {
        system("cls");
        operasi barang[1000];
        int totalData = loadData(barang);
        
        if (totalData == 0) {
            cout << "[SISTEM]: Belum ada data barang di gudang." << endl;
            system("pause");
            return;
        }

        string keyword;
        cout << "=== PENCARIAN BARANG ===" << endl;
        cout << "Masukkan Nama atau Kode Barang: " << endl;
        cin.ignore();
        getline(cin, keyword);

        bool ditemukan = false;
        cout << "\n--- Hasil Pencarian ---" << endl;
        for (int i = 0; i < totalData; i++) {
            if (barang[i].namaBarang == keyword || barang[i].kodeBarang == keyword) {
                cout << "Nama Barang   : " << barang[i].namaBarang << endl;
                cout << "Kode Barang   : " << barang[i].kodeBarang << endl;
                cout << "Kategori      : " << barang[i].kategoriBarang << endl;
                cout << "Stok Sisa     : " << barang[i].jumlahBarang << " pcs" << endl;
                cout << "Lokasi Rak    : Rak " << barang[i].kodeRak << endl;
                cout << "Harga Jual    : Rp. " << barang[i].hargaJual << endl;
                cout << "---------------------------------------" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "[SISTEM]: Barang '" << keyword << "' tidak ditemukan." << endl;
        }
        system("pause");
    }


    void penyesuaianStok() {
        system("cls");
        operasi barang[1000];
        int totalData = loadData(barang);

        if (totalData == 0) {
            cout << "[SISTEM]: Belum ada data barang di gudang." << endl;
            system("pause");
            return;
        }

        string kode;
        cout << "=== PENYESUAIAN STOK (STOCK OPNAME) ===" << endl;
        cout << "Masukkan Kode Barang yang ingin disesuaikan: " << endl;
        cin >> kode;

        bool ditemukan = false;
        for (int i = 0; i < totalData; i++) {
            if (barang[i].kodeBarang == kode) {
                ditemukan = true;
                cout << "\nData Saat Ini:" << endl;
                cout << "Nama Barang  : " << barang[i].namaBarang << endl;
                cout << "Stok Komputer: " << barang[i].jumlahBarang << " pcs" << endl;
                
                cout << "\nMasukkan Jumlah Stok Fisik Hasil Hitung Ulang: " << endl;
                cin >> barang[i].jumlahBarang;

                saveData(barang, totalData); 
                cout << "\n[SISTEM]: Berhasil! Stok barang telah diperbarui." << endl;
                break;
            }
        }
        if (!ditemukan) {
            cout << "[SISTEM]: Kode barang tidak terdaftar." << endl;
        }
        system("pause");
    }


    void KartuStok() {
        int PilihKS;
        do {
            system("cls");
            cout << "=== Kelola Barang ===" << endl;
            cout << "1. Barang Masuk " << endl;
            cout << "2. Cari Data Barang" << endl;
            cout << "3. Penyesuaian Stok (Stock Opname)" << endl;
            cout << "4. Kembali" << endl;
            cout << "Pilihan: " << endl; 
            cin >> PilihKS;
            
            if (PilihKS == 1) BarangMasuk();
            else if (PilihKS == 2) cariBarang();
            else if (PilihKS == 3) penyesuaianStok();
        } while (PilihKS != 4);
    }


    void lihatBarang() {
        system("cls");
        ifstream filebaca("Data Gudang.txt");
        string baris;
        cout << "=== DATA SELURUH BARANG DI GUDANG ===" << endl;
        cout << "-------------------------------------\n" << endl;
        if (filebaca.is_open()) {
            bool adaData = false;
            while (getline(filebaca, baris)) {
                cout << baris << endl;
                adaData = true;
            }
            filebaca.close();
            if (!adaData) cout << "File kosong atau belum ada data barang." << endl;
        } else {
            cout << "[SISTEM]: Gagal membuka file atau file belum dibuat!" << endl;
        }
        cout << "-------------------------------------\n" << endl;
        system("pause");
    }


    void SMinimum() {
        system("cls");
        operasi barang[1000];
        int totalData = loadData(barang);

        cout << "=== MANAJEMEN STOK MINIMUM (ALERT) ===" << endl;
        if (totalData == 0) {
            cout << "[SISTEM]: Belum ada data barang di gudang." << endl;
            system("pause");
            return;
        }

        int batasAman = 5; 
        bool adaPeringatan = false;

        cout << "Daftar Barang dengan Stok Kritis (< " << batasAman << " pcs):" << endl;
        cout << "--------------------------------------------------" << endl;
        for (int i = 0; i < totalData; i++) {
            if (barang[i].jumlahBarang < batasAman) {
                cout << "[ALERT] " << barang[i].namaBarang 
                     << " (Kode: " << barang[i].kodeBarang << ")"
                     << " -> Sisa: " << barang[i].jumlahBarang << " pcs [Lokasi: Rak " << barang[i].kodeRak << "]" << endl;
                adaPeringatan = true;
            }
        }
        cout << "--------------------------------------------------" << endl;
        if (!adaPeringatan) {
            cout << "[SISTEM]: Ketersediaan seluruh aman. Stok di atas " << batasAman << " pcs." << endl;
        }
        system("pause");
    }


    void KKategori() { 
        system("cls");
        operasi barang[1000];
        int totalData = loadData(barang);

        if (totalData == 0) {
            cout << "[SISTEM]: Belum ada data barang di gudang." << endl;
            system("pause");
            return;
        }

        string katKunci;
        cout << "=== KLASIFIKASI KATEGORI ===" << endl;
        cout << "Masukkan Nama Kategori yang ingin dilihat: " << endl;
        cin.ignore(); 
        getline(cin, katKunci);

        bool ditemukan = false;
        cout << "\n--- Daftar Barang dalam Kategori: \"" << katKunci << "\" ---" << endl;
        for (int i = 0; i < totalData; i++) {
   
            if (barang[i].kategoriBarang == katKunci) {
                cout << "Nama Barang   : " << barang[i].namaBarang << endl;
                cout << "Kode Barang   : " << barang[i].kodeBarang << endl;
                cout << "Stok Sisa     : " << barang[i].jumlahBarang << " pcs" << endl;
                cout << "Lokasi Rak    : Rak " << barang[i].kodeRak << endl;
                cout << "Harga Jual    : Rp. " << barang[i].hargaJual << endl;
                cout << "---------------------------------------" << endl;
                ditemukan = true;
            }
        }

        if (!ditemukan) {
            cout << "[SISTEM]: Tidak ditemukan barang dengan kategori '" << katKunci << "'." << endl;
            cout << "Pastikan penulisan huruf besar/kecil sesuai (Contoh: Makanan, Minuman, dll)." << endl;
        }
        system("pause");
    }
    


public:
    void jalankanGudang() {
        int PilihFG;
        do {
            system("cls");
            cout << "=== Selamat Datang Admin Gudang ===" << endl;
            cout << "1. Kelola Barang" << endl;
            cout << "2. Klasifikasi Kategori" << endl;
            cout << "3. Manajemen Stok Minimum" << endl;
            cout << "4. Lihat Data Barang" << endl;
            cout << "6. Kembali ke Login" << endl;
            cout << "Pilihan: " << endl; 
            cin >> PilihFG;

            switch (PilihFG) {
                case 1: KartuStok(); break;
                case 2: KKategori(); break;
                case 3: SMinimum(); break;
                case 4: lihatBarang(); break;
            }
        } while (PilihFG != 6);
    }
};

// === FUNGSI BELANJA ONLINE (PELANGGAN) ===
void belanjaOnline() {
    int pilihKat;
    do {
        system("cls");
        cout << "=======================================" << endl;
        cout << "        HALAMAN BELANJA ONLINE        " << endl;
        cout << "=======================================" << endl;
        cout << " 1. Makanan" << endl;
        cout << " 2. Minuman" << endl;
        cout << " 3. Kecantikan & Kesehatan" << endl;
        cout << " 4. Ibu, Bayi & Anak" << endl;
        cout << " 5. Privat Produk" << endl;
        cout << " 6. Pewangi dan Pembasmi Serangga" << endl;
        cout << " 7. Pembersih & Detergen" << endl;
        cout << " 8. Kembali" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih Kategori (1-8): " << endl; 
        cin >> pilihKat;

        if (pilihKat >= 1 && pilihKat <= 7) {
            string targetKategori = "";
            if (pilihKat == 1) targetKategori = "Makanan";
            else if (pilihKat == 2) targetKategori = "Minuman";
            else if (pilihKat == 3) targetKategori = "Kecantikan & Kesehatan";
            else if (pilihKat == 4) targetKategori = "Ibu, Bayi & Anak";
            else if (pilihKat == 5) targetKategori = "Privat Produk";
            else if (pilihKat == 6) targetKategori = "Pewangi dan Pembasmi Serangga";
            else if (pilihKat == 7) targetKategori = "Pembersih & Detergen";

            system("cls");
            ifstream filebaca("Data Gudang.txt");
            string line, currentNama = "", currentKategori = "", currentHarga = "";
            bool adaBarang = false;

            cout << "=======================================" << endl;
            cout << " DAFTAR BARANG KATEGORI: " << targetKategori << endl;
            cout << "=======================================" << endl;
            if (filebaca.is_open()) {
                while (getline(filebaca, line)) {
                    size_t pos = line.find(":");
                    if (pos != string::npos) {
                        string value = line.substr(pos + 2); 
                        if (!value.empty() && value[value.length() - 1] == '\r') {
                            value.erase(value.length() - 1);
                        }

                        if (line.find("Nama Barang") != string::npos) currentNama = value;
                        else if (line.find("Kategori Barang") != string::npos) currentKategori = value;
                        else if (line.find("Harga Jual Barang") != string::npos) currentHarga = value;
                    }
                    if (line.find("---------------------------------") != string::npos) {
                        if (currentKategori == targetKategori) {
                            cout << "Nama Barang : " << currentNama << endl;
                            cout << "Harga Jual  : Rp. " << currentHarga << endl;
                            cout << "---------------------------------------" << endl;
                            adaBarang = true;
                        }
                        currentNama = ""; currentKategori = ""; currentHarga = "";
                    }
                }
                filebaca.close();
                if (!adaBarang) cout << "[SISTEM]: Tidak ada data barang untuk kategori ini." << endl;
            } else {
                cout << "[SISTEM]: Gagal memuat database barang." << endl;
            }
            system("pause");
        }
    } while (pilihKat != 8);
}

// === MENU UTAMA ===
int main() {
    awal program;
    
    AdminKasir kasirAdmin;
    AdminKeuangan keuanganAdmin;
    AdminGudang gudangAdmin;

    int menuUtama, menuPelanggan, menuKaryawan;
    int statusLogin = 0;

    do {
        system("cls");
        cout << "+=====================================+" << endl;
        cout << "|       Selamat Datang di Toko        |" << endl;
        cout << "+=====================================+" << endl;
        cout << "1. Pelanggan" << endl;
        cout << "2. Karyawan" << endl;
        cout << "3. Keluar Aplikasi" << endl;
        cout << "Masukkan Pilihan : " << endl; 
        cin >> menuUtama;

        if (menuUtama == 3) break;

        if (menuUtama == 1) {
            do {
                system("cls");
                cout << "=== MENU PELANGGAN ===" << endl;
                cout << "1. Membuat Akun Baru" << endl;
                cout << "2. Masuk ke Akun (Belanja Online)" << endl;
                cout << "3. Ubah Username / Password Akun" << endl;
                cout << "4. Kembali" << endl;
                cout << "Pilihan : " << endl; 
                cin >> menuPelanggan;

                if (menuPelanggan == 1) program.buatAkunPelanggan();
                else if (menuPelanggan == 2) {
                    if (program.loginPelanggan() == 1) {
                        cout << "[SISTEM]: Login Berhasil!" << endl; 
                        system("pause");
                        belanjaOnline();
                    } else {
                        cout << "[SISTEM]: Username/Password Salah!" << endl; 
                        system("pause");
                    }
                }
                else if (menuPelanggan == 3) program.ubahAkunPelanggan();
            } while (menuPelanggan != 4);
        }
        else if (menuUtama == 2) {
            do {
                system("cls");
                cout << "=== MENU KARYAWAN ===" << endl;
                cout << "1. Kasir" << endl;
                cout << "2. Keuangan" << endl;
                cout << "3. Gudang" << endl;
                cout << "4. Kembali" << endl;
                cout << "Pilihan : " << endl; 
                cin >> menuKaryawan;

                if (menuKaryawan >= 1 && menuKaryawan <= 3) {
                    while (true) { 
                        program.inputAkun();
                        statusLogin = program.Login(menuKaryawan);

                        if (statusLogin != 0) {
                            if (statusLogin == 4) kasirAdmin.jalankanKasir();
                            else if (statusLogin == 2) keuanganAdmin.jalankanKeuangan();
                            else if (statusLogin == 3) gudangAdmin.jalankanGudang();
                            statusLogin = 0; 
                            break; 
                        } else {
                            char cobaLagi;
                            cout << "[SISTEM]: Login Gagal! Coba lagi? (y/n): " << endl; 
                            cin >> cobaLagi;
                            if (cobaLagi == 'n' || cobaLagi == 'N') break;
                        }
                    }
                } 
            } while (menuKaryawan != 4);
        } 
    } while (menuUtama != 3);

    return 0;
}

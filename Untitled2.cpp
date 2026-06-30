#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// === STRUKTUR DATA ===
struct operasi {
    string namaBarang, distributorBarang, kategoriBarang, kodeBarang;
    int hargaJual, hargaBeli, jumlahBarang, kodeRak;
};

// Variabel Global untuk Keuangan (Hadi)
string sumber[100];
string tanggalMasuk[100];
double jumlahMasuk[100];
int jmlMasuk = 0;

// === PROTOTYPE FUNGSI ===
void kasir();
void keuangan();
void gudang();
void KartuStok();
void KKategori();
void KRak();
void SMinimum();
void BarangMasuk();
void BarangKeluar();
void HapusBarang();
void lihatBarang(); 

void pemasukan();
void pengeluaran();
void liatpemasukan();
void liatpengeluaran();
void keuntungan();
void belanjaOnline(); 

// === CLASS LOGIN & AKUN ===
class awal {
private:
    string username, password;
public:
    void inputAkun() {
        cout << "\n--- Verifikasi Akun Karyawan ---\n";
        cout << "Masukkan Username : ";
        cin >> username;
        cout << "Masukkan Password : ";
        cin >> password;
    }

    int Login(int roleTerpilih) {
        if (roleTerpilih == 1 && username == "Rosyan" && password == "#111") 
            return 1;
        if (roleTerpilih == 2 && username == "Hadi" && password == "#141") 
            return 2;
        if (roleTerpilih == 3 && username == "Nabil" && password == "#132") 
            return 3;
            
        return 0;
    }

    // Fungsi Registrasi Pelanggan
    void buatAkunPelanggan() {
        string userBaru, passBaru;
        cout << "\n--- BUAT AKUN BARU PELANGGAN ---\n";
        cout << "Masukkan Username Baru : ";
        cin >> userBaru;
        cout << "Masukkan Password Baru : ";
        cin >> passBaru;

        ofstream fileAkun("akun_pelanggan.txt", ios::app);
        if (fileAkun.is_open()) {
            fileAkun << userBaru << " " << passBaru << endl;
            fileAkun.close();
            cout << "\n[SISTEM]: Akun Berhasil Dibuat!\n";
        } else {
            cout << "\n[SISTEM]: Gagal membuka database untuk menyimpan data.\n";
        }
        system("pause");
    }

    // Fungsi Login Pelanggan via TXT
    int loginPelanggan() {
        string userLogin, passLogin;
        cout << "\n--- MASUK AKUN PELANGGAN ---\n";
        cout << "Masukkan Username : ";
        cin >> userLogin;
        cout << "Masukkan Password : ";
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

        if (ditemukan) return 1;
        else return 0;
    }

    // Mengubah Username atau Password Pelanggan di Database
    void ubahAkunPelanggan() {
        string userLama, passLama, userBaru, passBaru;
        cout << "\n--- UBAH DATA AKUN PELANGGAN ---\n";
        cout << "Masukkan Username Lama : ";
        cin >> userLama;
        cout << "Masukkan Password Lama : ";
        cin >> passLama;

        ifstream fileBaca("akun_pelanggan.txt");
        string users[100], passwords[100];
        int jmlAkun = 0;
        bool ditemukan = false;

        if (fileBaca.is_open()) {
            while (fileBaca >> users[jmlAkun] >> passwords[jmlAkun]) {
                if (users[jmlAkun] == userLama && passwords[jmlAkun] == passLama) {
                    ditemukan = true;
                    cout << "\n[SISTEM]: Verifikasi Berhasil! Silakan masukkan data baru.\n";
                    cout << "Masukkan Username Baru : ";
                    cin >> userBaru;
                    cout << "Masukkan Password Baru : ";
                    cin >> passBaru;
                    
                    users[jmlAkun] = userBaru;
                    passwords[jmlAkun] = passBaru;
                }
                jmlAkun++;
                if (jmlAkun >= 100) break; 
            }
            fileBaca.close();
        } else {
            cout << "[SISTEM]: Database akun pelanggan belum tersedia (File tidak ditemukan).\n";
            system("pause");
            return;
        }

        if (ditemukan) {
            ofstream fileTulis("akun_pelanggan.txt");
            if (fileTulis.is_open()) {
                for (int i = 0; i < jmlAkun; i++) {
                    fileTulis << users[i] << " " << passwords[i] << endl;
                }
                fileTulis.close();
                cout << "\n[SISTEM]: Data Akun Berhasil Diperbarui di Database!\n";
            } else {
                cout << "\n[SISTEM]: Gagal menulis pembaruan data ke database.\n";
            }
        } else {
            cout << "\n[SISTEM]: Username atau Password lama salah / Tidak ditemukan!\n";
        }
        system("pause");
    }
};

// === FITUR KASIR (ROSYAN) ===
void kasir() {
    system("cls");
    string nama[100];
    int harga[100], jumlah[100];
    int jumlahBarang, total = 0, diskon = 0;
    string pilihan;
    float persen;
    string tanggal, namaKasir;

    cout << "Selamat Datang Admin Kasir." << endl;
    cin.ignore();
    cout << "\nMasukkan nama kasir: ";
    getline(cin, namaKasir);
    cout << "Masukkan tanggal (contoh: 11/05/2026): ";
    getline(cin, tanggal);
    cout << "Masukkan jumlah jenis barang: ";
    cin >> jumlahBarang;

    for (int i = 0; i < jumlahBarang; i++) {
        cin.ignore();
        cout << "\nBarang ke-" << i + 1 << endl;
        cout << "Nama barang   : ";
        getline(cin, nama[i]);
        cout << "Harga barang  : ";
        cin >> harga[i];
        cout << "Jumlah beli   : ";
        cin >> jumlah[i];
        total += harga[i] * jumlah[i];
    }

    cout << "\nApakah ada diskon? (ya/tidak): ";
    cin >> pilihan;
    if (pilihan == "ya" || pilihan == "YA") {
        cout << "Masukkan persen diskon (%) : ";
        cin >> persen;
        diskon = total * (persen / 100);
    }

    int bayar, kembalian;
    cout << "Masukkan uang bayar: ";
    cin >> bayar;
    kembalian = bayar - (total - diskon);

    cout << "\n========================================\n";
    cout << "            TOKO TIGA\n";
    cout << "     Jl. Contoh No. 123 Yogyakarta\n";
    cout << "----------------------------------------\n";
    cout << "Tanggal: " << tanggal << endl;
    cout << "Kasir  : " << namaKasir << endl;
    cout << "----------------------------------------\n";
    
    for (int i = 0; i < jumlahBarang; i++) {
        cout << nama[i] << endl;
        cout << jumlah[i] << " x " << harga[i] << "    " << harga[i] * jumlah[i] << endl;
    }
    
    cout << "----------------------------------------\n";
    cout << "TOTAL      : " << total << endl;
    cout << "DISKON     : " << diskon << endl;
    cout << "BAYAR      : " << total - diskon << endl;
    cout << "UANG       : " << bayar << endl;
    cout << "KEMBALIAN  : " << kembalian << endl;
    cout << "----------------------------------------\n";
    cout << "     TERIMA KASIH ATAS KUNJUNGAN ANDA\n";
    cout << "========================================\n";
    system("pause");
}

// === FITUR KEUANGAN (HADI) ===
void keuangan() {
    int PilihMK;
    do {
        system("cls");
        cout << "Selamat Datang Admin Keuangan." << endl;
        cout << "1. Input Pemasukan\n";
        cout << "2. Input Pengeluaran\n";
        cout << "3. Lihat Pemasukan\n";
        cout << "4. Lihat Pengeluaran\n";
        cout << "5. Keuntungan\n";
        cout << "6. Keluar\n";
        cout << "Pilihan : "; 
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

void pemasukan() {
    cout << "\n=== INPUT PEMASUKAN ===\n";
    cout << "Sumber pemasukan : "; 
    cin >> sumber[jmlMasuk];
    cout << "Tanggal : "; 
    cin >> tanggalMasuk[jmlMasuk];
    cout << "Jumlah  : "; 
    cin >> jumlahMasuk[jmlMasuk];
    jmlMasuk++;
    cout << "Berhasil disimpan!\n";
    system("pause");
}

void liatpemasukan() {
    cout << "\n=== DATA PEMASUKAN ===\n";
    if (jmlMasuk == 0) cout << "Belum ada data!\n";
    else {
        for (int i = 0; i < jmlMasuk; i++) {
            cout << "Data ke-" << i + 1 << " | " << sumber[i] << " | " << tanggalMasuk[i] << " | Rp " << jumlahMasuk[i] << endl;
        }
    }
    system("pause");
}

// === FITUR GUDANG (NABIL) ===
void menyimpan(operasi barang[], int jumlahData) {
    ofstream filemasuk("Data Gudang.txt", ios::app);
    if (filemasuk) {
        for (int i = 0; i < jumlahData; i++) {
            filemasuk << "Nama Barang\t\t: " << barang[i].namaBarang << endl;
            filemasuk << "Kategori Barang\t\t: " << barang[i].kategoriBarang << endl;
            filemasuk << "Kode Barang\t\t: " << barang[i].kodeBarang << endl;
            filemasuk << "Harga Jual Barang\t: " << barang[i].hargaJual << endl;
            filemasuk << "Jumlah Barang\t\t: " << barang[i].jumlahBarang << endl;
            filemasuk << "Nomor Rak\t\t: " << barang[i].kodeRak << endl;
            filemasuk << "---------------------------------\n";
        }
        filemasuk.close();
        cout << "[SISTEM]: Data rak tersebut berhasil disimpan ke file." << endl;
    }
}

void gudang() {
    int PilihFG;
    do {
        system("cls");
        cout << "=== Selamat Datang Admin Gudang ===\n";
        cout << "1. Kartu Stok\n";
        cout << "2. Klasifikasi Kategori\n";
        cout << "3. Klasifikasi Rak\n";
        cout << "4. Manajemen Stok Minimum\n";
        cout << "5. Lihat Data Barang\n"; 
        cout << "6. Kembali ke Login\n";
        cout << "Pilihan: "; 
        cin >> PilihFG;

        switch (PilihFG) {
            case 1: KartuStok(); break;
            case 2: KKategori(); break;
            case 3: KRak(); break;
            case 4: SMinimum(); break;
            case 5: lihatBarang(); break;
        }
    } while (PilihFG != 6);
}

void KartuStok() {
    system("cls");
    int PilihKS;
    cout << "=== Kartu Stok ===\n";
    cout << "1. Barang Masuk \n";
    cout << "2. Barang Keluar\n";
    cout << "3. Hapus Data Barang\n";
    cout << "Pilihan: ";
    cin >> PilihKS;
    switch (PilihKS) {
        case 1: BarangMasuk(); break;
        case 2: BarangKeluar(); break;
        case 3: HapusBarang(); break;
    }
}

void BarangMasuk() {
    system("cls");
    const int slotPerRak = 10; 
    operasi barang[slotPerRak]; 
    int jumlahRak;
    
    cout << "=== Sistem Inventaris Rak Otomatis ===\n";
    cout << "Setiap Rak Memiliki 10 Ruangan Untuk Menampung Data" << endl;
    cout << "Berapa banyak rak yang ingin Anda isi? : ";
    cin >> jumlahRak;

    for (int r = 1; r <= jumlahRak; r++) {
        int counter = 0; 
        system("cls");
        cout << "\n>>> MEMULAI PENGISIAN RAK KE-" << r << " <<<\n";
        
        while (counter < slotPerRak) {
            cout << "\n[Rak " << r << "] Mengisi Slot ke-" << counter + 1 << "/" << slotPerRak << endl;
            
            cin.ignore();
            cout << "Nama Barang          : "; 
            getline(cin, barang[counter].namaBarang);
            cout << "Distributor Barang   : "; 
            getline(cin, barang[counter].distributorBarang);
            cout << "Kategori Barang      : "; 
            getline(cin, barang[counter].kategoriBarang);
            cout << "Kode Barang          : "; 
            cin >> barang[counter].kodeBarang;
            cout << "Harga Beli Barang    : Rp. "; 
            cin >> barang[counter].hargaBeli;
            cout << "Harga Jual Barang    : Rp. "; 
            cin >> barang[counter].hargaJual;
            cout << "Jumlah Barang        : "; 
            cin >> barang[counter].jumlahBarang;
            
            barang[counter].kodeRak = r; 
            counter++;

            if (counter < slotPerRak) {
                int lanjut;
                cout << "Lanjut ke slot berikutnya di Rak " << r << "? (1.Ya / 2.Selesaikan Rak Ini): ";
                cin >> lanjut;
                if (lanjut != 1) break; 
            }
        }

        cout << "\n[SISTEM]: Rak " << r << " selesai. Menyimpan...\n";
        menyimpan(barang, counter);
        
        if (r < jumlahRak) {
            cout << "\nLanjut ke Rak berikutnya (" << r + 1 << ")? ";
            system("pause");
        }
    }
    cout << "\nSeluruh proses input rak selesai.";
    system("pause");
}

void lihatBarang() {
    system("cls");
    ifstream filebaca("Data Gudang.txt");
    string baris;

    cout << "=== DATA SELURUH BARANG DI GUDANG ===\n";
    cout << "-------------------------------------\n";

    if (filebaca.is_open()) {
        bool adaData = false;
        while (getline(filebaca, baris)) {
            cout << baris << endl;
            adaData = true;
        }
        filebaca.close();
        if (!adaData) cout << "File kosong atau belum ada data barang.\n";
    } else {
        cout << "[SISTEM]: Gagal membuka file atau file belum dibuat!\n";
    }
    cout << "\n-------------------------------------\n";
    system("pause");
}

// === FUNGSI RESERVED ===
void pengeluaran() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void liatpengeluaran() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void keuntungan() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void BarangKeluar() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void HapusBarang() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void KKategori() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void KRak() { cout << "Fitur Belum Tersedia\n"; system("pause"); }
void SMinimum() { cout << "Fitur Belum Tersedia\n"; system("pause"); }

// === Halaman Belanja Online Berdasarkan Kategori ===
void belanjaOnline() {
    int pilihKat;
    do {
        system("cls");
        cout << "=======================================\n";
        cout << "          HALAMAN BELANJA ONLINE       \n";
        cout << "=======================================\n";
        cout << " Kategori Produk:\n";
        cout << " 1. Makanan\n";
        cout << " 2. Minuman\n";
        cout << " 3. Kecantikan & Kesehatan\n";
        cout << " 4. Ibu, Bayi & Anak\n";
        cout << " 5. Privat Produk\n";
        cout << " 6. Pewangi dan Pembasmi Serangga\n";
        cout << " 7. Pembersih & Detergen\n";
        cout << " 8. Kembali\n";
        cout << "---------------------------------------\n";
        cout << "Pilih Kategori (1-8): ";
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
            string line;
            string currentNama = "", currentKategori = "", currentHarga = "";
            bool adaBarang = false;

            cout << "=======================================\n";
            cout << " DAFTAR BARANG KATEGORI: " << targetKategori << "\n";
            cout << "=======================================\n";

            if (filebaca.is_open()) {
                while (getline(filebaca, line)) {
                    size_t pos = line.find(":");
                    if (pos != string::npos) {
                        string value = line.substr(pos + 2); 
                        
                        if (line.find("Nama Barang") != string::npos) {
                            currentNama = value;
                        } else if (line.find("Kategori Barang") != string::npos) {
                            currentKategori = value;
                        } else if (line.find("Harga Jual Barang") != string::npos) {
                            currentHarga = value;
                        }
                    }
                    
                    if (line.find("---------------------------------") != string::npos) {
                        if (currentKategori == targetKategori) {
                            cout << "Nama Barang : " << currentNama << endl;
                            cout << "Harga Jual  : Rp. " << currentHarga << endl;
                            cout << "---------------------------------------\n";
                            adaBarang = true;
                        }
                        currentNama = ""; currentKategori = ""; currentHarga = "";
                    }
                }
                filebaca.close();

                if (!adaBarang) {
                    cout << "[SISTEM]: Tidak ada data barang untuk kategori ini.\n";
                }
            } else {
                cout << "[SISTEM]: Gagal memuat database barang.\n";
            }
            system("pause");
        }
    } while (pilihKat != 8);
}

// === MAIN SYSTEM ===
int main() {
    awal program;
    int menuUtama, menuPelanggan, menuKaryawan;
    int statusLogin = 0;

    do {
        system("cls");
        cout << "+=====================================+\n";
        cout << "|      Selamat Datang di Toko         |\n";
        cout << "+=====================================+\n";
        cout << "Keterangan Toko:\n";
        cout << "Menyediakan semua kebutuhan harian Anda secara offline.\n";
        cout << "Kini kami juga melayani Pembelian secara ONLINE!\n";
        cout << "---------------------------------------\n";
        cout << "1. Pelanggan\n";
        cout << "2. Karyawan\n";
        cout << "3. Keluar Aplikasi\n";
        cout << "Masukkan Pilihan : ";
        cin >> menuUtama;

        if (menuUtama == 3) {
            cout << "\nTerima kasih telah menggunakan program Toko Tiga.\n";
            break;
        }

        // --- PILIHAN 1: PELANGGAN ---
        if (menuUtama == 1) {
            do {
                system("cls");
                cout << "=== MENU PELANGGAN ===\n";
                cout << "1. Membuat Akun Baru\n";
                cout << "2. Masuk ke Akun (Belanja Online)\n";
                cout << "3. Ubah Username / Password Akun\n"; 
                cout << "4. Kembali ke Halaman Utama\n";
                cout << "Masukkan Pilihan : ";
                cin >> menuPelanggan;

                if (menuPelanggan == 1) {
                    program.buatAkunPelanggan();
                } 
                else if (menuPelanggan == 2) {
                    int punyaAkun;
                    // Intersepsi Peringatan Sebelum Masuk Loop Sesuai Permintaan
                    cout << "\n+=====================================+\n";
                    cout << "  [PERINGATAN]: Belum punya akun?\n";
                    cout << "  1. Belum (Daftar Akun Baru)\n";
                    cout << "  2. Sudah (Lanjut Masuk)\n";
                    cout << "+=====================================+\n";
                    cout << "Masukkan Pilihan : ";
                    cin >> punyaAkun;

                    if (punyaAkun == 1) {
                        // Langsung diarahkan ke fitur pembuatan akun baru
                        program.buatAkunPelanggan();
                    } 
                    else if (punyaAkun == 2) {
                        // Masuk ke proses input login dengan looping penanganan kesalahan
                        int loginCust = 0;
                        while (true) {
                            loginCust = program.loginPelanggan();
                            if (loginCust == 1) {
                                cout << "\n[SISTEM]: Login Berhasil! Menuju Halaman Belanja...\n";
                                system("pause");
                                belanjaOnline(); 
                                break; 
                            } else {
                                cout << "\n[SISTEM]: Username atau Password Salah! Silakan coba lagi.\n";
                                system("pause");
                                system("cls");
                                cout << "=== PELANGGAN (Coba Lagi) ===\n";
                            }
                        }
                    }
                }
                else if (menuPelanggan == 3) {
                    program.ubahAkunPelanggan(); 
                }
            } while (menuPelanggan != 4);
        }
        // --- PILIHAN 2: KARYAWAN ---
        else if (menuUtama == 2) {
            do {
                system("cls");
                cout << "=== MENU KARYAWAN ===\n";
                cout << "1. Kasir\n";
                cout << "2. Keuangan\n";
                cout << "3. Gudang\n";
                cout << "4. Kembali ke Halaman Utama\n";
                cout << "Masukkan Pilihan : ";
                cin >> menuKaryawan;

                if (menuKaryawan >= 1 && menuKaryawan <= 3) {
                    program.inputAkun();
                    statusLogin = program.Login(menuKaryawan);

                    if (statusLogin != 0) {
                        if (statusLogin == 1) kasir();
                        else if (statusLogin == 2) keuangan();
                        else if (statusLogin == 3) gudang();
                        statusLogin = 0; 
                    } else {
                        cout << "\nUsername atau Password Salah untuk Role tersebut!\n";
                        system("pause");
                    }
                } else if (menuKaryawan != 4) {
                    cout << "Pilihan tidak valid!\n";
                    system("pause");
                }
            } while (menuKaryawan != 4);
        } 
        else {
            cout << "Pilihan tidak valid!\n";
            system("pause");
        }

    } while (menuUtama != 3);

    return 0;
}
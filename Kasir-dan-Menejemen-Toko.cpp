#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

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
    void inputAkun(int roleTerpilih) {

        if (roleTerpilih == 3) {
            system("cls"); 
            
            
            time_t t = time(0);
            struct tm* now = localtime(&t);
            
            cout << "=================================================================" << endl;
            cout << "|			SISTEM WAKTU GUDANG			|" << endl;
            cout << "=================================================================" << endl;
            
           
            cout << "|		Jam Digital Laptop : ";
            if (now->tm_hour < 10) cout << "0"; cout << now->tm_hour << ".";
            if (now->tm_min < 10) cout << "0";  cout << now->tm_min << ".";
            if (now->tm_sec < 10) cout << "0";  cout << now->tm_sec << "			|" << endl;
            
            cout << "-----------------------------------------------------------------" << endl;
            cout << "|	INFORMASI JADWAL SHIFT AKTIF:				|" << endl;
            cout << "|	- Shift Pagi  : 04.00 - 12.00 (User: Nabil | Pw: #132)	|" << endl;
            cout << "|	- Shift Siang : 12.00 - 20.00 (User: nabil | Pw: #123)	|" << endl;
            cout << "|	- Shift Malam : 20.00 - 04.00 (User: NABIL | Pw: #321)	|" << endl;
            cout << "-----------------------------------------------------------------" << endl;
            
            
            cout << "|		Shift Anda Saat Ini : ";
            if (now->tm_hour >= 4 && now->tm_hour < 12) {
                cout << "PAGI";
            } else if (now->tm_hour >= 12 && now->tm_hour < 20) {
                cout << "SIANG";
            } else {
                cout << "MALAM";
            }
            cout << "			|" << endl;
            cout << "=================================================================" << endl;
        } else {
            cout << "--- Verifikasi Akun Karyawan ---" << endl;
        }

        cout << "Masukkan Username : ";
        cin >> username;
        cout << "Masukkan Password : ";
        cin >> password;
    }

    int Login(int roleTerpilih) {
    if (roleTerpilih == 1 && username == "Rosyhan" && password == "#111") return 1;
    if (roleTerpilih == 2 && username == "Hadi" && password == "#141") return 2;
    
    
    if (roleTerpilih == 3) {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        int hour = now->tm_hour;

        
        string shiftSekarang = "";
        if (hour >= 4 && hour < 12)       shiftSekarang = "pagi";
        else if (hour >= 12 && hour < 20) shiftSekarang = "siang";
        else                              shiftSekarang = "malam";

        
        string shiftInput = "";
        if (username == "Nabil" && password == "#132")      shiftInput = "pagi";
        else if (username == "nabil" && password == "#123") shiftInput = "siang";
        else if (username == "NABIL" && password == "#321") shiftInput = "malam";

        
        if (shiftInput != "") { 
            if (shiftInput == shiftSekarang) {
                return 3; 
            } else {
                
                cout << endl;
                cout << "=========================================" << endl;
                cout << "[SISTEM]: LOGIN DITOLAK!" << endl;
                cout << "[SISTEM]: Sekarang bukan shift " << shiftInput << "." << endl;
                cout << "[SISTEM]: Jam laptop mendeteksi shift " << shiftSekarang << "." << endl;
                cout << "=========================================" << endl;
                return 0; 
            }
        }
        
        
        cout << endl << "[SISTEM]: Login Gagal! Username atau Password salah." << endl;
        return 0;
    }
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
		string shiftKasir;
		int pilihShift;		

    
    int metodePembayaran;
    string namaMetode;
    int bayar, kembalian;
    int totalBayar;

    cout << "Selamat Datang Admin Kasir." << endl;
    cin.ignore();
    cout << "Masukkan nama kasir: " ;
    getline(cin, namaKasir);
    
    cout << "\n========================================" << endl;
	cout << "            SHIFT KASIR" << endl;
	cout << "========================================" << endl;
	cout << "1. Shift Pagi  (07.00 - 15.00)" << endl;
	cout << "2. Shift Siang (15.00 - 23.00)" << endl;
	cout << "3. Shift Malam (23.00 - 07.00)" << endl;
	cout << "Pilih Shift : ";
	cin >> pilihShift;
	cin.ignore();
	
	switch (pilihShift) {
	case 1:
	    shiftKasir = "Pagi";
	    break;
	case 2:
	    shiftKasir = "Siang";
	    break;
	case 3:
	    shiftKasir = "Malam";
	    break;
	default:
	    shiftKasir = "Tidak Diketahui";
	}

    cout << "Masukkan tanggal (contoh: 11/05/2026): " ;
    getline(cin, tanggal);

    cout << "Masukkan jumlah jenis barang: " ;
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

    totalBayar = total - diskon;

    
    cout << "\n========================================" << endl;
    cout << "        METODE PEMBAYARAN" << endl;
    cout << "========================================" << endl;
    cout << "1. Tunai" << endl;
    cout << "2. QRIS" << endl;
    cout << "3. Transfer" << endl;
    cout << "Pilih metode pembayaran : ";
    cin >> metodePembayaran;

    switch (metodePembayaran) {
    case 1:
        namaMetode = "Tunai";

        cout << "Masukkan uang bayar : ";
        cin >> bayar;

        while (bayar < totalBayar) {
            cout << "Uang kurang! Masukkan kembali : ";
            cin >> bayar;
        }

        kembalian = bayar - totalBayar;
        break;

    case 2:
        namaMetode = "QRIS";
        bayar = totalBayar;
        kembalian = 0;

        cout << "\n========================================" << endl;
        cout << "        PEMBAYARAN QRIS" << endl;
        cout << "========================================" << endl;
        cout << "Silakan pelanggan melakukan pembayaran" << endl;
        cout << "melalui QRIS sebesar Rp " << totalBayar << "." << endl;
        cout << endl;
        cout << "Tekan ENTER setelah pembayaran berhasil" << endl;
        cout << "dikonfirmasi..." << endl;
        cin.ignore();
        cin.get();
        break;

    case 3:
        namaMetode = "Transfer";
        bayar = totalBayar;
        kembalian = 0;

        cout << "\n========================================" << endl;
        cout << "      PEMBAYARAN TRANSFER" << endl;
        cout << "========================================" << endl;
        cout << "Silakan pelanggan melakukan transfer" << endl;
        cout << "sebesar Rp " << totalBayar << "." << endl;
        cout << endl;
        cout << "Tekan ENTER setelah pembayaran berhasil" << endl;
        cout << "dikonfirmasi..." << endl;
        cin.ignore();
        cin.get();
        break;

    default:
        cout << "Pilihan tidak valid! Sistem menggunakan pembayaran Tunai." << endl;
        namaMetode = "Tunai";

        cout << "Masukkan uang bayar : ";
        cin >> bayar;

        while (bayar < totalBayar) {
            cout << "Uang kurang! Masukkan kembali : ";
            cin >> bayar;
        }

        kembalian = bayar - totalBayar;
}

    
    // CETAK STRUK

    cout << endl;
    cout << "========================================" << endl;
    cout << "              TOKO TIGA" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Tanggal : " << tanggal << endl;
    cout << "Kasir   : " << namaKasir << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < jumlahBarang; i++) {
        cout << nama[i] << endl;
        cout << jumlah[i] << " x " << harga[i]
             << " = " << harga[i] * jumlah[i] << endl;
    }

	    cout << "----------------------------------------" << endl;
	    cout << "TOTAL      : " << total << endl;
	    cout << "DISKON     : " << diskon << endl;
	    cout << "METODE     : " << namaMetode << endl;
	    cout << "BAYAR      : " << totalBayar << endl;
	    cout << "UANG       : " << bayar << endl;
	    cout << "KEMBALIAN  : " << kembalian << endl;
	    cout << "========================================" << endl;
	    cout << "     TERIMA KASIH TELAH BERBELANJA" << endl;
	    cout << "========================================" << endl;

    system("pause");
	}
};




























//=================================
//=== CLASS ADMIN KEUANGAN HADI ===
//=================================

//=== CLASS ADMIN KEUANGAN HADI ===
class AdminKeuangan {
private:
//==============
//INPUT DATA
//==============

//===INPUT PEMASUKAN===
void pemasukan() {
    string sumber;
    string tanggal;
    long long jumlah;

	cout << "=== INPUT PEMASUKAN ===" << endl;
    cout << "Sumber pemasukan : ";
    cin.ignore();
    getline(cin, sumber);
    cout << "Tanggal pemasukan : ";
    cin >> tanggal;

    do {
        cout << "Jumlah : ";
        cin >> jumlah;

        if (jumlah <= 0) {
            cout << "Jumlah harus lebih dari 0!" << endl;
        }
    } while (jumlah <= 0);

    ofstream file("DataPemasukan.txt", ios::app);

    if (file.is_open()) {
        file << sumber
             << "|"
             << tanggal
             << "|"
             << jumlah
             << endl;
        file.close();
    }

    cout << "Data pemasukan berhasil disimpan!" << endl;
    system("pause");
}

//===INPUT PENGELUARAN===
void pengeluaran() {
    string tujuan;
    string tanggal;
    long long jumlah;

	cout << "=== INPUT PENGELUARAN ===" << endl;
    cout << "Tujuan pengeluaran : ";
    cin.ignore();
    getline(cin, tujuan);

    cout << "Tanggal pengeluaran : ";
    cin >> tanggal;

    do {
        cout << "Jumlah             : ";
        cin >> jumlah;
        if (jumlah <= 0) {
            cout << "Jumlah harus lebih dari 0!" << endl;
        }

    } while (jumlah <= 0);

    ofstream file("DataPengeluaran.txt", ios::app);

    if (file.is_open()) {

        file << tujuan
             << "|"
             << tanggal
             << "|"
             << jumlah
             << endl;

        file.close();
    }
    cout << "Data pengeluaran berhasil disimpan!" << endl;
    system("pause");
}


//==============
//LIHAT DATA
//==============

//===LIHAT PEMASUKAN===
void liatpemasukan() {
    string sumberFile;
    string tanggalFile;
    long long jumlahFile;
    
    ifstream file("DataPemasukan.txt");

    int nomor = 1;

    if (file.is_open()) {

        while (getline(file, sumberFile, '|')) {
	           getline(file, tanggalFile, '|');
	    	   file >> jumlahFile;

		file.ignore(1000, '\n');
            cout << "==============================" << endl;
            cout << "Data Pemasukan ke-" << nomor << endl;
            cout << "Sumber   : " << sumberFile << endl;
            cout << "Tanggal  : " << tanggalFile << endl;
            cout << "Nominal  : Rp " << jumlahFile << endl;
            nomor++;
        }
        file.close();
    }
    else {
        cout << "File belum tersedia." << endl;
    }
    system("pause");
}

//===LIHAT PENGELUARAN===
void liatpengeluaran() {
    string tujuanFile;
    string tanggalFile;
    long long jumlahFile;
    
    ifstream file("DataPengeluaran.txt");

    int nomor = 1;

    if (file.is_open()) {

        while (getline(file, tujuanFile, '|')) {
               getline(file, tanggalFile, '|');
               file >> jumlahFile;
		file.ignore(1000, '\n');

            cout << "==============================" << endl;
            cout << "Data Pengeluaran ke-" << nomor << endl;
            cout << "Tujuan   : " << tujuanFile << endl;
            cout << "Tanggal  : " << tanggalFile << endl;
            cout << "Nominal  : Rp " << jumlahFile << endl;
            nomor++;
        }
        file.close();
    }
    else {
        cout << "File belum tersedia." << endl;
    }
    system("pause");
}


//==============
//CARI DATA
//==============

//===CARI PEMASUKAN BERDASARKAN NAMA===
void cariNamaPemasukan() {
    ifstream file("DataPemasukan.txt");

    string sumber;
    string tanggal;
    string cariNama;
    long long jumlah;

    bool ketemu = false;

    cout << "Masukkan nama sumber : ";
    cin.ignore();
    getline(cin, cariNama);

    while (getline(file, sumber, '|')) {
        getline(file, tanggal, '|');

        file >> jumlah;
		file.ignore(1000, '\n');

        if (sumber == cariNama) {

            cout << "==============================" << endl;
            cout << "Sumber   : " << sumber << endl;
            cout << "Tanggal  : " << tanggal << endl;
            cout << "Jumlah   : Rp " << jumlah << endl;

            ketemu = true;
        }
    }

    file.close();

    if (!ketemu) {
        cout << "Data tidak ditemukan." << endl;
    }
    system("pause");
}

//CARI PENGELUARAN BERDASARKAN NAMA
void cariNamaPengeluaran() {
    ifstream file("DataPengeluaran.txt");
    
    if (!file.is_open()) {
    cout << "File DataPemasukan.txt tidak dapat dibuka!" << endl;
    system("pause");
    return;
}

    string tujuan;
    string tanggal;
    string cariNama;
    long long jumlah;

    bool ketemu = false;

    cout << "Masukkan nama tujuan : ";
    cin.ignore();
    getline(cin, cariNama);

    while (getline(file, tujuan, '|')) {
        getline(file, tanggal, '|');

       file >> jumlah;
	   file.ignore(1000, '\n');

        if (tujuan == cariNama) {
            cout << "==============================" << endl;
            cout << "Tujuan   : " << tujuan << endl;
            cout << "Tanggal  : " << tanggal << endl;
            cout << "Jumlah   : Rp " << jumlah << endl;

            ketemu = true;
        }
    }

    file.close();

    if (!ketemu) {
        cout << "Data tidak ditemukan." << endl;
    }
    system("pause");
}

//===CARI PENGELUARAN BERDASARKAN TANGGAL===
void cariPengeluaran() {
    ifstream file("DataPengeluaran.txt");
    
    if (!file.is_open()) {
    cout << "File DataPengeluaran.txt tidak dapat dibuka!" << endl;
    system("pause");
    return;
}
		if (!file.is_open()) {
		    cout << "File DataPengeluaran.txt tidak dapat dibuka!" << endl;
		    system("pause");
		    return;
		}
		
		string tujuan;
		string tanggal;
		string cariTanggal;
		long long jumlah;
		
		bool ketemu = false;
		
		    cout << "Masukkan tanggal yang dicari : ";
		    cin >> cariTanggal;
		
		    while (getline(file, tujuan, '|')) {
		
		        getline(file, tanggal, '|');
		
		    file >> jumlah;
			file.ignore(1000, '\n');
		
		if (tanggal == cariTanggal) {
		
		            cout << "==============================" << endl;
		            cout << "Tujuan   : " << tujuan << endl;
		            cout << "Tanggal  : " << tanggal << endl;
		            cout << "Jumlah   : Rp " << jumlah << endl;
		
		            ketemu = true;
		        }
		    }
		    file.close();
		
		    if (ketemu == false) {
		        cout << "Data tidak ditemukan." << endl;
		    }
		    system("pause");
}

//CARI PEMASUKAN BERDASARKAN TANGGAL
void cariPemasukan() {

    ifstream file("DataPemasukan.txt");

if (!file.is_open()) {
    cout << "File DataPemasukan.txt tidak dapat dibuka!" << endl;
    system("pause");
    return;
}
	string sumber;
	string tanggal;
	string cariTanggal;
	long long jumlah;
		
	bool ketemu = false;

    cout << "Masukkan tanggal yang dicari : ";
    cin >> cariTanggal;

    while (getline(file, sumber, '|')) {
        getline(file, tanggal, '|');
        
        file >> jumlah;
		file.ignore(1000, '\n');

	if (tanggal == cariTanggal) {
            cout << "==============================" << endl;
            cout << "Sumber   : " << sumber << endl;
            cout << "Tanggal  : " << tanggal << endl;
            cout << "Jumlah   : Rp " << jumlah << endl;

            ketemu = true;
        }
    }
    file.close();

    if (!ketemu) {
        cout << "Data tidak ditemukan." << endl;
    }
    system("pause");
}


//==============
//KEUANGAN TOKO
//==============

//===PEMASUKAN TERBESAR===
void pemasukanTerbesar() {
    ifstream file("DataPemasukan.txt");

    if (!file.is_open()) {

        cout << "File belum tersedia." << endl;
        system("pause");
        return;
    }

    string sumber;
    string tanggal;

    string sumberTerbesar;
    string tanggalTerbesar;

    long long jumlah;
    long long jumlahTerbesar = 0;

    bool adaData = false;

    while (getline(file, sumber, '|')) {

        getline(file, tanggal, '|');

        file >> jumlah;
        file.ignore(1000, '\n');

        if (adaData == false || jumlah > jumlahTerbesar) {

            jumlahTerbesar = jumlah;
            sumberTerbesar = sumber;
            tanggalTerbesar = tanggal;

            adaData = true;
        }
    }

    file.close();

    if (adaData == true) {
        cout << "==============================" << endl;
        cout << "   PEMASUKAN TERBESAR" << endl;
        cout << "==============================" << endl;
        cout << "Sumber   : " << sumberTerbesar << endl;
        cout << "Tanggal  : " << tanggalTerbesar << endl;
        cout << "Jumlah   : Rp " << jumlahTerbesar << endl;
    }
    else {
        cout << "Data pemasukan masih kosong." << endl;
    }
    system("pause");

}

//===PENGELUARAN TERBESAR===
void pengeluaranTerbesar() {

    ifstream file("DataPengeluaran.txt");

    if (!file.is_open()) {

        cout << "File belum tersedia." << endl;
        system("pause");
        return;

    }

    string tujuan;
    string tanggal;

    string tujuanTerbesar;
    string tanggalTerbesar;

    long long jumlah;
    long long jumlahTerbesar = 0;

    bool adaData = false;

    while (getline(file, tujuan, '|')) {

        getline(file, tanggal, '|');

        file >> jumlah;
        file.ignore(1000, '\n');

        if (adaData == false || jumlah > jumlahTerbesar) {
            jumlahTerbesar = jumlah;
            tujuanTerbesar = tujuan;
            tanggalTerbesar = tanggal;

            adaData = true;
        }
    }

    file.close();

    if (adaData == true) {
        cout << "==============================" << endl;
        cout << "  PENGELUARAN TERBESAR" << endl;
        cout << "==============================" << endl;
        cout << "Tujuan   : " << tujuanTerbesar << endl;
        cout << "Tanggal  : " << tanggalTerbesar << endl;
        cout << "Jumlah   : Rp " << jumlahTerbesar << endl;
    }
    else {
        cout << "Data pengeluaran masih kosong." << endl;
    }
    system("pause");
}

//===LIHAT SALDO TOKO===
void lihatSaldo() {
    long long totalMasuk = 0;
    long long totalKeluar = 0;
    string sumber;
    string tujuan;
    string tanggal;
    long long jumlah;

    ifstream fileMasuk("DataPemasukan.txt");

    if (fileMasuk.is_open()) {
        while (getline(fileMasuk, sumber, '|')) {
            getline(fileMasuk, tanggal, '|');

            fileMasuk >> jumlah;
            fileMasuk.ignore(1000, '\n');

            totalMasuk = totalMasuk + jumlah;
        }
        fileMasuk.close();
    }

    ifstream fileKeluar("DataPengeluaran.txt");

    if (fileKeluar.is_open()) {

        while (getline(fileKeluar, tujuan, '|')) {
            getline(fileKeluar, tanggal, '|');
            fileKeluar >> jumlah;
            fileKeluar.ignore(1000, '\n');

            totalKeluar = totalKeluar + jumlah;
        }
        fileKeluar.close();
    }

    cout << "==============================" << endl;
    cout << "        SALDO TOKO" << endl;
    cout << "==============================" << endl;
    cout << "Total Pemasukan   : Rp " << totalMasuk << endl;
    cout << "Total Pengeluaran : Rp " << totalKeluar << endl;
    cout << "------------------------------" << endl;
    cout << "Saldo Saat Ini    : Rp " << totalMasuk - totalKeluar << endl;

    system("pause");
}

//===STATUS KEUNTUNGAN TOKO===
void keuntungan() {
    long long totalMasuk = 0;
	long long totalKeluar = 0;
	long long untung;
		
	ifstream fileMasuk("DataPemasukan.txt");
		
	string sumberFile;
	string tanggalFile;
	long long jumlahFile;
		
	if (fileMasuk.is_open()) {
		
	while (getline(fileMasuk, sumberFile, '|')) {
		   getline(fileMasuk, tanggalFile, '|');
		
		fileMasuk >> jumlahFile;
		fileMasuk.ignore(1000, '\n');
			
		totalMasuk = totalMasuk + jumlahFile;
			}	
		fileMasuk.close();
			}
		ifstream fileKeluar("DataPengeluaran.txt");
			
		string tujuanFile;
		string tanggalKeluarFile;
		
	if (fileKeluar.is_open()) {
		while (getline(fileKeluar, tujuanFile, '|')) {
			   getline(fileKeluar, tanggalKeluarFile, '|');
		
		fileKeluar >> jumlahFile;
		fileKeluar.ignore(1000, '\n');
		
		totalKeluar = totalKeluar + jumlahFile;
		    }
		    fileKeluar.close();
		}
		untung = totalMasuk - totalKeluar;
		
		    cout << "===== LAPORAN KEUANGAN =====" << endl;
			cout << "Total Pemasukan   : Rp " << totalMasuk << endl;
			cout << "Total Pengeluaran : Rp " << totalKeluar << endl;
			cout << "Keuntungan        : Rp " << untung << endl;
			
			if (untung > 0) {
			    cout << "Status            : UNTUNG" << endl;
			}
			else if (untung < 0) {
			    cout << "Status            : RUGI" << endl;
			}
			else {
			    cout << "Status            : IMPAS" << endl;
			}	
			system("pause");
			}

//==============
//REKAP DATA
//==============

//===REKAB DATA BULANAN===
void rekapBulanan() {
    string bulan;
    string tahun;

    cout << "===== REKAP BULANAN =====" << endl;

    cout << "Masukkan Bulan (MM) : ";
    cin >> bulan;
    cout << "Masukkan Tahun (YYYY) : ";
    cin >> tahun;

    long long totalMasuk = 0;
    long long totalKeluar = 0;

    ifstream fileMasuk("DataPemasukan.txt");

    string sumber;
    string tanggal;
    long long jumlah;

    cout << endl;
    cout << "===== DATA PEMASUKAN =====" << endl;

    if (fileMasuk.is_open()) {
        while (getline(fileMasuk, sumber, '|')) {
            getline(fileMasuk, tanggal, '|');

            fileMasuk >> jumlah;
            fileMasuk.ignore(1000, '\n');

            if (tanggal.substr(3,2) == bulan &&
                tanggal.substr(6,4) == tahun) {

                cout << "Sumber  : " << sumber << endl;
                cout << "Tanggal : " << tanggal << endl;
                cout << "Jumlah  : Rp " << jumlah << endl;
                cout << "--------------------------" << endl;

                totalMasuk = totalMasuk + jumlah;
            }
        }
        fileMasuk.close();
    }

    ifstream fileKeluar("DataPengeluaran.txt");

    string tujuan;

    cout << endl;
    cout << "===== DATA PENGELUARAN =====" << endl;

    if (fileKeluar.is_open()) {
        while (getline(fileKeluar, tujuan, '|')) {

            getline(fileKeluar, tanggal, '|');

            fileKeluar >> jumlah;
            fileKeluar.ignore(1000, '\n');

            if (tanggal.substr(3,2) == bulan &&
                tanggal.substr(6,4) == tahun) {

                cout << "Tujuan  : " << tujuan << endl;
                cout << "Tanggal : " << tanggal << endl;
                cout << "Jumlah  : Rp " << jumlah << endl;
                cout << "--------------------------" << endl;

                totalKeluar = totalKeluar + jumlah;
            }
        }
        fileKeluar.close();
    }

    cout << endl;
    cout << "===== HASIL REKAP =====" << endl;
    cout << "Total Pemasukan   : Rp " << totalMasuk << endl;
    cout << "Total Pengeluaran : Rp " << totalKeluar << endl;
    cout << "Keuntungan        : Rp " << totalMasuk - totalKeluar << endl;

    system("pause");
}

//===REKAB TAHUNAN===
void rekapTahunan() {
    string tahun;

    cout << "===== REKAP TAHUNAN =====" << endl;
    cout << "Masukkan Tahun (YYYY) : ";
    cin >> tahun;

    long long totalMasuk = 0;
    long long totalKeluar = 0;

    ifstream fileMasuk("DataPemasukan.txt");

    string sumber;
    string tanggal;
    long long jumlah;

    cout << endl;
    cout << "===== DATA PEMASUKAN =====" << endl;

    if (fileMasuk.is_open()) {
        while (getline(fileMasuk, sumber, '|')) {
            getline(fileMasuk, tanggal, '|');

            fileMasuk >> jumlah;
            fileMasuk.ignore(1000, '\n');

            if (tanggal.substr(6,4) == tahun) {

                cout << "Sumber  : " << sumber << endl;
                cout << "Tanggal : " << tanggal << endl;
                cout << "Jumlah  : Rp " << jumlah << endl;
                cout << "--------------------------" << endl;
                totalMasuk = totalMasuk + jumlah;
            }
        }
        fileMasuk.close();
    }

    ifstream fileKeluar("DataPengeluaran.txt");

    string tujuan;

    cout << endl;
    cout << "===== DATA PENGELUARAN =====" << endl;
    if (fileKeluar.is_open()) {
        while (getline(fileKeluar, tujuan, '|')) {
            getline(fileKeluar, tanggal, '|');

            fileKeluar >> jumlah;
            fileKeluar.ignore(1000, '\n');

            if (tanggal.substr(6,4) == tahun) {

                cout << "Tujuan  : " << tujuan << endl;
                cout << "Tanggal : " << tanggal << endl;
                cout << "Jumlah  : Rp " << jumlah << endl;
                cout << "--------------------------" << endl;

                totalKeluar = totalKeluar + jumlah;
            }
        }
        fileKeluar.close();
    }

    cout << endl;
    cout << "===== HASIL REKAP =====" << endl;
    cout << "Total Pemasukan   : Rp " << totalMasuk << endl;
    cout << "Total Pengeluaran : Rp " << totalKeluar << endl;
    cout << "Keuntungan        : Rp " << totalMasuk - totalKeluar << endl;

    system("pause");
}

//==============
//MENU PROGRAM DIATAS
//==============

//===MENU INPUT DATA===
void menuInputData() {
    int pilih;

    do {
        system("cls");

        cout << "===== INPUT DATA =====" << endl;
        cout << "1. Pemasukan" << endl;
        cout << "2. Pengeluaran" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {

        case 1:
            pemasukan();
            break;
        case 2:
            pengeluaran();
            break;
        }
    } while (pilih != 3);
}

//===MENU LIHAT DATA===
void menuLihatData() {
    int pilih;

    do {
        system("cls");

        cout << "===== LIHAT DATA =====" << endl;
        cout << "1. Pemasukan" << endl;
        cout << "2. Pengeluaran" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {

        case 1:
            liatpemasukan();
            break;
        case 2:
            liatpengeluaran();
            break;
        }
    } while (pilih != 3);
}

//===MENU CARI DATA===
void menuCariData() {
    int pilih;

    do {
        system("cls");

        cout << "===== CARI DATA =====" << endl;
        cout << "1. Cari Berdasarkan Nama" << endl;
        cout << "2. Cari Berdasarkan Tanggal" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {

    	case 1:
		  	int jenisNama;
	
		    cout << endl;
		    cout << "1. Cari Pemasukan" << endl;
		    cout << "2. Cari Pengeluaran" << endl;
		    cout << "Pilihan : ";
		    cin >> jenisNama;
	
		    if (jenisNama == 1) {
		        cariNamaPemasukan();
		    }
		    else if (jenisNama == 2) {
		        cariNamaPengeluaran();
		    }
		    break;

        case 2:
            int jenis;

            cout << endl;
            cout << "1. Cari Pemasukan" << endl;
            cout << "2. Cari Pengeluaran" << endl;
            cout << "Pilihan : ";
            cin >> jenis;

            if (jenis == 1) {
                cariPemasukan();
            }
            else if (jenis == 2) {
                cariPengeluaran();
            }
            break;
        
        default:
			cout << "Pilihan tidak valid!" << endl;
			system("pause");
			break;
        }
    } while (pilih != 3);
}


//===MENU KEUANGAN TOKO===
void menuKeuanganToko() {
    int pilih;

    do {
        system("cls");

        cout << "===== KEUANGAN TOKO =====" << endl;
        cout << "1. Pemasukan Terbesar" << endl;
        cout << "2. Pengeluaran Terbesar" << endl;
        cout << "3. Lihat Saldo" << endl;
        cout << "4. Laporan Keuangan" << endl;
        cout << "5. Kembali" << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {

       	case 1:
			pemasukanTerbesar();
		    break;
    	case 2:
		    pengeluaranTerbesar();
		    break;
       	case 3:
		    lihatSaldo();
		    break;
        case 4:
            keuntungan();
            break;
        }
    } while (pilih != 5);
}


//===MENU REKAB DATA===
void menuRekapData() {
    int pilih;

    do {
        system("cls");

        cout << "===== REKAP DATA =====" << endl;
        cout << "1. Rekap Bulanan" << endl;
        cout << "2. Rekap Tahunan" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {

        case 1:
		    rekapBulanan();
		    break;
       	case 2:
		    rekapTahunan();
		    break;
        }
    } while (pilih != 3);
}

public:
    
void jalankanKeuangan() {
    int pilih;

    do {
        system("cls");

        cout << "========== ADMIN KEUANGAN ==========" << endl;
        cout << "1. Input Data" << endl;
        cout << "2. Lihat Data" << endl;
        cout << "3. Cari Data" << endl;
        cout << "4. Keuangan Toko" << endl;
        cout << "5. Rekap Data" << endl;
        cout << "6. Kembali" << endl;
        cout << "Pilihan : ";
        cin >> pilih;

        switch (pilih) {

        case 1:
            menuInputData();
            break;
        case 2:
            menuLihatData();
            break;
        case 3:
            menuCariData();
            break;
        case 4:
            menuKeuanganToko();
            break;
        case 5:
            menuRekapData();
            break;
        }
    } while (pilih != 6);
 }
};
//================================
//=======SELESAI KEUANGAN=========
//================================












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

	
	//=== Menyimpan Data ===
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


	//=== Barang Masuk ===
    void BarangMasuk() {
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
                cout << "Nama Barang          : "; 
                getline(cin, totalBarang[jumlahData].namaBarang);
                cout << "Distributor Barang   : "; 
                getline(cin, totalBarang[jumlahData].distributorBarang);
                cout << "Kategori Barang      : "; 
                getline(cin, totalBarang[jumlahData].kategoriBarang);
                
                
               string kodeOto = "KB";
                int urutan = 1;

                if (jumlahData > 0) {
                    string kodeTerakhir = totalBarang[jumlahData - 1].kodeBarang;
                    if (kodeTerakhir.length() >= 6 && kodeTerakhir.substr(0, 3) == "KB") {
                        string angkaS = kodeTerakhir.substr(3);
                        urutan = strToInt(angkaS) + 1;
                    } else {
                        urutan = jumlahData + 1;
                    }
                }
                
                if (urutan < 10) {
                    kodeOto += "00";
                } else if (urutan < 100) {
                    kodeOto += "0";
                }
                
                string angkaStr = "";
                int temp = urutan;
                while (temp > 0) {
                    angkaStr = char((temp % 10) + '0') + angkaStr;
                    temp /= 10;
                }
                if (angkaStr.empty()) {
                    angkaStr = "0";
                }
                kodeOto += angkaStr;

                totalBarang[jumlahData].kodeBarang = kodeOto;
                cout << "Kode Barang          : " << totalBarang[jumlahData].kodeBarang << endl;   
                cout << "Harga Beli Barang    : Rp. "; 
                cin >> totalBarang[jumlahData].hargaBeli;
                cout << "Harga Jual Barang    : Rp. "; 
                cin >> totalBarang[jumlahData].hargaJual;
                cout << "Jumlah Barang        : "; 
                cin >> totalBarang[jumlahData].jumlahBarang;
                
                totalBarang[jumlahData].kodeRak = r;

                ofstream tulisMasuk("Log_Masuk.txt", ios::app);
                if (tulisMasuk.is_open()) {
                    tulisMasuk << totalBarang[jumlahData].namaBarang << "|" << totalBarang[jumlahData].jumlahBarang << endl;
                    tulisMasuk.close();
                }
                
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


	//=== Mencari Barang ===
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

	//=== Ketika Ada Kesalahan Jumlah Stok Barang di Rill dan DI input ===
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


	//=== Pilihan Kelola Barang ===
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


	//=== Lihat Barang ===
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


	//=== Pengingat Barang yang Stok Paling Sedikit ===
    void peringatanMinimum() {
        operasi totalBarang[1000];
        int jumlahData = loadData(totalBarang);

        system("cls");
        cout << "=================================================================" << endl;
        cout << "|\t\t  LAPORAN AMBANG BATAS STOK MINIMUM\t\t|" << endl;
        cout << "=================================================================" << endl;
        cout << "[SISTEM]: Menampilkan barang dengan kuantitas kritis (stok <= 5).\n" << endl;

        bool adaKritis = false;
        int nomor = 1;

        for (int i = 0; i < jumlahData; i++) {
            
            if (totalBarang[i].jumlahBarang <= 5) {
                adaKritis = true;

                cout << nomor << ". Kode Barang : " << totalBarang[i].kodeBarang << endl;
                cout << "   Nama Barang : " << totalBarang[i].namaBarang << endl;
                cout << "   Sisa Stok   : " << totalBarang[i].jumlahBarang << " pcs (KRITIS!)" << endl;
                cout << "   Distributor : " << totalBarang[i].distributorBarang << endl;

                
                
                
                ifstream fileSupplier("Data_Supplier.txt");
                string line, idSup, namaSup, kontakSup;
                bool kontakDitemukan = false;

                if (fileSupplier.is_open()) {
                    while (getline(fileSupplier, line)) {
                        if (line.empty()) continue;
                        size_t p1 = line.find("|");
                        size_t p2 = line.find("|", p1 + 1);

                        if (p1 != string::npos && p2 != string::npos) {
                            idSup = line.substr(0, p1);
                            namaSup = line.substr(p1 + 1, p2 - p1 - 1);
                            kontakSup = line.substr(p2 + 1);

                            
                            if (totalBarang[i].distributorBarang == namaSup || totalBarang[i].distributorBarang == idSup) {
                                cout << "   -> REKOMENDASI: Hubungi " << namaSup << " (" << kontakSup << ") untuk restock." << endl;
                                kontakDitemukan = true;
                                break;
                            }
                        }
                    }
                    fileSupplier.close();
                }

                if (!kontakDitemukan) {
                    cout << "   -> REKOMENDASI: [Peringatan] Detail kontak supplier belum terdaftar di Data_Supplier.txt!" << endl;
                }
                

                cout << "-----------------------------------------------------------------" << endl;
                nomor++;
            }
        }

        if (!adaKritis) {
            cout << "[SISTEM]: Kuantitas aman! Seluruh stok barang di gudang masih tercukupi." << endl;
        }
        system("pause");
    }

	
	//=== Lihat Barang Sesuai Kategori ===
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
    
    
    //=== Menampilkan Data Barang Masuk Dan Barang Keluar ===
    void tampilkanLaporanMutasiBarang() {
    	system("cls");
    	string nama, jumlah, info;
    	cout << "=======================================" << endl;
    	cout << "       LAPORAN HISTORI BARANG MASUK    " << endl;
    	cout << "=======================================" << endl;
    	ifstream bacaMasuk("Log_Masuk.txt");
    		if (bacaMasuk.is_open()) {
        		while (getline(bacaMasuk, nama, '|') && getline(bacaMasuk, jumlah)) {
        	    cout << "Barang: " << nama << " | Jumlah Masuk: " << jumlah << " pcs" << endl;
        	}
        	bacaMasuk.close();
    		} else {
    	    cout << "Belum ada riwayat barang masuk." << endl;
    	}
    	cout << "=======================================" << endl;
    	cout << "       LAPORAN HISTORI BARANG KELUAR   " << endl;
    	cout << "=======================================" << endl;
    	ifstream bacaKeluar("Log_Keluar.txt");
    		if (bacaKeluar.is_open()) {
    		    while (getline(bacaKeluar, nama, '|') && getline(bacaKeluar, jumlah, '|') && getline(bacaKeluar, info)) {
    	        cout << "Barang: " << nama << " | Jumlah Keluar: " << jumlah << " pcs | Waktu/Ket: " << info << endl;
    	    }
    	    bacaKeluar.close();
    		} else {
        	cout << "Belum ada riwayat barang keluar." << endl;
    		}
    		cout << "=======================================" << endl;
   		system("pause");
	}
    
    
    //=== Tambah Supplier ===
    void tambahSupplier() {
        string idSupplier, namaSupplier, kontak;
        system("cls");
        cout << "=========================================" << endl;
        cout << "         INPUT DATA SUPPLIER BARU        " << endl;
        cout << "=========================================" << endl;
        
        cout << "Masukkan ID Supplier (contoh: SPL01): ";
        cin >> idSupplier;
        cout << "Masukkan Nama Perusahaan Supplier: ";
        cin.ignore();
        getline(cin, namaSupplier);
        cout << "Masukkan Kontak/No Telp: ";
        getline(cin, kontak);

        
        ofstream file("Data_Supplier.txt", ios::app);
        if (file.is_open()) {
            file << idSupplier << "|" << namaSupplier << "|" << kontak << endl;
            file.close();
            cout << "\n[SISTEM]: Supplier berhasil didaftarkan!" << endl;
        } else {
            cout << "\n[SISTEM]: Gagal membuka file Data_Supplier.txt!" << endl;
        }
        system("pause");
    }
    
    
    //=== Barang Yang di Pasok Oleh Supplier ===
    void pasokBarangDariSupplier() {
        operasi daftarBarang[1000];
        int jumlahData = loadData(daftarBarang);

        system("cls");
        cout << "=========================================" << endl;
        cout << "        PASOKAN BARANG DARI SUPPLIER     " << endl;
        cout << "=========================================" << endl;

        string kodeBarang, idSupplier;
        int jumlahMasuk;

        cout << "Masukkan Kode Barang yang ingin dipasok (contoh: KB0001): ";
        cin >> kodeBarang;

        bool barangDitemukan = false;
        for (int i = 0; i < jumlahData; i++) {
            if (daftarBarang[i].kodeBarang == kodeBarang) {
                barangDitemukan = true;
                
                cout << "-> Barang Ditemukan: " << daftarBarang[i].namaBarang << endl;
                cout << "-> Stok Saat Ini   : " << daftarBarang[i].jumlahBarang << " pcs" << endl;
                cout << "-----------------------------------------" << endl;

                cout << "Masukkan ID Supplier Pemasok : ";
                cin >> idSupplier;
                cout << "Masukkan Jumlah Stok Masuk   : ";
                cin >> jumlahMasuk;

                if (jumlahMasuk <= 0) {
                    cout << "\n[SISTEM]: Jumlah masuk tidak valid!" << endl;
                    system("pause");
                    return;
                }

               
                daftarBarang[i].jumlahBarang += jumlahMasuk;
                saveData(daftarBarang, jumlahData);

                
                ofstream log("Log_Masuk.txt", ios::app);
                if (log.is_open()) {
                    log << daftarBarang[i].namaBarang << "|" << jumlahMasuk << "|Pemasok: " << idSupplier << endl;
                    log.close();
                }
                
                cout << "\n[SISTEM]: Stok berhasil ditambah dari Supplier " << idSupplier << "!" << endl;
                break;
            }
        }

        if (!barangDitemukan) {
            cout << "\n[SISTEM]: Barang dengan kode " << kodeBarang << " tidak ditemukan di gudang!" << endl;
        }
        system("pause");
    }
    
    
    //=== Lihat Barang Setiap Rak ===
    void lihatBarangPerRak() {
        operasi totalBarang[1000];
        int jumlahData = loadData(totalBarang);

        system("cls");
        cout << "=================================================================" << endl;
        cout << "|\t\tCARI DAFTAR BARANG BERDASARKAN RAK\t\t|" << endl;
        cout << "=================================================================" << endl;

        if (jumlahData == 0) {
            cout << "[SISTEM]: Belum ada data barang di gudang." << endl;
            system("pause");
            return;
        }

        int rakTarget;
        cout << "Masukkan Nomor Rak yang ingin dicari (Contoh: 1, 2, dst): ";
        cin >> rakTarget;

        system("cls");
        cout << "======================================================" << endl;
        cout << "|\t\t   DAFTAR BARANG DI RAK NOMOR " << rakTarget << endl;
        cout << "======================================================" << endl;
        cout << "+====================================================+" << endl;
        

        bool barangDitemukan = false;
        int nomor = 1;

       
        for (int i = 0; i < jumlahData; i++) {
            if (totalBarang[i].kodeRak == rakTarget) {
                barangDitemukan = true;
                cout << "------------------------------------------------------" << endl;
                cout << "|	Data Nomor-" << nomor << endl;
                cout << "|	Kode Barang \t: " << totalBarang[i].kodeBarang << endl;
                cout << "|	Nama Barang\t: " << totalBarang[i].namaBarang << endl;
                cout << "|	Stok\t\t: " << totalBarang[i].jumlahBarang << endl;
                cout << "|	Kategori\t: " << totalBarang[i].kategoriBarang << endl;
                cout << "------------------------------------------------------" << endl;
                nomor++;
            }
        }

        cout << "+====================================================+" << endl;

        if (!barangDitemukan) {
            cout << "\n[SISTEM]: Tidak ada barang yang ditempatkan di Rak " << rakTarget << ".\n" << endl;
        }

        system("pause");
    }
    
    
    //=== Lihat Semua Data Supplier ===
    void lihatSemuaSupplier() {
        system("cls");
        cout << "======================================================" << endl;
        cout << "|\t\tDAFTAR MASTER DATA SUPPLIER\t     |" << endl;
        cout << "======================================================" << endl;

        ifstream fileSup("Data_Supplier.txt");
        string line;
        int nomor = 1;
        bool adaSupplier = false;

        if (fileSup.is_open()) {
            while (getline(fileSup, line)) {
                if (line.empty()) continue;

                size_t p1 = line.find("|");
                size_t p2 = line.find("|", p1 + 1);

                if (p1 != string::npos && p2 != string::npos) {
                    adaSupplier = true;
                    string idSup = line.substr(0, p1);
                    string namaSup = line.substr(p1 + 1, p2 - p1 - 1);
                    string kontakSup = line.substr(p2 + 1);

                    
                    cout << "------------------------------------------------------" << endl;
                    cout << "|\tData Nomor-" << nomor << endl;
                    cout << "|\tID Supplier\t: " << idSup << endl;
                    cout << "|\tNama Toko/PT\t: " << namaSup << endl;
                    cout << "|\tKontak/Telp\t: " << kontakSup << endl;
                    cout << "------------------------------------------------------" << endl;
                    nomor++;
                }
            }
            fileSup.close();
        }

        if (!adaSupplier) {
            cout << "\n[SISTEM]: Belum ada supplier yang terdaftar di database.\n" << endl;
        }
        system("pause");
    }
    
    
    //=== Membatalkan Kerjasama Dengan Suplier ===
    void batalkanSupplier() {
        system("cls");
        cout << "======================================================" << endl;
        cout << "|\t   PEMBATALAN / HAPUS MITRA SUPPLIER\t     |" << endl;
        cout << "======================================================" << endl;

        ifstream fileSup("Data_Supplier.txt");
        if (!fileSup.is_open()) {
            cout << "[SISTEM]: Gagal membuka database supplier atau data masih kosong." << endl;
            system("pause");
            return;
        }

        string idTarget;
        cout << "Masukkan ID Supplier yang ingin dibatalkan kerja samanya: ";
        cin >> idTarget;

        ofstream fileTemp("Data_Supplier_Temp.txt");
        string line;
        bool ditemukan = false;

        while (getline(fileSup, line)) {
            if (line.empty()) continue;

            size_t p1 = line.find("|");
            if (p1 != string::npos) {
                string idSup = line.substr(0, p1);

                
                if (idSup == idTarget) {
                    ditemukan = true;
                    size_t p2 = line.find("|", p1 + 1);
                    string namaSup = line.substr(p1 + 1, p2 - p1 - 1);
                    cout << "\n[INFO]: Berhasil membatalkan kerja sama dengan [" << namaSup << "]." << endl;
                    continue; 
                }
            }
            
            fileTemp << line << endl;
        }

        fileSup.close();
        fileTemp.close();

        
        if (ditemukan) {
            remove("Data_Supplier.txt");
            rename("Data_Supplier_Temp.txt", "Data_Supplier.txt");
        } else {
            remove("Data_Supplier_Temp.txt"); 
            cout << "\n[EROR]: ID Supplier '" << idTarget << "' tidak ditemukan di database!" << endl;
        }

        system("pause");
    }
    
    
    //=== Mengurutkan Stok Paling Sedikit ===
    void urutkanStokTersedikit() {
        operasi totalBarang[1000];
        int jumlahData = loadData(totalBarang);

        system("cls");
        cout << "======================================================" << endl;
        cout << "|\t URUTAN STOK BARANG TERSEDIKIT -> TERBANYAK   |" << endl;
        cout << "======================================================" << endl;

        if (jumlahData == 0) {
            cout << "[SISTEM]: Belum ada data barang di gudang." << endl;
            system("pause");
            return;
        }

        
        for (int i = 0; i < jumlahData - 1; i++) {
            for (int j = 0; j < jumlahData - i - 1; j++) {
                
                if (totalBarang[j].jumlahBarang > totalBarang[j + 1].jumlahBarang) {
                    
                    operasi temp = totalBarang[j];
                    totalBarang[j] = totalBarang[j + 1];
                    totalBarang[j + 1] = temp;
                }
            }
        }

        
        int nomor = 1;
        for (int i = 0; i < jumlahData; i++) {
            cout << "------------------------------------------------------" << endl;
            cout << "|\tData Nomor-" << nomor << endl;
            cout << "|\tKode Barang \t: " << totalBarang[i].kodeBarang << endl;
            cout << "|\tNama Barang\t: " << totalBarang[i].namaBarang << endl;
            cout << "|\tStok\t\t: " << totalBarang[i].jumlahBarang << " pcs" << endl;
            cout << "|\tKategori\t: " << totalBarang[i].kategoriBarang << endl;
            cout << "|\tLokasi Rak\t: Rak " << totalBarang[i].kodeRak << endl;
            cout << "------------------------------------------------------" << endl;
            nomor++;
        }

        system("pause");
    }
    
    
    //=== Pilihann Menu Menejemen Stok Minimum ===
    void SMinimum(){
    	system("cls");
    	int angka;
    	cout << "Pilihan :" <<endl;
    	cout << " 1. Peringatan Stok yang Harus di Isi Ulang." << endl;
    	cout << " 2. Urutan Stok Paling Sedikit." << endl;
    	cout << " 0. Kembali Ke Pilihan" << endl;
    	cout << " Masukan Pilihan :";
    	cin >> angka;
    	
    	do{
    		switch(angka){
    		case 1:
    			peringatanMinimum();
    			break;
    		case 2:
    			urutkanStokTersedikit();
    			break;
    		default : 
    			cout << "Maaf Pilihan Tidak Ada";
			}
		}while(angka != 0);
	}


public:
	//=== Menu Utama Admin Gudang ===
    void jalankanGudang() {
        int PilihFG;
        do {
            system("cls");
            cout << "=== Selamat Datang Admin Gudang ===" << endl;
            cout << "1. Kelola Barang" << endl;
            cout << "2. Klasifikasi Kategori" << endl;
            cout << "3. Manajemen Stok Minimum" << endl;
            cout << "4. Lihat Data Barang" << endl;
            cout << "5. Lihat Laporan Barang " << endl;
            cout << "6. Lihat Barang Berdasarkan Rak" << endl;   
            cout << "7. Tambah Data Supplier Baru" << endl;
            cout << "8. Pasok Stok Barang dari Supplier" << endl;
            cout << "9. Lihat Supplier" << endl;
            cout << "10 Hapus Supplier" << endl;
            cout << "0. Kembali ke Login" << endl;
            cout << "Pilihan: " << endl; 
            cin >> PilihFG;

            switch (PilihFG) {
             	    case 1: 
        				KartuStok(); 
        				break;
    				case 2: 
        				KKategori(); 
        				break;
    				case 3: 
        				SMinimum(); 
        				break;
    				case 4: 
        				lihatBarang(); 
        				break;
    				case 5:
        				tampilkanLaporanMutasiBarang();
        				break;
        			case 6:
        				lihatBarangPerRak();
        				break;
        			case 7:
        				tambahSupplier();
        				break;
        			case 8:
        				pasokBarangDariSupplier();
        				break;
        			case 9 :
        				lihatSemuaSupplier();
        				break;
        			case 10:
        				batalkanSupplier();
        				break;
        			default:
        				cout << "Maaf Pilihan " << PilihFG << " Tidak Ada" << endl;
        				break;
            }
        } while (PilihFG != 0);
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
		cout << " 8. Cari Barang" << endl;
		cout << " 9. Kembali" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih Kategori (1-9): " << endl; 
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
			else if (pilihKat == 8) {

            system("cls");

            ifstream filebaca("Data Gudang.txt");

            string line;
            string currentNama = "";
            string currentHarga = "";

            string cariBarang;
            bool ditemukan = false;

            cout << "=======================================" << endl;
            cout << "           CARI BARANG" << endl;
            cout << "=======================================" << endl;

            cin.ignore();

            cout << "Masukkan nama barang : ";
            getline(cin, cariBarang);

            while (getline(filebaca, line)) {

                size_t pos = line.find(":");

                if (pos != string::npos) {

                    string value = line.substr(pos + 2);

                    if (line.find("Nama Barang") != string::npos)
                        currentNama = value;

                    else if (line.find("Harga Jual Barang") != string::npos)
                        currentHarga = value;
                }

                if (line.find("---------------------------------") != string::npos) {

                    if (currentNama == cariBarang) {

                        ditemukan = true;

                        cout << "\nBarang ditemukan!" << endl;
                        cout << "Nama Barang : " << currentNama << endl;
                        cout << "Harga       : Rp. " << currentHarga << endl;

                        break;
                    }

                    currentNama = "";
                    currentHarga = "";
                }
            }

            filebaca.close();

            if (!ditemukan) {
                cout << "\nBarang tidak ditemukan." << endl;
            }

            system("pause");
        }

    } while (pilihKat != 9);
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
        cout << "+===============================================================================+" << endl;
        cout << "|										|" << endl;
        cout << "|      			 Selamat Datang di Toko Tiga				|" << endl;
        cout << "|										|" << endl;
        cout << "+===============================================================================+" << endl;
        cout << "|										|" << endl;
        cout << "|	Solusi Belanja Moderen di Jaringan Ritel Terbesar			|" << endl;
        cout << "|	Sekarang Hadir dengan Sistem Pembelian Online yang Aman dan Praktis	|" << endl;
        cout << "|										|" << endl;
        cout << "+===============================================================================+" << endl;
        cout << "|										|" << endl;
        cout << "|	Selamat Pengguna Silahkan Memilih Pilihan yang Sudah di Sediakan	|" << endl;
        cout << "|	1. Pelanggan								|" << endl;
        cout << "|	2. Karyawan								|" << endl;
        cout << "|	3. Keluar Aplikasi							|" << endl;
        cout << "|										|" << endl;
        cout << "+===============================================================================+" << endl;
        cout << "	Masukkan Pilihan : " ; 
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
                cout << "Pilihan : " ; 
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
                        program.inputAkun(menuKaryawan);
                        statusLogin = program.Login(menuKaryawan);

                        if (statusLogin != 0) {
                            if (statusLogin == 1) kasirAdmin.jalankanKasir();
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

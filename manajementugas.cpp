#include <iostream>
#include <string>
using namespace std;

// Struktur ChildTugas digunakan sebagai node anak pada Multi Linked List (MLL).
// Struktur ini menyimpan data tugas yang dimiliki oleh setiap mata kuliah.
struct ChildTugas {
    string namaTugas;      // Menyimpan nama tugas
    ChildTugas* next;     // Pointer ke tugas berikutnya
};

// Struktur MataKuliah digunakan sebagai node parent pada Binary Search Tree (BST).
// Struktur ini bertipe record dan menyimpan data mata kuliah.
struct MataKuliah {
    string kodeMK;         // Kode mata kuliah
    string namaMK;         // Nama mata kuliah
    string dosen;          // Nama dosen pengampu
    int semester;          // Semester mata kuliah

    int nilaiTugas[10];    // Array bertipe dasar untuk menyimpan nilai tugas
    int jumlahNilai;       // Menyimpan jumlah nilai yang telah dimasukkan

    ChildTugas* firstChild; // Pointer ke daftar tugas (MLL)
    MataKuliah* left;       // Pointer ke child kiri BST
    MataKuliah* right;      // Pointer ke child kanan BST
};

// Root digunakan sebagai penunjuk awal dari Binary Search Tree
MataKuliah* root = nullptr;

// Fungsi ini digunakan untuk membuat node MataKuliah baru
// sekaligus melakukan inisialisasi nilai awal pada setiap atributnya.
MataKuliah* createMK(string kode, string nama, string dosen, int sem) {
    MataKuliah* mk = new MataKuliah;
    mk->kodeMK = kode;
    mk->namaMK = nama;
    mk->dosen = dosen;
    mk->semester = sem;
    mk->firstChild = nullptr;
    mk->left = mk->right = nullptr;
    mk->jumlahNilai = 0;
    return mk;
}

// Fungsi ini digunakan untuk memasukkan data mata kuliah ke dalam BST
// berdasarkan kode mata kuliah sebagai key.
void insertMK(MataKuliah*& node, MataKuliah* mk) {
    if (!node) {
        node = mk;
        return;
    }
    if (mk->kodeMK < node->kodeMK)
        insertMK(node->left, mk);
    else if (mk->kodeMK > node->kodeMK)
        insertMK(node->right, mk);
    else
        cout << "Kode Mata Kuliah sudah terdaftar!\n";
}

// Fungsi ini digunakan untuk mencari data mata kuliah pada BST
// berdasarkan kode mata kuliah.
MataKuliah* searchMK(MataKuliah* node, string kode) {
    if (!node || node->kodeMK == kode)
        return node;
    if (kode < node->kodeMK)
        return searchMK(node->left, kode);
    return searchMK(node->right, kode);
}

// Fungsi findMin digunakan untuk mencari node dengan kode terkecil
// pada subtree tertentu di BST.
MataKuliah* findMin(MataKuliah* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Fungsi deleteMK digunakan untuk menghapus data mata kuliah dari BST
// berdasarkan kode mata kuliah.
MataKuliah* deleteMK(MataKuliah* node, string kode) {
    if (!node) return nullptr;

    if (kode < node->kodeMK)
        node->left = deleteMK(node->left, kode);
    else if (kode > node->kodeMK)
        node->right = deleteMK(node->right, kode);
    else {
        if (!node->left) {
            MataKuliah* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            MataKuliah* temp = node->left;
            delete node;
            return temp;
        }
        MataKuliah* temp = findMin(node->right);
        node->kodeMK = temp->kodeMK;
        node->namaMK = temp->namaMK;
        node->dosen = temp->dosen;
        node->semester = temp->semester;
        node->jumlahNilai = temp->jumlahNilai;
        for (int i = 0; i < temp->jumlahNilai; i++)
            node->nilaiTugas[i] = temp->nilaiTugas[i];
        node->right = deleteMK(node->right, temp->kodeMK);
    }
    return node;
}

// Fungsi ini digunakan untuk menambahkan data tugas ke dalam MLL
// berdasarkan mata kuliah yang dipilih.
void tambahTugas() {
    string kode, nama;
    cout << "Kode MK: ";
    cin >> kode;

    MataKuliah* mk = searchMK(root, kode);
    if (!mk) {
        cout << "Mata kuliah tidak ditemukan.\n";
        return;
    }

    cout << "Nama Tugas: ";
    cin.ignore();
    getline(cin, nama);

    ChildTugas* baru = new ChildTugas;
    baru->namaTugas = nama;
    baru->next = mk->firstChild;
    mk->firstChild = baru;

    cout << "Tugas berhasil ditambahkan.\n";
}

// Fungsi ini digunakan untuk menghapus data tugas dari MLL
// berdasarkan nama tugas.
void hapusTugas() {
    string kode, nama;
    cout << "Kode MK: ";
    cin >> kode;

    MataKuliah* mk = searchMK(root, kode);
    if (!mk) {
        cout << "Mata kuliah tidak ditemukan.\n";
        return;
    }

    cout << "Nama Tugas: ";
    cin.ignore();
    getline(cin, nama);

    ChildTugas* cur = mk->firstChild;
    ChildTugas* prev = nullptr;

    while (cur && cur->namaTugas != nama) {
        prev = cur;
        cur = cur->next;
    }

    if (!cur) {
        cout << "Tugas tidak ditemukan.\n";
        return;
    }

    if (!prev)
        mk->firstChild = cur->next;
    else
        prev->next = cur->next;

    delete cur;
    cout << "Tugas berhasil dihapus.\n";
}

// Fungsi ini digunakan untuk menambahkan nilai ke dalam array nilai tugas
// pada data mata kuliah.
void tambahNilai() {
    string kode;
    int nilai;
    cout << "Kode MK: ";
    cin >> kode;

    MataKuliah* mk = searchMK(root, kode);
    if (!mk) {
        cout << "MK tidak ditemukan.\n";
        return;
    }

    if (mk->jumlahNilai >= 10) {
        cout << "Array nilai sudah penuh.\n";
        return;
    }

    cout << "Nilai Tugas: ";
    cin >> nilai;

    mk->nilaiTugas[mk->jumlahNilai++] = nilai;
    cout << "Nilai berhasil ditambahkan.\n";
}

// Fungsi ini digunakan untuk menampilkan seluruh data mata kuliah
// beserta nilai dan daftar tugas yang dimilikinya.
void tampilMK() {
    string kode;
    cout << "Kode MK: ";
    cin >> kode;

    MataKuliah* mk = searchMK(root, kode);
    if (!mk) {
        cout << "MK tidak ditemukan.\n";
        return;
    }

    cout << "\nKode     : " << mk->kodeMK;
    cout << "\nNama     : " << mk->namaMK;
    cout << "\nDosen    : " << mk->dosen;
    cout << "\nSemester : " << mk->semester;

    cout << "\nNilai Tugas: ";
    for (int i = 0; i < mk->jumlahNilai; i++)
        cout << mk->nilaiTugas[i] << " ";

    cout << "\nDaftar Tugas:\n";
    ChildTugas* c = mk->firstChild;
    int i = 1;
    while (c) {
        cout << i++ << ". " << c->namaTugas << endl;
        c = c->next;
    }
}

// Fungsi inorder digunakan untuk menampilkan data mata kuliah
// berdasarkan urutan BST secara inorder.
void inorder(MataKuliah* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->kodeMK << " - " << node->namaMK << endl;
    inorder(node->right);
}

// Fungsi countMK digunakan untuk menghitung jumlah node mata kuliah
// yang tersimpan di dalam BST.
int countMK(MataKuliah* node) {
    if (!node) return 0;
    return 1 + countMK(node->left) + countMK(node->right);
}

// Fungsi minMK digunakan untuk mencari mata kuliah dengan kode terkecil.
MataKuliah* minMK(MataKuliah* node) {
    while (node && node->left) node = node->left;
    return node;
}

// Fungsi maxMK digunakan untuk mencari mata kuliah dengan kode terbesar.
MataKuliah* maxMK(MataKuliah* node) {
    while (node && node->right) node = node->right;
    return node;
}

// Fungsi main merupakan menu utama program yang mengatur seluruh
// proses input dan pemanggilan fungsi sesuai pilihan pengguna.
int main() {
    int pilih;
    do {
        cout << "\n=== SISTEM MANAJEMEN TUGAS KULIAH ===\n";
        cout << "1. Tambah Mata Kuliah\n";
        cout << "2. Tambah Tugas\n";
        cout << "3. Hapus Tugas\n";
        cout << "4. Tambah Nilai\n";
        cout << "5. Tampilkan Mata Kuliah\n";
        cout << "6. Inorder BST\n";
        cout << "7. Count MK\n";
        cout << "8. Min & Max MK\n";
        cout << "9. Hapus Mata Kuliah\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            string k, n, d;
            int s;
            cin.ignore();
            cout << "Kode MK: "; getline(cin, k);
            cout << "Nama MK: "; getline(cin, n);
            cout << "Dosen  : "; getline(cin, d);
            cout << "Semester: "; cin >> s;
            insertMK(root, createMK(k, n, d, s));
        }
        else if (pilih == 2) tambahTugas();
        else if (pilih == 3) hapusTugas();
        else if (pilih == 4) tambahNilai();
        else if (pilih == 5) tampilMK();
        else if (pilih == 6) inorder(root);
        else if (pilih == 7)
            cout << "Total MK: " << countMK(root) << endl;
        else if (pilih == 8) {
            cout << "MK Terkecil: " << minMK(root)->kodeMK << endl;
            cout << "MK Terbesar: " << maxMK(root)->kodeMK << endl;
        }
        else if (pilih == 9) {
            string kode;
            cout << "Kode MK: ";
            cin >> kode;
            root = deleteMK(root, kode);
            cout << "MK berhasil dihapus.\n";
        }
    } while (pilih != 0);

    return 0;
}

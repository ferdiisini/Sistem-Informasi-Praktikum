#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <math.h>

#include <windows.h>

#include "src\positive integer scan.h"

#include "src\tampilan.h"

#include "src\array.h"

#define MODUL 3

//Jumlah Praktikan
int jumlahPraktikan;

//Daftar Praktikan
void lihatPraktikan(FILE * fp);
void tambahPraktikan(FILE * fp);
FILE * hapusPraktikan(FILE * fp);

//Jadwal Praktikan
void lihatJadwalPraktikan(FILE * fp);
FILE * ubahJadwalPraktikan(FILE * fp);

//Absensi Praktikan
void lihatAbsensiPraktikan(FILE * fp);
FILE * ubahAbsensiPraktikan(FILE * fp);

//Nilai Praktikan
void lihatNilaiPraktikan(FILE * fp);
FILE * ubahNilaiPraktikan(FILE * fp);

//Tampilan Menit/Jam
void ifless10();

//Linked List
void gatherPraktikanLinked(FILE * fp); //Mengambil data dari db.txt untuk kemudian dimasukkan ke struct lokal pada program
void copasPeserta(int npm_peserta, char * nama_peserta, int nilaiAkhir_peserta,
    int jadwal_peserta[MODUL][5], int * absensi_peserta, int * modul_peserta, char komentar_peserta[MODUL][200]); //Fungsi yang mengeksekusi transfer data dari db.txt ke Linked List
void display(); //Menampilkan Praktikan secara Linked List
void insert(); //Menambahkan Praktikan pada Linked List
void search(); //Mencari Praktikan pada Linked List
void update(); //Mengubah data Praktikan (kecuali NPM) pada Linked List
void Delete(); //Menghapus Praktikan pada Linked List
void DeleteList(); //Menghapus seluruh Linked List

//Binary Tree
struct node {
    int key;
    struct node * left, * right;
}; //Struct untuk node-node pada Binary Tree

void transfer(struct node * root, int option); //Menyalin data NPM pada Linked List ke Node pada Binary Tree
void order(struct node * root); //Menampilkan Binary Tree dengan tiga mekanisme pengurutan/traversal yang berbeda, yaitu:
void inOrder(struct node * root); //In-Order, sesuai urutan NPM
void preOrder(struct node * root); //Pre-Order, mengikuti hierarkikal suksesi Binary Tree
void postOrder(struct node * root); //Post Order, mulai dari cabang-cabang terendah hingga cabang/node tertinggi
int searchTree(struct node * root); //Mencari node pada Binary Tree
void deleteTree(struct node * root); //Menghapus node pada Binary Tree
void dataPrint(int npm); //Menampilkan data Praktikan sesuai data NPM pada Node di Binary Tree

struct node * newNode(int item) {
    struct node * temp = (struct node * ) malloc(sizeof(struct node));
    temp -> key = item;
    temp -> left = temp -> right = NULL;
    return temp;
} // Struct untuk membuat node baru pada Binary Tree

struct node * insertTree(struct node * node, int key) {
    //Jika Binary Tree belum ada, maka dibuat head dari Binary Tree yang baru
    if (node == NULL)
        return newNode(key);

    //Jika Binary Tree sudah ada, maka fungsi secara rekursif akan mengisi cabang-cabang dari node-node yang sudah ada
    if (key < node -> key)
        node -> left = insertTree(node -> left, key);
    else if (key > node -> key)
        node -> right = insertTree(node -> right, key);

    //mengembalikan pointer dari node yang tidak berubah
    return node;
} //Struct untuk mengisi data pada node di Binary Tree

struct database {
    int npm; //menyimpan npm mahasiswa
    char nama[30]; //menyimpan nama mahasiswa
    int jadwal[MODUL][5]; //menyimpan jadwal modul praktikan
    int absensi[MODUL]; //menyimpan absensi praktikan
    int modul[MODUL]; //menyimpan penilaian setiap modul
    char komentar[MODUL][200]; //menyimpan komentar yang diberikan per modul per praktikan
    int nilaiAkhir; //menyimpan nilai akhir praktikan
}
praktikan;

struct Peserta {
    int npm;
    char nama[30];
    int nilaiAkhir;
    int jadwal[MODUL][5];
    int absensi[MODUL];
    int modul[MODUL];
    char komentar[MODUL][200];
    struct Peserta * next;
}* head;

int main() {
    FILE * fp;
    struct node * root = NULL;
    int pilihan;

    if ((fp = fopen("db.txt", "r+")) == NULL) {
        if ((fp = fopen("db.txt", "w+")) == NULL) {
            printf("Tidak dapat membuat atau memuat database praktikan.");
            return 0;
        }
    }

    SetConsoleTitle("Sistem Manajemen Praktikum Laboratorium");
    frontpage();

    do {
        system("CLS");
        header();
        printf("Menu: \n");
        printf("1. Daftar Praktikan\n2. Jadwal Praktikan\n3. Absensi Praktikan\n4. Nilai Praktikan\n5. Tentang Program\n6. Linked List + Binary Tree\n7. Keluar\n\nPilihan: ");
        pilihan = positive_scanfd();
        switch (pilihan) {
        case 1:
            do {
                system("CLS");
                printf("Pilih: \n");
                printf("1. Lihat Daftar Praktikan\n2. Tambahkan Praktikan\n3. Hapus Praktikan\n4. Kembali\n\nPilihan: ");
                pilihan = positive_scanfd();
                switch (pilihan) {
                case 1:
                    lihatPraktikan(fp);
                    continue;
                case 2:
                    tambahPraktikan(fp);
                    lihatPraktikan(fp);
                    continue;
                case 3:
                    fp = hapusPraktikan(fp);
                    lihatPraktikan(fp);
                    continue;
                case 4:
                    pilihan = -2;

                default:
                    printf("Input yang Anda masukkan salah!");
                    continue;
                }
            }
            while (pilihan != -2);
            break;

        case 2:
            do {
                system("CLS");
                printf("Pilih: \n");
                printf("1. Lihat Jadwal Praktikan\n2. Isi/Ubah Jadwal Praktikan\n3. Kembali\n\nPilihan: ");
                pilihan = positive_scanfd();
                switch (pilihan) {
                case 1:
                    lihatJadwalPraktikan(fp);
                    continue;
                case 2:
                    ubahJadwalPraktikan(fp);
                    lihatJadwalPraktikan(fp);
                    continue;
                case 3:
                    pilihan = -2;

                default:
                    printf("Input yang Anda masukkan salah!");
                    continue;
                }
            }
            while (pilihan != -2);
            break;

        case 3:
            do {
                system("CLS");
                printf("Pilih: \n");
                printf("1. Lihat Absensi Praktikan\n2. Isi/Ubah Absensi Praktikan\n3. Kembali\n\nPilihan: ");
                pilihan = positive_scanfd();
                switch (pilihan) {
                case 1:
                    lihatAbsensiPraktikan(fp);
                    continue;
                case 2:
                    ubahAbsensiPraktikan(fp);
                    lihatAbsensiPraktikan(fp);
                    continue;
                case 3:
                    pilihan = -2;

                default:
                    printf("Input yang Anda masukkan salah!");
                    continue;
                }
            }
            while (pilihan != -2);
            break;

        case 4:
            do {
                system("CLS");
                printf("Pilih: \n");
                printf("1. Lihat Nilai Praktikan\n2. Isi/Ubah Nilai Praktikan\n3. Kembali\n\nPilihan: ");
                pilihan = positive_scanfd();
                switch (pilihan) {
                case 1:
                    lihatNilaiPraktikan(fp);
                    continue;
                case 2:
                    ubahNilaiPraktikan(fp);
                    lihatNilaiPraktikan(fp);
                    continue;
                case 3:
                    pilihan = -2;

                default:
                    printf("Input yang Anda masukkan salah!");
                    continue;
                }
            }
            while (pilihan != -2);
            break;

        case 5:
            system("CLS");
            alprog();
            header();
            aboutprogram();
            break;

        case 6:
            system("CLS");
            gatherPraktikanLinked(fp);
            do {
                system("CLS");
                printf("Pilih: \n### LINKEDLIST ###\n\n");
                printf("1. Update/Reset Data Praktikan dari Database\n2. Tampilkan Linked List Praktikan\n");
                printf("3. Tambah Praktikan pada Linked List\n4. Cari Praktikan pada Linked List\n");
                printf("5. Update Data Praktikan pada Linked List\n6. Hapus Praktikan dari Linked List\n");
                printf("7. Hapus Seluruh Linked List\n\n### BINARY TREE ###\n\n");
                printf("8. Tampilkan NPM Praktikan Secara Berurutan\n9. Cari NPM Praktikan\n10. Hapus Tree\n11. Keluar\n\nPilihan: ");

                pilihan = positive_scanfd();

                switch (pilihan) {
                case 1:
                    DeleteList();
                    gatherPraktikanLinked(fp);
                    continue;
                case 2:
                    display();
                    system("PAUSE");
                    continue;
                case 3:
                    insert();
                    system("PAUSE");
                    continue;
                case 4:
                    search();
                    system("PAUSE");
                    continue;
                case 5:
                    update();
                    system("PAUSE");
                    continue;
                case 6:
                    Delete();
                    system("PAUSE");
                    continue;
                case 7:
                    DeleteList();
                    printf("Linked List telah dihapus!\n\n");
                    system("PAUSE");
                    continue;
                case 8:
                    transfer(root, 1);
                    system("PAUSE");
                    continue;
                case 9:
                    transfer(root, 2);
                    system("PAUSE");
                    continue;
                case 10:
                    transfer(root, 3);
                    system("PAUSE");
                    continue;
                case 11:
                    pilihan = -2;
                    break;

                default:
                    printf("Input yang Anda masukkan salah!\n\n");
                    system("PAUSE");
                    continue;
                }
            }
            while (pilihan != -2);
            break;

        case 7:
            system("CLS");
            printf("Terima kasih telah mengggunakan program ini!\n");
            return 0;

        default:
            printf("Input yang Anda masukkan salah!");
            getch();
            continue;
        }
    }
    while (pilihan != -1);
}

//A: daftar praktikan: melihat, menambah, menghapus
void lihatPraktikan(FILE * fp) {
    int size = sizeof(praktikan);
    jumlahPraktikan = 0;
    rewind(fp);
    int i = 0;
    int opsi;
    int npm_peserta[100];
    char * nama_peserta[100];
    char checknpm = '0';
    system("CLS");
    printf("DAFTAR PRAKTIKAN\n\n");
    char temp[100];
    while ((fread( & praktikan, size, 1, fp)) == 1) {
        printf("NPM: %d\n", praktikan.npm);
        printf("Nama Praktikan: %s\n\n", praktikan.nama);
        npm_peserta[jumlahPraktikan] = praktikan.npm;
        nama_peserta[jumlahPraktikan] = malloc(strlen(praktikan.nama));
        strcpy(nama_peserta[jumlahPraktikan], praktikan.nama);
        jumlahPraktikan++;
    }
    printf("Jumlah Praktikan = %d\n\n", jumlahPraktikan);
    printf("Klik P untuk melihat daftar daftar praktikan berdasarkan NPM, atau tekan Q untuk mengurut berdasarkan nama. \nTekan tombol lain untuk kembali ke menu\n");
    checknpm = getch();
    if (checknpm == 'q' || checknpm == 'Q' || checknpm == 'p' || checknpm == 'p') {
        system("CLS");
        printf("Daftar NPM Mahasiswa Terdaftar: \n");
        if (checknpm == 'p' || checknpm == 'P') {
            sort(npm_peserta, nama_peserta, jumlahPraktikan, 0);
        }
        if (checknpm == 'q' || checknpm == 'Q') {
            sort(npm_peserta, nama_peserta, jumlahPraktikan, 1);
        }
        //printArray(npm_peserta, jumlahPraktikan);
        //i=0;
        printf("\n");
        while (i < jumlahPraktikan) {
            printf("%d - %s\n", npm_peserta[i], nama_peserta[i]);
            i++;
        }
        system("PAUSE");
    }
    //system("PAUSE");
}

void tambahPraktikan(FILE * fp) {
    int i;
    int npm_true = 0;
    char pilihan;
    system("CLS");
    printf("TAMBAH PRAKTIKAN\n\n");
    int size = sizeof(praktikan);

    fseek(fp, 0, SEEK_END);
    do {
        while (npm_true == 0) {
            printf("NPM Praktikan: ");
            praktikan.npm = positive_scanfd();

            if (praktikan.npm > 999999999 || praktikan.npm < 100000000) {
                printf("NPM 9 digit, pastikan input benar\n");
            } else {
                npm_true = 1;
            }
        }
        npm_true = 0;
        printf("Nama Praktikan: ");
        fflush(stdin);
        fgets(praktikan.nama, 30, stdin);
        praktikan.nama[strlen(praktikan.nama) - 1] = '\0';
        capword(praktikan.nama);
        fwrite( & praktikan, sizeof(praktikan), 1, fp);
        printf("\n\nApakah Anda ingin menambah praktikan lain? (Y/N)");
        fflush(stdin);
        pilihan = getchar();
    }
    while (pilihan == 'y' || pilihan == 'Y');
}

FILE * hapusPraktikan(FILE * fp) {
    int flag = 0, npm, size = sizeof(praktikan);
    FILE * ft;

    system("CLS");
    printf("HAPUS PRAKTIKAN\n\n");

    if ((ft = fopen("temp.txt", "w+")) == NULL) {
        printf("ERROR!");
        system("PAUSE");
        return fp;
    }

    printf("Input NPM praktikan yang ingin Anda hapus perekamannya: ");
    npm = positive_scanfd();
    rewind(fp);

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        if (praktikan.npm == npm) {
            flag = 1;
            printf("Data praktikan a.n. %s dengan NPM %d telah dihapus dari sistem.\n\n", praktikan.nama, praktikan.npm);
            continue;
        }

        fwrite( & praktikan, size, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt", "db.txt");

    if ((fp = fopen("db.txt", "r+")) == NULL) {
        printf("ERROR!");
        return NULL;
    }

    if (flag == 0)
        printf("Praktikan dengan NPM %d tidak ditemukan di dalam sistem.\n\n", npm);

    system("PAUSE");
    return fp;
}

//B: jadwal praktikan: melihat, menambah/mengubah
void lihatJadwalPraktikan(FILE * fp) {
    int i;
    int size = sizeof(praktikan);
    jumlahPraktikan = 0;
    rewind(fp);
    system("CLS");
    printf("JADWAL PRAKTIKAN\n\n");
    while ((fread( & praktikan, size, 1, fp)) == 1) {
        printf("NPM: %d\n", praktikan.npm);
        printf("Nama Praktikan: %s\n", praktikan.nama);
        printf("Jadwal:\n");
        jumlahPraktikan++;
        for (i = 0; i < MODUL; i++) {
            printf("\tModul %d = %d/%d/%d, ", i + 1, praktikan.jadwal[i][0], praktikan.jadwal[i][1],
                praktikan.jadwal[i][2]);
            ifless10(praktikan.jadwal[i][3]);
            printf("%d:", praktikan.jadwal[i][3]);
            ifless10(praktikan.jadwal[i][4]);
            printf("%d WIB\n", praktikan.jadwal[i][4]);
        }

        printf("\n\n");
    }
    system("PAUSE");
}

FILE * ubahJadwalPraktikan(FILE * fp) {
    int flag = 0, npm, size = sizeof(praktikan), sunting, input_true = 0;;
    char pilihan;
    FILE * ft;

    system("CLS");
    printf("ISI/UBAH JADWAL PRAKTIKAN\n\n");

    if ((ft = fopen("temp.txt", "w+")) == NULL) {
        printf("ERROR!");
        system("PAUSE");
        return fp;
    }

    printf("Input NPM praktikan yang ingin Anda isi/ubah jadwalnya: ");

    npm = positive_scanfd();
    rewind(fp);

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        if (praktikan.npm == npm) {
            flag = 1;

            printf("Anda akan menyunting jadwal praktikan a.n. %s dengan NPM %d.\n", praktikan.nama, praktikan.npm);
            printf("Modul berapa yang ingin anda sunting penjadwalannya?\nModul : ");
            while (input_true == 0) {
                sunting = positive_scanfd();
                if (sunting < MODUL + 1 && sunting > 0) {
                    input_true = 1;
                } else {
                    printf("Hanya ada %d modul, pilih antara modul 1,2,3 : ", MODUL);
                }
            }
            input_true = 0;
            printf("\nSilakan isi jadwal modul ke-%d untuk praktikan a.n. %s\n", sunting, praktikan.nama);
            while (input_true == 0) {
                printf("\tTanggal (DD): ");
                praktikan.jadwal[sunting - 1][0] = positive_scanfd();
                if (praktikan.jadwal[sunting - 1][0] > 31) {
                    printf("Pastikan pengisian tanggal benar.\n");
                } else {
                    input_true = 1;
                }
            }
            input_true = 0;
            while (input_true == 0) {
                printf("\tBulan (MM): ");
                praktikan.jadwal[sunting - 1][1] = positive_scanfd();
                if (praktikan.jadwal[sunting - 1][1] > 12) {
                    printf("Pastikan pengisian bulan benar.\n");
                } else {
                    input_true = 1;
                }
            }
            input_true = 0;
            while (input_true == 0) {
                printf("\tTahun (YYYY): ");
                praktikan.jadwal[sunting - 1][2] = positive_scanfd();
                if (praktikan.jadwal[sunting - 1][2] > 9999 || praktikan.jadwal[sunting - 1][2] < 2000) {
                    printf("Pastikan pengisian tahun benar.\n");
                } else {
                    input_true = 1;
                }
            }
            input_true = 0;
            while (input_true == 0) {
                printf("\tJam (HH): ");
                praktikan.jadwal[sunting - 1][3] = positive_scanfd();
                if (praktikan.jadwal[sunting - 1][3] > 23) { //untuk menghindari kepusingan antara 24 dan 00
                    printf("Pastikan pengisian jam benar, bila jam 24, input 0.\n");
                } else {
                    input_true = 1;
                }
            }
            input_true = 0;
            while (input_true == 0) {
                printf("\tMenit (MM): ");
                praktikan.jadwal[sunting - 1][4] = positive_scanfd();
                if (praktikan.jadwal[sunting - 1][4] > 59) { //untuk menghindari kepusingan antara 60 dan 59
                    printf("Pastikan pengisian menit benar, untuk menit 60 input 0.\n");
                } else {
                    input_true = 1;
                }
            }
            printf("Praktikan a.n. %s memiliki jadwal untuk modul ke-%d pada %d/%d/%d, pukul ",
                praktikan.nama, sunting, praktikan.jadwal[sunting - 1][0], praktikan.jadwal[sunting - 1][1],
                praktikan.jadwal[sunting - 1][2]);
            ifless10(praktikan.jadwal[sunting - 1][3]);
            printf("%d:", praktikan.jadwal[sunting - 1][3]);
            ifless10(praktikan.jadwal[sunting - 1][4]);
            printf("%d WIB.\n\n", praktikan.jadwal[sunting - 1][4]);
            fwrite( & praktikan, size, 1, ft);
            continue;

        }

        fwrite( & praktikan, size, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt", "db.txt");

    if ((fp = fopen("db.txt", "r+")) == NULL) {
        printf("ERROR!");
        return NULL;
    }

    if (flag == 0)
        printf("Praktikan dengan NPM %d tidak ditemukan di dalam sistem.\n\n", npm);

    system("PAUSE");
    return fp;
}

//C: absensi praktikan: melihat, menambah/mengubah
void lihatAbsensiPraktikan(FILE * fp) {
    int i;
    int size = sizeof(praktikan);
    jumlahPraktikan = 0;

    rewind(fp);

    system("CLS");
    printf("ABSENSI PRAKTIKAN\n\n");

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        printf("NPM: %d\n", praktikan.npm);
        printf("Nama Praktikan: %s\n", praktikan.nama);
        printf("Absensi:\n");

        for (i = 0; i < MODUL; i++) {
            printf("\tAbsensi Modul %d %d/%d/%d, ", i + 1, praktikan.jadwal[i][0], praktikan.jadwal[i][1],
                praktikan.jadwal[i][2]);
            ifless10(praktikan.jadwal[i][3]);
            printf("%d:", praktikan.jadwal[i][3]);
            ifless10(praktikan.jadwal[i][4]);
            printf("%d WIB", praktikan.jadwal[i][4]);
            if (praktikan.absensi[i] == 0)
                printf(" Tidak Hadir\n");
            else
                printf(" Hadir\n");
        }

        printf("\n\n");
    }

    system("PAUSE");
}

FILE * ubahAbsensiPraktikan(FILE * fp) {
    int flag = 0, npm, size = sizeof(praktikan), sunting, input_true;
    char pilihan;
    FILE * ft;

    system("CLS");
    printf("ISI/UBAH ABSENSI PRAKTIKAN\n\n");

    if ((ft = fopen("temp.txt", "w+")) == NULL) {
        printf("ERROR!");
        system("PAUSE");
        return fp;
    }

    printf("Input NPM praktikan yang ingin Anda isi/ubah jadwalnya: ");
    npm = positive_scanfd();
    rewind(fp);

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        if (praktikan.npm == npm) {
            flag = 1;

            printf("Anda akan menyunting absensi praktikan a.n. %s dengan NPM %d.\n", praktikan.nama, praktikan.npm);
            printf("Modul berapa yang ingin anda sunting absensinya?\nModul : ");
            while (input_true == 0) {
                sunting = positive_scanfd();
                if (sunting < MODUL + 1 && sunting > 0) {
                    input_true = 1;
                } else {
                    printf("Hanya ada %d modul, pilih antara modul 1,2,3 : ", MODUL);
                }
            }
            input_true = 0;
            printf("\nApakah pada jadwal modul ke-%d, praktikan a.n. %s hadir? (1 jika ya, 0 jika tidak)\n", sunting, praktikan.nama);
            printf("\tKehadiran: ");
            praktikan.absensi[sunting - 1] = positive_scanfd();
            printf("\nPraktikan a.n. %s dengan jadwal untuk modul ke-%d pada %d/%d/%d, pukul ",
                praktikan.nama, sunting, praktikan.jadwal[sunting - 1][0], praktikan.jadwal[sunting - 1][1],
                praktikan.jadwal[sunting - 1][2]);
            ifless10(praktikan.jadwal[sunting - 1][3]);
            printf("%d:", praktikan.jadwal[sunting - 1][3]);
            ifless10(praktikan.jadwal[sunting - 1][4]);
            printf("%d WIB dinyatakan ", praktikan.jadwal[sunting - 1][4]);
            if (praktikan.absensi[sunting - 1] == 0)
                printf("Tidak Hadir.\n\n");
            else
                printf("Hadir.\n\n");

            fwrite( & praktikan, size, 1, ft);
            continue;

        }

        fwrite( & praktikan, size, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt", "db.txt");

    if ((fp = fopen("db.txt", "r+")) == NULL) {
        printf("ERROR!");
        return NULL;
    }

    if (flag == 0)
        printf("Praktikan dengan NPM %d tidak ditemukan di dalam sistem.\n\n", npm);

    system("PAUSE");
    return fp;
}

//D: nilai praktikan: melihat nilai praktikan, menambah/mengubah nilai praktikan
void lihatNilaiPraktikan(FILE * fp) {
    int i;
    float nilaiAkhir;
    int size = sizeof(praktikan);
    jumlahPraktikan = 0;

    rewind(fp);

    system("CLS");
    printf("NILAI PRAKTIKAN\n\n");

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        printf("NPM: %d\n", praktikan.npm);
        printf("Nama Praktikan: %s\n", praktikan.nama);
        printf("Nilai:\n");

        for (i = 0; i < MODUL; i++) {
            printf("\n\tNilai Modul %d = %d\n", i + 1, praktikan.modul[i]);
            printf("\tKomentar: %s\n", praktikan.komentar[i]);
        }

        nilaiAkhir = (praktikan.modul[0] + praktikan.modul[1] + praktikan.modul[2]) / 3;
        printf("\nNilai Akhir Praktikum: %.2f\n", nilaiAkhir);
        if (nilaiAkhir < 50) {
            printf("\nNilai Akhir %s TIDAK cukup untuk lulus mata kuliah praktikum ini.", praktikan.nama);
        } else {
            printf("\n%s LULUS mata kuliah praktikum ini.", praktikan.nama);
        }
        printf("\n\n");

    }

    system("PAUSE");
}

FILE * ubahNilaiPraktikan(FILE * fp) {
    int flag = 0, npm, size = sizeof(praktikan), sunting, input_true = 0;
    char pilihan;
    FILE * ft;

    system("CLS");
    printf("ISI/UBAH NILAI PRAKTIKAN\n\n");

    if ((ft = fopen("temp.txt", "w+")) == NULL) {
        printf("ERROR!");
        system("PAUSE");
        return fp;
    }

    printf("Input NPM praktikan yang ingin Anda isi/ubah nilainya: ");
    npm = positive_scanfd();
    rewind(fp);

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        if (praktikan.npm == npm) {
            flag = 1;

            printf("Anda akan mengubah nilai praktikan a.n. %s dengan NPM %d.\n", praktikan.nama, praktikan.npm);
            printf("Modul berapa yang ingin anda ubah nilainya?\nModul : ");
            while (input_true == 0) {
                sunting = positive_scanfd();
                if (sunting < MODUL + 1 && sunting > 0) {
                    input_true = 1;
                } else {
                    printf("Hanya ada %d modul, pilih antara modul 1,2,3 : ", MODUL);
                }
            }
            input_true = 0;
            printf("\nSilakan isi nilai modul ke-%d untuk praktikan a.n. %s\n", sunting, praktikan.nama);
            while (input_true == 0) {
                printf("\tNilai Modul %d (skala 100): ", sunting);
                praktikan.modul[sunting - 1] = positive_scanfd();
                if (praktikan.modul[sunting - 1] > 100) {
                    printf("Nilai maksimal 100\n");
                } else {
                    input_true = 1;
                }
            }
            //input_true = 0; //debugging
            printf("Praktikan a.n. %s untuk modul ke-%d memiliki nilai: %d\n",
                praktikan.nama, sunting, praktikan.modul[sunting - 1]);
            printf("Apakah Anda ingin menambahkan komentar untuk modul ini? (maksimal 200 karakter, kosongkan(-) jika tidak)\n\tKomentar: ");
            scanf(" %255[^\n]s", & praktikan.komentar[sunting - 1][0]);
            fflush(stdin);

            fwrite( & praktikan, size, 1, ft);
            continue;

        }

        fwrite( & praktikan, size, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt", "db.txt");

    if ((fp = fopen("db.txt", "r+")) == NULL) {
        printf("ERROR!");
        return NULL;
    }

    if (flag == 0)
        printf("Praktikan dengan NPM %d tidak ditemukan di dalam sistem.\n\n", npm);

    system("PAUSE");
    return fp;
}

void ifless10(int value) {
    if (value < 10) {
        printf("0");
    }
}

//E: Linkedlist
void copasPeserta(int npm_peserta, char * nama_peserta, int nilaiAkhir_peserta,
    int jadwal_peserta[MODUL][5], int * absensi_peserta, int * modul_peserta, char komentar_peserta[MODUL][200]) {
    int i, j;

    struct Peserta * peserta = (struct Peserta * ) malloc(sizeof(struct Peserta));

    peserta -> npm = npm_peserta;
    strcpy(peserta -> nama, nama_peserta);
    peserta -> nilaiAkhir = nilaiAkhir_peserta;

    for (i = 0; i < MODUL; i++)
        for (j = 0; j < 5; j++)
            peserta -> jadwal[i][j] = jadwal_peserta[i][j];
    for (i = 0; i < MODUL; i++)
        peserta -> absensi[i] = absensi_peserta[i];
    for (i = 0; i < MODUL; i++)
        peserta -> modul[i] = modul_peserta[i];
    for (i = 0; i < MODUL; i++)
        strcpy(peserta -> komentar[i], komentar_peserta[i]);

    peserta -> next = NULL;

    if (head == NULL) {
        //jika tidak ada Linked List, maka akan menjadi kepala/head dari Linked List
        head = peserta;
    } else {
        //Jika list tidak kosong, maka akan menjadi head dan next adalah head yang lama
        peserta -> next = head;
        head = peserta;
    }
}

void gatherPraktikanLinked(FILE * fp) {
    int size = sizeof(praktikan);
    jumlahPraktikan = 0;
    rewind(fp);
    int i = 0;
    int npm_peserta;
    char * nama_peserta;
    int nilaiAkhir_peserta;
    int jadwal_peserta[MODUL][5];
    int absensi_peserta[MODUL];
    int modul_peserta[MODUL];
    char komentar_peserta[MODUL][200];
    system("CLS");
    printf("Mengambil Data Praktikan\n\n");
    char temp[100];

    while ((fread( & praktikan, size, 1, fp)) == 1) {
        printf("NPM: %d\n", praktikan.npm);
        printf("Nama Praktikan: %s\n", praktikan.nama);
        printf("Nilai Akhir: %d\n\n", praktikan.nilaiAkhir);

        npm_peserta = praktikan.npm;
        nama_peserta = malloc(strlen(praktikan.nama));
        strcpy(nama_peserta, praktikan.nama);
        nilaiAkhir_peserta = praktikan.nilaiAkhir;

        memcpy(jadwal_peserta, praktikan.jadwal, MODUL * 5 * sizeof(int));
        memcpy(absensi_peserta, praktikan.jadwal, MODUL * sizeof(int));
        memcpy(modul_peserta, praktikan.jadwal, MODUL * sizeof(int));
        memcpy(komentar_peserta, praktikan.jadwal, MODUL * 200 * sizeof(char));

        copasPeserta(npm_peserta, nama_peserta, nilaiAkhir_peserta,
            jadwal_peserta, absensi_peserta, modul_peserta, komentar_peserta);

        jumlahPraktikan++;
    }

    printf("Jumlah Praktikan = %d\n\n", jumlahPraktikan);

    printf("Pengambilan Data Praktikan Selesai!\n\n");
    system("PAUSE");
}

void display() {
    struct Peserta * temp = head;

    if(temp == NULL) {
        printf("Linked List Kosong!\n\n");
    }

    while (temp != NULL) {
        printf("NPM: %d\n", temp -> npm);
        printf("Nama: %s\n", temp -> nama);
        printf("Nilai Akhir: %d\n\n", temp -> nilaiAkhir);
        temp = temp -> next;
    }
}

void insert() {
    int npm_peserta, nilaiAkhir_peserta;
    char nama_peserta[30];
    struct Peserta * peserta = (struct Peserta * ) malloc(sizeof(struct Peserta));

    printf("Masukkan NPM mahasiswa: ");
    scanf("%d", & npm_peserta);

    printf("Masukkan nama mahasiswa: ");
    scanf(" %255[^\n]s", nama_peserta);

    printf("Masukkan nilai akhir mahasiswa: ");
    scanf("%d", & nilaiAkhir_peserta);

    peserta -> npm = npm_peserta;
    strcpy(peserta -> nama, nama_peserta);
    peserta -> nilaiAkhir = nilaiAkhir_peserta;

    peserta -> next = NULL;

    if (head == NULL) {
        //jika tidak ada Linked List, maka akan menjadi kepala/head dari Linked List
        head = peserta;
    } else {
    	//Jika list tidak kosong, maka akan menjadi head dan next adalah head yang lama
        peserta -> next = head;
        head = peserta;
    }

    printf("Penambahan sukses!\n");

}

void search() {
    int npm;
    printf("Berapa NPM mahasiswa yang ingin anda cari? : ");
    scanf("%d", & npm);

    struct Peserta * temp = head;

    while (temp != NULL) {
        if (temp -> npm == npm) {
            printf("\nData mahasiswa ditemukan!\n");
            printf("NPM: %d\n", temp -> npm);
            printf("Nama: %s\n", temp -> nama);
            printf("Nilai Akhir: %d\n\n", temp -> nilaiAkhir);
            return;
        }
        temp = temp -> next;
    }
    printf("Mahasiswa dengan NPM %d tidak dapat ditemukan!\n", npm);
}

void update() {
    int npm_peserta, nilaiAkhir_peserta;
    char nama_peserta[30];

    printf("Berapa NPM mahasiswa yang ingin anda perbarui datanya? : ");
    scanf("%d", & npm_peserta);

    struct Peserta * temp = head;

    while (temp != NULL) {
        if (temp -> npm == npm_peserta) {
            printf("Data mahasiswa dengan NPM %d ditemukan!\n", npm_peserta);

            printf("Masukkan nama baru: ");
            scanf(" %255[^\n]s", nama_peserta);

            printf("Masukkan nilai akhir baru: ");
            scanf("%d", & nilaiAkhir_peserta);

            strcpy(temp -> nama, nama_peserta);
            temp -> nilaiAkhir = nilaiAkhir_peserta;
            temp = temp -> next;

            printf("Update sukses!\n");
            return;
        }
    }
    printf("Mahasiswa dengan NPM %d tidak dapat ditemukan!\n", npm_peserta);
}

void Delete() {
    int npm;
    printf("Berapa NPM mahasiswa yang ingin anda hapus datanya? : ");
    scanf("%d", & npm);

    struct Peserta * temp1 = head;
    struct Peserta * temp2 = head;
    while (temp1 != NULL) {

        if (temp1 -> npm == npm) {
            printf("Data mahasiswa dengan NPM %d ditemukan!\n", npm);

            if (temp1 == temp2) {
                //Jika yang ingin dihapus adalah node pertama dari Linked List
                head = head -> next;
                free(temp1);
            } else {
                //Jika node yang ingin dihapus dari Linked List (temp1) memiliki node sebelum node tersebut (temp2)
                temp2 -> next = temp1 -> next;
                free(temp1);
            }

            printf("Data Mahasiswa berhasil dihapus!\n");
            return;

        }

        temp2 = temp1;
        temp1 = temp1 -> next;

    }

    printf("Mahasiswa dengan NPM %d tidak dapat ditemukan!\n", npm);

}

void DeleteList() {
    struct Peserta * prev = head;

    while (head) {
        head = head -> next;
        free(prev);
        prev = head;
    }
}

//F: Binary Tree
void transfer(struct node * root, int option) {
    int npm_peserta;
    struct Peserta * temp = head;

    while (temp != NULL) {
        npm_peserta = temp -> npm;
        root = insertTree(root, npm_peserta);
        temp = temp -> next;
    }

    switch (option) {
    case 1:
        order(root);
        break;
    case 2:
        searchTree(root);
        break;
    case 3:
        deleteTree(root);
        break;
    }

}

void order(struct node * root) {
    int pilihan;
    printf("\nPilih jenis urutan:\n\t1. In-Order\n\t2. Pre-Order\n\t3. Post Order\n\nPilihan: ");
    scanf("%d", & pilihan);

    switch (pilihan) {
        do {
            case 1:
                printf("\n\nUrutan Secara In-Order:\n");
            inOrder(root);
            break;
            case 2:
                printf("\nUrutan Secara Pre-Order:\n");
            preOrder(root);
            break;
            case 3:
                printf("\nUrutan Secara Post-Order:\n");
            postOrder(root);
            break;

            default:
            printf("Input yang Anda masukkan salah!\n\n");
            system("PAUSE");
            system("CLS");
            pilihan = 2;
            continue;
        }
        while (pilihan == 2);
    }
}

void inOrder(struct node * root) {
    int npm;

    if (root != NULL) {
        inOrder(root -> left);
        printf("\nNPM: %d\n", root -> key);
        npm = root -> key;
        dataPrint(npm);
        inOrder(root -> right);
    }
}

void preOrder(struct node * root) {
    int npm;
    if (root != NULL) {
        printf("\nNPM: %d\n", root -> key);
        npm = root -> key;
        dataPrint(npm);
        preOrder(root -> left);
        preOrder(root -> right);
    }
}

void postOrder(struct node * root) {
    int npm;
    if (root != NULL) {
        postOrder(root -> left);
        postOrder(root -> right);
        printf("\nNPM: %d\n", root -> key);
        npm = root -> key;
        dataPrint(npm);
    }
}

void dataPrint(int npm) {
    struct Peserta * temp = head;

    while (temp != NULL) {
        if (temp -> npm == npm) {
            printf("Nama: %s\n", temp -> nama);
            printf("Nilai Akhir: %d\n\n", temp -> nilaiAkhir);
            return;
        }

        temp = temp -> next;
    }
}

int searchTree(struct node * root) {
    int search;
    printf("\nMasukkan NPM yang ingin Anda cek ketersediaannya: ");
    scanf("%d", & search);

    while (root != NULL) {
        if (search < root -> key) {
            root = root -> left;
        } else if (search > root -> key) {
            root = root -> right;
        } else if (search == root -> key) {
            printf("\nHasil: ADA!\n");
            dataPrint(search);
            break;
        }
	}

    if (root == NULL) {
        printf("\nHasil: TIDAK ADA!\n");
    }

}

void deleteTree(struct node * root) {
    if (root == NULL)
        return;

    //hapus sub-tree kiri
    deleteTree(root -> left);

    //hapus sub-tree kanan
    deleteTree(root -> right);

    //hapus root node
    printf("Menghapus NPM : %d\n", root -> key);
    free(root);

    return;
}

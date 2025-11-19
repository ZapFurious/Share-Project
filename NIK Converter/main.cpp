```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NIK_LEN 16
#define MAX_REGIONS 100

// Struktur data wilayah: kode (4 digit string) + nama
typedef struct {
    char code[5];      // e.g., "3171"
    char name[64];     // e.g., "Kota Jakarta Pusat"
} Region;

// Database wilayah sederhana (bisa diperluas)
Region regions[MAX_REGIONS] = {
    {"3171", "Kota Jakarta Pusat"},
    {"3172", "Kota Jakarta Utara"},
    {"3173", "Kota Jakarta Barat"},
    {"3174", "Kota Jakarta Selatan"},
    {"3175", "Kota Jakarta Timur"},
    {"3578", "Kota Surabaya"},
    {"3273", "Kota Bandung"},
    {"1371", "Kota Padang"},
    {"", ""} // sentinel
};

// Fungsi bantu: cek apakah string berisi digit saja
int is_digit_string(const char *s) {
    if (!s) return 0;
    for (int i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

// Cari nama wilayah berdasarkan kode 4-digit awal
const char* lookup_region(const char* code4) {
    for (int i = 0; strlen(regions[i].code) > 0 && i < MAX_REGIONS; i++) {
        if (strncmp(regions[i].code, code4, 4) == 0) {
            return regions[i].name;
        }
    }
    return "Kode wilayah tidak dikenal";
}

// Validasi dan parse tanggal
int parse_date(int day, int month, int year, char *out_str, size_t out_size) {
    // Penyesuaian abad: asumsi 00–25 = 2000–2025, 26–99 = 1926–1999
    if (year >= 0 && year <= 25) year += 2000;
    else if (year >= 26 && year <= 99) year += 1900;
    else return 0; // tahun tidak valid

    // Validasi tanggal sederhana
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    // Array hari per bulan (tanpa leap year untuk kesederhanaan)
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && month == 2) days_in_month[1] = 29; // kasar banget, tapi cukup

    if (day > days_in_month[month - 1]) return 0;

    // Format output: "DD Bulan YYYY"
    const char *bulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };

    snprintf(out_str, out_size, "%02d %s %d", day, bulan[month - 1], year);
    return 1;
}

// Fungsi utama parser NIK
int parse_nik(const char *nik_input, char *output, size_t out_size) {
    if (!nik_input || strlen(nik_input) != NIK_LEN || !is_digit_string(nik_input)) {
        snprintf(output, out_size, "Error: NIK harus 16 digit angka.\n");
        return -1;
    }

    char kode_wilayah[7];
    char tgl_str[7];
    char nomor_urut[5];

    strncpy(kode_wilayah, nik_input, 6); kode_wilayah[6] = '\0';
    strncpy(tgl_str, nik_input + 6, 6); tgl_str[6] = '\0';
    strncpy(nomor_urut, nik_input + 12, 4); nomor_urut[4] = '\0';

    int day = atoi(tgl_str);
    int month = atoi(tgl_str + 2);
    int year = atoi(tgl_str + 4);

    const char *gender = "Laki-laki";
    if (day > 40) {
        gender = "Perempuan";
        day -= 40;
    }

    char tanggal_lahir[64] = "Tanggal tidak valid";
    if (!parse_date(day, month, year, tanggal_lahir, sizeof(tanggal_lahir))) {
        strcpy(tanggal_lahir, "Tanggal tidak valid");
    }

    const char *lokasi = lookup_region(kode_wilayah); // ambil 4 digit pertama

    snprintf(output, out_size,
        "NIK: %s\n"
        "Tanggal Lahir: %s\n"
        "Jenis Kelamin: %s\n"
        "Kode Wilayah: %s\n"
        "Lokasi: %s\n"
        "Nomor Urut: %s\n",
        nik_input,
        tanggal_lahir,
        gender,
        kode_wilayah,
        lokasi,
        nomor_urut
    );

    return 0;
}

// Program utama
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Penggunaan: %s <NIK_16_digit>\n", argv[0]);
        return 1;
    }

    char result[1024];
    if (parse_nik(argv[1], result, sizeof(result)) == 0) {
        printf("%s", result);
    } else {
        fprintf(stderr, "%s", result);
        return 1;
    }

    return 0;
}
```

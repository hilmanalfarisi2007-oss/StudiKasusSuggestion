# Proyek Studi Kasus: Sistem Auto-Complete Berbasis Trie & Linked List

Proyek ini adalah implementasi sistem rekomendasi kata otomatis (*auto-complete/suggestion*) menggunakan gabungan struktur data **Trie** untuk pencarian prefix yang efisien dan **Singly Linked List** untuk menampung serta mengurutkan hasil rekomendasi berdasarkan bobot tertentu.

---

## 📂 Struktur File Proyek

Berdasarkan rancangan arsitektur modular, proyek ini dibagi menjadi beberapa file utama:
*   `AutoComplete.h` : File *header* yang berisi definisi struktur data (`TrieNode`, `RekomendasiNode`, `LinkedList`) dan prototipe fungsi.
*   `AutoComplete.c` : Implementasi lengkap dari seluruh logika fungsi Trie dan Linked List.
*   `main.c` : Driver utama program yang mengatur alur interaksi pengguna, membaca file teks, dan memanggil fungsi modul.

---

## 👥 Pembagian Tugas & Kolaborasi Tim

Proyek ini diselesaikan secara kolaboratif dengan pembagian peran yang terintegrasi sebagai berikut:

### 🧑‍💻 Orang 1 — Struktur Data & Trie Core
Bertanggung jawab atas fondasi dan manajemen memori pohon Trie.
*   `CreateNodeTrie()`: Mengalokasikan node Trie baru dengan inisialisasi anak-anak (`NULL`), status kata, dan bobot.
*   `InsertKata()`: Menyisipkan kata ke dalam Trie huruf per huruf dengan konversi indeks karakter berbasis `kata[i] - 'a'`.
*   `LoadKata()`: Membaca file dataset baris demi baris, menghitung bobot kata berdasarkan posisi baris (`10000 - nomorBaris`), lalu memasukkannya ke Trie.

### 🧑‍💻 Orang 2 — Pencarian & Pengumpulan Rekomendasi
Bertanggung jawab atas algoritma penelusuran kata kunci.
*   `SearchInput()`: Menelusuri Trie berdasarkan input/prefix dari pengguna untuk menemukan node persimpangan terakhir.
*   `AmbilRekomendasi()`: Melakukan *Depth First Search* (DFS) rekursif dari node prefix untuk merangkai semua kata yang valid, lalu mengirimkannya ke Linked List milik Orang 3.

### 🧑‍💻 Orang 3 — Linked List & Output 
Bertanggung jawab menyediakan kontainer penampung hasil, pengurutan, hingga penyajian ke layar.
*   `InitList()`: Menginisialisasi list penampung agar siap digunakan.
*   `InsertList()`: Menyisipkan rekomendasi kata baru dari Orang 2 ke bagian depan list secara dinamis.
*   `SortList()`: Mengurutkan list secara *descending* (bobot tertinggi ke terendah) menggunakan algoritma **Bubble Sort** dengan metode pertukaran data (`Kata` dan `Bobot`) tanpa merusak struktur pointer.
*   `PrintTop10()`: Mencetak maksimal 10 rekomendasi kata teratas yang paling relevan ke layar pengguna.
*   `HapusList()`: Membersihkan memori Linked List setelah pencarian selesai untuk mencegah terjadinya *memory leak*.

---

## 🔄 Alur Kerja Program (Workflow)

1. **Inisialisasi**: Program berjalan -> Orang 1 membaca file kata -> Mengisi Trie secara otomatis dengan bobot dinamis.
2. **Input**: Pengguna memasukkan kata kunci/prefix (misal: `"ap"`).
3. **Pencarian**: Orang 2 melacak prefix di Trie -> Melakukan DFS untuk menjaring semua kata berawalan `"ap"` (misal: *apple, apricot, application*).
4. **Penyimpanan**: Setiap kata yang terjaring otomatis masuk ke Linked List lewat fungsi Orang 3.
5. **Output**: Orang 3 mengurutkan kata tersebut berdasarkan bobot terbesar, menampilkan maksimal 10 data teratas, lalu menghapus list untuk bersiap menerima input pencarian berikutnya.

---

## 🛠️ Cara Kompilasi dan Menjalankan

Gunakan kompiler `gcc` untuk mengompilasi seluruh modul program secara bersamaan lewat terminal:

```bash
# Kompilasi program
gcc main.c AutoComplete.c -o AutoCompleteProgram

# Jalankan program
./AutoCompleteProgram
# keterangan utama
repo bernama welove ini memuat kode pemrograman untuk arduino uno agar dapat berkomunikasi dengan esp 01 sehingga dapat tersambung secara langsung dengan aplikasi.
## alat dan bahan yang digunakan
pada repo ini, saya hanya menggunakan liblarry lcd untuk mengontrol lcd. selebihnya, adalah kodingan yang saya buat sendiri.
## cara kerja
cara kerja repo ini untuk arduino uno. 

=> arduino uno menerima data dari esp01 apakah user telah login, telah melakukan scan tempat sampah, telah melakukan scan sampah, dan telah memasukkan sampah 

=> proses proses tadi akan ditampilkan di tempat sampah dan dari tampilan tersebut user bisa tahu sudah sampai mana proses yang mereka lakukan.

=> pada tahap user memasukkan sampah, tempat sampah mendeteksi sampah dan akan mengirimkan data sampah telah dimasukkan ke esp 01 yang kemudian akan dikirinkan ke database firebase

## keterangan tambahan
=> jika ada yang tidak dimengetri, bisa laporkan di kolom laporan bug dan error pada repo github ini.

=> atau bisa juga mengirimkan pesan ke admin di nomor wa 08988927565
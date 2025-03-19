<?php include_once "layout/header.php"; ?>
<?php include_once "layout/navbar.php"; ?>


<body>
    <div class="container mt-5">
        <h1 class="text-center mb-4"><strong>EmergenCall</strong></h1>
        <h3 class="text-center mb-4"><strong>Hadirkan Keamanan dalam Setiap Panggilan</strong></h3>

        <!-- Tempat untuk menampilkan pesan status -->
        <div id="statusMessage" class="alert alert-info"></div>
        <br>
        <!-- Kontainer untuk tombol -->
        <div class="d-flex justify-content-center">
    <button id="toggleButton" class="btn btn-primary btn-lg py-4 px-6" style="font-size: 24px; padding: 20px 40px;" onclick="ubahStatusLED()">TOMBOL</button>
</div>


    </div>

    <script>
        // Fungsi untuk mengubah status LED
        function ubahStatusLED() {
            fetch('get_status.php')
                .then(response => response.text())
                .then(data => {
                    console.log('Current status:', data); // Debugging
                    const newStatus = data === "1" ? 0 : 1;
                    console.log('New status:', newStatus); // Debugging

                    fetch(`get_status.php?status=${newStatus}`)
                        .then(response => response.text())
                        .then(data => {
                            console.log('Update response:', data); // Debugging
                            const message = newStatus === 1 ? 'Status Emergency Aktif' : 'Status Stand By';
                            document.getElementById('statusMessage').innerText = message;
                            document.getElementById('statusMessage').classList.remove('alert-info', 'alert-success', 'alert-danger');
                            document.getElementById('statusMessage').classList.add(newStatus === 1 ? 'alert-danger' : 'alert-success');
                            document.getElementById('toggleButton').innerText = newStatus === 1 ? 'Matikan' : 'Nyalakan';
                        })
                        .catch(error => console.error('Error updating status:', error));
                })
                .catch(error => console.error('Error fetching status:', error));
        }


        // Fungsi untuk mengambil status LED dari server dan menampilkannya saat halaman dimuat
        function ambilStatusLED() {
            fetch('get_status.php')
                .then(response => response.text())
                .then(data => {
                    let message = data == "1" ? "Status Emergency Aktif" : "Status Stand By";
                    document.getElementById('statusMessage').innerText = message;
                    document.getElementById('statusMessage').classList.remove('alert-info', 'alert-success', 'alert-danger');
                    document.getElementById('statusMessage').classList.add(data == "1" ? 'alert-danger' : 'alert-success');

                    // Update teks tombol sesuai dengan status
                    const buttonText = data == "1" ? 'Nyalakan' : 'Matikan';
                    document.getElementById('toggleButton').innerText = buttonText;
                })
                .catch(error => console.error('Error:', error));
        }

        // Memanggil fungsi ambilStatusLED saat halaman dimuat
        window.onload = ambilStatusLED;
    </script>

</body>

<?php include_once "layout/footer.php"; ?>
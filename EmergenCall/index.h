const char* index_html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Kontrol LED & Buzzer</title>
  <!-- Menambahkan link ke Bootstrap CSS -->
  <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
  <!-- Menambahkan link ke Chart.js -->
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>
  <div class="container mt-5">
    <h2 class="text-center">Kontrol LED dan Buzzer</h2>
    <br>
    <div class="text-center">
      <form action="/toggle" method="POST">
        <button class="btn btn-primary btn-lg" style="font-size: 20px; padding: 15px 30px;">TEKAN TOMBOL</button>
      </form>
    </div>
    <div class="text-center mt-4">
      <p>Status: <span class="badge badge-{{buttonStateBadge}}">{{buttonState}}</span></p>
    </div>

    <!-- Grafik Status LED dan Buzzer -->
    <div class="mt-5">
      <h3>Grafik Status</h3>
      <canvas id="statusChart" width="400" height="200"></canvas>
    </div>

  </div>

  <!-- Menambahkan link ke Bootstrap JS dan Popper.js -->
  <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.1/dist/umd/popper.min.js"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>

  <!-- Menambahkan script untuk mengambil data dan menampilkan grafik -->
  <script>
    // Fungsi untuk mengambil data dari get_data.php
    async function fetchData() {
      const response = await fetch('http://192.168.0.133/UAS_PBM_5/api/get_data.php');
      const data = await response.json();

      const status = [];
      const status_led = [];
      const timestamps = [];

      // Memasukkan data dari hasil query ke grafik
      data.forEach(item => {
        status.push(item.status);
        status_led.push(item.status_led);
        timestamps.push(item.timestamp);
      });

      // Membuat grafik dengan Chart.js
      const ctx = document.getElementById('statusChart').getContext('2d');
      const statusChart = new Chart(ctx, {
        type: 'line',  // Jenis grafik
        data: {
          labels: timestamps, // Waktu untuk sumbu X
          datasets: [{
            label: 'Status LED',
            data: status_led.map(s => s === 'AKTIF' ? 1 : 0),  // Status LED diubah menjadi angka (1 untuk AKTIF, 0 untuk NONAKTIF)
            borderColor: 'rgba(75, 192, 192, 1)',
            borderWidth: 1,
            fill: false,
          }, {
            label: 'Status Tombol',
            data: status.map(s => s === 'Emergency' ? 1 : 0),  // Status Tombol diubah menjadi angka (1 untuk Emergency, 0 untuk Stand By)
            borderColor: 'rgba(153, 102, 255, 1)',
            borderWidth: 1,
            fill: false,
          }]
        },
        options: {
          responsive: true,
          scales: {
            x: {
              title: {
                display: true,
                text: 'Timestamp'
              }
            },
            y: {
              title: {
                display: true,
                text: 'Status'
              },
              ticks: {
                beginAtZero: true,
                max: 1,
                stepSize: 1
              }
            }
          }
        }
      });
    }

    // Memanggil fetchData saat halaman dimuat
    window.onload = fetchData;
  </script>
</body>
</html>
)rawliteral";

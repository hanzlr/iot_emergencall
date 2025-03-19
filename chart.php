<?php include_once "layout/header.php"; ?>
<?php include_once "layout/navbar.php"; ?>

<body>
    <div class="container my-4">
        <h2 class="text-center mb-4">Grafik Status</h2>
        <div class="row justify-content-center">
            <div class="col-12 col-md-8">
                <canvas id="statusChart"></canvas>
            </div>
        </div>
    </div>

    <script>
        const ctx = document.getElementById('statusChart').getContext('2d');

        const statusChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [], // Waktu sebagai X
                datasets: [{
                    label: 'Status',
                    data: [], // Data status
                    borderColor: 'rgba(75, 192, 192, 1)',
                    backgroundColor: 'rgba(75, 192, 192, 0.2)',
                    borderWidth: 2
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: {
                        display: true,
                        position: 'top'
                    }
                },
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
                            stepSize: 1,
                            callback: function (value) {
                                const statusMapping = {
                                    0: "Stand By",
                                    1: "Emergency"
                                };
                                return statusMapping[value] || value;
                            }
                        }
                    }
                }
            }
        });

        // Fungsi untuk fetch data 
        function updateChartData() {
            fetch('get_chart_data.php')
                .then(response => response.json())
                .then(data => {
                    console.log("Data fetched:", data);

                    if (data.error) {
                        alert(`Error fetching data: ${data.error}`);
                        return;
                    }

                    // Konversi status menjadi angka dan timestamp menjadi label
                    const labels = data.map(item => new Date(item.timestamp).toLocaleString()); // Timestamp untuk label X
                    const statusData = data.map(item => {
                        if (item.status === "Emergency") return 1; // Emergency = 1
                        if (item.status === "Stand By") return 0;  // Stand By = 0
                        return null; // Status lain dianggap null
                    });
                    // Perbarui data chart dengan data terbaru
                    statusChart.data.labels = labels;
                    statusChart.data.datasets[0].data = statusData;
                    // chart secara realtime
                    statusChart.update();
                })
                .catch(error => {
                    console.error("Error fetching or displaying data:", error);
                    alert('Error loading data for the chart. Check console for details.');
                });
        }

        // 2 detik
        setInterval(updateChartData, 2000);
        updateChartData();
    </script>
</body>

<?php include_once "layout/footer.php"; ?>
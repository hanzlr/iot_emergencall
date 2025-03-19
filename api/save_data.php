<?php 
include_once "../config/database.php";

date_default_timezone_set('Asia/Jakarta'); // Atur timezone ke WIB (UTC+7)

// Mendapatkan data dari URL
$status = isset($_GET['status']) ? $_GET['status'] : '';
$status_led = isset($_GET['status_led']) ? $_GET['status_led'] : '';

// Menyimpan data ke dalam tabel
$sql = "INSERT INTO status_data (status, status_led) VALUES ('$status', '$status_led')";

if ($conn->query($sql) === TRUE) {
    echo "Data berhasil disimpan";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

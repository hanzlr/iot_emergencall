<?php
include_once "config/database.php";

// Ambil 15 data terakhir berdasarkan timestamp
$sql = "SELECT timestamp, status FROM status_data ORDER BY timestamp DESC LIMIT 15";
$result = $conn->query($sql);

$data = [];
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $data[] = [
            'timestamp' => $row['timestamp'],
            'status' => $row['status']
        ];
    }
}

// Urutkan data berdasarkan timestamp secara ascending setelah mengambil data terbaru
$data = array_reverse($data);

header('Content-Type: application/json');
echo json_encode($data);
?>
<?php
include_once "config/database.php";

// Cek apakah parameter status ada
if (isset($_GET['status'])) {
    $status = $_GET['status'];

    // Update status di database
    $sql = "UPDATE get_status SET status = ? WHERE id = 1";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $status);
    if ($stmt->execute()) {
        echo $status; // Pastikan mengirimkan status yang baru
    } else {
        echo "Error: " . $stmt->error;
    }
} else {
    // Ambil status saat ini
    $sql = "SELECT status FROM get_status WHERE id = 1";
    $result = $conn->query($sql);
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        echo $row['status']; // Pastikan mengirimkan status saat ini
    } else {
        echo "0"; // Default status jika tidak ada data
    }
}

$conn->close();
?>

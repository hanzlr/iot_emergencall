#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "index.h"  // File index.h untuk HTML halaman web
#include <HTTPClient.h>

#define BUZZER 4  // Pin Buzzer
#define LED1 13   // LED Merah
#define LED2 12   // LED Hijau

// Replace with your network credentials
const char* ssid = "BarraIbnuHasan";        // Nama WiFi Anda
const char* password = "barraibnuhasan12";  // Password WiFi Anda

AsyncWebServer server(80);  // Inisialisasi web server pada port 80

bool buttonState = false;          // Status tombol di web server
bool previousButtonState = false;  // Status tombol sebelumnya

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);

  // Mengatur pin sebagai output
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());  // Menampilkan IP address ESP32

  // Menyiapkan root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = String(index_html);  // Menggunakan konten dari index.h
    html.replace("{{buttonState}}", buttonState ? "AKTIF" : "NONAKTIF");
    html.replace("{{buttonStateBadge}}", buttonState ? "success" : "danger");
    request->send(200, "text/html", html);
  });

  // Menangani tombol ditekan
  server.on("/toggle", HTTP_POST, [](AsyncWebServerRequest* request) {
    buttonState = !buttonState;  // Toggle status tombol
    request->redirect("/");      // Redirect kembali ke halaman utama
  });

  // Memulai server
  server.begin();
}

void loop() {
  // Kontrol LED dan Buzzer berdasarkan status tombol
  String status;
  String statusled;
  
  // Periksa jika tombol berubah
  if (buttonState != previousButtonState) {
    // Perbarui status berdasarkan nilai buttonState yang baru
    if (buttonState) {
      digitalWrite(LED1, HIGH);  // LED Merah menyala
      digitalWrite(LED2, LOW);   // LED Hijau mati
      tone(BUZZER, 1000);        // Buzzer berbunyi dengan frekuensi 1000 Hz
      status = "Emergency";
      statusled = "Aktif";
    } else {
      digitalWrite(LED1, LOW);   // LED Merah mati
      digitalWrite(LED2, HIGH);  // LED Hijau menyala
      noTone(BUZZER);            // Buzzer mati
      status = "Stand%20By";
      statusled = "Stand%20By";
    }

    // Kirimkan data ke server hanya jika status tombol berubah
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String serverPath = "http://192.168.0.133/UAS_PBM_5/api/create.php?status=" + status + "&status_led=" + statusled;  // Kirim status dan status_led
      Serial.print("Requesting URL: ");
      Serial.println(serverPath);

      http.begin(serverPath);             // Start HTTP
      int httpResponseCode = http.GET();  // Permintaan GET

      // Debugging: Cek kode respon HTTP
      if (httpResponseCode > 0) {
        String response = http.getString();  // Get respon
        Serial.println(httpResponseCode);    // Kode respon
        Serial.println(response);            // Respon server
      } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode);
      }
      http.end();  // Close koneksi
    } else {
      Serial.println("WiFi Disconnected");
    }

    // Update status tombol sebelumnya
    previousButtonState = buttonState;
  }
}



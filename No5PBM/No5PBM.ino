#include <WiFi.h>
#include <HTTPClient.h>

#define BUZZER 4  // Pin Buzzer
#define LED1 13   // LED Merah
#define LED2 12   // LED Hijau

// Gantilah dengan kredensial WiFi Anda
const char* ssid = "BarraIbnuHasan";        // Nama WiFi Anda
const char* password = "barraibnuhasan12";  // Password WiFi Anda

// Endpoint server
const char* statusServer = "http://192.168.0.133/UAS_PBM_5/get_status.php";

// Variabel untuk status
String status;
String statusled;

// Variabel untuk menyimpan status terakhir
String lastStatus = "";
String lastStatusLed = "";

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
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Mengambil status dari server
    http.begin(statusServer);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Response dari server: ");
      Serial.println(response);

      if (response == "1") {
        // Jika status Emergency
        digitalWrite(LED1, HIGH);  // LED Merah menyala
        digitalWrite(LED2, LOW);   // LED Hijau mati
        tone(BUZZER, 1000);        // Buzzer berbunyi dengan frekuensi 1000 Hz
        status = "Emergency";
        statusled = "Aktif";
      } else {
        // Jika status Stand By
        digitalWrite(LED1, LOW);   // LED Merah mati
        digitalWrite(LED2, HIGH);  // LED Hijau menyala
        noTone(BUZZER);            // Buzzer mati
        status = "Stand%20By";
        statusled = "Stand%20By";
      }

      // Cek apakah status telah berubah
      if (status != lastStatus || statusled != lastStatusLed) {
        // Kirim status dan status_led ke server hanya jika ada perubahan
        String serverPath = "http://192.168.0.133/UAS_PBM_5/api/save_data.php?status=" + status + "&status_led=" + statusled;
        Serial.print("Requesting URL: ");
        Serial.println(serverPath);

        http.begin(serverPath);  // Mulai HTTP Request
        int saveDataResponseCode = http.GET(); // Permintaan GET untuk menyimpan data

        // Debugging: Cek kode respon HTTP
        if (saveDataResponseCode > 0) {
          String saveDataResponse = http.getString();
          Serial.println(saveDataResponseCode); // Kode respon
          Serial.println(saveDataResponse);     // Respon server
        } else {
          Serial.print("Error on HTTP request: ");
          Serial.println(saveDataResponseCode);
        }

        http.end();  // Menutup koneksi HTTP

        // Update status terakhir yang telah dikirim
        lastStatus = status;
        lastStatusLed = statusled;
      }
    } else {
      Serial.println("WiFi Disconnected");
    }
  }

  delay(1000);  // Delay sebelum melakukan request berikutnya
}

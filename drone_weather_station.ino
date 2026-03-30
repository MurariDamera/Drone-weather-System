#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

// DHT11 Settings
#define DHTPIN 4       // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);


Adafruit_BMP085 bmp;


#define RAIN_PIN 33  

#define LDR_PIN 34   

// WiFi Settings
const char* ssid = "Htspt";   // Wi-Fi SSID
const char* password = "murarimcc"; // Wi-Fi Password

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Initialize DHT11
  dht.begin();
  
  // Initialize BMP180
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }

  // Initialize Rain Sensor Pin
  pinMode(RAIN_PIN, INPUT);

  // Initialize LDR Pin
  pinMode(LDR_PIN, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // Start the server
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  // Wait for a client to connect
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    String request = client.readStringUntil('\r');
    client.flush();

    // Get sensor data
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    float pressure = bmp.readPressure() / 100.0;  // Convert to hPa
    int rain = digitalRead(RAIN_PIN);
    int light_intensity = analogRead(LDR_PIN);

    // Send data to client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<html>");
    client.println("<head><title>ESP32 Weather Station</title></head>");
    client.println("<body>");
    client.println("<h1>Weather Station Data</h1>");
    client.print("<p>Temperature: ");
    client.print(temp);
    client.println(" °C</p>");
    client.print("<p>Humidity: ");
    client.print(humidity);
    client.println(" %</p>");
    client.print("<p>Pressure: ");
    client.print(pressure);
    client.println(" hPa</p>");
    client.print("<p>Rain: ");
    client.println(rain == HIGH ? "No" : "Yes");
    client.println("</p>");
    client.print("<p>Light Intensity: ");
    client.print(light_intensity);
    client.println("</p>");
    client.println("</body>");
    client.println("</html>");
    
    client.stop();
    Serial.println("Client disconnected.");
  }
}

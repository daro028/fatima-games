/*
 * Arcade Micro - Servidor Web para ESP32-C3 / ESP32-S3
 * Juegos incluidos:
 * 1. Lights Out (index.html)
 * 2. Flow Free  (flow.html)
 * 3. Panel Admin (admin.html)
 * 
 * Funcionalidad:
 * - Crea su propia red Wi-Fi: "Juegos-Fatima"
 * - Acceso directo desde cualquier dispositivo en:
 *   http://192.168.4.1/  (Lights Out)
 *   http://192.168.4.1/flow.html (Flow Free)
 *   http://192.168.4.1/admin.html (Admin)
 * - LittleFS para almacenamiento de puntajes en Flash.
 */

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <LittleFS.h>

// ================= CONFIGURACIÓN DE RED =================
const bool MODO_PUNTO_DE_ACCESO = true;

const char* AP_SSID = "Juegos-Fatima";
const char* AP_PASS = ""; // Red abierta

const char* WIFI_SSID = "TU_WIFI_AQUI";
const char* WIFI_PASS = "TU_CONTRASENA_AQUI";

const String ADMIN_PIN = "1234";

// ================= SERVIDORES =================
WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;

// Declaración de archivos HTML embebidos en PROGMEM
extern const char INDEX_HTML[] PROGMEM;
extern const char FLOW_HTML[] PROGMEM;
extern const char ADMIN_HTML[] PROGMEM;

const char* SCORES_FILE = "/scores.json";

// ================= RUTAS HTTP =================
void handleRoot() {
  server.send_P(200, "text/html", INDEX_HTML);
}

void handleFlow() {
  server.send_P(200, "text/html", FLOW_HTML);
}

void handleAdmin() {
  server.send_P(200, "text/html", ADMIN_HTML);
}

void handleGetScores() {
  if (LittleFS.exists(SCORES_FILE)) {
    File f = LittleFS.open(SCORES_FILE, "r");
    server.streamFile(f, "application/json");
    f.close();
  } else {
    server.send(200, "application/json", "[]");
  }
}

void handlePostScores() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    File f = LittleFS.open(SCORES_FILE, "w");
    if (f) {
      f.print(body);
      f.close();
      server.send(200, "application/json", "{\"status\":\"ok\"}");
      return;
    }
  }
  server.send(500, "application/json", "{\"error\":\"write_failed\"}");
}

void handleClearScores() {
  String key = server.arg("key");
  if (key == ADMIN_PIN) {
    File f = LittleFS.open(SCORES_FILE, "w");
    if (f) {
      f.print("[]");
      f.close();
      server.send(200, "application/json", "{\"status\":\"cleared\"}");
      return;
    }
  }
  server.send(403, "application/json", "{\"error\":\"unauthorized\"}");
}

void handleNotFound() {
  if (MODO_PUNTO_DE_ACCESO) {
    server.sendHeader("Location", "http://192.168.4.1/", true);
    server.send(302, "text/plain", "");
  } else {
    server.send(404, "text/plain", "404: Not found");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- Iniciando Servidor de Juegos Fatima (ESP32) ---");

  if (!LittleFS.begin(true)) {
    Serial.println("Error al montar LittleFS");
  } else {
    Serial.println("LittleFS montado correctamente.");
  }

  if (MODO_PUNTO_DE_ACCESO) {
    WiFi.mode(WIFI_AP);
    if (strlen(AP_PASS) > 0) {
      WiFi.softAP(AP_SSID, AP_PASS);
    } else {
      WiFi.softAP(AP_SSID);
    }

    IPAddress IP = WiFi.softAPIP();
    Serial.print("Punto de Acceso: ");
    Serial.println(AP_SSID);
    Serial.print("Direccion IP: http://");
    Serial.println(IP);

    dnsServer.start(DNS_PORT, "*", IP);
  } else {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Conectando a Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConectado!");
    Serial.print("IP Local: http://");
    Serial.println(WiFi.localIP());
  }

  if (MDNS.begin("juegos")) {
    Serial.println("mDNS iniciado: http://juegos.local");
  }

  // Rutas de Juegos
  server.on("/", HTTP_GET, handleRoot);
  server.on("/index.html", HTTP_GET, handleRoot);
  server.on("/flow", HTTP_GET, handleFlow);
  server.on("/flow.html", HTTP_GET, handleFlow);
  server.on("/admin", HTTP_GET, handleAdmin);
  server.on("/admin.html", HTTP_GET, handleAdmin);

  // API REST para puntajes
  server.on("/api/scores", HTTP_GET, handleGetScores);
  server.on("/api/scores", HTTP_POST, handlePostScores);
  server.on("/api/scores/clear", HTTP_POST, handleClearScores);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP listo. ¡A jugar!");
}

void loop() {
  if (MODO_PUNTO_DE_ACCESO) {
    dnsServer.processNextRequest();
  }
  server.handleClient();
  delay(2);
}

// Carga de archivos HTML compilados en Flash
#include "index_html.h"
#include "flow_html.h"
#include "admin_html.h"

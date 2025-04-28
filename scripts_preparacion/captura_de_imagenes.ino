#include <WiFi.h>
#include "VideoStream.h"
#include "AmebaFatFS.h"

#define CHANNEL 0
#define INTERVAL 1000  // 1.5 segundos entre capturas

VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);  // JPEG para HTTP y almacenamiento

char ssid[] = "A55 de Juan";  // Tu red Wi-Fi
char pass[] = "12345678";

int status = WL_IDLE_STATUS;
WiFiServer server(80);

AmebaFatFS fs;

uint32_t img_addr = 0;
uint32_t img_len = 0;
uint32_t count = 500;
unsigned long lastCapture = 0;

void sendImage(WiFiClient& client, uint8_t* buf, uint32_t len)
{
    char header[128];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %lu\r\n\r\n", len);
    client.write((const uint8_t*)header, header_len);
    client.write(buf, len);
}

void setup()
{
    Serial.begin(115200);

    // Conexión Wi-Fi
    while (status != WL_CONNECTED) {
        Serial.print("Conectando a WiFi: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(3000);
    }

    Serial.println("WiFi conectado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Inicializar cámara
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    // Inicializar servidor HTTP
    server.begin();

    // Inicializar microSD
    if (!fs.begin()) {
        Serial.println("Fallo al inicializar el sistema de archivos");
    } else {
        Serial.println("microSD inicializada correctamente");
    }
}

void loop()
{
    // Captura y guarda imagen cada 3 segundos
    unsigned long currentMillis = millis();
    if (currentMillis - lastCapture >= INTERVAL) {
        lastCapture = currentMillis;

        Camera.getImage(CHANNEL, &img_addr, &img_len);

        // Crear nombre de archivo
        char filename[64];
        snprintf(filename, sizeof(filename), "%simage_%04d.jpg", fs.getRootPath(), count);

        File file = fs.open(filename);
        if (file) {
            file.write((uint8_t *)img_addr, img_len);
            file.close();
            sprintf("Imagen guardada: %s\n", filename);
            count++;
        } else {
            sprintf("Error al guardar imagen: %s\n", filename);
        }
    }

    // Atender peticiones HTTP para mostrar la imagen en navegador
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Cliente HTTP conectado");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        Camera.getImage(CHANNEL, &img_addr, &img_len);
                        sendImage(client, (uint8_t*)img_addr, img_len);
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        client.stop();
        Serial.println("Cliente desconectado");
    }
}

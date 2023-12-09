#include <WiFi.h>
#include <HTTPClient.h>
#include<ESP32Servo.h>
#include<Arduino_JSON.h>
#include<base64.h>
#include <FS.h>
#include "UltraSonic.h"
#include "Controller.h"
#include "ServoC.h"
#include "Alarm.h"

void parseJsonString(String jsonString, String& mostConfidentLabel, double& confidence) {
  int index = jsonString.indexOf(',');
  mostConfidentLabel = jsonString.substring(26, index-1);
  confidence = jsonString.substring(index+16, jsonString.length()-1).toDouble();
}

UltraSonic ultrasonic(2, 4);
ServoC servo(23);
Alarm alarmC(5);

const char *ssid = "LT";
const char *password = "prudencio";

/* const char* ssid = "LTR";
const char* password = "2J8LQV5L"; */

// const char* serverUrl = "https://shark-app-ko77v.ondigitalocean.app/web/sendImg/";
const char* serverUrl = "http://192.168.163.193:8000/web/sendImg/";
const char* contentType = "application/json";
// const char* contentType = "application/x-www-form-urlencoded";
const char* cameraServer = "http://192.168.163.129/capture";

void setup() {
  // put your setup code here, to run once:+
  ultrasonic.begin();
  servo.begin();
  alarmC.begin();
  WiFi.begin(ssid, password);
  Serial.begin(19200);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }
}

bool find = false;
int factor = 1;
byte angle = 20;
byte cont = 0;

void loop() {
  int d = ultrasonic.getDistance();
  find = d>=0 && d<=20;
  delay(500);
  if (find) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(cameraServer);

      int httpCode = http.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          String image_data = http.getString();
          http.end();
          http.begin(serverUrl);
          http.addHeader("Content-Type", contentType);
          String payload = "{\"frame\":\"" + base64::encode((uint8_t*)image_data.c_str(), image_data.length()) + "\"}";
          int httpResponseCode = http.POST(payload);
          String response = http.getString();
          Serial.print("HTTP Response Code: ");
          Serial.println(httpResponseCode);
          Serial.print("Response: ");
          Serial.println(response);
          String mostConfidentLabel;
          double confidence;
          parseJsonString(response, mostConfidentLabel, confidence);
          /* Serial.println(mostConfidentLabel);
          Serial.println(confidence); */
          http.end();
          if (mostConfidentLabel == "person" && confidence > 0.7) {
            alarmC.tick();
          }
        } else {
          Serial.println("Error en la solicitud HTTP");
        }
      } else {
        Serial.println("Error en la conexión HTTP");
      }

    }
    /* if (WiFi.status() == WL_CONNECTED) {
      alarmC.tick();
      HTTPClient http;
      http.begin(cameraServer);

      int httpCode = http.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          const int bufferSize = 1024;
          uint8_t buffer[bufferSize];
          size_t bytesRead;
          // Descargar los datos binarios de la imagen directamente
          WiFiClient *stream = http.getStreamPtr();
          memset(buffer, 0, bufferSize);
          bytesRead = stream->readBytes(buffer, bufferSize);

          // Codificar los datos en base64
          String image_data_base64 = base64::encode(buffer, bytesRead);

          http.end();

          // Realizar la solicitud POST al servidor Django con los datos codificados en base64
          http.begin(serverUrl);
          http.addHeader("Content-Type", contentType);
          String payload = "frame=" + image_data_base64;
          int httpResponseCode = http.POST(payload);
          String response = http.getString();
          Serial.print("HTTP Response Code: ");
          Serial.println(httpResponseCode);
          Serial.print("Response: ");
          Serial.println(response);
          http.end();
        } else {
          Serial.println("Error en la solicitud HTTP");
        }
      } else {
        Serial.println("Error en la conexión HTTP");
      }
    } */
    /* if (WiFi.status() == WL_CONNECTED) {
      alarmC.tick();
      
      HTTPClient http;
      http.begin(cameraServer);

      int httpCode = http.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          String image_data = http.getString();
          http.end();
          http.begin(serverUrl);
          http.addHeader("Content-Type", contentType);
          String payload = "{\"frame\": " + image_data + "}";
          int httpResponseCode = http.POST(payload);
          String response = http.getString();
          Serial.print("HTTP Response Code: ");
          Serial.println(httpResponseCode);
          Serial.print("Response: ");
          Serial.println(response);
          http.end();
        } else {
          Serial.println("Error en la solicitud HTTP");
        }
      } else {
        Serial.println("Error en la conexión HTTP");
      }

    } */
    cont=0;
  } else {
    if (cont==5) {
      angle += factor*40;
      servo.move(angle, factor);
      if (angle == 140) {
        factor = -1;
      }
      if (angle==20) {
        factor =1;
      }
      cont=0;
    } else {
      cont++;
    }
  }
}
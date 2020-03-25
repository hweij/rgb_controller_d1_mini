#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#include "controller.html.h"
#include "manifest.json.h"
#include "favicon.ico.h"
#include "icon.png.h"

const char *ssid = "TMNL-818E4D";
const char *password = "DSC8ZLKGLKYFT7";
const char *hostname = "rgbcontroller";
const uint8_t addr[]{192, 168, 1, 99};

IPAddress ipaddress(addr[0], addr[1], addr[2], addr[3]);
IPAddress gateway(addr[0], addr[1], addr[2], 1);
IPAddress subnet(255, 255, 255, 0);

int ledPin = LED_BUILTIN;
WiFiServer server(80);

int LED_R = D5;
int LED_G = D6;
int LED_B = D7;

class Color {
  public:
    int r,g,b;

    Color(): Color(0,0,0) { }

    Color(int r, int g, int b) {
      Color::r = r;
      Color::g = g;
      Color::b = b;
    }
};

// The step factor determines how much values will be increased at every step.
// The increment will be equal to interp * stepFactor, so the step will increase
// as the value increases. This creates an exponential behaviour, which is
// more logical than linear.
const float stepFactor = 0.1f;
Color cFrom, cTo;
// We interpolate over the max component (max delta of r, g, or b)
// Interpolation is done when interp != interpTo
float interpFrom = 0, interpTo = 0, interp = 0;

// For timing
unsigned long curTime = 0;
// Interval for each tick in milliseconds, 20ms = 50hz
const int animInterval = 20;

// Interpolates the from and two colors, based on the interpolation values.
// It returns the interpolated color.
Color interpColor() {
  if (interp == interpTo) {
    return cTo;
  }
  else {
    if (interp == interpFrom) {
      return cFrom;
    }
    else {
      float span = interpTo - interpFrom;
      if (span == 0) {
        return cFrom;
      }
      else {
        float f = (interp - interpFrom) / span;
        return Color(
          (int)((cTo.r - cFrom.r) * f + cFrom.r),
          (int)((cTo.g - cFrom.g) * f + cFrom.g),
          (int)((cTo.b - cFrom.b) * f + cFrom.b)
        );
      }
    }
  }
}

void rgbOut(int r, int g, int b) {
    analogWrite(LED_R, r);
    analogWrite(LED_G, g);
    analogWrite(LED_B, b);
}

void rgbOut(Color c) {
  rgbOut(c.r, c.g, c.b);
}

// Handle interpolation
void doInterp() {
  if (interp != interpTo) {
    unsigned long t = millis();
    if ((t - curTime) >= animInterval) {
      curTime += animInterval;
      // Make sure we do not lag behind
      if ((t - curTime) >= animInterval) {
        // Catch up
        curTime = t;
      } 
      float delta = (interp + 1) * stepFactor;
      if (interpFrom < interpTo) {
        interp += delta;
        if (interp > interpTo)
          interp = interpTo;  // Stops interpolation
      }
      else {
        interp -= delta;
        if (interp < interpTo)
          interp = interpTo;  // Stops interpolation
      }
      rgbOut(interpColor());
    }
  }
}

void initOTA()
{
  // ArduinoOTA.setHostname("esp8266LEDString");
  ArduinoOTA.onStart([]() {
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.printf("Start updating %s\n",
      (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    const char *msg;
    switch (error) {
      case OTA_AUTH_ERROR:
        msg = "Auth Failed";
        break;
      case OTA_BEGIN_ERROR:
        msg = "Begin Failed";
        break;
      case OTA_CONNECT_ERROR:
        msg = "Connect Failed";
        break;
      case OTA_RECEIVE_ERROR:
        msg = "Receive Failed";
        break;
      case OTA_END_ERROR:
        msg = "End Failed";
        break;
      default:
        msg = "Unknown error";
        break;
    }
    Serial.println(msg);
  });
  ArduinoOTA.begin();
}

void writeHeader200_OK(WiFiClient client, const char *mime) {
// Return the response
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(mime);
  client.println("Connection: close");
}

void sendHeader(WiFiClient client, const char *mime) {
  // Return the response
  writeHeader200_OK(client, mime);
  client.println("");
}

void sendData(WiFiClient client, const char *mime, uint8_t data[], int data_length) {
  // Return the response
  writeHeader200_OK(client, mime);
  client.print("Content-Length: ");
  client.println(data_length);
  client.println("");
  client.write((const char *)data, data_length);
}

void handleWebRequests() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data

  int timeOut = 500;
  while (!client.available())
  {
    timeOut--;
    if (timeOut <= 0)
      break;
    delay(1);
  }

  bool handled = false;

  // String request = "";
  const int REQ_BUFFER_SIZE = 100;
  uint8_t requestBuffer[REQ_BUFFER_SIZE];
  if (client.available())
  {
    // Read the first line of the request
    // request = client.readStringUntil('\r');

    int b;
    int index = 0;
    while (index < (REQ_BUFFER_SIZE - 1)) {
      b = client.read();
      if ((b > 0) && (b != '\r')) {
        requestBuffer[index++] = (uint8_t)b;
      }
    }
    requestBuffer[index] = 0; // Terminating zero

    // client.flush();

    // Match the request

    if (strncmp((const char *)requestBuffer, "GET ", 4) == 0)
    {
      char * url = (char *)requestBuffer + 4;
      // Main page: controller
      if (strncmp(url, "/ ", 2) == 0)
      {
        // *** Root: display the application
        sendHeader(client, "text/html");
        client.println("<!DOCTYPE HTML>");
        client.println(controller_html);
        handled = true;
      }

      if (strncmp(url, "/manifest.json", 14) == 0)
      {
        // *** Server manifest file
        sendHeader(client, "application/json");
        client.println(manifest_html);
        handled = true;
      }

      // Favicon
      if (strncmp(url, "/favicon.ico", 12) == 0) {
        sendData(client, "image/x-icon", favicon_data, favicon_data_length);
      }

      // Icon
      if (strncmp(url, "/icon.png", 9) == 0) {
        sendData(client, "image/png", icon_data, icon_data_length);
      }

      // Request for RGB values: /api/set, ex: /api/set0,20,1023
      // int rval = -1, gval = -1, bval = -1;
      if (strncmp(url, "/api/set", 8) == 0)
      {
                // API call, return json result
        sendHeader(client, "application/json");
        // Find boundaries for r, g, b
        char *params = url + 8;

        char *rString = params;
        char *rEnd = strchr(rString, ',');
        if (rEnd != NULL)
        {
          rEnd[0] = 0;  // Terminate r
          char *gString = rEnd + 1;
          char *gEnd = strchr(gString, ',');
          if (gEnd != NULL)
          {
            // RGB OK, set interpolation
            gEnd[0] = 0;
            char *bString = gEnd + 1;

            int r = atoi(rString);
            int g = atoi(gString);
            int b = atoi(bString);
            cFrom = interpColor();  // Start where you are now
            cTo = Color(r, g, b);
            // Find the largest component
            float dr = abs(cTo.r - cFrom.r);
            float dg = abs(cTo.g - cFrom.g);
            float db = abs(cTo.b - cFrom.b);
            if (dr >= dg) {
              if (dr >= db) {
                // Red
                interpFrom = cFrom.r;
                interpTo = cTo.r;
              }
              else {
                // Blue
                interpFrom = cFrom.b;
                interpTo = cTo.b;
              }
            }
            else {
              if (dg >= db) {
                // Green
                interpFrom = cFrom.g;
                interpTo = cTo.g;
              }
              else {
                // Blue
                interpFrom = cFrom.b;
                interpTo = cTo.b;
              }
            }
            // Start interpolation if cFrom and cTo differ
            interp = interpFrom;

            client.printf("{ \"result\":\"OK\", \"r\":%d, \"g\":%d, \"b\":%d }", cTo.r, cTo.g, cTo.b);
            handled = true;
          }
        }
        if (!handled) {
          client.print("{ \"result\":\"ERROR\", \"detail\":\"Invalid set command\" }");
          handled = true;
        }
      }
    }
  }

  if (!handled) {
    sendHeader(client, "text/html");
    client.println("<!DOCTYPE HTML>");
    client.print("<html>Unknown request: [");
    client.print((char *)requestBuffer);
    client.println("]");
    client.print("Rest of the input: [");
    client.print(client.readString());
    client.println("]\n</html>");
  }

  // delay(1);
}

void setup()
{
  // pinMode(ledPin, OUTPUT);
  // digitalWrite(ledPin, LOW);

  // LEDs off
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  analogWriteFreq(500); // PWM freq for LEDs

  // Faint red to indicate the processor has started
  rgbOut(1, 0, 0);

  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.config(ipaddress, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //  }

  initOTA();

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  rgbOut(0, 1, 0);  // Green indicates the server has started

  // digitalWrite(ledPin, LOW);
}

// int toggle = 0;

void loop()
{
  ArduinoOTA.handle();

  // Interpolation and output of RGB
  doInterp();

  // Web requests, set interpolation target
  handleWebRequests();

  // digitalWrite(ledPin, toggle);
  // toggle = 1 - toggle;
}

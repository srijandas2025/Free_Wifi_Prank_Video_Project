#include <WiFi.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char* ssid = "Free_5G_WiFi_Click_Me";

const byte DNS_PORT = 53;

IPAddress apIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

DNSServer dnsServer;
AsyncWebServer server(80);


// ================= WEB PAGE =================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta name="viewport"
      content="width=device-width, initial-scale=1">

<title>Free 5G WiFi</title>

<style>

* {
  box-sizing: border-box;
}

body {
  margin: 0;
  background: #000;
  color: white;
  font-family: Arial, sans-serif;

  min-height: 100vh;

  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}

video {
  width: 95%;
  max-width: 600px;

  border-radius: 12px;

  background: #000;
}

h2 {
  margin-top: 20px;
}

</style>

</head>


<body>

<video
  id="video"
  controls
  playsinline
  preload="auto">

  <source
    src="/video.mp4"
    type="video/mp4">

  Your browser does not support HTML5 video.

</video>


<h2>😂 Got You!</h2>


<script>

const video = document.getElementById("video");

video.addEventListener("loadedmetadata", () => {
    console.log("Video duration:", video.duration);
});

video.addEventListener("error", () => {
    console.log("Video loading error:", video.error);
});

</script>

</body>

</html>
)rawliteral";


// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 Free WiFi Portal");
  Serial.println("==============================");


  // ================= LITTLEFS =================

  if (!LittleFS.begin(true)) {

    Serial.println("LittleFS FAILED!");

    return;

  }

  Serial.println("LittleFS OK");


  // ================= CHECK VIDEO =================

  if (LittleFS.exists("/video.mp4")) {

    File video = LittleFS.open("/video.mp4", "r");

    if (video) {

      Serial.println("Video found!");

      Serial.print("Video size: ");
      Serial.print(video.size());
      Serial.println(" bytes");

      video.close();

    }

  } else {

    Serial.println();
    Serial.println("ERROR: video.mp4 NOT FOUND!");
    Serial.println("Make sure:");
    Serial.println("data/video.mp4");
    Serial.println();

  }


  // ================= WIFI ACCESS POINT =================

  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(
    apIP,
    gateway,
    subnet
  );

  WiFi.softAP(ssid);


  Serial.println();
  Serial.println("WiFi Started!");

  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());


  // ================= DNS CAPTIVE PORTAL =================

  dnsServer.start(
    DNS_PORT,
    "*",
    apIP
  );


  // ================= MAIN PAGE =================

  server.on(
    "/",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      request->send_P(
        200,
        "text/html",
        index_html
      );

    }
  );


  // ================= VIDEO =================

  server.on(
    "/video.mp4",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      Serial.println("Video requested");

      if (!LittleFS.exists("/video.mp4")) {

        Serial.println("Video file missing!");

        request->send(
          404,
          "text/plain",
          "video.mp4 not found"
        );

        return;

      }


      File video = LittleFS.open(
        "/video.mp4",
        "r"
      );


      if (!video) {

        Serial.println("Could not open video!");

        request->send(
          500,
          "text/plain",
          "Could not open video"
        );

        return;

      }


      size_t fileSize = video.size();

      video.close();


      Serial.print("Sending video: ");
      Serial.print(fileSize);
      Serial.println(" bytes");


      AsyncWebServerResponse *response =
        request->beginResponse(
          LittleFS,
          "/video.mp4",
          "video/mp4"
        );


      response->addHeader(
        "Accept-Ranges",
        "bytes"
      );

      response->addHeader(
        "Cache-Control",
        "no-cache"
      );

      response->addHeader(
        "Access-Control-Allow-Origin",
        "*"
      );


      request->send(response);

    }
  );


  // ================= DEBUG FILE SIZE =================

  server.on(
    "/video-info",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      if (!LittleFS.exists("/video.mp4")) {

        request->send(
          404,
          "text/plain",
          "video.mp4 not found"
        );

        return;

      }


      File video =
        LittleFS.open("/video.mp4", "r");


      String info =
        "Video exists\n";

      info +=
        "Size: ";

      info +=
        String(video.size());

      info +=
        " bytes\n";

      video.close();


      request->send(
        200,
        "text/plain",
        info
      );

    }
  );


  // ================= ANDROID CAPTIVE PORTAL =================

  server.on(
    "/generate_204",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      request->redirect("/");

    }
  );


  // ================= APPLE CAPTIVE PORTAL =================

  server.on(
    "/hotspot-detect.html",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      request->redirect("/");

    }
  );


  // ================= WINDOWS =================

  server.on(
    "/ncsi.txt",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      request->redirect("/");

    }
  );


  server.on(
    "/connecttest.txt",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {

      request->redirect("/");

    }
  );


  // ================= OTHER REQUESTS =================

  server.onNotFound(
    [](AsyncWebServerRequest *request) {

      request->redirect("/");

    }
  );


  // ================= START SERVER =================

  server.begin();

  Serial.println();
  Serial.println("Web server started!");
  Serial.println("==============================");

}


// ================= LOOP =================

void loop() {

  dnsServer.processNextRequest();

}
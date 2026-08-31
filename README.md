# Free_Wifi_Prank_Video_Project
# 📱 ESP32 Free Wi-Fi Captive Portal + Video

A fun ESP32 project that creates its own Wi-Fi network and displays a locally stored MP4 video when a phone connects to the ESP32 Wi-Fi.

The ESP32 works as a Wi-Fi Access Point (AP), runs a DNS captive portal, hosts a web page using ESPAsyncWebServer, and serves an MP4 video stored in the ESP32's LittleFS filesystem.

> ⚠️ This project is intended for educational, experimental and authorized demonstration purposes.

---

## 🎯 Project Idea

The basic idea is:

Phone
  ↓
Connects to ESP32 Wi-Fi
  ↓
ESP32 creates a captive portal
  ↓
Phone is redirected to the ESP32 web page
  ↓
Web page requests /video.mp4
  ↓
ESP32 reads video from LittleFS
  ↓
Video is streamed to the phone
  ↓
😂 "Got You!"

The ESP32 does not need an internet connection for this.

The phone communicates directly with the ESP32 over its local Wi-Fi network.

---

# ✨ Features

- 📡 ESP32 works as a Wi-Fi Access Point
- 🌐 Captive portal using DNS redirection
- 📱 Designed for phones and other Wi-Fi devices
- 🎬 Local MP4 video hosting
- 💾 Video stored in ESP32 LittleFS
- ⚡ Async web server
- 🔍 Video file existence/size debugging endpoint
- 🤖 Android captive portal route
- 🍎 Apple captive portal route
- 🪟 Windows captive portal routes
- 📱 Responsive webpage
- 😂 Custom "Got You!" message

---

# 🧰 Hardware Required

## Required Hardware

- ESP32 development board
- USB data cable
- Computer/laptop
- Smartphone for testing
- MP4 video file

No external sensors or additional electronic components are required.

---

# 💻 Software Required

## Arduino IDE

This project was developed/tested using:

- Arduino IDE 2.3.10
- ESP32 Dev Module

Arduino IDE can be downloaded from:

https://www.arduino.cc/en/software/

---

# 📦 ESP32 Board Package

Open Arduino IDE.

Go to:

Tools → Board → Boards Manager

Search:

esp32

Install:

ESP32 by Espressif Systems

Then select:

Tools → Board → ESP32 Arduino → ESP32 Dev Module

---

# 📚 Required Libraries

The project uses:


#include <WiFi.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

Required external libraries
1. ESPAsyncWebServer

Use:

ESPAsyncWebServer by ESP32Async

Repository:

https://github.com/ESP32Async/ESPAsyncWebServer

2. AsyncTCP

Use:

AsyncTCP by ESP32Async

Repository:

https://github.com/ESP32Async/AsyncTCP

⚠️ IMPORTANT: ESP32 vs ESP8266

This project is for ESP32.

For ESP32 use:

ESPAsyncWebServer
AsyncTCP

Do NOT use:

ESPAsyncTCP

ESPAsyncTCP is associated with ESP8266 projects.

Using the wrong library can cause compilation errors or compatibility problems.

🗂️ Project Folder Structure

The project should have this structure:

FreeWiFi/
│
├── FreeWiFi.ino
│
└── data/
    │
    └── video.mp4

The data folder is extremely important.

The video must be inside:

data/video.mp4
🗑️ Unnecessary Files

When the project ZIP was originally extracted, some macOS-generated files may appear:

__MACOSX
.DS_Store

These files are not required by the ESP32 project.

They can be ignored or deleted.

The important files are:

FreeWiFi.ino
data/video.mp4
🎬 Video Requirements

The project expects the video to have this filename:

video.mp4

The ESP32 code looks for:

/video.mp4

Therefore, if you rename the video, you must also change the filename/path in the code.

The video is stored in LittleFS rather than directly inside the Arduino sketch.

🧠 How the Project Works

The project has two main parts:

1. ESP32 Program

FreeWiFi.ino

This program:

Starts LittleFS
Checks for the video
Creates the Wi-Fi Access Point
Starts the DNS server
Starts the web server
Creates the webpage
Serves the MP4 video
Handles captive portal requests
2. LittleFS Filesystem

The data folder contains:

video.mp4

This file is uploaded separately to the ESP32 filesystem.

## 🔄 VERY IMPORTANT: Two Different Uploads

This is one of the most important things to remember.

You must perform TWO uploads.

## Upload 1 — LittleFS

Uploads:

data/video.mp4

to the ESP32 filesystem.
for this step 1 :
 download Arduino Littlefs from github from chrome browser .
 https://github.com/earlephilhower/arduino-littlefs-upload/releases?utm_source=chatgpt.com

 download only .vsix  file not zip one .
 
 then move this " .vsix  " file into arduino plugin file . open arduino ide with .ino code with esp32 connected to computer port . press ctrl + shift + P to open  command pelatte . search and select  "Upload LittleFS to Pico/ESP8266/ESP32" . press enter and then vsix file go to esp32 flash showing the file uploaded successfully.

Upload 2 — Normal Arduino Upload

Uploads:

FreeWiFi.ino

to the ESP32 program memory.

Therefore:

FreeWiFi.ino
      ↓
ESP32 Program Flash

video.mp4
      ↓
ESP32 LittleFS

Uploading only the .ino file is not enough.

Uploading only LittleFS is also not enough.

📡 Wi-Fi Configuration

The ESP32 creates this Wi-Fi network:

SSID:
Free_5G_WiFi_Click_Me

The project uses:

Wi-Fi Mode:
WIFI_AP

The ESP32 Access Point is configured as:

IP Address:
192.168.4.1

Gateway:
192.168.4.1

Subnet:
255.255.255.0

The DNS server uses:

Port:
53

and redirects DNS requests to:

192.168.4.1
🌐 Captive Portal

The project uses a DNS server to redirect requests to the ESP32.

The DNS server is started using:

dnsServer.start(
    DNS_PORT,
    "*",
    apIP
);

This allows the ESP32 to behave like a captive portal.

When a connected device checks for internet/captive portal connectivity, the ESP32 can redirect the request to its local webpage.

📱 Captive Portal Compatibility

The project includes routes for several operating systems.

Android
/generate_204
Apple
/hotspot-detect.html
Windows
/ncsi.txt
/connecttest.txt

These routes redirect the device to:

/

The project also redirects unknown URLs back to the main page.

🌐 Web Server

The project uses:

AsyncWebServer server(80);

Therefore the HTTP server runs on:

Port 80

The main webpage is:

/

So the normal local address is:

http://192.168.4.1/
🎨 Web Page

The HTML webpage is embedded directly inside:

FreeWiFi.ino

There is no separate index.html file in this project.

The page contains an HTML5 video element:

<video
  id="video"
  controls
  playsinline
  preload="auto">

The video source is:

<source
  src="/video.mp4"
  type="video/mp4">

The page also displays:

😂 Got You!
🎬 How Video Streaming Works

When the browser loads the webpage, it requests:

/video.mp4

The ESP32 receives this request.

The code checks whether:

/video.mp4

exists in LittleFS.

If it exists, the ESP32 creates a response using:

request->beginResponse(
    LittleFS,
    "/video.mp4",
    "video/mp4"
);

The response is sent with:

Content Type:
video/mp4

The project also adds:

Accept-Ranges: bytes

which helps browsers request portions of the video when necessary.

🔍 Video Debugging Endpoint

The project includes:

/video-info

After connecting to the ESP32, open:

http://192.168.4.1/video-info

If the video exists, the ESP32 returns something similar to:

Video exists
Size: 302920 bytes

The exact size depends on the video file.

This is useful for checking whether LittleFS contains the video.

🛠️ Installation Guide
Step 1 — Install Arduino IDE

Install Arduino IDE 2.x.

Recommended version used for this project:

Arduino IDE 2.3.10
Step 2 — Install ESP32 Board Support

Open:

Tools → Board → Boards Manager

Search:

esp32

Install:

ESP32 by Espressif Systems
Step 3 — Select Board

Select:

Tools → Board → ESP32 Arduino → ESP32 Dev Module
Step 4 — Connect ESP32

Connect the ESP32 to your computer using a USB data cable.

Step 5 — Select COM Port

Go to:

Tools → Port

Select the COM port belonging to the ESP32.

Example:

COM7

The COM number can be different on another computer.

📚 Step 6 — Install Libraries

Open:

Sketch → Include Library → Manage Libraries

Search for:

ESPAsyncWebServer

Install:

ESPAsyncWebServer by ESP32Async

Then search:

AsyncTCP

Install:

AsyncTCP by ESP32Async
🧪 Step 7 — Verify the Program

Open:

FreeWiFi.ino

Click:

✓ Verify

The program should compile successfully.

If you see:

ESPAsyncWebServer.h: No such file or directory

the ESPAsyncWebServer library is missing or incorrectly installed.

❌ Compilation Problem Encountered

During the original setup, this error occurred:

fatal error: ESPAsyncWebServer.h: No such file or directory
Cause

Arduino IDE could not find the ESPAsyncWebServer library.

Solution

Install:

ESPAsyncWebServer by ESP32Async

and:

AsyncTCP by ESP32Async
❌ MbedTLS Compilation Error

Another error occurred:

mbedtls_md5_starts_ret was not declared
mbedtls_md5_update_ret was not declared
mbedtls_md5_finish_ret was not declared

The errors appeared inside:

ESPAsyncWebServer/src/WebAuthentication.cpp
Cause

There was a compatibility problem between the installed async web server library and the ESP32/MbedTLS environment.

Solution Used

Remove the problematic async libraries and install the ESP32-compatible versions:

ESPAsyncWebServer by ESP32Async
AsyncTCP by ESP32Async

For ESP32, do not use:

ESPAsyncTCP
🧹 Removing Old Libraries

If an old or incompatible library causes compilation problems, Windows CMD can be used.

Open:

Windows + R

Type:

cmd

Then:

cd /d "C:\Users\<YOUR_USERNAME>\Documents\Arduino\libraries"

Remove old libraries if necessary:

rmdir /s /q "ESPAsyncWebServer"
rmdir /s /q "ESPAsyncTCP"
rmdir /s /q "AsyncTCP"

Then reinstall the correct libraries.

Replace <YOUR_USERNAME> with your Windows username.

📁 Step 8 — Check Project Structure

Before uploading LittleFS, make sure:

FreeWiFi/
│
├── FreeWiFi.ino
│
└── data/
    └── video.mp4

The data folder must be next to the .ino file.

💾 Step 9 — Install LittleFS Upload Tool

The MP4 video must be uploaded to the ESP32 filesystem.

Use:

Arduino LittleFS Upload:

https://github.com/earlephilhower/arduino-littlefs-upload

Download the appropriate .vsix release for Arduino IDE 2.x.

⚠️ LittleFS Plugin Folder Problem

During the original setup, the LittleFS .vsix file was initially placed inside:

C:\Users\<USERNAME>\.arduinoIDE\plugin-storage

This did not make the LittleFS command appear.

The required plugin directory is:

C:\Users\<USERNAME>\.arduinoIDE\plugins

If the plugins folder does not exist, create it.

Final structure:

C:\Users\<USERNAME>\.arduinoIDE\
│
├── globalStorage
├── plugin-storage
├── plugins
│   └── arduino-littlefs-upload-xxxxx.vsix
└── ...

The .vsix file must be inside:

plugins

not:

plugin-storage
🔄 Step 10 — Restart Arduino IDE

After placing the .vsix file in the correct folder:

Completely close Arduino IDE.
Open Arduino IDE again.
Open FreeWiFi.ino.
📤 Step 11 — Upload LittleFS

Make sure:

Board:
ESP32 Dev Module

and the correct COM port are selected.

Then press:

Ctrl + Shift + P

This opens the Command Palette.

Search:

Upload LittleFS

Select the LittleFS upload command.

The uploader reads:

data/video.mp4

and uploads it into the ESP32's LittleFS filesystem.

Wait until the terminal/output indicates that the LittleFS upload completed successfully.

✅ Step 12 — Upload Arduino Sketch

After LittleFS upload is complete:

Click:

→ Upload

This uploads:

FreeWiFi.ino

to the ESP32.

If the ESP32 remains stuck at:

Connecting........

press and hold the ESP32's:

BOOT

button.

When uploading begins, release the BOOT button.

🖥️ Step 13 — Serial Monitor

Open:

Tools → Serial Monitor

Set baud rate to:

115200

The program uses:

Serial.begin(115200);
✅ Expected Startup Messages

A successful startup should show messages similar to:

==============================
ESP32 Free WiFi Portal
==============================

LittleFS OK
Video found!
Video size: XXXXX bytes

WiFi Started!
SSID: Free_5G_WiFi_Click_Me
IP Address: 192.168.4.1

Web server started!
==============================

The exact video size will depend on the MP4 file.

📱 Step 14 — Connect Smartphone

Open Wi-Fi settings on your phone.

Find:

Free_5G_WiFi_Click_Me

Connect to it.

The phone may show:

Connected without internet

or:

No internet

This is normal.

The ESP32 is intentionally operating as a local Wi-Fi Access Point and does not provide internet access.

🌐 Step 15 — Open the Web Page

If the captive portal opens automatically, the webpage should appear.

If it does not open automatically, open a browser and enter:

http://192.168.4.1

The webpage should appear.

The browser will request:

/video.mp4

from the ESP32.

🎬 Step 16 — Test Video

The video should appear on the webpage.

The page includes browser controls:

Play
Pause
Seek
Volume
Fullscreen (depending on browser/device)

The page also displays:

😂 Got You!
🐛 Troubleshooting
Problem: Wi-Fi network doesn't appear

Check:

ESP32 is powered.
Correct sketch was uploaded.
Serial Monitor is set to 115200.
The Serial Monitor shows:
WiFi Started!
SSID: Free_5G_WiFi_Click_Me
Problem: LittleFS FAILED!

Serial Monitor:

LittleFS FAILED!
Solution

Upload LittleFS again.

Make sure:

FreeWiFi/
├── FreeWiFi.ino
└── data/
    └── video.mp4

Then perform:

Ctrl + Shift + P
→ Upload LittleFS
Problem: video.mp4 NOT FOUND!

Serial Monitor:

ERROR: video.mp4 NOT FOUND!
Check

Your computer must contain:

data/video.mp4

Then upload LittleFS again.

Problem: Webpage opens but video doesn't play

First check:

http://192.168.4.1/video-info

If it says:

Video exists
Size: XXXXX bytes

the video exists in LittleFS.

Then check the browser again.

Problem: Serial Monitor says Video file missing!

This means the browser requested:

/video.mp4

but the ESP32 could not find the file.

Upload LittleFS again.

Problem: Serial Monitor says Could not open video!

The file exists, but the ESP32 couldn't open it.

Try:

Upload LittleFS again.
Restart ESP32.
Check the video file.
Test with another MP4 if necessary.
Problem: Captive portal doesn't open automatically

Some phones/browser versions may not automatically trigger the captive portal.

Manually open:

http://192.168.4.1

The project can still work even if automatic captive-portal detection doesn't appear.

## 🔍 Debugging URLs
Main webpage
http://192.168.4.1/
Video
http://192.168.4.1/video.mp4
Video information
http://192.168.4.1/video-info
🧪 Debugging With Serial Monitor

## The Serial Monitor is one of the most useful tools for this project.

Set:

115200 baud

Important messages include:

LittleFS OK

This means LittleFS started successfully.

Video found!

This means /video.mp4 exists.

Video requested

This means the phone/browser requested the video.

Sending video: XXXXX bytes

This means the ESP32 is sending the video.

Video file missing!

The requested video does not exist in LittleFS.

Could not open video!

The ESP32 couldn't open the file.

## 🧩 Program Architecture

## The project can be understood as five main blocks:

             ┌─────────────────────┐
             │       ESP32         │
             └──────────┬──────────┘
                        │
              ┌─────────▼─────────┐
              │   Wi-Fi Access    │
              │       Point       │
              └─────────┬─────────┘
                        │
                        ▼
                  📱 Smartphone
                        │
                        ▼
              ┌───────────────────┐
              │   DNS Captive     │
              │      Portal       │
              └─────────┬─────────┘
                        │
                        ▼
              ┌───────────────────┐
              │ Async Web Server  │
              └─────────┬─────────┘
                        │
                        ▼
                ┌──────────────┐
                │   LittleFS   │
                │              │
                │  video.mp4   │
                └──────────────┘
🧠 Important IP Addresses and Ports
Item	Value
Wi-Fi SSID	Free_5G_WiFi_Click_Me
ESP32 IP	192.168.4.1
Gateway	192.168.4.1
Subnet	255.255.255.0
HTTP Port	80
DNS Port	53
Serial Baud Rate	115200
Video Path	/video.mp4
Debug Path	/video-info
🔧 Important Code Sections
Wi-Fi SSID
const char* ssid = "Free_5G_WiFi_Click_Me";

Change this if you want to change the Wi-Fi name.

ESP32 IP Address
IPAddress apIP(192, 168, 4, 1);
HTTP Server
AsyncWebServer server(80);
LittleFS
LittleFS.begin(true)
Video Path
/video.mp4
## ✏️ Changing the Wi-Fi Name

Find:

const char* ssid = "Free_5G_WiFi_Click_Me";

For example:

const char* ssid = "My_ESP32_WiFi";

Then upload the sketch again.

## 🎬 Changing the Video

Replace:

data/video.mp4

with another MP4.

The filename must remain:

video.mp4

Then upload LittleFS again.

You do not need to change the .ino code if the new file is still called:

video.mp4
⚠️ Important: Storage Limit

The video must fit inside the ESP32's available LittleFS partition.

The ESP32 also needs space for:

Program
Filesystem
Web server
Other data

A very large video may not fit.

For demonstrations, using a relatively small, compressed MP4 is recommended.

🔐 Security / Privacy Note

This project creates an open Wi-Fi network unless a password is added to:

WiFi.softAP(ssid);

Anyone nearby may be able to see and connect to the Wi-Fi network while the ESP32 is running.

Do not use this project to access, monitor or interfere with devices or networks without permission.

## This project should be used for:

Personal experiments
Electronics demonstrations
Educational projects
Authorized testing
Hackathons
Lab demonstrations

📝 Lessons Learned During Setup
Lesson 1

Installing a library with the correct name is not always enough.

The library must also be compatible with the board and ESP32 core version.

Lesson 2

ESP32 and ESP8266 use different asynchronous TCP libraries.

For this project:

ESP32
 ↓
AsyncTCP

not:

ESPAsyncTCP
Lesson 3

The Arduino program and filesystem are separate.

Remember:

.ino → program
data/ → LittleFS files
Lesson 4

A webpage can be embedded directly into an Arduino sketch.

This project does not require a separate index.html.

Lesson 5

The phone doesn't need internet access to communicate with the ESP32.

The ESP32 creates a local network.

## 🔄 Complete Rebuild Checklist

If rebuilding this project after a long time, follow this checklist from the beginning.

Software
 Install Arduino IDE
 Install ESP32 board package
 Select ESP32 Dev Module
 Install ESPAsyncWebServer by ESP32Async
 Install AsyncTCP by ESP32Async
 Do NOT install ESPAsyncTCP
Project
 Extract project
 Open FreeWiFi.ino
 Make sure data/video.mp4 exists
 Ignore/delete __MACOSX
 Ignore/delete .DS_Store
LittleFS
 Install Arduino LittleFS Upload
 Put .vsix in .arduinoIDE/plugins
 Restart Arduino IDE
 Open Command Palette
 Select Upload LittleFS
 Wait for successful LittleFS upload
Program
 Connect ESP32
 Select correct COM port
 Select ESP32 Dev Module
 Upload FreeWiFi.ino
Testing
 Open Serial Monitor
 Set 115200 baud
 Check LittleFS OK
 Check Video found!
 Check WiFi Started!
 Check Web server started!
 Connect phone to Free_5G_WiFi_Click_Me
 Open 192.168.4.1 if necessary
 Test video
 Test /video-info
📌 Quick Start

For someone who already knows Arduino:

1. Install ESP32 board support.

2. Install:
   ESPAsyncWebServer by ESP32Async
   AsyncTCP by ESP32Async

3. Open:
   FreeWiFi.ino

4. Make sure:
   data/video.mp4

5. Upload LittleFS.

6. Upload FreeWiFi.ino.

7. Open Serial Monitor at 115200.

8. Connect phone to:
   Free_5G_WiFi_Click_Me

9. Open:
   http://192.168.4.1

10. Enjoy the video!
📚 Useful Resources
Arduino IDE:
https://www.arduino.cc/en/software/
ESPAsyncWebServer:
https://github.com/ESP32Async/ESPAsyncWebServer
AsyncTCP:
https://github.com/ESP32Async/AsyncTCP
Arduino LittleFS Upload:
https://github.com/earlephilhower/arduino-littlefs-upload
ESP32 Arduino Core:
https://github.com/espressif/arduino-esp32
👨‍💻 Project

Project Name: ESP32 Free Wi-Fi Captive Portal + Video

Platform: ESP32

Development Environment: Arduino IDE

Main Technologies:

ESP32 Wi-Fi Access Point
DNS Server
Captive Portal
ESPAsyncWebServer
AsyncTCP
LittleFS
HTML5 Video
HTTP

## ❤️ Final Note
## This project was built as an experiment to understand how an ESP32 can create a local Wi-Fi network and serve web content without internet access.

The most important concepts learned from this project are:

ESP32 Wi-Fi AP
       +
DNS Captive Portal
       +
Async Web Server
       +
LittleFS
       +
HTML5 Video
       =
Local ESP32 Video Portal 🎬



```text
FreeWiFi/
├── FreeWiFi.ino
├── README.md
└── data/
    └── video.mp4

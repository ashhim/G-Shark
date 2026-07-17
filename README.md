# G-Shark

**Version:** 1.0  
**Platform:** ESP8266 (ESP-12E / ESP-12F)  
**Category:** Wireless Security Research Platform  
**Architecture:** Embedded Standalone Firmware  
**Storage:** SPIFFS + EEPROM  
**Display:** 128×64 SSD1306 OLED  
**Development Framework:** Arduino Core for ESP8266  
**Programming Language:** C++  

---

## Contents

1. [System Overview](#system-overview)
2. [Hardware Architecture](#hardware-architecture)
3. [Firmware Architecture](#firmware-architecture)
4. [Project Directory Structure](#project-directory-structure)
5. [Core System Components](#core-system-components)
6. [OLED User Interface](#oled-user-interface)
7. [Button Navigation System](#button-navigation-system)
8. [Wireless Scanning Engine](#wireless-scanning-engine)
9. [Access Point Management](#access-point-management)
10. [Station Management](#station-management)
11. [Attack Framework](#attack-framework)
12. [Beacon Frame System](#beacon-frame-system)
13. [Probe Request System](#probe-request-system)
14. [Captive Portal Framework](#captive-portal-framework)
15. [Embedded Web Interface](#embedded-web-interface)
16. [SPIFFS File System](#spiffs-file-system)
17. [EEPROM Configuration](#eeprom-configuration)
18. [Command Line Interface](#command-line-interface)
19. [Configuration System](#configuration-system)
20. [Web API & Firmware Communication](#web-api--firmware-communication)
21. [Display Rendering Engine](#display-rendering-engine)
22. [Power Management](#power-management)
23. [System Configuration Options](#system-configuration-options)
24. [Compilation & Build Process](#compilation--build-process)
25. [Installation & Flashing](#installation--flashing)
26. [Firmware Customization](#firmware-customization)
27. [Project Resources](#project-resources)
28. [Troubleshooting](#troubleshooting)
29. [License](#license)

---

## Overview

G-Shark is a compact ESP8266-based wireless research platform that integrates packet processing, wireless scanning, access point management, an embedded web server, OLED user interface, persistent configuration storage, and a modular firmware architecture into a single standalone device.

Designed around a wearable hardware platform, G-Shark provides a complete firmware environment that combines physical controls, a graphical OLED interface, browser-based management pages, and an onboard command-line interface, allowing the device to operate independently without requiring external software after deployment.

The firmware incorporates multiple subsystems responsible for wireless scanning, packet transmission, access point management, station tracking, display rendering, configuration management, filesystem storage, and runtime control. These modules communicate through a shared firmware architecture while maintaining persistent configuration through EEPROM and serving web assets directly from the onboard SPIFFS filesystem.

The integrated captive portal framework supports fully customizable web interfaces that can be replaced with user-defined HTML, CSS, JavaScript, images, audio, fonts, and other static resources stored within the firmware. The embedded web interface communicates directly with the firmware, enabling browser-based interaction while synchronizing information with the OLED display and other runtime interface components.

G-Shark also provides a configurable wireless interface capable of operating as an access point with customizable network parameters, allowing developers to tailor the device for different embedded networking, testing, demonstration, and educational workflows.

The firmware has been designed using a modular codebase where individual components such as scanning, display management, wireless communication, configuration storage, web services, command processing, and hardware abstraction remain independent while operating together as a unified embedded system. This architecture simplifies maintenance, feature expansion, customization, and future firmware development while preserving consistent runtime performance on the ESP8266 platform.

# G-Shark

**Version:** 3.0  
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

## System Overview

G-Shark is a compact ESP8266-based wireless research platform that integrates packet processing, wireless scanning, access point management, an embedded web server, OLED user interface, persistent configuration storage, and a modular firmware architecture into a single standalone device.

Designed around a wearable hardware platform, G-Shark provides a complete firmware environment that combines physical controls, a graphical OLED interface, browser-based management pages, and an onboard command-line interface, allowing the device to operate independently without requiring external software after deployment.

The firmware incorporates multiple subsystems responsible for wireless scanning, packet transmission, access point management, station tracking, display rendering, configuration management, filesystem storage, and runtime control. These modules communicate through a shared firmware architecture while maintaining persistent configuration through EEPROM and serving web assets directly from the onboard SPIFFS filesystem.

The integrated captive portal framework supports fully customizable web interfaces that can be replaced with user-defined HTML, CSS, JavaScript, images, audio, fonts, and other static resources stored within the firmware. The embedded web interface communicates directly with the firmware, enabling browser-based interaction while synchronizing information with the OLED display and other runtime interface components.


## Hardware Architecture

### 2.1 Hardware Overview

G-Shark is built around the ESP8266 Wi-Fi System-on-Chip, providing a compact, self-contained embedded platform capable of wireless communication, local data storage, real-time display rendering, and standalone firmware execution. The hardware architecture integrates networking, user interaction, persistent storage, and power management into a lightweight wearable device.

The system has been designed to operate independently without requiring external computing hardware during normal operation. All wireless processing, web services, user interface rendering, packet generation, configuration management, and filesystem operations are executed directly by the ESP8266.

---

### 2.2 Hardware Components

| Component | Model | Purpose |
|-----------|-------|---------|
| **Microcontroller** | ESP8266 ESP-12E / ESP-12F | Main processing unit |
| **Wireless Interface** | Integrated 2.4 GHz IEEE 802.11 b/g/n | Wi-Fi communication |
| **Display** | SSD1306 OLED (128×64) | User interface and system information |
| **Storage** | SPI Flash Memory | Firmware and SPIFFS storage |
| **Configuration Storage** | EEPROM Emulation | Persistent device configuration |
| **Navigation Buttons** | Multiple Push Buttons | User input and menu navigation |
| **Power Source** | USB / Battery | Device power supply |
| **GPIO Interfaces** | ESP8266 GPIO Pins | Display and button connectivity |

---

### 2.3 ESP8266 Processing Unit

The ESP8266 serves as the central processing unit of the G-Shark platform. It is responsible for executing every firmware subsystem including wireless communication, display rendering, filesystem management, HTTP services, configuration storage, packet processing, and hardware interaction.

The processor simultaneously manages multiple firmware modules while maintaining responsive operation through efficient task scheduling and optimized memory utilization.

**Responsibilities**

- Firmware execution
- Wi-Fi communication
- Packet processing
- Access Point management
- Station management
- Embedded web server
- OLED display rendering
- Button event processing
- SPIFFS filesystem access
- EEPROM configuration management
- Runtime configuration updates
- System monitoring

---

### 2.4 Wireless Communication Hardware

The integrated IEEE 802.11 b/g/n wireless radio enables the firmware to perform wireless communication and network management directly through the ESP8266 hardware.

The wireless subsystem supports simultaneous interaction with multiple firmware modules, allowing scanning, packet transmission, access point services, station tracking, and browser communication to operate through a unified networking architecture.

The firmware dynamically configures the wireless hardware according to the active operating mode while maintaining communication with other internal subsystems.

---

### 2.5 OLED Display Module

G-Shark incorporates a 128×64 monochrome SSD1306 OLED display connected through the I²C interface.

The display provides the primary user interface for standalone operation, allowing users to navigate menus, monitor wireless activity, configure settings, and observe system status without requiring a browser or external computer.

Displayed information includes:

- Main navigation menus
- Wireless scan results
- Access point information
- Connected stations
- Device status
- Runtime statistics
- Configuration values
- Progress indicators
- Warning messages
- System notifications

The display rendering engine continuously synchronizes with the firmware to ensure that the information shown accurately reflects the current operating state.

---

### 2.6 Navigation Buttons

Physical push buttons provide direct interaction with the firmware.

The button navigation system enables complete operation of the device through the OLED interface without requiring external software.

Supported interactions include:

- Menu navigation
- Item selection
- Configuration editing
- Function execution
- Menu return
- System control
- Shortcut operations

Button events are continuously monitored by the firmware and processed in real time.

---

### 2.7 Flash Memory Architecture

The onboard flash memory stores both the firmware image and the SPIFFS filesystem.

The firmware occupies the program storage region while the remaining flash memory is allocated to SPIFFS for storing web assets and runtime resources.

Stored resources include:

- HTML pages
- CSS stylesheets
- JavaScript files
- Images
- Icons
- Fonts
- Audio resources
- Configuration files
- Runtime assets

This architecture enables complete customization of the embedded web interface without modifying the firmware source code.

---

### 2.8 EEPROM Configuration Storage

EEPROM emulation provides persistent storage for firmware configuration.

Configuration values remain available after power loss and are automatically restored during device startup.

Typical stored parameters include:

- Device settings
- Display preferences
- Wireless configuration
- Access Point configuration
- User preferences
- Runtime options
- Feature states
- System parameters

The configuration manager automatically validates stored data before applying it during initialization.

---

### 2.9 Hardware Block Diagram

```
                    ┌──────────────────────────────┐
                    │          Power Supply        │
                    └──────────────┬───────────────┘
                                   │
                     ┌─────────────▼─────────────┐
                     │      ESP8266 ESP-12E/F    │
                     │   Main Processing Unit    │
                     └───────┬─────────┬─────────┘
                             │         │
                 ┌───────────▼───┐     ▼
                 │ Wi-Fi Radio   │  EEPROM
                 │ IEEE 802.11   │ Configuration
                 └───────────────┘
                             │
               ┌─────────────┼──────────────┐
               │             │              │
               ▼             ▼              ▼
         OLED Display   Push Buttons    SPI Flash
          SSD1306       User Input       SPIFFS
               │                            │
               └─────────────┬──────────────┘
                             ▼
                    Embedded Firmware
```

---

### 2.10 Hardware Characteristics

| Feature | Specification |
|----------|---------------|
| Processing Unit | ESP8266 ESP-12E / ESP-12F |
| Wireless Standard | IEEE 802.11 b/g/n |
| Operating Band | 2.4 GHz |
| Display Type | SSD1306 OLED |
| Display Resolution | 128 × 64 Pixels |
| Display Interface | I²C |
| Storage | SPI Flash + SPIFFS |
| Configuration Storage | EEPROM Emulation |
| User Input | Physical Navigation Buttons |
| Firmware Architecture | Standalone Embedded System |
| Web Interface | Integrated HTTP Server |
| Configuration | Runtime Configurable |
| Filesystem | SPIFFS |
| Platform | Arduino Core for ESP8266 |
G-Shark also provides a configurable wireless interface capable of operating as an access point with customizable network parameters, allowing developers to tailor the device for different embedded networking, testing, demonstration, and educational workflows.

The firmware has been designed using a modular codebase where individual components such as scanning, display management, wireless communication, configuration storage, web services, command processing, and hardware abstraction remain independent while operating together as a unified embedded system. This architecture simplifies maintenance, feature expansion, customization, and future firmware development while preserving consistent runtime performance on the ESP8266 platform.

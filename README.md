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


## Firmware Architecture

### 3.1 Architecture Overview

G-Shark is built upon a modular embedded firmware architecture that separates major system functionality into independent software components while maintaining coordinated communication through shared runtime services. This design enables the firmware to manage wireless communication, display rendering, user interaction, configuration storage, embedded web services, and hardware control simultaneously on the ESP8266 platform.

Rather than implementing all functionality within a single execution flow, the firmware is organized into specialized modules that each perform a dedicated responsibility. These modules exchange information through shared data structures, global state management, and common hardware abstraction layers, allowing the system to remain scalable, maintainable, and extensible.

The modular architecture also simplifies future feature development by allowing individual subsystems to be updated or expanded without requiring significant modifications to unrelated components.

---

### 3.2 Firmware Layers

The firmware is logically divided into multiple abstraction layers, each responsible for a specific area of system operation.

```
┌────────────────────────────────────────────┐
│           User Interaction Layer           │
│ OLED • Buttons • Web Interface • CLI       │
├────────────────────────────────────────────┤
│         Application Service Layer          │
│ Scan • AP • Stations • Display • Settings  │
├────────────────────────────────────────────┤
│        System Management Layer             │
│ Config • EEPROM • SPIFFS • Runtime         │
├────────────────────────────────────────────┤
│       Network & Communication Layer        │
│ Wi-Fi Driver • HTTP Server • DNS • TCP/IP  │
├────────────────────────────────────────────┤
│        Hardware Abstraction Layer          │
│ GPIO • OLED • Flash • Timers • EEPROM      │
├────────────────────────────────────────────┤
│          ESP8266 Hardware Platform         │
└────────────────────────────────────────────┘
```

Each layer exposes services to the layer above while abstracting lower-level hardware implementation details.

---

### 3.3 Core Firmware Modules

The firmware consists of several primary modules that operate together throughout the device lifecycle.

| Module | Primary Responsibility |
|---------|------------------------|
| Display Manager | OLED rendering and menu interface |
| Button Manager | Physical input handling |
| Wireless Scanner | Network discovery |
| Access Point Manager | AP configuration and operation |
| Station Manager | Connected client management |
| Packet Engine | Wireless packet processing |
| Captive Portal | Embedded portal services |
| Web Server | Browser interface |
| CLI Manager | Command processing |
| Configuration Manager | Runtime settings |
| EEPROM Manager | Persistent storage |
| SPIFFS Manager | Static resource management |
| System Controller | Runtime coordination |

Each module performs a dedicated task while communicating with other components through the firmware runtime.

---

### 3.4 System Initialization Sequence

During startup, the firmware initializes hardware and software components in a predefined sequence to ensure stable operation.

```
Power On
     │
     ▼
ESP8266 Boot
     │
     ▼
Hardware Initialization
     │
     ▼
GPIO Configuration
     │
     ▼
OLED Initialization
     │
     ▼
EEPROM Initialization
     │
     ▼
SPIFFS Mount
     │
     ▼
Configuration Loading
     │
     ▼
Wi-Fi Initialization
     │
     ▼
Web Server Startup
     │
     ▼
Runtime Module Initialization
     │
     ▼
OLED Home Screen
     │
     ▼
System Ready
```

Each initialization stage validates successful completion before proceeding to the next subsystem.

---

### 3.5 Runtime Architecture

Once initialized, the firmware enters its continuous execution loop.

The runtime continuously performs tasks including:

- Processing user input
- Updating the OLED interface
- Managing wireless communication
- Processing HTTP requests
- Handling command execution
- Updating runtime configuration
- Reading EEPROM values
- Serving SPIFFS resources
- Managing timers
- Monitoring system status

These operations execute repeatedly throughout the lifetime of the device.

---

### 3.6 Module Communication

Firmware components communicate through shared runtime resources rather than direct hardware interaction.

```
                 Configuration
                       │
         ┌─────────────┼─────────────┐
         │             │             │
         ▼             ▼             ▼
      Scanner      AP Manager    Display
         │             │             │
         └──────┬──────┴──────┬──────┘
                ▼             ▼
           Runtime Controller
                │
      ┌─────────┼──────────┐
      ▼         ▼          ▼
   Web UI      CLI      EEPROM
      │                     │
      └──────────┬──────────┘
                 ▼
               SPIFFS
```

This architecture minimizes coupling between modules while allowing efficient information exchange.

---

### 3.7 State Management

The firmware maintains a centralized runtime state that reflects the current operating condition of the device.

Examples of managed runtime information include:

- Active menu
- Display state
- Wireless status
- Scan results
- Access Point configuration
- Connected stations
- Configuration values
- Feature states
- Runtime counters
- System flags

The centralized state enables synchronized updates across the OLED interface, embedded web interface, and command-line interface.

---

### 3.8 Event Processing

Firmware operation is primarily event-driven.

Typical events include:

- Button presses
- Timer expirations
- Wireless events
- HTTP requests
- Configuration updates
- Filesystem operations
- Display refresh requests
- Runtime status changes
- Command execution
- System initialization

Each event is processed by the responsible subsystem while maintaining overall system responsiveness.

---

### 3.9 Resource Management

Because the ESP8266 provides limited RAM and processing resources, the firmware employs efficient resource management techniques throughout the codebase.

The architecture is designed to:

- Minimize dynamic memory allocation
- Reuse shared buffers
- Reduce unnecessary processing
- Optimize display updates
- Manage filesystem access efficiently
- Coordinate wireless operations
- Maintain responsive user interaction

These design principles contribute to stable runtime performance on resource-constrained hardware.

---

### 3.10 Firmware Design Characteristics

| Characteristic | Description |
|---------------|-------------|
| Architecture Style | Modular Embedded Firmware |
| Runtime Model | Continuous Event-Driven Execution |
| Platform | ESP8266 |
| Programming Language | C++ |
| Development Framework | Arduino Core for ESP8266 |
| User Interfaces | OLED, Web Interface, CLI |
| Persistent Storage | EEPROM |
| Filesystem | SPIFFS |
| Network Services | Integrated HTTP Server |
| Configuration | Runtime Configurable |
| Hardware Abstraction | Layered Design |
| Scalability | Independent Modular Components |
| Maintainability | Loosely Coupled Architecture |
| Extensibility | Module-Based Expansion |
| Execution Model | Standalone Embedded System |


## Project Directory Structure

### 4.1 Overview

The G-Shark firmware is organized into a modular directory structure that separates wireless functionality, hardware abstraction, user interface components, configuration management, embedded web resources, and supporting libraries into dedicated source files. This organization simplifies development, maintenance, debugging, and future feature expansion while allowing individual firmware modules to remain logically independent.

The project follows the standard Arduino Core for ESP8266 project layout, where the primary firmware entry point initializes and coordinates the remaining subsystems.

---

### 4.2 Root Directory Structure

```text
G-Shark/
│
├── esp8266_deauther.ino
├── A_config.h
├── debug.h
├── functions.h
│
├── Scan.cpp
├── Scan.h
│
├── Attack.cpp
├── Attack.h
│
├── Accesspoints.cpp
├── Accesspoints.h
│
├── Stations.cpp
├── Stations.h
│
├── DisplayUI.cpp
├── DisplayUI.h
│
├── CLI.cpp
├── CLI.h
│
├── SSIDs.cpp
├── SSIDs.h
│
├── Names.cpp
├── Names.h
│
├── EEPROMHelper.h
├── SimpleList.h
│
├── CapAdPage.h
├── NameMePages.h
│
├── data/
│   ├── web/
│   ├── nameme/
│   ├── logo.png
│   ├── instapage.jpg
│   └── music.mp3
│
└── README.md
```

---

### 4.3 Firmware Entry Point

**File**

```
esp8266_deauther.ino
```

This file serves as the primary firmware entry point.

Its responsibilities include:

- System initialization
- Hardware startup
- Runtime initialization
- Module creation
- Main execution loop
- Firmware coordination

All major firmware components are initialized from this location before runtime execution begins.

---

### 4.4 Core Source Modules

The firmware functionality is divided into dedicated source files.

| Module | Purpose |
|---------|---------|
| `Scan.cpp` | Wireless scanning engine |
| `Attack.cpp` | Packet processing framework |
| `Accesspoints.cpp` | Access Point management |
| `Stations.cpp` | Station tracking and management |
| `DisplayUI.cpp` | OLED interface rendering |
| `CLI.cpp` | Command-line interface |
| `SSIDs.cpp` | SSID management |
| `Names.cpp` | Name generation and management |

Each module encapsulates a specific functional area of the firmware while exposing interfaces used by the remaining system.

---

### 4.5 Header Files

Header files define class declarations, shared structures, constants, function prototypes, and configuration interfaces used throughout the firmware.

Important header files include:

| File | Description |
|------|-------------|
| `A_config.h` | Global firmware configuration |
| `functions.h` | Shared utility functions |
| `EEPROMHelper.h` | EEPROM management |
| `SimpleList.h` | Dynamic list container |
| `debug.h` | Debugging utilities |
| `CapAdPage.h` | Embedded captive portal resources |
| `NameMePages.h` | Embedded HTML page definitions |

Separating declarations from implementation improves readability and simplifies firmware maintenance.

---

### 4.6 SPIFFS Data Directory

The `data` directory contains files uploaded to the SPIFFS filesystem during deployment.

```text
data/
│
├── web/
│   ├── HTML pages
│   ├── JavaScript
│   ├── CSS
│   ├── Language files
│   └── Static resources
│
├── nameme/
│   └── HTML templates
│
├── logo.png
├── instapage.jpg
└── music.mp3
```

These resources are served directly by the embedded web server and can be replaced or customized independently of the firmware source code.

---

### 4.7 Embedded Web Interface

The `data/web` directory contains the browser-based management interface.

Typical resources include:

- HTML documents
- JavaScript modules
- CSS stylesheets
- Language translation files
- Compressed static assets

These files are stored within SPIFFS and delivered through the integrated HTTP server.

---

### 4.8 Static Assets

The firmware stores various static resources inside SPIFFS to support the embedded web interface.

Examples include:

- Images
- Logos
- Background graphics
- Audio files
- Icons
- Fonts
- Compressed web resources

Keeping these resources separate from the firmware binary simplifies customization and future updates.

---

### 4.9 Module Dependency Structure

```text
                     esp8266_deauther.ino
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
        ▼                     ▼                     ▼
   DisplayUI             Wireless             Configuration
        │              (Scan / AP / STA)          │
        │                     │                   │
        └──────────────┬──────┴──────────────┐
                       ▼                     ▼
                  Runtime Services      EEPROM
                       │
                       ▼
                    SPIFFS
                       │
                       ▼
                 Embedded Web UI
```

Each subsystem performs a dedicated function while communicating through shared runtime services.

---

### 4.10 Project Organization Principles

The project structure follows several organizational principles:

- Separation of hardware abstraction and application logic
- Independent firmware modules
- Shared configuration interfaces
- Modular source organization
- Centralized runtime initialization
- Dedicated filesystem resources
- Maintainable code separation
- Expandable architecture for future features

This layout enables developers to extend individual firmware components without significantly affecting unrelated modules.

---

### 4.11 Directory Summary

| Directory / File | Primary Purpose |
|------------------|-----------------|
| `esp8266_deauther.ino` | Firmware entry point |
| `*.cpp` | Module implementations |
| `*.h` | Interfaces and declarations |
| `A_config.h` | Global configuration |
| `EEPROMHelper.h` | Persistent storage management |
| `DisplayUI.*` | OLED interface |
| `Scan.*` | Wireless scanning |
| `Attack.*` | Packet processing |
| `Accesspoints.*` | Access Point management |
| `Stations.*` | Station management |
| `CLI.*` | Command-line interface |
| `data/` | SPIFFS filesystem resources |
| `data/web/` | Embedded web application |
| `data/nameme/` | HTML template resources |
| Static Assets | Images, audio, and supporting resources |



## Core System Components

### 5.1 Overview

The G-Shark firmware is composed of multiple core software components that collectively provide wireless communication, user interaction, configuration management, embedded web services, persistent storage, and runtime coordination. Each component performs a well-defined responsibility while interacting with other subsystems through the shared firmware architecture.

The modular design allows each component to operate independently while contributing to the overall functionality of the embedded platform. This separation improves maintainability, scalability, debugging, and future firmware development.

---

### 5.2 Component Architecture

```
                           G-Shark Firmware
                                  │
 ┌────────────────────────────────┼────────────────────────────────┐
 │                                │                                │
 ▼                                ▼                                ▼
User Interface              Wireless Services              System Services
 │                                │                                │
 ├── OLED Display                ├── Scanner                     ├── EEPROM
 ├── Button Manager              ├── Access Point               ├── SPIFFS
 ├── Web Interface               ├── Station Manager            ├── Configuration
 └── CLI                         └── Packet Engine              └── Runtime Manager
                                  │
                                  ▼
                          Embedded Web Server
```

Each subsystem performs a dedicated task while sharing common runtime resources.

---

### 5.3 OLED Display Manager

The OLED Display Manager is responsible for rendering all graphical content presented on the SSD1306 display.

Its responsibilities include:

- Rendering menus
- Drawing icons
- Displaying system status
- Showing scan results
- Presenting runtime information
- Updating progress indicators
- Displaying notifications
- Refreshing user interface elements

The display subsystem continuously synchronizes with runtime data to present current system information.

---

### 5.4 Button Navigation Manager

The Button Navigation Manager processes physical user input received from the device navigation buttons.

Supported operations include:

- Menu navigation
- Option selection
- Configuration editing
- Function activation
- Menu traversal
- Screen transitions
- User confirmation
- Shortcut execution

Button events are translated into firmware actions and dispatched to the appropriate subsystem.

---

### 5.5 Wireless Scanning Engine

The Wireless Scanning Engine performs discovery of nearby IEEE 802.11 wireless networks and collects information required by other firmware modules.

The scanner is responsible for:

- Network discovery
- Channel scanning
- Access Point identification
- Signal strength collection
- Network information updates
- Scan result storage
- Runtime synchronization

Collected information is made available to the OLED interface, embedded web interface, and other firmware components.

---

### 5.6 Access Point Manager

The Access Point Manager controls the device's integrated wireless access point functionality.

Its primary responsibilities include:

- Access Point initialization
- SSID configuration
- Channel configuration
- Network parameter management
- Runtime state updates
- Client association monitoring
- Wireless service coordination

Configuration parameters are loaded from persistent storage during system startup.

---

### 5.7 Station Manager

The Station Manager maintains runtime information regarding wireless stations detected or associated with the system.

Responsibilities include:

- Station tracking
- MAC address management
- Signal monitoring
- Runtime updates
- Station list maintenance
- Display synchronization
- Web interface integration

The Station Manager continuously updates runtime information as wireless activity changes.

---

### 5.8 Packet Processing Engine

The Packet Processing Engine manages the construction, processing, and transmission of IEEE 802.11 management frames used throughout the firmware.

The engine provides:

- Frame generation
- Buffer preparation
- Packet scheduling
- Transmission control
- Runtime synchronization
- Wireless interface coordination

This component serves as the central packet handling layer for firmware operations involving wireless frame transmission.

---

### 5.9 Embedded Web Server

The embedded HTTP server provides browser-based access to firmware functionality without requiring external software.

Its responsibilities include:

- Serving web pages
- Processing HTTP requests
- Delivering static resources
- Runtime data exchange
- API communication
- Configuration updates
- Browser synchronization

Web content is served directly from the onboard SPIFFS filesystem.

---

### 5.10 Captive Portal Framework

The Captive Portal Framework integrates browser-based interaction with the embedded web server.

The framework supports deployment of fully customizable web applications stored within SPIFFS, allowing developers to replace or extend the web interface without modifying the firmware source code.

Supported resource types include:

- HTML
- CSS
- JavaScript
- Images
- Icons
- Fonts
- Audio
- Additional static assets

---

### 5.11 Configuration Manager

The Configuration Manager maintains firmware settings throughout system operation.

Responsibilities include:

- Runtime configuration
- Parameter validation
- Settings synchronization
- Default value management
- Configuration updates
- Feature enablement
- System preferences

Configuration values are automatically restored during device startup.

---

### 5.12 EEPROM Manager

The EEPROM Manager provides persistent storage for firmware configuration.

Stored information may include:

- Device settings
- Display preferences
- Wireless parameters
- User preferences
- Feature states
- Runtime options

The EEPROM subsystem automatically reads configuration data during initialization and commits updates when required.

---

### 5.13 SPIFFS Manager

The SPIFFS Manager provides access to the onboard flash filesystem.

Its responsibilities include:

- Filesystem mounting
- File access
- Resource loading
- Static asset delivery
- Web content retrieval
- Storage management

The embedded web server relies on SPIFFS for serving browser resources.

---

### 5.14 Command Line Interface

The Command Line Interface (CLI) provides an additional interface for interacting with the firmware.

The CLI supports:

- Command execution
- Configuration management
- Runtime inspection
- System control
- Status reporting
- Parameter modification

Commands are processed through a dedicated parser before being dispatched to the appropriate subsystem.

---

### 5.15 Runtime Controller

The Runtime Controller coordinates interaction between all firmware components.

Primary responsibilities include:

- Module initialization
- Event distribution
- State synchronization
- Task coordination
- Resource management
- Runtime monitoring
- System scheduling

The Runtime Controller ensures that all firmware modules operate cohesively while maintaining responsive system performance.

---

### 5.16 Component Interaction

```
                    User Input
                         │
         ┌───────────────┴───────────────┐
         ▼                               ▼
   Button Manager                  Embedded Web UI
         │                               │
         └───────────────┬───────────────┘
                         ▼
                 Runtime Controller
                         │
 ┌──────────────┬────────┼─────────┬──────────────┐
 ▼              ▼        ▼         ▼              ▼
Scanner      AP Manager Stations Packet Engine Display
 │              │        │         │              │
 └──────────────┴────────┴─────────┴──────────────┘
                         │
                         ▼
              Configuration Manager
                         │
              ┌──────────┴──────────┐
              ▼                     ▼
           EEPROM                SPIFFS
```

---

### 5.17 Core Component Summary

| Component | Primary Responsibility |
|-----------|------------------------|
| OLED Display Manager | Graphical user interface |
| Button Navigation Manager | Physical user interaction |
| Wireless Scanning Engine | Network discovery |
| Access Point Manager | Wireless AP operation |
| Station Manager | Station tracking |
| Packet Processing Engine | IEEE 802.11 frame handling |
| Embedded Web Server | Browser interface |
| Captive Portal Framework | Web application delivery |
| Configuration Manager | Runtime settings |
| EEPROM Manager | Persistent storage |
| SPIFFS Manager | Filesystem management |
| Command Line Interface | Command processing |
| Runtime Controller | System coordination |


## OLED User Interface

### 6.1 Overview

The G-Shark firmware provides a fully integrated graphical user interface through a 128×64 SSD1306 OLED display. The OLED serves as the primary local interaction interface, allowing users to operate the device directly without requiring an external computer, smartphone, or browser.

The interface is designed for real-time embedded operation and continuously reflects the current runtime state of the firmware. Information displayed on the screen is dynamically updated as wireless operations, system events, user interactions, and configuration changes occur.

The OLED interface is tightly integrated with the firmware runtime, ensuring synchronized operation with the wireless subsystem, configuration manager, embedded web interface, and command processing engine.

---

### 6.2 Display Specifications

| Property | Specification |
|----------|---------------|
| Display Controller | SSD1306 |
| Resolution | 128 × 64 Pixels |
| Color | Monochrome |
| Interface | I²C |
| Display Type | OLED |
| Refresh Method | Runtime Rendering |
| Orientation | Landscape |
| Power Consumption | Low Power |

---

### 6.3 User Interface Architecture

The OLED interface is managed by a dedicated display subsystem responsible for rendering graphical elements, menus, status indicators, runtime information, and navigation screens.

```
                Firmware Runtime
                       │
      ┌────────────────┼────────────────┐
      ▼                ▼                ▼
 Wireless Data   Configuration     System Status
      │                │                │
      └────────────────┼────────────────┘
                       ▼
               DisplayUI Module
                       │
               Rendering Engine
                       │
              SSD1306 OLED Display
```

The display subsystem continuously retrieves runtime information and converts it into graphical elements suitable for presentation on the OLED.

---

### 6.4 Display Responsibilities

The OLED interface is responsible for presenting information generated by multiple firmware modules.

Displayed information includes:

- Main menu
- Navigation menus
- Wireless scan results
- Access Point information
- Station information
- Configuration values
- Runtime statistics
- Status indicators
- Progress information
- Notifications
- Warning messages
- System information

The display automatically refreshes whenever runtime data changes.

---

### 6.5 Main Menu

The main menu serves as the primary navigation hub for the firmware.

From the main menu, users can access all major firmware functions through the physical navigation buttons.

Typical menu categories include:

- Wireless Scanner
- Access Point Management
- Station Management
- Configuration
- System Information
- Display Settings
- Runtime Controls
- Additional Utilities

The menu structure is organized hierarchically to simplify navigation on the limited display area.

---

### 6.6 Menu Navigation

Navigation is performed entirely through the device's physical buttons.

Supported operations include:

- Navigate upward
- Navigate downward
- Enter submenu
- Return to previous menu
- Select menu item
- Modify configuration values
- Confirm operations
- Cancel operations

The current menu selection is visually highlighted to improve usability.

---

### 6.7 Screen Rendering

The rendering engine is responsible for drawing all visible interface elements.

Displayed graphical components include:

- Text
- Icons
- Borders
- Selection indicators
- Status symbols
- Progress bars
- Lists
- Menus
- Dialog boxes
- Notifications

Rendering operations are optimized to minimize unnecessary screen updates while maintaining smooth user interaction.

---

### 6.8 Runtime Synchronization

The OLED interface operates as a live representation of the firmware runtime.

Displayed information is synchronized with:

- Wireless scanning engine
- Access Point Manager
- Station Manager
- Configuration Manager
- Embedded web interface
- Runtime controller
- EEPROM Manager

Whenever a subsystem updates its runtime state, the display reflects the changes during the next refresh cycle.

---

### 6.9 Status Information

The OLED provides continuous feedback regarding the operational state of the device.

Typical runtime information includes:

- Active operating mode
- Selected menu
- Wi-Fi channel
- Wireless status
- Number of detected networks
- Connected stations
- Configuration status
- Runtime counters
- System notifications

This information enables users to monitor firmware operation without accessing the web interface.

---

### 6.10 Notification System

The interface includes a notification mechanism used to inform the user about significant runtime events.

Examples include:

- Initialization complete
- Configuration saved
- Filesystem mounted
- Network scan completed
- Access Point started
- Operation completed
- Runtime warnings
- Error messages

Notifications are displayed temporarily before returning to the previous screen.

---

### 6.11 Display Refresh Process

The rendering process follows a continuous refresh cycle.

```
Runtime Update
      │
      ▼
Display Event Generated
      │
      ▼
Retrieve Current State
      │
      ▼
Generate Screen Layout
      │
      ▼
Render Graphics
      │
      ▼
Update OLED Display
      │
      ▼
Wait for Next Event
```

Only modified interface elements are refreshed when possible to improve rendering efficiency.

---

### 6.12 Interface Characteristics

The OLED interface has been designed with the following objectives:

- Standalone operation
- Simple navigation
- Fast response
- Minimal resource usage
- Clear information presentation
- Consistent menu hierarchy
- Efficient rendering
- Real-time status updates

These characteristics provide a responsive user experience while operating within the hardware limitations of the ESP8266 platform.

---

### 6.13 Interaction with Other Components

The OLED subsystem exchanges information with multiple firmware modules.

```
                 Runtime Controller
                        │
        ┌───────────────┼───────────────┐
        ▼               ▼               ▼
 Wireless Engine   Configuration   Web Server
        │               │               │
        └───────────────┼───────────────┘
                        ▼
                  DisplayUI Module
                        │
                  SSD1306 OLED
```

The display remains synchronized with the firmware throughout device operation.

---

### 6.14 Display Features Summary

| Feature | Description |
|----------|-------------|
| Display Controller | SSD1306 |
| Resolution | 128 × 64 Pixels |
| Interface | I²C |
| Menu System | Hierarchical Navigation |
| User Input | Physical Buttons |
| Screen Updates | Real-Time |
| Rendering | Dynamic Runtime Rendering |
| Status Monitoring | Integrated |
| Notifications | Supported |
| Configuration Display | Supported |
| Runtime Synchronization | Automatic |
| Standalone Operation | Fully Supported |


## Button Navigation System

### 7.1 Overview

The Button Navigation System provides the primary physical interface for operating the G-Shark firmware. It enables complete interaction with the device through a set of dedicated navigation buttons, eliminating the requirement for external peripherals during normal operation.

The navigation subsystem is closely integrated with the OLED user interface and firmware runtime, allowing users to browse menus, modify configuration parameters, execute firmware functions, and monitor system status directly from the device.

All button events are processed in real time and translated into navigation commands that control the graphical user interface.

---

### 7.2 Navigation Architecture

The button subsystem consists of hardware input lines, an input processing layer, a navigation controller, and the OLED rendering engine.

```
             Physical Buttons
                    │
                    ▼
          GPIO Input Processing
                    │
                    ▼
          Button Event Detection
                    │
                    ▼
         Navigation Controller
                    │
                    ▼
            DisplayUI Module
                    │
                    ▼
             SSD1306 OLED
```

Each button press is interpreted by the navigation controller before updating the active screen.

---

### 7.3 Navigation Responsibilities

The Button Navigation System is responsible for:

- Detecting user input
- Processing button events
- Navigating between menus
- Selecting menu entries
- Executing firmware functions
- Editing configuration values
- Confirming user actions
- Returning to previous screens
- Controlling interface navigation
- Synchronizing with the OLED display

These responsibilities allow the firmware to be operated entirely through the onboard controls.

---

### 7.4 Navigation Controls

The firmware supports multiple navigation actions that provide intuitive movement throughout the graphical interface.

| Navigation Action | Description |
|-------------------|-------------|
| Up | Move selection upward |
| Down | Move selection downward |
| Left / Back | Return to previous menu |
| Right / Enter | Open selected menu or execute action |
| Select | Confirm selection |
| Cancel | Exit current operation |

The exact hardware button mapping may vary depending on the device configuration while maintaining identical firmware behavior.

---

### 7.5 Menu Navigation

The firmware organizes interface elements using a hierarchical menu structure.

```
Main Menu
     │
     ├── Wireless Scanner
     │
     ├── Access Point Manager
     │
     ├── Station Manager
     │
     ├── Configuration
     │
     ├── System Information
     │
     ├── Display Settings
     │
     └── Utilities
```

Navigation is performed sequentially through menu items using the available buttons.

---

### 7.6 Input Processing

Each physical button generates an electrical input that is monitored through the ESP8266 GPIO interface.

The firmware continuously performs:

- GPIO monitoring
- Input sampling
- Button state detection
- Event generation
- Navigation processing
- Display updates

The navigation controller converts hardware input into firmware actions without interrupting other runtime operations.

---

### 7.7 Button Event Flow

The firmware processes button interaction using an event-driven workflow.

```
Button Press
      │
      ▼
GPIO Detection
      │
      ▼
Input Validation
      │
      ▼
Generate Navigation Event
      │
      ▼
Update Menu State
      │
      ▼
Render OLED Screen
```

Each navigation event immediately updates the user interface to reflect the new selection or executed operation.

---

### 7.8 Configuration Navigation

Configuration menus use the navigation subsystem to modify firmware parameters.

Typical operations include:

- Browsing configuration pages
- Selecting configurable items
- Incrementing values
- Decrementing values
- Saving settings
- Cancelling modifications
- Restoring previous values

Updated parameters are synchronized with the Configuration Manager and may be stored persistently through the EEPROM subsystem.

---

### 7.9 Runtime Integration

The Button Navigation System communicates with multiple firmware modules.

```
             Physical Buttons
                    │
                    ▼
          Navigation Controller
                    │
     ┌──────────────┼──────────────┐
     ▼              ▼              ▼
 DisplayUI    Configuration   Runtime Controller
     │              │              │
     └──────────────┼──────────────┘
                    ▼
             OLED Interface
```

This integration ensures that user input is immediately reflected across the firmware.

---

### 7.10 Navigation States

During operation, the navigation controller maintains the current interface state.

Typical runtime information includes:

- Current menu
- Selected item
- Parent menu
- Active configuration page
- Editing mode
- Confirmation dialogs
- System notifications
- Runtime status screens

Maintaining these states enables consistent navigation throughout the firmware.

---

### 7.11 User Interaction

The navigation subsystem supports a variety of user interactions, including:

- Browsing menus
- Opening submenus
- Viewing runtime information
- Changing configuration values
- Executing firmware operations
- Returning to previous screens
- Confirming actions
- Cancelling operations

These interactions allow complete standalone control of the device.

---

### 7.12 Design Characteristics

The Button Navigation System has been designed with the following objectives:

- Simple operation
- Fast response
- Low processing overhead
- Consistent navigation behavior
- Real-time user feedback
- Reliable input detection
- Seamless OLED integration
- Standalone usability

The navigation logic minimizes resource consumption while maintaining responsive interaction on the ESP8266 platform.

---

### 7.13 Navigation Features Summary

| Feature | Description |
|----------|-------------|
| Input Method | Physical Push Buttons |
| Interface | GPIO |
| Navigation Style | Hierarchical Menu System |
| Event Model | Event-Driven |
| Display Integration | SSD1306 OLED |
| Configuration Editing | Supported |
| Runtime Synchronization | Automatic |
| Menu Navigation | Multi-Level |
| Standalone Operation | Fully Supported |
| Firmware Integration | Runtime Controller |


## Wireless Scanning Engine

### 8.1 Overview

The Wireless Scanning Engine is responsible for discovering nearby IEEE 802.11 wireless networks and collecting information required by other firmware components. It serves as one of the primary runtime services within G-Shark, continuously interacting with the ESP8266 wireless hardware to retrieve broadcast management information from surrounding wireless infrastructure.

The scanning subsystem operates as a centralized information provider, supplying discovered network data to the OLED interface, embedded web application, command-line interface, configuration modules, and other firmware components. Scan results are maintained within runtime memory and are continuously refreshed to reflect changes in the surrounding wireless environment.

The scanning engine has been designed to provide efficient network discovery while minimizing resource utilization on the ESP8266 platform.

---

### 8.2 Scanning Architecture

```
                ESP8266 Wi-Fi Radio
                         │
                         ▼
              Wireless Scanning Engine
                         │
         ┌───────────────┼────────────────┐
         ▼               ▼                ▼
   Network Database   Runtime Cache   Channel Manager
         │               │                │
         └───────────────┼────────────────┘
                         ▼
               Runtime Controller
                         │
      ┌──────────────────┼──────────────────┐
      ▼                  ▼                  ▼
 OLED Interface      Embedded Web        CLI
```

The scanning engine continuously gathers wireless information and distributes processed results throughout the firmware.

---

### 8.3 Primary Responsibilities

The Wireless Scanning Engine performs several essential tasks during firmware operation.

Primary responsibilities include:

- Discovering nearby wireless networks
- Collecting network information
- Maintaining runtime scan results
- Updating wireless statistics
- Managing scan operations
- Synchronizing discovered data
- Refreshing network information
- Providing scan data to firmware modules

These operations form the foundation for wireless awareness throughout the firmware.

---

### 8.4 Scan Workflow

The scanning process follows a structured sequence that continuously updates the internal network database.

```
Initialize Scanner
        │
        ▼
Configure Wi-Fi Hardware
        │
        ▼
Start Scan Operation
        │
        ▼
Receive Beacon Information
        │
        ▼
Extract Network Parameters
        │
        ▼
Store Runtime Data
        │
        ▼
Update User Interfaces
        │
        ▼
Ready for Next Scan
```

Each completed scan updates the internal runtime structures used by the remaining firmware components.

---

### 8.5 Network Information Collection

During scanning, the firmware collects information broadcast by nearby wireless networks.

Typical information includes:

- Network Name (SSID)
- BSSID
- Operating Channel
- Signal Strength (RSSI)
- Authentication Information
- Encryption Information
- Broadcast Status
- Supported Capabilities

This information is stored within runtime memory and made available to authorized firmware modules.

---

### 8.6 Runtime Data Management

Discovered wireless information is maintained within an internal runtime database.

The runtime database enables:

- Fast data retrieval
- Continuous updates
- Duplicate filtering
- List management
- Sorting operations
- User interface synchronization
- Runtime statistics

The database is refreshed whenever new scan results become available.

---

### 8.7 Channel Processing

The scanning engine coordinates channel selection during network discovery.

Its responsibilities include:

- Channel switching
- Channel monitoring
- Scan timing
- Scan scheduling
- Runtime synchronization
- Hardware coordination

Channel management ensures that the firmware can observe wireless activity across supported channels.

---

### 8.8 Firmware Integration

The scanning engine exchanges information with multiple firmware subsystems.

```
             Wireless Scanner
                    │
      ┌─────────────┼─────────────┐
      ▼             ▼             ▼
 OLED Display   Web Interface    CLI
      │             │             │
      ▼             ▼             ▼
Configuration  Runtime Controller DisplayUI
```

This centralized architecture allows discovered wireless information to remain synchronized across all user interfaces.

---

### 8.9 Display Integration

Scan results are automatically presented through the OLED graphical interface.

Displayed information may include:

- Number of discovered networks
- Network names
- Signal strength
- Operating channel
- Security information
- Runtime statistics
- Current scan status
- Progress information

The display is updated dynamically as new scan results become available.

---

### 8.10 Embedded Web Integration

The embedded web interface retrieves scan information directly from the runtime scanning subsystem.

Browser-based functionality includes:

- Viewing discovered networks
- Refreshing scan results
- Displaying runtime information
- Browsing wireless information
- Monitoring scan progress

The web interface remains synchronized with the current runtime database.

---

### 8.11 Command-Line Integration

The Command-Line Interface provides access to scanning functionality through firmware commands.

Typical CLI operations include:

- Initiating scans
- Viewing scan results
- Inspecting network information
- Displaying runtime statistics
- Managing scan operations

The CLI interacts with the same runtime database used by the OLED and web interface.

---

### 8.12 Runtime Synchronization

The Wireless Scanning Engine continuously exchanges information with other firmware modules.

```
             Wi-Fi Hardware
                    │
                    ▼
        Wireless Scanning Engine
                    │
        ┌───────────┼───────────┐
        ▼           ▼           ▼
 Runtime Cache   DisplayUI   Web Server
        │           │           │
        └───────────┼───────────┘
                    ▼
          Runtime Controller
```

This synchronization ensures that all user interfaces display current wireless information.

---

### 8.13 Resource Management

The scanning subsystem has been optimized for operation on the ESP8266 platform.

Design objectives include:

- Efficient memory utilization
- Low processor overhead
- Controlled runtime allocation
- Optimized scan scheduling
- Continuous runtime synchronization
- Stable long-term operation
- Fast interface updates

These optimizations contribute to responsive firmware performance while maintaining accurate wireless information.

---

### 8.14 Scanning Engine Summary

| Feature | Description |
|----------|-------------|
| Function | Wireless Network Discovery |
| Wireless Standard | IEEE 802.11 |
| Runtime Updates | Continuous |
| Information Storage | Runtime Memory |
| Channel Management | Supported |
| OLED Integration | Yes |
| Web Interface Integration | Yes |
| CLI Integration | Yes |
| Runtime Synchronization | Automatic |
| Configuration Support | Integrated |
| Firmware Architecture | Modular |
| Platform | ESP8266 |

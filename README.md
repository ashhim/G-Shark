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
15. [Embedded Web UI](#embedded-web-ui)
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


## Access Point Management

### 9.1 Overview

The Access Point Management subsystem controls the wireless access point functionality of the G-Shark firmware. It is responsible for creating, configuring, managing, and monitoring the embedded IEEE 802.11 access point provided by the ESP8266 wireless hardware.

Operating as an independent firmware component, the subsystem integrates with the configuration manager, embedded web server, OLED interface, command-line interface, and runtime controller to provide centralized management of wireless network services.

The subsystem maintains the complete operational state of the access point throughout device execution and automatically restores saved configuration during system initialization.

---

### 9.2 Access Point Architecture

```
                  Runtime Controller
                          │
                          ▼
              Access Point Manager
                          │
        ┌─────────────────┼─────────────────┐
        ▼                 ▼                 ▼
 Configuration      Wi-Fi Driver      Client Monitor
        │                 │                 │
        └─────────────────┼─────────────────┘
                          ▼
                  ESP8266 Wi-Fi Radio
                          │
                          ▼
                  Wireless Access Point
```

The Access Point Manager coordinates wireless services while synchronizing runtime information across the firmware.

---

### 9.3 Primary Responsibilities

The subsystem performs all runtime operations required to manage the embedded wireless access point.

Primary responsibilities include:

- Access Point initialization
- SSID configuration
- Wireless channel selection
- Network parameter management
- Runtime status monitoring
- Client association tracking
- Configuration synchronization
- Runtime updates
- Service initialization
- System shutdown handling

These responsibilities ensure stable wireless network operation throughout device execution.

---

### 9.4 Initialization Process

The firmware initializes the access point through a predefined startup sequence.

```
Firmware Startup
        │
        ▼
Load Configuration
        │
        ▼
Initialize Wi-Fi Hardware
        │
        ▼
Configure Access Point
        │
        ▼
Apply Runtime Parameters
        │
        ▼
Start Wireless Services
        │
        ▼
Monitor Runtime State
```

Initialization occurs automatically during firmware startup after the configuration subsystem has restored saved settings.

---

### 9.5 Access Point Configuration

The subsystem supports runtime configuration of various wireless network parameters.

Typical configurable parameters include:

- Network name (SSID)
- Operating channel
- Visibility settings
- Authentication mode
- Maximum client count
- Network timeout
- Runtime behavior
- Startup preferences

Configuration values may be modified through the OLED interface, embedded web interface, or command-line interface.

---

### 9.6 Runtime Management

During operation, the Access Point Manager continuously monitors the wireless subsystem and maintains the current operational state.

Runtime responsibilities include:

- Maintaining service availability
- Updating network status
- Monitoring connected clients
- Applying configuration changes
- Synchronizing runtime information
- Reporting operational status
- Handling service transitions

The subsystem automatically updates shared runtime structures whenever changes occur.

---

### 9.7 Client Monitoring

The Access Point Manager maintains information regarding devices associated with the embedded access point.

Runtime information may include:

- Connected client count
- Client MAC addresses
- Association status
- Connection events
- Runtime statistics

This information is shared with the OLED interface, embedded web interface, and runtime controller.

---

### 9.8 Firmware Integration

The Access Point Manager communicates with several firmware modules.

```
              Access Point Manager
                      │
     ┌────────────────┼────────────────┐
     ▼                ▼                ▼
Configuration     Web Server      OLED Display
     │                │                │
     ▼                ▼                ▼
 EEPROM        Runtime Controller     CLI
```

The centralized architecture ensures consistent wireless information throughout the firmware.

---

### 9.9 OLED Integration

The OLED interface displays current access point information during runtime.

Displayed information may include:

- Access Point status
- Network name
- Operating channel
- Connected client count
- Runtime state
- Configuration status
- Service notifications

Display information is refreshed automatically whenever the access point state changes.

---

### 9.10 Embedded Web Integration

The embedded web interface communicates directly with the Access Point Manager to present current wireless information.

Browser-based functionality includes:

- Viewing access point status
- Modifying network parameters
- Applying configuration updates
- Displaying runtime information
- Monitoring connected clients

Changes made through the browser are synchronized with the runtime configuration manager.

---

### 9.11 Command-Line Integration

The Command-Line Interface provides direct access to access point management functions.

Typical CLI operations include:

- Viewing current configuration
- Starting wireless services
- Stopping wireless services
- Updating network parameters
- Displaying runtime status
- Inspecting client information

Commands are processed through the firmware command parser before execution.

---

### 9.12 Configuration Persistence

The subsystem integrates with EEPROM to preserve configuration between power cycles.

Persistent information may include:

- Network configuration
- Startup preferences
- Channel selection
- User-defined parameters
- Feature states

Saved configuration is restored automatically during firmware initialization.

---

### 9.13 Runtime Synchronization

The Access Point Manager continuously exchanges information with the runtime controller.

```
            Access Point Manager
                    │
        ┌───────────┼───────────┐
        ▼           ▼           ▼
 Configuration   OLED UI    Web Interface
        │           │           │
        └───────────┼───────────┘
                    ▼
          Runtime Controller
```

This synchronization ensures that every user interface reflects the current operational state of the wireless subsystem.

---

### 9.14 Design Characteristics

The Access Point Management subsystem has been designed with the following objectives:

- Reliable wireless service
- Runtime configurability
- Persistent configuration
- Efficient resource utilization
- Continuous status monitoring
- Modular architecture
- Real-time synchronization
- Standalone operation

These characteristics allow the subsystem to integrate seamlessly with the remaining firmware components.

---

### 9.15 Access Point Management Summary

| Feature | Description |
|----------|-------------|
| Function | Embedded Wireless Access Point Management |
| Platform | ESP8266 |
| Configuration | Runtime Configurable |
| Startup | Automatic Initialization |
| Configuration Storage | EEPROM |
| Runtime Monitoring | Supported |
| OLED Integration | Yes |
| Web Interface Integration | Yes |
| CLI Integration | Yes |
| Client Monitoring | Supported |
| Firmware Architecture | Modular |
| Runtime Synchronization | Automatic |
| Standalone Operation | Fully Supported |


## Station Management

### 10.1 Overview

The Station Management subsystem is responsible for monitoring, organizing, and maintaining information about wireless stations detected during firmware operation. It functions as the central repository for station-related runtime data and provides synchronized information to the OLED interface, embedded web application, command-line interface, and other firmware components.

The subsystem continuously receives wireless station information from the ESP8266 networking stack and maintains an updated runtime database that reflects the current wireless environment. Information collected by the Station Management subsystem is used throughout the firmware to support wireless monitoring, runtime statistics, device tracking, and system visualization.

Designed as an independent module within the firmware architecture, the subsystem operates continuously while maintaining efficient memory usage and fast runtime access to station information.

---

### 10.2 Station Management Architecture

```
                  ESP8266 Wi-Fi Hardware
                           │
                           ▼
                  Station Management
                           │
        ┌──────────────────┼──────────────────┐
        ▼                  ▼                  ▼
   Runtime Database   Client Monitor   Device Manager
        │                  │                  │
        └──────────────────┼──────────────────┘
                           ▼
                  Runtime Controller
                           │
      ┌────────────────────┼────────────────────┐
      ▼                    ▼                    ▼
 OLED Interface     Embedded Web UI          CLI
```

The subsystem maintains runtime station information while synchronizing updates across all user interfaces.

---

### 10.3 Primary Responsibilities

The Station Management subsystem performs several runtime functions throughout device operation.

Primary responsibilities include:

- Detecting wireless stations
- Maintaining station information
- Recording MAC addresses
- Monitoring station activity
- Updating runtime data
- Synchronizing user interfaces
- Managing station lists
- Providing runtime statistics
- Supporting configuration services
- Coordinating with other firmware modules

These responsibilities ensure that station information remains current and accessible throughout the firmware.

---

### 10.4 Station Detection Workflow

Station information is collected through a continuous runtime process.

```
Initialize Wireless Interface
            │
            ▼
Monitor Wireless Traffic
            │
            ▼
Detect Station Activity
            │
            ▼
Extract Station Information
            │
            ▼
Update Runtime Database
            │
            ▼
Refresh User Interfaces
            │
            ▼
Continue Monitoring
```

The process repeats continuously during firmware execution, allowing the station database to remain synchronized with the surrounding wireless environment.

---

### 10.5 Station Information

For each detected station, the subsystem maintains runtime information that may include:

- MAC Address
- Signal Strength (RSSI)
- Operating Channel
- Associated Access Point
- Detection Status
- Runtime Activity
- Last Detection Time
- Connection Information

The exact information available depends on runtime conditions and firmware operation.

---

### 10.6 Runtime Database

Detected station information is stored within an internal runtime database.

The database supports:

- Fast lookup operations
- Duplicate filtering
- Dynamic updates
- Runtime synchronization
- Efficient memory utilization
- User interface integration
- Runtime statistics generation

Information is updated whenever new wireless activity is observed.

---

### 10.7 Client Monitoring

The subsystem continuously observes wireless station activity throughout firmware execution.

Monitoring operations include:

- Station discovery
- Runtime updates
- Signal monitoring
- Activity tracking
- Client list maintenance
- Status synchronization
- Runtime statistics

This continuous monitoring ensures that displayed information reflects the current operating environment.

---

### 10.8 OLED Integration

The OLED interface retrieves station information directly from the Station Management subsystem.

Displayed information may include:

- Total detected stations
- Station list
- Signal strength
- Runtime status
- Current selection
- Station details
- Activity indicators
- System notifications

Display updates occur automatically whenever station information changes.

---

### 10.9 Embedded Web Integration

The embedded web interface communicates with the Station Management subsystem to present station information through the browser.

Browser-based functionality includes:

- Viewing detected stations
- Refreshing station information
- Displaying runtime statistics
- Monitoring wireless activity
- Browsing station details

All displayed information is synchronized with the runtime database maintained by the firmware.

---

### 10.10 Command-Line Integration

The Command-Line Interface provides direct access to station information through firmware commands.

Typical CLI functionality includes:

- Viewing station lists
- Displaying runtime information
- Inspecting station details
- Refreshing station data
- Displaying statistics
- Runtime monitoring

The CLI operates on the same runtime data used by the OLED and embedded web interface.

---

### 10.11 Runtime Synchronization

The Station Management subsystem exchanges information with multiple firmware components.

```
              Station Management
                      │
        ┌─────────────┼─────────────┐
        ▼             ▼             ▼
 OLED Display     Embedded Web      CLI
        │             │             │
        └─────────────┼─────────────┘
                      ▼
             Runtime Controller
```

Centralized synchronization ensures consistent station information throughout the firmware.

---

### 10.12 Resource Management

The subsystem has been designed to efficiently utilize the limited resources available on the ESP8266 platform.

Optimization objectives include:

- Efficient memory allocation
- Fast data retrieval
- Runtime synchronization
- Duplicate filtering
- Low processing overhead
- Stable long-term operation
- Responsive interface updates

These optimizations contribute to reliable operation during extended runtime.

---

### 10.13 Design Characteristics

The Station Management subsystem has been designed with the following principles:

- Modular architecture
- Continuous monitoring
- Efficient resource utilization
- Runtime synchronization
- Centralized information management
- Standalone operation
- Real-time updates
- Seamless integration with other firmware modules

The modular implementation allows future expansion without affecting unrelated components.

---

### 10.14 Station Management Summary

| Feature | Description |
|----------|-------------|
| Function | Wireless Station Monitoring |
| Runtime Database | Dynamic |
| Information Updates | Continuous |
| Platform | ESP8266 |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| CLI Integration | Yes |
| Runtime Synchronization | Automatic |
| Memory Management | Optimized |
| Modular Architecture | Yes |
| Standalone Operation | Fully Supported |
| Firmware Integration | Runtime Controller |
```


## Attack Framework

### 11.1 Overview

The Attack Framework is a modular runtime subsystem responsible for coordinating packet-oriented wireless operations within the G-Shark firmware. Rather than implementing all functionality inside a single execution routine, the framework organizes supported wireless operations into independent modules that share a common execution pipeline, runtime controller, and configuration interface.

The framework acts as a central management layer between the firmware runtime and the ESP8266 wireless hardware. It is responsible for scheduling operations, managing execution states, allocating packet buffers, synchronizing user interfaces, and maintaining runtime statistics.

Designed using a modular architecture, the framework allows individual packet-processing modules to operate independently while sharing common initialization, configuration, memory management, and event handling services.

---

### 11.2 Framework Architecture

```text
                    Runtime Controller
                            │
                            ▼
                  Attack Framework Core
                            │
        ┌───────────────────┼───────────────────┐
        ▼                   ▼                   ▼
  Packet Manager      Scheduler Engine    State Manager
        │                   │                   │
        └───────────────────┼───────────────────┘
                            ▼
                 ESP8266 Wireless Driver
                            │
                            ▼
                   IEEE 802.11 Interface
```

The framework coordinates packet-oriented operations while maintaining synchronization with the rest of the firmware.

---

### 11.3 Primary Responsibilities

The Attack Framework is responsible for:

- Managing packet-oriented runtime modules
- Initializing execution environments
- Coordinating packet scheduling
- Managing runtime state
- Allocating transmission resources
- Synchronizing configuration values
- Updating user interfaces
- Recording runtime statistics
- Managing execution lifecycle
- Coordinating wireless operations

---

### 11.4 Execution Lifecycle

Each runtime operation follows a common execution sequence.

```text
Initialize Framework
         │
         ▼
Load Configuration
         │
         ▼
Allocate Resources
         │
         ▼
Start Runtime Module
         │
         ▼
Monitor Execution
         │
         ▼
Update Runtime State
         │
         ▼
Release Resources
         │
         ▼
Return to Idle
```

Using a common lifecycle simplifies integration of additional modules while maintaining consistent runtime behavior.

---

### 11.5 Packet Management

The Packet Manager is responsible for handling packet buffers used throughout the framework.

Its responsibilities include:

- Packet buffer allocation
- Buffer reuse
- Memory management
- Transmission preparation
- Runtime synchronization
- Resource cleanup

Centralized packet management reduces memory fragmentation and improves runtime efficiency on the ESP8266 platform.

---

### 11.6 Scheduler Engine

The Scheduler Engine coordinates the execution of packet-processing tasks.

Primary functions include:

- Task scheduling
- Runtime sequencing
- Timing coordination
- Execution control
- State transitions
- Runtime monitoring

The scheduler ensures that active operations execute in an organized and predictable manner.

---

### 11.7 State Management

The framework maintains the current execution state of each runtime module.

Typical runtime states include:

- Idle
- Initializing
- Ready
- Active
- Paused
- Completed
- Stopped
- Error

State information is shared with the OLED interface, embedded web interface, and command-line interface.

---

### 11.8 Configuration Integration

The framework retrieves operational parameters from the Configuration Manager during initialization.

Configuration synchronization includes:

- Loading saved settings
- Applying runtime parameters
- Updating active modules
- Validating configuration values
- Restoring persistent preferences

Configuration changes are propagated throughout the framework without requiring firmware recompilation.

---

### 11.9 Runtime Integration

The Attack Framework exchanges information with multiple firmware components.

```text
              Attack Framework
                     │
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 Configuration   OLED Display   Web Interface
      │              │              │
      ▼              ▼              ▼
 EEPROM            CLI       Runtime Controller
```

This integration ensures consistent runtime information across all user interfaces.

---

### 11.10 Resource Management

The framework has been designed for efficient operation on resource-constrained embedded hardware.

Design objectives include:

- Efficient RAM utilization
- Shared packet buffers
- Low processing overhead
- Predictable execution
- Stable long-term operation
- Runtime synchronization
- Modular extensibility

These principles help maintain responsive firmware performance during extended operation.

---

### 11.11 Design Characteristics

The Attack Framework follows several architectural principles:

- Modular implementation
- Centralized execution control
- Shared runtime services
- Independent functional modules
- Persistent configuration support
- Event-driven operation
- Efficient memory management
- Tight integration with the firmware runtime

---

### 11.12 Attack Framework Summary

| Feature | Description |
|----------|-------------|
| Architecture | Modular Runtime Framework |
| Execution Model | Event-Driven |
| Runtime Coordination | Centralized |
| Packet Management | Shared Buffer System |
| Scheduler | Integrated |
| State Management | Runtime Controlled |
| Configuration | Persistent via EEPROM |
| OLED Integration | Yes |
| Web Interface Integration | Yes |
| CLI Integration | Yes |
| Platform | ESP8266 |
| Firmware Integration | Runtime Controller |


## Beacon Frame System

### 12.1 Overview

The Beacon Frame System is a dedicated firmware subsystem responsible for generating, managing, scheduling, and transmitting IEEE 802.11 Beacon management frames through the ESP8266 wireless interface. It provides a modular framework for constructing beacon packets, controlling transmission timing, managing runtime configuration, and coordinating packet delivery with the wireless hardware.

The subsystem operates as an independent component within the firmware architecture while maintaining synchronization with the runtime controller, configuration manager, OLED interface, embedded web application, and command-line interface. It manages the complete beacon transmission lifecycle, from packet construction and parameter initialization to scheduled transmission and runtime monitoring.

Designed with a modular architecture, the Beacon Frame System separates packet generation, transmission scheduling, configuration handling, and runtime management into dedicated components, improving maintainability and simplifying future firmware expansion.

---

### 12.2 System Architecture

```text
                  Runtime Controller
                          │
                          ▼
                Beacon Frame System
                          │
        ┌─────────────────┼─────────────────┐
        ▼                 ▼                 ▼
 Packet Builder    Scheduler Engine   State Manager
        │                 │                 │
        └─────────────────┼─────────────────┘
                          ▼
                 ESP8266 Wi-Fi Driver
                          │
                          ▼
                IEEE 802.11 Radio Hardware
```

The subsystem coordinates beacon frame generation and transmission while remaining synchronized with the overall firmware runtime.

---

### 12.3 Primary Responsibilities

The Beacon Frame System performs the following responsibilities during runtime:

- Beacon frame construction
- Packet buffer management
- Runtime parameter application
- Transmission scheduling
- Execution monitoring
- Runtime synchronization
- State management
- Configuration loading
- Resource allocation
- Status reporting

---

### 12.4 Packet Construction

The subsystem constructs IEEE 802.11 Beacon management frames using firmware-defined runtime parameters.

The packet construction process includes:

- Header generation
- Information element insertion
- Frame parameter configuration
- Runtime data integration
- Buffer preparation
- Packet validation

Completed frames are prepared for transmission through the ESP8266 wireless interface.

---

### 12.5 Transmission Workflow

The Beacon Frame System follows a structured execution sequence.

```text
Initialize Module
        │
        ▼
Load Configuration
        │
        ▼
Generate Beacon Frame
        │
        ▼
Prepare Packet Buffer
        │
        ▼
Schedule Transmission
        │
        ▼
Transmit Frame
        │
        ▼
Update Runtime Status
        │
        ▼
Repeat Until Stopped
```

This workflow ensures consistent packet generation throughout firmware operation.

---

### 12.6 Scheduler Engine

The Scheduler Engine controls the timing of beacon frame transmission.

Its responsibilities include:

- Scheduling transmission intervals
- Runtime timing control
- Execution sequencing
- Runtime synchronization
- Transmission monitoring
- Resource coordination

The scheduler operates continuously while the subsystem remains active.

---

### 12.7 Runtime Configuration

The Beacon Frame System retrieves operational parameters from the Configuration Manager during initialization.

Runtime configuration may include:

- Wireless channel
- Transmission interval
- Packet timing
- Runtime options
- System preferences
- Feature states

Configuration values remain synchronized with the runtime controller throughout device operation.

---

### 12.8 State Management

The subsystem maintains runtime information describing its current operational state.

Typical states include:

- Idle
- Initializing
- Ready
- Active
- Paused
- Completed
- Stopped
- Error

These states are made available to the OLED interface, embedded web interface, and command-line interface.

---

### 12.9 Firmware Integration

The Beacon Frame System communicates with multiple firmware components.

```text
              Beacon Frame System
                      │
      ┌───────────────┼───────────────┐
      ▼               ▼               ▼
 Configuration   OLED Display   Web Interface
      │               │               │
      ▼               ▼               ▼
 EEPROM             CLI       Runtime Controller
```

This centralized communication model ensures consistent runtime information throughout the firmware.

---

### 12.10 OLED Integration

The OLED interface displays runtime information related to the Beacon Frame System.

Displayed information may include:

- Module status
- Runtime state
- Operating channel
- Execution status
- Runtime counters
- Configuration status
- System notifications

Display updates occur automatically as the subsystem state changes.

---

### 12.11 Embedded Web Integration

The embedded web interface communicates directly with the Beacon Frame System to provide browser-based interaction.

Supported functionality includes:

- Viewing runtime status
- Displaying configuration
- Updating operational parameters
- Monitoring execution
- Synchronizing runtime information

Configuration changes are applied immediately through the firmware runtime.

---

### 12.12 Command-Line Integration

The Command-Line Interface provides access to subsystem functionality through firmware commands.

Typical operations include:

- Viewing runtime information
- Displaying current configuration
- Starting execution
- Stopping execution
- Inspecting module status
- Displaying statistics

Commands are processed through the firmware command parser before execution.

---

### 12.13 Resource Management

The subsystem has been optimized for efficient operation on the ESP8266 platform.

Optimization objectives include:

- Efficient memory utilization
- Shared packet buffers
- Predictable runtime behavior
- Low processor overhead
- Stable long-term execution
- Runtime synchronization
- Efficient packet scheduling

These optimizations contribute to reliable firmware performance.

---

### 12.14 Design Characteristics

The Beacon Frame System has been designed with the following architectural principles:

- Modular implementation
- Event-driven execution
- Shared runtime services
- Efficient resource management
- Persistent configuration support
- Runtime synchronization
- Independent subsystem design
- Scalable architecture

The modular implementation simplifies maintenance while supporting future firmware enhancements.

---

### 12.15 Beacon Frame System Summary

| Feature | Description |
|----------|-------------|
| Function | IEEE 802.11 Beacon Frame Management |
| Architecture | Modular Runtime Subsystem |
| Packet Generation | Integrated |
| Transmission Scheduling | Supported |
| Runtime Configuration | Dynamic |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| CLI Integration | Yes |
| Runtime Synchronization | Automatic |
| Configuration Storage | EEPROM |
| Platform | ESP8266 |
| Firmware Integration | Runtime Controller |
```



## Probe Request System

### 13.1 Overview

The Probe Request System is a dedicated firmware subsystem responsible for generating, scheduling, and transmitting IEEE 802.11 Probe Request management frames through the ESP8266 wireless interface. It provides a modular framework for packet construction, transmission scheduling, runtime configuration, and execution management while operating as an integrated component of the G-Shark firmware.

The subsystem coordinates with the runtime controller, wireless driver, configuration manager, OLED interface, embedded web application, and command-line interface to maintain synchronized operation throughout the device lifecycle. By separating probe request processing into an independent module, the firmware maintains a clean architecture that simplifies maintenance, improves scalability, and allows future expansion.

---

### 13.2 System Architecture

```text
                  Runtime Controller
                          │
                          ▼
                 Probe Request System
                          │
        ┌─────────────────┼─────────────────┐
        ▼                 ▼                 ▼
 Packet Builder    Scheduler Engine   State Manager
        │                 │                 │
        └─────────────────┼─────────────────┘
                          ▼
                 ESP8266 Wi-Fi Driver
                          │
                          ▼
                IEEE 802.11 Radio Hardware
```

The Probe Request System operates as a modular runtime service while remaining synchronized with the firmware architecture.

---

### 13.3 Primary Responsibilities

The subsystem performs several runtime responsibilities, including:

- Probe request frame generation
- Packet construction
- Runtime scheduling
- Transmission management
- State monitoring
- Configuration synchronization
- Packet buffer management
- Runtime statistics
- Resource allocation
- Firmware integration

---

### 13.4 Packet Construction

The subsystem constructs IEEE 802.11 Probe Request management frames using runtime configuration values supplied by the firmware.

The packet construction process includes:

- MAC header generation
- Information element creation
- Frame parameter initialization
- Runtime value insertion
- Buffer preparation
- Packet validation

After construction, the completed frame is prepared for transmission through the ESP8266 wireless interface.

---

### 13.5 Execution Workflow

The Probe Request System follows a structured execution sequence.

```text
Initialize Module
        │
        ▼
Load Configuration
        │
        ▼
Generate Probe Request
        │
        ▼
Prepare Packet Buffer
        │
        ▼
Schedule Transmission
        │
        ▼
Transmit Packet
        │
        ▼
Update Runtime Status
        │
        ▼
Continue Execution
```

This workflow ensures consistent runtime behavior while maintaining synchronization with other firmware components.

---

### 13.6 Scheduler Engine

The Scheduler Engine manages the timing and sequencing of probe request transmission.

Primary responsibilities include:

- Transmission scheduling
- Runtime timing control
- Execution sequencing
- Resource coordination
- State monitoring
- Runtime synchronization

The scheduler continuously coordinates packet transmission while the subsystem remains active.

---

### 13.7 Runtime Configuration

Operational parameters are obtained from the Configuration Manager during subsystem initialization.

Runtime configuration may include:

- Wireless channel
- Transmission interval
- Execution timing
- Runtime options
- System preferences
- Feature states

Configuration updates are propagated throughout the subsystem without requiring firmware recompilation.

---

### 13.8 State Management

The subsystem maintains runtime information describing its current execution state.

Typical runtime states include:

- Idle
- Initializing
- Ready
- Active
- Paused
- Completed
- Stopped
- Error

State information is synchronized with the OLED interface, embedded web interface, and command-line interface.

---

### 13.9 Firmware Integration

The Probe Request System exchanges information with multiple firmware components.

```text
             Probe Request System
                      │
      ┌───────────────┼───────────────┐
      ▼               ▼               ▼
 Configuration   OLED Display   Web Interface
      │               │               │
      ▼               ▼               ▼
 EEPROM             CLI       Runtime Controller
```

This centralized communication architecture ensures consistent runtime information across the firmware.

---

### 13.10 OLED Integration

The OLED interface displays runtime information generated by the Probe Request System.

Displayed information may include:

- Module status
- Runtime state
- Operating channel
- Execution progress
- Runtime counters
- Configuration status
- System notifications

The display automatically updates whenever subsystem state changes occur.

---

### 13.11 Embedded Web Integration

The embedded web interface communicates directly with the Probe Request System to provide browser-based management and monitoring.

Supported functionality includes:

- Viewing runtime status
- Displaying configuration values
- Updating operational parameters
- Monitoring execution
- Viewing runtime statistics

Browser interactions are synchronized directly with the firmware runtime.

---

### 13.12 Command-Line Integration

The Command-Line Interface provides access to subsystem functionality through firmware commands.

Typical CLI functionality includes:

- Viewing runtime status
- Displaying configuration
- Starting execution
- Stopping execution
- Monitoring module activity
- Viewing runtime statistics

All commands are processed through the firmware command parser before execution.

---

### 13.13 Resource Management

The Probe Request System has been optimized for efficient execution on the ESP8266 platform.

Optimization objectives include:

- Efficient RAM utilization
- Shared packet buffers
- Predictable execution timing
- Low processor overhead
- Stable runtime operation
- Runtime synchronization
- Efficient scheduling

These optimizations contribute to reliable long-term firmware performance.

---

### 13.14 Design Characteristics

The Probe Request System has been designed with the following architectural principles:

- Modular implementation
- Event-driven execution
- Shared runtime services
- Efficient memory management
- Persistent configuration support
- Runtime synchronization
- Independent subsystem design
- Expandable architecture

These principles simplify firmware maintenance while supporting future feature development.

---

### 13.15 Probe Request System Summary

| Feature | Description |
|----------|-------------|
| Function | IEEE 802.11 Probe Request Frame Management |
| Architecture | Modular Runtime Subsystem |
| Packet Generation | Integrated |
| Transmission Scheduling | Supported |
| Runtime Configuration | Dynamic |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| CLI Integration | Yes |
| Runtime Synchronization | Automatic |
| Configuration Storage | EEPROM |
| Platform | ESP8266 |
| Firmware Integration | Runtime Controller |


## Captive Portal Framework

### 14.1 Overview

The Captive Portal Framework is an integrated firmware subsystem responsible for providing browser-based interaction through the embedded HTTP server and the onboard SPIFFS filesystem. It enables users to access a locally hosted web application directly from a wireless connection without requiring an external web server or additional software.

The framework combines wireless networking, web serving, filesystem management, runtime APIs, and configuration services into a unified architecture. Static web resources are stored within the SPIFFS filesystem and delivered by the embedded web server, while dynamic information is exchanged directly with the firmware through internal communication interfaces.

Designed as a modular component, the Captive Portal Framework operates independently while remaining synchronized with the runtime controller, configuration manager, OLED interface, and wireless subsystems.

---

### 14.2 Framework Architecture

```text
                    User Device
            (Phone / Tablet / Computer)
                        │
                        ▼
                ESP8266 Access Point
                        │
                        ▼
              Embedded HTTP Server
                        │
        ┌───────────────┼────────────────┐
        ▼               ▼                ▼
      SPIFFS        Runtime API     Configuration
        │               │                │
        └───────────────┼────────────────┘
                        ▼
               Captive Portal Framework
                        │
                        ▼
                Runtime Controller
```

The framework delivers static web resources while providing synchronized communication with the firmware runtime.

---

### 14.3 Primary Responsibilities

The Captive Portal Framework performs several core responsibilities throughout firmware operation.

Primary responsibilities include:

- Hosting the embedded web application
- Serving static web resources
- Managing browser requests
- Processing runtime API communication
- Synchronizing firmware data
- Loading filesystem resources
- Supporting runtime configuration
- Coordinating browser interaction
- Managing portal sessions
- Integrating with the embedded web server

---

### 14.4 Framework Components

The Captive Portal Framework consists of multiple cooperating software components.

| Component | Responsibility |
|----------|----------------|
| Embedded HTTP Server | Processes browser requests |
| SPIFFS Filesystem | Stores web resources |
| Runtime API | Exchanges data with firmware |
| Configuration Manager | Applies runtime settings |
| Runtime Controller | Coordinates subsystem communication |
| OLED Interface | Displays runtime status |

Each component performs a dedicated responsibility while contributing to the overall browser experience.

---

### 14.5 Web Resource Management

All browser resources are stored within the onboard SPIFFS filesystem.

Supported resource types include:

- HTML documents
- CSS stylesheets
- JavaScript files
- Images
- Icons
- Fonts
- Audio files
- JSON resources
- SVG graphics
- Additional static assets

During runtime, these resources are served directly by the embedded HTTP server without requiring external storage.

---

### 14.6 Custom Portal Support

The Captive Portal Framework has been designed to support complete replacement and customization of the embedded web application.

Developers may deploy their own browser interface by replacing the resources stored within the SPIFFS filesystem.

Supported customization includes:

- Complete HTML replacement
- Custom CSS styling
- JavaScript applications
- Images and logos
- Icons
- Fonts
- Audio resources
- Custom page layouts
- Additional static resources

This architecture allows the browser interface to be redesigned independently of the firmware source code while preserving communication with the underlying runtime services.

---

### 14.7 Runtime Communication

The browser interface communicates directly with the firmware through internal runtime APIs.

The communication layer supports:

- Runtime information retrieval
- Configuration updates
- Status synchronization
- System monitoring
- User interaction
- Firmware control
- Runtime notifications

All exchanged information remains synchronized with the firmware during operation.

---

### 14.8 Request Processing Workflow

Browser requests are processed through the embedded web server before interacting with the firmware.

```text
Browser Request
        │
        ▼
Embedded HTTP Server
        │
        ▼
Determine Resource Type
        │
 ┌──────┴─────────┐
 ▼                ▼
Static File    Runtime API
 │                │
 ▼                ▼
SPIFFS       Firmware Runtime
 │                │
 └──────┬─────────┘
        ▼
HTTP Response
        │
        ▼
Browser
```

Static resources are delivered directly from SPIFFS, while runtime requests are processed by the firmware.

---

### 14.9 Firmware Integration

The Captive Portal Framework communicates with multiple firmware modules.

```text
            Captive Portal Framework
                     │
     ┌───────────────┼────────────────┐
     ▼               ▼                ▼
 Embedded Web     Configuration   Runtime Controller
     │               │                │
     ▼               ▼                ▼
 SPIFFS          EEPROM         OLED Interface
```

This architecture ensures that browser interactions remain synchronized with all runtime components.

---

### 14.10 Configuration Integration

The framework retrieves operational parameters from the Configuration Manager.

Configuration includes:

- Access Point settings
- Runtime preferences
- Portal configuration
- Startup behavior
- User preferences
- Feature states

Changes are applied dynamically without requiring firmware recompilation.

---

### 14.11 Standalone Operation

The Captive Portal Framework operates entirely on the ESP8266 hardware.

Its integrated architecture includes:

- Embedded HTTP server
- Local filesystem
- Runtime API
- Configuration services
- Browser interface
- Wireless networking

Because all required components are contained within the firmware, no external web server or cloud infrastructure is required for operation.

---

### 14.12 Design Characteristics

The Captive Portal Framework has been designed according to several architectural principles.

These include:

- Modular implementation
- Complete standalone operation
- Runtime synchronization
- Dynamic configuration
- Efficient filesystem access
- Expandable web architecture
- Independent resource management
- Firmware integration

These characteristics simplify long-term maintenance and future development.

---

### 14.13 Captive Portal Framework Summary

| Feature | Description |
|----------|-------------|
| Function | Embedded Browser-Based Interface |
| HTTP Server | Integrated |
| Filesystem | SPIFFS |
| Static Resources | HTML, CSS, JS, Images, Fonts, Audio |
| Runtime Communication | Internal API |
| Custom Portal Support | Fully Supported |
| Resource Replacement | Fully Supported |
| Configuration | Runtime Configurable |
| OLED Integration | Yes |
| EEPROM Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |
``


## Embedded Web Interface

### 15.1 Overview

The Embedded Web Interface provides a browser-based management environment that operates directly on the ESP8266 without requiring external software or cloud-based services. It serves as one of the primary user interfaces of the G-Shark firmware alongside the OLED display and Command-Line Interface (CLI), allowing users to interact with the firmware through any standard web browser connected to the device.

The interface is hosted entirely within the firmware using the integrated HTTP server and the onboard SPIFFS filesystem. Static resources such as HTML, CSS, JavaScript, images, fonts, and other assets are served directly from flash memory, while dynamic information is exchanged with the firmware through internal runtime APIs.

The Embedded Web Interface has been designed using a modular architecture, allowing the web application to evolve independently of the firmware core while maintaining synchronized communication with all runtime subsystems.

---

### 15.2 System Architecture

```text
               User Web Browser
        (Desktop / Mobile / Tablet)
                    │
                    ▼
            Embedded HTTP Server
                    │
       ┌────────────┼────────────┐
       ▼            ▼            ▼
    SPIFFS      Runtime API   Web Router
       │            │            │
       └────────────┼────────────┘
                    ▼
         Embedded Web Interface
                    │
                    ▼
          Firmware Runtime Services
```

The browser communicates directly with the embedded web server, which serves static resources and forwards runtime requests to the firmware.

---

### 15.3 Primary Responsibilities

The Embedded Web Interface performs several important responsibilities within the firmware.

Primary responsibilities include:

- Displaying firmware information
- Providing browser-based device management
- Presenting runtime status
- Synchronizing configuration values
- Processing user interaction
- Displaying wireless information
- Loading SPIFFS resources
- Communicating with runtime services
- Presenting graphical controls
- Providing responsive browser operation

---

### 15.4 Interface Components

The web application is composed of several logical components.

| Component | Responsibility |
|----------|----------------|
| HTML Pages | User interface structure |
| CSS Stylesheets | Visual appearance |
| JavaScript | Runtime interaction |
| Runtime API | Firmware communication |
| HTTP Server | Browser request handling |
| SPIFFS | Resource storage |
| Configuration Manager | Runtime settings |

Each component performs a dedicated function while operating together as a unified browser application.

---

### 15.5 User Interface Layout

The browser interface presents firmware information through organized pages and interactive controls.

Typical interface elements include:

- Navigation menus
- Information panels
- Configuration pages
- Status indicators
- System notifications
- Interactive controls
- Runtime statistics
- Device information
- Configuration forms
- Management pages

The interface is designed to remain responsive across desktop and mobile browsers.

---

### 15.6 Runtime Communication

The web interface exchanges information with the firmware through an internal runtime communication layer.

Supported communication includes:

- Runtime information retrieval
- Configuration updates
- Status synchronization
- System monitoring
- User commands
- Firmware control
- Dynamic interface updates

Communication occurs entirely within the embedded firmware environment.

---

### 15.7 SPIFFS Integration

All web interface resources are stored within the onboard SPIFFS filesystem.

Supported resources include:

- HTML documents
- CSS files
- JavaScript files
- Images
- Logos
- Icons
- Fonts
- Audio files
- SVG graphics
- Additional static assets

Resources are loaded directly from flash memory during browser requests.

---

### 15.8 Browser Request Processing

Every browser request follows a structured processing sequence.

```text
Browser Request
        │
        ▼
HTTP Server
        │
        ▼
Identify Requested Resource
        │
 ┌──────┴─────────┐
 ▼                ▼
SPIFFS File    Runtime API
 │                │
 ▼                ▼
Load File    Process Request
 │                │
 └──────┬─────────┘
        ▼
Generate Response
        │
        ▼
Browser
```

This workflow provides efficient handling of both static resources and dynamic runtime requests.

---

### 15.9 Firmware Synchronization

The Embedded Web Interface remains synchronized with multiple firmware modules.

```text
          Embedded Web Interface
                    │
     ┌──────────────┼──────────────┐
     ▼              ▼              ▼
 Wireless       Configuration   Runtime
  Services          Manager     Controller
     │              │              │
     ▼              ▼              ▼
 OLED Display     EEPROM        SPIFFS
```

Synchronization ensures that browser information accurately reflects the current firmware state.

---

### 15.10 Responsive Design

The interface has been designed to operate across multiple device types.

Supported platforms include:

- Desktop computers
- Laptop computers
- Smartphones
- Tablets
- Embedded browsers

The layout automatically adapts to different screen sizes while maintaining usability.

---

### 15.11 Customization Support

The Embedded Web Interface has been designed for complete customization through replacement of the web resources stored in the SPIFFS filesystem.

Developers may customize:

- HTML page layouts
- CSS styling
- JavaScript functionality
- Images
- Logos
- Icons
- Fonts
- Audio resources
- Additional static files

Because the browser interface is stored separately from the firmware executable, visual customization can be performed without modifying the firmware source code.

---

### 15.12 Integration with Other Subsystems

The Embedded Web Interface communicates with multiple firmware components.

Integrated subsystems include:

- Wireless Scanning Engine
- Access Point Management
- Station Management
- Configuration Manager
- Captive Portal Framework
- OLED User Interface
- Command-Line Interface
- EEPROM Manager
- SPIFFS Manager
- Runtime Controller

This integration provides a consistent user experience across all firmware interfaces.

---

### 15.13 Design Characteristics

The Embedded Web Interface has been designed according to several architectural principles.

These include:

- Modular implementation
- Standalone operation
- Responsive browser compatibility
- Dynamic runtime synchronization
- Efficient resource loading
- Runtime configuration support
- Expandable interface architecture
- Independent resource management

These characteristics simplify maintenance while supporting future enhancements.

---

### 15.14 Embedded Web Interface Summary

| Feature | Description |
|----------|-------------|
| Function | Browser-Based Firmware Interface |
| Web Server | Integrated HTTP Server |
| Filesystem | SPIFFS |
| Resource Types | HTML, CSS, JavaScript, Images, Fonts, Audio |
| Runtime Communication | Internal Firmware API |
| Responsive Design | Supported |
| Runtime Synchronization | Automatic |
| Configuration | Runtime Configurable |
| Resource Customization | Fully Supported |
| OLED Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |




## SPIFFS File System

### 16.1 Overview

The SPI Flash File System (SPIFFS) provides the persistent storage layer used by the G-Shark firmware for hosting the embedded web application and other static resources. It allows the ESP8266 to serve web content directly from onboard flash memory without requiring external storage devices or remote servers.

The filesystem operates independently of the firmware executable. While the firmware occupies the program memory region, SPIFFS stores browser resources, media files, configuration assets, and other static content that can be accessed through the embedded HTTP server.

By separating executable firmware from web resources, SPIFFS enables independent customization and maintenance of the browser interface while preserving the core firmware architecture.

---

### 16.2 Filesystem Architecture

```text
                  ESP8266 Flash Memory
┌───────────────────────────────────────────────────────┐
│                                                       │
│  Bootloader                                            │
│───────────────────────────────────────────────────────│
│                                                       │
│  Firmware Application                                 │
│                                                       │
│───────────────────────────────────────────────────────│
│                                                       │
│  EEPROM Emulation                                     │
│                                                       │
│───────────────────────────────────────────────────────│
│                                                       │
│                SPIFFS File System                     │
│                                                       │
│   HTML • CSS • JavaScript • Images • Audio • Fonts   │
│                                                       │
└───────────────────────────────────────────────────────┘
```

The firmware and SPIFFS operate independently while sharing the same onboard flash memory.

---

### 16.3 Primary Responsibilities

The SPIFFS subsystem is responsible for:

- Mounting the filesystem during startup
- Storing web resources
- Providing file access
- Managing static assets
- Supporting browser requests
- Loading runtime resources
- Reading configuration files
- Delivering media assets
- Managing persistent storage
- Supporting web interface customization

---

### 16.4 Filesystem Initialization

The filesystem is initialized during firmware startup before the embedded web server becomes available.

```text
Power On
      │
      ▼
Firmware Startup
      │
      ▼
Initialize Flash Storage
      │
      ▼
Mount SPIFFS
      │
      ▼
Verify Filesystem
      │
      ▼
Load Runtime Resources
      │
      ▼
Start HTTP Server
      │
      ▼
Filesystem Ready
```

Successful filesystem initialization is required before browser resources can be served.

---

### 16.5 Directory Structure

The SPIFFS image typically contains directories and static resources required by the embedded web interface.

```text
SPIFFS
│
├── web/
│   ├── index.html
│   ├── css/
│   ├── js/
│   ├── images/
│   ├── fonts/
│   └── language/
│
├── nameme/
│
├── logo.png
├── instapage.jpg
├── music.mp3
└── additional resources
```

The exact directory layout depends on the firmware version and deployed web application.

---

### 16.6 Supported Resource Types

SPIFFS can store a wide variety of static resources.

Supported resource types include:

- HTML documents
- CSS stylesheets
- JavaScript files
- PNG images
- JPG images
- SVG graphics
- Icons
- Fonts
- Audio files
- JSON files
- Text files
- Additional static resources

These resources are delivered directly by the embedded HTTP server.

---

### 16.7 File Access Workflow

Whenever a browser requests a resource, the firmware follows a structured processing sequence.

```text
Browser Request
        │
        ▼
Embedded HTTP Server
        │
        ▼
Locate Requested File
        │
        ▼
SPIFFS File Access
        │
        ▼
Read Flash Storage
        │
        ▼
Generate HTTP Response
        │
        ▼
Return Resource
```

This workflow allows static content to be served directly from flash memory with minimal runtime overhead.

---

### 16.8 Embedded Web Server Integration

The embedded HTTP server relies on SPIFFS as its primary storage backend.

The integration provides:

- Static file delivery
- Resource loading
- Page rendering
- Asset management
- Browser compatibility
- Runtime file access
- Media delivery
- Efficient flash utilization

Every static browser resource is retrieved through the filesystem before being transmitted to the client.

---

### 16.9 Firmware Integration

The SPIFFS subsystem communicates with multiple firmware modules.

```text
                  SPIFFS File System
                          │
        ┌─────────────────┼─────────────────┐
        ▼                 ▼                 ▼
 Embedded HTTP      Configuration      Runtime
     Server            Manager        Controller
        │                 │                 │
        ▼                 ▼                 ▼
 Browser UI         EEPROM Manager     OLED Display
```

This architecture allows static resources and runtime services to operate together while remaining logically independent.

---

### 16.10 Resource Customization

The browser interface is fully customizable because all static resources reside within the SPIFFS filesystem.

Developers may replace or modify:

- HTML pages
- CSS stylesheets
- JavaScript applications
- Logos
- Images
- Icons
- Fonts
- Audio files
- Animation assets
- Additional static resources

After uploading an updated SPIFFS image, the firmware automatically serves the new resources without requiring modifications to the firmware executable.

---

### 16.11 Filesystem Management

The firmware performs several management operations during normal execution.

These include:

- Filesystem mounting
- File existence verification
- Resource loading
- Read operations
- Runtime access
- Error handling
- Storage validation
- Filesystem status monitoring

These operations ensure reliable access to stored resources throughout device operation.

---

### 16.12 Design Characteristics

The SPIFFS implementation has been designed with the following objectives:

- Efficient flash utilization
- Fast resource loading
- Reliable file access
- Modular resource management
- Independent web application storage
- Runtime compatibility
- Simplified customization
- Standalone embedded operation

These characteristics provide a reliable storage layer for the embedded web application while minimizing runtime overhead.

---

### 16.13 SPIFFS File System Summary

| Feature | Description |
|----------|-------------|
| Filesystem | SPI Flash File System (SPIFFS) |
| Storage Medium | ESP8266 Internal Flash |
| Purpose | Static Resource Storage |
| Resource Types | HTML, CSS, JavaScript, Images, Fonts, Audio, JSON |
| HTTP Server Integration | Yes |
| Browser Resource Delivery | Supported |
| Runtime File Access | Supported |
| Independent Customization | Fully Supported |
| Firmware Integration | Modular |
| Platform | ESP8266 |
| Persistent Storage | Yes |
| Standalone Operation | Fully Supported |





## EEPROM Configuration

### 17.1 Overview

The EEPROM Configuration subsystem provides persistent storage for firmware settings and operational parameters within the G-Shark platform. It enables the firmware to preserve user-defined configuration values across power cycles, system resets, and firmware restarts without requiring external storage devices.

The subsystem utilizes the EEPROM emulation layer provided by the ESP8266, storing configuration data inside the device's internal flash memory. During system initialization, stored values are validated and loaded into runtime memory, allowing the firmware to restore its previous operating state automatically.

The EEPROM subsystem operates transparently in the background and is tightly integrated with the Configuration Manager, OLED interface, embedded web interface, command-line interface, and runtime controller.

---

### 17.2 EEPROM Architecture

```text
               Firmware Runtime
                      │
                      ▼
           Configuration Manager
                      │
      ┌───────────────┼───────────────┐
      ▼               ▼               ▼
 OLED Interface   Web Interface      CLI
      │               │               │
      └───────────────┼───────────────┘
                      ▼
             EEPROM Manager
                      │
                      ▼
        ESP8266 EEPROM Emulation
                      │
                      ▼
            Internal Flash Storage
```

The EEPROM Manager serves as the interface between runtime configuration and persistent storage.

---

### 17.3 Primary Responsibilities

The EEPROM Configuration subsystem performs several essential functions throughout firmware operation.

Primary responsibilities include:

- Initializing EEPROM storage
- Reading stored configuration
- Writing updated settings
- Validating stored data
- Restoring configuration during startup
- Synchronizing runtime parameters
- Managing persistent storage
- Handling configuration updates
- Preserving system preferences
- Supporting firmware modules

---

### 17.4 Initialization Process

During firmware startup, the EEPROM subsystem performs a structured initialization sequence.

```text
Firmware Startup
        │
        ▼
Initialize EEPROM
        │
        ▼
Read Stored Data
        │
        ▼
Validate Configuration
        │
        ▼
Load Runtime Settings
        │
        ▼
Synchronize Modules
        │
        ▼
Configuration Ready
```

If stored configuration is unavailable or invalid, the firmware automatically loads default values before continuing initialization.

---

### 17.5 Stored Configuration

The EEPROM subsystem maintains persistent configuration values required by various firmware modules.

Typical stored information may include:

- Device settings
- Display preferences
- Wireless configuration
- Access Point settings
- User preferences
- Runtime options
- System parameters
- Feature states
- Startup behavior
- Interface preferences

The exact configuration layout depends on the firmware version and enabled features.

---

### 17.6 Read Operations

Whenever the firmware requires persistent information, the EEPROM Manager retrieves the corresponding values from flash memory.

Read operations include:

- Startup configuration loading
- Runtime parameter retrieval
- Preference restoration
- Configuration synchronization
- Module initialization
- System validation

Retrieved values are copied into runtime memory where they are used by the firmware during execution.

---

### 17.7 Write Operations

Configuration changes initiated by the user or firmware are committed to EEPROM through controlled write operations.

Typical write operations include:

- Saving configuration
- Updating preferences
- Modifying runtime settings
- Persisting feature states
- Updating wireless parameters
- Recording interface settings

Write operations occur only when necessary in order to minimize flash wear and improve long-term reliability.

---

### 17.8 Configuration Validation

Before stored values are applied to the firmware, the EEPROM subsystem performs validation to ensure data integrity.

Validation includes:

- Structure verification
- Version compatibility
- Value range checking
- Default value recovery
- Runtime consistency checks

If invalid data is detected, the firmware restores default configuration values and continues normal operation.

---

### 17.9 Runtime Synchronization

The EEPROM subsystem continuously exchanges information with the Configuration Manager.

```text
            Configuration Manager
                     │
                     ▼
              EEPROM Manager
                     │
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 OLED Display    Web Interface      CLI
                     │
                     ▼
            Runtime Controller
```

This synchronization ensures that user interfaces always display the current configuration state.

---

### 17.10 Firmware Integration

The EEPROM Configuration subsystem integrates with numerous firmware components.

Integrated modules include:

- Configuration Manager
- OLED User Interface
- Embedded Web Interface
- Access Point Manager
- Wireless Scanning Engine
- Station Manager
- Runtime Controller
- Command-Line Interface
- SPIFFS Manager

Each subsystem retrieves persistent configuration through the centralized EEPROM Manager.

---

### 17.11 Configuration Workflow

Configuration updates follow a structured processing sequence.

```text
User Changes Setting
         │
         ▼
Configuration Manager
         │
         ▼
Validate Parameter
         │
         ▼
Update Runtime Value
         │
         ▼
Write EEPROM
         │
         ▼
Synchronize Modules
         │
         ▼
Configuration Saved
```

This workflow ensures that runtime and persistent configuration remain synchronized.

---

### 17.12 Error Handling

The EEPROM subsystem incorporates mechanisms to maintain reliable configuration storage.

Supported error handling includes:

- Initialization failure detection
- Invalid configuration recovery
- Default value restoration
- Read verification
- Write verification
- Runtime synchronization
- Storage integrity monitoring

These mechanisms improve overall firmware stability and reduce the likelihood of configuration corruption.

---

### 17.13 Design Characteristics

The EEPROM Configuration subsystem has been designed according to several architectural principles.

These include:

- Persistent configuration storage
- Automatic startup restoration
- Centralized configuration management
- Runtime synchronization
- Efficient flash utilization
- Reliable data validation
- Modular implementation
- Seamless firmware integration

These characteristics provide reliable long-term configuration management while minimizing resource consumption.

---

### 17.14 EEPROM Configuration Summary

| Feature | Description |
|----------|-------------|
| Storage Type | EEPROM Emulation |
| Storage Medium | ESP8266 Internal Flash |
| Purpose | Persistent Configuration Storage |
| Startup Restoration | Automatic |
| Runtime Synchronization | Supported |
| Configuration Validation | Automatic |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| CLI Integration | Yes |
| Configuration Manager Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |




## 18. Command-Line Interface

### 18.1 Overview

The Command-Line Interface (CLI) provides a text-based management interface for interacting directly with the G-Shark firmware. It enables users to execute firmware commands, inspect runtime information, modify configuration parameters, control system modules, and retrieve diagnostic information through a serial communication channel.

The CLI operates as an independent subsystem within the firmware architecture while remaining synchronized with the Runtime Controller, Configuration Manager, OLED User Interface, Embedded Web Interface, and other firmware modules. It serves as an alternative management interface that complements both the graphical OLED interface and the browser-based web application.

Designed with a modular command-processing architecture, the CLI separates command parsing, execution, validation, and response generation into dedicated components, allowing new commands and functionality to be integrated without affecting unrelated firmware modules.

---

### 18.2 CLI Architecture

```text
               Serial Terminal
                      │
                      ▼
            UART Communication
                      │
                      ▼
          Command-Line Interface
                      │
      ┌───────────────┼────────────────┐
      ▼               ▼                ▼
 Command Parser   Command Handler   Response Engine
      │               │                │
      └───────────────┼────────────────┘
                      ▼
             Runtime Controller
                      │
     ┌────────────────┼────────────────┐
     ▼                ▼                ▼
 Configuration   Wireless Modules   System Services
```

The CLI receives user commands through the serial interface, processes them, and forwards execution requests to the appropriate firmware subsystem.

---

### 18.3 Primary Responsibilities

The Command-Line Interface is responsible for:

- Processing user commands
- Parsing command arguments
- Executing firmware functions
- Displaying runtime information
- Managing configuration
- Monitoring system status
- Reporting diagnostics
- Controlling firmware modules
- Returning execution results
- Synchronizing runtime information

---

### 18.4 Command Processing Workflow

Each command follows a structured execution sequence.

```text
User Command
      │
      ▼
UART Reception
      │
      ▼
Command Parser
      │
      ▼
Validate Syntax
      │
      ▼
Execute Command
      │
      ▼
Generate Response
      │
      ▼
Display Result
```

This workflow provides consistent command execution and standardized response handling.

---

### 18.5 Command Parser

The Command Parser is responsible for interpreting user input before execution.

Its responsibilities include:

- Reading input
- Tokenizing commands
- Parsing arguments
- Syntax validation
- Parameter extraction
- Error detection
- Command identification

Only validated commands are forwarded to the execution engine.

---

### 18.6 Command Execution

After successful parsing, commands are dispatched to the appropriate firmware subsystem.

Supported execution categories include:

- Runtime information
- Configuration management
- Wireless subsystem control
- Filesystem operations
- Diagnostic commands
- System information
- Firmware utilities
- Module management

Each subsystem processes its assigned commands independently while remaining synchronized with the firmware runtime.

---

### 18.7 Runtime Monitoring

The CLI provides direct access to runtime information maintained by the firmware.

Available runtime information may include:

- System status
- Firmware version
- Runtime statistics
- Wireless information
- Access Point status
- Station information
- Configuration values
- Filesystem status
- Memory information
- Device diagnostics

Runtime information is retrieved directly from the corresponding firmware modules.

---

### 18.8 Configuration Management

The Command-Line Interface allows runtime configuration of firmware parameters.

Configuration operations include:

- Viewing configuration
- Updating parameters
- Saving settings
- Restoring defaults
- Applying runtime changes
- Synchronizing configuration

Updated settings are propagated to the Configuration Manager and stored persistently when required.

---

### 18.9 Firmware Integration

The CLI communicates with multiple firmware subsystems.

```text
          Command-Line Interface
                     │
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 Configuration   Runtime Controller  OLED UI
      │              │              │
      ▼              ▼              ▼
 EEPROM        Wireless Modules   Web Interface
```

This integration enables commands to access firmware functionality through a centralized interface.

---

### 18.10 UART Communication

The CLI communicates with external serial terminals using the ESP8266 UART interface.

The communication layer provides:

- Command reception
- Response transmission
- Runtime logging
- Diagnostic output
- Configuration interaction
- Firmware control

Serial communication enables firmware management without requiring the embedded web interface.

---

### 18.11 Error Handling

The CLI incorporates several mechanisms to improve reliability during command execution.

Supported error handling includes:

- Invalid command detection
- Syntax validation
- Parameter verification
- Execution failure reporting
- Runtime error messages
- Response formatting

These mechanisms provide consistent feedback during user interaction.

---

### 18.12 Runtime Synchronization

The CLI remains synchronized with the firmware runtime throughout device operation.

Runtime synchronization includes:

- Configuration updates
- System status
- Wireless information
- Filesystem state
- Module status
- Runtime statistics

Information displayed by the CLI reflects the current operational state of the firmware.

---

### 18.13 Design Characteristics

The Command-Line Interface has been designed according to several architectural principles.

These include:

- Modular implementation
- Event-driven processing
- Centralized command dispatch
- Runtime synchronization
- Efficient memory utilization
- Expandable command architecture
- Consistent response generation
- Seamless firmware integration

These principles simplify future expansion while maintaining reliable operation on the ESP8266 platform.

---

### 18.14 Command-Line Interface Summary

| Feature | Description |
|----------|-------------|
| Interface Type | Serial Command-Line Interface |
| Communication | UART |
| Command Parsing | Integrated |
| Runtime Monitoring | Supported |
| Configuration Management | Supported |
| Diagnostic Reporting | Supported |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| EEPROM Integration | Yes |
| Runtime Synchronization | Automatic |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |




## 19. Configuration System

### 19.1 Overview

The Configuration System serves as the centralized management layer responsible for maintaining, validating, synchronizing, and distributing firmware settings throughout the G-Shark platform. Rather than allowing individual modules to manage their own independent settings, the Configuration System provides a unified architecture that ensures consistent behavior across the entire firmware.

It acts as the primary interface between persistent storage, runtime memory, user interfaces, and firmware services. Configuration values are loaded during system initialization, maintained throughout runtime, and synchronized across all integrated interfaces, including the OLED User Interface, Embedded Web Interface, and Command-Line Interface.

The Configuration System has been designed with a modular architecture, allowing new configuration parameters and firmware modules to be integrated without modifying the existing configuration framework.

---

### 19.2 System Architecture

```text
                 User Interfaces
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 OLED Display   Web Interface      CLI
      │              │              │
      └──────────────┼──────────────┘
                     ▼
            Configuration System
                     │
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 Validation      Runtime Cache   EEPROM Manager
                     │
                     ▼
            Runtime Controller
                     │
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 Wireless      Display System   System Services
```

The Configuration System serves as the central authority for firmware settings, ensuring all subsystems operate using synchronized configuration data.

---

### 19.3 Primary Responsibilities

The Configuration System performs several core responsibilities during firmware operation.

Primary responsibilities include:

- Managing firmware configuration
- Loading startup settings
- Validating configuration values
- Synchronizing runtime parameters
- Distributing configuration updates
- Coordinating subsystem settings
- Managing default values
- Handling persistent storage requests
- Supporting user interfaces
- Maintaining configuration consistency

---

### 19.4 Configuration Lifecycle

Configuration values follow a structured lifecycle throughout firmware execution.

```text
Firmware Startup
        │
        ▼
Load Configuration
        │
        ▼
Validate Values
        │
        ▼
Initialize Runtime
        │
        ▼
Apply Configuration
        │
        ▼
Runtime Operation
        │
        ▼
Save Updates (If Required)
```

This lifecycle ensures that valid configuration values are available before dependent firmware modules begin execution.

---

### 19.5 Configuration Categories

The Configuration System organizes settings into multiple logical categories.

Typical configuration categories include:

- System settings
- Wireless configuration
- Access Point configuration
- Display preferences
- User interface settings
- Runtime parameters
- Device preferences
- Startup options
- Feature configuration
- Service parameters

This organization simplifies configuration management and future expansion.

---

### 19.6 Configuration Validation

Before configuration values are accepted by the firmware, the Configuration System performs validation to ensure consistency and reliability.

Validation operations include:

- Structure verification
- Data integrity checks
- Value range validation
- Default value assignment
- Compatibility verification
- Runtime consistency checks

Invalid configuration values are automatically replaced with safe defaults before being applied to the firmware.

---

### 19.7 Runtime Synchronization

The Configuration System continuously synchronizes configuration values across the firmware.

Synchronization includes:

- OLED interface
- Embedded Web Interface
- Command-Line Interface
- Wireless subsystems
- Runtime Controller
- EEPROM Manager
- Display Manager
- System services

This centralized synchronization ensures that every subsystem operates using the same configuration state.

---

### 19.8 Configuration Update Workflow

Configuration modifications follow a controlled processing sequence.

```text
Configuration Change
         │
         ▼
Validate Parameter
         │
         ▼
Update Runtime Value
         │
         ▼
Notify Dependent Modules
         │
         ▼
Store Configuration
         │
         ▼
Synchronization Complete
```

Only validated configuration values are propagated throughout the firmware.

---

### 19.9 Firmware Integration

The Configuration System communicates with nearly every major subsystem within the firmware.

```text
              Configuration System
                      │
    ┌─────────────────┼─────────────────┐
    ▼                 ▼                 ▼
 EEPROM         Runtime Controller   OLED UI
    │                 │                 │
    ▼                 ▼                 ▼
 Web Interface   Wireless Modules    CLI
```

This architecture enables centralized configuration management while reducing inter-module dependencies.

---

### 19.10 Persistent Storage Integration

Persistent configuration is maintained through the EEPROM subsystem.

The Configuration System is responsible for:

- Loading stored values
- Saving updated settings
- Restoring default configuration
- Verifying stored data
- Maintaining configuration consistency

Persistent storage allows configuration to remain available after resets and power cycles.

---

### 19.11 User Interface Integration

Multiple user interfaces interact with the Configuration System through a common runtime layer.

Supported interfaces include:

- OLED User Interface
- Embedded Web Interface
- Command-Line Interface

Regardless of the interface used to modify a setting, the Configuration System ensures that all interfaces immediately reflect the updated configuration.

---

### 19.12 Error Handling

The Configuration System incorporates mechanisms to maintain reliable operation during configuration processing.

Supported error handling includes:

- Invalid parameter detection
- Configuration recovery
- Default value restoration
- Data validation
- Runtime consistency monitoring
- Synchronization verification

These mechanisms improve firmware stability while reducing the risk of invalid operating states.

---

### 19.13 Design Characteristics

The Configuration System has been designed according to several architectural principles.

These include:

- Centralized configuration management
- Modular implementation
- Automatic runtime synchronization
- Persistent storage support
- Dynamic configuration updates
- Efficient memory utilization
- Reliable validation
- Seamless subsystem integration

These characteristics simplify firmware maintenance while supporting future feature expansion.

---

### 19.14 Configuration System Summary

| Feature | Description |
|----------|-------------|
| Purpose | Centralized Firmware Configuration Management |
| Configuration Storage | EEPROM |
| Runtime Synchronization | Automatic |
| Validation | Integrated |
| Default Configuration | Supported |
| Persistent Storage | Yes |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| CLI Integration | Yes |
| Runtime Controller Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |



## 20. Web API & Firmware Communication

### 20.1 Overview

The Web API & Firmware Communication subsystem provides the communication bridge between the browser-based Embedded Web Interface and the underlying firmware runtime. It enables the web application to retrieve runtime information, submit configuration changes, invoke firmware services, and synchronize interface data without requiring direct access to internal firmware modules.

The communication layer follows a request-response architecture where browser requests are processed by the embedded HTTP server, forwarded to the appropriate firmware handlers, and returned as structured responses. This separation allows the web application and firmware logic to evolve independently while maintaining a consistent communication interface.

Designed as a modular subsystem, the Web API centralizes all browser-to-firmware interactions, simplifying maintenance and supporting future expansion.

---

### 20.2 Communication Architecture

```text
               Web Browser
                    │
                    ▼
        Embedded Web Interface
                    │
                    ▼
            HTTP Request Layer
                    │
                    ▼
           Embedded HTTP Server
                    │
                    ▼
             Web API Dispatcher
                    │
     ┌──────────────┼──────────────┐
     ▼              ▼              ▼
 Configuration   Runtime Data   System Services
     │              │              │
     └──────────────┼──────────────┘
                    ▼
           Firmware Response Engine
                    │
                    ▼
             HTTP Response
                    │
                    ▼
               Web Browser
```

The communication layer isolates browser interactions from internal firmware implementation details.

---

### 20.3 Primary Responsibilities

The Web API subsystem performs several core responsibilities.

Primary responsibilities include:

- Processing browser requests
- Routing API calls
- Retrieving runtime information
- Applying configuration updates
- Synchronizing interface data
- Returning structured responses
- Managing request validation
- Coordinating subsystem communication
- Reporting execution status
- Supporting browser interaction

---

### 20.4 Communication Model

The communication framework follows a structured request-response model.

```text
Browser Action
       │
       ▼
HTTP Request
       │
       ▼
API Dispatcher
       │
       ▼
Firmware Service
       │
       ▼
Generate Response
       │
       ▼
HTTP Response
       │
       ▼
Browser Update
```

Each request is processed independently while maintaining synchronization with the firmware runtime.

---

### 20.5 Request Processing

Incoming browser requests pass through multiple processing stages before reaching the firmware.

Processing stages include:

- Request reception
- Resource identification
- API routing
- Parameter validation
- Service execution
- Response generation
- Browser delivery

This layered approach provides clear separation between communication logic and firmware functionality.

---

### 20.6 Runtime Data Exchange

The Web API enables the browser interface to retrieve current firmware information.

Typical runtime information includes:

- System status
- Firmware information
- Runtime statistics
- Wireless information
- Access Point status
- Connected station information
- Configuration values
- Device information
- Filesystem status
- System diagnostics

All runtime information is retrieved directly from the active firmware state.

---

### 20.7 Configuration Communication

Configuration updates initiated from the browser are processed through the Web API before being applied to the firmware.

Configuration workflow includes:

- Receiving configuration requests
- Validating parameters
- Updating runtime configuration
- Synchronizing affected modules
- Persisting settings when required
- Returning execution status

This centralized workflow ensures configuration consistency across all firmware interfaces.

---

### 20.8 Firmware Integration

The Web API communicates with multiple firmware subsystems.

```text
               Web API Dispatcher
                       │
      ┌────────────────┼────────────────┐
      ▼                ▼                ▼
 Configuration    Runtime Controller   System Services
      │                │                │
      ▼                ▼                ▼
 EEPROM         Wireless Modules      SPIFFS
                       │
                       ▼
                  OLED Interface
```

Each subsystem exposes runtime services through the centralized API dispatcher.

---

### 20.9 Interface Synchronization

The communication subsystem maintains synchronization between browser data and firmware state.

Synchronization includes:

- Configuration changes
- Runtime statistics
- Device status
- Module state
- System information
- Interface updates

This synchronization ensures that information presented by the browser accurately reflects the current firmware operation.

---

### 20.10 Response Generation

After a firmware service completes execution, the communication layer generates a structured response for the browser.

Response processing includes:

- Result formatting
- Status generation
- Data serialization
- Error reporting
- Browser transmission

Consistent response formatting simplifies browser-side processing and improves interface reliability.

---

### 20.11 Error Handling

The communication subsystem incorporates several mechanisms to ensure reliable interaction between the browser and firmware.

Supported error handling includes:

- Invalid request detection
- Parameter validation
- Unsupported operation handling
- Execution failure reporting
- Response generation
- Communication recovery

These mechanisms improve robustness while providing meaningful feedback to the browser interface.

---

### 20.12 Modular API Design

The Web API has been designed as an expandable communication layer.

Its modular architecture supports:

- Independent service handlers
- Centralized request routing
- Simplified maintenance
- Future endpoint expansion
- Consistent response handling
- Reduced subsystem coupling

This design allows additional firmware functionality to be exposed without modifying the overall communication framework.

---

### 20.13 Design Characteristics

The Web API & Firmware Communication subsystem has been designed according to several architectural principles.

These include:

- Modular implementation
- Request-response architecture
- Centralized API routing
- Runtime synchronization
- Efficient communication
- Consistent response generation
- Independent service handlers
- Seamless firmware integration

These characteristics provide a scalable and maintainable communication layer between the browser interface and the firmware runtime.

---

### 20.14 Web API & Firmware Communication Summary

| Feature | Description |
|----------|-------------|
| Purpose | Browser-to-Firmware Communication |
| Communication Model | Request–Response |
| Transport | Embedded HTTP Server |
| Runtime Data Access | Supported |
| Configuration Updates | Supported |
| Response Generation | Structured |
| Runtime Synchronization | Automatic |
| Embedded Web Integration | Yes |
| Configuration System Integration | Yes |
| Runtime Controller Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |


## 21. Display Rendering Engine

### 21.1 Overview

The Display Rendering Engine is the graphics subsystem responsible for generating and updating all visual output presented on the OLED display. It transforms runtime information maintained by the firmware into organized graphical elements that provide real-time feedback regarding system status, navigation, configuration, and operational activity.

Rather than allowing individual firmware modules to draw directly to the display hardware, the Display Rendering Engine acts as a centralized rendering layer. This architecture separates graphical presentation from business logic, resulting in consistent screen layouts, simplified maintenance, and improved rendering efficiency.

The rendering engine operates continuously throughout firmware execution and remains synchronized with the Runtime Controller, OLED User Interface, Configuration System, Wireless Scanning Engine, Access Point Manager, Station Manager, and other integrated subsystems.

---

### 21.2 Rendering Architecture

```text
              Firmware Runtime
                     │
     ┌───────────────┼────────────────┐
     ▼               ▼                ▼
 Wireless Data   Configuration   System Status
     │               │                │
     └───────────────┼────────────────┘
                     ▼
         Display Rendering Engine
                     │
     ┌───────────────┼────────────────┐
     ▼               ▼                ▼
 Layout Manager  Graphics Engine  Text Renderer
                     │
                     ▼
              OLED Display Driver
                     │
                     ▼
               OLED Hardware
```

The rendering engine converts runtime information into graphical output before transmitting it to the OLED display.

---

### 21.3 Primary Responsibilities

The Display Rendering Engine performs several core responsibilities.

Primary responsibilities include:

- Rendering user interface screens
- Drawing graphical elements
- Updating runtime information
- Managing screen layouts
- Rendering text
- Displaying icons
- Processing screen transitions
- Refreshing display content
- Coordinating visual updates
- Optimizing rendering performance

---

### 21.4 Rendering Pipeline

Each screen update follows a structured rendering sequence.

```text
Runtime Event
      │
      ▼
Retrieve Display Data
      │
      ▼
Generate Layout
      │
      ▼
Render Graphics
      │
      ▼
Compose Display Buffer
      │
      ▼
Transmit to OLED
      │
      ▼
Screen Updated
```

This pipeline ensures that display updates remain organized and synchronized with the firmware runtime.

---

### 21.5 Layout Management

The Layout Manager determines the placement of visual elements before rendering begins.

Layout responsibilities include:

- Screen composition
- Text positioning
- Icon placement
- Menu organization
- Status indicator alignment
- Navigation layout
- Information grouping
- Screen consistency

A centralized layout system ensures a uniform appearance throughout the firmware.

---

### 21.6 Graphics Rendering

The graphics subsystem is responsible for drawing visual elements displayed on the OLED.

Supported graphical elements include:

- Text
- Icons
- Selection indicators
- Status symbols
- Progress indicators
- Borders
- Menus
- Notifications
- Information panels
- System messages

Rendering operations are optimized for the limited resolution of the OLED display.

---

### 21.7 Display Buffer Management

Before updating the OLED hardware, graphical elements are composed within an internal display buffer.

Buffer management includes:

- Buffer initialization
- Screen composition
- Graphics drawing
- Text rendering
- Refresh preparation
- Buffer transmission

Using an intermediate buffer reduces visible flickering and improves rendering consistency.

---

### 21.8 Runtime Synchronization

The rendering engine continuously retrieves information from active firmware modules.

Runtime information includes:

- Menu state
- System status
- Configuration values
- Wireless information
- Runtime notifications
- Device activity
- Navigation state
- Interface status

Only the current runtime state is rendered, ensuring that displayed information remains accurate.

---

### 21.9 Firmware Integration

The Display Rendering Engine communicates with multiple firmware components.

```text
           Display Rendering Engine
                     │
     ┌───────────────┼────────────────┐
     ▼               ▼                ▼
 OLED Interface  Runtime Controller  Configuration
     │               │                │
     ▼               ▼                ▼
 Wireless Data  System Services   Display Driver
```

This centralized integration allows display updates to remain synchronized with the firmware while minimizing dependencies between modules.

---

### 21.10 Refresh Management

The rendering engine controls how and when the OLED display is updated.

Refresh management includes:

- Screen refresh scheduling
- Runtime updates
- Menu changes
- Notification display
- Information refresh
- Status updates

Controlled refresh scheduling minimizes unnecessary display operations while maintaining responsive user interaction.

---

### 21.11 Rendering Optimization

The Display Rendering Engine incorporates several techniques to improve performance on the ESP8266 platform.

Optimization strategies include:

- Efficient buffer usage
- Incremental screen updates
- Lightweight graphics rendering
- Reduced redraw operations
- Optimized text rendering
- Minimal memory allocation

These optimizations reduce processor utilization while maintaining smooth display performance.

---

### 21.12 Error Handling

The rendering subsystem includes mechanisms to maintain reliable display operation.

Supported handling includes:

- Display initialization verification
- Buffer validation
- Rendering recovery
- Refresh synchronization
- Runtime consistency checks
- Driver communication monitoring

These mechanisms improve reliability during continuous firmware execution.

---

### 21.13 Design Characteristics

The Display Rendering Engine has been designed according to several architectural principles.

These include:

- Centralized rendering architecture
- Modular implementation
- Efficient buffer management
- Runtime synchronization
- Consistent layout generation
- Optimized graphics rendering
- Independent display abstraction
- Seamless firmware integration

These characteristics provide a reliable graphical subsystem while minimizing processing overhead.

---

### 21.14 Display Rendering Engine Summary

| Feature | Description |
|----------|-------------|
| Purpose | OLED Graphics Rendering |
| Rendering Model | Buffered Rendering |
| Graphics Support | Text, Icons, Menus, Status Indicators |
| Layout Management | Centralized |
| Runtime Synchronization | Automatic |
| Refresh Scheduling | Integrated |
| OLED Driver Integration | Yes |
| Configuration System Integration | Yes |
| Runtime Controller Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |


## 22. Power Management

### 22.1 Overview

The Power Management subsystem is responsible for controlling the initialization, distribution, monitoring, and utilization of electrical resources throughout the G-Shark firmware. Although the ESP8266 platform is powered from an external supply, efficient power management remains essential for maintaining system stability, reliable wireless operation, and consistent OLED performance.

Rather than actively regulating voltage, the firmware coordinates hardware initialization, subsystem activation, display updates, wireless operations, and peripheral usage to optimize overall power consumption and reduce unnecessary processor activity.

The Power Management subsystem operates continuously during firmware execution and remains integrated with the Runtime Controller, Wireless Manager, Display Rendering Engine, Configuration System, and system scheduler.

---

### 22.2 Power Architecture

```text
              External Power Supply
                       │
                       ▼
                Voltage Regulation
                       │
                       ▼
                 ESP8266 Controller
                       │
      ┌────────────────┼─────────────────┐
      ▼                ▼                 ▼
 OLED Display   Wireless Hardware   Flash Memory
      │                │                 │
      └────────────────┼─────────────────┘
                       ▼
              Power Management
                       │
                       ▼
              Runtime Controller
```

The firmware coordinates subsystem activity to maintain efficient and stable operation across all hardware components.

---

### 22.3 Primary Responsibilities

The Power Management subsystem performs several important responsibilities.

Primary responsibilities include:

- Managing subsystem initialization
- Coordinating hardware startup
- Optimizing processor utilization
- Managing peripheral activity
- Controlling display updates
- Coordinating wireless operations
- Reducing unnecessary processing
- Supporting runtime scheduling
- Maintaining operational stability
- Improving overall power efficiency

---

### 22.4 Startup Power Sequence

During system startup, hardware components are initialized in a controlled order.

```text
Power Applied
      │
      ▼
ESP8266 Bootloader
      │
      ▼
Firmware Initialization
      │
      ▼
Initialize Flash Storage
      │
      ▼
Initialize EEPROM
      │
      ▼
Initialize OLED
      │
      ▼
Initialize Wireless Modules
      │
      ▼
System Ready
```

This sequence ensures that dependent components are initialized only after the required system resources become available.

---

### 22.5 Runtime Resource Management

During normal operation, the Power Management subsystem coordinates resource usage across the firmware.

Managed resources include:

- Processor activity
- OLED updates
- Wireless operations
- Flash access
- EEPROM access
- Runtime scheduling
- Peripheral communication
- Background services

Efficient coordination minimizes unnecessary hardware activity while maintaining responsive system behavior.

---

### 22.6 Display Power Optimization

The OLED display is one of the continuously active peripherals within the firmware.

Power optimization strategies include:

- Controlled refresh scheduling
- Efficient rendering
- Reduced unnecessary redraws
- Event-driven display updates
- Optimized graphics rendering
- Runtime synchronization

These techniques reduce processor workload while maintaining a responsive user interface.

---

### 22.7 Wireless Resource Coordination

Wireless communication represents one of the most resource-intensive functions of the ESP8266.

The Power Management subsystem coordinates:

- Wireless initialization
- Channel operations
- Network scanning
- Access Point operation
- Runtime scheduling
- Background wireless tasks

Scheduling these activities efficiently improves overall firmware responsiveness while avoiding unnecessary processor utilization.

---

### 22.8 Runtime Scheduling

Subsystem execution is coordinated by the Runtime Controller.

```text
          Runtime Controller
                  │
     ┌────────────┼─────────────┐
     ▼            ▼             ▼
 Display      Wireless      System Tasks
     │            │             │
     └────────────┼─────────────┘
                  ▼
         Power Management
```

Task scheduling distributes processor time efficiently among active firmware modules.

---

### 22.9 Firmware Integration

The Power Management subsystem communicates with numerous firmware components.

Integrated modules include:

- Runtime Controller
- Display Rendering Engine
- OLED User Interface
- Wireless Scanning Engine
- Access Point Manager
- Station Manager
- Configuration System
- Embedded Web Interface
- SPIFFS Manager
- EEPROM Manager

Centralized coordination ensures stable operation across all integrated services.

---

### 22.10 Operational Stability

The Power Management subsystem contributes to overall firmware stability by coordinating subsystem activity.

Stability functions include:

- Controlled startup
- Ordered initialization
- Runtime scheduling
- Peripheral coordination
- Resource balancing
- Continuous subsystem synchronization

These mechanisms reduce resource contention and improve long-term reliability.

---

### 22.11 Performance Optimization

The firmware incorporates several techniques to improve efficiency during extended operation.

Optimization strategies include:

- Efficient task scheduling
- Event-driven processing
- Optimized display refresh
- Reduced redundant processing
- Controlled peripheral access
- Efficient memory utilization

These optimizations improve responsiveness while reducing unnecessary processor workload.

---

### 22.12 Error Handling

The Power Management subsystem includes mechanisms to support reliable operation.

Supported handling includes:

- Startup verification
- Initialization monitoring
- Hardware readiness validation
- Runtime consistency checks
- Peripheral synchronization
- Recovery during subsystem initialization

These mechanisms improve overall firmware robustness during startup and runtime.

---

### 22.13 Design Characteristics

The Power Management subsystem has been designed according to several architectural principles.

These include:

- Centralized resource coordination
- Controlled subsystem initialization
- Efficient runtime scheduling
- Event-driven operation
- Modular implementation
- Reduced processor overhead
- Reliable hardware coordination
- Seamless firmware integration

These characteristics contribute to stable and efficient firmware execution on the ESP8266 platform.

---

### 22.14 Power Management Summary

| Feature | Description |
|----------|-------------|
| Purpose | Runtime Resource & Power Coordination |
| Startup Management | Controlled Initialization |
| Display Optimization | Supported |
| Wireless Coordination | Integrated |
| Runtime Scheduling | Managed |
| Resource Balancing | Automatic |
| Performance Optimization | Supported |
| Runtime Controller Integration | Yes |
| OLED Integration | Yes |
| Configuration System Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |


## 23. System Configuration Options

### 23.1 Overview

The System Configuration Options subsystem defines the collection of configurable parameters that control the behavior of the G-Shark firmware during startup and runtime. These options provide flexibility by allowing firmware behavior to be customized without modifying the firmware source code.

Configuration parameters are centrally managed by the Configuration System and stored persistently through the EEPROM subsystem. During system initialization, stored values are loaded into runtime memory and distributed to the corresponding firmware modules. Any changes made through supported user interfaces are validated, synchronized, and applied consistently across the entire system.

The System Configuration Options subsystem provides a unified configuration model for all integrated firmware components, ensuring reliable and predictable operation.

---

### 23.2 Configuration Architecture

```text
              User Interfaces
     ┌────────────┼────────────┐
     ▼            ▼            ▼
 OLED Display  Web Interface   CLI
     │            │            │
     └────────────┼────────────┘
                  ▼
      Configuration System
                  │
        Configuration Manager
                  │
     ┌────────────┼─────────────┐
     ▼            ▼             ▼
 EEPROM      Runtime Memory   Validation
                  │
                  ▼
         Firmware Subsystems
```

Configuration values are managed centrally before being distributed to the firmware runtime.

---

### 23.3 Primary Responsibilities

The System Configuration Options subsystem is responsible for:

- Managing configurable parameters
- Validating configuration values
- Loading startup settings
- Synchronizing runtime configuration
- Maintaining persistent settings
- Applying configuration updates
- Supporting user interfaces
- Coordinating subsystem configuration
- Restoring default values
- Maintaining configuration consistency

---

### 23.4 Configuration Categories

Configuration parameters are organized into logical categories to simplify management and maintenance.

Typical configuration categories include:

- System settings
- Device preferences
- Wireless configuration
- Access Point configuration
- Display settings
- User interface preferences
- Runtime behavior
- Startup options
- Filesystem preferences
- Service configuration

This organization improves readability while allowing future expansion of firmware capabilities.

---

### 23.5 System Settings

General system settings define the overall behavior of the firmware.

Typical parameters include:

- Device name
- Firmware information
- Startup behavior
- Runtime preferences
- Interface defaults
- Operating parameters
- System limits
- Service enablement

These settings affect multiple firmware modules simultaneously.

---

### 23.6 Wireless Configuration

Wireless-related configuration parameters determine how the firmware interacts with the onboard Wi-Fi hardware.

Typical configuration includes:

- Wireless operating mode
- Channel selection
- Access Point settings
- Network parameters
- Runtime wireless preferences
- Communication options
- Radio behavior
- Service configuration

These parameters are distributed to the wireless management subsystem during initialization.

---

### 23.7 Display Configuration

Display configuration controls the behavior of the OLED interface.

Supported display parameters may include:

- Display orientation
- Brightness preferences
- Screen timeout
- Refresh behavior
- Interface layout
- Navigation preferences
- Visual indicators
- Status display options

Display settings are synchronized automatically with the Display Rendering Engine.

---

### 23.8 Runtime Configuration Workflow

Configuration changes follow a controlled processing sequence.

```text
User Updates Setting
         │
         ▼
Validate Parameter
         │
         ▼
Update Runtime Value
         │
         ▼
Notify Dependent Modules
         │
         ▼
Store Configuration
         │
         ▼
Synchronization Complete
```

Only validated configuration values are applied throughout the firmware.

---

### 23.9 Configuration Persistence

Persistent storage is handled through the EEPROM subsystem.

Configuration persistence includes:

- Startup restoration
- Runtime saving
- Default configuration recovery
- Parameter synchronization
- Configuration verification
- Storage integrity checking

This ensures that configuration values remain available across resets and power cycles.

---

### 23.10 User Interface Integration

System configuration can be accessed through multiple firmware interfaces.

Supported interfaces include:

- OLED User Interface
- Embedded Web Interface
- Command-Line Interface

Regardless of the interface used, all configuration updates are processed through the centralized Configuration Manager.

---

### 23.11 Firmware Integration

The System Configuration Options subsystem communicates with nearly every major firmware component.

```text
          Configuration Manager
                    │
     ┌──────────────┼──────────────┐
     ▼              ▼              ▼
 EEPROM       Runtime Controller  OLED UI
     │              │              │
     ▼              ▼              ▼
 Wireless      Web Interface      CLI
```

Centralized integration eliminates duplicated configuration logic while maintaining consistency across the firmware.

---

### 23.12 Validation & Error Handling

Configuration values are validated before being accepted by the firmware.

Validation includes:

- Parameter verification
- Value range checking
- Configuration consistency
- Default value recovery
- Storage validation
- Runtime synchronization

These mechanisms prevent invalid configuration values from affecting firmware operation.

---

### 23.13 Design Characteristics

The System Configuration Options subsystem has been designed according to several architectural principles.

These include:

- Centralized configuration management
- Modular implementation
- Runtime synchronization
- Persistent storage support
- Reliable validation
- Expandable parameter architecture
- Independent user interfaces
- Seamless firmware integration

These characteristics simplify configuration management while supporting future firmware development.

---

### 23.14 System Configuration Options Summary

| Feature | Description |
|----------|-------------|
| Purpose | Centralized Firmware Configuration |
| Configuration Categories | System, Wireless, Display, Runtime |
| Persistent Storage | EEPROM |
| Validation | Integrated |
| Runtime Synchronization | Automatic |
| Default Configuration | Supported |
| OLED Integration | Yes |
| Embedded Web Integration | Yes |
| CLI Integration | Yes |
| Runtime Controller Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |



## 24. Compilation & Build Process

### 24.1 Overview

The Compilation & Build Process transforms the G-Shark firmware source code into an executable binary that can be deployed to the ESP8266 platform. This process combines multiple source files, libraries, configuration files, and embedded resources into a single firmware image while preparing the SPIFFS filesystem as a separate flash partition.

The build system compiles individual firmware modules independently before linking them into a unified executable. Static web resources are packaged separately into a SPIFFS image, allowing the browser interface to be updated independently of the firmware executable.

The compilation workflow has been designed to support modular development, efficient dependency management, and simplified firmware maintenance.

---

### 24.2 Build Architecture

```text
             Source Code
                  │
     ┌────────────┼────────────┐
     ▼            ▼            ▼
 .ino Files   C++ Modules   Libraries
     │            │            │
     └────────────┼────────────┘
                  ▼
              Compilation
                  │
                  ▼
              Object Files
                  │
                  ▼
              Linking Stage
                  │
                  ▼
         Firmware Executable
                  │
     ┌────────────┼────────────┐
     ▼                         ▼
Firmware Binary         SPIFFS Image
     │                         │
     └────────────┬────────────┘
                  ▼
          ESP8266 Flash Memory
```

The firmware executable and SPIFFS image are generated independently before deployment to the ESP8266.

---

### 24.3 Primary Responsibilities

The build system performs several important tasks.

Primary responsibilities include:

- Compiling firmware modules
- Resolving library dependencies
- Linking object files
- Generating executable firmware
- Creating SPIFFS filesystem images
- Validating build output
- Preparing deployment artifacts
- Managing build resources
- Supporting incremental development
- Producing flash-ready binaries

---

### 24.4 Build Workflow

The firmware follows a structured compilation sequence.

```text
Source Files
      │
      ▼
Preprocessing
      │
      ▼
Compilation
      │
      ▼
Object Generation
      │
      ▼
Linking
      │
      ▼
Firmware Binary
      │
      ▼
Ready for Flashing
```

Each stage prepares the firmware for the subsequent phase until a deployable binary is produced.

---

### 24.5 Source Compilation

The compiler processes each firmware module individually.

Compilation includes:

- Arduino sketch processing
- C++ source compilation
- Header inclusion
- Library integration
- Symbol generation
- Object file creation
- Dependency resolution

Independent module compilation simplifies maintenance while reducing unnecessary recompilation.

---

### 24.6 Library Integration

The firmware depends on several external libraries that are integrated during compilation.

Typical library categories include:

- ESP8266 platform libraries
- Wi-Fi libraries
- Display libraries
- Filesystem libraries
- EEPROM libraries
- Graphics libraries
- Communication libraries
- Utility libraries

The build system resolves all required dependencies before the linking stage.

---

### 24.7 Linking Process

After compilation, the linker combines all generated object files into a single firmware executable.

Linking responsibilities include:

- Symbol resolution
- Object merging
- Memory allocation
- Dependency integration
- Runtime initialization
- Executable generation

The resulting firmware image contains all executable code required for standalone operation.

---

### 24.8 SPIFFS Image Generation

Static browser resources are packaged independently of the firmware executable.

The SPIFFS build process includes:

- Collecting web resources
- Packaging HTML files
- Packaging CSS files
- Packaging JavaScript files
- Including images
- Including fonts
- Including audio resources
- Generating filesystem image

The generated SPIFFS image is flashed to the designated filesystem partition of the ESP8266.

---

### 24.9 Build Output

The compilation process produces multiple deployment artifacts.

Typical outputs include:

- Firmware binary
- SPIFFS filesystem image
- Build logs
- Object files
- Intermediate files
- Memory usage reports

These outputs support firmware deployment and development diagnostics.

---

### 24.10 Firmware Deployment

Following successful compilation, the generated artifacts are written to the ESP8266 flash memory.

```text
Firmware Binary
        │
        ▼
Flash Firmware
        │
        ▼
SPIFFS Image
        │
        ▼
Flash Filesystem
        │
        ▼
System Restart
        │
        ▼
Firmware Ready
```

The firmware executable and SPIFFS image operate together after deployment.

---

### 24.11 Build Validation

Before deployment, the build process performs validation of generated artifacts.

Validation includes:

- Successful compilation
- Dependency resolution
- Link verification
- Binary generation
- Filesystem generation
- Memory allocation verification
- Build completion confirmation

These validation steps ensure that the generated firmware is suitable for deployment.

---

### 24.12 Development Workflow

The modular build architecture supports efficient firmware development.

Development advantages include:

- Independent module compilation
- Simplified debugging
- Efficient incremental builds
- Modular source organization
- Easier maintenance
- Expandable architecture

This workflow enables future enhancements while minimizing development complexity.

---

### 24.13 Design Characteristics

The Compilation & Build Process has been designed according to several architectural principles.

These include:

- Modular compilation
- Independent source modules
- Automatic dependency resolution
- Efficient linking
- Separate filesystem generation
- Reliable build validation
- Expandable architecture
- Simplified deployment

These characteristics provide a scalable and maintainable firmware build environment.

---

### 24.14 Compilation & Build Process Summary

| Feature | Description |
|----------|-------------|
| Purpose | Firmware Compilation & Build Generation |
| Source Language | C++ / Arduino |
| Build Model | Modular Compilation |
| Dependency Resolution | Automatic |
| Firmware Output | Flashable Binary |
| Filesystem Output | SPIFFS Image |
| Library Integration | Supported |
| Build Validation | Integrated |
| ESP8266 Deployment | Supported |
| Firmware Architecture | Modular |
| Platform | ESP8266 |
| Standalone Operation | Fully Supported |



## 25. Installation & Flashing

### 25.1 Overview

The Installation & Flashing process deploys the G-Shark firmware and its accompanying SPIFFS filesystem image onto the ESP8266 platform. The firmware executable contains the embedded application logic, while the SPIFFS image stores the browser-based web interface and other static resources required during runtime.

Deployment consists of writing both images to their designated flash memory partitions. After flashing is complete and the device restarts, the firmware initializes all hardware peripherals, mounts the SPIFFS filesystem, restores stored configuration, and begins normal operation.

The installation workflow has been designed to provide a consistent deployment process while maintaining the modular separation between executable firmware and web resources.

---

### 25.2 Deployment Architecture

```text
Development Computer
        │
        ▼
Build Output
        │
 ┌──────┴─────────┐
 ▼                ▼
Firmware BIN   SPIFFS Image
 │                │
 └──────┬─────────┘
        ▼
USB Serial Interface
        │
        ▼
ESP8266 Flash Memory
        │
        ▼
Device Restart
        │
        ▼
Firmware Initialization
```

The firmware executable and SPIFFS image are programmed independently before the device enters normal operation.

---

### 25.3 Installation Requirements

Successful installation requires the following components.

Hardware requirements:

- ESP8266 development board
- USB connection
- Stable power supply
- Compatible development computer

Software requirements:

- Arduino IDE or compatible build environment
- ESP8266 board package
- Required firmware libraries
- SPIFFS upload support
- USB serial driver

These components provide the complete environment for firmware deployment.

---

### 25.4 Installation Workflow

The firmware installation follows a structured deployment sequence.

```text
Prepare Development Environment
            │
            ▼
Compile Firmware
            │
            ▼
Generate SPIFFS Image
            │
            ▼
Flash Firmware Binary
            │
            ▼
Flash SPIFFS Image
            │
            ▼
Restart Device
            │
            ▼
Verify Initialization
```

Each stage prepares the device for the subsequent deployment step.

---

### 25.5 Firmware Programming

The firmware executable is written to the application partition of the ESP8266 flash memory.

Programming responsibilities include:

- Uploading firmware binary
- Verifying flash operation
- Initializing application memory
- Preparing runtime execution
- Preserving filesystem partition

The firmware executable operates independently from the SPIFFS filesystem.

---

### 25.6 SPIFFS Deployment

Following firmware installation, the SPIFFS filesystem image is programmed into the dedicated filesystem partition.

The deployment includes:

- Filesystem image upload
- Resource installation
- Static asset deployment
- Browser interface installation
- Filesystem verification

After deployment, all browser resources become available through the embedded HTTP server.

---

### 25.7 First Boot Sequence

During the first startup after installation, the firmware performs a complete initialization process.

```text
Power Applied
      │
      ▼
Bootloader
      │
      ▼
Firmware Startup
      │
      ▼
Initialize Hardware
      │
      ▼
Mount SPIFFS
      │
      ▼
Load Configuration
      │
      ▼
Initialize Runtime
      │
      ▼
System Ready
```

This sequence prepares all firmware subsystems before entering normal runtime operation.

---

### 25.8 Installation Verification

After deployment, the firmware performs several initialization checks.

Verification includes:

- Firmware startup
- Flash memory access
- SPIFFS mounting
- EEPROM initialization
- OLED initialization
- Wireless subsystem startup
- Runtime controller initialization
- Embedded web server startup

Successful completion of these checks indicates that the installation process has completed correctly.

---

### 25.9 Firmware Updates

The modular architecture allows firmware components to be updated independently when appropriate.

Supported update operations include:

- Firmware executable replacement
- SPIFFS filesystem replacement
- Configuration preservation
- Resource updates
- Browser interface customization

This separation simplifies maintenance while reducing deployment complexity.

---

### 25.10 Recovery Considerations

If initialization does not complete successfully, the firmware incorporates mechanisms that support recovery during startup.

Recovery procedures include:

- Startup verification
- Configuration validation
- Filesystem initialization checks
- Hardware initialization monitoring
- Default configuration restoration
- Runtime consistency verification

These mechanisms improve reliability during installation and subsequent firmware updates.

---

### 25.11 Deployment Integration

The installation process prepares every major firmware subsystem for operation.

Integrated components include:

- Runtime Controller
- Configuration System
- EEPROM Manager
- SPIFFS File System
- Embedded Web Interface
- Captive Portal Framework
- OLED User Interface
- Wireless Scanning Engine
- Access Point Manager
- Display Rendering Engine

Each subsystem becomes operational after successful initialization.

---

### 25.12 Installation Characteristics

The installation process has been designed according to several architectural principles.

These include:

- Modular deployment
- Independent firmware and filesystem images
- Reliable initialization
- Automated subsystem startup
- Persistent configuration support
- Simplified firmware updates
- Expandable deployment architecture
- Consistent startup behavior

These characteristics simplify firmware deployment while supporting long-term maintenance.

---

### 25.13 Design Characteristics

The Installation & Flashing subsystem emphasizes:

- Reliable firmware deployment
- Independent filesystem installation
- Structured initialization
- Consistent runtime preparation
- Efficient update workflow
- Modular architecture
- Standalone operation
- Seamless firmware integration

These design principles provide a dependable installation process for the ESP8266 platform.

---

### 25.14 Installation & Flashing Summary

| Feature | Description |
|----------|-------------|
| Purpose | Firmware Deployment to ESP8266 |
| Firmware Image | Flashable Binary |
| Filesystem Image | SPIFFS |
| Deployment Method | USB Serial Programming |
| Firmware Installation | Supported |
| SPIFFS Installation | Supported |
| Startup Verification | Automatic |
| Configuration Restoration | Supported |
| Runtime Initialization | Automatic |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |



## 26. Firmware Customization

### 26.1 Overview

The G-Shark firmware has been designed with a modular architecture that allows developers to customize functionality, appearance, configuration, and system behavior without redesigning the entire firmware. Individual subsystems are logically separated, enabling independent modification while preserving compatibility with the remaining firmware components.

Customization may involve replacing browser resources, modifying user interface elements, adjusting runtime parameters, extending firmware modules, or integrating additional hardware support. The centralized Configuration System, SPIFFS File System, and Runtime Controller provide a common foundation that simplifies future development.

The customization architecture encourages maintainability by minimizing dependencies between modules and providing well-defined integration points throughout the firmware.

---

### 26.2 Customization Architecture

```text
             Firmware Source Code
                     │
      ┌──────────────┼──────────────┐
      ▼              ▼              ▼
 Configuration   UI Resources   Core Modules
      │              │              │
      ▼              ▼              ▼
 EEPROM         SPIFFS Files     C++ Source
      │              │              │
      └──────────────┼──────────────┘
                     ▼
            Firmware Customization
                     │
                     ▼
            Compiled Firmware Image
```

The modular architecture allows multiple firmware components to be customized independently before compilation and deployment.

---

### 26.3 Primary Responsibilities

The firmware architecture supports customization of:

- System configuration
- User interface
- Browser resources
- Display layouts
- Runtime behavior
- Wireless parameters
- Feature modules
- Startup behavior
- Static resources
- Hardware integration

Each customization area operates independently while remaining synchronized with the firmware runtime.

---

### 26.4 User Interface Customization

The firmware provides multiple interfaces that can be customized according to project requirements.

Customizable interfaces include:

- OLED menus
- Display layouts
- Navigation structure
- Icons
- Status screens
- Notification messages
- Browser interface
- Runtime information panels

These modifications can be performed without affecting unrelated firmware modules.

---

### 26.5 Embedded Web Interface Customization

The browser-based interface is fully customizable through the SPIFFS filesystem.

Developers may replace or modify:

- HTML documents
- CSS stylesheets
- JavaScript applications
- Images
- Logos
- Icons
- Fonts
- Audio resources
- Additional static assets

Because these resources are stored independently of the firmware executable, the web interface can be redesigned without modifying the underlying firmware logic.

---

### 26.6 Configuration Customization

Firmware behavior can be adjusted through configurable runtime parameters.

Supported configuration areas include:

- System preferences
- Wireless configuration
- Access Point settings
- Display preferences
- Startup behavior
- Runtime options
- User interface settings
- Service configuration

Configuration changes are managed by the Configuration System and stored persistently through the EEPROM subsystem.

---

### 26.7 Module Expansion

The modular architecture supports future expansion by allowing additional firmware components to be integrated.

Expandable areas include:

- Runtime services
- Display modules
- Configuration parameters
- Communication services
- User interface pages
- Browser functionality
- Diagnostic services
- System utilities

New modules communicate with the firmware through the Runtime Controller and Configuration System.

---

### 26.8 Resource Customization Workflow

Customization of browser resources follows a structured workflow.

```text
Modify Resource Files
         │
         ▼
Update SPIFFS Contents
         │
         ▼
Generate SPIFFS Image
         │
         ▼
Deploy Filesystem
         │
         ▼
Restart Firmware
         │
         ▼
Updated Web Interface
```

This workflow allows visual changes to be deployed independently of the firmware executable.

---

### 26.9 Firmware Source Customization

Developers may extend firmware functionality by modifying the source code.

Typical customization areas include:

- System modules
- Runtime controller
- Display rendering
- Configuration manager
- Communication handlers
- Hardware support
- User interface logic
- Utility functions

The modular source structure simplifies maintenance while reducing dependencies between components.

---

### 26.10 Hardware Adaptation

The firmware architecture supports adaptation to compatible hardware configurations.

Customizable hardware components include:

- OLED display
- Input buttons
- Flash storage
- GPIO assignments
- External peripherals
- Communication interfaces

Hardware-specific modifications remain isolated from higher-level firmware logic whenever possible.

---

### 26.11 Firmware Integration

The Firmware Customization subsystem interacts with multiple core components.

```text
            Firmware Customization
                     │
     ┌───────────────┼────────────────┐
     ▼               ▼                ▼
 Configuration   SPIFFS System   Runtime Controller
     │               │                │
     ▼               ▼                ▼
 EEPROM       Web Interface     Display Engine
```

This architecture enables customization while maintaining consistency across the firmware.

---

### 26.12 Customization Guidelines

To preserve firmware stability, customization follows several architectural guidelines.

Recommended practices include:

- Maintain modular structure
- Preserve subsystem interfaces
- Validate configuration values
- Keep runtime synchronization intact
- Isolate hardware-specific changes
- Update dependent resources consistently
- Verify build integrity before deployment

Following these principles simplifies future maintenance and feature expansion.

---

### 26.13 Design Characteristics

The Firmware Customization architecture has been designed according to several core principles.

These include:

- Modular implementation
- Independent subsystem customization
- Expandable architecture
- Centralized configuration management
- Resource separation
- Consistent runtime synchronization
- Simplified maintenance
- Seamless firmware integration

These characteristics enable long-term extensibility while maintaining firmware reliability.

---

### 26.14 Firmware Customization Summary

| Feature | Description |
|----------|-------------|
| Purpose | Modular Firmware Customization |
| UI Customization | Supported |
| Web Interface Customization | Fully Supported |
| SPIFFS Resource Replacement | Supported |
| Configuration Customization | Supported |
| Module Expansion | Supported |
| Hardware Adaptation | Supported |
| EEPROM Integration | Yes |
| Runtime Controller Integration | Yes |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |



## 27. Project Resources

### 27.1 Overview

The G-Shark firmware is composed of multiple software components, hardware resources, development tools, libraries, and supporting assets that collectively provide a complete embedded firmware platform for the ESP8266.

Project resources are organized into logical categories to simplify development, maintenance, customization, and future expansion. These resources include firmware source code, embedded libraries, hardware components, development environments, browser assets, documentation, and deployment artifacts.

The modular organization of these resources enables developers to understand the complete firmware ecosystem while maintaining a clear separation between software, hardware, and supporting infrastructure.

---

### 27.2 Resource Architecture

```text
                 G-Shark Project
                       │
     ┌─────────────────┼─────────────────┐
     ▼                 ▼                 ▼
 Software         Hardware         Documentation
     │                 │                 │
     ▼                 ▼                 ▼
 Libraries      ESP8266 Board      Technical Docs
     │                 │                 │
     ▼                 ▼                 ▼
 SPIFFS Files     OLED Display     Build Resources
```

Each resource category contributes to the complete firmware platform while remaining logically independent.

---

### 27.3 Firmware Resources

The software layer consists of modular firmware components.

Primary firmware resources include:

- Core firmware source code
- Runtime Controller
- Wireless Scanning Engine
- Access Point Manager
- Station Manager
- Display Rendering Engine
- Configuration System
- Embedded Web Interface
- Command-Line Interface
- Captive Portal Framework
- SPIFFS File System
- EEPROM Manager
- Utility modules

These modules collectively implement the firmware functionality.

---

### 27.4 Hardware Resources

The firmware is designed around the ESP8266 embedded platform.

Primary hardware resources include:

- ESP8266 microcontroller
- OLED display
- Push buttons
- Internal flash memory
- EEPROM emulation
- Wi-Fi radio
- USB serial interface
- GPIO peripherals
- Power regulation circuitry

These hardware components provide the foundation for firmware execution.

---

### 27.5 Software Libraries

The firmware utilizes several software libraries during compilation.

Typical library categories include:

- ESP8266 platform libraries
- Wi-Fi libraries
- OLED display libraries
- Graphics libraries
- SPIFFS libraries
- EEPROM libraries
- Communication libraries
- Arduino core libraries
- Utility libraries

Each library provides specialized functionality while remaining integrated into the firmware architecture.

---

### 27.6 Web Resources

The embedded browser interface relies on resources stored within the SPIFFS filesystem.

Stored resources include:

- HTML documents
- CSS stylesheets
- JavaScript files
- Images
- Logos
- Icons
- Fonts
- Audio resources
- SVG graphics
- Additional static assets

These resources collectively provide the browser-based management interface.

---

### 27.7 Development Resources

Development of the firmware utilizes several supporting tools.

Typical development resources include:

- Arduino IDE
- ESP8266 Board Package
- Serial Monitor
- SPIFFS upload tools
- USB serial drivers
- C++ compiler
- Build system
- Flash programming utilities

These tools provide the complete firmware development environment.

---

### 27.8 Documentation Resources

Project documentation accompanies the firmware throughout its lifecycle.

Documentation resources include:

- Firmware architecture
- Hardware architecture
- Module documentation
- Build documentation
- Installation documentation
- Configuration documentation
- API documentation
- System diagrams
- Project structure
- Technical reference material

Comprehensive documentation simplifies maintenance and future development.

---

### 27.9 Runtime Resources

During execution, the firmware maintains several runtime resources.

Runtime resources include:

- Runtime memory
- Configuration cache
- Display buffer
- Wireless information
- Filesystem resources
- Communication buffers
- System state information
- Runtime statistics

These resources support continuous firmware operation.

---

### 27.10 Build Resources

Compilation produces multiple deployment artifacts.

Generated resources include:

```text
Source Code
      │
      ▼
Compilation
      │
      ▼
Firmware Binary
      │
      ├─────────────► Flash Image
      │
      ▼
SPIFFS Image
      │
      ▼
Deployment Package
```

These artifacts are used during firmware deployment to the ESP8266 platform.

---

### 27.11 Resource Organization

The project follows a modular organization that separates resources according to their responsibilities.

```text
Project Resources
│
├── Firmware Source
├── Libraries
├── Hardware Support
├── SPIFFS Resources
├── Documentation
├── Build Output
├── Configuration
└── Deployment Files
```

This organization improves maintainability while supporting future expansion.

---

### 27.12 Resource Integration

Project resources interact through well-defined subsystem interfaces.

Integrated resource groups include:

- Firmware modules
- Hardware abstraction
- Configuration System
- Embedded Web Interface
- Display Rendering Engine
- Runtime Controller
- Build system
- Documentation

This integration enables efficient coordination across the entire firmware platform.

---

### 27.13 Design Characteristics

The Project Resources have been organized according to several architectural principles.

These include:

- Modular organization
- Independent resource groups
- Centralized configuration
- Expandable project structure
- Simplified maintenance
- Consistent documentation
- Efficient build workflow
- Seamless firmware integration

These principles provide a scalable foundation for continued firmware development.

---

### 27.14 Project Resources Summary

| Resource Category | Description |
|-------------------|-------------|
| Firmware Source | Core C++ / Arduino Modules |
| Hardware Resources | ESP8266 Platform Components |
| Software Libraries | Embedded Support Libraries |
| Web Resources | HTML, CSS, JavaScript, Images, Fonts |
| Runtime Resources | Memory, Buffers, System State |
| Configuration Resources | EEPROM & Runtime Configuration |
| Build Resources | Firmware Binary & SPIFFS Image |
| Documentation | Technical Reference & Architecture |
| Platform | ESP8266 |
| Project Structure | Modular |
| Firmware Architecture | Layered |
| Standalone Operation | Fully Supported |


## 28. Troubleshooting

### 28.1 Overview

The G-Shark firmware incorporates multiple diagnostic and recovery mechanisms that assist in identifying and resolving operational issues during development, deployment, and normal runtime. These mechanisms monitor system initialization, hardware peripherals, wireless services, filesystem access, configuration loading, and runtime execution.

Most operational issues can be isolated by observing system behavior through the OLED display, serial output, embedded web interface, or command-line interface. Since the firmware is composed of modular subsystems, problems can typically be traced to a specific component without affecting unrelated modules.

This section provides general troubleshooting guidance for common firmware conditions and outlines recommended diagnostic procedures.

---

### 28.2 Troubleshooting Architecture

```text
          System Issue Detected
                  │
                  ▼
        Identify Affected Module
                  │
        ┌─────────┼─────────┐
        ▼         ▼         ▼
 Hardware   Configuration  Software
        │         │         │
        ▼         ▼         ▼
 Diagnostics  Validation  Runtime Checks
        │         │         │
        └─────────┼─────────┘
                  ▼
          Corrective Action
                  │
                  ▼
          System Verification
```

The troubleshooting process isolates issues by identifying the responsible subsystem before applying corrective actions.

---

### 28.3 Primary Responsibilities

The troubleshooting subsystem assists with:

- Startup diagnostics
- Hardware verification
- Configuration validation
- Runtime monitoring
- Wireless diagnostics
- Filesystem verification
- Display diagnostics
- Service validation
- Error identification
- Recovery guidance

---

### 28.4 Startup Issues

If the firmware does not initialize correctly, the following components should be verified:

- Stable power supply
- Successful firmware installation
- Correct SPIFFS deployment
- Compatible board configuration
- Proper hardware connections
- Valid EEPROM contents
- Successful boot sequence

Startup issues are typically detected during the initialization phase before runtime services begin.

---

### 28.5 Wireless Issues

Wireless-related problems generally originate from configuration or environmental conditions.

Typical checks include:

- Wireless subsystem initialization
- Access Point status
- Channel configuration
- Signal availability
- Radio initialization
- Runtime configuration
- Client association status

Verifying these parameters helps isolate wireless communication problems.

---

### 28.6 Display Issues

If the OLED interface does not function correctly, the following items should be inspected:

- Display initialization
- Power availability
- I²C communication
- Display configuration
- Rendering engine startup
- Runtime refresh operation
- Hardware connections

Display diagnostics can usually be confirmed during the firmware startup sequence.

---

### 28.7 Filesystem Issues

Problems related to browser resources or embedded content often originate from the filesystem.

Diagnostic checks include:

- SPIFFS mounting
- Filesystem integrity
- Resource availability
- Static asset loading
- Flash memory verification
- Filesystem initialization

If the filesystem cannot be mounted, browser resources may become unavailable until the SPIFFS image is restored.

---

### 28.8 Configuration Issues

Configuration-related problems are typically associated with invalid or unavailable stored settings.

```text
Configuration Error
         │
         ▼
Validate Parameters
         │
         ▼
Load Default Values
         │
         ▼
Store Configuration
         │
         ▼
Restart Services
         │
         ▼
Normal Operation
```

The Configuration System attempts to maintain consistent runtime behavior by validating parameters before they are applied.

---

### 28.9 Runtime Diagnostics

The firmware continuously monitors several runtime components.

Diagnostic areas include:

- Memory usage
- Wireless status
- Filesystem status
- Display status
- Runtime controller
- Configuration manager
- Peripheral initialization
- Service availability

These diagnostics assist in locating operational issues during normal firmware execution.

---

### 28.10 Common Symptoms

Typical observable symptoms include:

| Symptom | Possible Area |
|----------|---------------|
| Device does not boot | Firmware or power initialization |
| Blank OLED display | Display initialization or I²C communication |
| Web interface unavailable | SPIFFS or embedded web server |
| Configuration not retained | EEPROM subsystem |
| Wireless unavailable | Wireless initialization |
| Missing browser resources | SPIFFS filesystem |
| Startup interruption | Initialization sequence |
| Unexpected runtime behavior | Configuration or runtime synchronization |

These symptoms provide an initial indication of the subsystem requiring inspection.

---

### 28.11 Diagnostic Workflow

A structured diagnostic process improves troubleshooting efficiency.

```text
Observe Symptom
        │
        ▼
Identify Subsystem
        │
        ▼
Verify Configuration
        │
        ▼
Check Hardware
        │
        ▼
Inspect Runtime Status
        │
        ▼
Apply Corrective Action
        │
        ▼
Verify Resolution
```

Following a consistent workflow reduces unnecessary troubleshooting steps.

---

### 28.12 Recovery Recommendations

General recovery procedures include:

- Restart the device
- Verify firmware installation
- Confirm SPIFFS deployment
- Validate configuration values
- Restore default settings if necessary
- Rebuild firmware after source modifications
- Reflash firmware when required
- Verify hardware connections

These procedures resolve the majority of installation and runtime issues.

---

### 28.13 Design Characteristics

The troubleshooting framework has been designed according to several architectural principles.

These include:

- Modular diagnostics
- Independent subsystem verification
- Structured fault isolation
- Runtime monitoring
- Configuration validation
- Simplified recovery procedures
- Consistent diagnostic workflow
- Seamless firmware integration

These characteristics improve maintainability while reducing the time required to identify and resolve operational issues.

---

### 28.14 Troubleshooting Summary

| Feature | Description |
|----------|-------------|
| Purpose | Firmware Diagnostics and Issue Resolution |
| Startup Diagnostics | Supported |
| Hardware Verification | Supported |
| Wireless Diagnostics | Supported |
| Display Diagnostics | Supported |
| SPIFFS Diagnostics | Supported |
| EEPROM Validation | Supported |
| Runtime Monitoring | Supported |
| Recovery Guidance | Included |
| Platform | ESP8266 |
| Firmware Architecture | Modular |
| Standalone Operation | Fully Supported |



## 29. License

This project is based on the original work of **Spacehuhn Technologies**, which is licensed under the MIT License.

The G-Shark firmware has been extensively modified and expanded with significant architectural, functional, and interface enhancements, including but not limited to:

- Complete firmware restructuring
- Redesigned OLED user interface
- Modular firmware architecture
- New configuration system
- Enhanced embedded web interface
- Captive portal customization framework
- Additional runtime modules
- Improved display engine
- Expanded command-line interface
- New project documentation
- Performance optimizations
- Bug fixes and stability improvements
- Various additional features and custom implementations

Copyright © 2026 Hashim

Original Project Copyright © 2020 Spacehuhn Technologies

The original MIT License is reproduced below and continues to apply to the portions derived from the original project.

---

**Do not advertise, redistribute, or market this software as a "Wi-Fi Jammer".**

This firmware is intended for educational purposes, firmware research, embedded systems development, and authorized wireless testing within applicable laws and regulations.

---

### MIT License

Copyright (c) 2020 Spacehuhn Technologies

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

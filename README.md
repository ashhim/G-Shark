# G-Shark

## Contents

* [Overview](#overview)
* [Project Architecture](#project-architecture)
* [Hardware Architecture](#hardware-architecture)
* [GPIO / Pinout](#gpio--pinout)
* [Hardware BOM](#hardware-bom)
* [Power Architecture](#power-architecture)
* [Flash, EEPROM, and SPIFFS](#flash-eeprom-and-spiffs)
* [Module Dependency Graph](#module-dependency-graph)
* [Feature Inventory](#feature-inventory)
* [Display / Screen Output](#display--screen-output)
* [Menu Hierarchy](#menu-hierarchy)
* [Web Interface](#web-interface)
* [CLI Reference](#cli-reference)
* [Scan Architecture](#scan-architecture)
* [Attack Architecture](#attack-architecture)
* [Workflow Summary](#workflow-summary)
* [Build / Flash Notes](#build--flash-notes)
* [Files Included](#files-included)

## Overview

G-Shark is a custom **ESP8266 wearable Wi-Fi tool** built around the ESP8266 Deauther codebase and extended with a compact OLED-driven UI, hardware buttons, live scan views, a serial CLI, a local web interface, SPIFFS-backed assets, persistent settings, and multiple monitoring and scanning modes.

The firmware combines the following subsystems into a single embedded platform:

* OLED user interface through `DisplayUI`
* Physical button navigation
* Wi-Fi scanning and live monitoring
* Packet monitor screens
* AP tracker and APST tracker views
* Clock, stopwatch, and timer screens
* Serial command-line control
* Local web interface served from SPIFFS
* Persistent configuration storage
* Optional RTC support
* RGB LED status output
* Captive portal-style local presentation
* Modular wireless analysis and control workflow

The project is centered on a compact wearable form factor, with the display, buttons, scan logic, target selection, and runtime controls all designed to work together as one integrated embedded system.

## Project Architecture

G-Shark follows a layered firmware architecture:

```text
esp8266_deauther.ino
├── settings
├── wifi
├── DisplayUI
├── Scan
├── Attack
├── CLI
├── Accesspoints
├── Stations
├── SSIDs
├── Names
├── LED
└── SPIFFS assets / web UI
```

### Architecture summary

| Layer             | Role                                      |
| ----------------- | ----------------------------------------- |
| Hardware layer    | ESP8266, OLED, buttons, LED, optional RTC |
| Driver layer      | Wi-Fi, display, GPIO, filesystem, EEPROM  |
| State layer       | APs, stations, SSIDs, names, settings     |
| UI layer          | OLED menus, live screens, status pages    |
| Control layer     | Scan, attack, CLI, web interface          |
| Persistence layer | EEPROM config and SPIFFS content          |

The system is designed so that scan results, selected targets, settings, and UI state can be shared across multiple front ends.

## Hardware Architecture

The active watch profile uses an ESP8266 module with an I²C OLED display, four buttons, one WS2812-style RGB LED, and optional DS3231 RTC support.

### Core hardware

| Component         | Role                                 |
| ----------------- | ------------------------------------ |
| ESP8266 module    | Main microcontroller                 |
| SH1106 OLED       | Primary display controller           |
| Buttons           | Menu and action input                |
| WS2812 / NeoPixel | Status indicator                     |
| DS3231 RTC        | Timekeeping, if enabled              |
| Internal flash    | Firmware + SPIFFS + EEPROM emulation |

### Bus overview

| Bus       | Devices                              |
| --------- | ------------------------------------ |
| I²C       | OLED, optional DS3231 RTC            |
| GPIO      | Buttons, RGB LED                     |
| Wi-Fi     | Scanner, monitor, AP/packet features |
| SPI flash | System storage and filesystem        |

## GPIO / Pinout

### Active watch profile

| Function     |   GPIO | NodeMCU label | Notes                   |
| ------------ | -----: | ------------- | ----------------------- |
| OLED SDA     |  GPIO4 | D2            | I²C data                |
| OLED SCL     |  GPIO5 | D1            | I²C clock               |
| Button UP    | GPIO14 | D5            | menu up / scroll up     |
| Button DOWN  | GPIO12 | D6            | menu down / scroll down |
| Button A     |  GPIO2 | D4            | select / confirm        |
| Button B     |  GPIO0 | D3            | back / cancel           |
| NeoPixel DIN | GPIO15 | D8            | status LED              |

### Boot-sensitive pins

| GPIO   | Role                |
| ------ | ------------------- |
| GPIO0  | boot mode-sensitive |
| GPIO2  | boot mode-sensitive |
| GPIO15 | boot mode-sensitive |

### I²C display configuration

| Parameter    | Value    |
| ------------ | -------- |
| Display type | SH1106   |
| Interface    | I²C      |
| Address      | `0x3C`   |
| Resolution   | 128 × 64 |

## Hardware BOM

### Confirmed by firmware

| Component             |        Qty | Purpose                       |
| --------------------- | ---------: | ----------------------------- |
| ESP8266 module        |          1 | Main controller               |
| SH1106 OLED           |          1 | Watch display                 |
| Tactile buttons       |          4 | Navigation and action control |
| WS2812 / NeoPixel LED |          1 | Status indication             |
| DS3231 RTC            | 1 optional | Timekeeping                   |
| Internal SPI flash    |          1 | Firmware and data storage     |

### Required for a functional build

| Component                                | Purpose                           |
| ---------------------------------------- | --------------------------------- |
| 3.3 V regulator                          | Power for ESP8266 and peripherals |
| Battery or regulated supply              | Portable operation                |
| Power switch                             | On/off control                    |
| Programming header or USB-UART bridge    | Flashing and serial access        |
| Pull resistors and decoupling capacitors | ESP8266 support circuitry         |
| Antenna matched to module                | Wi-Fi radio operation             |

## Power Architecture

G-Shark is built around a single 3.3 V logic rail.

```text
USB 5V / battery
→ charging or regulation stage
→ 3.3V rail
→ ESP8266 + OLED + buttons + LED + RTC
```

### Power behavior

| Subsystem                        | Relative load |
| -------------------------------- | ------------- |
| Wi-Fi transmit / frame injection | Highest       |
| Wi-Fi scan / receive             | High          |
| OLED rendering                   | Moderate      |
| RGB LED activity                 | Moderate      |
| RTC standby                      | Minimal       |
| Buttons                          | Negligible    |

### Firmware-controlled power features

| Feature                            | Present |
| ---------------------------------- | ------- |
| OLED on/off                        | Yes     |
| OLED brightness / contrast control | Yes     |
| Wi-Fi active control               | Yes     |
| NeoPixel status control            | Yes     |
| Deep sleep as primary mode         | No      |
| Battery percentage calculation     | No      |
| Low-battery shutdown logic         | No      |

## Flash, EEPROM, and SPIFFS

### Flash usage

The ESP8266 internal flash is used for:

* firmware code
* EEPROM emulation
* SPIFFS filesystem

### EEPROM

EEPROM emulation stores persistent configuration such as:

* scan behavior
* display settings
* LED settings
* AP / attack options
* web / interface preferences
* boot metadata

### SPIFFS

SPIFFS stores local assets used by the firmware:

* HTML pages
* JavaScript files
* CSS
* images
* audio assets
* named portal pages
* generated or exported content

### Notable asset families

| Path or asset group  | Role                        |
| -------------------- | --------------------------- |
| `data/web/`          | web interface files         |
| `data/nameme/`       | branded or themed page sets |
| `data/logo.png`      | visual identity             |
| `data/instapage.jpg` | portal artwork              |
| `data/music.mp3`     | audio asset                 |

## Module Dependency Graph

```text
esp8266_deauther.ino
├── settings
├── wifi
├── DisplayUI
├── Scan
├── Attack
├── CLI
├── Accesspoints
├── Stations
├── SSIDs
├── Names
├── LED
└── SPIFFS assets / web UI
```

### Dependency highlights

| Module        | Depends on                                                               |
| ------------- | ------------------------------------------------------------------------ |
| `DisplayUI`   | `Scan`, `Attack`, `Accesspoints`, `Stations`, `SSIDs`, `Names`, settings |
| `Scan`        | Wi-Fi APIs, AP/station databases                                         |
| `Attack`      | selected APs, stations, SSIDs, Wi-Fi raw transmit support                |
| `CLI`         | shared runtime state and command dispatch                                |
| Web interface | SPIFFS assets, shared state, HTTP server                                 |
| `Settings`    | EEPROM and configuration structures                                      |

## Feature Inventory

### Core system features

* ESP8266 firmware
* Modular class-based design
* Serial console
* OLED front panel
* Local web interface
* SPIFFS-backed assets
* EEPROM-backed settings
* Optional RTC integration
* RGB LED status output

### Wi-Fi features

* AP scanning
* station scanning
* combined scan modes
* hidden AP detection
* channel management
* vendor lookup from OUI data
* promiscuous sniffing
* raw 802.11 frame transmission
* live packet statistics

### UI features

* splash / intro screen
* main menu
* scan menu
* select menu
* attack menu
* packet monitor
* AP tracker
* APST tracker
* APST monitor
* clock
* stopwatch
* timer
* loading screens
* button test
* scrolling lists
* fixed metric columns
* trend arrows
* real-time counters

### Storage and persistence

* settings save/load
* AP / station / SSID / name lists
* SPIFFS file operations
* web assets stored locally
* JSON status outputs for the browser UI

### Web and CLI features

* offline browser-based control surface
* dynamic status pages
* scan data pages
* attack status pages
* settings pages
* scan commands
* selection commands
* LED commands
* screen commands
* script execution commands
* packet send commands
* configuration persistence commands

## Display / Screen Output

This section documents the primary visible output used by the firmware.

### Boot and intro

```text
CRABOX
#iM
G-Shark 2.6
```

### Main menu

```text
SCAN
SELECT
ATTACK
PACKET MONITOR
APST MONITOR
CLOCK
```

### Scan menu

```text
[BACK]
SCAN AP + ST
SCAN APs
SCAN Stations
AUTOSCAN
AP TRACKER
APST TRACKER
```

### Select menu

```text
APs
Stations
SSIDs
Names
```

### Attack menu

```text
[BACK]
DEAUTH
BEACON
PROBE
FISH
CAPAD
START
STOP
```

### Clock menu

```text
CLOCK DISPLAY
SET CLOCK
STOPWATCH
TIMER
```

### Live monitoring layouts

#### AP tracker

```text
APs [15]       PKTs [642]
>Home WiFi      -37 ↑
 Office         -45 ↑
 TP-Link        -61 ↓
```

#### APST tracker

```text
APs [15]       ST [5]
>Home WiFi      -37 ↑ ST [5]
 Office         -45 ↑ ST [2]
 TP-Link        -61 ↓ ST [7]
```

#### APST monitor

```text
AP [0] ST [0]
/_____
---------^--
```

### Common on-screen labels

* `SELECT`
* `PACKET MONITOR`
* `APST MONITOR`
* `CLOCK`
* `CLOCK DISPLAY`
* `SET CLOCK`
* `STOPWATCH`
* `TIMER`
* `SCAN AP + ST`
* `SCAN APs`
* `SCAN Stations`
* `AUTOSCAN`
* `AP TRACKER`
* `APST TRACKER`
* `DEAUTH`
* `BEACON`
* `PROBE`
* `FISH`
* `CAPAD`
* `START`
* `STOP`

## Menu Hierarchy

### Main menu

* SCAN
* SELECT
* ATTACK
* PACKET MONITOR
* APST MONITOR
* CLOCK

### Scan

* SCAN AP + ST
* SCAN APs
* SCAN Stations
* AUTOSCAN
* AP TRACKER
* APST TRACKER

### Select

* APs
* Stations
* SSIDs
* Names

### Attack

* DEAUTH
* BEACON
* PROBE
* FISH
* CAPAD
* START
* STOP

### Clock

* CLOCK DISPLAY
* SET CLOCK
* STOPWATCH
* TIMER

## Web Interface

G-Shark includes a local browser interface served from SPIFFS.

### Web interface capabilities

* local asset hosting
* custom HTML, CSS, JavaScript pages
* embedded status pages
* device configuration pages
* runtime monitoring pages
* scan and selection views
* offline operation
* UI synchronization with OLED state

### Web assets

| Asset type | Examples                            |
| ---------- | ----------------------------------- |
| HTML       | index, attack, info, settings       |
| JavaScript | site, scan, attack, settings, ssids |
| CSS        | shared styling                      |
| Images     | logos and artwork                   |
| Audio      | locally stored media                |

### Portal framework

The captive-portal framework is configurable and can be tailored with custom web pages stored on the device. The firmware can exchange data between the browser interface and the embedded application, and those values can be reflected on the OLED, in status views, or in other runtime screens.

## CLI Reference

The serial CLI provides direct control over scan, selection, settings, display, LED, file, and script functions.

### Typical command groups

| Group     | Purpose                                |
| --------- | -------------------------------------- |
| System    | help, info, reboot, reset, status      |
| Scan      | scan, show, stop                       |
| Attack    | attack, start, stop, packet monitoring |
| Selection | add, remove, select, deselect, clear   |
| Settings  | get, set, save, load                   |
| Display   | screen, draw, buttontest               |
| LED       | led, enable, disable                   |
| Files     | load, save, delete, write, print       |
| Scripts   | script, run                            |
| Wi-Fi     | startap, stopap, rename                |
| Utility   | random, replace, copy, delay           |

### Representative command vocabulary

```text
help
info
sysinfo
status
reboot
reset
format
scan
show
stop
start
attack
send
packetmonitor
add
remove
select
deselect
clear
print
set
get
save
load
settings
random
replace
copy
delete
write
run
script
led
screen
draw
loadingscreen
buttontest
startap
stopap
rename
enable
disable
custom
delay
on
off
```

## Scan Architecture

The scan subsystem is responsible for discovering and organizing Wi-Fi data for the rest of the firmware.

### Scan modes

* AP scan
* station scan
* combined AP + station scan
* autoscan
* AP tracker
* APST tracker
* APST monitor

### Shared data model

| Database     | Role                                |
| ------------ | ----------------------------------- |
| AccessPoints | discovered APs and selection state  |
| Stations     | discovered clients and associations |
| SSIDs        | generated or stored SSID entries    |
| Names        | stored labels and aliases           |

### Runtime behavior

* scan modes update the shared databases
* the display reads from those databases
* the CLI and web UI can inspect the same state
* the attack engine consumes selected targets from those lists

### Tracker extensions

The later UI extensions documented in the change history add:

* persistent autoscan history
* per-AP expiry
* auto-selection of scanned APs
* live AP tracker
* APST tracker with station counts
* APST monitor graph mode
* background scan continuation behavior

## Attack Architecture

The attack subsystem uses raw Wi-Fi frame generation through ESP8266 Wi-Fi APIs.

### Supported methods

* deauthentication
* beacon frame generation
* probe frame generation
* CAPAD
* start / stop control

### High-level flow

1. User selects targets
2. The attack engine reads the selected APs, stations, and SSIDs
3. The firmware builds management frames
4. The ESP8266 transmits raw packets
5. Counters and status update on the OLED, CLI, and web UI

### Attack control data

| Input         | Role                                  |
| ------------- | ------------------------------------- |
| Access points | target selection                      |
| Stations      | target selection                      |
| SSIDs         | generated or cloned identifiers       |
| Settings      | timeout, behavior, output preferences |
| Wi-Fi driver  | raw frame transmission                |

## Workflow Summary

### Boot flow

```text
Power on
→ bootloader
→ setup()
→ SPIFFS / EEPROM / UI init
→ intro screen
→ main menu
```

### Scan flow

```text
Open SCAN
→ choose scan mode
→ update AP/station databases
→ render live list or monitor
```

### Select flow

```text
Open SELECT
→ view APs / Stations / SSIDs / Names
→ choose targets
→ selected items are used by other modules
```

### Attack flow

```text
Open ATTACK
→ choose method
→ start
→ packet generation
→ packet transmit
→ status and counters
```

### Web flow

```text
Connect browser
→ local HTTP page
→ load from SPIFFS
→ request JSON status
→ update controls
```

### CLI flow

```text
Open serial terminal
→ enter command
→ parser dispatches command
→ state updates
→ output printed to serial
```

## Build / Flash Notes

### Platform

* Arduino IDE
* ESP8266 board profile

### Common library dependencies

* OLED driver library
* DS3231 library
* SimpleButton
* SPI / Wire / FS
* ESP8266 Wi-Fi / Arduino core

### Compile-time configuration

The active board profile and screen configuration are selected in `A_config.h`. That file determines:

* display driver
* pin mapping
* button layout
* LED behavior
* optional peripherals
* runtime defaults

## Files Included

### Core source

* `esp8266_deauther.ino`
* `DisplayUI.cpp/.h`
* `Scan.cpp/.h`
* `Attack.cpp/.h`
* `CLI.cpp/.h`
* `Accesspoints.cpp/.h`
* `Stations.cpp/.h`
* `SSIDs.cpp/.h`
* `Names.cpp/.h`
* `settings.cpp/.h`
* `led.cpp/.h`
* `wifi.cpp/.h`
* `language.h`
* `A_config.h`

### Assets

* `data/web/`
* `data/nameme/`
* `data/logo.png`
* `data/instapage.jpg`
* `data/music.mp3`

### Bundled support files

* display driver sources
* RTC support
* button support
* helper headers

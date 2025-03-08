# Lazuli Peripheral
<!-- ![esp32](https://ae01.alicdn.com/kf/S60bfe5f7ed764c1e81522e5a955afeceZ.jpg) -->

Lazuli Peripheral is a Zephyr-based application designed to collect sensor data and transmit it to a central server via WiFi. It also displays connection details on an onboard display.

## Project Overview

This application runs on a microcontroller with WiFi and sensor capabilities, enabling it to:

* Collect temperature, humidity, and pressure sensor data.
* Transmit the collected data to the Lazuli Central server via WiFi.
* Display connection status and sensor readings on an onboard display.

## Project Structure

Lazuli Peripheral/
├── src/          # Source code for the application
│   ├── main.c    # Main application logic
│   ├── sensor.c  # Sensor data collection functions
│   ├── wifi.c    # WiFi communication functions
│   ├── display.c # Display control functions
│   └── ...
├── boards/       # Zephyr board configurations
│   └── <your_board>/ # Your specific board configuration
│       ├── <your_board>.dts
│       └── prj.conf
├── prj.conf      # Zephyr project configuration
├── README.md
└── LICENSE

## Features

* **Sensor Data Collection:** Gathers temperature, humidity, and pressure data from onboard sensors.
* **WiFi Communication:** Transmits sensor data to the Lazuli Central server via WiFi.
* **Onboard Display:** Displays connection status, IP address, and sensor readings.
* **Data Formatting:** [Implement data formatting logic here]
* **Error Handling:** [Implement error handling logic here]
* **Power Saving:** [Implement power saving logic here]

## Getting Started

### Prerequisites

* Zephyr RTOS development environment set up.
* A microcontroller board with WiFi and sensor capabilities.
* [List any other specific hardware requirements here]

### Building and Flashing

1.  Navigate to the `lazuli-peripheral` directory.
2.  Configure and build the application using Zephyr's `west` tool:

    ```bash
    west build -b <your_board>
    ```

    Replace `<your_board>` with the appropriate board name.
3.  Flash the application to the microcontroller:

    ```bash
    west flash
    ```

### Configuration

* **WiFi Configuration:** Configure the WiFi credentials (SSID and password).
    * [Add details on how to configure WiFi within Zephyr]
* **Sensor Configuration:** Configure the sensor drivers and parameters.
    * [Add details on how to configure sensors within Zephyr]
* **Display Configuration:** Configure the display driver and settings.
    * [Add details on how to configure the display within Zephyr]
* **Central Server IP:** Configure the IP address of the Lazuli Central server.
    * [Add details on how to configure the Central server IP address]
* **Data Transmission Interval:** [Add details on how to change the interval that the data is sent]
* **Sensor Calibration:** [Add details on how to calibrate the sensors]

### Usage

1.  Power on the device.
2.  The device will attempt to connect to the configured WiFi network.
3.  Once connected, the device will display connection details on the onboard display.
4.  The device will then begin collecting sensor data and transmitting it to the Lazuli Central server.
5.  View the sensor data on the Lazuli Central server's web interface.

### Dependencies

* Zephyr RTOS
* [List any other dependencies here, like specific sensor libraries, WiFi drivers, display drivers, etc.]
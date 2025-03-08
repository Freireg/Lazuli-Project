# Lazuli Project

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

The Lazuli Project aims to develop two Zephyr-based applications that demonstrate robust embedded system communication and data management.

## Project Overview

This repository contains two primary applications built using the Zephyr RTOS:

* **Lazuli Central:** A microcontroller-based HTTP server with Ethernet connectivity. It receives data from peripheral devices, stores it on an SD card, and displays the gathered data on a dynamic HTML webpage.
* **Lazuli Peripheral:** An end device that collects sensor data (temperature, humidity, and pressure), transmits it to the central server via WiFi, and displays connection details on an onboard display.

## Project Structure

Lazuli Project/
├── lazuli-central/    # Source code for Lazuli Central application
│   ├── src/
│   ├── boards/
│   ├── prj.conf
│   └── ...
├── lazuli-peripheral/ # Source code for Lazuli Peripheral application
│   ├── src/
│   ├── boards/
│   ├── prj.conf
│   └── ...
├── README.md
└── LICENSE


## Lazuli Central

The Lazuli Central application functions as a central data hub, providing the following features:

* **HTTP Server:** Hosts a web server to receive data from peripheral devices.
* **Data Storage:** Stores received data on an SD card for persistent storage.
* **Web Interface:** Displays gathered data through an HTML-based webpage, offering a user-friendly interface.
* **Ethernet Connectivity:** Utilizes Ethernet for reliable network communication.

## Lazuli Peripheral

The Lazuli Peripheral application acts as a remote sensor node, offering the following features:

* **Sensor Data Collection:** Gathers temperature, humidity, and pressure data from onboard sensors.
* **WiFi Communication:** Transmits sensor data to the Lazuli Central server via WiFi.
* **Onboard Display:** Displays connection status and other relevant information on an onboard display.

## Getting Started with Zephyr

## Building and Flashing

### Zephyr Freestanding Application
To set up the environment, run the following command:
```sh
source ~/zephyrproject/zephyr/zephyr-env.sh
```
### Lazuli Central

1.  Navigate to the `lazuli-central` directory.
2.  Configure and build the application using Zephyr's `west` tool:

    ```bash
    west build -b <board_name>
    ```

    Replace `<board_name>` with the appropriate board name.
3.  Flash the application to the microcontroller:

    ```bash
    west flash
    ```

### Lazuli Peripheral

1.  Navigate to the `lazuli-peripheral` directory.
2.  Configure and build the application using Zephyr's `west` tool:

    ```bash
    west build -b <board_name>
    ```

    Replace `<board_name>` with the appropriate board name.
3.  Flash the application to the microcontroller:

    ```bash
    west flash
    ```

## Dependencies

* Zephyr RTOS
* [List any other dependencies here, like specific sensor libraries, network drivers, etc.]

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues to suggest improvements or report bugs.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
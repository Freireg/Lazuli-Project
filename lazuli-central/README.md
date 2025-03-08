# Lazuli Central
<!-- ![frdm](https://br.mouser.com/images/nxp/lrg/FRDMK64F_t.jpg) -->

Lazuli Central is a Zephyr-based application designed to act as a central data hub for sensor information collected from peripheral devices. It features an HTTP server, SD card data storage, and a dynamic web interface.

## Project Overview

This application runs on a microcontroller with Ethernet connectivity, enabling it to:

* Receive sensor data from Lazuli Peripheral devices via HTTP requests.
* Store the received data persistently on an SD card.
* Serve a dynamic HTML webpage that displays the collected data.

## Project Structure

Lazuli Central/
├── src/          # Source code for the application
│   ├── main.c    # Main application logic
│   ├── http_server.c # HTTP server implementation
│   ├── sd_card.c   # SD card access functions
│   ├── web_page.c # logic for generating the webpage
│   └── ...
├── boards/       # Zephyr board configurations
│   └── <your_board>/ # Your specific board configuration
│       ├── <your_board>.dts
│       └── prj.conf
├── prj.conf      # Zephyr project configuration
└── README.md
## Features

* **HTTP Server:** Implements an HTTP server to receive data from peripheral devices.
* **SD Card Storage:** Utilizes an SD card for reliable and persistent data storage.
* **Dynamic Web Interface:** Provides an HTML-based webpage to visualize collected data.
* **Ethernet Connectivity:** Leverages Ethernet for stable network communication.
* **Data Parsing:** [Implement data parsing logic here if needed]
* **Error Handling:** [Implement error handling logic here]

## Getting Started

### Prerequisites

* Zephyr RTOS development environment set up.
* A microcontroller board with Ethernet and SD card support.
* [List any other specific hardware requirements here]

### Building and Flashing

1.  Navigate to the `lazuli-central` directory.
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

* **Network Configuration:** Configure the Ethernet interface with appropriate IP address, subnet mask, and gateway.
    * [Add details on how to configure the network within Zephyr]
* **SD Card Configuration:** Ensure the SD card is properly formatted and connected to the microcontroller.
    * [Add details on how to configure the SD card within Zephyr]
* **Web Page Customization:** Modify the `web_page.c` file to customize the displayed data and the web page's appearance.
    * [Add details on how to customize the webpage]
* **HTTP Server Port:** [Add details on how to change the port of the HTTP server]
* **Data Storage Format:** [Add details on how the data is stored on the SD card]

### Usage

1.  Connect the microcontroller to your network via Ethernet.
2.  Power on the device.
3.  Access the web interface by entering the microcontroller's IP address in a web browser.
4.  Send data from Lazuli Peripheral devices to the microcontroller's HTTP server.
5.  View the collected data on the web page.

### Dependencies

* Zephyr RTOS
* [List any other dependencies here, like specific SD card libraries, network drivers, etc.]

### Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues to suggest improvements or report bugs.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

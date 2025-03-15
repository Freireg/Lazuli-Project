#include <stdio.h>
#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/net/tls_credentials.h>
#include <zephyr/net/http/server.h>
#include <zephyr/net/http/service.h>
#include <zephyr/net/net_ip.h>
#include <zephyr/net/socket.h>
#include "zephyr/device.h"
#include "zephyr/sys/util.h"
#include <zephyr/drivers/led.h>
#include <zephyr/data/json.h>
#include <zephyr/sys/util_macro.h>

#include <zephyr/net/net_config.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_http_server_sample, LOG_LEVEL_DBG);

// Server configuration
static uint16_t test_http_service_port = CONFIG_NET_HTTP_SERVER_SERVICE_PORT;
HTTP_SERVICE_DEFINE(test_http_service, NULL, &test_http_service_port, 1,
		    10, NULL, NULL);

// Functions prototypes
static void setup_tls(void);

int main(void){
  int ret = 0;

  net_config_init_app(NULL, "Initializing Network");
  http_server_start();

  return 0;
}
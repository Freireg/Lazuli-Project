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

// HTTPS structures

static uint8_t index_html_gz[] = {
#include "index.html.gz.inc"
};

static struct http_resource_detail_static index_html_gz_resource_detail = {
	.common = {
			.type = HTTP_RESOURCE_TYPE_STATIC,
			.bitmask_of_supported_http_methods = BIT(HTTP_GET),
			.content_encoding = "gzip",
			.content_type = "text/html",
		},
	.static_data = index_html_gz,
	.static_data_len = sizeof(index_html_gz),
};

// Server configuration
static uint16_t test_http_service_port = CONFIG_NET_HTTP_SERVER_SERVICE_PORT;
HTTP_SERVICE_DEFINE(test_http_service, NULL, &test_http_service_port, 1,
		    10, NULL, NULL);

HTTP_RESOURCE_DEFINE(index_html_gz_resource, test_http_service, "/",
		     &index_html_gz_resource_detail);

/* -------------------------------------------------------- */
// Functions prototypes


/* -------------------------------------------------------- */


int main(void){
  int ret = 0;

  //Initialize this network application
  net_config_init_app(NULL, "Initializing Network");
  //Start the HTTP2 server
  http_server_start();

  return 0;
}
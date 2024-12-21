#include "api/v1.c"

const httpd_uri_t pages_list[] = {
  home_page,
  api_v1__get_buttons_count,
  api_v1__get_buttons_status
};


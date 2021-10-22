#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_sd.h"


#define PIN_NUM_MISO 12
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   15

struct mgos_sd * sd_card = NULL;
struct json_out * json_temp;

enum mgos_app_init_result mgos_app_init(void)
{
  json_temp = (struct json_out *) calloc(1, sizeof(struct json_out));
  mgos_jsar_enableSDPortSpiMode();

  sd_card = mgos_sd_open(false, "/sdcard", 0);

  LOG(LL_INFO, ("Mount point:%s", mgos_sd_get_mount_point()));

  mgos_sd_print_info(json_temp);


  //LOG(LL_INFO, ("Size:%d, len %d", json_temp->u.buf.size, json_temp->u.buf.len));
  //LOG(LL_INFO, ("Chars: %s", json_temp->u.buf.buf));



  return MGOS_APP_INIT_SUCCESS;
}
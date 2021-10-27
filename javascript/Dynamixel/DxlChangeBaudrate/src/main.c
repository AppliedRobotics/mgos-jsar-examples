#include "mgos.h"
#include "mgos_jsar.h"

const uint8_t id = 0x15; // RGB
const unsigned long baudrate_57k = 57600;
const unsigned long baudrate_1kk = 1000000;

/* Create Dynamixel device */ 
DynamixelDevice * rgb = NULL;



enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_dxl_master_begin(baudrate_1kk);

  rgb = mgos_dxl_module_create(id);
  mgos_dxl_init(rgb);

  LOG(LL_INFO, ("Ping: %d", mgos_dxl_ping(rgb)));

  mgos_dxl_write(rgb, 26, 5);
  mgos_dxl_write(rgb, 27, 0);
  mgos_dxl_write(rgb, 28, 0);
  mgos_msleep(500);

  mgos_dxl_communicationSpeed(rgb, baudrate_57k);
  mgos_msleep(500);
  mgos_dxl_master_begin(baudrate_57k);
  mgos_msleep(500);
  LOG(LL_INFO, ("Ping1kk: %d", mgos_dxl_ping(rgb)));

  mgos_dxl_write(rgb, 26, 5);
  mgos_dxl_write(rgb, 27, 5);
  mgos_dxl_write(rgb, 28, 5);




  return MGOS_APP_INIT_SUCCESS;
}

#include "mgos.h"
#include "mgos_jsar.h"

DynamixelConsole *console;

static void loop(void *arg)
{
  mgos_dxl_console_loop(console);
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_dxl_master_begin(57600);
  console = mgos_dxl_console_create();  
  mgos_set_timer(1000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}



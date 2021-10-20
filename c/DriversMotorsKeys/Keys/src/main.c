#include "mgos.h"
#include "mgos_jsar.h"

#define PIN 36

static void loop(void *arg)
{
  mgos_jsar_KeysDigitalWrite(1, 1);
  mgos_jsar_KeysDigitalWrite(2, 0);
  mgos_jsar_KeysDigitalWrite(3, 1);
  mgos_jsar_KeysDigitalWrite(4, 0);
  mgos_msleep(1000);

  mgos_jsar_KeysDigitalWrite(1, 0);
  mgos_jsar_KeysDigitalWrite(2, 1);
  mgos_jsar_KeysDigitalWrite(3, 0);
  mgos_jsar_KeysDigitalWrite(4, 1);
  mgos_msleep(1000);

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_KeysBegin();

  mgos_set_timer(2000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

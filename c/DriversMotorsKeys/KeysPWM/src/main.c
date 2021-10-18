#include "mgos.h"
#include "mgos_jsar.h"

static void loop(void *arg)
{
  mgos_jsar_KeysPowerWrite(1, 10);
  mgos_jsar_KeysPowerWrite(2, 20);
  mgos_jsar_KeysPowerWrite(3, 30);
  mgos_jsar_KeysPowerWrite(4, 40);
  mgos_msleep(1000);

  mgos_jsar_KeysPowerWrite(1, 40);
  mgos_jsar_KeysPowerWrite(2, 30);
  mgos_jsar_KeysPowerWrite(3, 20);
  mgos_jsar_KeysPowerWrite(4, 10);
  mgos_msleep(1000);

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_KeysBegin();

  mgos_set_timer(2000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
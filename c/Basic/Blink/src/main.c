#include "mgos.h"
#include "mgos_jsar.h"

#define LED_PIN 2

static void loop(void *arg)
{
  mgos_gpio_toggle(LED_PIN);
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_gpio_set_mode(LED_PIN, MGOS_GPIO_MODE_OUTPUT);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

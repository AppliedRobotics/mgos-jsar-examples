#include "mgos.h"
#include "mgos_jsar.h"

int16_t power1 = 50;
int16_t power2 = 100;


static void loop(void *arg)
{
  int16_t e1, e2, s1, s2, p1, p2;

  mgos_jsar_MotorsPowerWrite(1, power1);
  mgos_jsar_MotorsPowerWrite(2, power2);

  mgos_jsar_MotorsPositionReadAll(&e1, &e2);
  mgos_jsar_MotorsSpeedReadAll(&s1, &s2);
  mgos_jsar_MotorsPowerReadAll(&p1, &p2);

  LOG(LL_INFO, ("p1: %d\t p2: %d", p1, p2));
  LOG(LL_INFO, ("e1: %d\t e2: %d", e1, e2));
  LOG(LL_INFO, ("s1: %d\t s2: %d", s1, s2));
 

  mgos_msleep(100);  

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_MotorsBegin();

  mgos_jsar_MotorsEncoderModeAB();

  LOG(LL_INFO, ("Start!"));
  
  mgos_msleep(1000);

  mgos_set_timer(500, MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

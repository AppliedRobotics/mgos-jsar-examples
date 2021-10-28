#include "mgos.h"
#include "mgos_jsar.h"

int16_t speed = 1;
int16_t power = 1;
uint8_t pid_p = 16, pid_i = 32, pid_d = 0;
uint8_t encoder_mode = 1;

uint8_t buf[128];
uint8_t p = 0, pp = 0;

/* User UART callback */
void user_cb(uint16_t len, uint8_t *data, void *userdata)
{
  memcpy(buf + p, data, len);
  p = p + len;
  (void) userdata;
}

static void loop(void *arg)
{
  int16_t e1, e2, s1, s2, p1, p2;
  
  pp = 0;
  
  while (pp < p) {
    char c = buf[pp++];
    switch (c) {
      case ']': speed += 5; mgos_jsar_MotorsSpeedWrite(1, speed); break;
      case '[': speed -= 5; mgos_jsar_MotorsSpeedWrite(1, speed); break;
      //case 'p': speed += 5; mgos_jsar_MotorsPowerWrite(1, power); break;
      //case 'o': speed -= 5; mgos_jsar_MotorsPowerWrite(1, power); break;
      case '1': pid_p -= 1; mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);break;
      case '2': pid_p += 1; mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);break;
      case '3': pid_i -= 1; mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);break;
      case '4': pid_i += 1; mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);break;
      case '5': pid_d -= 1; mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);break;
      case '6': pid_d += 1; mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);break;
      case 'b': mgos_jsar_MotorsEncoderModeAB(); break;
      case 'a': mgos_jsar_MotorsEncoderModeA();  break;
      case 'r': mgos_jsar_MotorsEncoderModeARising(); break;
    }
  };

  mgos_jsar_MotorsReadAll(&e1, &s1, &e2, &s2);
  p1 = mgos_jsar_MotorsPowerRead(1);

  LOG(LL_INFO, ("Speed: %d\t p1: %d\t", speed, p1));
  LOG(LL_INFO, ("PID_p: %d\t PID_i: %d\t PID_d: %d", pid_p, pid_i, pid_d));
  LOG(LL_INFO, ("e1: %d\t e2: %d\t", e1, e2));
  LOG(LL_INFO, ("s1: %d\t s2: %d\t", s1, s2));


  mgos_msleep(100);  

  p = 0;

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_MotorsBegin();();

  mgos_jsar_MotorsLoopPeriodWrite(10);
  mgos_jsar_MotorsPidWrite(pid_p, pid_i, pid_d);
  mgos_jsar_MotorsEncoderModeAB();
  mgos_jsar_MotorsMaxPowerWrite(500);
  LOG(LL_INFO, ("Start!"));
  
  mgos_msleep(1000);

  mgos_dxl_setUserUartCb(user_cb, NULL);
  mgos_set_timer(500, MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

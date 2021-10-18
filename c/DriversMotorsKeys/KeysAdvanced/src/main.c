#include "mgos.h"
#include "mgos_jsar.h"

#define UARTno (0)

int16_t speed = 0;
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
  uint16_t e1, e2, e3, e4, s1, s2, s3, s4, p4;
  
  pp = 0;
  
  while (pp < p) {
    char c = buf[pp++];
    switch (c) {
      case ']': speed += 5; mgos_jsar_KeysSpeedWrite(4, speed); break;
      case '[': speed -= 5; mgos_jsar_KeysSpeedWrite(4, speed); break;
      //case ']': speed += 5; mgos_jsar_KeysSpeedWrite(1, speed); break;
      //case '[': speed -= 5; mgos_jsar_KeysSpeedWrite(1, speed); break;
      case '1': pid_p -= 1; mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d); break;
      case '2': pid_p += 1; mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d); break;
      case '3': pid_i -= 1; mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d); break;
      case '4': pid_i += 1; mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d); break;
      case '5': pid_d -= 1; mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d); break;
      case '6': pid_d += 1; mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d); break;
    }
  };

  e1 = mgos_jsar_KeysPositionRead(1);
  e2 = mgos_jsar_KeysPositionRead(2);
  e3 = mgos_jsar_KeysPositionRead(3);
  e4 = mgos_jsar_KeysPositionRead(4);
  s1 = mgos_jsar_KeysSpeedRead(1);
  s2 = mgos_jsar_KeysSpeedRead(2);
  s3 = mgos_jsar_KeysSpeedRead(3);
  s4 = mgos_jsar_KeysSpeedRead(4);
  
  p4 = mgos_jsar_KeysPowerRead(4);
  
  LOG(LL_INFO, ("Speed: %d\t p4: %d\t", speed, p4));
  LOG(LL_INFO, ("PID_p: %d\t PID_i: %d\t PID_d: %d", pid_p, pid_i, pid_d));
  LOG(LL_INFO, ("e1: %d\t e2: %d\t", e1, e2));
  LOG(LL_INFO, ("e3: %d\t e4: %d\t", e3, e4));
  LOG(LL_INFO, ("s1: %d\t s2: %d\t", s1, s2));
  LOG(LL_INFO, ("s3: %d\t s4: %d\t", s3, s4));

  mgos_msleep(100);  

  p = 0;

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_KeysBegin();

  mgos_jsar_KeysLoopPeriodWrite(10);
  mgos_jsar_KeysEncodersEnable();
  mgos_jsar_KeysPidWrite(pid_p, pid_i, pid_d);

  mgos_dxl_setUserUartCb(user_cb, NULL);
  mgos_set_timer(500, MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

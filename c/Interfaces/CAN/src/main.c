#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_jsar_can.h"

CAN_device_t CAN_cfg;               // CAN Config
const int rx_queue_size = 10;       // Receive Queue s


static void loop(void *arg)
{
  CAN_frame_t rx_frame;

  // Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      mgos_uart_printf(0, "\nNew standard frame:");
    } 
    else {
      mgos_uart_printf(0, "\nNew extended frame:");
    }

    if (rx_frame.FIR.B.RTR == CAN_RTR) {
      mgos_uart_printf(0, " RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
    } 
    else {
      mgos_uart_printf(0, " from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);

      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
         mgos_uart_printf(0, "0x%02X ", rx_frame.data.u8[i]);
      }
      
    }
  }

  /* Send CAN Message */
  CAN_frame_t tx_frame;
  tx_frame.FIR.B.FF = CAN_frame_std;
  tx_frame.FIR.B.RTR = CAN_no_RTR;
  tx_frame.MsgID = 0x033;
  tx_frame.FIR.B.DLC = 8;
  tx_frame.data.u8[0] = 0x33;
  tx_frame.data.u8[1] = 0x34;
  tx_frame.data.u8[2] = 0x32;
  tx_frame.data.u8[3] = 0x33;
  tx_frame.data.u8[4] = 0x3a;
  tx_frame.data.u8[5] = 0x3b;
  tx_frame.data.u8[6] = 0x3e;
  tx_frame.data.u8[7] = 0x3f;
  mgos_jsar_can_write_frame(&tx_frame);
  
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_enableCanModule();

  /* Configure and Init CAN Module */
  CAN_cfg.speed = CAN_SPEED_125KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_2;
  CAN_cfg.rx_pin_id = GPIO_NUM_39;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  mgos_jsar_can_init();

  /* Timers */
  mgos_set_timer(1000 , MGOS_TIMER_REPEAT, loop, NULL);

  LOG(LL_INFO, ("Can app init end"));

  return MGOS_APP_INIT_SUCCESS;
}

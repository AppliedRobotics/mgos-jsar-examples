#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_ir.h"

const uint16_t rxPin = 34;
const uint16_t txPin = 2;

static void irrecv_cb(void *arg)
{
  struct mgos_irrecv_nec_s *obj = (struct mgos_irrecv_nec_s *)arg;

  LOG(LL_INFO, ("IR_rx: %08X", obj->code.dword));
  (void) arg;
}

static void loop(void *arg)
{

  mgos_irsend_nec(txPin, 0xff55, true);

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_msleep(1000);
  mgos_jsar_enableIrRx();
  mgos_jsar_enableIrTx();

  mgos_irrecv_nec_create(rxPin, irrecv_cb, NULL);

  mgos_set_timer(2000 , MGOS_TIMER_REPEAT, loop, NULL);
  return MGOS_APP_INIT_SUCCESS;
}
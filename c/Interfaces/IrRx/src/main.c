#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_ir.h"

#define PIN 34

static void irrecv_cb(void *arg)
{
  struct mgos_irrecv_nec_s *obj = (struct mgos_irrecv_nec_s *)arg;

  LOG(LL_INFO, ("IR_rx: %08X", obj->code.dword));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_msleep(1000);
  mgos_jsar_enableIrRx();

  mgos_irrecv_nec_create(34, irrecv_cb, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
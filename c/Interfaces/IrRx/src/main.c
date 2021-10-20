#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_ir.h"

#define PIN 34

struct mgos_irrecv_nec_s * ir_inst = NULL;

void irrecv_cb(int code, void *arg)
{
  LOG(LL_INFO, ("IR: %08X", code));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_enableIrRx();

  ir_inst = mgos_irrecv_nec_create(PIN, irrecv_cb, NULL);

  LOG(LL_INFO, ("IrRx app end"));
  return MGOS_APP_INIT_SUCCESS;
}




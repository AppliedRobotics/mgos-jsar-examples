load('api_config.js');
load('api_sys.js');
load('api_gpio.js');
load('api_timer.js');
load('api_ir.js');
load('api_jsar.js');

let rx_pin = 34;
let rx_code = 0;
let rx_new = false;

JsAr.enableIrRx();

// TSOP on pin 14, NEC protocol
let ir = IR.Receiver.NEC.create(rx_pin, function(code) {
    rx_code = code;
    rx_new = true;
}, null);

Timer.set(500, Timer.REPEAT, function() {
    if (rx_new === true) {
        print("IR", rx_code);
        rx_new = false;
    }
  
  }, null);
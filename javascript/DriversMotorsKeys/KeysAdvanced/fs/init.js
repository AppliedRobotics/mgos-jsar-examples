load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');
/*
let speed = 0;
let pid_p = 16, pid_i = 32, pid_d = 0;
let encoder_mode = 1;

let uart_cb = function(len, data) {
  print('len:', len, 'Data:', data[len-1]);
};

DxlMaster.set_uart_callback(uart_cb, null);

print('Start Keys app');

JsArKeys.begin();

Timer.set(2500, Timer.REPEAT, function() {
    JsArKeys.digitalWrite(1, state);
    JsArKeys.digitalWrite(2, !state);
    JsArKeys.digitalWrite(3, state);
    JsArKeys.digitalWrite(4, !state);
    state = !state;
  }, null);
  */
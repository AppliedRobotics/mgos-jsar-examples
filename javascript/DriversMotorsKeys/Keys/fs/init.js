load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

let state = false;

print('Start Keys app');

JsArKeys.begin();

Timer.set(2500, Timer.REPEAT, function() {
    JsArKeys.digitalWrite(1, state);
    JsArKeys.digitalWrite(2, !state);
    JsArKeys.digitalWrite(3, state);
    JsArKeys.digitalWrite(4, !state);
    state = !state;
  }, null);
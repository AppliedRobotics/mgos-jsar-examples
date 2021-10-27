load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let led_state = false;

Timer.set(1000, Timer.REPEAT, function() {
  JsAr.expanderWriteLed(led_state);
  led_state = !led_state;
}, null);
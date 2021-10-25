load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let led_state = false;

Timer.set(300, Timer.REPEAT, function() {
  if (led_state === false) {
    led_state = true;
    JsAr.expanderWriteLed(1);
  } else {
    led_state = false;
    JsAr.expanderWriteLed(0);
  }

}, null);
load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start Keys PWM app');

JsArKeys.begin();

JsArKeys.powerWrite(1, 20);
JsArKeys.powerWrite(2, 40);
JsArKeys.powerWrite(3, 80);
JsArKeys.powerWrite(4, 160);


load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start js app');


JsArMotors.begin();
JsArMotors.powerWrite(1, 50);
JsArMotors.powerWrite(2, 150);





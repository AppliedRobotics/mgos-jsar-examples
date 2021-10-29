load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start Keys PWM app');

JsArKeys.begin();

JsArKeys.speedWrite(1, 50);
JsArKeys.speedWrite(2, 100);
JsArKeys.speedWrite(3, 150);
JsArKeys.speedWrite(4, 200);

Timer.set(500, Timer.REPEAT, function() {
    let e1, e2, e3, e4;

    JsArKeys.encodersEnable();
    e1 = JsArKeys.positionRead(1);
    e2 = JsArKeys.positionRead(2);
    e3 = JsArKeys.positionRead(3);
    e4 = JsArKeys.positionRead(4);

    print('e1', e1, 'e2', e2, 'e3', e3, 'e4', e4, );
  
  }, null);


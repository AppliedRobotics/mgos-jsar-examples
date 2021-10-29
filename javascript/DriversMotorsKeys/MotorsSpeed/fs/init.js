load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Motors Speed app');

JsArMotors.begin();
JsArMotors.encoderModeAB();

JsArMotors.speedWrite(1, 100);
JsArMotors.speedWrite(2, 200);

print('Start!');


Timer.set(500, Timer.REPEAT, function() {
  let pos1, pos2;

  pos1 = JsArMotors.positionRead(1);
  pos2 = JsArMotors.positionRead(2);
  print('Pos1:', pos1, 'Pos2:', pos2);
  
}, null);


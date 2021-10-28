load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start dxl console app');

DxlMaster.begin(57600);
let console = DynamixelConsole.create();

Timer.set(1000, Timer.REPEAT, function() {
    DynamixelConsole.loop(console);
  }, null);

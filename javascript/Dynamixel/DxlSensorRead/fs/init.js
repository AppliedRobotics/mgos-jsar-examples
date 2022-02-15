load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start js app');

let id = 0x08; 
let ROM_ID = 0x03;

let sensor = DynamixelDevice.create(id);

DxlMaster.begin(57600);

if (sensor.init() !== 0) {
    print('Sensor init: Error');
} else {
    print('Sensor init: Ok'); 
}


Timer.set(1000, Timer.REPEAT, function() {
    // Read first 6 bytes
    print('ROM 0:', sensor.read(0) , ' 1:', sensor.read(1), ' 2:', sensor.read(2), 
          ' 3:', sensor.read(3), ' 4:', sensor.read(4), ' 5:', sensor.read(5));

    // 8bit read
    let read_id = sensor.read(ROM_ID);
    if (sensor.status() !== 0) read_id = 0;
    if (read_id === id) {
        print('Read8  success', id , '==', read_id);
    } else {
        print('Read8  wrong', id , '!=', read_id);
    }

    // 16bit read
    let read16_id = sensor.read16(2);
    if (sensor.status() !== 0) read16_id = 0;

    let val = (id << 8) + sensor.read(2);

    if (read16_id === val) {
        print('Read16 success', val , '==', read16_id);
    } else {
        print('Read16 wrong', val, '!=', read16_id);
    }
    
    print('');

}, null);





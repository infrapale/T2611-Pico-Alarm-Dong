/************************************************************************************************************************************
@title T2602_PicoTFT28_AIO
@git  	https://github.com/infrapale/T2602_PicoTFT28_AIO.git
************************************************************************************************************************************
@HW Raspberry Pi Pico W on a pico TFT classic board (2.8" TFT display + 4 Cherry key buttons)

************************************************************************************************************************************
https://github.com/adafruit/Adafruit_MQTT_Library
https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial1-creating-freertos-task-to-blink-led-in-arduino-uno
https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial-using-semaphore-and-mutex-in-freertos-with-arduino
https://learn.adafruit.com/dvi-io/code-the-dashboard
***********************************************************************************************************************************/


#include "main.h"
#include <SPI.h>
#include <Wire.h>
#include "io.h"
#include "atask.h"
#include "io.h"
#include "rfm.h"
#include "comm.h"
#include "sd.h"
#include "dingdong.h"
#include "action.h"


void print_debug_task(void)
{
  atask_print_status(true);
}

//                                  123456789012345   ival  next  state  prev  cntr flag  call backup
atask_st debug_task_handle    =   {"Debug Task     ", 2000,    0,     0,  255,    0,  1,  print_debug_task };



uint32_t  targetTime = 0; 

void run_tft_pin_check(void);

void setup(void) {
    delay(2000);
    Serial1.setTX(PIN_TX0);   //SerialLte connected to Clipper 4G
    Serial1.setRX(PIN_RX0);   
    Serial2.setTX(PIN_TX1);   //SerialRfm connected to RFM MCU 
    Serial2.setRX(PIN_RX1);   // RFM69 and RuuviTag

    Serial.begin(115200);
    Serial1.begin(9600);
    Serial2.begin(9600);

    delay(2000);
    //while (!Serial);
    Serial.println(F(__APP__));
    Serial.printf(" Compiled: %s %s\n",__DATE__, __TIME__);
    Wire1.setSDA(PIN_I2C1_SDA);
    Wire1.setSCL(PIN_I2C1_SCL);
    Wire1.begin();

    SPI.setRX(PIN_SPI_0_MISO); // or setMISO()
    SPI.setCS(PIN_SD_CS);
    SPI.setSCK(PIN_SPI_0_SCK);
    SPI.setTX(PIN_SPI_0_MOSI); // or setMOSI()
    SPI.begin(false);


    io_initialize();
    atask_initialize();
    // atask_add_new(&debug_task_handle);
    io_task_initialize();
    rfm_initialize();
    action_initialize();
    dingdong_initialize();
    // dingdong_play_all();
}

void setup1()
{
  //Watchdog.reset();
  targetTime = millis() + 100;
}

// Fast running loop
void loop() 
{
  atask_run();
  rfm_rx_task();
}

// Slow running loop: WiFI an MQTT
void loop1()
{
  if (millis() > targetTime)
  {
    targetTime = millis() + 100;
    
  }
}

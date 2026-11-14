#ifndef __IO_H__ 
#define __IO_H__
#include "Arduino.h"
#include "main.h"
//#define BOARD_PICO_TFT_4KEYS

#define PIN_TX0         (0u)
#define PIN_RX0         (1u)
#define PIN_I2C1_SDA    (2u)
#define PIN_I2C1_SCL    (3u)
#define PIN_I2C0_SDA    (4u)
#define PIN_I2C0_SCL    (5u)
// LED
#define PIN_LED_RED     (6u)
#define PIN_LED_YELLOW  (7u)

#define PIN_TX1         (8u)
#define PIN_RX1         (9u)

// I2S Audio Out
#define PIN_I2S_BCLK    (10u)
#define PIN_I2S_LRCLK   (11u)
#define PIN_I2S_DOUT    (12u)

#define PIN_SW_1        (13u)
#define PIN_SW_2        (14u)
#define PIN_SW_3        (15u)

#define PIN_SW_WD_EN    PIN_SW_1


// SD Card SPI
#define PIN_SPI_0_SCK   (18u)
#define PIN_SPI_0_MOSI  (19u)
#define PIN_SPI_0_MISO  (16u)
#define PIN_SD_CS       (17u)

#define PIN_PIR         (22u)
#define PIN_LDR_AN      (A0)

typedef enum
{
    LED_INDX_RED =0,
    LED_INDX_YELLOW,
    LED_INDX_NBR_OF
} led_index_et;


typedef enum
{
  BLINK_OFF = 0,
  BLINK_ON,
  BLINK_SHORT_FLASH,
  BLINK_FLASH,
  BLINK_FAST_FLASH,
  BLINK_SLOW_BLINK,
  BLINK_BLINK,
  BLINK_FAST_BLINK,
  BLINK_SOS,
  BLINK_RELIABLE_CLIENT,
  BLINK_SERVER,
  BLINK_RELIABLE_SERVER,
  BLINK_NBR_OF
} blink_et;

// MISO 16 MOSI 19 SCLK 18 CS 13 DC 15 RST 9 BL 13 T_CS 21
//#define PIN_TFT_CS            (17u)


void io_initialize(void);
void io_task_initialize(void);

bool io_wd_is_enabled(void);

uint16_t io_read_ldr(void);
uint16_t io_read_akbd(void);
void io_led_flash(led_index_et lindx, blink_et bindx, uint16_t tick_nbr);
void io_task(void);



#endif

#include <Arduino.h>
#include "SPI.h"
#include "st7735s_compat.h"
#include "ASettings.h"

#define CS_PIN    OLED_CS
#define RES_PIN   OLED_RESET
#define DC_PIN    OLED_DC
#define MOSI_PIN  OLED_MOSI
#define SCK_PIN   OLED_CLK
#define BLK_PIN    OLED_BACKLIGHT

void SPI_Init(void) {
    pinMode(CS_PIN, OUTPUT);
    pinMode(RES_PIN, OUTPUT);
    pinMode(DC_PIN, OUTPUT);
    pinMode(BLK_PIN, OUTPUT);
    pinMode(MOSI_PIN, OUTPUT);
    pinMode(SCK_PIN, OUTPUT);

    digitalWrite(CS_PIN, LOW);
    digitalWrite(RES_PIN, HIGH);

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void Pin_CS_Low(void) {
}

void Pin_CS_High(void) {
}

void Pin_RES_High(void) {
    digitalWrite(RES_PIN, HIGH);
}

void Pin_RES_Low(void) {
    digitalWrite(RES_PIN, LOW);
}

void Pin_DC_High(void) {
    digitalWrite(DC_PIN, HIGH);
}

void Pin_DC_Low(void) {
    digitalWrite(DC_PIN, LOW);
}
extern uint8_t backlight_pct;
void Pin_BLK_Pct(uint8_t pct) {
	backlight_pct = pct;
    // or connect to PWM output
    digitalWrite(BLK_PIN, HIGH);
}

void SPI_send(uint16_t len, uint8_t *data) {
	digitalWrite(CS_PIN, LOW);

    while (len--)
        SPI.transfer(*data++);

    digitalWrite(CS_PIN, HIGH);
}

void SPI_TransmitCmd(uint16_t len, uint8_t *data) {
    Pin_DC_Low();
    SPI_send(len, data);
}

void SPI_TransmitData(uint16_t len, uint8_t *data) {
    Pin_DC_High();
    SPI_send(len, data);
}

void SPI_Transmit(uint16_t len, uint8_t *data) {
     SPI_TransmitCmd(1, data++);
     if (--len)
        SPI_TransmitData(len, data);
}

void _Delay(uint32_t d) {
    uint32_t m = millis();
    while (millis() - m < d) ;
}


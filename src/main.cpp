#include "SD.h"
#include <epdiy.h>
#include <M5Unified.h>

// https://docs.m5stack.com/en/core/papers3
// https://github.com/m5stack/M5GFX/blob/master/docs/M5PaperS3.md
// https://docs.m5stack.com/ja/arduino/m5cores3/sdcard
// display 540 x 960, 16 gray levels
// MicroSD CS: GPIO_NUM_47, SCK:GPIO_NUM_39, MISO:GPIO_NUM_40, MOSI:GPIO_NUM_38

#define SD_SPI_CS_PIN   GPIO_NUM_47
#define SD_SPI_SCK_PIN  GPIO_NUM_39
#define SD_SPI_MISO_PIN GPIO_NUM_40
#define SD_SPI_MOSI_PIN GPIO_NUM_38

#define icon_scale  1.4
#define icon_width  232 * icon_scale
#define icon_height 308 * icon_scale

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Power.begin();
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
    delay(500);

    while (false == SD.begin(GPIO_NUM_47, SPI, 15000000)) {
        Serial.println("SD Wait...");
        delay(500);
    }

    M5.Display.begin();
    M5.Display.startWrite();
        M5.Display.setRotation(0);
        M5.Display.setTextSize(4);
        M5.Display.drawString("kakimochi", 4*1, 4*1);
        M5.Display.drawPngFile(SD, "/kakimochi.png", 
            (M5.Display.width() - icon_width)/2, (M5.Display.height() - icon_height)/2,
            M5.Display.width(), M5.Display.height(), 0,
            icon_scale, icon_scale);
    M5.Display.endWrite();

    Serial.println("[Info] init done");
}

void loop() {

}


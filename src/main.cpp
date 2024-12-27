#include "SD.h"
#include <epdiy.h>
#include <M5Unified.h>

// 参考情報
// https://docs.m5stack.com/en/core/papers3
// https://github.com/m5stack/M5GFX/blob/master/docs/M5PaperS3.md
// https://docs.m5stack.com/ja/arduino/m5cores3/sdcard

// M5Paper S3 hardware情報
// display 540 x 960, 16 gray levels
// MicroSD CS: GPIO_NUM_47, SCK:GPIO_NUM_39, MISO:GPIO_NUM_40, MOSI:GPIO_NUM_38

// microSD SPI pin設定
#define SD_SPI_CS_PIN   GPIO_NUM_47
#define SD_SPI_SCK_PIN  GPIO_NUM_39
#define SD_SPI_MISO_PIN GPIO_NUM_40
#define SD_SPI_MOSI_PIN GPIO_NUM_38

// icon表示設定
#define ICON_DISP_SCALE  1.9    // icon画像の表示倍率
#define ICON_W  232             // icon画像サイズ
#define ICON_H  308
#define ICON_DISP_WIDTH  (ICON_W * ICON_DISP_SCALE)
#define ICON_DISP_HEIGHT (ICON_H * ICON_DISP_SCALE)

// QRコード表示設定
#define QR_DISP_SCALE  0.7     // QRコード画像の表示倍率
#define QR_W  280              // QRコード画像サイズ
#define QR_H  280
#define QR_DISP_WIDTH  (QR_W * QR_DISP_SCALE)
#define QR_DISP_HEIGHT (QR_H * QR_DISP_SCALE)

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Power.begin();
    USBSerial.begin(115200);
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
    delay(100);

    while (false == SD.begin(GPIO_NUM_47, SPI, 15000000)) {
        USBSerial.println("[Info] SD Wait...");
        delay(500);
    }

    M5.Display.begin();
    M5.Display.startWrite();
        M5.Display.setRotation(2);
        // header
        M5.Display.setTextSize(6);
        M5.Display.setTextColor(WHITE, DARKGREY);
        M5.Display.drawString(" kakimochi     ", 0, 0);
        // icon
        M5.Display.drawPngFile(SD, "/kakimochi.png", (M5.Display.width() - ICON_DISP_WIDTH)/2, (M5.Display.height() - ICON_DISP_HEIGHT)/2 - 100, M5.Display.width(), M5.Display.height(), 0, ICON_DISP_SCALE, ICON_DISP_SCALE);
        // footer
        M5.Display.setTextSize(6);
        M5.Display.setTextColor(WHITE, DARKGREY);
        M5.Display.drawString("   @crazybocan ", 0, 910);
        // QR
        M5.Display.drawPngFile(SD, "/kakimochi_x_qr.png", (M5.Display.width() - QR_DISP_WIDTH)/2 + 120, (M5.Display.height() - QR_DISP_HEIGHT)/2 + 240, M5.Display.width(), M5.Display.height(), 0, QR_DISP_SCALE, QR_DISP_SCALE);

    M5.Display.endWrite();

    USBSerial.println("[Info] init done");
}

void loop() {

}


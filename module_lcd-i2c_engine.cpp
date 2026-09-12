#include "core_web/FSWebServerLib.h"

#include "core_ntp/NtpClientLib.h"

#include "module_lcd-i2c.h"
#include "core_sys/eertos.h"

#include <Wire.h>

// ============================================================
// Конкретная логика модуля
// ============================================================

void CLASS_MODULE_I2C_LCD::_initDisplay() {
    DEBUGLCD("%s: addr=0x%02X, cols=%d, rows=%d, bl=%d\r\n",
             __FUNCTION__, _config.i2cAddr, _config.cols, _config.rows, _config.backlight);

    Wire.begin(LCD_I2C_SDA, LCD_I2C_SCL);

    if (_lcd) { _lcd->clear(); _lcd->noBacklight(); _lcd = NULL; }

    _lcd = new LiquidCrystal_I2C(_config.i2cAddr, _config.cols, _config.rows);
    _lcd->init();
    if (_config.backlight) { _lcd->backlight(); } else { _lcd->noBacklight(); }
    _lcd->clear();

    _applyLines();
}

void CLASS_MODULE_I2C_LCD::_applyLines() {
    if (!_lcd) { return; }

    bool ntpSynced = (NTP.getLastNTPSync() > 0);

    for (uint8_t r = 0; r < _config.rows && r < LCD_I2C_MAX_ROWS; r++) {
        String line = _displayLines[r];
        String out;

        if (line == "date") {
            if (ntpSynced) {
                String dt = NTP.getTimeDateString();
                int spaceIdx = dt.indexOf(' ');
                if (spaceIdx > 0) {
                    String d = dt.substring(0, spaceIdx);
                    if (d.length() >= 10) {
                        out = d.substring(0, 10);
                    } else {
                        out = d;
                    }
                } else {
                    out = "--.--.----";
                }
            } else {
                out = "--.--.----";
            }
        } else if (line == "time") {
            if (ntpSynced) {
                String dt = NTP.getTimeDateString();
                int spaceIdx = dt.indexOf(' ');
                if (spaceIdx > 0 && (int)dt.length() > spaceIdx + 8) {
                    out = dt.substring(spaceIdx + 1, spaceIdx + 9);
                } else {
                    out = "--:--:--";
                }
            } else {
                out = "--:--:--";
            }
        } else {
            out = line;
        }

        if (out.length() > _config.cols) { out = out.substring(0, _config.cols); }
        _lcd->setCursor(0, r);
        _lcd->print(out);
        uint8_t remaining = _config.cols - out.length();
        if (remaining > 0) {
            for (uint8_t i = 0; i < remaining; i++) { _lcd->print(' '); }
        }
    }
}

void CLASS_MODULE_I2C_LCD::_lcdUpdateTask() {
    module_lcd_i2c._applyLines();
    SetTimerTask(_lcdUpdateTask, 1000);
}

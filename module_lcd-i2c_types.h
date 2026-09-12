#ifndef _MODULE_LCD_I2C_TYPES_h
#define _MODULE_LCD_I2C_TYPES_h

// ============================================================
// module_lcd-i2c_types.h — типы, структуры и define'ы модуля LCD I2C.
// Реализация: module_lcd-i2c.cpp (шаблон) и
// module_lcd-i2c_engine.cpp (дисплей и перерисовка).
// ============================================================

#include <Arduino.h>
#include <stdint.h>

#if defined(ESP32)
#define LCD_I2C_SDA  21
#define LCD_I2C_SCL  22
#endif

#if defined(ESP8266)
#define LCD_I2C_SDA  4
#define LCD_I2C_SCL  5
#endif

#define CONFIG_FILE_LCD_I2C       "/config_lcd-i2c.json"
#define LCD_I2C_MAX_ROWS          4
#define LCD_I2C_MAX_LINE_LEN      40

typedef struct {
    uint8_t i2cAddr;
    uint8_t cols;
    uint8_t rows;
    bool    backlight;
} strLcdConfig;

#endif // _MODULE_LCD_I2C_TYPES_h

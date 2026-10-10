# module_lcd-i2c — LCD I2C

> **Опциональный модуль.** Подключается через `src_filter` + `build_flags`.
> **Работоспособен только в составе сборки, содержащей ядро** (см. `../../TRS.md` §2.1).

Управление LCD-дисплеем по I2C: до 4 строк, подсветка, настройка адреса/столбцов/строк,
раскрытие масок `date`/`time`, задача перерисовки раз в секунду.

- **Репозиторий:** https://github.com/Arcanum753/module_lcd-i2c
- **Папка:** `src/module_lcd-i2c/`
- **Флаг активации:** `-D MODULE_LCD_I2C`
- **Registry:** `object=module_lcd_i2c`, `define=MODULE_LCD_I2C`, `web=1`, `loop=0` (без `namespace`/`res`/`prio`)
- **Только для платформы:** обе (ESP8266/ESP32)
- **Зависит от модулей:** —
- **Зависит от ядра:** `core_web`, `core_sys`, `core_json` (маски даты/времени — `core_sys.timeNow()`)

## Назначение

Управление LCD-дисплеем I2C: до 4 строк, подсветка, настройка адреса/столбцов/строк,
раскрытие масок `date`/`time`, задача перерисовки раз в секунду.

## Функциональные требования

- FR-LCD-1: Инициализация дисплея по I2C (`LCD_I2C_SDA/SCL`); лимиты `LCD_I2C_MAX_ROWS=4`, `LCD_I2C_MAX_LINE_LEN=40`.
- FR-LCD-2: Конфиг `/config_lcd-i2c.json`: `i2cAddr` (по умолчанию `0x27`), `cols`, `rows`, `backlight`, `display_lines[]`.
- FR-LCD-3: Поддержка масок даты/времени в строках; время — `core_sys.timeNow()` (валидность — `core_sys.timeValid()`); перерисовка раз в секунду.
- FR-LCD-4: Включение/выключение подсветки без перезагрузки.

## Аппаратные интерфейсы

| Интерфейс | Выводы по умолчанию | Примечание |
|-----------|---------------------|------------|
| I2C (LCD) | ESP32 21/22, ESP8266 4/5 (SDA/SCL) | адрес задаётся в `config_lcd-i2c.json` (`i2cAddr`, по умолчанию `0x27`) |

## Веб-интерфейс

Маршруты: `GET /lcd-i2c/info`, `POST /lcd-i2c/save_content`, `/lcd-i2c/save_config`,
`GET /lcd-i2c/sysinfo`, `POST /lcd-i2c/backlight`, `GET /lcd-i2c/ver`.
Страницы `lcd-i2c.html`, `lcd-i2c2.html` (пункт меню — `web/_menu.html`).

## Конфигурация

`/config_lcd-i2c.json` — поля: `i2cAddr` (по умолчанию `0x27`), `cols`, `rows`,
`backlight`, `display_lines[]`.

## Слоистая структура

Из `../../LAYERS.md`: `module_lcd-i2c` — LCD I2C: вывод строк, backlight; сейчас
`strLcdConfig`, пин-define'ы; выделить `_types.h`, `_engine.cpp`.

## Тестирование

- HIL-стенд (уровень 5): реальный LCD I2C на шине (см. `../../TESTING.md`).

## Ссылки

- Ядро и конвенции: `../../TRS.md`
- Слоистая структура: `../../LAYERS.md`
- Общие утилиты: `../../TRS.md` §3.1.12 (`common/`)
- Сборка: `../../BUILD.md`
- Реестр компонентов: `../../INVENTORY.md`

> Если модуль читается вне дерева ядра (standalone), корневые документы доступны в
> репозитории ядра avr-fota.

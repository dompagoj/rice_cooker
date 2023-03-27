#pragma once

#include "Color.h"
#include "app_state.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define HEIGHT 240
#define WIDTH 240

#define TFT_MOSI 23 // SDA Pin on ESP32
#define TFT_SCLK 18 // SCL Pin on ESP32
#define TFT_CS 15   // Chip select control pin
#define TFT_DC 4    // Data Command control pin
#define TFT_RST 2   // Reset pin (could connect to RST pin)

enum class TextAlign
{
    Center,
    Left,
    Right,
};

namespace UI
{
void init();
void clear();
void draw(const AppState &state);
void wifi_start();
void wifi_connected();
} // namespace UI
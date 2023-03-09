#include "ui.h"
#include "globals.h"
#include "macros.h"
#include "utils.h"
#include <WiFi.h>
#include <functional>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

static i16 bounds_x, bounds_y = 0;

struct Vec2
{
    i16 x, y;
};

struct TextBounds
{
    i16 x, y;
    u16 w, h;
};

TextBounds get_text_bounds(const String &str)
{
    TextBounds bounds{};

    tft.getTextBounds(str, tft.getCursorX(), tft.getCursorY(), &bounds.x, &bounds.y, &bounds.w, &bounds.h);

    return bounds;
}

Vec2 get_x_centered(const String &str, i16 offset = 0)
{
    u16 w, h = 0;

    static constexpr i16 middle = WIDTH / 2;
    static constexpr i16 xDest = 0;
    i16 yDest = tft.getCursorY();

    tft.getTextBounds(str, xDest, yDest, &bounds_x, &bounds_y, &w, &h);
    return {middle - (w / 2) + offset, yDest};
}

void print_aligned_center(const String &str, i16 x_offset = 0)
{
    i16 x, y;
    auto coords = get_x_centered(str, x_offset);
    tft.setCursor(coords.x, coords.y);
    tft.print(str);
}

void print_aligned_left(const String &str)
{
    NOT_IMPL();
}

void print_aligned_right(const String &str)
{
}

void print_to_center(const String &str, i16 y_offset = 0, i16 x_offset = 0)
{
    tft.setCursor(0, HEIGHT / 2);
    auto coords = get_x_centered(str);

    tft.setCursor(coords.x + x_offset, coords.y + y_offset);
    tft.print(str);
}

void next_line(u8 lines = 1)
{
    for (int i = 0; i < lines; i++)
        tft.println();
}

void refresh_if_changed(bool changed, const String &str)
{
    if (changed)
    {
        auto bounds = get_text_bounds(str);
        tft.fillRect(bounds.x, bounds.y, bounds.w, bounds.h, Color::Black);
    }
}

void draw_timer()
{
}

void UI::draw(const AppState &state)
{
    tft.setCursor(0, HEIGHT / 4);
    print_aligned_center("Power: ", -10);
    auto circleXCord = tft.getCursorX() + 5;
    tft.fillCircle(circleXCord, tft.getCursorY() + 5, 15, state.m_power.state ? Color::Green : Color::Red);

    next_line(2);

    print_aligned_center("Heat:  ", -10);
    tft.fillCircle(circleXCord, tft.getCursorY() + 5, 15, state.m_heat.state ? Color::Green : Color::Red);

    next_line(2);

    print_aligned_center("Sensor: ", -10);
    refresh_if_changed(state.m_turnoff_sensor.is_changed, "OFF");
    if (state.m_turnoff_sensor.state)
        tft.print("ON");
    else
        tft.print("OFF");

    tft.println();
}

void UI::clear()
{
    tft.fillScreen(Color::Black);
}

void UI::init()
{
    tft.init(HEIGHT, WIDTH, SPI_MODE2);
    clear();
    tft.setRotation(1);
}

void UI::wifi_start()
{
    clear();
    tft.setTextSize(3);

    print_to_center("Hi dompa", -30);
    tft.setTextSize(2);
    print_to_center("Connecting to wifi", 20);
}

void UI::wifi_connected()
{
    clear();
    DEBUG(return;)

    auto ip = WiFi.localIP();
    tft.setCursor(WIDTH / 2, HEIGHT / 2);
    tft.setTextColor(Color::Green);
    print_to_center("Conntected to wifi!", -30);
    print_to_center(ip.toString(), 15);
    tft.setTextColor(Color::White);

    delay(3000);

    clear();
}

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

i16 get_x_centered(const String &str, i16 offset = 0)
{
    u16 w, h = 0;

    static constexpr i16 middle = WIDTH / 2;
    static constexpr i16 xDest = 0;
    // i16 yDest = tft.getCursorY();

    tft.getTextBounds(str, xDest, 0, &bounds_x, &bounds_y, &w, &h);

    return (middle - (w / 2)) + offset;
}

void print_aligned_center(const String &str, i16 x_offset = 0)
{
    i16 x, y;
    auto x_center = get_x_centered(str, x_offset);
    tft.setCursor(x_center, tft.getCursorY());
    tft.print(str);
}

void print_aligned_left(const String &str)
{
    NOT_IMPL();
}

void print_aligned_right(const String &str)
{
    NOT_IMPL();
}

void print_to_center(const String &str, i16 y_offset = 0, i16 x_offset = 0)
{
    auto x_coord = get_x_centered(str);
    tft.setCursor(x_coord + x_offset, HEIGHT / 2 + y_offset);
    tft.print(str);
}

template <u8 Lines = 2> void next_line()
{
    for (u8 i = 0; i < Lines; i++)
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

void UI::draw(const AppState &state)
{
    if (state.m_is_display_off)
    {
        clear();
        delay(20);
        return;
    }
    auto x_center = get_x_centered("00:00");
    tft.setCursor(x_center - 25, HEIGHT / 4);
    tft.setTextSize(4);
    refresh_if_changed(state.m_cooker.has_changed(), "00:00");
    tft.print(state.m_cooker.get_str());
    tft.setTextSize(2);

    next_line<3>();

    print_aligned_center("Warm: ", -10);
    auto circleXCord = tft.getCursorX() + 5;
    tft.fillCircle(circleXCord, tft.getCursorY() + 5, 15, state.m_keep_warm.state ? Color::Green : Color::Red);

    next_line();

    print_aligned_center("Heat:  ", -10);
    tft.fillCircle(circleXCord, tft.getCursorY() + 5, 15, state.m_cooker.m_heat.state ? Color::Green : Color::Red);

    next_line<3>();

    print_aligned_center("Overheat: ", -10);
    refresh_if_changed(state.m_turnoff_sensor.is_changed, "Yes");
    if (state.m_turnoff_sensor.state)
        tft.print("Yes");
    else
        tft.print("No");
}

void UI::clear()
{
    tft.fillScreen(Color::Black);
}

void UI::init()
{
    tft.init(HEIGHT, WIDTH, SPI_MODE2);
    clear();
    tft.setRotation(2);
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
    IF_DEBUG(return;)

    auto ip = WiFi.localIP();
    tft.setCursor(WIDTH / 2, HEIGHT / 2);
    tft.setTextColor(Color::Green);
    print_to_center("Conntected to wifi!", -30);
    print_to_center(ip.toString(), 15);
    tft.setTextColor(Color::White);

    delay(3000);

    clear();
}

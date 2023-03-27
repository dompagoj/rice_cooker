#include "globals.h"

#define ROTARY_PIN1 34
#define ROTARY_PIN2 35

AppState app_state{};

CustomHASwitch devices::keep_warm_switch("keep_warm_switch", Pin(12, OUTPUT, true), "Power", "mdi:power");
CustomHASwitch devices::high_temp_switch("high_temp_switch", Pin(14, OUTPUT, true), "High temp", "mdi:thermometer-high");
Buzzer devices::buzzer{};
CustomHASensor devices::turn_off_sensor("turn_off_sensor", Pin(19, INPUT, true), "Temp sensor", "mdi:thermometer-off");
OneButton devices::power_button(22, true, true);
OneButton devices::rotary_button(21, true, false);
Rotary devices::rotary_encoder(ROTARY_PIN1, ROTARY_PIN2);

HASensor devices::timer_sensor_ha("timer");

IRAM_ATTR void tick_rotary()
{
    devices::rotary_encoder.tick(); // just call tick() to check the state.
}

void devices::init_devices()
{
    devices::timer_sensor_ha.setName("Timer");
    devices::timer_sensor_ha.setIcon("mdi:clock-outline");
    devices::timer_sensor_ha.setValue("10:00:00");

    devices::keep_warm_switch.m_ChangeCb = [](bool state, CustomHASwitch *sw) {
        if (state)
            return;

        devices::high_temp_switch.turn_off();
    };

    devices::high_temp_switch.m_ChangeCb = [](bool state, CustomHASwitch *sw) {
        if (!state)
            return;

        devices::keep_warm_switch.turn_on();
    };

    devices::turn_off_sensor.m_ChangeCb = [](bool state, CustomHASensor *sensor) {
        if (state)
            app_state.m_cooker.end();

        sensor->setValue(state ? "On" : "OFF");
    };

    devices::power_button.attachClick([]() {
        if (app_state.m_is_display_off)
        {
            app_state.m_is_display_off = false;
            return;
        }
        devices::keep_warm_switch.toggle();
        if (app_state.m_cooker.m_is_started)
        {
            app_state.m_cooker.end();
        }
    });

    devices::power_button.attachLongPressStart([]() {
        if (!app_state.m_cooker.m_is_started && app_state.m_cooker.is_zero())
            app_state.m_is_display_off = true;

        app_state.m_cooker.reset();
    });

    devices::rotary_button.attachClick([]() {
        if (app_state.m_cooker.is_zero())
            return;

        if (app_state.m_cooker.m_is_started)
        {
            devices::high_temp_switch.turn_off();
            app_state.m_cooker.pause();
        }
        else
        {
            devices::high_temp_switch.turn_on();
            app_state.m_cooker.start();
        }
    });

    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), tick_rotary, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), tick_rotary, CHANGE);
}

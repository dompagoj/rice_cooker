#include "globals.h"

AppState app_state{};

CustomHASwitch devices::power_switch("power_switch", Pin(17, OUTPUT, true), "Power", "mdi:power");
CustomHASwitch devices::high_temp_switch("high_temp_switch", Pin(16, OUTPUT, true), "High temp", "mdi:thermometer-high");
CustomHASwitch devices::buzzer_switch("buzzer_switch", Pin(5, OUTPUT), "Buzzer", "mdi:alarm-light");
CustomHASensor devices::turn_off_sensor("turn_off_sensor", Pin(19, INPUT, true), "Temp sensor", "mdi:thermometer-off");

HASensor devices::timer_sensor_ha("timer");

void devices::init_devices()
{
    devices::timer_sensor_ha.setName("Timer");
    devices::timer_sensor_ha.setIcon("mdi:clock-outline");
    devices::timer_sensor_ha.setValue("10:00:00");

    devices::power_switch.m_ChangeCb = [](bool state, CustomHASwitch *sw) {
        if (state)
            return;

        devices::high_temp_switch.turn_off();
    };

    devices::high_temp_switch.m_ChangeCb = [](bool state, CustomHASwitch *sw) {
        if (!state)
            return;

        devices::power_switch.turn_on();
    };

    devices::turn_off_sensor.m_ChangeCb = [](bool state, CustomHASensor *sensor) {
        if (state)
            devices::high_temp_switch.turn_off();

        sensor->setValue(state ? "On" : "OFF");
    };
}

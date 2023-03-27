#pragma once
#include "ha_wrappers.h"

// CustomHASwitch devices::buzzer_switch("buzzer_switch", Pin(5, OUTPUT), "Buzzer", "mdi:alarm-light");

struct Buzzer : public CustomHASwitch
{
    /* data */
    Buzzer() : CustomHASwitch("buzzer_switch", Pin(5, OUTPUT), "Buzzer", "mdi:alarm-light")
    {
    }

    void cook_ended()
    {
        buzz(350, 350);
        buzz(350, 350);
        buzz(350, 350);
        buzz(3500);
    }

    void cook_started()
    {
        buzz(750);
    }

  private:
    void buzz(u16 d1 = 0, u16 d2 = 0)
    {
        turn_on();
        if (d1 > 0)
            delay(d1 / 2);
        turn_off();
        if (d2 > 0)
            delay(d2);
    }
};

#pragma once

#include "pin.h"
#include <ArduinoHA.h>

struct CustomHASwitch : private HASwitch
{
    CustomHASwitch(const char *id, Pin pin, const char *name, const char *icon = nullptr);
    void (*m_ChangeCb)(bool state, CustomHASwitch *sw);

    void turn_off();
    void turn_on();
    void set_state(bool state);
    void toggle();
    bool read_state();
    bool read_ha_state();

  private:
    Pin m_Pin;
};

struct CustomHASensor : public HASensor
{
    CustomHASensor(const char *id, Pin pin, const char *name, const char *icon = nullptr);
    void (*m_ChangeCb)(bool state, CustomHASensor *sensor);

    Pin m_Pin;
    bool m_State;

    bool read_state();
    bool update_state();
};
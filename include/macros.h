#pragma once

#define NOT_IMPL()                                                                                                                         \
    Serial.printf("NOT IMPLEMENTED! | %s::%s::%d", __FILE__, __func__, __LINE__);                                                          \
    while (true)                                                                                                                           \
    {                                                                                                                                      \
    }

#ifndef _COMMON_H_
#define _COMMON_H_

#include <Arduino.h>
#include "user_config.h"

void setupCommon();
void write_to_log(String line, ...);
String read_log_buffer();


typedef struct { 
    bool isLightOn;
    bool isAutoChangeColor;
    int userSetColor[3];
    unsigned int updateInternalSeconds;
    unsigned int version;
    unsigned int animationTimeMs;
} moodLightState;


extern moodLightState globalState;
#endif
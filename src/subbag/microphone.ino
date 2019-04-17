/**
 * Microphone interface code. @see /misc/microphone.ino for testing.
 * This file is not used.
 */

#include <driver/adc.h>

#define AUDIO_BUFFER_MAX 800

uint8_t audioBuffer[AUDIO_BUFFER_MAX];
uint8_t transmitBuffer[AUDIO_BUFFER_MAX];
uint32_t bufferPointer = 0;

bool transmitNow = false;

hw_timer_t * timer = NULL; // our timer
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; 

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux); // says that we want to run critical code and don't want to be interrupted
  int adcVal = adc1_get_voltage(ADC1_CHANNEL_0); // reads the ADC
  uint8_t value = map(adcVal, 0 , 4096, 0, 255);  // converts the value to 0..255 (8bit)
  audioBuffer[bufferPointer] = value; // stores the value
  bufferPointer++;
 
  if (bufferPointer == AUDIO_BUFFER_MAX) { // when the buffer is full
    bufferPointer = 0;
    memcpy(transmitBuffer, audioBuffer, AUDIO_BUFFER_MAX); // copy buffer into a second buffer
    transmitNow = true; // sets the value true so we know that we can transmit now
  }
  portEXIT_CRITICAL_ISR(&timerMux); // says that we have run our critical code
}

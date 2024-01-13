#include <Calculations.h> 
#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
/// @brief Check the current amount/
/// @param currentAmount 
/// @return amount + 10
int checkCurrentAmount(double currentAmount){
  // for now it is +=10
  // later it will check the weight
  currentAmount += 10;
  return currentAmount;
}
// #include "config.h"
// extern config_str myconf;


// void statusLED(boolean traffic)
// {
//   static int gnStatusValueCurrent = -1;
//   static long int gnLastUpdate = millis();

//   if (Settings.Pin_status_led == -1)
//     return;

//   if (gnStatusValueCurrent<0)
//     pinMode(Settings.Pin_status_led, OUTPUT);

//   int nStatusValue = gnStatusValueCurrent;

//   if (traffic)
//   {
//     nStatusValue += STATUS_PWM_TRAFFICRISE; //ramp up fast
//   }
//   else
//   {

//     if (WiFi.status() == WL_CONNECTED)
//     {
//       long int delta = timePassedSince(gnLastUpdate);
//       if (delta>0 || delta<0 )
//       {
//         nStatusValue -= STATUS_PWM_NORMALFADE; //ramp down slowly
//         nStatusValue = std::max(nStatusValue, STATUS_PWM_NORMALVALUE);
//         gnLastUpdate=millis();
//       }
//     }
//     //AP mode is active
//     else if (WifiIsAP())
//     {
//       nStatusValue = ((millis()>>1) & PWMRANGE) - (PWMRANGE>>2); //ramp up for 2 sec, 3/4 luminosity
//     }
//     //Disconnected
//     else
//     {
//       nStatusValue = (millis()>>1) & (PWMRANGE>>2); //ramp up for 1/2 sec, 1/4 luminosity
//     }
//   }

//   nStatusValue = constrain(nStatusValue, 0, PWMRANGE);

//   if (gnStatusValueCurrent != nStatusValue)
//   {
//     gnStatusValueCurrent = nStatusValue;

//     long pwm = nStatusValue * nStatusValue; //simple gamma correction
//     pwm >>= 10;
//     if (Settings.Pin_status_led_Inversed)
//       pwm = PWMRANGE-pwm;

//     #if defined(ESP8266)
//       analogWrite(Settings.Pin_status_led, pwm);
//     #endif
//   }
// }

// void statusLED(boolean value) {
//     if (value) {
//         if (myconf.status_led_inversed) {
//             digitalWrite(myconf.status_led, HIGH);
//         } else {
//             digitalWrite(myconf.status_led, LOW);
//         }
//     } else {
//         if (myconf.status_led_inversed) {
//             digitalWrite(myconf.status_led, LOW);
//         } else {
//             digitalWrite(myconf.status_led, HIGH);
//         }
//     }
// }


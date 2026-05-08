# Smart-Baby-Cradle
Smart Baby Cradle  Controller is an intelligent Arduino-powered system that monitors a baby's crying, diaper condition, and automatically soothes with cradle rocking, ambient light, buzzer notification and music.
# COMPONENTS
### -- Arduino Uno ---------- Main microcontroller — runs all logic
### A0 -- Moisture Sensor--- --- Detects wet diaper (analog input)
### D2 -- Sound Sensor (KY-038)- Detects baby crying (digital HIGH)
### D3 -- LED (PWM) ------------ Ambient light — fades in/out smoothly
### D4 -- Buzzer --------------- Beeps 3× to alert parents of wet diaper
### D9 -- Relay Module --------- Switches music speaker ON/OFF
### D6 -- Servo Motor (SG90) --- Rocks cradle

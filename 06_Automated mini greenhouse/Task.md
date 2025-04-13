# Exam: Electrical Engineering with Arduino

**Duration:** 180 minutes  
**Allowed Resources:** Arduino IDE, datasheets, (personal notes)

---

## Scenario: Automated Greenhouse

In the automated mini-greenhouse, temperature, humidity, time, and control elements are to be monitored and displayed:

- Temperature and humidity are measured using a **DHT11 sensor**  
- Values are displayed on an **OLED screen**  
- The **maximum temperature** is permanently displayed  
- The **current time** is shown using a **RTC (real-time clock)**  
- If the **temperature exceeds 28°C**, a **vent flap opens (servo motor)** and a **red LED** lights up  
- If the **humidity drops below 40%**, **watering starts (stepper motor)**  
- **LED brightness** can be controlled via a **potentiometer**  
- The system can be **activated/deactivated** with an **IR remote control**  
- A **push button tests the system**:
  - The **red LED** lights up for one second
  - The word "**TEST**" appears on the **OLED**
- The last measured **maximum temperature value** is saved to **EEPROM** and displayed again after restart

---

## Tasks

### 1. Circuit Setup (20 points)

Build the corresponding circuit using the Arduino board.  
Enter the used pins in the table in `task.docx`.

---

### 2. Programming the Functions (90 points)

- Temperature + humidity + OLED display + max value + red LED (**30 points**)  
- Time display on OLED (**10 points**)  
- Control of ventilation (servo) and watering (stepper motor) (**20 points**)  
- LED dimming using potentiometer (**10 points**)  
- IR remote control system on/off (**10 points**)  
- Save max temperature in EEPROM and load after restart (**10 points**)

---

### 3. Testing the Circuit (20 points)

Test your circuit using the button:

- LED lights up for one second  
- "TEST" appears on the OLED  
- Enter the status of each function in the test list in `task.docx`

---

## Notes

### Pin Assignment

Enter the Arduino pins used in `task.docx`:

| Module            | Arduino Pin |
|-------------------|-------------|
| Red LED           |             |
| DHT11 Sensor      |             |
| OLED Display      |             |
| RTC (Clock)       |             |
| Servo Motor       |             |
| Stepper Motor     |             |
| IR Receiver       |             |
| Potentiometer     |             |
| Push Button       |             |

---

### Test List

| Function                             | Status (e.g. OK, error description, not implemented) |
|--------------------------------------|------------------------------------------------------|
| Temperature measurement + display    |                                                      |
| Maximum value display                |                                                      |
| Max value saved to EEPROM            |                                                      |
| Time display on OLED                 |                                                      |
| LED when >28°C                       |                                                      |
| Vent opens at 28°C                   |                                                      |
| Watering when <40%                   |                                                      |
| LED dimming via potentiometer        |                                                      |
| IR remote on/off                     |                                                      |
| Button test (LED + "TEST")           |                                                      |

---

## Total Points: 130

**Good luck!**

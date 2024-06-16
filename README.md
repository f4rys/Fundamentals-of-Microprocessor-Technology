# Fundamentals of Microprocessor Technology
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

Assignments from the subject of Fundamentals of Microprocessor Technology. Built using SimulIDE and Arduino IDE. Solutions are based on the Arduino Mega controller.
## Content

1. **Simple calculator:**
Built using a keypad and LCD. Capable of execution of simple arithmetic operations on two integers.

<br>
<div align="center">
  <p>
    <img src="calculator/calculator.png"/>
  </p>
</div>

2. **Clock:**
Built using servomechanisms, seven-segment displays and steppers. It counts down the time that has elapsed since the mechanism was switched on and gives a short beep after each minute has elapsed.

<br>
<div align="center">
  <p>
    <img src="clock/clock.png"/>
  </p>
</div>

3. **Codes converter:**
Converts a number from binary form (Input on the left side of the board) to the code of a seven-segment display. Input from the top side of the  board (also in binary form) determines the type of code to be used,  according to a list:

<br>

<div>0 - Binary code to decimal code</div>
<div>1 - Gray code to decimal code</div>
<div>2 - Binary to hexadecimal code</div>
<div>3 - Gray code to hexadecimal code</div>
<div>4 - Aiken code to decimal code</div>
<div>5 - Aiken code to hexadecimal code</div>
<div>6 - Johnson code to the decimal code</div>
<div>7 - Johnson code to hexadecimal code</div>
<br>

Example:

<div>
Controller input: 001<sub>(2)</sub> = 1<sub>(10)</sub>
</div>
<div>
Number input: 10001111<sub>(GRAY)</sub> = 245<sub>(10)</sub>
</div>

<br>
<div align="center">
  <p>
    <img src="codes_converter/codes_converter.png"/>
  </p>
</div>

4. **Pedestrian crossing:**
Simple simulation of a pedestrian crossing. When the button is pressed at the traffic lights, a sequence of green lights for pedestrians is activated and then the green lights for drivers are switched back on.  The second switch (located outside the image) turns on night mode.

<br>
<div align="center">
  <p>
    <img src="pedestrian_crossing/pedestrian_crossing.png"/>
  </p>
</div>

5. **Multi-band voltmeter:**
Built with the help of voltage dividers. Allows to safely measure the applied voltage in the range of 0-50V (avoiding burning the Arduino board). May require some time to automatically tune the system to measure voltage more precisely.

<br>
<div align="center">
  <p>
    <img src="voltmeter/voltmeter.png"/>
  </p>
</div>

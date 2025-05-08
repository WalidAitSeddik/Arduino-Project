In this folder, you will find all the tests we performed during our project development. We began by testing each component individually, then gradually grouped and integrated them into two distinct sets.

The first group includes the motion sensor, buzzer, and LEDs — used to detect activity and provide visual and sound feedback.

The second group consists of the 4x4 matrix keypad, LCD, and servo motor, which are used for user interaction and control.

We also attempted to use an RFID module, but it didn’t work due to a defective component.

The final integrated code is saved under the name “Test final”.

   Description of the project:

Design and implementation, in a team of two, of an interactive security system based on the Arduino Mega 2560. The system integrates a motion sensor, 4x4 keypad, 16x2 LCD, buzzer, servo motor, and dynamic power management.

Features:
Motion detection using a PIR sensor that immediately triggers a buzzer alarm.

The LCD screen (16x2) activates only when motion is detected, prompting the user for input.

Secure 4-digit password entry via a 4x4 matrix keypad, with masked visual feedback (***).

If the password is correct: the screen displays "Welcome home", the SG90 servo motor rotates 90° for 5 seconds to simulate a garage door opening, and a green LED turns on.

If the password is incorrect: the message "Incorrect code, please try again" is displayed.

The LCD automatically turns off 2 seconds after password validation.

Complete wiring diagram created using Cirkit Designer.

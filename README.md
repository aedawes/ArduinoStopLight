# Lab 2 - Wifi Controlled Stop Light (Arduino)
### Anais Dawes

This lab’s main focus is to learn how to use the GPIO pins on an Arduino D1 mini (generation 3) in order to run a web server that allows us to control a stoplight.  This lab consists of a stoplight prototype using LEDs and a breadboard to demonstrate the functionality.  The arduino uses wifi in order to communicate with a web page.  Clicking any of the particular colours on the stoplight image on the web page will illuminate the corresponding LED.  Clicking the cycle button, will cause the LEDs to cycle colours, like a real stoplight, and clicking the off button will cause all LEDs to turn off, regardless of the current state.

## Requirements
- Use a Arduino and it’s GPIO pins
- Use a breadboard, LEDs (red, green, yellow), resistors, and wires to create the circuit
- Connect to a webpage via wifi to control the stoplight remotely
- When one of the lights on webpage is pressed, the corresponding LED on the breadboard lights up
- When the cycle button on webpage is pressed, the LEDs rotate which one is lit (red, yellow, green, and back to red)
- Reasonable time interval for each LED in the cycle is used
- When the off button on webpage is pressed, any illuminated LED or current cycle mode is stopped and the machine is in the off state


## State machine
The state machine (Figure 1)  is a visual representation of the states of the stoplight and the input needed to take it from one state to another.  We start in the “start” state and once started, it moves into the off position, regardless of any input.  From the off state, it can move into any other state, and back to off, depending on the input.  For example, if the machine is in the off state and the input ‘red’ is given, the state will change to be in the ‘red’ state.  This will continue for theoretically forever as there is no end unless power is removed.  Once in a state, each state can be given the input of another colour or the input of ‘cycle’.  If ‘cycle’ is given, the cycle boolean is set to true and the state will be set to green.  Then, the machine will rotate to each colour every 2 seconds until another input is given.

<img width="633" alt="Screen Shot 2022-10-07 at 4 26 52 PM" src="https://user-images.githubusercontent.com/59840208/194671044-be3cedc2-6faf-4e15-a877-b35e6784453d.png">
Figure 1


## System View

The user facing interface for this system is a webpage served by an arduino in java.  HTML and CSS is injected at the end of the file. This website has a traffic light interface that the user can interact with (figure 2).  This interface includes an image of a stoplight with three coloured buttons corresponding with the lights on a traffic light, an “Off” button, and a “Cycle” button.  

When the user presses one of the lights on the traffic light image, the corresponding colour will show up on the connected LEDs through the Arduino’s GPIO pins, to the breadboard.  When the “Off” button is pressed, any light that was previously set to on, is set to an off state. When the “Cycle” button is pressed, the lights will, starting at green, cycle through the different lights at 2 second intervals.  If the “Off” button is pressed in this mode, the cycle will stop.


<img width="470" alt="Screen Shot 2022-10-07 at 4 27 02 PM" src="https://user-images.githubusercontent.com/59840208/194671104-0fb5bbdb-6358-4116-820e-8bc93bd7a76f.png">
Figure 2

## Component View
There are three main components to this lab.  The first is the computer and web browser from which the Arduino is connected to in order to control the circuit (more details mentioned in the System View section).  

The second is the Arduino (D1 Mini generation 3).  By plugging the Arduino to a computer with the Arduino IDE installed, the Arduino was configured to perform the functionality of the flashlight and host the web server. 

The third component is the breadboard.  This is what is implementing the circuits (Figure 4), allowing power to flow through to the LED’s to light them up when requested.  Figure 3 clearly shows the different parts of the breadboard circuits.  The first thing to note is the ground wire.  This wire provides power from the Arduino to the breadboard.  The next part of this component  is the other three cords connecting from the Arduino to the breadboard.  These are hooked up to pins D0, D5, and D6.  They are providing the electrical input to the board and the specific pins will allow for the programming of each individual circuit.  Then we have the LED lights corresponding with the correct colors of the stoplight.  These then connect to resistors which reduce the flow of electrical current.  The resistors are added so that the LEDs don’t receive too much current at once and short out.

<img width="623" alt="Screen Shot 2022-10-07 at 4 27 13 PM" src="https://user-images.githubusercontent.com/59840208/194671144-5c8eafc3-0e3d-4ab3-836e-cba8b2103d49.png">
Figure 3

<img width="352" alt="Screen Shot 2022-10-07 at 4 27 19 PM" src="https://user-images.githubusercontent.com/59840208/194671180-1916e8a8-c201-474c-a0f2-f9dd1f1d60f7.png">
Figure 4: note battery is in actuality, the arduino

Unlike what would be done with a raspberry pi, all of the functionality on the Arduino is done in one file. It begins by setting up the wifi connection, with variables that would change depending on what internet you are trying to connect to.  It then initializes the pins by setting the mode to output on all three pins and then setting all the pins to low.  The program then sets up the web server that will listen for different requests.  Then there is a loop where when a new request is given. These requests are outlined in the state diagram (figure 1).  The loop will continuously loop forever, listening for different requests.  

The most complicated request is the cycle request.  This will set a boolean to true, and if true, the beginning of the loop will use millis() to loop through the lights.  The reason millis() is used, is because it is non-blocking code.  This means that the code, unlike delay(), will not stop the entire program, waiting for the next input.  It simply checks the amount of time since the last LED was on.  This allows us to be able to give the “off” input during any point in the cycle.

 

## Thought Questions

1. What are some key differences between developing this lab on a Raspberry Pi, and developing on Arduino?
- One of the main difference was the language and the file set up.  On the raspberry pi, I had to set up a whole project and install lots of things on both devices.  I then had to send everything to the raspberry pi using ssh to avoid using nano to code.  On the Arduino, all I needed to do was install the IDE and plug it straight into the computer.
2. What are the strengths and trade-offs of each of these platforms?
- Raspberry pi’s main advantage is threading.  Since the Arduino is a microprocessor, so it doesn’t support multithreading.  This means on Arduino, we can’t use the clean delay() function.  The Arduino is much easier to set up and everything being in one file and modifiable from a laptop, make it faster to get started.
3. How familiar were you with the Arduino platform prior to this lab?
- I had no experience with Arduino.
4. What was the biggest challenge you overcame in this lab?
- I tried many different ways to implement millis().  I feel like millis() didn’t have a whole lot of good documentation.
5. Please estimate the total time you spent on this lab and report.
- 6 to 7 hours


## References:

Example of similar project: 
https://github.com/todddb/example-lab

Setting up a web server:
http://www.esp8266learning.com/wemos-webserver-example.php

Help with understanding millis(): Steve Palica, IT&C undergraduate student

Help with debugging my code and millis(): Berin Hamilton (Ellsworth), IT&C undergraduate student

## Appendix:

Link to online lab: https://github.com/aedawes/ArduinoStopLight

GPIO pins: 
https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

<img width="652" alt="Screen Shot 2022-10-07 at 4 27 27 PM" src="https://user-images.githubusercontent.com/59840208/194671376-f9cf8e99-2e3c-4b3d-ba77-f1934f64f25d.png">

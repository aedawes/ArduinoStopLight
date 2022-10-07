# Lab 3 - Vehicle Sensor
### Anaïs Dawes

This lab's main focus is to learn how to configure two different Wemos D1 Mini Arduino boards to talk to each other through wifi and a web server.  In this lab, one arduino is connected to a circuit of leds to create a mock stop light.  This arduino will host a web server as the “server” of the system.  The second arduino is connected to a HC-SR04 distance sensor.  This arduino will send information to the server as the “client” of the system.  The distance sensor will send a request to the server based on what distance an object is away from the distance sensor.

## Requirements
- Use two Arduino Wemos D1 Mini’s
- Use a breadboard, LEDs (red, green, yellow), and resistors to create one of the circuits
- Use a breadboard and a distance sensor to create the other circuit
- Host a web server on one of the arduino’s (server)
- Use the other arduino (client) to send requests to the server arduino
- When the distance sensor senses something very close, the red light flashes
- When the distance sensor senses something close, the red light turns on
- When the distance sensor senses something at a medium distance, the yellow light turns on
- When the distance sensor senses something at a larger distance, the green light turns on
- When the distance to sensor exceeds a large reasonable distance, any illuminated LED or current blink mode is stopped and the machine is in the off state
- Reasonable time interval for each flash in the blink mode is used

## State machine
The state machine (Figure 1)  is a visual representation of the states of the stoplight and the input from the sensor needed to take it from one state to another.  We start in the “start” state and once started, it moves into the off position, regardless of any input.  From the off state, it can move into any other state, and back to off, depending on the input.  For example, if the machine is in the off state and the distance sensor senses something between 10 cm away and 20 cm away, the state will change to be in the “RED” state.  This state machine will continue for theoretically forever as there is no end unless power is removed.

<img width="978" alt="Screen Shot 2022-10-07 at 2 47 34 PM" src="https://user-images.githubusercontent.com/59840208/194670399-62b78873-65c7-47a8-8463-b90eb7df5eca.png">
Figure 1



## System View

The user facing interface for this system is a physical stoplight (Figure 2) that is visible to the user and a distance sensor (Figure 3) to interact with.  The user will be able to move an object at varying distances from the sensor and be able to witness different colours of lights that will indicate how far away that object is.

![IMG_0026](https://user-images.githubusercontent.com/59840208/194670415-820b5490-9420-475a-9114-f2a6bc9e13b6.jpeg)
Figure 2

![IMG_0025](https://user-images.githubusercontent.com/59840208/194670440-8b35ef30-f16e-4bbe-b075-65d830d11eaf.jpeg)
Figure 3

## Component View
There are two main components for this lab.  The first component is the circuit for the stoplight (Figures 4 and 5) and the second is the circuit for the distance sensor (Figures 6 and 7).  Both of the main components use a breadboard and wires to complete the circuits.

The circuit for the stoplight has a few parts.  The main driver of the whole system is the Wemos arduino D1 mini.  This is programmed via computer to run the server and to define the routes connected to each GPIO pin.  Once programmed the arduino only needs to be provided power and it will use wifi to communicate.  There are also some LED lights (red, yellow, and green) that indicate the different distances from the sensor.  The red LED is connected to pin D6, the yellow LED is connected to pin D5, and the green is connected to pin D0.  There are also resistors that are provided so that the LEDs do not blow from too much voltage.  These are connected to the ground wire, connected to the ground pin. Lastly, we have the power source which is connected to the arduino through a micro usb cable.

![IMG_0024](https://user-images.githubusercontent.com/59840208/194670500-f54c8c80-3a23-429c-b48c-888c636b7f8b.jpeg)
Figure 4						

<img width="454" alt="Screen Shot 2022-10-07 at 1 35 12 PM" src="https://user-images.githubusercontent.com/59840208/194670512-38c3fb74-ba52-4acb-86f0-c8aa42023f0f.png">
Figure 5


The circuit for the sensor also has a few parts.  Like the stoplight, a Wemos arduino D1 mini is also programmed.  This arduino is programmed to read in data from the sensor and send it to the server based on the output of that sensor.  The other part of this circuit is the sensor (HC-SR04) itself.  The sensor will read in data from sending a signal and reading the echo of the sensor.  The last part is a power source which connects to the arduino through a micro usb cable.

![IMG_0023](https://user-images.githubusercontent.com/59840208/194670523-3db6dcef-d264-4e30-a762-748dc5178a82.jpeg)
Figure 6							

<img width="197" alt="Screen Shot 2022-10-07 at 1 43 31 PM" src="https://user-images.githubusercontent.com/59840208/194670529-bc2098a9-8502-4e4a-b6fd-035db2c5efb1.png">
Figure 7


For this lab, two files were used, one for each arduino.  The file for the light system was titled “DistanceSensor_Light” and the file for the sensor was titled “DistanceSensor_Sensor”.  Since the two files communicate through the server created by the boards, the two files do not need to directly talk to each other or be located in the same location.

The light system file begins by setting up the wifi connection, with variables that would change depending on what internet you are trying to connect to.  It then initializes the pins by setting the mode to output on all three pins and then setting all the pins to low.  It then attempts to connect to wifi through the ssid and the password provided.  It will provide different outputs to the serial monitor based on the status of the connection.  In the loop, it begins by checking if the boolean used to check if the light should be blinking is true.  If so, we run non-blocking code using millis() to turn the light on and off every 100 milliseconds.  Millis() works by checking to see when the last time the light was on and comparing it to preset values.  It is updated each loop which allows us to blink the light without using delay.  If we were to use delay, the entire program would freeze until the delay ends, which would not allow any other input to be given.  The code then starts the server and listens for requests.  “request.indexOf()” is used to check the parameters given to the server’s url and run code accordingly.  If the URL has “/RED” on the end, red will turn on and all other lights turn off.  This is the same for all of the other states.

The sensor system has four different wires.  The Vcc pin is connected to the 5v pin, the ground wire is connected to the ground pin, the echo pin is connected to the D2 pin, and the trigger pin is connected to the D1 pin.  The program starts by setting the pin modes according to what needs to be done for the sensor.  The trigger pin needs to output a signal and the echo pin needs to read the input of that signal.  The program then tried to connect to the internet and provides messages depending on the status.  The loop begins by reading the sensor.  First, the trigger pin is cleared.  It is then set to high for 10 microseconds and then sets it to low.  Once that occurs, the echo pin is set to high and the reading from the echo and the speed of sound is used to determine the distance in cm that the object is away from the sensor.  The program then checks what state to put the light in depending on that distance.  It then sends that state from the client to the server to determine what state it must enter in.

## Thought Questions

1. Think of the interaction between your devices. How well would this scale to multiple devices? Is it easy to add another sensor? Another actuator?
- It would be relatively easy to add another sensor.  It would just need to be configured like the distance sensor in this project to be able to send information from the sensor to the server to control the actuator.  
- It would be relatively easy to add another actuator as well.  The sensor would just need to ensure that it send the required information to both sensors or the correct sensor.
2. What are strengths and weaknesses of the tennis-ball-on-a-string system that Don had originally? What are strengths and weaknesses of the IoT system that he developed? What enhancements would you suggest?
- The tennis ball on the string is a simple solution that works fairly well and requires no power.  It can, however, break often, and be a bit of an eyesore in the garage.  The driver would also need to specifically be looking at the ball while pulling in where it may be better to view all surroundings when entering the garage, especially with kids around.
- The stop light allows the driver to see a clear and accurate indicator of how far in the garage they are.  Since it is a light system, the need to focus straight at the light would have diminished.  However, the system don created has a few flaws.  Firstly, the system is currently on a breadboard.  Connecting this to larger LEDs would be far more practical.  Second, the system may not particularly sense the car.  Whilst testing, any object that gets in the way can mess it up, whether that be a bug or something else placed in the garage interfering.  It may be better to hook the system directly to the car to be turned on when needed so that the driver can ensure it is the car that is reading the sensors.
3. What was the biggest challenge you overcame in this lab?
- The hardest part was figuring out how to get the specific requests I needed sent to the server.  It took a sleep and a bit of thinking during the next day to piece together the solution that ultimately worked.  
4. Please estimate the total time you spent on this lab and report.
- 6 to 7 hours

## References:

Hooking up a ultrasonic sensor to arduino:
https://microdigisoft.com/esp8266-wemos-d1-mini-with-hc-sr04-ultrasonic-sensor/

How to set up client http get requests:
https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/

How to send custom requests to server from client:
https://www.youtube.com/watch?v=gZhUi24_qms


## Appendix:

Link to online lab: https://github.com/aedawes/raspStopLight

GPIO pins: 
https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/




# RoboCup Junior Crestwood Lions
Robot programmed by the Crestwood Lions software team: Daniel Markusson, Kyle Andersen, and Jacky Zhang. <br> <br>
Robot designed by the Crestwood Lions hardware team: Hayden Patience, Tristan Samarasekera, and Jayson Sone.

## Table of Contents
1. Introduction
2. Documentation
   * Components
     * Shift Register
     * Color Sensor
     * Compass
     * Motors
   * Strategy
     * Master flowchart
   * Designs and models
     * PCB designs
     * 3D models
3. Lessons and Takeaways
4. Conclusion

## Introduction
The point of this information is to provide future RoboCup participants with the knowledge and information we have, so that they are able to improve upon our work and create something better. We did not have any of
this information when we began, and I'm sure we'd all agree that our lives would have been a lot easier if someone else had shared their process with us. 
<br> <br>
RoboCup is an international robotics tournament held in Europe every year. More information can be found here: https://www.robocup.org/. The tournament we participated in this year was RoboCup Junior Lightweight. 

## Documentation

## 1. Components

### Shift Register
#### Description
The shift register class is a class for the daisy-chained shift registers used within the robot for the IR sensors. Their job is to turn the 16 readings of the IR sensors into just three pins (seen in the constructor). The shift registers output the bits of info through an info bus, enabling the microcontroller to read the bits one-by-one.
<br> <br>
We did not end up using this class because of a hardware oversight. Not realizing that the IR sensors output analog values rather than digital, we forgot to impliment analog-to-digital converters on the outputs, which made the outputted readings of the shift-registers garbage. It is still a great piece of code that should be made into a library.
#### Public:
##### Methods:
* `readchips(int numOfChips, int sizeOfChips)`: Reads the values stored in a set of daisy-chained shift registers.
* `Shift_Register(int ioSelect_, int clockPulse_, int dataPin_)`: Constructor for the `Shift_Register` class.
  * Parameters:
    * `ioSelect_`: The pin which will tell the shift register whether to accept input or produce output.
    * `clockPulse_`: The clock pin.
    * `dataPin_`: The data-bus pin.
* `int** readChips(int numOfChips, int sizeOfChips)`: reads the values stored in a set of daisy-chained shift registers.
  * Parameters:
    * `numOfChips`: The number of chips daisy-chained.
    * `sizeOfChips`: The size of the chips.
  * Returns: A 2D integer array with dimentions [`numOfChips` x `sizeOfChips`] where each value is a value once stored on the corresponding chips address.
* `void printChips(int secondsDelay)`: Nicely formats and prints the 2D array read in the daisy-chained shift registers.
  * Parameters:
    * `secondsDelay`: Number of miliseconds to delay in-between print statements.
#### Private:
##### Variables:
* `const int CHIPSIZE`: Number of bits of data that the chip can manage. Always equal to 8.
* `const int NUM_CHIPS`: Number of chips that are daisy-chained together. In our use-case, it is 2.
* `int dataPin`: The pin on which data is travelling.
* `int ioSelect`: The pin which will tell the shift register whether to accept input or produce output.
##### Methods:
* `void ioType(int io_type)`: Sets the chip to accept parallel or serial input.
* `void clkPulse()`: Pulses the clock. Writes the clock pin to low then high, once, in rapid succession.
* `int* readChip(int sizeOfChips)`: Reads all 8 bits of the serial output of a shift register.
  * Parameters:
    * `sizeOfChips`: The size of the chips being read.
  * Returns: Integer array of size `CHIPSIZE` where each int is a respective chip bit.
* `void chipParallelIn()`: Shifts in parallel data to the shift register.

### IR Sensors
#### Description
The IR sensors are in charge of telling the robot where the ball is. It can also, somewhat primatively, tell the robot how far away the ball is as well. This is done by seeing how many pins view the ball - if more pins see the ball, it is likely the ball is farther. On our robot, there are 16 pins. Originally, we were going to use shift registers to make it easier to read all 16 pieces of data. However, due to a hardware oversight, we were no longer able to use them. We ended up just hardwiring the IR sensors directly to the Teensy, costly using 16 analog pins. This caused further complications down the line, which are elaborated on in the lessons and takeaways section.
#### Public:
##### Methods

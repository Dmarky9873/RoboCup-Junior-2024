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
* `readchips(int numOfChips, int sizeOfChips)`: reads the values stored in a set of daisy-chained shift registers.
* `Shift_Register(int ioSelect_, int clockPulse_, int dataPin_)`: Constructor for the `Shift_Register` class.
  * Parameters:
    * `ioSelect_`: the pin which will tell the shift register whether to accept input or produce output.
    * `clockPulse_`: the clock pin.
    * `dataPin_`: the data-bus pin.
  * Returns: `void`
* `int** readChips(int numOfChips, int sizeOfChips)`: reads the values stored in a set of daisy-chained shift registers.
  * `numOfChips`: the number of chips daisy-chained.
  * `sizeOfChips`: the size of the chips.
* Returns: a 2D integer array with dimentions [`numOfChips` x `sizeOfChips`] where each value is a value once stored on the corresponding chips address.
#### Private:
##### Variables:
* `const int CHIPSIZE`: Number of bits of data that the chip can manage. Always equal to 8.
* `const int NUM_CHIPS`: Number of chips that are daisy-chained together. In our use-case, it is 2.
* `void ioType(int io_type)`: Sets the chip to accept parallel or serial input.

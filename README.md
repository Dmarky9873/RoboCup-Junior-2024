# RoboCup Junior Crestwood Lions
Robot programmed by the Crestwood Lions software team: Daniel Markusson, Kyle Andersen, and Jacky Zhang. <br> <br>
Robot designed by the Crestwood Lions hardware team: Hayden Patience, Tristan Samarasekera, and Jayson Sone.

## Table of Contents
1. Introduction
2. Documentation
   * Components
     * Color Sensor
     * Compass
     * Motors
     * Shift Register
   * Strategy
     * Master flowchart
   * Designs and models
     * PCB designs
     * 3D models
3. Lessons and takeaways
4. Conclusion

## Introduction
The point of this information is to provide future RoboCup participants with the knowledge and information we have, so that they are able to improve upon our work and create something better. We did not have any of
this information when we began, and I'm sure we'd all agree that our lives would have been a lot easier if someone else had shared their process with us. 
<br> <br>
RoboCup is an international robotics tournament held in Europe every year. More information can be found here: https://www.robocup.org/. The tournament we participated in this year was RoboCup Junior Lightweight. 

## Documentation

## 1. Components
### Components Superclass
#### Description
The components class is a parent class for every component. Every component has shared features (multiple pins, a name, etc.), and this parent class condenses them all into a single constructor for ease of use.
#### Public:
* `setUp`: Initializes each pin in `pin_numbers[]` to their respective mode in `modes[]`. No returns or params. 
* `getPinMode(uint8_t pin)`: Gets the pinMode of param `pin`. Returns `INPUT`, `OUTPUT`, or `UNKNOWN_PIN`.
* `Component(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name)`: Constructor, sets private variables to params.



![Static Badge](https://img.shields.io/badge/Notice-README%20under%20construction-darkred)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)


# Robot Arm

A cheap and opensource desktop robot arm powered by Arduino

![Arm Gif](https://via.placeholder.com/468x300?textScreenshot+Here)
## Features

#### Arm
- Fully 3D printed body
- Low-cost design
- Easy repairability
- Repeatable and easy-to-program routines
- Control over serial from any device
    - Allows for easy integration with custom-made software
![Arm Picture](https://via.placeholder.com/234x150?textScreenshot+Here)

#### App
- Live preview of the arm's position
- Full control of the arm's movement
    - Follow mouse mode
        - The end effector of the arm will follow the mouse on the screen
    - Fine control mode
        - Move the arm in 1-step increments using a keyboard 
![App Screenshot](https://via.placeholder.com/234x150?textScreenshot+Here)

## Manual Control
Manual commands can be sent directly to the Arduino using the serial tool.

It is possible (and probably easy) to send the commands using serial tools other than the Arduino IDE, but I haven't gotten to it.

| Axis Name | Identifier | Usage |
| - | - | - |
| Base | A | A180 |
| First arm segment | B | B90 |
| Second arm segment | C | C90 |
| Claw open/close | D | D85 (open) | D150 (closed)
| Claw joint | E | E90 |


## Routines

| Routine Name | Identifier | Usage |
| - | - | - |
| Vertical | `1` | 1 | ![Routine 1 Gif](https://via.placeholder.com/175x112?textScreenshot+Here) |
| 90° Rotation Grab | `2` | 2 | ![Routine 2 Gif](https://via.placeholder.com/175x112?textScreenshot+Here) |


## To-do

#### Arm

- Redesign the entire arm to support larger/higher torque servos

- Determine solution for hot stepper motor shaft melting base slot, resulting in unstable arm

- Add limit switch to base to determine 0 automatically
    - Currently, the base sets the position it is in on startup as 0

#### App

- Update control software to support the new arm code

- Add the ability to save the current position as movement points for a routine

- Add the ability to select end effectors (claw, pen holder, etc.)

#### Other

- Create a web app for simulation and programming without the physical arm
    - *Kinda need to learn how to do that first though*

- Add tutorial on how to upload code to Arduino

- Create step-by-step assembly guide
## Credits

- Author: [William Heald | @greendino2000](https://www.github.com/greendino2000)
- Contributor: Valerie Umipig


## Contact

If you have any feedback or questions, please reach out to me at greendino30ba@gmail.com


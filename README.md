
![Static Badge](https://img.shields.io/badge/Notice-README%20under%20construction-darkred)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)


# Robot Arm

A cheap and opensource desktop robot arm powered by Arduino

<img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/cf5ad78f-866d-47a4-8f6b-780c5da2424f" width=500>

## Features

#### Arm
- Fully 3D printed body
- Low-cost design
- Easy repairability
- Repeatable and easy-to-program routines
- Control over serial from any device
    - Allows for easy integration with custom-made software

<img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/edf8ef5c-4da6-47d9-b294-9b9e96f8d6a5" width=400>

#### App
- Live preview of the arm's position
- Full control of the arm's movement
    - Follow mouse mode
        - The end effector of the arm will follow the mouse on the screen
    - Fine control mode
        - Move the arm in 1-step increments using a keyboard

![App Screenshot](https://via.placeholder.com/400x220?textScreenshot+Here)

## Control Methods

###$ Manual Control
Manual commands can be sent directly to the Arduino using the serial tool.

It is possible (and probably easy) to send the commands using serial tools other than the Arduino IDE, but I haven't gotten to it.

| Axis Name | Identifier | Usage (Identifier + Angle) |
| - | - | - |
| Base | `A` | A180 |
| First arm segment | `B` | B90 |
| Second arm segment | `C` | C90 |
| Claw open/close | `D` | D85 (open) / D150 (closed)* |
| Claw joint | `E` | E90 |

*It is important not to go outside the range provided for the claw, otherwise, it will break the servo

### Routines

| Routine Name | Identifier | Usage |  |
| - | - | - | - |
| Vertical | `1` | 1 | ![Routine 1 Gif](https://via.placeholder.com/112x200?textScreenshot+Here) |
| 90° Rotation Grab | `2` | 2 | ![Routine 2 Gif](https://github.com/greendino2000/Robot-Arm/assets/66684604/00b61e19-4e65-4340-a7a2-31270fb3ba48) |


## Parts list

#### Electronics
| Part | Count |
| - | - |
| [TB6612 Stepper control board](https://www.adafruit.com/product/2448) | `1` |
| [DC barrel jack](https://www.adafruit.com/product/373) | `1` |
| [Servo extension cable](https://www.adafruit.com/product/972) | `3` |
| [Power Switch](https://www.adafruit.com/product/482) | `1` |

| Part | Torque | Count |
| - | - | - |
| [MG996R Servos](https://a.co/d/dw7dRt2) | 12kg/cm | `1` |
| [SG90 Servos](https://a.co/d/6B0u2jD) | 1kg/cm | `1` |
| [Nema 17 Stepper Motor](https://a.co/d/1J1Ycyb) | 13Ncm | `1` |

#### Hardware
| Part | Size | Count |
| - | - | - |
| [Rigid Flange Shaft Coupling](https://a.co/d/5UAfUNy) | 5 mm | `1` |
| [M4 Screw Kit](https://a.co/d/59BZscf) | 4 mm | `1` |
| [M3 Screw Kit](https://a.co/d/ajKkV96) | 3 mm | `1` |
| [M1 Screw Kit](https://a.co/d/dh6dXQ9) | 1 mm | `1` |
| [Servo Horns for MG996R](https://a.co/d/1S2e7fp) | 3 mm | `1` |

#### 3D Printed Parts
| File Name | Infill | Supports | Count |
| - | - | - | - |
| Arm1 | 20% | ❌ | `1` |

#### Other
- 

***Note:** "Count" refers to the number of times the linked product should be purchased. A more specific count for items such as screws and servos will be available with the build guide. The linked items generally come in a larger quanitity than needed.*

*The urls provided link to the actual parts and sites that I purchased and used for this project. These parts can be substituted. This list is being updated as updates are made. I do not make any commission from these links*

## To-do

#### Arm

- ✅ Redesign the entire arm to support larger/higher torque servos.
    - ✅ This will increase the cost significantly, so this will only happen once there is a working version using the affordable micro servos so this project can be viable for people who want to build their own robot arm for less.

- ✅ Determine solution for hot stepper motor shaft melting base slot, resulting in unstable arm.
    - **Solution:** Added flange shaft coupling to stepper motor shaft to better secure the arm to the base and disperse heat.

- Add limit switch to base to determine 0 automatically.
    - Currently, the base sets the position it is in on startup as 0.

- ⭐ Remove DC barrel jack from circuit board
    - Replace with a [panel mount](https://www.adafruit.com/product/610) design that will run wires to a header

- Add a usb keystone to the electronics box
    - Determine if a USB-A to USB-B keystone would work

#### App

- Update control software to support the new arm code.

- Add the ability to save the current position as movement points for a routine.

- Add the ability to select end effectors (claw, pen holder, etc.)

#### Other

- Create a web app for simulation and programming without the physical arm
    - *Kinda need to learn how to do that first though*

- Add tutorial on how to upload code to Arduino

- Create step-by-step assembly guide

## Faq

**Q:** Why are their such complicated notes for the parts list?

**A:** I have found that parts lists for open source electronics projects tend to be confusing with what parts to order.

---

**Q:** I'm having a hard time building this for myself. Can I reach out for help?

**A:** For sure! Send me an email and I'll be happy to guide you through building and operating your new robot arm.

---

**Q:** Where is the part list for the arm design that uses only micro servos?

**A:** The part list for the initial design that only used micro servos will be avalible once I finish the build guide for that specific version.

---


## Credits

- Author: [William Heald | @greendino2000](https://www.github.com/greendino2000)


## Contact

If you have any feedback or questions, please reach out to me at greendino30ba@gmail.com

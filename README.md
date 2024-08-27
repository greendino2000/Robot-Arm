
![Static Badge](https://img.shields.io/badge/Notice-README%20under%20construction-darkred)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)


# Robot Arm

An affordable and opensource 4 DoF desktop robot arm powered by Arduino

<img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/cf5ad78f-866d-47a4-8f6b-780c5da2424f" width=500>

## Features

#### Arm
- Fully 3D printed body
- Low-cost design
- Easy repairability
- Built-in and easy-to-program routines
- Controllable over serial from any device
    - Allows for easy integration with custom-made software

<img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/edf8ef5c-4da6-47d9-b294-9b9e96f8d6a5" width=400>

#### Web UI ([Link](https://armcontrol.greendino.dev/))
- Interactive terminal
- Full control of the arm's movement
    - Individual control of each motor and servo
        - Slider control & Text boxes
    - Direct serial control through terminal
        - Reference "Manual Control"
- Added routine functionality
    - Easy programming of routines
    - Integrated execution of routines without the need to hardcode the routines to the Arduino
    - Intelligent file parsing for quick routine sharing between users and devices

<img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/b7a35cfb-fb3b-4f82-a40e-00e8e1d0145d" width=400>
<img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/a22e23fb-ed8e-4eec-9e71-2d165f0288f1" width=400>


## Control Methods

### Manual Control
Manual commands can be sent directly to the Arduino using the serial tool.

It is possible (and probably easy) to send the commands using serial tools other than the Arduino IDE, but I haven't gotten to it.

| Axis Name | Identifier | Usage (Identifier + Angle) |
| - | - | - |
| Base | `A` | A180 |
| First arm segment | `B` | B90 |
| Second arm segment | `C` | C90 |
| Claw open/close | `D` | D85 (open) / D150 (closed)* |
| Claw joint | `E` | E90 |

**It is important not to go outside the range provided for the claw, otherwise, it will break the servo.*

### Routines
*The following routines come built-in with the arm's firmware.*

| Routine Name | Identifier | Usage |  |
| - | - | - | - |
| Vertical | `1` | 1 | ![Routine 1 Gif](https://via.placeholder.com/112x200?textScreenshot+Here) |
| 90° Rotation Grab | `2` | 2 | ![Routine 2 Gif](https://github.com/greendino2000/Robot-Arm/assets/66684604/00b61e19-4e65-4340-a7a2-31270fb3ba48) |


## BOM

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
| BaseSwivel | 75% | ❌ | `1` |
| Base | 20% | ❌ | `1` |
| SmallServoBigHornArmSegment | 20% | ❌ | `1` |
| BigServoArmSegment | 20% | ❌ | `1` |
| ClawJoint | 20% | ❌ | `1` |
| Electronics Enclosure Top | 40% | ❌ | `1` |
| Electronics Enclosure Shell | 20% | ❌ | `1` |

***Note:** "Count" refers to the number of times the linked product should be purchased. A more specific count for items such as screws and servos will be available with the build guide. The linked items generally come in a larger quanitity than needed.*

*The URLs provided link to the actual parts and sites that I purchased and used for this project. These parts can be substituted. This list is being updated as updates are made. I do not make any commission from these links*

## To-do

#### Arm

- Add limit switch to base to determine 0 automatically.
    - Currently, the base sets the position it is in on startup as 0.

#### Other

- Add tutorial on how to upload code to Arduino

- Create step-by-step assembly guide

- Update BOM

- Upload photos of newest iteration of robot arm

<details>
<summary>Archived</summary>
<br>

#### Arm

- ✅ Redesign the entire arm to support larger/higher torque servos.
    - ✅ This will increase the cost, so this will only happen once there is a working version using the affordable micro servos so this project can be viable for people who want to build their own robot arm for less.
 
      <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/43cfa616-a986-43a0-8ce7-554302d3333c" width=150>

- ✅ Determine solution for hot stepper motor shaft melting base slot, resulting in unstable arm.
    - **Solution:** Added flange shaft coupling to stepper motor shaft to better secure the arm to the base and disperse heat. Need to lower the stepper motor into the electronics box to compensate for the height of the coupler.
 
      <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/b596bd3f-3f4f-418d-9285-0e5348124355" width=300>

- ✅⭐ Remove the DC barrel jack from the circuit board
    - Replace with a [panel mount](https://www.adafruit.com/product/610) design that will run wires to a header
      
      <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/f8aae525-f117-4124-9e52-ffe8943bdb7e" width=300>

- ✅ Add a USB keystone to the electronics box
    - Determine if a USB-A to USB-B keystone would work
 
      <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/1029b9ce-0152-43fd-ab4a-a3bbf9b743d6" width=300>

#### App

- ✅ Update control software to support the new arm code.

- ✅ Add the ability to save the current position as movement points for a routine.

- ✅ Add the ability to select end effectors (claw, pen holder, etc.)

#### Other

- ✅ Create a web app for simulation and programming without the physical arm
    - *Kinda need to learn how to do that first though*

</details>

## Gallery
<details>
<summary>V0</summary>
<br>
</details>
<details>
<summary>V1</summary>
<br>
    <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/cf5ad78f-866d-47a4-8f6b-780c5da2424f" width=300>
</details>
<details>
<summary>V2</summary>
<br>
    <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/be18a873-1ef0-44f0-b762-fdaeb0d8fe2e" width=300>
</details>
<details>
<summary>Presentation</summary>
<br>
    <img src="https://github.com/greendino2000/Robot-Arm/assets/66684604/3c4ca209-e576-481d-b856-9d7dd63e911e" width=800>
</details>

## FAQ

**Q:** I'm having a hard time building this for myself. Can I reach out for help?

**A:** For sure! Send me an email and I'll be happy to guide you through building and operating your new robot arm.

---

**Q:** Where is the part list for the arm design that uses only micro servos?

**A:** The part list for the initial design that only used micro servos will be available once I finish the build guide for that specific version.

---


## Credits

- Author: [William Heald | @greendino2000](https://www.github.com/greendino2000)


## Contact

If you have any feedback or questions, please reach out to me at greendino30ba@gmail.com

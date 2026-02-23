# Night Owl: Servo-Controlled Blue Boot

This project features an interactive "Night Owl" gesture using a servo motor and a Light Dependent Resistor (LDR). A **blue boot** is attached to the servo, acting as the owl's foot. The object mimics the behavior of a night owl: energetic and active in the darkness, but slowing down and eventually "sleeping" when exposed to light.

## Features

- **Night Owl Logic:** The object is most active during the night. The darker it is, the more energetically the blue boot moves.
- **Light Sensitivity:** As soon as light is introduced, the movement slows down immediately.
- **Daytime Sleep:** If light is consistently introduced for a period of time, the object stops moving entirely and enters its "sleep" state.
- **Awakening:** When darkness returns, the blue boot starts moving slowly and gradually gains speed as it gets darker, just like an owl waking up for the night.

## Project Assets

![Project Photo](assets/project_photo.jpg)

### Video Demo

[Watch the project video](assets/project_video.mov)

## Hardware List

- **Microcontroller:** Arduino Uno, Nano, or compatible board.
- **Actuator:** SG90 Micro Servo (or standard 5V servo).
- **Sensor:** Light Dependent Resistor (LDR) / Photoresistor.
- **Resistor:** 10kΩ Resistor (for the LDR voltage divider circuit).
- **Miscellaneous:** Breadboard and jumper wires.

## Wiring / Pinout

| Component | Pin on Arduino | Notes |
| :--- | :--- | :--- |
| **LDR Output** | `A0` | Connect in a voltage divider configuration with the 10kΩ resistor. |
| **Servo Signal** | `D9` | PWM capable pin. |
| **Servo VCC** | `5V` | |
| **Servo GND** | `GND` | |

**Note:** For the LDR circuit, connect one leg of the LDR to 5V. Connect the other leg to both Pin A0 and one leg of the 10kΩ resistor. Connect the other leg of the 10kΩ resistor to GND.

## Installation & Usage

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Dafu-Liu/com-obj-gesture.git
    cd com-obj-gesture
    ```

2.  **Open with PlatformIO:**
    - Open Visual Studio Code.
    - Ensure the PlatformIO extension is installed.
    - Open the project folder.

3.  **Upload:**
    - Connect your Arduino board.
    - Click the "Upload" arrow in the PlatformIO toolbar.

4.  **Monitor:**
    - Open the Serial Monitor (baud rate 9600) to see debug output regarding light levels and states.

# 🤖 Desktop Robot Arm

A compact, fully customizable desktop robot arm designed for small-scale automation tasks. Developed as part of a Bachelor of Engineering in Mechatronics at Technological University Dublin, this project integrates 3D-printed components, servo motor actuation, custom electronics, Arduino-based firmware, Bluetooth control, and an Android app interface.

---

## 📦 Features

- 6 Degrees of Freedom using MG66R and SG90 servo motors  
- Bluetooth-enabled control with HC-05 and MIT App Inventor  
- Android app with presets and direct manual controls  
- Custom PCB with schematics and Gerber files (KiCAD)  
- Modular 3D-printed design with STL files included  
- Smooth servo motion using filtering algorithms  

---

## 📁 Repository Structure

1. **Documentation**  
   - `RobotArm-ProjectReport.pdf` – Full project report with design, testing, and results

2. **Electrical**  
   - `KiCAD-PCB/` – Circuit schematics, custom PCB layout, and Gerber files

3. **Mechanical**  
   - `STL-Files/` – 3D-printable mechanical components  
   - Includes exploded views and CAD drawings

4. **Software**  
   - `Arduino-Firmware/` – Code for ATmega328P (Arduino)  
   - `MIT-App-Inventor/` – Android app `.aia` source and `.apk` installer

---

## 🔧 Hardware Overview

- **Microcontroller:** ATmega328P (Arduino Uno or custom board)  
- **Servos:** 5× MG66R, 1× SG90  
- **Peak Current Draw:** 2.8A (measured)  
- **Bluetooth Module:** HC-05  
- **Build Volume:** 135mm x 90mm footprint  
- **Chassis:** Fully 3D-printed components (PLA)  

---

## 📱 Android App

- Built with **MIT App Inventor**  
- Control individual servo angles or trigger gesture presets:
  - `Home`, `Ready`, `Wave`, `Screwdriver`, `Circles`, `Diagonals`, `Worm`, `Demo`
- Bluetooth communication with Arduino via HC-05  

---

## 📐 Mechanical Design

- All STL files for 3D printing included  
- Exploded views, BOM, and design drawings available  
- Desktop-sized and modular for easy assembly and customization  

---

## 🔌 Electrical Design

- Custom PCB designed in **KiCAD**  
- Includes:
  - Circuit schematics  
  - PCB layout  
  - Gerber files for fabrication  
- Power and signal headers for servos, Bluetooth, and logic  

---

## 🧠 Arduino Firmware Features

- Servo smoothing for fluid movement  
- Bluetooth and Serial input parsing  
- Support for:
  - Comma-delimited angle commands (e.g., `90,90,90,90,90,90*`)
  - Keyword triggers (`Demo`, `Home`, etc.)
  - Real-time smoothing level adjustment (`0#/100#`)  

---

## 🚀 Getting Started

### 🔩 Requirements

- Arduino IDE  
- Android device with Bluetooth  
- 3D printer (recommended material: PLA)  
- 5V power supply (min. 3A)  
- HC-05 Bluetooth module  
- Basic tools for assembly and soldering  

### 🛠️ Setup Instructions

1. **3D Print** all components from the `STL-Files/` folder.  
2. **Assemble** using provided CAD diagrams.  
3. **Upload firmware** from `Arduino-Firmware/` to your ATmega328P.  
4. **Install Android app** from `MIT-App-Inventor/` (`.apk`) or open `.aia` to modify.  
5. **Pair Bluetooth** module and connect via the app.  
6. **Power on** the system and start experimenting!  

---

## 📚 Documentation

📄 Full design details, diagrams, testing results, and methodology can be found in the [Project Report (PDF)](./RobotArm-ProjectReport.pdf).

---

## 🧩 Future Improvements

- Add tactile or force sensors  
- Integrate IoT control (Wi-Fi, MQTT)  
- Implement gesture learning via AI  
- Design swappable gripper attachments  
- Develop an educational kit version  

---

## 📝 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 👤 Author

**Ethan Lawlor**  
B.Eng. Mechatronics  
Technological University Dublin

# 🔒 Smart Home Door Lock System (IoT-Enabled Access Control)

This project implements a robust **Internet of Things (IoT)-enabled smart door lock system** designed to enhance home security, accessibility, and convenience. By integrating physical hardware with cloud services, the system allows for secure, real-time remote control and monitoring.

---

## 💡 Problem and Solution

### Problem Addressed
Traditional door locks present several limitations, including the risk of **unauthorized key duplication**, **inconvenience** when keys are lost or forgotten, and a **lack of remote monitoring or access history logging**.

### Solution
The Smart Door Lock System solves these issues by providing:
* **RFID-based authentication** for local, secure access.
* **Real-Time Remote Control** via a mobile application (Blynk App).
* **Instant Alerts and Notifications** for unauthorized attempts and access events.
* **Data Logging** of all access activities for a comprehensive security history.

---

## ✨ Key Features

* **Dual-Access Control:** Local authentication via **RFID Tag** and remote control via a mobile app.
* **Real-time Monitoring:** View the lock's status and access logs from anywhere using the **Blynk IoT Platform**.
* **Secure Communication:** Utilizes the **MQTT protocol** for reliable and efficient, low-latency data exchange.
* **Physical Actuation:** Uses a **Motor Lock/Solenoid Lock** controlled by a **Relay Module** to physically secure the door.
* **Audio-Visual Feedback:** **Buzzer** and **LED indicator** provide immediate feedback on successful or failed authentication attempts.

---

## 📐 System Architecture

The system is primarily built on the **Three-Layer Architecture** (Perception, Network, and Application Layers):

1.  **Perception Layer:** Sensors (**RFID Reader**) and actuators (**Motor Lock**, **Buzzer**) collect data and perform physical actions.
2.  **Network Layer:** The **ESP8266** microcontroller connects to the internet via Wi-Fi and transmits data securely to the cloud using the **MQTT protocol**.
3.  **Application Layer:** The **Blynk App** provides the user interface for control, monitoring, and receiving notifications.

---

## ⚙️ Hardware and Software Requirements

### Hardware Components
| Component | Purpose |
| :--- | :--- |
| **ESP8266 (NodeMCU)** | Main Microcontroller, connects components, and handles logic. |
| **RFID Reader Module (e.g., RC522)** | Reads and authenticates user RFID tags. |
| **Motor Lock / Solenoid Lock** | The physical locking mechanism. |
| **Relay Module** | Controls the high-power Solenoid Lock using the low-power ESP8266 signal. |
| **RFID Tags** | Unique identifiers for users. |
| **Buzzer and LED** | Provides system status and alert feedback. |

### Software & Platforms
* **Arduino IDE** (or PlatformIO) for writing and uploading the code.
* **Blynk IoT Platform** (App & Cloud) for remote access and data visualization.
* **Libraries:** Necessary libraries for the ESP8266, RFID-RC522, and Blynk connectivity.

---

## 🚀 Getting Started (High-Level Setup)

1.  **Configure Blynk:** Create a project on the Blynk platform and obtain the necessary Authentication Token.
2.  **Wire Components:** Connect the **RFID Reader**, **Relay Module**, **Buzzer**, and **Motor Lock** to the **ESP8266 (NodeMCU)** pins as per the wiring diagram (refer to `schematic.png` if available).
3.  **Code Upload:** Update the provided code with your Wi-Fi credentials and Blynk Authentication Token. Upload the code using the **Arduino IDE**.
4.  **Testing:** Test local access using a registered **RFID Tag** and remote control using the buttons on the **Blynk App** dashboard.

---

## 📈 Future Enhancements

Based on iterative testing and user feedback, potential improvements and future work for this system include:

* **Enhanced Security:** Implement **data encryption** for RFID tag communication and integrate more robust authentication methods (e.g., fingerprint, facial recognition).
* **Battery Backup:** Add a **battery backup** system to ensure the lock remains functional during a power outage.
* **Professional Deployment:** Develop a custom **PCB** (Printed Circuit Board) to replace the breadboard setup, improving system durability, aesthetics, and overall robustness.
* **Advanced Features:** Integrate with voice assistants (like Alexa or Google Assistant) for voice control.

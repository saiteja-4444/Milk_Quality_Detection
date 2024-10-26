<h1 align="center"> 🥛 Milk Quality Detection Using IoT Sensors </h1>

<h2>📝 Project Overview</h2>

This project utilizes IoT sensors to monitor and ensure the quality of milk. By integrating pH sensors, temperature sensors, LDR sensors, a NodeMCU for data processing, and a GSM module for alert messaging, we aim to provide real-time monitoring and alerting systems for milk quality.

## 🧰 Components
- pH Sensor: Measures the acidity or alkalinity of the milk.
- Temperature Sensor: Monitors the temperature of the milk to ensure it stays within safe levels.
- LDR Sensor: Detects the presence of light, which can be used to infer storage conditions.
- NodeMCU: A low-cost open-source IoT platform that collects and processes data from the sensors.
- GSM Module: Sends alert messages when the milk quality parameters exceed acceptable limits.

## 🌟 Features
Real-Time Monitoring: Continuous monitoring of milk quality parameters.
Alert System: Sends SMS alerts through the GSM module when any parameter exceeds the preset threshold.
User-Friendly Interface: Data visualization through dashboards (if applicable).
Low Cost & Efficient: Utilizes cost-effective IoT components to ensure an affordable solution.

## 🛠️ Setup Instructions
### Hardware Setup:

Connect the pH sensor, temperature sensor, and LDR sensor to the NodeMCU.

Connect the GSM module to the NodeMCU for SMS alerts.

### Software Setup:

Install the Arduino IDE and necessary libraries for NodeMCU and sensors.

Upload the code (provided in the repository) to the NodeMCU.

## ⚙️ Configuration:

Set the threshold values for pH, temperature, and light levels in the code.
Configure the GSM module with your SIM card details to enable SMS alerts.

## 🚀 Running the Project:

Power up the NodeMCU and ensure all sensors are functioning correctly.
Monitor the readings and receive alerts if any parameter exceeds the set thresholds.

## 👨‍💻 How to Use
Monitoring: Use the serial monitor in Arduino IDE or a custom-built dashboard to observe the sensor readings in real-time.
Alerts: Receive SMS notifications for any anomalies in milk quality.

## 🤝 Contribution
Feel free to fork this repository, submit pull requests, or raise issues for any bugs or feature requests.

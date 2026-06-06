<div align="center">

# 🌍 Real-Time Disaster Monitoring & Alert System

### IoT + ML — Flood · Fire · Earthquake · Gas Leak · Landslide Detection

![Status](https://img.shields.io/badge/Status-Active-1D9E75?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-ESP32-085041?style=flat-square&logo=espressif&logoColor=white)
![ML](https://img.shields.io/badge/ML-CNN%20·%20LSTM%20·%20XGBoost-3C3489?style=flat-square)
![Alerts](https://img.shields.io/badge/Alerts-SMS%20·%20Email%20·%20Voice-378ADD?style=flat-square)

</div>

---

## 📸 Screenshots

<div align="center">

![Dashboard](Screenshot%202026-06-06%20145732.png)

</div>

<div align="center">

| | |
|---|---|
| ![View 1](Screenshot%202025-10-06%20230940.png) | ![View 2](Screenshot%202025-10-06%20231906.png) |
| ![View 3](Screenshot%202025-10-06%20232406.png) | ![View 4](Screenshot%202025-10-08%20003753.png) |

</div>

<div align="center">

| | |
|---|---|
| ![View 5](Screenshot%202025-10-10%20140620.png) | ![View 6](Screenshot%202025-11-15%20121015.jpg) |
| ![View 7](Screenshot%202025-11-15%20121444.png) | ![View 8](Screenshot%202025-11-15%20121543.png) |

</div>

---

## 🧠 Overview

A full-stack disaster detection system combining **ESP32-based IoT hardware** with **AI/ML predictive models**. The hardware prototype integrates multiple sensors to detect floods, earthquakes, fires, gas leaks, and landslides in real time. Alerts are delivered via **multilingual SMS and email** (English, Hindi, Tamil) through GSM and SMTP.

---

## ⚙️ Sensors

| Sensor | Detects |
|--------|---------|
| Temperature Sensor | Heat anomalies / Fire |
| Gas Sensor | Gas leaks |
| Flame Sensor | Fire |
| Water Level Sensor | Floods |
| Vibration Sensor | Earthquakes |
| Soil Moisture Sensor | Landslides |

---

## 🤖 ML Models

| Model | Purpose |
|-------|---------|
| **CNN** | Image-based disaster classification (>90% accuracy) |
| **LSTM** | Time-series environmental forecasting |
| **XGBoost** | Severity prediction |

GIS-based geospatial risk mapping included for spatial disaster analysis.

---

## 🖥️ Features

- **Real-time sensor monitoring** — live readings from 6 sensors via ESP32
- **Multi-disaster detection** — flood, fire, earthquake, gas leak, landslide
- **Multilingual alerts** — SMS and email in English, Hindi, and Tamil
- **Django web platform** — live dashboard with ML model outputs
- **GIS risk mapping** — geospatial visualization of disaster zones
- **Scalable architecture** — PHP + MySQL backend, TensorFlow/Keras ML stack

---

## 🛠️ Tech Stack

![ESP32](https://img.shields.io/badge/ESP32-085041?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Python](https://img.shields.io/badge/Python-0C447C?style=for-the-badge&logo=python&logoColor=white)
![Django](https://img.shields.io/badge/Django-092E20?style=for-the-badge&logo=django&logoColor=white)
![TensorFlow](https://img.shields.io/badge/TensorFlow-3C3489?style=for-the-badge&logo=tensorflow&logoColor=white)
![Keras](https://img.shields.io/badge/Keras-3C3489?style=for-the-badge&logo=keras&logoColor=white)
![Scikit-learn](https://img.shields.io/badge/Scikit--learn-3C3489?style=for-the-badge&logo=scikitlearn&logoColor=white)
![PHP](https://img.shields.io/badge/PHP-633806?style=for-the-badge&logo=php&logoColor=white)
![MySQL](https://img.shields.io/badge/MySQL-633806?style=for-the-badge&logo=mysql&logoColor=white)

---

## 🏗️ System Architecture

```
ESP32 + Sensors
      │
      ▼ GSM / Wi-Fi
Django Web Platform
      │
      ├── CNN  → Image disaster classification
      ├── LSTM → Time-series forecasting
      ├── XGBoost → Severity prediction
      └── GIS → Geospatial risk mapping
      │
      ▼
SMS · Email Alerts (English · Hindi · Tamil)
```

---

## 👨‍💻 Author

**Sanjay S** — VIT Vellore, M.Tech Software Engineering

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/s-sanjay-contactsanjay)
[![Email](https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:sanjaysureshbabu1@gmail.com)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/sanjay10code)

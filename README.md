#  Industrial-Edge Predictive Maintenance (PdM) System

##  Overview
This project implements a scalable, end-to-end Predictive Maintenance solution designed for industrial rotating machinery. It leverages high-frequency vibration data (NASA Bearing Dataset) to predict Remaining Useful Life (RUL) and detect early-stage mechanical failures.

The system is built with a focus on **Industrial IoT (IIoT) architectures**, bridging the gap between Edge hardware (ESP32) and Cloud-based AI inference.

##  System Architecture
The project follows a strict **3-Layer Architectural Pattern** to ensure modularity and scalability:

1. **Edge Layer (ESP32/Simulator):** High-frequency data acquisition and initial signal preprocessing.
2. **Logic Layer (FastAPI & Signal Engine):** - Digital Signal Processing (FFT, Kurtosis, RMS calculation).
   - AI Inference using structured predictive models.
3. **Infrastructure & Persistence:**
   - PostgreSQL for time-series data storage.
   - Docker-containerized environment for SRE-compliant deployment.



## Tech Stack
- **Backend:** Python 3.10+, FastAPI, Uvicorn
- **Data Science:** NumPy, SciPy (FFT/Signal Processing), Scikit-learn
- **Hardware/Edge:** ESP32 (Simulated via NASA Data Streamer)
- **DevOps:** Docker, Docker Compose, Pydantic (Data Validation)
- **Database:** PostgreSQL / SQLite

## Key Features
- **Real-time Signal Processing:** Implementation of Hamming windows and FFT for spectral leakage reduction.
- **Condition Indicators:** Real-time tracking of Kurtosis and RMS to identify the "Death Curve" of bearings.
- **Automated Alerts:** Status-based notification system (Healthy, Warning, Critical).
- **Industrial Standards:** Built following ISO 20816 standards for mechanical vibration.

Author: Tushar Tyagi

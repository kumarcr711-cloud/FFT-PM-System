# FFT-PM-System

Predictive maintenance prototype focused on vibration analysis for rotating machinery.

This repository combines:
- ESP32 firmware for vibration capture and MQTT publishing
- Python scripts/notebooks for FFT-based analysis on bearing data
- early data-bridge code for MQTT to InfluxDB

The project is still in progress. Current code demonstrates core ideas and working building blocks, not a full production system.

## Current Scope

Implemented:
- ESP32 data acquisition with MPU6050
- MQTT publish flow from device side
- FFT, RMS, and kurtosis experiments in Python
- initial MQTT to InfluxDB bridge script

Planned next:
- clean service boundaries (edge, ingestion, analytics)
- reproducible runtime setup and dependency management
- proper automated tests and CI checks
- dashboard/API layer and stronger documentation

## Repository Structure

- [src/main.cpp](src/main.cpp): ESP32 firmware (Wi-Fi, sensor readout, MQTT publish)
- [ESP.cpp](ESP.cpp): edge-side FFT/RMS feature extraction prototype
- [bridge.py](bridge.py): MQTT to InfluxDB bridge prototype
- [fft_pipeline.ipynb](fft_pipeline.ipynb): notebook experiments on bearing data
- [test_fft.py](test_fft.py): simple FFT simulation script
- [data/](data/): NASA bearing dataset samples used in analysis

## Quick Start

### Firmware (PlatformIO)

1. Install PlatformIO.
2. Open this repository in VS Code.
3. Build and flash using the environment in [platformio.ini](platformio.ini).

### Python analysis

1. Create and activate a virtual environment.
2. Install required packages (numpy, scipy, matplotlib, pandas, paho-mqtt, influxdb-client).
3. Run scripts or notebooks:
   - `python test_fft.py`
   - `python bridge.py`

Note: package pinning and a single dependency file will be added as part of the polishing phase.

## Data Source

The project uses bearing run-to-failure files stored under [data/1st_test](data/1st_test).

## Status

Development stage: prototype.

This repository is intended to show practical work on embedded sensing, signal processing, and data pipeline fundamentals. 

Here are demo videos

First video captures the reading on InfluxDB and spike is caused due to failure caused manually to test edge device and pipeline functionality (successful here)
Second video is a demonstration of a simulated failure and visualisaton of the normal vs failure mode simulation.




https://github.com/user-attachments/assets/5c8f7229-af37-41d5-bd2a-2da6e96bec47


https://github.com/user-attachments/assets/af29ff0a-1a9c-4cf2-8b18-1511adb899cf




## Author

Tushar Tyagi

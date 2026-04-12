#include <Arduino.h>
#include <Wire.h>
#include <arduinoFFT.h> 
#include <PubSubClient.h> // For MQTT
#include <WiFi.h>

// --- Configuration ---
#define SAMPLES 1024             // Must be a power of 2
#define SAMPLING_FREQUENCY 1000  // 1kHz sampling
#define MPU_ADDR 0x68

double vReal[SAMPLES];
double vImag[SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

// --- Feature Extraction Math ---
double calculateRMS(double* data, uint16_t size) {
    double sum = 0;
    for(int i=0; i<size; i++) sum += pow(data[i], 2);
    return sqrt(sum / size);
}

void setup() {
    Serial.begin(115200);
    Wire.begin(8, 9); // Your S3 I2C Pins
    
    // Initialize MPU6050
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // Wake up
    Wire.endTransmission(true);

    Serial.println("Edge Device Initialized.");
}

void loop() {
    // 1. High Speed Sampling
    unsigned long microseconds = micros();
    for(int i=0; i<SAMPLES; i++) {
        Wire.beginTransmission(MPU_ADDR);
        Wire.write(0x3B); // Accel X-axis data
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_ADDR, 2, true);
        
        vReal[i] = (Wire.read() << 8 | Wire.read()); // Raw X-Accel
        vImag[i] = 0; // Imaginary part is 0 for real signals

        while(micros() - microseconds < (1000000 / SAMPLING_FREQUENCY));
        microseconds = micros();
    }

    // 2. Feature Extraction (Time Domain)
    double rms = calculateRMS(vReal, SAMPLES);

    // 3. FFT (Frequency Domain)
    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD);
    FFT.complexToMagnitude();
    double peak = FFT.majorPeak();

    // 4. Output to Serial (Next step: MQTT)
    Serial.print("RMS: "); Serial.print(rms);
    Serial.print(" | Peak Freq: "); Serial.print(peak);
    Serial.println(" Hz");

    delay(2000); // Send data every 2 seconds
}

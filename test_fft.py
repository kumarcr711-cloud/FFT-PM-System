import numpy as np
import matplotlib.pyplot as plt

# Simulate a 1-second motor hum at 60Hz
fs = 1000  # Sampling frequency
t = np.linspace(0, 1, fs)
# Healthy motor (60Hz) + Random Noise
healthy_signal = np.sin(2 * np.pi * 60 * t) + 0.5 * np.random.randn(len(t))

# The FFT Magic
fft_values = np.fft.fft(healthy_signal)
frequencies = np.fft.fftfreq(len(t), 1/fs)

# Plot the "Frequency Signature" for your LinkedIn post
plt.plot(frequencies[:fs//2], np.abs(fft_values)[:fs//2])
plt.title("Motor Frequency Signature (FFT)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Intensity")
plt.show()

# Progarm to conduct a fourier transform on a data signal

from math import *
from cmath import *
import numpy as np
import wave
import struct
import matplotlib.pyplot as plt

# Parameters
amp = 16000 # Amplitude
freq = 1000 # Frequency
ns = 32 # number of samples
sr = 32 # sampling rate (for analog to digital conversion)


file = "test.wav"

# Implement structure
sin_wave_uncompressed = [sin(2 * pi * freq * x/sr) for x in range(ns)]
#swu = np.ndarray(shape=(32, 1), dtype = np.float64, buffer = bytes(sin_wave_uncompressed))
# TODO: Play wave uncompressed

# Create structure for a complex exponential function
Fourier = [exp(1j * amp * x/sr) for x in range(ns)]
# Multiply before integration
func = []
for i in range(ns):
    func.append(sin_wave_uncompressed[i] * Fourier[i])
fn = [z.real for z in func]
dn = (min(fn) + max(fn))/len(fn)

fns = np.ndarray(len(func), dtype = complex, buffer = np.array(func))
X_ = [x for x in range(ns)]

wave_compressed = np.trapz(func, X_, dx = dn, axis = -1)

# TODO: Play wave compressed

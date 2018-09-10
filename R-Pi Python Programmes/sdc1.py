from pylab import *
from rtlsdr import *
from scipy import signal
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import time
import math

sdr = RtlSdr()

# configure device
sdr.sample_rate = 2.4e6
sdr.center_freq = 433e6
sdr.gain = 1

samples = sdr.read_samples(256*1024)


# use matplotlib to estimate and plot the PSD
[p,f] = signal.periodogram(samples, nfft=1024, fs=(sdr.sample_rate)/1e6)
p=p.tolist()
f=f.tolist()
print f,p
#power = 10*log10(p[i])
#print (power)
#xlabel('Frequency (MHz)')	
#ylabel('Relative power (dB)')
#plt.show()

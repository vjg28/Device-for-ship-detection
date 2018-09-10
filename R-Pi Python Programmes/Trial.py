import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation
from pylab import *
from rtlsdr import *
import time 
import math

#create a Rtl object
sdr = RtlSdr()

# configure device(sdr.center_freq-sdr.sample_rate)/1e6, (sdr.center_freq+sdr.sample_rate)/1e6 
sdr.sample_rate = 2.4e6
sdr.center_freq = 433e6
sdr.gain = 1

# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim=((sdr.center_freq-sdr.sample_rate)/1e6, (sdr.center_freq+sdr.sample_rate)/1e6 ), ylim=(-80, 50 ))
line, = ax.plot([], [], lw=1)
a=[0]*10
# initialization function: plot the background of each frame
def init():
    line.set_data([],[])
    return line,

# animation function.  This is called sequentially
def animate(i):
    samples = sdr.read_samples(256*1024)
    [y,x]=psd(samples, NFFT=1024, Fs=sdr.sample_rate/1e6, Fc=sdr.center_freq/1e6,lw=0)
    line.set_data(x,10*log10(y))
    a[i%10]=freq_power(x,y)		#average of 10 values for better approximate result
    print sum(a)/len(a)			
    return line,

def freq_power(x,y):
    y=y.tolist()                               #cxonvert numpy array into list
    x=x.tolist()
    ld=y[885:925]                              #bandwidth setter
    power1=10*log10(max(ld))                   #calculating power in dB from pxx value
    #power2=10*log10(y[x.index(93.5015625)])
    return power1 #power2

anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=2000, interval=20, blit=False)

plt.show()

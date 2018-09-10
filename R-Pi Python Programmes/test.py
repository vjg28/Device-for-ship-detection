import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation
from pylab import *
from rtlsdr import *
import time
import math
#import smbus
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(24,GPIO.OUT)

#create i2c bus as object
#bus=smbus.SMBus(1)
#address=0x04

#rtl object
sdr=RtlSdr()

#configure device
sdr.sample_rate= 2.4e6
sdr.center_freq=433e6
sdr.gain=1

fig=plt.figure()
a=[0]*10

def freq_power(x,y):
	y=y.tolist()
	x=x.tolist()
	ld=y[600:1020]
	power=10*log10(max(ld))
	return power
	

i=0
while(1):
	i=i+1
	samples=sdr.read_samples(256*1024)
	[y,x]=psd(samples,NFFT=1024,Fs=sdr.sample_rate/1e6 , Fc=sdr.center_freq/1e6,lw=0)
	#line.set_data
	k=freq_power(x,y)
	print k

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
sdr.center_freq = 100e6
sdr.gain = 1

# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim=((sdr.center_freq-sdr.sample_rate)/1e6, (sdr.center_freq+sdr.sample_rate)/1e6 ), ylim=(-100, 100))
line, = ax.plot([], [], lw=1)

# initialization function: plot the background of each frame
def init():
    line.set_data([], [])
    return line,

# animation function.  This is called sequentially
def animate(i):
    samples = sdr.read_samples(256*1024)
    [y,x]=psd(samples, NFFT=1024, Fs=sdr.sample_rate/1e6, Fc=sdr.center_freq/1e6)
    line.set_data(x,y)
    return line,

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=200, interval=20, blit=False)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
#anim.save('basic_animation.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm, colors
import numpy as np

## Sssht!
np.seterr(all='ignore')

def plot_sensor(s):
  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')

  xedges = np.arange(0, s.pixel_rows+1)
  yedges = np.arange(0, s.pixel_columns+1)
  elements = (len(xedges) - 1) * (len(yedges) - 1)
  xpos, ypos = np.meshgrid(xedges[:-1]+0.25, yedges[:-1]+0.25)

  xpos = xpos.flatten()
  ypos = ypos.flatten()
  zpos = np.zeros(elements)
  dx = 0.5 * np.ones_like(zpos)
  dy = dx.copy()
  dz = np.array(s.data()).flatten()
  print "Calculating colors..."
  
  norm = colors.normalize(dz.min(), dz.max())
  col = []
  for i in dz:
    col.append(cm.jet(norm(i)))
  
  print "Now rendering image..."
  ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color=col, zsort='average')
  print "Saving image..."
  plt.savefig("out.eps", dpi=300)  
  print "All done!"
  
from libesame import *

print "Preparing simulation..."

u = Universe()

g = Generator()
g.position = Vector(10, 0, 0)
g.fire_rate = 5000
g.particles_speed = 1

s = Sensor()
s.pixel_rows = 50
s.pixel_columns = 50
s.top_left = Vector(0, -30, 30)
s.bottom_left = Vector(0, -30, -30)
s.top_right = Vector(0, 30, 30)

u.addGenerator(g)
u.addSensor(s)
u.boundary = 40

for i in range(0, 10):
  u.nextBatch()

print "Simulation finished!"
plot_sensor(s)


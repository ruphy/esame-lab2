from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm, colors
import numpy as np

## Sssht!
np.seterr(all='ignore')

def plot_sensor(s):
  print "Preparing the plot"
  # Create canvas
  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')

  # Calculate 3d plot data: grid
  xedges = np.arange(0, s.pixel_rows+1)
  yedges = np.arange(0, s.pixel_columns+1)
  elements = (len(xedges) - 1) * (len(yedges) - 1)
  xpos, ypos = np.meshgrid(xedges[:-1]+0.05, yedges[:-1]+0.05)

  # Calculate starting x, y, z
  xpos = xpos.flatten()
  ypos = ypos.flatten()
  zpos = np.zeros(elements)
  # Areas of the bins, flatten the heights
  dx = 0.9 * np.ones_like(zpos)
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
  plt.savefig("out.png", dpi=500)  
  #plt.show()
  print "All done!"
  
from libesame import *

print "Preparing simulation..."

u = Universe()

g = Generator()
g.position = Vector(7, 0, 0)
g.fire_rate = 5000
g.particles_speed = 1

s = Sensor()
s.pixel_rows = 20
s.pixel_columns = 20
s.top_left = Vector(0, -15, 15)
s.bottom_left = Vector(0, -15, -15)
s.top_right = Vector(0, 15, 15)

p = Sphere()
p.accuracy = 0.05
p.radius = 3
p.setAbsorbingCoefficient(0.3)
p.center = Vector(3, 0.65, 0.65)
#p.center = Vector(3, 0, 0)

u.addGenerator(g)
u.addSensor(s)
u.addSphere(p)
u.boundary = 20

for i in range(0, 10):
  print "batch ", i
  u.nextBatch()

#s.dump()
print "Simulation finished!"
plot_sensor(s)


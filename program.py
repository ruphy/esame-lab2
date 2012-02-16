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
  
  #print "Calculating colors..."
  #norm = colors.normalize(dz.min(), dz.max())
  #col = []
  #for i in dz:
    #col.append(cm.jet(norm(i)))
  
  print "Now rendering image..."
  #ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color=col, zsort='average')
  #cm.Greys.set_gamma(0.1)
  cax = ax.imshow(s.data(), interpolation='nearest', cmap=cm.Greys)
  #ax.set_title('Gaussian noise with horizontal colorbar')

  cbar = fig.colorbar(cax, ticks=[dz.min(), (dz.max()+dz.min())/2, dz.max()], orientation='vertical')
  cbar.ax.set_xticklabels(['Low', 'Medium', 'High'])# horizontal colorbar

  print "Saving image..."
  plt.savefig("out.png", dpi=500)  
  #plt.show()
  print "All done!"
  
from libesame import *
#from shared_ptr import *

print "Preparing simulation..."

u = Universe()

g = Generator()
g.position = Vector(5, 0, 0)
g.fire_rate = 10000
g.particles_speed = 1

s = Sensor()
s.pixel_rows = 100
s.pixel_columns = 100
s.top_left = Vector(0, -15, 15)
s.bottom_left = Vector(0, -15, -15)
s.top_right = Vector(0, 15, 15)

p = Sphere()
p.accuracy = 0.01
p.radius = 1.5
p.setAbsorbingCoefficient(0.2)
p.center = Vector(2, 0, 0)

u.addGenerator(g)
u.addObject(s)
u.addObject(p)
u.boundary = 20
#u.accuracy = 0.1

#quit()

for i in range(0, 10000):
  print "batch", i
  u.nextBatch()

#s.dump()
print "Simulation finished!"
plot_sensor(s)


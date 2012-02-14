from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm, colors
import numpy as np

def plot_sensor(s):
  np.seterr(all='ignore')
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
  
  #print colors.makeMappingArray(2, [[0, 0.1, 0.1],[1, 0.5, 1]])
  #array = [0, 0.2, 0.4, 1]
  ddz = dz.copy()
  #ddz.sort()
  #print ddz
  norm = colors.normalize(ddz.min(), ddz.max())
  col = []
  print norm(2)
  for i in dz:
    #print norm(i)
    a = cm.jet(norm(i))
    col.append(a)
    #print a
  #dzn = dz.copy()
  
  #print cm.ScalarMappable(norm=a, cmap=cm.jet).to_rgba(0.1)
  #print makeMappingArray(cm.jet.N, )
  #pcolor(dx, dy, dz)
  #cm.jet.set_array(dz)
  #dzn = dz.copy()
  #print cm.jet._colormap(dzn.normalize())
  #print help(cm.jet)
  
  print "Now rendering image..."
  ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color=col, zsort='average')
  #ax.contour(xedges, yedges, np.array(s.data()))
  print "Saving image..."
  plt.savefig("out.eps", dpi=300)  

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


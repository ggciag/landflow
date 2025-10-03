import numpy as np
import matplotlib.pyplot as plt



cont = 6000

Qr = np.loadtxt("t_%d.txt"%(cont))

Qr = np.reshape(Qr,(4380,3300))
Qr[Qr<=0]=1.0

seg_por_ano = 365.0*24.0*60.0*60.0

Qr*=(1800**2)/seg_por_ano

print(np.max(Qr))

plt.figure(figsize=(10,5))
plt.imshow(np.log10(Qr),extent=[-85,-30,-58,15])

plt.xlim(-85, -30) 
plt.ylim(-20, 15) 

cbar = plt.colorbar()
cbar.set_ticks([0,1,2,3,4,5])
cbar.set_ticklabels(["1","10","10$^2$","10$^3$","10$^4$","10$^5$"])

plt.title("$Q_r$ (m$^3$/s)")
plt.savefig("Qr_map.png",dpi=2500)
plt.close()
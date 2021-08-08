import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
df = pd.read_csv("CsIDetectorResults_nt_CsI Detector Gamma Spectrum(Cs137keV).csv",usecols=[0],header=None,sep = ',', skiprows= [0,1,2,3,4])

print(df.head())
df.plot.hist(bins=1023)
plt.title("CS137 Spectrum")
plt.xlabel("Energy (keV)")
plt.ylabel("Counts")
plt.yscale("log")
plt.show()


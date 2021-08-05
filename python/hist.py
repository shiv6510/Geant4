# import libraries
import numpy as np
from matplotlib import pyplot as plt


def graph(nuclide):

    # load in data points and reference peaks
    data_path = "/home/shiv/Desktop/Atom Workspace/python/geant4/data/"

    data = np.loadtxt(data_path + "data_" + nuclide + ".txt")
    max_ene = np.amax(data)

    # graph the spectra
    # DON'T FORGET TO CHANGE MAX BIN
    bins = np.arange(0., max_ene+0.05, 0.0005)

    # plt.style.use('dark_background')
    plt.hist(data, bins=bins, density=True, edgecolor='black',
             color='limegreen', histtype='step', zorder=1)
    plt.yscale('log', nonpositive='clip')

    # for i in peaks:
    # 	ene = i[0]
    # 	height = i[1]
    # 	plt.vlines(x=ene, ymin=0, ymax=height*5e3, colors='red', zorder=2)

    plt.xlabel("Energy[MeV]")
    plt.ylabel("Relative Counts")
    plt.title(nuclide + " Spectra")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    nuclide = input("What is your nuclide? ")
    graph(nuclide)

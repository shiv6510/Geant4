# import libraries
import numpy as np


def macro(nuclide):

    # set variables
    command = "/gps/hist/point "
    peaks_path = "/home/shiv/Desktop/Atom Workspace/python/geant4/peaks/"
    spectra_path = "/home/shiv/Desktop/Atom Workspace/python/geant4/spectra/"

    # use branching ratios to get relative intensities
    peaks = np.loadtxt(peaks_path + "peaks_" + nuclide + ".txt")
    peaks[:, 1] = peaks[:, 1] / np.amax(peaks[:, 1])
    peaks = peaks[np.argsort(peaks[:, 0])]

    energies = peaks[:, 0]
    ratios = peaks[:, 1]

    # write macro to file
    bins = np.linspace(0., 2., 1024)
    f = open(spectra_path + "spectra_" + nuclide + ".mac", 'w')
    f.write("# Macro spectra.g4mac\n\n/gps/hist/type energy\n\n")

    j = 0
    for i in range(0, bins.size):
        if (j < energies.size):
            if (bins[i] < energies[j]):
                f.write(command + str(bins[i]) + ' 0.\n')
            else:
                f.write(
                    command + str('{:.4f}'.format(bins[i])) + ' ' + str(ratios[j]) + '\n')
                j += 1
        else:
            f.write(command + str(bins[i]) + ' 0.\n')
    f.close()


if __name__ == "__main__":
    nuclide = input("What is your nuclide? ")
    macro(nuclide)

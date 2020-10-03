from simulation_results.extract_lte_spectrum_phy_results import LteSpectrumPhyResults


def extract_tbler_results(simulation_path):
    LteSpectrumPhyResults(simulation_path)
    return LteSpectrumPhyResults.tbler_results

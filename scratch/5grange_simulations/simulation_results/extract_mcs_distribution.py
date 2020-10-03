from simulation_results.extract_lte_spectrum_phy_results import LteSpectrumPhyResults


def extract_mcs_distribution(simulation_path):
    LteSpectrumPhyResults(simulation_path)
    return LteSpectrumPhyResults.mcs_distribution

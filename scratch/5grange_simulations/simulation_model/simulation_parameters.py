from .pu_model import PU_Model
from .enb_model import eNB_Model
from .ue_model import UE_Model

# Small selection of fusion algorithms, as we already have a ton of other different parameters to change
fusionAlgorithms = {
    6: "MRG_OR",
    7: "MRG_AND",
    11: "MRG_2_OF_N",
    12: "MRG_3_OF_N",
    13: "MRG_4_OF_N",
}

mimoSchemes = {
    0: "SISO",
    1: "TX_Diversity",
    2: "Spatial_mux",
}

class SimulationParameters():
    def __init__(self,
                 PU_models,
                 UE_models,
                 eNB_model,
                 traffic_profile_model=None,
                 simulation_time=10,
                 fusion_algorithm = 6,
                 propagation_model = "ns3::RANGE5GPropagationLossModel",
                 enableDSA = False,
                 SNRSensing = False,
                 attackers_per_channel = 0,
                 markov_detection = False,
                 harmonic_detection = False,
                 useErrorModel = True,
                 usePerfectChannel = False,
                 useHarq = True,
                 useIdealRrc = True,
                 useCdlPathLoss = False,
                 forceMaxMcsSched = False,
                 numerology = 0,
                 kval = 0.0,
                 numAntennas = 2,
                 mimoMode = 0,
                 channel_bandwidth = 24,  # converted into number of RBS inside the simulation program
                 freqBand = 100,  # converted into frequency ranges inside the simulation program
                 cdlType = "CDL_D"):

        self.dictio = {"SimulationParameters": {}}

        #Original settings
        self.dictio["SimulationParameters"]["ts"] = simulation_time
        self.dictio["SimulationParameters"]["bw"] = channel_bandwidth
        self.dictio["SimulationParameters"]["propagationModel"] = propagation_model
        self.dictio["PU"]  = PU_models
        self.dictio["eNB"] = eNB_model
        self.dictio["UE"]  = UE_models

        # COLAB settings
        self.dictio["SimulationParameters"]["fusionAlgorithm"] = fusion_algorithm
        self.dictio["SimulationParameters"]["fusionAlgorithmName"] = fusionAlgorithms[fusion_algorithm]
        self.dictio["SimulationParameters"]["enableDSA"] = enableDSA
        self.dictio["SimulationParameters"]["SNRSensing"] = SNRSensing #if false, distance-based detection curves will be loaded

        # MHM settings
        self.dictio["SimulationParameters"]["attackers_per_channel"] = attackers_per_channel
        self.dictio["SimulationParameters"]["markov_detection"]   = markov_detection
        self.dictio["SimulationParameters"]["harmonic_detection"] = harmonic_detection

        # LTE/5G-RANGE channel model settings
        self.dictio["SimulationParameters"]["useErrorModel"]     = useErrorModel
        self.dictio["SimulationParameters"]["usePerfectChannel"] = usePerfectChannel
        self.dictio["SimulationParameters"]["useHarq"]           = useHarq
        self.dictio["SimulationParameters"]["useIdealRrc"]       = useIdealRrc
        self.dictio["SimulationParameters"]["useCdlPathLoss"]    = useCdlPathLoss
        self.dictio["SimulationParameters"]["forceMaxMcsSched"]  = forceMaxMcsSched
        self.dictio["SimulationParameters"]["kval"]              = kval
        self.dictio["SimulationParameters"]["numAntennas"]       = numAntennas
        self.dictio["SimulationParameters"]["mimoMode"]          = mimoMode
        self.dictio["SimulationParameters"]["freqBand"]          = freqBand
        self.dictio["SimulationParameters"]["cdlType"]           = cdlType
        self.dictio["SimulationParameters"]["numerology"]        = numerology

        # EROS generated traffic profile to inject into applications
        self.dictio["SimulationParameters"]["traffic_profile_model"] = traffic_profile_model

        #Clean classes as processes may be recycled
        PU_Model.PUs = {}
        PU_Model.num_PU = 0
        eNB_Model.eNBs = {}
        eNB_Model.num_eNB = 0
        UE_Model.UEs = {}
        UE_Model.num_UE = 0

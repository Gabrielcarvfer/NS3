class eNB_Model():
    num_eNB = 0
    eNBs = {}

    def __init__(self, coordinate_tuple, transmission_power, antenna_gain):
        self.dictio = {}
        self.dictio["num"]      = eNB_Model.num_eNB
        self.dictio["position"] = coordinate_tuple
        self.dictio["tx_power"] = transmission_power
        self.dictio["gain"]     = antenna_gain

        eNB_Model.eNBs[eNB_Model.num_eNB] = self.dictio
        eNB_Model.num_eNB += 1
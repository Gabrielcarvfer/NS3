class UE_Model():
    num_UE = 0
    UEs = {}
    def __init__(self, coordinate_tuple, transmission_power, antenna_gain, speed):
        self.dictio = {}
        self.dictio["num"]      = UE_Model.num_UE
        self.dictio["position"] = coordinate_tuple
        self.dictio["tx_power"] = transmission_power
        self.dictio["gain"]     = antenna_gain
        self.dictio["speed"]     = speed

        UE_Model.UEs[UE_Model.num_UE] = self.dictio
        UE_Model.num_UE += 1

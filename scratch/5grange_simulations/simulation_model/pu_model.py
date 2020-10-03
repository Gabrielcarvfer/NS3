class PU_Model():
    num_PU = 0
    PUs = {}
    def __init__(self, coordinate_tuple, transmission_power, duty_cycle, period, channel):
        self.dictio = {}
        self.dictio["position"]   = coordinate_tuple
        self.dictio["tx_power"]   = transmission_power
        self.dictio["duty_cycle"] = duty_cycle
        self.dictio["period"]     = period
        self.dictio["num"]        = PU_Model.num_PU
        self.dictio["channel"]    = channel

        PU_Model.PUs[PU_Model.num_PU] = self.dictio
        PU_Model.num_PU += 1
        return
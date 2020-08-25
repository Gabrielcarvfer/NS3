#!/usr/bin/python3
import process_output

baseFolder = "../build/bin/"

inputFiles = { "cqi_p10"                : { "file" : "dump_p10.json"                    , "keys" : [], "data": []},
               "cqi_a30"                : { "file" : "dump_a30.json"                    , "keys" : [], "data": []},
               #"lcid_qci"               : { "file" : "dump_lcidqci.json"                , "keys" : [], "data": []},
               "holgroup_gbr"           : { "file" : "dump_holgroups_gbr.json"          , "keys" : [], "data": []},
               "holgroup_ngbr"          : { "file" : "dump_holgroups_ngbr.json"         , "keys" : [], "data": []},
               "ue_data_to_transfer"    : { "file" : "dump_ue_data_to_transfer.json"    , "keys" : [], "data": []},
               "ue_assigned_resources"  : { "file" : "dump_ue_assigned_resources.json"  , "keys" : [], "data": []},
               "dci_buffer"             : { "file" : "dump_dci_buffer.json"             , "keys" : [], "data": []},
               "allocation_map"         : { "file" : "dump_allocation_map.json"         , "keys" : [], "data": []},
               "available_rbgs_postharq": { "file" : "dump_availablerbgs_postharq.json" , "keys" : [], "data": []},
               "rargrants"              : { "file" : "dump_rargrants.json"              , "keys" : [], "data": []},
               "datagrants"             : { "file" : "dump_datagrants.json"             , "keys" : [], "data": []}

               }
#"available_rbgs_preharq": {"file": "dump_availablerbgs_preharq.json", "keys": [], "data": []},
#"active_harq"            : { "file" : "dump_activeharqs.json"           , "data": []},
#"rlc_sched"              : { "file" : "dump_rlcsched.json"              , "data": []},


class SimResults:

    def __init__(self, inputFiles):
        self.currentInterval = 0
        self.compiledSimData = {}
        self.compiledSimKeys = []

        self.compiledNnInput = {}
        self.compiledNnInputKeys = {}
        self.encodedNnInput = {}
        self.compiledNnOutput = {}
        self.availableSchedulers = {"ns3"       : self.remountNS3Scheduler,
                                    "roundRobin": self.roundRobinScheduler
                                    }
        self.normalizeCqi = [i/15 for i in range(16)]
        self.unnormalizeCqi = {}
        for i in range(16):
            self.unnormalizeCqi[i/15] = i
            
        self.lcidqci = process_output.read_json_file(baseFolder+"dump_lcidqci.json")["lcid_qci"]


        for inputFile in inputFiles.values():
            for sample in list(inputFile["data"].keys()):
                if sample not in self.compiledSimData.keys():
                    self.compiledSimData[sample] = {}

                for key, value in inputFile["data"][sample].items():
                    self.compiledSimData[sample][key] = value

        self.compiledSimKeys = sorted([int(x) for x in list(self.compiledSimData.keys())])
        return

    def remountNS3Scheduler(self):
        for key in self.compiledSimKeys:
            dataKey = str(key) #process_output.f2s(key)
            data = self.compiledSimData[dataKey]

            i = 0
            if len(data["a30cqiPerUe"]) > 0:# and data["availablerbgs_postharq"].count(1) > 0:
                self.compiledNnInput[dataKey] = {}
                self.compiledNnInput[dataKey]["datagrants"] = data["datagrants"]
                self.compiledNnInput[dataKey]["ues"] = {}
                for ue in data["a30cqiPerUe"].keys():
                    #if data["ueToAmountOfDataToTransfer"][ue]["bitsToTransmit"] > 0:
                        ueData = self.compiledNnInput[dataKey]["ues"][ue] = {}
                        ueData["a30cqi"] = data["a30cqiPerUe"][ue]
                        ueData["dataToTransfer"] = {}
                        if ue in data["bitsToTransmitPerUePerLcid"]:
                            ueData["dataToTransfer"] = data["bitsToTransmitPerUePerLcid"][ue]
                        ueData["holgroups"] = {"gbr":{}, "ngbr":{}}
                        i += 1
                        pass
                    #pass
                pass
                for holkey, holvalues in data["holgroups_gbr"].items():
                    for holpair in holvalues:
                        self.compiledNnInput[dataKey]["ues"][str(holpair["rnti"])]["holgroups"]["gbr"][holpair["lcid"]] = holkey
                        pass

                pass
                for holkey, holvalues in data["holgroups_ngbr"].items():
                    for holpair in holvalues:
                        self.compiledNnInput[dataKey]["ues"][str(holpair["rnti"])]["holgroups"]["ngbr"][holpair["lcid"]] = holkey
                        pass
                    pass
                pass

            if i > 0:
                self.compiledNnInput[dataKey]["availablerbgs_postharq"] = data["availablerbgs_postharq"]
        pass

    def roundRobinScheduler(self):
        pass

    def build_nn_input(self, scheduler="ns3"):
        #Totally depends on the chosen scheduler
        self.availableSchedulers[scheduler]()

        #Translate compiled nn input to UE CQIs, QCI,
        self.compiledNnInputKeys = sorted([int(x) for x in list(self.compiledNnInput.keys())])

        for key in self.compiledNnInputKeys:
            keyStr = str(key)#process_output.f2s(key)
            nnData = self.compiledNnInput[keyStr]

            ue_gbr = {}
            ue_ngbr = {}
            ue_lcid = {}
            max_to_transmit = 0
            #Search for gbr holgroups, and qcis of lcids
            for ue_key, ue_value in nnData["ues"].items():
                if len(ue_value["holgroups"]["gbr"]) > 0:
                    ue_gbr[ue_key] = 0
                if len(ue_value["holgroups"]["ngbr"]) > 0:
                    ue_ngbr[ue_key] = 0

                ue_lcid[ue_key] = {}

                for lcid in ue_value["dataToTransfer"]:
                    bitsToTransmit = ue_value["dataToTransfer"][lcid]
                    ue_lcid[ue_key][lcid] = bitsToTransmit

                    max_to_transmit = bitsToTransmit if (bitsToTransmit > max_to_transmit) else max_to_transmit

                pass

            #Number of available slots
            numAvailableSlots = nnData["availablerbgs_postharq"].count(1)
            freeSlotsIndex = [i for i, x in enumerate(nnData["availablerbgs_postharq"]) if x == 1]

            nnEntries = []
            #First GBR

            #After nGBR
            #todo: prioritize different LCIDs and QCIs
            for ue in ue_ngbr.keys():
                for lcid in ue_lcid[ue].keys():
                    normalizedBitsToTransmit = ue_lcid[ue][lcid]/max_to_transmit

                    qci = self.lcidqci[lcid]["qci"]
                    normalizedQci = 0

                    cqi = nnData["ues"][ue]["a30cqi"]
                    normalizedCqi = [self.normalizeCqi[cqiVal] if i in freeSlotsIndex else 0 for i, cqiVal in enumerate(cqi)]

                    #Build nn entry
                    nnEntry = []
                    nnEntry += normalizedCqi
                    nnEntry += [normalizedQci]
                    nnEntry += [normalizedBitsToTransmit]
                    #nnEntry += hol

                    #Pack newly built entry into a list for the time slot
                    nnEntries += [nnEntry]
                    pass
                pass
            #Save entries generated for a slot
            self.encodedNnInput[keyStr] = nnEntries
            pass

        pass


    def build_nn_output(self, scheduler="ns3"):
        # Totally depends on the chosen scheduler
        self.availableSchedulers[scheduler]()

        # Translate compiled nn input to UE CQIs, QCI,
        self.compiledNnInputKeys = sorted([int(x) for x in list(self.compiledNnInput.keys())])

        for key in self.compiledNnInputKeys:
            keyStr = str(key)#process_output.f2s(key)
            nnData = self.compiledNnInput[keyStr]
            allocationMap = self.compiledSimData[keyStr]["allocationMapPerRntiPerLCId"]

            ue_gbr = {}
            ue_ngbr = {}
            ue_lcid = {}
            max_to_transmit = 0
            # Search for gbr holgroups, and qcis of lcids
            for ue_key, ue_value in nnData["ues"].items():
                if len(ue_value["holgroups"]["gbr"]) > 0:
                    ue_gbr[ue_key] = 0
                if len(ue_value["holgroups"]["ngbr"]) > 0:
                    ue_ngbr[ue_key] = 0

                ue_lcid[ue_key] = {}

                for lcid in ue_value["dataToTransfer"]:
                    bitsToTransmit = ue_value["dataToTransfer"][lcid]
                    ue_lcid[ue_key][lcid] = bitsToTransmit

                    max_to_transmit = bitsToTransmit if (bitsToTransmit > max_to_transmit) else max_to_transmit


                pass

            # Number of available slots
            numAvailableSlots = nnData["availablerbgs_postharq"].count(1)
            freeSlotsIndex = [i for i, x in enumerate(nnData["availablerbgs_postharq"]) if x == 1]

            # Hold scheduler UEs, their LCID and CQI
            scheduledUes = {}

            # Check if a UE got allocated for the previously free slots and fetch LCID and CQI
            for reg in nnData["datagrants"]:
                rnti   = reg["rnti"]
                bitmap = reg["rbBitmap"]
                slotList = []
                i = 0
                while bitmap > 0:
                    slotList += [i] if (bitmap & 0x01 == 1) else []
                    bitmap >>= 1
                    i += 1

                if len(slotList) == 0:
                    continue

                if keyStr not in self.compiledNnOutput:
                    self.compiledNnOutput[keyStr] = {}

                # Save entries generated for a slot
                for slot in slotList:
                    rntiStr = str(rnti)
                    cqi = nnData["ues"][rntiStr]["a30cqi"][int(slot)]
                    lcid = nnData["ues"][rntiStr]["dataToTransfer"]
                    #todo: extract the data to transfer after allocation and fetch correct lcid
                    self.compiledNnOutput[keyStr][slot] = {"ue": rntiStr, "cqi": cqi, "lcid": list(ue_lcid.keys())[0]}
                pass


            pass


        pass



def main():
    for inputFile in inputFiles.values():
        inputFile["data"] = process_output.read_json_file(baseFolder+inputFile["file"])
        inputFile["keys"] = sorted([float(x) for x in list(inputFile["data"].keys())])
        pass

    #Print allocation map
    #process_output.print_allocation_map(inputFiles["allocation_map"])

    #Join every json output file from NS3
    simResults = SimResults(inputFiles)
    simResults.remountNS3Scheduler()

    #Build input to nn
    simResults.build_nn_input()

    #Build output to nn
    simResults.build_nn_output()

    #Write output pickle and json
    import pickle
    with open("output_data.pickle", "wb") as file:
        pickle.dump({"input": simResults.compiledNnInput, "output": simResults.compiledNnOutput, "lcid_qci": simResults.lcidqci}, file)


    import json
    with open("output_data.json", "w") as file:
        json.dump({"input": simResults.compiledNnInput, "output": simResults.compiledNnOutput, "lcid_qci": simResults.lcidqci}, file, indent=4)
    return



main()
#!/usr/bin/python3
import os
import torch
import torch.nn as nn
import torch.optim as optim
import numpy
import pickle
import statistics
import random
import time

debug = True
verbose = True
N_EPOCHS = 15
learning_rate=0.05

import matplotlib.pyplot as plt

fig, ( (lossTrainAxis, accTrainAxis), (lossTestAxis, accTestAxis), (lossValidAxis, accValidAxis) ) = plt.subplots(3, 2, gridspec_kw={'width_ratios': [1, 1]})

yLossTrain = []
yAccTrain  = []
yLossTest  = []
yAccTest   = []
yLossValid = []
yAccValid  = []

plt.ion()
plt.show()

xs = list(range(0, N_EPOCHS))


def animate():

    global lossTrainAxis, fig, accTrainAxis, lossTestAxis, accTestAxis, lossValidAxis, accValidAxis, yLossTrain, yAccTrain, yLossTest, yAccTest, yLossValid, yAccValid
    lossTrainAxis.clear()
    lossTrainAxis.plot(xs[:len(yLossTrain)], yLossTrain)

    accTrainAxis.clear()
    accTrainAxis.plot(xs[:len(yAccTrain)], yAccTrain)

    lossTestAxis.clear()
    lossTestAxis.plot(xs[:len(yLossTest)], yLossTest)

    accTestAxis.clear()
    accTestAxis.plot(xs[:len(yAccTest)], yAccTest)

    lossValidAxis.clear()
    lossValidAxis.plot(xs[:len(yLossValid)], yLossValid)

    accValidAxis.clear()
    accValidAxis.plot(xs[:len(yAccValid)], yAccValid)
    plt.draw()
    plt.pause(0.001)

from torch.jit import ScriptModule, script_method, trace


# Class definitions
class Net(torch.nn.Module): #ScriptModule):

    def __init__(self):
        super(Net, self).__init__()
        self.numSlots = 50  # number of available slots to schedule
        self.numReqs  = 100  # number of simultaneous requests being input
        self.inputsPerReq = (self.numSlots + 4)
        self.filler_input = [0] * (self.inputsPerReq)
        self.inputs = (self.inputsPerReq) * self.numReqs  # +1 is for the QCI + 1 budget, increase if need more inputs
        self.outputs = self.numSlots * self.numReqs
        self.fc1 = nn.Linear(self.inputs, self.inputs//2, 2)
        self.fc2 = nn.Linear(self.inputs//2, self.inputs//4, 2)
        self.fc3 = nn.Linear(self.inputs//4, self.inputs//8, 2)
        self.fc4 = nn.Linear(self.inputs//8, self.inputs//16, 2)
        self.fc5 = nn.Linear(self.inputs//16, self.inputs//32, 2)
        self.fc6 = nn.Linear(self.inputs//32, self.outputs, 2)

        self.saved_log_probs = []
        self.rewards = []

    #@script_method
    def forward(self, x):
        y = x
        y = torch.sigmoid(self.fc1(y))
        y = torch.sigmoid(self.fc2(y))
        y = torch.sigmoid(self.fc3(y))
        y = torch.sigmoid(self.fc4(y))
        y = torch.sigmoid(self.fc5(y))
        y = torch.sigmoid(self.fc6(y))
        return y

folder              = "./checkpoints9/"
filename            = "checkpoint.pth.tar"
bestfilename        = "model_best.pth.tar"
translationDataFile = "translationData.pickle"
trainLoaderFile     = "trainLoaderData.pickle"
testLoaderFile      = "testLoaderData.pickle"

# Global variable declaration
device = torch.device("cpu")
model = Net().to(device)
optimizer = optim.Adam(model.parameters(), lr=learning_rate)
lossf = nn.MSELoss()
torch.set_num_threads(15)
eps = numpy.finfo(numpy.float32).eps.item()

best_score = 1.0

log_acc_loss = {}
log_acc_loss["train"] = {}
log_acc_loss["test"] = {}


def train(train_loader, test_loader, args):
    global optimizer
    torch.manual_seed(args["seed"])

    optimizer = optim.SGD(model.parameters(), lr=args["lr"], momentum=args["momentum"])

    if "state_dict" in args:
        model.load_state_dict(args["state_dict"])
    if "optimizer" in args:
        optimizer.load_state_dict(args["optimizer"])

    for epoch in range(args["start_epoch"], args["epochs"] + 1):
        train_epoch(epoch, args, train_loader)
        args["start_batch"] = 0
        test_epoch(epoch, test_loader)


def test(epoch, test_loader, args):
    torch.manual_seed(args["seed"])
    test_epoch(epoch, test_loader)

def train_epoch(epoch, args, data_loader):
    global best_score, log_acc_loss, yLossTrain, yAccTrain
    model.train()
    pid = os.getpid()

    correct  = []
    losses = []
    unique = {}
    for batch_idx, (data, target) in enumerate(data_loader):

        if batch_idx <= args["start_batch"]:
            continue
        if (tuple(data),tuple(target)) not in unique:
            unique[(tuple(data),tuple(target))] = 0
        else:
            continue
        optimizer.zero_grad()

        input = torch.Tensor([data])

        output = model(input)

        targetOutput = torch.Tensor([target])
        loss = lossf(output, targetOutput)
        loss.backward()
        optimizer.step()

        corr = 0
        total = 0
        freeSlots = target.count(1)
        maxIndexes = numpy.argpartition(output.detach()[0], -freeSlots)[-freeSlots:]

        for index in maxIndexes:
            corr += target[index]
            total += 1
        correct += [corr == total]
        losses += [loss.item()]

        if batch_idx % args["log_interval"] == 0:
            if batch_idx % args["log_interval"]*2 == 0:
                print('{}\tTrain Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                    pid, epoch, batch_idx * len(data), len(data_loader) * len(data),
                    100. * batch_idx / len(data_loader), loss.item()))

            is_best = loss.item() < best_score
            best_score = min(best_score, loss.item())

            # Save checkpoint for every batch
            save_checkpoint({
                'epoch': epoch,
                'batch_idx': batch_idx,
                'best_score': best_score,
                'state_dict': model.state_dict(),
                'optimizer': optimizer.state_dict(),
                'log_acc_loss': log_acc_loss
            }, is_best)

    log_acc_loss["train"][epoch] = {}
    log_acc_loss["train"][epoch]["acc"]     = statistics.mean(correct)
    log_acc_loss["train"][epoch]["accDev"]  = statistics.stdev(correct)
    log_acc_loss["train"][epoch]["loss"]    = statistics.mean(losses)
    log_acc_loss["train"][epoch]["lossDev"] = statistics.stdev(losses)

    yLossTrain.append(statistics.mean(losses))
    yAccTrain.append(statistics.mean(correct))
    #animate()



def save_checkpoint(state, is_best):
    import shutil
    torch.save(state, folder+filename)
    if is_best:
        shutil.copyfile(folder+filename, folder+bestfilename)


def load_checkpoint():
    state = None
    with open(folder+filename,'rb') as file:
        state = torch.load(file)
    return state


def test_epoch(epoch, data_loader):
    global log_acc_loss, yLossTest, yAccTest
    model.eval()
    correct = []
    losses = []
    with torch.no_grad():
        for batch_idx, (data, target) in enumerate(data_loader):
            input = torch.Tensor([data])

            output = model(input)

            targetOutput = torch.Tensor([target])
            loss = lossf(output, targetOutput) # sum up batch loss

            corr = 0
            total = 0
            freeSlots = target.count(1)
            maxIndexes = numpy.argpartition(output[0],-freeSlots)[-freeSlots:]

            for index in maxIndexes:
                corr += target[index]
                total += 1
            #for slot_slice in range(0, model.numSlots*model.numReqs, model.numReqs):
            #    maxIndex = int(output[0][slot_slice:slot_slice+model.numReqs].argmax())
            #    targetIndex = int(target[slot_slice:slot_slice+model.numReqs].index(1))
            #    if target[slot_slice+maxIndex] and target[slot_slice:slot_slice+model.numReqs].count(1) == 1:
            #        corr += 1
            #    total += 1

            correct += [int(corr == total)]
            losses += [loss.item()]
            #pred = output.max(1)[1] # get the index of the max log-probability
            #correct += pred.eq(target).sum().item()

    print('\nTest set: Average loss: {:.4f}, Deviation: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        statistics.mean(losses), statistics.stdev(losses), correct.count(1), len(data_loader),
        100. * statistics.mean(correct)))

    log_acc_loss["test"][epoch] = {}
    log_acc_loss["test"][epoch]["acc"]     = statistics.mean(correct)
    log_acc_loss["test"][epoch]["accDev"]  = statistics.stdev(correct)
    log_acc_loss["test"][epoch]["loss"]    = statistics.mean(losses)
    log_acc_loss["test"][epoch]["lossDev"] = statistics.stdev(losses)

    yLossTest.append(statistics.mean(losses))
    yAccTest.append(statistics.mean(correct))
    animate()

    pass

def main():
    global log_acc_loss, lossTrainAxis, accTrainAxis, lossTestAxis, accTestAxis, lossValidAxis, accValidAxis, yLossTrain, yAccTrain, yLossTest, yAccTest, yLossValid, yAccValid, model
    args = {}
    args["batch_size"]   = 10
    args["lr"]           = learning_rate
    args["momentum"]     = 0.025
    args["epochs"]       = N_EPOCHS
    args["log_interval"] = 250
    args["seed"] = 0
    args["start_batch"] = 0
    args["start_epoch"] = 1

    if not os.path.exists(folder):
        os.mkdir(folder)

    state = None
    if os.path.exists(folder+filename):
        state = load_checkpoint()

    if state is not None:
        args["start_epoch"] = state["epoch"]
        args["start_batch"] = state["batch_idx"]
        args["best_score"]  = state["best_score"]
        args["state_dict"]  = state["state_dict"]
        args["optimizer"]   = state["optimizer"]
        log_acc_loss        = state["log_acc_loss"]

        for run_type in log_acc_loss.keys():
            for epoch in log_acc_loss[run_type]:
                if run_type == "train":
                    yLossTrain += [log_acc_loss[run_type][epoch]["loss"]]
                    yAccTrain  += [log_acc_loss[run_type][epoch]["acc"]]
                elif run_type == "test":
                    yLossTest  += [log_acc_loss[run_type][epoch]["loss"]]
                    yAccTest   += [log_acc_loss[run_type][epoch]["acc"]]
                else:
                    pass
        animate()
        pass

    train_loader = []
    test_loader  = []

    if not os.path.exists(trainLoaderFile):
        #prepare normalized cqi values
        normalizeCqi = [i / 15 for i in range(16)]
        unnormalizeCqi = {}
        for i in range(16):
            unnormalizeCqi[i / 15] = i

        #prepare qci scaled values
        qci_priority = [69, 65, 5, 1, 66, 75, 3, 2, 4, 70, 6, 79, 7, 8, 9]
        reversed_qci_priority = list(reversed(qci_priority))

        #higher preference results in higher value (ranging between 0 and 1)
        normalizeQci = {}
        for qci in reversed_qci_priority:
            normalizeQci[qci] = reversed_qci_priority.index(qci)/len(reversed_qci_priority)

        import json
        simData = None#torch.utils.data.DataLoader()

        #Load data
        with open("./output_data.json", "r") as file:
            simData = json.load(file)

        #Zip input and output
        zipped = {}
        for key in simData["output"]:
            zipped[key] = {"data": simData["input"][key], "target": simData["output"][key]}

        #Sort keys
        zippedKeys = sorted([int(x) for x in list(simData["output"].keys())])

        from itertools import permutations, islice

        translationData = {}
        #Build nn input list
        for key in zippedKeys:
            zipVal = zipped[str(key)]

            #Find UEs with data to transfer
            ues_transmit = []
            list_ues = {}
            max_bits_to_transmit = 0
            position = 0
            for ue, ue_data in zipVal["data"]["ues"].items():
                availableSlotsVsCqi = []
                for j in range(len(zipVal["data"]["availablerbgs_postharq"])):
                    availableSlotsVsCqi += [ zipVal["data"]["availablerbgs_postharq"][j] * ue_data["a30cqi"][j] ]

                for lcid, bits_transmit in ue_data["dataToTransfer"].items():
                    if bits_transmit > 0:
                        list_ues[int(ue)] = 0
                        ngbr = False
                        if lcid in ue_data["holgroups"]["ngbr"].keys():
                            ngbr = True

                        ues_transmit += [[int(ue), int(lcid), bits_transmit, ngbr, position, availableSlotsVsCqi]]
                        if bits_transmit > max_bits_to_transmit:
                            max_bits_to_transmit = bits_transmit
                        position += 1

            #Find slots that were allocated
            slots_transmitted = {}
            for slot, slot_use in zipVal["target"].items():
                slot = int(slot)
                ue   = int(slot_use["ue"])
                lcid = int(slot_use["lcid"])

                slots_transmitted[slot] = [slot, ue, lcid, int(slot_use["cqi"]) ]

            #Encode input for nn
            ue_keys = {}
            i = 0
            for ue in list_ues.keys():
                ue_keys[ue] = i / len(list_ues)
                i += 1

            datat = []
            for ue_lcid_info in ues_transmit:
                #ue_lcid_info[0] = ue
                #ue_lcid_info[1] = lcid
                #ue_lcid_info[2] = bits to transmit
                #ue_lcid_info[3] = gbr or not
                #ue_lcid_info[4] = position
                #ue_lcid_info[5] = [cqi per slot masked with available slots]
                normUe   = ue_keys[ue_lcid_info[0]]
                qci      = simData["lcid_qci"][str(ue_lcid_info[1])]["qci"]
                normQci  = normalizeQci[qci]
                normBits = ue_lcid_info[2]/max_bits_to_transmit
                gbr      = float(ue_lcid_info[3])
                normCqi   = [normalizeCqi[cqiVal] for cqiVal in ue_lcid_info[5]]
                #datat   += [[normUe, normQci, normBits, gbr, normQci, *normCqi]] #bizarrely duplicated normQci instead of position, but the duplicated value shouldn't affect results, so can be kept
                datat    += [[normUe, normQci, normBits, gbr, *normCqi]]
                pass

            translationData[str(key)] = {}
            translationData[str(key)]["ues_transmit"] = ues_transmit

            #Encode output for nn
            positions = {}
            for i in range(model.numSlots):
                if i in slots_transmitted.keys():
                    slot_info = slots_transmitted[i]
                    #search for ues_transmit position to bitflip correct bits
                    for val in ues_transmit:
                        if val[0] is slot_info[1] and val[1] is slot_info[2]:
                            positions[i] = val[4]

            translationData[str(key)]["positions"] = positions

            #Create some permutations of the input
            while len(datat) < model.numReqs:
                datat += [model.filler_input]


            translationData[str(key)]["datat"] = datat

            dataLog  = []
            dataLog2 = []
            #perms = list(permutations(range(len(datat)), len(datat)))
            permutationIterator = permutations(range(len(datat)), len(datat))
            perms = [next(permutationIterator) for _ in range(10000)]

            permsList = random.sample(perms, 500)
            permsList2 = random.sample(perms, 50)
            translationData[str(key)]["perms"] = permsList
            translationData[str(key)]["perms2"] = permsList2


            for permutation in permsList:
                data = []
                target = []
                for t in permutation:
                    data += datat[t]

                for i in range(model.numSlots):
                    bang = [0]*model.numReqs
                    if i in positions:
                        bang[permutation.index(positions[i])] = 1
                    target += bang

                dataLog += [[data, target]]

            for permutation in permsList2:
                data = []
                target = []
                for t in permutation:
                    data += datat[t]

                for i in range(model.numSlots):
                    bang = [0]*model.numReqs
                    if i in positions:
                        bang[permutation.index(positions[i])] = 1
                    target += bang

                dataLog2 += [[data, target]]

            train_loader += dataLog
            test_loader  += dataLog2

        with open(translationDataFile, "wb") as file:
            pickle.dump(translationData, file)

        with open(trainLoaderFile, "wb") as file:
            pickle.dump(train_loader, file)

        with open(testLoaderFile, "wb") as file:
            pickle.dump(test_loader, file)

    else:
        with open(trainLoaderFile, "rb") as file:
            train_loader = pickle.load(file)
        with open(testLoaderFile, "rb") as file:
            test_loader = pickle.load(file)

    #Train nn
    train(train_loader, test_loader, args)

    #Dump nn
    model.save("fusion_model.pt")
    pass



if __name__ == '__main__':
    main()

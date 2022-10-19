//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 10/15/2022.
//

#ifndef NS3_ORAN_3GPP_MEASUREMENTS_H
#define NS3_ORAN_3GPP_MEASUREMENTS_H

#include <string>
#include <map>

enum FeatureImplemented
{
    NOTIMPLEMENTED = 0,
    IMPLEMENTED
};

enum MeasurementType
{
    INTEGER,
    REAL,
    NONE
};

const std::map<std::string,
               std::tuple<enum MeasurementType, std::string, enum FeatureImplemented>
               > m_defaultEndpointsKpmTypeAndUnit =
{
    // Measurements defined in ORAN WG3 E2SM KPM v02.02
    {"DRB.PdcpSduVolumeDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.PdcpSduVolumeUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"QosFlow.PdcpPduVolumeDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"QosFlow.PdcpPduVolumeUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"QosFlow.PdcpSduVolumeDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"QosFlow.PdcpSduVolumeUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.PdcpSduVolumeX2DL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.PdcpSduVolumeX2UL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.F1uPdcpSduVolumeDL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.X2uPdcpSduVolumeDL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.F1uPdcpSduVolumeUL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.X2uPdcpSduVolumeUL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"QF.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
    {"QF.SessionTimeUE.Qos", {INTEGER, "s", NOTIMPLEMENTED}},
    {"QF.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
    {"QF.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
    {"ERAB.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
    {"ERAB.SessionTimeQCI.QCI", {INTEGER, "s", NOTIMPLEMENTED}},
    {"DRB.IPThpUL.QCI", {REAL, "Kbit", NOTIMPLEMENTED}},
    // NR
    {"DRB.PdcpSduVolumeXnDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.PdcpSduVolumeXnUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.XnuPdcpSduVolumeDL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"DRB.XnuPdcpSduVolumeUL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
    {"QF.SessionTimeUE.5QI", {INTEGER, "s", NOTIMPLEMENTED}},
    {"QF.SessionTimeUE.SNSSAI", {INTEGER, "s", NOTIMPLEMENTED}},

    // Measurements defined in 3GPP TS 32.425 version 14.1.0 Release 14
    // 4.1-
    // Act = Active
    // Alloc = Allocation
    // AOA = Angle of arrival
    // Att = Attempt
    // Conn = Connection
    // Ded = Dedicated
    // EE = Energy Efficiency
    // Err = Error
    // Estab = Establish(ment)
    // Fail = Fail(ed/ure)
    // Ho = Handover
    // La = Location Area
    // Inc = Incoming
    // Out = Outgoing
    // Nbr = Number
    // Prep = Prepar(e/ation)
    // Succ = Success

    // 4 Measurements related to eNodeB, donor eNodeB and relay node
    // 4.1 RRC Connection Related Measurements
    // 4.1.1 RRC Connection Establishment
    {"RRC.ConnEstabAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnEstabSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnEstabFail.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnEstabFaileNBCause.Congestion", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnEstabFaileNBCause.Unspecified", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnEstabFaileNBCause.EnergySaving", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.1.2 RRC Connection Re-Establishment
    {"RRC.ConnReEstabAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnReEstabSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnReEstabFail.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.1.3 RRC Connection Number
    {"RRC.ConnMean", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnMax", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.1.4 RRC Connection Setup Time
    {"RRC.ConnEstabTimeMean.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRC.ConnEstabTimeMax.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.1.5 UE Context Release
    {"UECNTX.RelReq.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"UECNTX.RelSuccNbr", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRCConn.Setup.TimeBin", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.2 E-RAB Measurements
    // 4.2.1 E-RAB Setup
    {"ERAB.EstabInitAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabInitSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabInitFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabAddAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabAddSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabAddFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabTimeMean.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabTimeMax.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabIncHoAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.EstabIncHoSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.2.2 E-RAB Release
    {"ERAB.RelEnbNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.RelEnbNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.RelAttrNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.RelSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.RelFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.RelActNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.2.3 E-RAB Modification
    {"ERAB.ModQosAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.ModQosSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"ERAB.ModQosFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.2.4 E-RAB Activity
    {"ERAB.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}}, // periodicity 100ms
    {"ERAB.SessionTimeQCI.QCI", {INTEGER, "s", NOTIMPLEMENTED}}, // periodicity 100ms
    // 4.2.5 E-RAB Number
    {"ERAB.UsageNbrMean.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // mean simultaneous e-RABs in a period
    {"ERAB.UsageNbrMax.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // mean simultaneous e-RABs in a period
    // 4.3 Handover Related Measurements
    // 4.3.1 Intra-RAT Handovers
    // 4.3.1.1 Intra-eNB/RN Handover Related Measurements
    {"HO.IntraEnbOutAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // RRCConnectionReconfigurationMessage added to handover
    {"HO.IntraEnbOutSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // RRCConnectionReconfigurationCompleteMessage added to handover
    {"HO.IntraDenbOutPrepToRnAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // X2AP HANDOVER_REQUEST added to handover
    {"HO.IntraDenbOutToRnAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // RRCConnectionReconfigurationMessage added to handover
    {"HO.IntraDenbOutToRnSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // X2AP UE_CONTEXT_RELEASE added to thandover
    // 4.3.1.2 Inter-eNB Handover Related Measurements
    {"HO.InterEnbOutPrepAtt", {INTEGER, "", NOTIMPLEMENTED}}, // X2AP HANDOVER_REQUEST + S1AP HANDOVER_REQUIRED
    {"HO.InterEnbOutAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // RRC ConnectionConfigurationMessage
    {"HO.InterEnbOutSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // X2AP UE_CONTEXT_RELEASE
    // 4.3.1.3 Handover Measurements On Neighbour Cell Basis
    {"HO.OutAttTarget.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // X2AP HANDOVER_REQUEST + S1AP HANDOVER_REQUIRED
    {"HO.OutSuccTarget.Cause", {INTEGER, "", NOTIMPLEMENTED}}, // RRC ConnectionConfigurationMessage
    {"HO.OutFail.TooEarly", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutFail.TooLate", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutFail.TooLateOwnNotCrossed", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutFail.TooLateNeighborNotCrossed", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutFail.ToWrongCell", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutFail.HwcReestablish", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.3.1.4 Intra/Inter-frequency Handover Related Measurements
    {"HO.IntraFreqOutAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.IntraFreqOutSucc", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.InterFreqMeasGapOutAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.InterFreqMeasGapOutSucc", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.InterFreqNoMeasGapOutAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.InterFreqMeasGapOutSucc", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.3.1.5 Handover Related Measurements for DRX/non-DRX
    {"HO.DrxOutAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.DrxOutSucc", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.NoDrxOutAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.NoDrxOutSucc", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.3.1.6 Handover To Cells Outside The RN Related Measurements
    {"HO.OutRNOutPrepAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutRNOutAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.OutRNOutSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.3.1.7 Handover Triggering Measurements
    {"HO.SrcCellQual.RSRP", {INTEGER, "dBm", IMPLEMENTED}},
    {"HO.SrcCellQual.RSRQ", {INTEGER, "dB", IMPLEMENTED}},
    {"HO.TrgtCellQual.RSRP", {INTEGER, "dBm", IMPLEMENTED}},
    {"HO.TrgtCellQual.RSRQ", {INTEGER, "dB", IMPLEMENTED}},
    // 4.3.2 Inter-RAT Handovers
    {"HO.IartOutAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.IartOutSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}},
    {"HO.IartOutUnnecessaryFromEutran", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.4 Cell Level Radio Bearer QoS Related Measurements
    // 4.4.1 Cell PDCP SDU Bit-rate
    {"DRB.PdcpSduBitrateDl.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // user plane
    {"DRB.PdcpSduBitrateUl.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // user plane
    {"DRB.PdcpSduBitrateDlMax.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // user plane
    {"DRB.PdcpSduBitrateUlMax.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // user plane
    {"SRB.PdcpSduBitrateDl.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // control plane
    {"SRB.PdcpSduBitrateUl.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // control plane
    // 4.4.2 Active UEs
    {"DRB.UEActiveDl.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"DRB.UEActiveUl.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.4.3 Packet Delay And Drop Rate
    {"DRB.PdcpSduDelayDl.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"DRB.PdcpSduDropRateDl.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.4.4 Packet Loss Rate
    {"DRB.PdcpSduAirLossRateDl.QCI", {INTEGER, "", NOTIMPLEMENTED}},
    {"DRB.PdcpSduAirLossRateUl.QCI", {INTEGER, "", NOTIMPLEMENTED}}, // the standard doesn't use Air for UL, which is weird
    // 4.4.5 IP Latency Measurements
    {"DRB.IpLateDl.QCI", {INTEGER, "ms", NOTIMPLEMENTED}},
    // 4.4.6 IP Throughput Measurements
    {"DRB.IpThpDl.QCI", {INTEGER, "kbps", NOTIMPLEMENTED}},
    {"DRB.IpThpUl.QCI", {INTEGER, "kbps", NOTIMPLEMENTED}},
    {"DRB.IpVolDl.QCI", {INTEGER, "kbps", NOTIMPLEMENTED}},
    {"DRB.IpVolUl.QCI", {INTEGER, "kbps", NOTIMPLEMENTED}},
    {"DRB.IpTimeDl.QCI", {INTEGER, "kbps", NOTIMPLEMENTED}},
    {"DRB.IpTimeUl.QCI", {INTEGER, "kbps", NOTIMPLEMENTED}},
    // 4.4.7 PDCP Data Volume Measurements
    // SKIPPING DUE TO CRAZY MEASUREMENT NAMES
    // 4.5 Radio Resource Utilization Related Measurements
    {"RRU.PrbDl.QCI", {INTEGER, "PRBs", NOTIMPLEMENTED}},
    {"RRU.PrbUl.QCI", {INTEGER, "PRBs", NOTIMPLEMENTED}},
    {"RRU.PrbTotDl", {INTEGER, "PRBs", NOTIMPLEMENTED}},
    {"RRU.PrbTotUl", {INTEGER, "PRBs", NOTIMPLEMENTED}},
    {"RRU.RachPreambleDedMean", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRU.RachPreambleAMean", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRU.RachPreambleBMean", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRU.RachPreambleDist.Bin", {INTEGER, "", NOTIMPLEMENTED}}, // number of bin
    {"RRU.RachAccessDelayDist.Bin", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRU.RachContentionReported", {REAL, "%", NOTIMPLEMENTED}},
    {"RRU.RachReportCount", {INTEGER, "", NOTIMPLEMENTED}},
    {"RRU.RachDedicatedPreamblesAssigned", {REAL, "%", NOTIMPLEMENTED}},
    // 4.5.6 Cell Unavailable Time
    {"RRU.CellUnavailableTime", {INTEGER, "s", NOTIMPLEMENTED}},
    // 4.5.7 TB Related Measurements
    {"TB.TotNbrDl", {INTEGER, "s", NOTIMPLEMENTED}},
    {"TB.ErrNbrDl", {INTEGER, "s", NOTIMPLEMENTED}},
    {"TB.TotNbrUl", {INTEGER, "s", NOTIMPLEMENTED}},
    {"TB.ErrNbrUl", {INTEGER, "s", NOTIMPLEMENTED}},
    // 4.5.8 Power Utilization Measurements
    {"CARR.MaxTxPwr", {REAL, "dBm", NOTIMPLEMENTED}},
    {"CARR.AvgTxPwr", {REAL, "dBm", NOTIMPLEMENTED}},
    // 4.5.9 PRB Full Utilisation
    {"RRU.PrbCongestionDl", {INTEGER, "%", NOTIMPLEMENTED}},
    {"RRU.PrbCongestionUl", {INTEGER, "%", NOTIMPLEMENTED}},
    // 4.6 UE-associated Logical S1-Connection Related Measurements
    {"S1SIG.ConnEstabAtt", {INTEGER, "", NOTIMPLEMENTED}},
    {"S1SIG.ConnEstabSucc", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.7 Paging Related Measurements
    {"PAG.DiscardedNbr", {INTEGER, "", NOTIMPLEMENTED}}, // X == (T/N)*(UE_RNTI % N) && Y == floor(UE_RNTI/N) % N && max_paging_records_queue.isFull()
    {"PAG.ReceivedNbr", {INTEGER, "", NOTIMPLEMENTED}},
    // 4.8 Measurements Related To Equipment Resources
    // 4.8.1 eNodeB/RN processor usage
    // 4.9 Common LAs of overlapping RATs Coverag
    {"RRC.IratIncMobility.LAI", {INTEGER, "", NOTIMPLEMENTED}}, // LAI = LA Identifier of RAT serving UE from RRCConnectionSetupComplete
    // 4.10 RF Measurements
    // 4.10.1 CQI Distribution
    {"CARR.WBCQIDist.Bin", {INTEGER, "", NOTIMPLEMENTED}}, // Bin = CQI value 0-15
    {"CARR.AvgSubCQI.SubbandX", {REAL, "", NOTIMPLEMENTED}}, // X = subband index
    // 4.10.2 Timing Advance Distribution
    // SKIPPING DUE TO IT BEING CONFUSING https://www.sharetechnote.com/html/Handbook_LTE_ServCellID_SCellID.html
    // 4.11 SCell Scheduling Related Measurements in CA
    // 4.11.1 Attempted PUCCH Allocations For SCell Scheduling In Carrier Aggregation
    // 4.11.2 Successful PUCCH Allocations For SCell Scheduling In Carrier Aggregation
    // 4.11.3 Failed PUCCH Allocations for SCell Scheduling In Carrier Aggregation
    // 5 Measurements Related To Relay Node
    // UNINTERESTING
    // 6 Measurements Related To Measurement Report
    // 6.1 RSRP Related Measurements
            /**
             * c) Receipt by the eNodeB from the UE of MeasurementReport message indicating a periodical UE measurement
             * report where IE MeasResults field includes rsrpResult. The event triggered MeasurementReport messages are excluded.
             * This measurement shall be increased for each reported value RSRP_LEV (See in 3GPP TS 36.331
             * [18]). For every one or two or 17 or 20 RSRP_LEV(s) a separate measurement is defined. (See in 3GPP TS
             * 36.133 [19])
             * d) Each measurement is an integer value.
             * e) MR.Rsrp.y . y is an integer from 00 to 47.
             * Note:
             * 00 of y indicates from RSRP _LEV _00 to RSRP _LEV _LEV _20, namely RSRP < -120dBm,
             * 01 of y indicates RSRP _LEV _21 and RSRP _LEV _25, namely -120 ≤ RSRP < -115dBm,
             * 02 of y indicates RSRP _LEV _26, namely -115≤ RSRP < -114dBm,
             * 03 of y indicates RSRP _LEV _27, namely -114≤ RSRP < -113dBm
             * …
             * 36 of y indicates RSRP _LEV _60, namely -81 ≤ RSRP < -80dBm,
             * 37 of y indicates RSRP _LEV _61, RSRP _LEV _62, namely -80 ≤ RSRP < -78dBm,
             * 38 of y indicates RSRP _LEV _63, RSRP _LEV _64, namely -78 ≤ RSRP < -76dBm,
             * …
             * 46 of y indicates from RSRP _LEV _79 to RSRP _LEV _80, namely -62 ≤ RSRP < -60dBm,
             * 47 of y indicates from RSRP _LEV _81 to RSRP _LEV _97, namely -60dBm ≤ RSRP. (See in 3GPP TS36.133
             * [19])
             */
    // 6.2 RSRQ Related Measurements
            /**
             * Receipt by the eNodeB from the UE of MeasurementReport message indicating a periodical UE measurement
             * report where IE MeasResults field includes rsrqResult. The event triggered MeasurementReport messages are
             * excluded. This measurement shall be increased for each reported value RSRQ_LEV (See in 3GPP TS 36.331
             * [18]). For every one or two RSRQ_LEV(s) a separate measurement is defined. (See in 3GPP TS 36.133 [19])
             * d) Each measurement is an integer value.
             * e) MR. Rsrq.y y is an integer from 00 to 17.
             * Note:
             * 00 of y indicates RSRQ_00, namely RSRQ < -19.5dB,
             * 01 of y indicates RSRQ_01 and RSRQ_02, namely -19.5 ≤ RSRQ < -18.5dB,
             * 02 of y indicates RSRQ_03 and RSRQ_04, namely -18.5 ≤ RSRQ < -17.5dB,
             * …
             * 16 of y indicates RSRQ_31 and RSRQ_32, namely -4.5 ≤ RSRQ < -3.5dB,
             * 17 of y indicates RSRQ_33 and RSRQ_34, namely -3.5dB ≤ RSRQ ,
             * (See in 3GPP TS36.133 [19])
             */
    // 6.3 UE Power Headroom Related Measurements
            /**
             * c) Receipt by the eNodeB from the UE of Power Headroom Report message indicating a periodical UE
             * measurement POWER_HEADROOM report. This measurement shall be increased for each reported value
             * POWER_HEADROOM (See in 3GPP TS 36.321 [16]). For every one POWER_HEADROOM (s) a separate
             * measurement is defined. (See in 3GPP TS 36.133 [19]).
             * d) Each measurement is an integer value.
             * e) MR.PowerHeadRoom.y . y is an integer from 00 to 63.
             * Note:
             * 00 of y indicates POWER_HEADROOM_00, namely -23 ≤ PH < -22,
             * 01 of y indicates POWER_HEADROOM_01, namely -22 ≤ PH < -21,
             * …
             * 63 of y indicates POWER_HEADROOM_63, namely PH≥40. (See in 3GPP TS36.133 [19])
             */
    // 6.4 UE Rx-Tx Time Difference Related Measurements
            /**
             * Receipt by the eNodeB from the UE of MeasurementReport message indicating a periodical UE measurement
             * report where IE MeasResults field includes ue-RxTxTimeDiffResult. The event triggered MeasurementReport
             * messages are excluded. This measurement shall be increased for each reported value RXTX_TIME_DIFFERENCE
             * (See in 3GPP TS 36.331 [18]).
             * For every 5 or 20 or 100 or 524 RXTX_TIME_DIFFERENCEs a separate measurement is defined. (See in 3GPP TS 36.133 [19])
             * d) Each measurement is an integer value.
             * e) MR.RxTxTimeDiff.y y is an integer from 00 to 47
             * Note:
             * 00 of y indicates from RX-TX_TIME_DIFFERENCE_0000 to RX-TX_TIME_DIFFERENCE_0004, namely 0
             * Ts ≤ TUE Rx-Tx< 10 Ts,
             * …
             * 19 of y indicates from RX-TX_TIME_DIFFERENCE_0095 to RX-TX_TIME_DIFFERENCE_0099, namely
             * 190Ts ≤ TUE RX-TX< 200 Ts,
             * 20 of y indicates from RX-TX_TIME_DIFFERENCE_0100 to RX-TX_TIME_DIFFERENCE_0119, namely
             * 200Ts ≤ TUE RX-TX< 240 Ts,
             * …
             * 39 of y indicates from RX-TX_TIME_DIFFERENCE_0480 to RX-TX_TIME_DIFFERENCE_0499, namely
             * 960Ts ≤ TUE RX-TX< 1000 Ts,
             * 40 of y indicates from RX-TX_TIME_DIFFERENCE_0500 to RX-TX_TIME_DIFFERENCE_0599, namely
             * 1000Ts ≤ TUE RX-TX< 1200 Ts,
             * 44 of y indicates from RX-TX_TIME_DIFFERENCE_0900 to RX-TX_TIME_DIFFERENCE_0999, namely
             * 1800Ts ≤ TUE RX-TX< 2000 Ts,
             * 45 of y indicates from RX-TX_TIME_DIFFERENCE_1000 to RX-TX_TIME_DIFFERENCE_1523, namely
             * 2000Ts ≤ TUE RX-TX< 3048 Ts,
             * 46 of y indicates from RX-TX_TIME_DIFFERENCE_1524 to RX-TX_TIME_DIFFERENCE_2047, namely
             * 3048 Ts ≤ TUE RX-TX< 4096 Ts,
             * 47 of y indicates from RX-TX_TIME_DIFFERENCE_2048 to RX-TX_TIME_DIFFERENCE_4095, namely
             * 4096 Ts ≤ TUE RX-TX
             * (See in 3GPP TS36.133[20])
             */
    // 6.5 AOA Related Measurements
        /**
         * c) Receipt by the eNodeB from the UE of MeasurementReport message indicating a periodical UE
         * measurement report where IE MeasResults field includes aoaResult. The event triggered MeasurementReport
         * messages are excluded. This measurement shall be increased for each reported value AOA_ANGLE (See in
         * 3GPP TS 36.331 [18]). For every 5 AOA_ANGLE (s) a separate measurement is defined. (See in 3GPP TS
         * 36.133 [19])
         * Note: antenna deployment.
         * Note: this measurement is only valid for eNodeB with antenna array.
         * d) Each measurement is an integer value.
         * e) MR.EutranAOA.y y is an integer from 00 to 71.
         * Note:
         *  00 of y indicates from AOA_ANGLE _000 to AOA_ANGLE_009, namely 0 ≤ AOA_ANGLE < 5 degree,
         * …
         * 71 of y indicates from AOA_ANGLE _710 to AOA_ANGLE _719, namely 355 ≤ AOA_ANGLE < 360
         * degree. (See in 3GPP TS36.133 [19])
         */
};

#endif // NS3_ORAN_3GPP_MEASUREMENTS_H

import pandas as pd
import numpy as np
import math

ues=1
enb=1
dur=5
pkt=2000
interval_us = 100
interval = interval_us/1000

local="./5gsim_n" + str(ues) + "_p" + str(pkt) + "_i" + "{:.1f}".format(interval_us) + "/"
arq_app="5grange_app_trace.txt"
arq_phy="5grange_phy_trace.txt"
arq_p2p_enb="p2p_ascii_enb.txt"
arq_p2p_remote="p2p_ascii_remote.txt"

data_p2p_remote=pd.read_csv(local+arq_p2p_remote,sep=' ',header=None,usecols=[0,1])
data_p2p_enb=pd.read_csv(local+arq_p2p_enb,sep=' ',header=None,usecols=[0,1])
data_app = pd.read_csv(local+arq_app)
data_phy = pd.read_csv(local+arq_phy)

data_p2p_remote_sent=data_p2p_remote[data_p2p_remote[0]=='-']

pkts_enviados=data_p2p_remote_sent[0].count()
tempo_inicio_envio_p2p=data_p2p_remote_sent[1].agg('min')
tempo_fim_envio_p2p=data_p2p_remote_sent[1].agg('max')
dur_p2p=tempo_fim_envio_p2p-tempo_inicio_envio_p2p


pkts_recebidos_p2p=data_p2p_enb[data_p2p_enb[0]=='r'].count().agg('sum')
bits_enviados=float(pkts_enviados)*pkt*8
bits_esperados_app=bits_enviados
bits_esperados_phy=(float(pkt)+32)*8*pkts_enviados
vazao_gerada_app=bits_enviados/dur_p2p/1.0e6
vazao_gerada_phy=bits_esperados_phy/dur_p2p/1.0e6


phy_stats = data_phy.groupby(['node','channel', 'rxtx','status']).agg('sum')
app_stats = data_app.groupby(['node','channel', 'rxtx','status']).agg('sum')


app_rec_inicio=data_app['time'].agg('min')
app_rec_inicio=float(app_rec_inicio[1:-2])/1.0e9

app_rec_fim=data_app['time'].agg('max')
app_rec_fim=float(app_rec_fim[1:-2])/1.0e9

app_dur=app_rec_fim-tempo_inicio_envio_p2p

phy_dl_pkts_recebidos_ok=phy_stats.xs('UE').xs('DL').xs('RX').xs('OK').qtd_pkts
#phy_dl_pkts_recebidos_erro=phy_stats.xs('UE').xs('DL').xs('RX').xs('ERRO').qtd_pkts
phy_dl_bits_recebidos_ok=phy_stats.xs('UE').xs('DL').xs('RX').xs('OK')['size'] * 8
#phy_dl_bits_recebidos_erro=phy_stats.xs('UE').xs('DL').xs('RX').xs('ERRO')['size'] * 8
phy_dl_vazao=phy_dl_bits_recebidos_ok/app_dur/1.0e6


app_dl_bits_recebidos=app_stats.xs('UE').xs('--').xs('RX').xs('OK')['size'] * 8
app_dl_vazao=app_dl_bits_recebidos/app_dur/1.0e6

'''
phy_ul_pkts_recebidos_ok=phy_stats.xs('UE').xs('UL').xs('RX').xs('OK').qtd_pkts
phy_ul_pkts_recebidos_erro=phy_stats.xs('UE').xs('UL').xs('RX').xs('ERRO').qtd_pkts
phy_ul_bits_recebidos_ok=phy_stats.xs('UE').xs('UL').xs('RX').xs('OK')['size'] * 8
phy_ul_bits_recebidos_erro=phy_stats.xs('UE').xs('UL').xs('RX').xs('ERRO')['size'] * 8
phy_ul_vazao=phy_ul_bits_recebidos_ok/dur
'''

print("Simulação")
print("UEs: " + str(ues))
print("eNB: " + str(enb))
print("Duração: " + str(app_dur) + "s")
print("Tamanho do pacote: " + str(pkt) + " bytes")
print("Intervalo: " + str(interval) + " ms")
print("Pacotes enviados: " + str(pkts_enviados))
print("Vazão gerada APP: " + str(vazao_gerada_app) + " mbps")
print("Vazão esperada PHY: " + str(vazao_gerada_phy) + " mbps")
print("Duração PP: " + str(app_dur))

print("--")

print("Stats PHY")
print(phy_stats)
print("ENB  P2P     RX   OK       "+ str(pkts_recebidos_p2p))
print("DL Pacotes recebidos: " + str(phy_dl_pkts_recebidos_ok))
print()
print("DL Bits recebidos: " + str(phy_dl_bits_recebidos_ok))
print("DL Vazão: " + str(phy_dl_vazao) + "mbps")
print("% vazão alcançada: " + "{:.2f}".format(phy_dl_vazao*100/vazao_gerada_phy) + "%")
print("Gerada: ")
print("--")
print("Stats APP")
print(app_stats)
print("Bits recebidos: " + str(app_dl_bits_recebidos))
print("Vazão: " + str(app_dl_vazao) + "mbps")
print("% vazão alcançada: " + "{:.2f}".format(app_dl_vazao*100/vazao_gerada_app) + "%")
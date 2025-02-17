# scenario 1
./ns3 run "HandoverXappsScenario --scenario=5 --outputFile=0_outputRlRicInitiated.csv"

python3 ./src/oran/PlotKpmsJson.py
python3 ./src/oran/examples/PlotUeThrLogJson.py

mv kpms.png triangle_kpms.png
mv ueThrLog.png triangle_ueThrLog.png

#scenario 2
./ns3 run "HandoverXappsScenario  --scenario=5 --stride=\"opposite_senoids\""


python3 ./src/oran/PlotKpmsJson.py
python3 ./src/oran/examples/PlotUeThrLogJson.py

mv kpms.png opp_senoids_kpms.png
mv ueThrLog.png opp_senoids_ueThrLog.png

#scenario 3
./ns3 run "HandoverXappsScenario  --scenario=5 --stride=\"offset_senoids\""

python3 ./src/oran/PlotKpmsJson.py
python3 ./src/oran/examples/PlotUeThrLogJson.py

mv kpms.png offset_senoids_kpms.png
mv ueThrLog.png offset_senoids_ueThrLog.png

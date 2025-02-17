mkdir results
rm *.csv
python3 HandoverXappsScenarioCompanion.py
mv consolidated.csv results/triangle_consolidated.csv
rm *.csv


python3 HandoverXappsScenarioCompanion.py "--stride="opposite_senoids""
mv consolidated.csv results/opp_senoids_consolidated.csv
rm *.csv


python3 HandoverXappsScenarioCompanion.py "--stride="offset_senoids""
mv consolidated.csv results/offset_senoids_consolidated.csv
rm *.csv

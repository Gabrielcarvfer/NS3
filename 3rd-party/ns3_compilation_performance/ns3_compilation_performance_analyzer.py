"""
Configure gcc with -ftime-report and run "make -j1 > compile_targets.txt 2> time_reports.txt"
Yes, -j1 will take a long time, but you really want these results to analyze your compilation time,
don't you?
"""
sample_compile_target = """
[ 12%] Building CXX object src/internet/CMakeFiles/ns3.30.1-internet-reldeb-obj.dir/model/icmpv4.cc.o
[ 12%] Building CXX object src/internet/CMakeFiles/ns3.30.1-internet-reldeb-obj.dir/model/icmpv4-l4-protocol.cc.o
"""
sample_time_report = """

Time variable                                   usr           sys          wall               GGC
 phase setup                        :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)    1478 kB (  2%)
 phase parsing                      :   0.31 ( 46%)   0.17 ( 85%)   0.48 ( 55%)   55432 kB ( 71%)
 phase lang. deferred               :   0.03 (  4%)   0.00 (  0%)   0.03 (  3%)    4287 kB (  5%)
 phase opt and generate             :   0.32 ( 48%)   0.03 ( 15%)   0.35 ( 40%)   16635 kB ( 21%)
 phase last asm                     :   0.01 (  1%)   0.00 (  0%)   0.01 (  1%)     769 kB (  1%)
 |name lookup                       :   0.05 (  7%)   0.02 ( 10%)   0.04 (  5%)    2468 kB (  3%)
 |overload resolution               :   0.05 (  7%)   0.00 (  0%)   0.05 (  6%)    4217 kB (  5%)
 dump files                         :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)       0 kB (  0%)
 callgraph construction             :   0.01 (  1%)   0.00 (  0%)   0.01 (  1%)    2170 kB (  3%)
 callgraph optimization             :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)       1 kB (  0%)
 ipa inlining heuristics            :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)     227 kB (  0%)
 ipa pure const                     :   0.00 (  0%)   0.00 (  0%)   0.02 (  2%)       0 kB (  0%)
 ipa icf                            :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 ipa SRA                            :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)     396 kB (  1%)
 trivially dead code                :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 df reaching defs                   :   0.02 (  3%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 df live regs                       :   0.03 (  4%)   0.00 (  0%)   0.01 (  1%)       2 kB (  0%)
 df live&initialized regs           :   0.01 (  1%)   0.00 (  0%)   0.01 (  1%)       0 kB (  0%)
 df reg dead/unused notes           :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)     115 kB (  0%)
 register information               :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 preprocessing                      :   0.05 (  7%)   0.06 ( 30%)   0.10 ( 11%)    1751 kB (  2%)
 parser (global)                    :   0.06 (  9%)   0.03 ( 15%)   0.07 (  8%)   16303 kB ( 21%)
 parser struct body                 :   0.06 (  9%)   0.04 ( 20%)   0.08 (  9%)   12525 kB ( 16%)
 parser enumerator list             :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)     112 kB (  0%)
 parser function body               :   0.02 (  3%)   0.02 ( 10%)   0.02 (  2%)    3039 kB (  4%)
 parser inl. func. body             :   0.03 (  4%)   0.00 (  0%)   0.01 (  1%)    2024 kB (  3%)
 parser inl. meth. body             :   0.02 (  3%)   0.01 (  5%)   0.06 (  7%)    5792 kB (  7%)
 template instantiation             :   0.09 ( 13%)   0.01 (  5%)   0.13 ( 15%)   12274 kB ( 16%)
 constant expression evaluation     :   0.00 (  0%)   0.00 (  0%)   0.03 (  3%)      66 kB (  0%)
 integration                        :   0.02 (  3%)   0.00 (  0%)   0.02 (  2%)    2119 kB (  3%)
 tree gimplify                      :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)     726 kB (  1%)
 tree tail merge                    :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)      21 kB (  0%)
 tree VRP                           :   0.03 (  4%)   0.00 (  0%)   0.00 (  0%)     189 kB (  0%)
 tree PTA                           :   0.01 (  1%)   0.01 (  5%)   0.00 (  0%)      60 kB (  0%)
 tree PHI insertion                 :   0.00 (  0%)   0.01 (  5%)   0.00 (  0%)      40 kB (  0%)
 tree operand scan                  :   0.01 (  1%)   0.00 (  0%)   0.02 (  2%)     835 kB (  1%)
 dominator optimization             :   0.00 (  0%)   0.01 (  5%)   0.02 (  2%)     125 kB (  0%)
 tree CCP                           :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)      56 kB (  0%)
 tree backward propagate            :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)       0 kB (  0%)
 tree DSE                           :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)       3 kB (  0%)
 tree SSA uncprop                   :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)       0 kB (  0%)
 dominance computation              :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)       0 kB (  0%)
 out of ssa                         :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)       4 kB (  0%)
 expand                             :   0.01 (  1%)   0.00 (  0%)   0.01 (  1%)    1236 kB (  2%)
 CSE                                :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)      26 kB (  0%)
 dead store elim1                   :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)      37 kB (  0%)
 dead store elim2                   :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)      51 kB (  0%)
 CPROP                              :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)     112 kB (  0%)
 PRE                                :   0.00 (  0%)   0.00 (  0%)   0.02 (  2%)      39 kB (  0%)
 CSE 2                              :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)      12 kB (  0%)
 combiner                           :   0.02 (  3%)   0.00 (  0%)   0.00 (  0%)     123 kB (  0%)
 integrated RA                      :   0.02 (  3%)   0.00 (  0%)   0.02 (  2%)    1198 kB (  2%)
 LRA non-specific                   :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)      23 kB (  0%)
 LRA create live ranges             :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)       4 kB (  0%)
 hard reg cprop                     :   0.00 (  0%)   0.00 (  0%)   0.02 (  2%)       3 kB (  0%)
 final                              :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)     756 kB (  1%)
 symout                             :   0.01 (  1%)   0.00 (  0%)   0.02 (  2%)    8114 kB ( 10%)
 var-tracking emit                  :   0.00 (  0%)   0.00 (  0%)   0.01 (  1%)     382 kB (  0%)
 straight-line strength reduction   :   0.01 (  1%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 rest of compilation                :   0.02 (  3%)   0.00 (  0%)   0.02 (  2%)     139 kB (  0%)
 TOTAL                              :   0.67          0.20          0.88          78612 kB

Time variable                                   usr           sys          wall               GGC
 phase setup                        :   0.00 (  0%)   0.00 (  0%)   0.00 (  0%)    1478 kB (  1%)
 phase parsing                      :   0.46 ( 19%)   0.32 ( 58%)   0.78 ( 26%)  100901 kB ( 47%)
 phase lang. deferred               :   0.07 (  3%)   0.01 (  2%)   0.09 (  3%)   11742 kB (  6%)
 phase opt and generate             :   1.82 ( 75%)   0.22 ( 40%)   2.04 ( 68%)   94797 kB ( 45%)
 phase last asm                     :   0.08 (  3%)   0.00 (  0%)   0.07 (  2%)    4020 kB (  2%)
 phase finalize                     :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 |name lookup                       :   0.07 (  3%)   0.04 (  7%)   0.13 (  4%)    3947 kB (  2%)
 |overload resolution               :   0.07 (  3%)   0.02 (  4%)   0.12 (  4%)   11597 kB (  5%)
 dump files                         :   0.00 (  0%)   0.01 (  2%)   0.02 (  1%)       0 kB (  0%)
 callgraph construction             :   0.03 (  1%)   0.00 (  0%)   0.04 (  1%)    6625 kB (  3%)
 callgraph optimization             :   0.02 (  1%)   0.00 (  0%)   0.03 (  1%)       6 kB (  0%)
 ipa function summary               :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)     434 kB (  0%)
 ipa cp                             :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)     327 kB (  0%)
 ipa inlining heuristics            :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)    1084 kB (  1%)
 ipa reference                      :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 ipa icf                            :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 ipa SRA                            :   0.02 (  1%)   0.01 (  2%)   0.04 (  1%)    2518 kB (  1%)
 ipa free inline summary            :   0.00 (  0%)   0.01 (  2%)   0.00 (  0%)       0 kB (  0%)
 cfg cleanup                        :   0.02 (  1%)   0.00 (  0%)   0.04 (  1%)     212 kB (  0%)
 trivially dead code                :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 df scan insns                      :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       5 kB (  0%)
 df reaching defs                   :   0.04 (  2%)   0.00 (  0%)   0.02 (  1%)       0 kB (  0%)
 df live regs                       :   0.11 (  5%)   0.00 (  0%)   0.05 (  2%)      12 kB (  0%)
 df live&initialized regs           :   0.05 (  2%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 df must-initialized regs           :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 df use-def / def-use chains        :   0.02 (  1%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 df reg dead/unused notes           :   0.04 (  2%)   0.01 (  2%)   0.01 (  0%)     595 kB (  0%)
 alias analysis                     :   0.00 (  0%)   0.00 (  0%)   0.03 (  1%)    1147 kB (  1%)
 alias stmt walking                 :   0.01 (  0%)   0.03 (  5%)   0.02 (  1%)      96 kB (  0%)
 rebuild jump labels                :   0.00 (  0%)   0.00 (  0%)   0.02 (  1%)       0 kB (  0%)
 preprocessing                      :   0.07 (  3%)   0.08 ( 15%)   0.15 (  5%)    4701 kB (  2%)
 parser (global)                    :   0.07 (  3%)   0.05 (  9%)   0.17 (  6%)   30016 kB ( 14%)
 parser struct body                 :   0.03 (  1%)   0.05 (  9%)   0.11 (  4%)   16137 kB (  8%)
 parser function body               :   0.10 (  4%)   0.02 (  4%)   0.11 (  4%)    8338 kB (  4%)
 parser inl. func. body             :   0.01 (  0%)   0.02 (  4%)   0.03 (  1%)    3078 kB (  1%)
 parser inl. meth. body             :   0.07 (  3%)   0.04 (  7%)   0.04 (  1%)    7157 kB (  3%)
 template instantiation             :   0.16 (  7%)   0.06 ( 11%)   0.23 (  8%)   30374 kB ( 14%)
 constant expression evaluation     :   0.00 (  0%)   0.01 (  2%)   0.01 (  0%)     102 kB (  0%)
 early inlining heuristics          :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)     865 kB (  0%)
 inline parameters                  :   0.02 (  1%)   0.00 (  0%)   0.02 (  1%)    1798 kB (  1%)
 integration                        :   0.10 (  4%)   0.02 (  4%)   0.09 (  3%)   16124 kB (  8%)
 tree gimplify                      :   0.02 (  1%)   0.00 (  0%)   0.02 (  1%)    3248 kB (  2%)
 tree eh                            :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)     789 kB (  0%)
 tree CFG construction              :   0.00 (  0%)   0.00 (  0%)   0.00 (  0%)    1465 kB (  1%)
 tree CFG cleanup                   :   0.02 (  1%)   0.01 (  2%)   0.08 (  3%)      13 kB (  0%)
 tree tail merge                    :   0.01 (  0%)   0.00 (  0%)   0.02 (  1%)     218 kB (  0%)
 tree VRP                           :   0.02 (  1%)   0.01 (  2%)   0.03 (  1%)    1240 kB (  1%)
 tree Early VRP                     :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)     902 kB (  0%)
 tree copy propagation              :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)      10 kB (  0%)
 tree PTA                           :   0.01 (  0%)   0.01 (  2%)   0.05 (  2%)     354 kB (  0%)
 tree PHI insertion                 :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)     211 kB (  0%)
 tree SSA rewrite                   :   0.01 (  0%)   0.00 (  0%)   0.02 (  1%)    1149 kB (  1%)
 tree SSA other                     :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)     111 kB (  0%)
 tree SSA incremental               :   0.02 (  1%)   0.00 (  0%)   0.01 (  0%)     301 kB (  0%)
 tree operand scan                  :   0.03 (  1%)   0.01 (  2%)   0.03 (  1%)    3849 kB (  2%)
 dominator optimization             :   0.05 (  2%)   0.00 (  0%)   0.04 (  1%)    1126 kB (  1%)
 backwards jump threading           :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)      67 kB (  0%)
 tree CCP                           :   0.03 (  1%)   0.00 (  0%)   0.04 (  1%)     269 kB (  0%)
 tree PRE                           :   0.02 (  1%)   0.00 (  0%)   0.01 (  0%)     986 kB (  0%)
 tree FRE                           :   0.01 (  0%)   0.00 (  0%)   0.06 (  2%)     328 kB (  0%)
 tree backward propagate            :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 tree forward propagate             :   0.02 (  1%)   0.00 (  0%)   0.03 (  1%)     216 kB (  0%)
 tree phiprop                       :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 tree aggressive DCE                :   0.00 (  0%)   0.01 (  2%)   0.01 (  0%)    1036 kB (  0%)
 gimple CSE sin/cos                 :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 dominance computation              :   0.05 (  2%)   0.00 (  0%)   0.05 (  2%)       0 kB (  0%)
 expand vars                        :   0.02 (  1%)   0.00 (  0%)   0.00 (  0%)     332 kB (  0%)
 expand                             :   0.04 (  2%)   0.00 (  0%)   0.03 (  1%)    8000 kB (  4%)
 forward prop                       :   0.02 (  1%)   0.01 (  2%)   0.03 (  1%)     324 kB (  0%)
 CSE                                :   0.05 (  2%)   0.01 (  2%)   0.05 (  2%)     136 kB (  0%)
 dead store elim1                   :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)     233 kB (  0%)
 dead store elim2                   :   0.01 (  0%)   0.00 (  0%)   0.02 (  1%)     332 kB (  0%)
 loop analysis                      :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 loop init                          :   0.02 (  1%)   0.00 (  0%)   0.03 (  1%)    1358 kB (  1%)
 CPROP                              :   0.01 (  0%)   0.00 (  0%)   0.04 (  1%)     920 kB (  0%)
 PRE                                :   0.01 (  0%)   0.00 (  0%)   0.03 (  1%)     211 kB (  0%)
 CSE 2                              :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)      69 kB (  0%)
 branch prediction                  :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)     144 kB (  0%)
 combiner                           :   0.03 (  1%)   0.00 (  0%)   0.03 (  1%)     726 kB (  0%)
 if-conversion                      :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)      90 kB (  0%)
 integrated RA                      :   0.08 (  3%)   0.00 (  0%)   0.08 (  3%)    5257 kB (  2%)
 LRA non-specific                   :   0.03 (  1%)   0.00 (  0%)   0.03 (  1%)     196 kB (  0%)
 LRA virtuals elimination           :   0.04 (  2%)   0.00 (  0%)   0.00 (  0%)     236 kB (  0%)
 LRA reload inheritance             :   0.03 (  1%)   0.00 (  0%)   0.02 (  1%)     182 kB (  0%)
 LRA create live ranges             :   0.02 (  1%)   0.01 (  2%)   0.02 (  1%)      34 kB (  0%)
 LRA rematerialization              :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 reload CSE regs                    :   0.02 (  1%)   0.00 (  0%)   0.04 (  1%)     437 kB (  0%)
 ree                                :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)       6 kB (  0%)
 thread pro- & epilogue             :   0.02 (  1%)   0.00 (  0%)   0.02 (  1%)     367 kB (  0%)
 combine stack adjustments          :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)       0 kB (  0%)
 peephole 2                         :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)      89 kB (  0%)
 hard reg cprop                     :   0.01 (  0%)   0.00 (  0%)   0.01 (  0%)      14 kB (  0%)
 scheduling 2                       :   0.07 (  3%)   0.00 (  0%)   0.06 (  2%)     315 kB (  0%)
 reorder blocks                     :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)     290 kB (  0%)
 shorten branches                   :   0.02 (  1%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 final                              :   0.06 (  2%)   0.01 (  2%)   0.04 (  1%)    5102 kB (  2%)
 symout                             :   0.10 (  4%)   0.00 (  0%)   0.15 (  5%)   27649 kB ( 13%)
 variable tracking                  :   0.07 (  3%)   0.00 (  0%)   0.09 (  3%)    2393 kB (  1%)
 var-tracking dataflow              :   0.07 (  3%)   0.01 (  2%)   0.02 (  1%)      52 kB (  0%)
 var-tracking emit                  :   0.06 (  2%)   0.00 (  0%)   0.09 (  3%)    3217 kB (  2%)
 store merging                      :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)      17 kB (  0%)
 initialize rtl                     :   0.00 (  0%)   0.00 (  0%)   0.01 (  0%)      12 kB (  0%)
 rest of compilation                :   0.02 (  1%)   0.02 (  4%)   0.05 (  2%)     697 kB (  0%)
 remove unused locals               :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       2 kB (  0%)
 address taken                      :   0.01 (  0%)   0.00 (  0%)   0.00 (  0%)       0 kB (  0%)
 repair loop structures             :   0.00 (  0%)   0.01 (  2%)   0.00 (  0%)       0 kB (  0%)
 TOTAL                              :   2.43          0.55          2.99         212949 kB

"""

def parse_compile_target_time(compile_targets_contents=sample_compile_target, time_reports_contents=sample_time_report):
    #First we parse compile targets and group them per folder to analyze module compile times
    compile_targets = {}
    compile_target_group = {"children":{}, "total": 0.0}

    #Break entire content into lines
    compile_target_lines = compile_targets_contents.splitlines()
    time_report_lines = time_reports_contents.splitlines()
    j = 0 #used as an index for time_report lines, as each report may have a different number of lines

    #For each line
    for i in range(len(compile_target_lines)):
        #Ignore lines that are not building anything (linking/scanning)
        if compile_target_lines[i].find("Building") == -1:
            continue

        #Pick the target name (excluding building/linking stuff and language)
        target_name = compile_target_lines[i].split()[-1]

        #Break the target name into specific object and path
        target_name_components = target_name.split("/")
        target_name = target_name_components[-1]

        #Create an entry to store reported compile times
        compile_targets[target_name] = {"components": {}, "total" : 0.0}

        #Create a group structure for modules //todo: refactor
        if target_name_components[0] not in compile_target_group["children"]:
            compile_target_group["children"][target_name_components[0]] = {"children": {}, "total": 0.0}

        if target_name_components[1] not in compile_target_group["children"][target_name_components[0]]["children"]:
            compile_target_group["children"][target_name_components[0]]["children"][target_name_components[1]] = { "children" : {}, "total": 0.0}

        if target_name not in compile_target_group["children"][target_name_components[0]]["children"][target_name_components[1]]["children"]:
            compile_target_group["children"][target_name_components[0]]["children"][target_name_components[1]]["children"][target_name] = {"total": 0.0}

        #Skip possible error lines or blank lines until reach a line initiating with T (Time)
        while j < len(time_report_lines) and (len(time_report_lines[j]) < 1 or time_report_lines[j][0] != "T"):
            j+=1

        #Then skip the first line
        if j < len(time_report_lines):
            j+=1

        #After that we parse the compile times for each target
        while j < len(time_report_lines) and len(time_report_lines[j]) > 2:
            time_line_content = time_report_lines[j]

            #Get component name
            component_name, time_line_content = time_line_content.split(":")


            #Skip if subentry of previous component
            if component_name[1] == "|":
                j+=1
                continue

            #Stop if last line (TOTAL)
            if component_name.find("TOTAL") != -1:
                j+=2 #skip blank space between reports
                break

            #Clean component name
            name_components = []
            for name in component_name.split(" "):
                if len(name) > 1:
                    name_components += [name]
            component_name = " ".join(name_components)
            del name, name_components

            #We now have the 4 columns with user, system, wall and GCC info
            #I only want the wall time, if you want more, do it yourself

            #Break remaining content into 4 columns using the ")"
            time_line_content = time_line_content.split(")")

            #Get the wall column (3rd one = index 2)
            time_line_content = time_line_content[2]

            #Get rid of the weird percentages that doesn't really add up to 100%
            wall_time = float(time_line_content.split("(")[0])

            compile_targets[target_name]["components"][component_name] = wall_time
            j+=1
            del time_line_content


    #Return compile time results
    return compile_targets, compile_target_group

def main(test=False, forceReprocessing=False):
    import os
    import json

    compile_target_results = None
    
    #Skip processing if output file already exists
    if not os.path.exists("compile_target_time.json") or forceReprocessing:

        compile_target_contents, time_report_contents = None, None

        #Read contents of compile_targets and time_reports files
        if os.path.exists("compile_targets.txt"):
            with open("compile_targets.txt", "r") as fd:
                compile_target_contents = fd.read()
        if os.path.exists("time_reports.txt"):
            with open("time_reports.txt", "r") as fd:
                time_report_contents = fd.read()

        #Parse contents with file contents or with samples provided at the beginning of this file
        compile_targets, compile_target_group = None, None
        if test:
            compile_targets, compile_target_group = parse_compile_target_time()
        else:
            compile_targets, compile_target_group = parse_compile_target_time(compile_target_contents, time_report_contents)


        #Marge results and compute group timing and gcc_component timing
        compile_target_results = None
        if compile_targets is not None and compile_target_group is not None:
            compile_target_results = {"individual":None, "group": None, "gcc_component": None}

            #Remove modules to check side effects
            modules_to_remove = []#[lte]
            for module in modules_to_remove:
                for target in compile_target_group["children"]["src"]["children"][module]["children"]:
                    del compile_targets[target]
                del compile_target_group["children"]["src"]["children"][module]

            #Compute aggregated times for each group and subgroup of targets
            total_time = 0.0
            for group in compile_target_group["children"]:
                group_time = 0.0
                for subgroup in compile_target_group["children"][group]["children"]:
                    subgroup_time = 0.0
                    for target in compile_target_group["children"][group]["children"][subgroup]["children"]:
                        #compile_target_group["children"][group]["children"][subgroup]["children"][target] = compile_targets[target] #reduce duplication of data
                        target_time = sum(compile_targets[target]["components"].values())
                        compile_target_group["children"][group]["children"][subgroup]["children"][target]["total"] = target_time
                        compile_targets[target]["total"] = target_time
                        subgroup_time += target_time
                    compile_target_group["children"][group]["children"][subgroup]["total"] = subgroup_time
                    group_time += subgroup_time
                compile_target_group["children"][group]["total"] = group_time
                total_time += group_time
            compile_target_group["total"] = total_time

            del subgroup_time, group_time

            # Save all individual target times
            compile_target_results["individual"] = compile_targets

            #Save all aggregated group times
            compile_target_results["group"] = compile_target_group

            #Compute aggregated times for gcc steps
            gcc_component_time = {}
            for target in compile_targets:
                for component in compile_targets[target]["components"]:
                    if component not in gcc_component_time:
                        gcc_component_time[component] = {}
                        gcc_component_time[component]["total"] = compile_targets[target]["components"][component]
                        gcc_component_time[component]["targets"] = {target:compile_targets[target]["components"][component]}
                    else:
                        gcc_component_time[component]["total"] += compile_targets[target]["components"][component]
                        gcc_component_time[component]["targets"][target] = compile_targets[target]["components"][component]

            compile_target_results["gcc_component"] = gcc_component_time

        #Dump computed results to a json file
        if compile_target_results is not None:
            with open("compile_target_time.json", "w") as fd:
                json.dump(compile_target_results, fd, indent=3)

    #Load json dump before plotting
    if compile_target_results is None and os.path.exists("compile_target_time.json"):
        with open("compile_target_time.json", "r") as fd:
            compile_target_results = json.load(fd)


    import numpy as np
    import matplotlib.pyplot as plt

    #Print top 50 individual compile targets
    sorted_compile_targets = list(sorted(compile_target_results["individual"].items(), key=lambda kv: kv[1]["total"], reverse=True))

    names = []
    values = []
    for target in sorted_compile_targets[:50]:
        values += [target[1]["total"]]
        names += [target[0]]
    plt.bar(list(range(len(sorted_compile_targets[:50]))), values)
    plt.title("Top 50 individual compilation targets by time")
    plt.ylabel('Total compilation time (s)')
    plt.xticks(list(range(len(sorted_compile_targets[:50]))), names, rotation="vertical", fontsize=8)
    plt.savefig("top50individualTargets.jpg", dpi=300, bbox_inches = "tight")
    plt.show()

    plt.clf()

    # Print rank of module compile times
    sorted_compile_modules = list(sorted(compile_target_results["group"]["children"]["src"]["children"].items(), key=lambda kv: kv[1]["total"], reverse=True))

    names = []
    values = []
    for target in sorted_compile_modules:
        values += [target[1]["total"]]
        names += [target[0]]
    plt.bar(list(range(len(sorted_compile_modules))), values)
    plt.title("Module compilation rank by time")
    plt.ylabel('Total compilation time (s)')
    plt.xticks(list(range(len(sorted_compile_modules))), names, rotation="vertical", fontsize=8)
    plt.savefig("rankModules.jpg", dpi=300, bbox_inches = "tight")
    plt.show()

    plt.clf()

    # Print top 50 individual gcc compile phases
    sorted_compile_phases = list(sorted(compile_target_results["gcc_component"].items(), key=lambda kv: kv[1]["total"], reverse=True))

    names = []
    values = []
    for target in sorted_compile_phases[:50]:
        values += [target[1]["total"]]
        names += [target[0]]
    plt.bar(list(range(len(sorted_compile_phases[:50]))), values)
    plt.title("Top 50 gcc compilation phases by time")
    plt.ylabel('Total compilation time (s)')
    plt.xticks(list(range(len(sorted_compile_phases[:50]))), names, rotation="vertical", fontsize=8)
    plt.savefig("top50compilePhases.jpg", dpi=300, bbox_inches = "tight")
    plt.show()

    plt.clf()

    # Print top 50 individual gcc compile phases
    sorted_targets_of_topCompilePhase = list(sorted(compile_target_results["gcc_component"][sorted_compile_phases[0][0]]["targets"].items(), key=lambda kv: kv[1], reverse=True))

    names = []
    values = []
    for target in sorted_targets_of_topCompilePhase[:50]:
        values += [target[1]]
        names += [target[0]]
    plt.bar(list(range(len(sorted_targets_of_topCompilePhase[:50]))), values)
    plt.title("Top targets of top gcc compilation phase (%s) by time" % sorted_compile_phases[0][0])
    plt.ylabel('Total compilation time (s)')
    plt.xticks(list(range(len(sorted_targets_of_topCompilePhase[:50]))), names, rotation="vertical", fontsize=8)
    plt.savefig("top50targetsOfTopCompilePhase.jpg", dpi=300, bbox_inches="tight")
    plt.show()

    plt.clf()
    print("pew pew")
    pass

main()

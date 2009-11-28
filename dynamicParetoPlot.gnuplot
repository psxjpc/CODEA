#set lmargin 5
#set bmargin 3
#set rmargin 2
#set tmargin 2
#set size 0.5,0.5
set xtics font "Arial,10"
set ytics font "Arial,10"
set font "Arial,10"
set grid
set autoscale
fontType = "Arial,10"
point_size = 0.2
point_color = "black"

# Data
# -----------------
# 1: Vehicles
# 2: Elapsed time
# 3: Waiting time
# 4: Distance
# 5: Time Window Violation
# 6: Number of Time Window Violations
# 7: Capacity Violations
# 8: Numbrt of Capacity Violations


f1 = 4
f2 = 6
filename="./r101.out"
set xrange [0:   ]
set yrange [0:100]
#if (f2 == 6) set xrange [0:100]

call "./plotPareto.gnuplot" filename f1 f2 point_size point_color


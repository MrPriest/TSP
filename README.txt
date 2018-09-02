Author: Thomas Del Prete

I used simulated annealing method to solve the TSP. The average error is 10%. Maybe by seeding, the mean error would have lowered but not much I think.

I optimised the memory and cpu usage as much as I could. Here you can find my project on github (I uploaded it later on, though you can still see the optimisation part):

https://github.com/MrPriest/TSP

Finally, these are the commands to get the results I claimed into the excel file:

ch130)    ./cup AI_cup_2017_problems/ch130.tsp 0.99999 1535652201
d198)     ./cup AI_cup_2017_problems/d198.tsp 0.99999 1535653076
eil76)    ./cup AI_cup_2017_problems/eil76.tsp 0.99999 1535653544
fl1577)   ./cup AI_cup_2017_problems/fl1577.tsp 0.99999 1535862610
kroa100)  ./cup AI_cup_2017_problems/kroa100.tsp 0.99999 1535657419
lin318)   ./cup AI_cup_2017_problems/lin318.tsp 0.999996 1535816889
pcb442)   ./cup AI_cup_2017_problems/pcb442.tsp 0.99999 1535659754
pr493)    ./cup AI_cup_2017_problems/pr439.tsp 0.999995 1535819703
rat783)   ./cup AI_cup_2017_problems/rat783.tsp 0.999991 1535840248
u1060)    ./cup AI_cup_2017_problems/u1060.tsp 0.99999 1535878155

To compile the cup use this command:

g++ -o cup cup.cpp

To run each problem, this is the input:

./cup <path from cup to problem file> <temperature change> (optional: <seed>)

For any doubt or question about the code or anything, feel free to contact me.

p.s. Execution ALWAYS stops at 2.55 minutes. Also, the results you’ll get after running the code will be the best path and its cost (plus the seed).
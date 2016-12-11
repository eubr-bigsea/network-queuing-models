# Network Queuing Models
Repository with implementations for the network queing models (eg. Lundstrom, Badue)

### Install
```
git clone git@github.com:eubr-bigsea/network-queuing-models.git
cd network-queuing-models
gcc -o makva makva.c
gcc -o badue badue.c
```
### Run Badue
```
Solves a fork-join queues with homogenous server service rates according to Badue et. al. 2010.

Input metrics are p (number of slave servers), lambda (arrival rate in open networks, throughput in closed networks), and service times for master and slave servers. If historical data is available, one can simply input the average response time of servers instead. 

If another measurement is available (eg. utilization), then first compute service times with system laws (eg. S = U/X).                   

Output metrics are lower and upper bounds on system response times.
```
#####Sample output:
```
0.402488 <= R <= 1.035577
```
#####Parameters:
```
-p Number of slave servers
-l Task arrival rate or throughput
-s Average service times for master and slave servers
-r Average response times for master and slave servers (optional and mutually exclusive with -l -s)
```
#####Format:
```
  ./badue -p <num servers> -l <arrival rate> -s <service time of master>
  <service time of slave> -r <response time of master> <response time of slave>
```
#####Example:
```
./badue -p 8 -r 0.0 0.475
```
### Run Makva/Lundstrom
```
Approximate Mean Value Analysis for closed queueing networks.

Solves a closed queuing network through modified MVA according to Mak & Lundstrom 1990 and Liang & Tripathi 2000.

Input metrics are N (number of tasks), C (number of service centers), epsilon (error tolerance), average response time for each task,service demand for each task and  the matrix of task overlaps, which should be calculated from the task graph in a previous step.     

Output metric is the total job response time.
```
#####Sample output:
```
R = 2.584088
```
#####Parameters:
```
-N Number of tasks
-C Number of servers\n\
-e Error tolerance\n\
-r Log file containing response times for each task\n\
-s Log file containing service demands for each task\n\
-o File containing the task overlap matrix\
```
#####Format:
```
./makva -N <num tasks> -C <num centers> -e <error> -r <log_response.txt> -s <log_demand.txt> -o <log_overlap.txt>
```
#####Example:
```
./makva -N 4 -C 1 -e 2.5 -r response.txt -s demand.txt -o overlap.txt
```

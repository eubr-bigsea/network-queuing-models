//===================================================== file = badue2.c =====
//=  Bounding model for fork-join networks                                  =
//===========================================================================
//=  Solves a fork-join queues with homogenous server service rates         =
//=  according to Badue et. al. 2010                                        =
//=                                                                         =
//=  Input metrics are p (number of slave servers), lambda (arrival rate in =
//=  open networks, throughput in closed networks), and service times for   =
//=  master and slave servers. If historical data is available, one can     =
//=  simply input the average response time of servers instead.             =
//=  If another measurement is available (eg. utilization), then first      =
//=  compute service times with system laws (eg. S = U/X)                   =
//=                                                                         =
//=  Output metrics are lower and upper bounds on system response times.    =
//=  Sample output:                                                         =
//=   0.402488 <= R <= 1.035577                                             =
//=-------------------------------------------------------------------------=
//=  Build:  gcc badue.c -o badue                                           =
//=-------------------------------------------------------------------------=
//=  Run:  ./badue -?                                                       =
//=-------------------------------------------------------------------------=
//=  History:  v1 April 2016                                                =
//=            v2 September 2016: support for optional input parameters     =
//===========================================================================

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void usage(){
  fprintf(stderr, "Usage:\n\
  -p Number of slave servers\n\
  -l Task arrival rate or throughput\n\
  -s Average service times for master and slave servers\n\
  -r Average response times for master and slave servers\n\
  \n\
  -r is optional and mutually exclusive with -l -s\n\
  \n\
  Format:\n\
  ./badue -p <num servers> -l <arrival rate> -s <service time of master>\
  <service time of slave> -r <response time of master> <response time of slave>\n\
  \n\
  Example:\n\
  ./badue -p 8 -r 0.0 0.475\n");
}

int main(int argc, char *argv[]){
  float minR, maxR;  // Bounds for the response time of the system
  float R_m;         // Response time of master server
  float R_s;         // Response time of slave servers
  int p;             // Number of slave servers
  float H_p;         // p-th Harmonic number
  
  float lambda;      // Task arrival rate
  float S_m;         // Service time at the master server
  float S_s;         // Service time at the slave servers
  int opt, i;        
  
  // Get server info
  R_s = -1;
  S_s = -1;

  while((opt=getopt(argc,argv,"p:s:l:r:"))!=-1){
    switch(opt){
      case 'p':
        p = atoi(optarg); break;
      case 's':
        S_m = atof(optarg);
        if (optind < argc && *argv[optind] != '-'){
          S_s = atof(argv[optind]);
          optind++;
        } else {
          printf("\n-s option require TWO arguments \
          -s <service time of master> <service time of slaves> \n\n");
         usage();
	 return 0;
       } break;
      case 'l':
        lambda = atof(optarg); break;
      case 'r':
        R_m = atof(optarg);
	if (optind < argc && *argv[optind] != '-'){
          R_s = atof(argv[optind]);
          optind++;
        } else {
          printf("\n-r option require TWO arguments \
          -r <response time of master> <response time of slaves> \n\n");
         usage();
	 return 0;
       } break;
      default:
        case '?': usage();
        return 0;
    }
  }
  
  // Calculate response times from service times, if not given
  if(R_s < 0){
    R_m = S_m/(1 - lambda*S_m);
    R_s = S_s/(1 - lambda*S_s);
  }

  // Bounds for system response time
  H_p = 0.0;
  for (i=1; i<=p; i++)
        H_p += 1.0/i;

  minR = R_s + R_m;
  maxR = (H_p * R_s) + R_m;

  // Output bounds
  printf("%f <= R <= %f\n", minR, maxR);
}

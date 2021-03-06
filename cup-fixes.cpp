/* Author: Thomas Del Prete */
// VERY IMPORTANTE: Use "g++ -o cup cup.cpp" to compile!
// SAMPLE INPUT: ./cup AI_cup_2017_problems/ch130.tsp 0.99999 1535651642
//               ./cup <path from cup to problem file> <temp_change> (optional: <seed>)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <cmath>
#include <sstream>
#include <fstream>
#include <array>
#include <ctime>
#include <cstdlib>

double nodes[2000][3]; //MAX INPUT NODES 2000. [id, x, y]
int nodes_number;
int shuffled_cost;

int myrandom (int i) {
  return std::rand()%i;
}

int path_cost (double nodes_array[][3]){
  int cost = 0;
  for (int i = 0; i < nodes_number; ++i){
    if (i == (nodes_number - 1)) {
      cost += sqrt( pow((nodes_array[i][1] - nodes_array[0][1]), 2) + pow((nodes_array[i][2] - nodes_array[0][2]), 2) );
    } else {
      cost += sqrt( pow((nodes_array[i][1] - nodes_array[i+1][1]), 2) + pow((nodes_array[i][2] - nodes_array[i+1][2]), 2) );
    }
  }
  return cost;
}

int otp2 (double nodes_array[][3], int initial_dist){
  int pos_1 = (std::rand() % (nodes_number - 1));
  int pos_2 = (std::rand() % (nodes_number - 1));
    
  if (pos_1 > pos_2) {
    int tmp = pos_2;
    pos_2 = pos_1;
    pos_1 = tmp;
  }
    
  int swapless_dist;
    if ((pos_1 == 0) && (pos_2 == (nodes_number - 1))) {
        swapless_dist = sqrt( pow((nodes_array[nodes_number-1][1] - nodes_array[pos_1][1]), 2) +
                              pow((nodes_array[nodes_number-1][2] - nodes_array[pos_1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                              pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                              pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2][1] - nodes_array[0][1]), 2) +
                              pow((nodes_array[pos_2][2] - nodes_array[0][2]), 2) );
    } else if (pos_1 == 0) {
        swapless_dist = sqrt( pow((nodes_array[nodes_number-1][1] - nodes_array[pos_1][1]), 2) +
                              pow((nodes_array[nodes_number-1][2] - nodes_array[pos_1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                              pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                              pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2][1] - nodes_array[pos_2+1][1]), 2) +
                              pow((nodes_array[pos_2][2] - nodes_array[pos_2+1][2]), 2) );
    } else if (pos_2 == (nodes_number - 1)) {
        swapless_dist = sqrt( pow((nodes_array[pos_1-1][1] - nodes_array[pos_1][1]), 2) +
                              pow((nodes_array[pos_1-1][2] - nodes_array[pos_1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                              pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                              pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2][1] - nodes_array[0][1]), 2) +
                              pow((nodes_array[pos_2][2] - nodes_array[0][2]), 2) );
    } else {
        swapless_dist = sqrt( pow((nodes_array[pos_1-1][1] - nodes_array[pos_1][1]), 2) +
                              pow((nodes_array[pos_1-1][2] - nodes_array[pos_1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                              pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                              pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                        sqrt( pow((nodes_array[pos_2][1] - nodes_array[pos_2+1][1]), 2) +
                              pow((nodes_array[pos_2][2] - nodes_array[pos_2+1][2]), 2) ); //this computes the distance, before the 2opt swap, between each
                                                                                           //"to be swapped" node and its neighbouring nodes
    }
    
  std::swap(nodes_array[pos_1], nodes_array[pos_2]);
    
    int swap_dist;
    if ((pos_1 == 0) && (pos_2 == (nodes_number - 1))) {
        swap_dist = sqrt( pow((nodes_array[nodes_number-1][1] - nodes_array[pos_1][1]), 2) +
                          pow((nodes_array[nodes_number-1][2] - nodes_array[pos_1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                          pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                          pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2][1] - nodes_array[0][1]), 2) +
                          pow((nodes_array[pos_2][2] - nodes_array[0][2]), 2) );
    } else if (pos_1 == 0) {
        swap_dist = sqrt( pow((nodes_array[nodes_number-1][1] - nodes_array[pos_1][1]), 2) +
                          pow((nodes_array[nodes_number-1][2] - nodes_array[pos_1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                          pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                          pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2][1] - nodes_array[pos_2+1][1]), 2) +
                          pow((nodes_array[pos_2][2] - nodes_array[pos_2+1][2]), 2) );
    } else if (pos_2 == (nodes_number - 1)) {
        swap_dist = sqrt( pow((nodes_array[pos_1-1][1] - nodes_array[pos_1][1]), 2) +
                          pow((nodes_array[pos_1-1][2] - nodes_array[pos_1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                          pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                          pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2][1] - nodes_array[0][1]), 2) +
                          pow((nodes_array[pos_2][2] - nodes_array[0][2]), 2) );
    } else {
        swap_dist = sqrt( pow((nodes_array[pos_1-1][1] - nodes_array[pos_1][1]), 2) +
                          pow((nodes_array[pos_1-1][2] - nodes_array[pos_1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_1][1] - nodes_array[pos_1+1][1]), 2) +
                          pow((nodes_array[pos_1][2] - nodes_array[pos_1+1][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2-1][1] - nodes_array[pos_2][1]), 2) +
                          pow((nodes_array[pos_2-1][2] - nodes_array[pos_2][2]), 2) ) +
                    sqrt( pow((nodes_array[pos_2][1] - nodes_array[pos_2+1][1]), 2) +
                          pow((nodes_array[pos_2][2] - nodes_array[pos_2+1][2]), 2) ); //this computes the distance, after the 2opt swap, between each
                                                                                       //"swapped" node and its neighbouring nodes
    }
    
  return (initial_dist - swapless_dist + swap_dist); //new 2otp total distance

}

void should_accept (double nodes_array[][3], double temp){ //generates 2otp from current, compares them and picks the optimal one (at the end, input array will contain optimal).
  double otp_nodes[nodes_number][3];
  std::copy(&nodes_array[0][0], &nodes_array[0][0]+nodes_number*3,&otp_nodes[0][0]);
  int otp_cost = otp2(otp_nodes, shuffled_cost);
  if (otp_cost <= shuffled_cost) {
    shuffled_cost = otp_cost;
    std::copy(&otp_nodes[0][0], &otp_nodes[0][0]+nodes_number*3,&nodes_array[0][0]);
  } else {
    if ( exp((shuffled_cost - otp_cost)/temp) > ((double)rand()/(RAND_MAX)) ){
      shuffled_cost = otp_cost;
      std::copy(&otp_nodes[0][0], &otp_nodes[0][0]+nodes_number*3,&nodes_array[0][0]);
    }
  }
}

int main (int argc, char** argv) {

  time_t start, end; //initialising counter to exit after 3 minutes
  double elapsed;  // seconds
  start = time(NULL);

  double temperature = 1000.0;
  double temp_change = atof(argv[2]); //0.99997; //alpha
  double temp_min = 0.00000001;

  time_t seed;
  if ((argc < 3) || (argc > 4)) {
    printf ("Wrong command!\nUsage: ./cup <path from cup to problem file> <temp_change> (optional: <seed>)");
    exit (EXIT_FAILURE);
  } else if (argc == 3) {
    seed = std::time(0); // seed used for random generated by time
  } else if (argc == 4) {
    seed = atof(argv[3]);
  }
  std::srand(unsigned(seed)); // srand using known seed

/////////////////////////////////TAKING INPUT//////////////////////////////////
  std::string line;
  int line_count = 0;
  std::ifstream myfile (argv[1]);
  if (myfile.is_open()) {
    while ( getline (myfile,line) ) {
      if (line_count == 3) { //when line_count=3 get dimension
        std::istringstream iss (line); //used to then parse the line
        std::string dump;
        iss >> dump >> dump >> nodes_number;
      }
      if (line_count >= 7) { //when line_count=7 start getting nodes
        std::istringstream iss (line); //used to then parse the line
        int node_id;
        double x_coord;
        double y_coord;
        iss >> node_id >> x_coord >> y_coord;
        nodes[node_id - 1][0] = node_id;
        nodes[node_id - 1][1] = x_coord;
        nodes[node_id - 1][2] = y_coord;
      }
      ++line_count;
    }
    myfile.close();
  } else {
    std::cout << "Unable to open file";
  }

//////////////////////// CREATE FIRST RANDOM TOUR /////////////////////////////

  double shuffled_nodes[nodes_number][3];
  std::copy(&nodes[0][0], &nodes[0][0]+nodes_number*3,&shuffled_nodes[0][0]);
  std::random_shuffle ( &shuffled_nodes[0], &shuffled_nodes[nodes_number], myrandom);
  shuffled_cost = path_cost(shuffled_nodes);

////////////////////////////////// ANNEALING //////////////////////////////////

  int best_cost = shuffled_cost;
  double best[nodes_number][3];

  for (double i = temperature; i > temp_min; i = temp_change * i){
    should_accept(shuffled_nodes, i);
    // shuffled nodes better than solution?
    if (shuffled_cost <= best_cost) {
      std::copy(&shuffled_nodes[0][0], &shuffled_nodes[0][0]+nodes_number*3,&best[0][0]);
      best_cost = shuffled_cost;
    }

    end = time(NULL); //exit after 3 minutes
    elapsed = difftime(end, start);
    if (elapsed >= 175.0 /* seconds */)
       break;
  }

  std::cout << "-------------------------------------------------------------" << std::endl;
  std::cout << "best solution: " << std::endl;
 //          nodes array print            //

   for (int i = 0; i < nodes_number; ++i)
   {
       for (int j = 0; j < 3; ++j)
       {
           std::cout << best[i][j] << " ";
       }
       std::cout << std::endl;
   }
 //                                       //
 std::cout << "-------------------------------------------------------------" << std::endl;
 std::cout << "best cost: " << best_cost << std::endl;
 std::cout << "-------------------------------------------------------------" << std::endl;
 std::cout << "seed: " << seed << std::endl;
 std::cout << "-------------------------------------------------------------" << std::endl;

  return 0;
}

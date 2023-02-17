/**
 * @file my_parallel.cc
 * @author Hunter Stout (hs127321@ohio.edu)
 * @brief Converting from boost library to different arithmetic & parallel.
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <iomanip>
#include <set>
#include <omp.h> //Replaced boost with openMP library.

using namespace std;

/**
 * @brief Power
 * 
 * @param a - Multiplier.
 * @param n - Power we are looking to achieve.
 * @return size_t 
 */
size_t power(size_t a, size_t n) {
  size_t p = 1;

  for (size_t i=1;i<=n;i++) { //Loop to multiply size_t by itself.
    p*=a; 
    p%=1000000; //Saves mod version to size_t to avoid exceeding integer limits.
  }
  return p; //Returns last 6 digits of size_t.
}

int main() {

  size_t n; //Input information.
  cin >> n;
  size_t sum = 0;

  const int threads = omp_get_thread_num(); //Grabs thread number from openMP.
  #pragma omp parallel for reduction(+:sum) num_threads(threads) //Reduction on sum inside loop & sets thread number based on PC.

  for (size_t i=1;i<=n;i++) { sum+=power(i,i); } //Loop we are running parallel.

  cout << setw(6) << setfill('0') << sum%1000000 << endl; //Modded output.
}

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

int64_t current_time_micros(){
    return (std::chrono::duration_cast< microseconds >(high_resolution_clock::now().time_since_epoch())).count();
}

void benchmark(int64_t n, ostream& out){
    int64_t* data = (int64_t*) malloc(n * sizeof(int64_t));

    for(int64_t i = 0; i < n; i++){
        data[i] = rand()%n;
    }
    
    int64_t n_accesses = 1e7;
    int64_t* access_pattern = (int64_t*) malloc(n_accesses * sizeof(int64_t));
    for(int64_t i = 0; i < n_accesses; i++){
        access_pattern[i] = rand()%n;
    }

    int64_t t0 = current_time_micros();
    int64_t sum = 0;
    for(int64_t i = 0; i < n_accesses; i++){
        sum += data[access_pattern[i]];
    }
    int64_t t1 = current_time_micros();
    cerr << "Time: " << (double)(t1 - t0) / n_accesses * 1000 << " ns / access" << endl;
    cerr << "Final sum: " << sum << endl;
    out << n << " " << (double)(t1 - t0) / n_accesses * 1000 << endl;

    free(data);
    free(access_pattern);
}

int main(){
    srand(1234);
    ofstream out("results.txt");
    for(int64_t n = 1024; n <= (1LL << 30); n *= 2){
        cerr << "n = " << n << endl;
        benchmark(n, out);
    }

}
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <functional> 
#include <numeric>     

#include "sobol.hpp"

# define DIM_MAX 2

int dim_num = 1; //originally 1 but suggested to be 2
float *r;
int seed;
int seed_in;
int seed_out;

double getQuasiRandomNumber(int *seed)
{
	i4_sobol(dim_num, seed, r);
	return r[0];
}


void getNDimQuasiRandomNumber(int *seed, int dim_number, float *r)
{
	i4_sobol(dim_number, seed, r);
}
//Quasirandom Number Generators can also be called low discrepency or sub random sequence
//Types of Quasirandom Number Generators (QRNG)
//Faure
//Halton Sequence
//Hammersley Set
//Niderriter
//Sobol Sequence ** must use this
//Random Numbers
//Aditive Reccurance
//van der Corput Sequence
//Poisson disk sampling

//(Kider, 2017; Wikimedia Foundation Inc.,2016)


int main()
{
	r = new float[DIM_MAX];

	//use a random device
	std::random_device rd;

	// Another seed intialization routine (this is just here for future reference for you.)
	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	// 2 different ways to get a random starting seed
	seed = rd();
	//seed = ss;

	// 3) Play with N
	unsigned int N = 5000;  // number of values generated
	double randomValue;
	std::map<int, int> hist; //Counts of discrete values
	std::vector<double> raw; //raw random values 


	for (unsigned int i = 0; i < N; ++i) {
		randomValue = 0 + getQuasiRandomNumber(&seed) * 100;//*100

		++hist[std::round(randomValue)]; // count the values
		raw.push_back(randomValue);  //push the raw values
	}

	for (auto p : hist) {

		// Uncomment if you want to see the values
		//std::cout << std::fixed << std::setprecision(1) << std::setw(2)
		//	<< p.first << " -  "<< p.second << std::endl;

		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "  " << std::string(p.second / (N / 500), '*') << std::endl;

	}


	// Print Results to File
	std::ofstream myfile;
	myfile.open("histogram_results.txt");
	for (auto p : hist) {
		myfile << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "\t" << p.second << std::endl;
	}
	myfile.close();

	myfile.open("raw_results.txt");
	for (auto p : raw) {
		myfile << std::fixed << std::setprecision(5) << std::setw(2)
			<< p << std::endl;
	}
	myfile.close();


	//if you choose to write useful stats here
	myfile.open("useful_stats.txt");
	double sum = std::accumulate(raw.begin(), raw.end(), 0.0);
	double mean = sum / raw.size();
	myfile << "mean: " << mean << std::endl;
	std::cout << "mean: " << mean << std::endl;

	std::vector<double> diff(raw.size());
	std::transform(raw.begin(), raw.end(), diff.begin(),
		std::bind2nd(std::minus<double>(), mean));
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / raw.size());
	myfile << "stdev: " << stdev << std::endl;
	std::cout << "stdev: " << stdev << std::endl;

	myfile.close();

	//References
	//Kider, J. (2017). Quasi-random generation [Webcourse Page]. Retrieved from Notes Online Web site: https://webcourses.ucf.edu/courses/1246518/pages/quasi-random-generation?module_item_id=10541649
	//Wikimedia Foundation Inc. (2016) Low-discrepence sequence. Retrived from https://en.wikipedia.org/wiki/Low-discrepancy_sequence
}
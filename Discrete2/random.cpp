#include <iostream> // http://www.cplusplus.com/reference/iostream/
#include <iomanip> // http://www.cplusplus.com/reference/iomanip/
#include <string> // http://www.cplusplus.com/reference/string/
#include <map> //http://www.cplusplus.com/reference/map/
#include <random> //http://www.cplusplus.com/reference/random/
#include <vector> //http://www.cplusplus.com/reference/vector/
#include <chrono> //http://www.cplusplus.com/reference/chrono/
#include <fstream> //http://www.cplusplus.com/reference/fstream/
#include <algorithm> //http://www.cplusplus.com/reference/algorithm/
#include <functional> //http://www.cplusplus.com/reference/functional/
#include <numeric> //http://www.cplusplus.com/reference/numeric/  
#include <cmath> // reference: https://msdn.microsoft.com/en-us/library/4hwaceh6.aspx

int main()
{
	// Get a random seed
	std::srand(time(0)); //(Dawson, 2008)
	
	// Another seed intialization routine (this is just here for future reference for you.)
		// initialize the random number generator with time-dependent seed
		// This is because you want your seed to be different each time you run your program and this is based on the current time (Dawson, 2008)
		// seed_seq = seed sequence (Cplusplus.com, 2017)
	//uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	//std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	//std::mt19937_64 e2;
	//e2.seed(ss);
	
	//use a random device
	std::random_device rd;
	//"true random number generator"-(Cplusplus.com, 2017)

	// 1) Change random number generators

	//Pseudorandom Number Generators (PRNG)
		std::mt19937_64 engine(rd()); //Mersenne Twister 19937 generator 64 bit
		//std::knuth_b engine(rd()); //Knuth-B generator 
		//std::minstd_rand engine(rd()); // Minimal Standard Random Generator
		//std::minstd_rand0 engine(rd()); // Minimal Standard Random0 Generator
		//std::ranlux48 engine(rd());//Ranlux 48 generator
		//std::ranlux24 engine(rd());//Ranlux 24 generator
		//std::ranlux48_base engine(rd());//Ranlux 48 base generator
		//std::ranlux24_base engine(rd());//Ranlux 24 base generator
		//std::default_random_engine engine(rd());//Defualt random engine
		//(Cplusplus.com, 2017)

	//  2) - Change distribution types

	//Types of Uniform Distributions
	//"for each member of the family, all intervals of the same length on the distribution's support are equally probable," (https://en.wikipedia.org/wiki/Uniform_distribution_(continuous))
		//std::uniform_real_distribution<> dist(0, 100);  // example of a uniform real (continuous?) distribution
		//std::uniform_int_distribution<> dist(0, 100);  // example of a uniform discrete distribution
	//Is it using continuous or discrete data?

	//Types of Bernoulli (yes/no) Distributions
		//std::bernoulli_distribution<> dist(0.5);    // example of a Bernoulli distribution
			//Probabulity between yes/true/one outcomes and no/false/zero outcomes, can be used for coin tosses (https://en.wikipedia.org/wiki/Bernoulli_distribution)
		//std::binomial_distribution<> dist(1,0.5);    // example of a Binomial distribution
			// yes/no, discrete, (https://en.wikipedia.org/wiki/Binomial_distribution)
		//std::geometric_distribution<> dist(0.5);    // example of a Geometric distribution
			//discrete; two different instances: "The probability distribution of the number X of Bernoulli trials needed to get one success, supported on the set { 1, 2, 3, ...} OR The probability distribution of the number Y = X − 1 of failures before the first success, supported on the set{ 0, 1, 2, 3, ... }." (https://en.wikipedia.org/wiki/Geometric_distribution)
		//std::negative_binomial_distribution<> dist(0,0);    // example of a Negative Binomial distribution
			//discrete data;

	//Types of Rate-based Distributions
		std::poisson_distribution<> dist(25); //   // example of a Poisson distribution
		//******std::exponential_distribution<> dist(10);    // example of an Exponential distribution
		//std::gamma_distribution<> dist(0,0);    // example of a Gamma distribution
		//std::weibull_distribution<> dist(0,0);    // example of a Weibull distribution
		//std::extreme_value_distribution<> dist(0,0);    // example of an Extreme Value distribution

	//Normal Distribution
		//std::normal_distribution<> dist(50,10);    // example of a normal distribution
			//AKA Gaussian; "to represent real-valued random variables whose distributions are not known."

	//Related to Normal Distribution
		//std::lognormal_distribution<> dist(0,0);  //example of a lognormal distribution
			//"It resembles the normal distribution in shape but has heavier tails (higher kurtosis)," (https://en.wikipedia.org/wiki/Logistic_distribution)
		//std::chi_squared_distribution<> dist(0,0);  //example of a Chi-squared distribution
			//Related to gamma distribution; "The chi-squared distribution is used in the common chi-squared tests for goodness of fit of an observed distribution to a theoretical one, the independence of two criteria of classification of qualitative data, and in confidence interval estimation for a population standard deviation of a normal distribution from a sample standard deviation. Many other statistical tests also use this distribution, like Friedman's analysis of variance by ranks."(https://en.wikipedia.org/wiki/Chi-squared_distribution)
		//std::cauchy_distribution<> dist(0,0);  //example of a Cauchy distribution
			//"The Cauchy distribution is often used in statistics as the canonical example of a "pathological" distribution since both its expected value and its variance are undefined." (https://en.wikipedia.org/wiki/Cauchy_distribution)
		//std::fisher_f__distribution<> dist(0,0);  //example of a Fisher-F distribution
			//"arises frequently as the null distribution of a test statistic, most notably in the analysis of variance, e.g., F-test." (https://en.wikipedia.org/wiki/F-distribution)
		//std::student_t__distribution<> dist(0,0);  //example of a Student-T distribution
			//Continuous;  "sample size is small and population standard deviation is unknown," (https://en.wikipedia.org/wiki/Student%27s_t-distribution)

	//Types of Piecewise Distributions
		//std::discrete_distribution<> dist(0,0);    // example of a discrete distribution
		//std::piecewise_constant_distribution<> dist(0,0);    // example of a Piecewise constant distribution
		//std::piecewise_linear_distribution<> dist(0,0);    // example of a Piecewise linear distribution
	
	//(Cplusplus.com, 2017)


		auto generator = std::bind(dist, engine);

		// 3) Play with N
		unsigned int N = 5000;  // number of values generated
		double randomValue;
		std::map<int, int> hist; //Counts of discrete values
		std::vector<double> raw; //raw random values 

		for (unsigned int i = 0; i < N; ++i) {

			randomValue = generator();

			++hist[std::round(randomValue)]; // count the values
			raw.push_back(randomValue);  //push the raw values
		}


		for (auto p : hist) {

			// Uncomment if you want to see the values
			//std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			//<< p.first << " -  "<< p.second << std::endl;
			std::cout << std::fixed << std::setprecision(1) << std::setw(2)
				<< p.first << "  " << std::string(p.second / (N / 500), '*') << std::endl;

		}

	// Print Results to File
	std::ofstream myfile;
	myfile.open("histogram_results.txt");
	for (auto p : hist) {
		myfile << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << "\t" << p.second  << std::endl;
	}
	myfile.close();

	myfile.open("raw_results.txt");
	for (auto p : raw) {
		myfile << std::fixed << std::setprecision(5) << std::setw(2)
			<< p << std::endl;
	}
	myfile.close();

	//if you choose to write "useful" stats here

	//Mean
	myfile.open("useful_stats.txt");
	double sum = std::accumulate(raw.begin(), raw.end(), 0.0);
	double mean = sum / raw.size();
	myfile << "mean: " << mean << std::endl;
	std::cout << "mean: " << mean << std::endl;

	//Standard Deviation
	std::vector<double> diff(raw.size());
	std::transform(raw.begin(), raw.end(), diff.begin(),
	std::bind2nd(std::minus<double>(), mean));
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / raw.size());
	myfile << "stdev: " << stdev << std::endl;
	std::cout << "stdev: " << stdev << std::endl;

	//Autocorrelation Test
		//Signal Processing-Finding the signal in the noise
		//Application-"In analysis of Markov chain Monte Carlo data, autocorrelation must be taken into account for correct error determination," (https://en.wikipedia.org/wiki/Autocorrelation)

	//Kolmogorov-Smirnov Test
		//Requires a large N 
		//Non-parametric 
		//"of the number of successes in a sequence of independent and identically distributed Bernoulli trials before a specified (non-random) number of failures (denoted r) occurs. For example, if we define a 1 as failure, all non-1s as successes, and we throw a die repeatedly until the third time 1 appears (r = three failures), then the probability distribution of the number of non-1s that had appeared will be a negative binomial." (https://en.wikipedia.org/wiki/Kolmogorov%E2%80%93Smirnov_test)
			//Is this quote correct?

	//Chi-Squared Test
		//Categorical data- e.g., yes/no (Field, 2009)-use for Bernoulli Type Distributions
		//Used to check for uniform distribution (Law, 2008)
		//Use a Chi-Square test when "comparing the frequencies you observe in certian categories to the frequencies you might expect to get in those categories by chance," (Field, 2009).

	//Biserial and point-biseral correlations
		//Specifically for dichotomous variables- e.g., yes/no (Field, 2009)-use for Bernoulli Type Distributions

	//Spearman’s Rank Correlation Coefficient
		//Non-parametric test "so it can be used when the data have violated parametric assumptions such as non-normally distributed data," (Field, 2009)
		//Can be used with "everything" that is non-normal
		//Need a large N if not use Kendall's Tau (Field,2009).
			//what is a "large" N???

	//Kendall's Tau
	
	//Dont draw a conclusion from the P-value

	myfile.close();

}
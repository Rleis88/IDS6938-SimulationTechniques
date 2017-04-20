# Homework 2 :  Discrete-Event Simulation Assignment
IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)
Submitted By **Rebecca Leis**

**I plan to use my last extra day for this assignment. This sums up my three late days.*

## Introduction
This assignment is broken into four parts: Emperical Tests of Randomness, building Discrete Event Markov Chain and Monte Carlo Simulation, building a Discrete Queueing Simulation, and writing up the finalized results.

## Part 1: Empirical Tests of Randomness

It is important to point out here that there are two different categories of randomness tests: *emperial* and *theoretical* (Law, 2008). To explain the difference between the two, I must also explain the difference between *local* and *global* randomness. "Local randomness refers to the idea that there can be minimim sequence lengths in which random distributions are approximated, " (https://en.wikipedia.org/wiki/Statistical_randomness). Whereas, global randomness refers to"the idea that 'in the long run' a sequence looks truely random, even if certain sub-sequences would not look random," (https://en.wikipedia.org/wiki/Statistical_randomness).

![](images/dilbert.jpg?raw=true)

DILBERT © 2001 Scott Adams. Retrived from https://www.random.org/analysis/

Local and gloabal randomness are "tested" quite differently. Local randomness test are more emperical in nature; whereas gloabl randomness test are more theoretical. "Emperical tests are the usual kind of statistical tests and are based on the actual [data points] produces by the generator. Theoretical tests are not tests in the statistical sense, but use the numerical parameters of a generator to assess it globally without actually generating any [data points] at all," (Law, 2008, p.405).

It is important to note here that for the scope of the assignmt, I will only conduct emperical tests of randomness and not theoretical tests.

### (a) Random Number Generators and "Useful" Statistical Analyses
"[R]andom values can be conveniently and efficiently generated from a desired probability distribution for use in executing simulation models," (Law, 2008, p. 389). Using the data generated from various types of Random Number Generators (RNG), I can draw inferences about specific real-world systems (Field, 2009, p.32), and determine the *probability* that a specific event will occur. Statistical tests of randomness investigae how random the data actually is. This will vary dependent on the type of RNG I choose. Once Visual Studio utilizes the C++ RNG of choice to create the raw data, I can visualize the data in a way that drives my analyses. "It is useful to plot your data first: plots tell you a great deal about what models should be applied to the data," (Field, 2009) which I will do later but first, to understand which RNGs I should use, I compare different types of RNGs.

#### A Comparison of Random Number Generators (RNGs)
There are multiple types of RNGs; generally they are broken into 2 different categories: *hardware random number generators* and *numerical random number generators*(Law, 2008; https://en.wikipedia.org/wiki/Random_number_generation).

##### Hardware Random Number Generators

A hardware RNG "is a device that generates random numbers from a physical process, rather than a computer program," (https://en.wikipedia.org/wiki/Hardware_random_number_generator) Hardware RNGs a "true" RNG, because of this they poses "large memory requiremens or a lot of time for relativley slow input operatons," (Law, 2008, p.390). It is outside the scope of this assignment to discuss Hardware Random Number egenerators. Thus, the reaminer of the document will be dedicated to numerical random number generators.

##### Numerical (Arithmetic) Number Generators
"[N]umerical or arithmetic ways to generate 'random' numbers... each new number being determined by one or several of its predecessrs according to a fixed mathematical formula," (Law , 2008, p.390). To be artimetic means that it is not turely random and is in fact a deterministic algorythm. However, numerical or arithmetic generation methods are commonly used bacuse of their feasability and "closeness" to truely random numbers. Having "truely" random numbers may also not be desirable; for example, "properties of the generated numbers, such as "evenness" of the distribution pf points, are more important in some applications such as Monte Carlo integration," (Law, 2008, p.392). Numeric Random Number generators inlude *pseudo-random number generators* and *quasi-random number generators*. "Pseudo random number generaton aims to seem random whereas quasi random number generation aims to be deterministic but well equidistributed," (Dutang & Wuertz, 2009)

###### Pseudo-random number generators (PRNGs)

> A PRNG "is an algorithm for generating a sequence of numbers whose properties approximate the properties of sequences of random numbers. The PRNG-generated sequence is not truly random, because it is completely determined by a relatively small set of initial values, called the PRNG's seed (which may include truly random values). Although sequences that are closer to truly random can be generated using hardware random number generators, pseudorandom number generators are important in practice for their speed in number generation and their reproducibility," (https://en.wikipedia.org/wiki/Pseudorandom_number_generator).

Psudo-random number generator seeds are typically determined using a time or clock component, (Dawson, 2008; Dutang & Wuertz, 2009). This is denoted in the cade differently depending on the RNG.

Pseudorandom Number Generators (PRNG) used in the C++ code:
* **Mersenne Twister (MT)**: The version chosen here is the 19937 64 bit engine. This is the most commonly used PRNG and is "high quality" (https://en.wikipedia.org/wiki/Mersenne_Twister). This version has a long period of 2^19937 (Dutang & Wuertz, 2009). Additionally, it is desirable becuse it passes many tests of randomness including the Diehard Tests (see below; Dutang & Wuertz, 2009; https://en.wikipedia.org/wiki/Mersenne_Twister); however, it does not pass all tests (https://en.wikipedia.org/wiki/Linear_congruential_generator). The MT Generator uses binary operations, which some RNGS do not (Dutang & Wuertz, 2009). "All operations used in the recurrance are bitwise operations, thus it is a very fast computation compared to modulus operations used in [other] algorythms." (Dutang & Wuertz, 2009). Additionally, because it uses bitwise operations it can also be easiloy implemented into many computer languages(Dutang & Wuertz, 2009). In summary, poisitives of the MT RNG is that it has a longer period, better equidistribution, and computational time compared to other PRGNs (Dutang & Wuertz, 2009).

* **Knuth-B Generator**: This is a Multiple Recursive Generator which utilized a *shuffle order* of the matrix linear congruential generator (LCG) which is another common type of PRNG (Dutang & Wuertz, 2009; Law, 2008, p.393; http://www.cplusplus.com/reference/random/knuth_b/). Specifically, this is a Multiple Recursive Generator in which the *n*th terms depends on the previous one (Dutang & Wuertz, 2009). Which leads me to believe that this is an inappropriate RNG for Markov chains (see below). This can also be called the "Kunth TAOCP-2002" or "Kunth TAOCP" where "TAOCP" stands for Kunth's book *The Art of Computer Programing* (Dutang & Wuertz, 2009). For "Kunth-B", "B" stands for "Book". In general LCGs are desirable because they do not require a lot of memeory to implement and have a "high-quality" of randomness (https://en.wikipedia.org/wiki/Linear_congruential_generator). However the data points of the LCG can only take on rational values (Law, 2008, p.394) and is inappropriate for more detailed/"true" RNG work like cryptogeaphic applications (https://en.wikipedia.org/wiki/Linear_congruential_generator). Specifically, it may be undesirable to use certain (earlier) versions of the Kunth-B Generator because they fail randomness tests; to alieviate this issue, researchers suggest eliminating the first 2000 numbers (Dutang & Wuertz, 2009). I believe the C++ version is the later version, but this can be checked using statistical tests of randomness (see below).

* **Minimal Standard Random Generator**: This is a RNG which utilized another multiplicative LCG multiplied by a constant (16807) and a prime modulus of (2^31)-1 (Park & Miller, 1988; http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.94.3416&rep=rep1&type=pdf). The Minimal Standard Generator came about when Park and Miller (1988) noticed a lack of "good" RNGs. They notes that many RNGs avaliable were developed for an undergraduate audiance, which did not suit their graduate audiances needs (Park & Miller, 1988). Additionally, Park and Miller (1988), stated "the widespread adoption of good, portable, *industry standard* software for random number generation has proven to be an elusive goal." Thus, the Minimul Standard Random Number Generator is named such because of it's goal of meeting a "minimum standard" for RNGs. Park and Miller (1988), go onto explain that users should utilize this RNG unless an alternative is "*known*" to be better. Since then, there have been many advances in RNGs (Dutang & Wuertz, 2009).

* **Ranlux 48 Generator**: A "distinctive feature of the generator is the necessity to discard out groups of generated pseudo-randomnumbers after one generation cycle. Omitted values quantity is determined by the “luxury” parameter," (Demchik, 2010).This PRNG can be grouped into 24 or 48 elements (Demchik, 2010), thus a distinction in the 24 and the 48 generator (see below). The "RANLUX generator is found to be the most appropriate for using on [Graphics Processing Unit] in Monte Carlo simulations," (Demchik, 2010). One benefit of this PRNG is that the statistical properties are often well known, but it can be resource intensive (Demchik, 2010).

Additionally, below is a snapshot of the advantages and disadvantages of different types of PRNGs, particularly when compared to each other.
![](images/SummaryofPRNGs.JPG?raw=true)
Retrived from http://www.pcg-random.org/

Below is a graphic of the histograms (*NOT* Bar charts -- see following citation) produced by each of these PRNGs using a continuous uniform distribution with U(0,100) and an N of 10,000. I chose to present this data using histograms becuse these types of graphs are appropriate for visually displaying distributional data (https://www.forbes.com/sites/naomirobbins/2012/01/04/a-histogram-is-not-a-bar-chart/#52b2fe616d77). From this data I can aee that each of these sets is *close* to a uniform distibution in different ways, but not exactly uniform.

![](images/Histograms.JPG?raw=true)

Other PRNGs in the C++ Code:
* **Minimal Standard Random0 Generator**
* **Ranlux 24 generator**
* **Ranlux 48 base generator**
* **Ranlux 24 base generator**
* **Defualt random engine**

PRNGs are denoted in the code as:

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
		//(Cplusplus.com, 2017).

To see more examples of PRNGs please visit [webcourses here](https://webcourses.ucf.edu/courses/1246518/pages/pseudo-random-generation?module_item_id=10541639)


###### Quasi-random number generators (QRNGs)

QRNG are can also be called low discrepency or sub random sequence (https://webcourses.ucf.edu/courses/1246518/pages/quasi-random-generation?module_item_id=10541649). QRNGs are typically "less random" than PRNGs (https://webcourses.ucf.edu/courses/1246518/pages/quasi-random-generation?module_item_id=10541649). However, they often appear to be less random locally and more random globally. Sometimes it may be more desirable to use QRNGs rather than PRNGs because the data is typically more uniformly distributed (which we will see in the histogram below) allowing superior convergence over PRNGs (https://webcourses.ucf.edu/courses/1246518/pages/quasi-random-generation?module_item_id=10541649). Due to this superior convergence, Quasi methods are sometimes preffered over pseuo-random, (e.g., Quasi-Monte Carlo Methods; https://en.wikipedia.org/wiki/Quasi-Monte_Carlo_method).

Types of Quasirandom Number Generators (QRNG):
* Faure
* Halton Sequence
* Hammersley Set
* Niderriter
* Sobol Sequence
* Random Numbers
* Aditive Reccurance
* van der Corput Sequence
* Poisson disk sampling
(https://webcourses.ucf.edu/courses/1246518/pages/quasi-random-generation?module_item_id=10541649; https://en.wikipedia.org/wiki/Low-discrepancy_sequence)

Below is a histogram of the Sobol RNG data using a continuous uniform distribution with U(0,100) and an N of 10,000.

*It is part of the requirements of this assignment to use the Sobol RNG.*

![](images/Sobol_RNG.JPG?raw=true)
As mentioned above, QRNGs (like Sobol seen here) possess a more uniform distribution than PRNGs. This histogram appears to be more uniformly distributed compared to the four PRNG distributions displayed above.

#### Potential Statistical Tests

Before I begin analyzing the RNG data, it is important to understand the context of the problem (Kanflic, 2015). In this instance I intend to use the data to create both an eletronic version of the board game Snakes and Ladders for Part 2 and an Airport Security Queueing Systems using Markov Chains and Monte Carlo methods. For Part 2-Snakes and Ladders I will need to use an  RNGs to simulate rolling dice to progress forward in the game. For the Part 3-Queueing System I will utilize an RNG to randomize the movement of people within the system (e.g., inter-arrival time, etc.)

Additionally, in order to make sure the RNG output is appropriate, independent and identically distributed (IID), and  fits the distribution and intended purpose/context, I need to employ some *exploratory* statistical analyses. Exploratory analyses is defined as "what you do to understand the data and figure out what might be noteworthy or interesting to highlight to others,"(Kanflic, 2015). Exploratory anayses is in contrast to *explanatory* analysis which is the type of data presented when you would like to explain the reason for a particular characteristic in your data set (Kanflic, 2015). In this instance I will use exploratory analyses. In order to figure out which test is most approrpiate I first need to understand which tests are available to me. Below is a list of potential statistical analyses of RNGs.

##### Statistical Tests suggested by Dr. Kider:
* Autocorrelation Test
* Kolmogorov-Smirnov Test
* Chi-Squared Test
* Spearman’s Rank Correlation Coefficient

##### Other Statistical Tests
Correlations (Field, 2009)
* Pearson's Correlation
* Spearman's Correlation -Repeat
* Kendall's Tau
* Biserial and point-biserial correlations

Tests on one sequence of *n* Numbers (Dutang & Wuertz, 2009)
* Goodness of Fit Tests
* The Gap Test
* The Order Test
* The Frequency Test
* The Serial Test
* The Collision Test
* The Divergence Test
* The Poker Test

Diehard Tests (https://en.wikipedia.org/wiki/Diehard_tests)
* Birthday Spacing
* Overlapping Permutations
* Ranks of Matricies
* Monkey Tests
* Count the 1s
* Parking Lot Test
* Minimum Distance Test
* Random Spheres Test
* The Square Test
* Overlapping Sums Test
* Runs Test
* The Craps Test

It is beyond the scope of this assignment to discuss each of the tests listed above, thus the following section will address only a few of these tests. Additionally, this list is not exhaustive and steams from multiple sources, this results in lists that may overlap. Some test from one list may be repeated in another list, or they may belong to a group of tests listed in another set.

#### Statistical Analyses Listed by Dr. Kider

##### Autocorrelation Test
Autocorrelation "is the correlation of a signal with a delayed copy of itself as a function of delay. Informally, it is the similarity between observations as a function of the time lag between them. The analysis of autocorrelation is a mathematical tool for finding repeating patterns," (https://en.wikipedia.org/wiki/Autocorrelation). It is important to note here that SPSS, the statistical software of choice, automatically does both autocorrelation and partial autocorrelation. Thus, both will be shown here.

In order to complete this test in SPSS these are the steps I followed:

* **Step 1:**
![](images/AutocorrelationStep1.png?raw=true)

* **Step 2:**
![](images/AutocorrelationStep2.PNG?raw=true)

Below are the Autocorrelation and Partial Autocorrelation test result for the 5 RNG data sets:
* **MT RNG**
![](images/AutoMT.PNG?raw=true)

* **Knuth-B Generator**
![](images/AutoKunth.PNG?raw=true)

* **Minimal Standard Random Generator**
![](images/AutoMS.PNG?raw=true)

* **Ranlux 48 Generator**
![](images/AutoRanlux.PNG?raw=true)

* **Sobol**
![](images/AutoSobol.PNG?raw=true)

**I did not actually *interperate* the results**

##### Kolmogorov-Smirnov Test (K-S Test)
The K-S test can be utilized in two different ways. K-S can be used as a goodness of fit test in which it examined the normality of a distribution (https://en.wikipedia.org/wiki/Kolmogorov%E2%80%93Smirnov_test), meaning it tests "whether the distribution as a whole deviated from a comparable normal distribution (Field, 2009). For Part 1a I used a continuous uniform distribution, and as such, this type of K-S test would be inappropriate. However, I can still use a K-S test which compares the "equality of continuous, one-dimensional probability distributions that can be used to compare a sample with a reference probability distribution (one-sample K–S test), or to compare two samples (two-sample K–S test; https://en.wikipedia.org/wiki/Kolmogorov%E2%80%93Smirnov_test#Kolmogorov_distribution). This distintion is important because, in SPSS, which is my chosen analysis software, the former is simply refered to as "Kolmogorov-Smirnov" and the later is refered to as "Kolmogorov-Smirnov Z"

In order to complete this test in SPSS these are the steps I followed:
* **Step 1:**
![](images/KSUniformMTRNG.png?raw=true)

* **Step 2:**
![](images/KSUniformMTRNG2.png?raw=true)

Below are the KS test result for the 5 RNG data sets:

* **MT RNG**
![](images/KSUniformMTRNGResults.JPG?raw=true)

* **Knuth-B Generator**
![](images/KSUniformKunthBRNGResults.JPG?raw=true)

* **Minimal Standard Random Generator**
![](images/KSUniformMinStandRNGResults.JPG?raw=true)

* **Ranlux 48 Generator**
![](images/KSUniformRanlux48RNGResults.JPG?raw=true)

* **Sobol**
![](images/KSUniformSobolRNGResults.JPG?raw=true)

**I did not actually *interperate* the results**

##### Pearson's Chi-Squared Test (Goodness of Fit)
A Pearson's Chi-Square test is used when "comparing the frequencies you observe in certian categories to the frequencies you might expect to get in those categories by chance," (Field, 2009).The Pearson's Chi Squared-Test can be used to check for uniform distribution (Law, 2008), which would lead me to think that this would be an appropriate test to run for the present data. However, the Pearson's Chi Squared test should be used when dealing with categorical data (e.g., yes/no; Field, 2009; https://en.wikipedia.org/wiki/Chi-squared_test). In this case my variables are not categorial, but are in fact Ratio variables (Field, 2008), as such, this test would be inappropriate in the instance.

##### Spearman’s Rank Correlation Coefficient
The Spearman's Rank Correlation Coefficient test is a non-parametric test "so it can be used when the data have violated parametric assumptions such as non-normally distributed data," (Field, 2009). In this case I am using a uniform distribution so this would be appropriate. To run the Spearman's Rank Correlation Coefficient test I need a large *N*, if not I should use a Kendall's Tau Test (Field, 2009), which will be used later when varing the sample size. However, I would like to point out that "large" in this instance can be a subjective term. In some fields such as engineering and computer science, a **much** larger *N* is necessary than what is typically expected of fields in social sciences like Psychology and Sociology. In this instance my question would be "What is a large *N* in this instance?" Further,the Spearman's test should be used when dealing with ordinal data (Field, 2009, p.180) In this case my variables are not ordinal, but are in fact Ratio variables (Field, 2008), as such, this test would be inappropriate in the instance. However, Pearson's *r* could be use because it is similar but uses interval or ratio data (Field, 2009, p.180). For the sake of time and brevity (something I'm not ususlaly known for :P) I will move on.

*There are additional tests that would be appropriate for these data sets (see potential statistical tests list for an idea), but for the sake of time, I will continue onto the rest of the assignment.*

### (b) Varying the Amount of Samples
How do things change when the number of samples varries?

The larger the *N* the less uniform the RNG data appears. However, the same obervations about the PNGs versus Sobol mentioned above also hold. It is important to note that one of the limitations of Excel (the program I graphed my results in) is that it does not create vector graphics. Thus, is difficult for the reader to see the difference in the number of *N* sizes. In the future, I would suggest not using Excel as my visualization program and rather another visualization software such as MatLab. However, I am unfamiliar with MatLab and as such I was limited on the amount of time I could learn a new software among the other software we learned for this assignments. However, I tried to remain consistant with the color (associated with RNG type) and scale between each histrogram so they are all meaningful grouped together. Meaning, you can compare them across the *N*s and types of RNGs.

Below is an image of the histograms of each RNG when varying the N.
![](images/VaryingNs.JPG?raw=true)

### (c) Varying (5) Distributions for (1) PRNG and Stats

I will be using the Meresenne Twister to demonstate the differences in distributions because (as stated above) it is a common PRNG and it also passess many statistical tests including the Diehard tests.

#### Types of Uniform Distributions
There are two types of Uniform Distributions: the continuous unifrom distribution and the discrete uniform distribution. The uniform distribution is a prominent distribution type.

>"This prominent role of the U(0,1) distribution stems from the fact that random variates from all other distributions (normal, gamma, binomial, etc.) and relaizations of various random processes (e.g., a nonstationary Poission process) can be obtained by transforming IID random number in a way determined by the desired distribution or process," (Law, 2008, p.389).

* **Uniform Real (Continuous) Distribution**: "for each member of the family, all intervals of the same length on the distribution's support are equally probable,"(https://en.wikipedia.org/wiki/Uniform_distribution_(continuous))
* **Uniform Discrete Distribution**: "is a symmetric probability distribution whereby a finite number of values are equally likely to be observed; every one of n values has equal probability 1/n. Another way of saying "discrete uniform distribution" would be "a known, finite number of outcomes equally likely to happen," (https://en.wikipedia.org/wiki/Discrete_uniform_distribution).

Denoted in the C++ Code as:

		//std::uniform_real_distribution<> dist(0, 0);
        //std::uniform_int_distribution<> dist(0, 0);
        //(Cplusplus.com, 2017)

#### Types of Bernoulli (Yes/No) Distributions

* **Bernoulli**- Probabulity between yes/true/one outcomes and no/false/zero outcomes, can be used for coin tosses (https://en.wikipedia.org/wiki/Bernoulli_distribution)
* **Binomial** - yes/no, discrete, (https://en.wikipedia.org/wiki/Binomial_distribution)
* **Gometric Distribution** - Discrete; two different instances: "The probability distribution of the number X of Bernoulli trials needed to get one success, supported on the set { 1, 2, 3, ...} OR The probability distribution of the number Y = X − 1 of failures before the first success, supported on the set{ 0, 1, 2, 3, ... }." (https://en.wikipedia.org/wiki/Geometric_distribution)
* **Negative Binomial** - Discrete data; "of the number of successes in a sequence of independent and identically distributed Bernoulli trials before a specified (non-random) number of failures (denoted r) occurs. For example, if we define a 1 as failure, all non-1s as successes, and we throw a die repeatedly until the third time 1 appears (r = three failures), then the probability distribution of the number of non-1s that had appeared will be a negative binomial." (https://en.wikipedia.org/wiki/Negative_binomial_distribution)

The Bernoulli distribution types are denoted in the C++ Code as:

        //std::bernoulli_distribution<> dist(0,0);    // example of a Bernoulli distribution
		//std::binomial_distribution<> dist(1,0.5);    // example of a Binomial distribution
		//std::geometric_distribution<> dist(0.5);    // example of a Geometric distribution
		//std::negative_binomial_distribution<> dist(0,0);    // example of a Negative Binomial distribution
        //(Cplusplus.com, 2017)

#### Normal Distribution
* **Normal Distribution**- AKA Gaussian; "to represent real-valued random variables whose distributions are not known," (https://en.wikipedia.org/wiki/Normal_distribution)

Denoted in the C++ Code as:

		//std::normal_distribution<> dist(50,10);    // example of a normal distribution

#### Related to Normal Distribution

* **Lognormal Distibution** - "It resembles the normal distribution in shape but has heavier tails (higher kurtosis)," (https://en.wikipedia.org/wiki/Logistic_distribution)
* **Chi-squared Distribution** - //Related to gamma distribution; "The chi-squared distribution is used in the common chi-squared tests for goodness of fit of an observed distribution to a theoretical one, the independence of two criteria of classification of qualitative data, and in confidence interval estimation for a population standard deviation of a normal distribution from a sample standard deviation. Many other statistical tests also use this distribution, like Friedman's analysis of variance by ranks."(https://en.wikipedia.org/wiki/Chi-squared_distribution)
* **Cauchy Distribution** - "The Cauchy distribution is often used in statistics as the canonical example of a "pathological" distribution since both its expected value and its variance are undefined." (https://en.wikipedia.org/wiki/Cauchy_distribution)
* **Fisher-F Distribution** - "arises frequently as the null distribution of a test statistic, most notably in the analysis of variance, e.g., F-test." (https://en.wikipedia.org/wiki/F-distribution)
* **Student-T Distribution** - Continuous;  "sample size is small and population standard deviation is unknown," (https://en.wikipedia.org/wiki/Student%27s_t-distribution)

Denoted in the C++ Code as:

		//std::lognormal_distribution<> dist(0,0);  //example of a lognormal distribution
		//std::chi_squared_distribution<> dist(0,0);  //example of a Chi-squared distribution
		//std::cauchy_distribution<> dist(0,0);  //example of a Cauchy distribution
		//std::fisher_f__distribution<> dist(0,0);  //example of a Fisher-F distribution
		//std::student_t__distribution<> dist(0,0);  //example of a Student-T distribution
         //(Cplusplus.com, 2017)

#### Other types of Distributions in the C++ Code

* **Piecewise Distributions**
* **Rate-based Distributions**

Denoted in the C++ Code as:

		//Piecewise Distributions
        //std::discrete_distribution<> dist(0,0);    // example of a discrete distribution
		//std::piecewise_constant_distribution<> dist(0,0);    // example of a Piecewise constant distribution
		//std::piecewise_linear_distribution<> dist(0,0);    // example of a Piecewise linear distribution
        //(Cplusplus.com, 2017)

        //Rate-based Distributions
		//std::poisson_distribution<> dist(25);    // example of a Poisson distribution
		//std::exponential_distribution<> dist(0,0);    // example of an Exponential distribution
		//std::gamma_distribution<> dist(0,0);    // example of a Gamma distribution
		//std::weibull_distribution<> dist(0,0);    // example of a Weibull distribution
		//std::extreme_value_distribution<> dist(0,0);    // example of an Extreme Value distribution
        //(Cplusplus.com, 2017)

*Please note here that in the C++ code some of the distribution parameters are not shown*

*Also, there are additional distributions that would be appropriate for these data sets, but for the sake of time, I will continue onto the rest of the assignment.*

Below are the histograms for the different distributions. The raw data is also in the Excel fit on github
![](images/Distributions.JPG?raw=true)

**For this section I would have liked to write out the information a bit more rather than relying on quotes. I would also have liked to work on my graphs a bit more.**

#### Statistical Analyses

##### Biserial and point-biseral correlations
* Specifically for dichotomous variables- e.g., yes/no (Field, 2009)-use for Bernoulli Type Distributions

**I did not get to this part of the assignment**

### (d) 2D Square Results of RNGs with Varying Ns

Below is the graphic of the varying *N*s for the Unit Square Scatter Plot (except for Sobol)**I believe my Sobol is incorrect above and I did not notice until 8pm on Wednesday 3/29. I did not have time to fix it**
![](images/ScatterPlotsNUnit.JPG?raw=true)

Included in the githubfolder is an Excel file with my raw data. I realized *after* I ran the debugger that I could change the unit square output in C++ rather than doing it in Excel by changing the random function to:


	for (unsigned int i = 0; i < N; ++i) {
		randomValue = generator()/100;

And the Sobol function to:

	for (unsigned int i = 0; i < N; ++i) {
		randomValue = 0 + getQuasiRandomNumber(&seed); //*100

*OR* by chaning the range in the uniform distribution code.

### (e) 2D Square Results of RNGs with Varying Distributions

**I did not get to this part of the assignment**

### (f) 2D Circle Results of RNGs with Varying Ns and Distributions

With the raw data from the Excel file, I started to work on converting the cartesian to polar coordinates as explained in the [Piazza post](https://webcourses.ucf.edu/courses/1246518/external_tools/11900).

Below is a snapshot of what I got working. I have *half* a circle-ish thing.
![](images/StartingCircle.JPG?raw=true)

**I did not finish this part of the assignment**

## Part 2 - Snakes and Ladders (Discrete Event Markov Chains and Monte Carlo Simulations)

### Background/Context on Snakes and Ladders
The classic game has 100 positions on the board. You toss one die, and move squares based on the result of the die. If you land on a ladder you move up the ladder to a higher numbered square. If you land on a snake's mouth, you descend to a lower numbered square. For purposes of simulation, we will add one extra square 0 (starting position). So there are 101 positions on the board.

The game is **memoryless** - your progression to the next position is independent of how you arrived there (opposed to Blackjack or Candyland where your progression is based on what cards have been drawn). A Markov Chain defines the probability of a move from state *i* to state *j* by a **Transition Matrix**, *T*. So in the case of *Snakes and Ladders* the dimensions of a transition matrix is 101x101.

For a more comprehensive historical and theoretical background visit [here](http://www.datagenetics.com/blog/november12011/).

**Pulled directly from assignment instructions*


### (a) Null State Game transition matrix
The Null State Game Matrix is denoted in the C++ code as:

 	int size = 101;  //TODO -this shoudl be 101
	Eigen::MatrixXf TransitionMatrix(size, size);
	Eigen::VectorXf v(size);

	unsigned int ROLLS = 100; //TODO-pick a random number???/?

	double prob = 1.0/6.0 ;  //TODO- from classvoid SetTransitionMatrix() //TODO -from class
	{
	TransitionMatrix.setZero();
	for (int i = 0; i < TransitionMatrix.rows() - 6; i++)
	{
		TransitionMatrix(i, i + 1) = prob;
		TransitionMatrix(i, i + 2) = prob;
		TransitionMatrix(i, i + 3) = prob;
		TransitionMatrix(i, i + 4) = prob;
		TransitionMatrix(i, i + 5) = prob;
		TransitionMatrix(i, i + 6) = prob;
	} //class notes still need to hard code the last 6 rows: 95-101

		//Rows 95-101 with help from study group
		TransitionMatrix(95, 96) = prob;
		TransitionMatrix(95, 97) = prob;
		TransitionMatrix(95, 98) = prob;
		TransitionMatrix(95, 99) = prob;
		TransitionMatrix(95, 100) = prob * 2;

		TransitionMatrix(96, 97) = prob;
		TransitionMatrix(96, 98) = prob;
		TransitionMatrix(96, 99) = prob;
		TransitionMatrix(96, 100) = prob * 3;

		TransitionMatrix(97, 98) = prob;
		TransitionMatrix(97, 99) = prob;
		TransitionMatrix(97, 100) = prob * 4;

		TransitionMatrix(98, 99) = prob;
		TransitionMatrix(98, 100) = prob * 5;

		TransitionMatrix(99, 100) = 1;

		TransitionMatrix(100, 100) = 1;

		std::cout << TransitionMatrix << std::endl;
		exit(1);
	}

**Below is a list of items I would have liked to include in the final draft if given more time.**

I did not include checks in my code. I would like to have done this. In addition to the checks mentioned in the asignment, I would have also like to implement a check for the rolls to stop at a certain point.**


### (b) Simulate and analyze the results of Null State Game
What is the modal number of moves required by a single player to finish the game?

#### (1) Markov Chain:

Denoted in the code as:

 	int main(){

	SetTransitionMatrix();

	//Output Vector
	v.setZero();
	v(0) = 1.0;

	// Print Results to File

	std::ofstream myfile;
	myfile.open("markov_results.txt");

    // TODO add Markov vector - Matrix multiplication
	v = v.transpose()*TransitionMatrix;// went over this in class but edited with study group
    //this is the only part I did and we went over it in the study group

	std::cout << v << std::endl;
	myfile << v << std::endl;
	//http://www.cplusplus.com/doc/tutorial/files/
	//this is just a sample, becareful how you print to file so you can mine useful stats

	myfile.close();

#### (2) Monte Carlo:

Denoted in the code as:

	//TODO (add DTMC, and histogram lines.)
	discreteMC = DTMC(TransitionMatrix, ROLLS, start);
	++hist[std::round(discreteMC.back())];

	// Code if you wanted to print out results at each step
	for (auto elem : discreteMC)
	std::cout << elem << std::endl;

Produce graphs to analyze the results and show how the game evolves over time for both methods. Plot useful statistics of the results such as percentage chance of finishing the game in n-moves, cumulative probability of finishing the game in n-moves, and other ways to convey useful information of the results. **TODO**

### (c) Simulate and analyze the results of Snakes and Ladders


Ladders From  | Ladders To | |  Snakes From  | Snakes To
-------- | -------- | ------------- | -------- | -------- 
3|19| |11|7
15|37| |18|13
22|42| |28|12
25|64| |36|34
41|73| |77|16
53|74| |47|26
63|86| |83|39
76|91| |92|75
84|98| |99|70

Using the table above, This is the code I put in the C++ file:

	void ModifyTransitionMatrix() {
	TransitionMatrix.setZero();
	for (int i = 0; i < TransitionMatrix.rows(); i++)
	{

		//All Ladders

		if (TransitionMatrix(i, 3) > 0) {
			// L: 3-->19
			TransitionMatrix(i, 19) = prob;
			TransitionMatrix(i, 3) = 0;
		}

		if (TransitionMatrix(i, 15) > 0) {
			// L: 15-->37
			TransitionMatrix(i, 37) = prob;
			TransitionMatrix(i, 15) = 0;
		}

		if (TransitionMatrix(i, 22) > 0) {
			// L: 22-->42
			TransitionMatrix(i, 42) = prob;
			TransitionMatrix(i, 22) = 0;
		}

		if (TransitionMatrix(i, 25) > 0) {
			// L: 25-->64
			TransitionMatrix(i, 64) = prob;
			TransitionMatrix(i, 25) = 0;
		}

		if (TransitionMatrix(i, 41) > 0) {
			// L: 41-->74
			TransitionMatrix(i, 74) = prob;
			TransitionMatrix(i, 41) = 0;
		}

		if (TransitionMatrix(i, 53) > 0) {
			// L: 53-->74
			TransitionMatrix(i, 74) = prob;
			TransitionMatrix(i, 53) = 0;
		}

		if (TransitionMatrix(i, 63) > 0) {
			// L: 63-->86
			TransitionMatrix(i, 86) = prob;
			TransitionMatrix(i, 63) = 0;
		}

		if (TransitionMatrix(i, 76) > 0) {
			// L: 76-->91
			TransitionMatrix(i, 91) = prob;
			TransitionMatrix(i, 76) = 0;
		}

		if (TransitionMatrix(i, 84) > 0) {
			// L: 84-->98
			TransitionMatrix(i, 98) = prob;
			TransitionMatrix(i, 84) = 0;
		}

		//All Snakes

		if (TransitionMatrix(i,11) > 0) {
			// S: 11-->7
			TransitionMatrix(i, 7) = prob;
			TransitionMatrix(i, 11) = 0;
		}

		if (TransitionMatrix(i, 18) > 0) {
			// S: 18-->13
			TransitionMatrix(i, 13) = prob;
			TransitionMatrix(i, 18) = 0;
		}

		if (TransitionMatrix(i,28) > 0) {
			// S: 28-->12
			TransitionMatrix(i, 12) = prob;
			TransitionMatrix(i, 28) = 0;
		}

		if (TransitionMatrix(i, 36) > 0) {
			// S: 36-->34
			TransitionMatrix(i, 34) = prob;
			TransitionMatrix(i, 36) = 0;
		}

		if (TransitionMatrix(i, 77) > 0) {
			// S: 77-->16
			TransitionMatrix(i, 16) = prob;
			TransitionMatrix(i, 77) = 0;
		}

		if (TransitionMatrix(i, 47) > 0) {
			// S: 47-->26
			TransitionMatrix(i, 26) = prob;
			TransitionMatrix(i, 47) = 0;
		}

		if (TransitionMatrix(i, 83) > 0) {
			// S: 83-->39
			TransitionMatrix(i, 39) = prob;
			TransitionMatrix(i, 83) = 0;
		}

		if (TransitionMatrix(i, 92) > 0) {
			// S: 92-->75
			TransitionMatrix(i, 75) = prob;
			TransitionMatrix(i, 92) = 0;
		}

		if (TransitionMatrix(i, 99) > 0) {
			// S: 99-->70
			TransitionMatrix(i, 70) = prob;
			TransitionMatrix(i, 99) = 0;
		}
	}
    }

Run the same simulation and analyze your results similar to part (b) for the proper game of *Snakes and Ladders* for both methods. How often are the snakes and ladders used, how do the probability of finishing change, etc? What is the maximum and expected amount of moves for the game? Use charts and graphs to illustrate these points.

**I did not get to this part**

In an ideal world, if I had more time I would have programed it to run many more times in order to find the percentage chance of finishing game in *n*-moves.

Here is an example of a graph that shows the Percentage change of finishing in n-moves for another version of snakes and ladders (**it has different S&L postions**):

![](images/m1.png?raw=true)
[Source](http://www.datagenetics.com/blog/november12011/)

Some observations from this graph (taken from above source):
* In this graph the shortest game was **7** rolls
* The game was most often finished in 20 rolls (mode-peak of graph)

Further, I would have liked to have shown the cumulative probability of finishing the games in n rolls.

Here is an example:
![](images/m2.png?raw=true)
[Source](http://www.datagenetics.com/blog/november12011/)

Some observations from this graph(taken from above source):
* The Median number of rolls was **29**
* The Mean number was **32.6**

Another observation from this [source](http://www.datagenetics.com/blog/november12011/) was that not all ladders are equal. Below are histograms of the count implements each time a person landed on a ladder or snake "head":

Ladder|Snakes
-------- | --------
![](images/lad.png?raw=true)|![](images/sna.png?raw=true)

**I was unsure of how to print out the results**

### (d) Think
If these games are built entirely on chance, do they require any strategy? Is it really a *game*, would you rather play games of chance or games of strategy?

**I did not get to this part**

## Part 3 - Discrete Event Simulation - Queue Simulation (30 pts)

### Background/Context on Airport Queueing Simulation
This problem will look at queues and commonly used performance measures. For this problem we will look to design a simple airport security check. We will make the following assumptions: (1) there is only one airline - Southwest; (2) passengers' interarrival times are independent and identically distributed (IID) with an exponential distribution with mean 1 / lambda. The service times are also assumed to be IID and exponentially distributed random variables with mean 1 / mu.

<BR>![](images/queue.png?raw=true)<BR>

When a passanger arrives they have to wait in a queue to present their ID and ticket to the gate agent with all the other passengers. Once approved by the agent they will have to pass through a security check. Since this is Orlando, there are only 3 open metal/screening devices open and again passangers have to wait in a queue. After passing through security you again have to wait in a queue to board your plane.

**Pulled directly from assignment instructions*


### (a) Airport Set up in C++

For each of the 5 queues:
* Add *mu*
* Add acceptance of arrivals characteristics

This is denoted in the C++ code as:

 	  MM1_Queue Checkin;
	   Checkin.set_file_names("Checkin_log.txt", "Checkin_wait.txt", "Checkin_service.txt");
	   Checkin.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Checkin.set_mu(53);
	   Checkin.initialize();
	   Checkin.set_seed(rd(), rd());

	   MM1_Queue Securityone;
	   Securityone.set_file_names("Securityone_log.txt", "Securityone_wait.txt", "Securityone_service.txt");
	   Securityone.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Securityone.set_mu(20);
	   Securityone.autogenerate_new_arrivals(false);
	   Securityone.initialize();
	   Securityone.set_seed(rd(), rd());

	   MM1_Queue Securitytwo;
	   Securitytwo.set_file_names("Securitytwo_log.txt", "Securitytwo_wait.txt", "Securitytwo_service.txt");
	   Securitytwo.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Securitytwo.set_mu(20);
	   Securitytwo.autogenerate_new_arrivals(false);
	   Securitytwo.initialize();
	   Securitytwo.set_seed(rd(), rd());

	   MM1_Queue Securitythree;
	   Securitythree.set_file_names("Securitythree_log.txt", "Securitythree_wait.txt", "Securitythree_service.txt");
	   Securitythree.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Securitythree.set_mu(20);
	   Securitythree.autogenerate_new_arrivals(false);
	   Securitythree.initialize();
	   Securitythree.set_seed(rd(), rd());

	   MM1_Queue Departure;
	   Departure.set_file_names("Departure_log.txt", "Departure_wait.txt", "Departure_service.txt");
	   Departure.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Departure.set_mu(80);
	   Departure.initialize();
	   Departure.set_seed(rd(), rd());
       //from Piazza

### (b) Add a check that your process is within an error range, process next event, and add external arrivals where marked.

* Check for error range - per the assignment directions the error range will be 0.002
* Process the next event
* Add an external arrival where marked

This is denoted in the C++ code as:

	   for (;
		//TODO: add is_within_error_range check
	   !Checkin.is_within_error_range(0.002) ||
	   !Securityone.is_within_error_range(0.002) ||
	   !Securitytwo.is_within_error_range(0.002) ||
	   !Securitythree.is_within_error_range(0.002)
       ;)
 	  {
	   Customer cust  = Checkin.process_next_event();   // =  TODO: process next event;
	   Customer cust2 = Securityone.process_next_event();  // =  TODO: process next event;
	   Customer cust3 = Securitytwo.process_next_event();  // =  TODO: process next event;
	   Customer cust4 = Securitythree.process_next_event();  // =  TODO: process next event;
	   Customer cust5 = Departure.process_next_event();  // =  TODO: process next event; //TODO: one more process_next_event for the last object.

       if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
				Securityone.add_external_arrival();
                 break;
            case 1:
				//TODO add_external_arrival() for your security gates;
				Securitytwo.add_external_arrival();
                 break;
            case 2:
                //TODO add_external_arrival() for your security gates;
				Securitythree.add_external_arrival();
                 break;
          }
          next++;
          if (next%3==0) next = 0;
       }
       if (cust2.get_type() == Customer::COMPLETED() || cust3.get_type() == Customer::COMPLETED() || cust4.get_type() == Customer::COMPLETED())
       {
		   //TODO add_external_arrival(); on your final boarding MM1_Queue object
		   Departure.add_external_arrival();
       }

### (c) Add code to caculate the expected results for:

 * expected_server_utilization
 * expected idle prob
 * expected queue length
 * expected number customers
 * expected waiting time
 * expected response time

This is denoted in the C++ code as:

	//From slides on Webcourses but went over with study group. Particularly they helped me with expected_server_utilization_^2 which was giving me an error.
      //TODO---------------------------------------------
      expected_server_utilization_ = lambda_/mu_;
      expected_idle_prob_ = 1 - expected_server_utilization_;
      expected_queue_length_ = (expected_server_utilization_*expected_server_utilization_)/(expected_idle_prob_);
      expected_number_customers_ = expected_server_utilization_*expected_idle_prob_*(1/(expected_idle_prob_*expected_idle_prob_));
      expected_waiting_time_ = expected_server_utilization_/(mu_-lambda_);
      expected_response_time_ = 1/(mu_ - lambda_);
      // ------------------------------------------------

### (d) Output and generate data and plot and analyze the useful statistics/results in the program of your choice

#### Output and Generate Data
This is denoted in the C++ code as:

    //TODO Output statistics airport senario.
	Checkin.get_current_time();
	Checkin.plot_results_output();
	Securityone.get_current_time();
	Securityone.plot_results_output();
	Securitytwo.get_current_time();
	Securitytwo.plot_results_output();
	Securitythree.get_current_time();
	Securitythree.plot_results_output();
	Departure.get_current_time();
	Departure.plot_results_output();

	Checkin.output(); cout << endl << endl;
	Securityone.output(); cout << endl << endl;
	Securitytwo.output(); cout << endl << endl;
	Securitythree.output(); cout << endl << endl;
	Departure.output(); cout << endl << endl;
    //from Piazza but went over with study group

#### Statistical Analyses

**I did not get to this part of the assignment, but I did print out values (see below)**
![](images/Outputfiles.JPG?raw=true)

### (e) Set up Same Airport Queue in Anylogic
In anylogic I set up a Logic Model with the same characteristics/parameters as above.

![](images/AnylogicModel2.JPG?raw=true)

## Part 4 - Implementing Extra Features (10 pts)

### (10 Points) - Add a 2D visualization to AnyLogic for Part 3
For my required extra features I implemented a 2d Anylogic Model for Part 3

![](images/AnylogicModel2D.JPG?raw=true)

## Part 5 - Final Report
The present Readme file is presented to (*hopefully*) fullfill this requirement.

## Extra Features (Extra Credit - 25pts)

### (10 Points) - Add a 3D visualization to AnyLogic for Part 3
Additionally, I added a 3D model in Anylogic for extra credit
![](images/AnylogicModel3D.JPG?raw=true)

> <a href="http://www.youtube.com/watch?feature=player_embedded&v=1-Ov-0zVLng" target="_blank"><img src="http://img.youtube.com/vi/1-Ov-0zVLng/0.jpg" alt="Anylogic" width="850" height="490" border="1" /></a>
>

### (5 Points) - Pick a research problem. Compare and contrast different software packages. Convince me and come to a conclusion.

#### Background/Context

For my dissertation I am investigating whys in which to optimize resources within interdiciplinary graduate programs using the M&S program as a case study. Some background informaiton: graduate programs are stuctured differently from undergraduate programs (i.e. students have different needs) and interdiciplinary programs rely on shared resource compared to traditional programs. I am MOST interested in ways to support students with said research to increase both degree completion and success after degree (job placement, job performance, etc.). However, there are limitations to this with the current data available to me. I expect to have to collect data. "Student success" isn't only realted to the resources avaiilable but also the relationship between the students (and facult), how the students (and facult) behave, and how the students move through the system (i.e., the curriculum). Thus there are both discrete event and agent-based elements to this problem.

Additionally, the software will need to be easy to understand/use -- not only for my understanding since I am limited in my experience with most simulation software programs but also because my end user will mostly likely be program administration (especially since this could be generalizable outside of M&S). I intend for this simulation software to produce useful results for administrators to use toward making arguments to upper level administroators, supporting requests for additional resources. Further, this could be used to optimize the *limited* resource availble during budget cuts.

Further, as my dissertaiton project is unfunded. I will need to utilize a program that is cheap and/or free. This could be in the form of a student version of a commerical software program. However, that may limit me based on the capability of the program. Additionally, I also imageine the program being cheap and/or free will be appealing to the end user as well.

In summary, the simulation software requirements include:
* needs to have both discrete event and agent-based capability
* needs to be easy to understand/use
* need to be cheap or free

#### Quick Investigation

I looked for various types of simulation software for both discrete event and agent-based capabilities. Here is the list I found:

|Agent Based| Discrete Event|
|--------------|--------------|
|A3/AAA, Able, ADK, AgentBuilder, AgentService, AgentSheets, Altreva, **Anylogic**, AOR Simulation, Ascape, BDI4 Jade, Behavior Composer, Boris, Brahms, Breve, Construct, Cormas, Cougaar, CybelePro, Dali, Descartes, DeX, DigiHive, D-OMAR, ECHO, EVE, FAMOJA, FLAME, FLAME GPU, FLUXY, Framsticks, GPU Agents, GROWlab, ICARO-T, iGen, Insight Maker, JABM, JADE, Jade’s sim++, JAMEL, Janus, JASA, JAS-mine, Jason, JCA-Sim, jEcho, jES, JESS, JIAC, LSD, MacStarLogo, MaDKit, MAGSY, MAML, MASON, MASS, MAS-SOC, Mesa, MIMOSE, Moduleco, MOOSE, NetLogo, OBEUS, Omonia, OpenOME, OpenStarLogo, oRIS, PS-I, Repast, SDML, SEAS, SeSAm, SimAgent, SimBioSys, SimPack, SimPlusPlus, Soar, Spatial Modeling Environment, StarLogoT, StarLogoTNG, StartLogo, Sugarscape, Swarm, TerraME, VisualBots, VSEit, Xholon, Zeus | **AnyLogic**, ARENA*, Care pathway simulatior, CPN Tools, DESMO-J, Enterprise Dynamics, ExtendSim, Facsimile, Flex Sim, GoldSim, GPSS, JaamSim, MS4 Modeling Environment, NetSim, Plant Simulation, PowerDEVS, ProModel, Ptolemy II, SIM.JS,Simcad Pro, SimEvents, Simio, SIMUL8, Simula, SystemC
**Not on Wikipedia List*
(https://en.wikipedia.org/wiki/Comparison_of_agent-based_modeling_software)
(https://en.wikipedia.org/wiki/List_of_discrete_event_simulation_software)

#### Conclusion

As you can see from the table above, the *only* software program that shows up twice is Anylogic. While some of these software programs use base languages like C++, I dont think the end user will want to use/learn a new langugae for this problem. Anylogic is easy to use (drag and drop interface), is available as a free trial version or free student version, and can supposrt discrete, angent based and sytem dynamics modeling (http://www.anylogic.com/). It meets all of my above requirements. Additionally, the 2D and 3D capabilities make it easy for the end user and any high level decision makers to easily *visualize* the benefits of interdiciplinary graduate program resource allocation andoptimization.

Thus, **Anylogic** is my simulation program of choice.

**I did not get a chance to sketch up my framework**

### (20 Points) - Complete Part 2 with a different board game.

**Not doing this, but interesting note, I found a step-by-step guide on how to implement Blackjack in C++ in the Dawson (2008) book. However, I would rather focus on the dissertation related extra credit above. :)**

## References

* Cplusplus.com (2017). <random>. Retrived from http://www.cplusplus.com/reference/random/
* Dawson, M. (2008). Beginning C++ Through Game Programming (2nd ed.). Boston. MA: Course Technology
* Demchik (2010). Pseudo-random number generators for Monte Carlo simulations on Graphics Processing Units. Retrived from https://arxiv.org/pdf/1003.1898.pdf
* Dutang, C. & Wuertz, D. (2009). A note of random number generation. Retrived from webcourses materials
* Field, A. (2009). DIscovering statistics using SPSS (3rd ed.) London; SAGE Publications.
* Kider, J. (2017). Pseudo-random generation [Webcourse Page]. Retrieved from Notes Online Web site: https://webcourses.ucf.edu/courses/1246518/pages/pseudo-random-generation?module_item_id=10541639
* Law, A.M. (2008). Simulation and Modeling Analysis (4th ed). New Delhi, McGrawHill.
* Park, S.K & Miller, K.W. (1988). Random number generators: Good ones are hard to find. ACM October 1988 V. 31 N. 10.

*Mulitple Wikipedia, Webcourse, and C++ pages were used as reference. For readability I just put the links for each page next to the associated material*

* People I works with for Part 1:
	* Karla Badillo-Urquiola
* People I worked with for Part 2:
	* Sarah Matthews
	* Keith MacArthur
	* Cory Hendricks
	* Joey Netterville
	* Karla Badillo-Urquiola
* People I worked with for Part 3 (Anylogic set-up-2D and 3D I did on my own):
	* Sarah Matthews
	* Cory Hendricks

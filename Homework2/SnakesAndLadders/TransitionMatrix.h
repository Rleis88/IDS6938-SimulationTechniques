int size = 101;  //TODO -this shoudl be 101
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);

unsigned int ROLLS = 45; //TODO
// should check if it goes over the threshold if time http://www.datagenetics.com/blog/november12011/

double prob = 1.0/6.0 ;  //TODO- from class

void SetTransitionMatrix() //TODO -from class
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

//we talked about this in the study group but I was half paying attention. What we went over didnt work for me (it looked the same as my null). 
//However, Mac explained it differently. The way he explained it made more sense, so I changed it. 
	//The zero probability should go after. the other one should be the addition of the other---if that makes sense?????

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
//it still looks the same to me but eh whatever.
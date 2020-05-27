struct Student {
	int index;
	int self_estimation;
	int pair_estimation;
	bool sex; //True - studentka, false - student.

	Student(bool sex) {
		this->sex = sex;
	}
};
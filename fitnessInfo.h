#ifndef FITNESSINFO_H
#define FITNESSINFO_H

class fitnessInfo {		//Class to store weight and height data
private:
	double weight, height;

public:
	fitnessInfo() {
		weight = height = 0;
	}
	~fitnessInfo() {
		weight = height = 0;
	}
	void setFitnessInfo(double w, double h) {
		weight = w;
		height = h;
	}
	double getWeight() {
		return weight;
	}
	double getHeight() {
		return height;
	}
};
#endif

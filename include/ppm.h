#pragma once
#include <string>
#include <eigen3/Eigen/Dense>
#include <vector>




class PPM
{
private:
	std::string file_name;
	std::vector<Eigen::Vector3f> data;
	int height, width;

public:
	PPM(std::string file_name_,int width,int height);
	void setpixel(int x, int y, Eigen::Vector3f pixel);

	std::vector<Eigen::Vector3f>& getData();
	void write_file();


};
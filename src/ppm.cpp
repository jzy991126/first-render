#include "ppm.h"
#include "utils.h"
#include <cmath>

PPM::PPM(std::string file_name_, int width, int height):width(width),height(height)
{
	file_name = file_name_ + ".ppm";
	data.resize(width * height, Eigen::Vector3f(0.0,0.0,0.0));
}

void PPM::setpixel(int x, int y, Eigen::Vector3f pixel)
{
	data[y * width + x] = pixel;
}

void PPM::write_file()
{

	FILE* fp = fopen(file_name.c_str(), "wb");
	(void)fprintf(fp, "P6\n%d %d\n255\n", width, height);
	for (auto i = 0; i < height * width; ++i) {
		static unsigned char color[3];
		color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, data[i].x()), 0.6f));
		color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, data[i].y()), 0.6f));
		color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, data[i].z()), 0.6f));
		fwrite(color, 1, 3, fp);
	}
	fclose(fp);
}
std::vector<Eigen::Vector3f>& PPM::getData()
{
	return data;
}


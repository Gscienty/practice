
#include <malloc.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
	using namespace cv;

	int input_size = 5;
	int disp_width = 10;

	int block_width = disp_width * (input_size - 1);
	std::vector<IplImage*> srcs;
	//input image
	char tmp_filename[128] = { 0 };
	unsigned char tmp_stack[10] = { 0 };
	unsigned char tmp_stack_ptr = 0;
	unsigned char filename_ptr = 0;
	for (int i = 1; i <= input_size; i++) {
		//initialize ptr
		filename_ptr = 0;
		tmp_stack_ptr = 0;
		int tmp = i;
		//fill stack
		while (tmp != 0) {
			tmp_stack[tmp_stack_ptr++] = tmp % 10;
			tmp /= 10;
		}
		//fill filename
		while (tmp_stack_ptr) {
			tmp_filename[filename_ptr++] = tmp_stack[--tmp_stack_ptr] + 48;
		}
		tmp_filename[filename_ptr] = 0;
		strcat_s(tmp_filename, ".jpg");
		//input image
		srcs.push_back(cvLoadImage(tmp_filename));
	}

	IplImage* result = cvCreateImage(cvSize(srcs[0]->width * srcs.size(), srcs[0]->height), IPL_DEPTH_8U, 3);

	//build moer
	for (int i = 0; i < srcs.size(); i++) {
		int result_offset = i * disp_width;
		int image_offset = 0;
		while (image_offset + disp_width < srcs[i]->width) {
			cvSetImageROI(result, cvRect(result_offset, 0, disp_width, srcs[i]->height));
			cvSetImageROI(srcs[i], cvRect(image_offset, 0, disp_width, srcs[i]->height));
			cvAddWeighted(result, 0, srcs[i], 1, 0, result);
			cvResetImageROI(result);
			cvResetImageROI(srcs[i]);
			result_offset += block_width + disp_width;
			image_offset += disp_width;
		}
	}
	cvSaveImage("result.jpg", result);
	return 0;
}

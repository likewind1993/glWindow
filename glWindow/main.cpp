#include "Bmp.h"
using namespace image;


int main() {
	Bmp bmp =  Bmp();
	bmp.Read("test.bmp");
	bmp.PrintSelf();

	return 0;
}
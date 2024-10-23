#include <string.h>
class Pixel {
private:
	int R;
	int G;
	int B;
public:
	Pixel(int r = 0, int g = 0, int b = 0);
	int GetR();
	int GetG();
	int GetB();
	void SetR(int r);
	void SetG(int g);
	void SetB(int b);
	int GetGray();
};

class Image {
private:
	int width;
	int height;
	Pixel** pixels;
	int hello;
public:
	Image(int width, int height);
	~Image();
	int GetHeight();
	int GetWidth();
	Pixel GetPixel(int x, int y);
	void Resize(int NewW, int NewH);
	void SetPixel(int x, int y, Pixel& pixel);
};

class Palette {
private:
	Pixel* pixels;
	int size;
	int capacity;
public:
	Palette(int InitCapaity = 10);
	~Palette();
	int GetSize();
	int GetCapacity();
	void Clear();
};

class Filter {
public:
	Image Apply(Image image);
};

class BlackAndWhite {
public:
	Image Apply(Image image);
};

class BrightnessFilter : public Filter {
private:
	int brightness;

public:
	BrightnessFilter(int level);
	Image Apply(Image image);
};

class PhotoEditor {
private:
	Image image;
	Filter** filters;
	int FilterCount;
public:
	void ApplyFilter(Filter* filter);
	void ShowImageInfo();
};

class Gradient {
private:
	Pixel StartColor;
	Pixel EndColor;
public:
	Gradient(Pixel start, Pixel end);
	Image Apply(Image image);

};


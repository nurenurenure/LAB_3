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
	int Clear();
};

class Filter {
private:
	int level;
public:
	void Apply(Image& image);
};

class BlackAndWhite {
public:
	void Apply(Image& image);
};

class BrightnessFilter : public Filter {
private:
	int brightness;

public:
	BrightnessFilter(int level);
	void Apply(Image& image);
};

class ResizeImage {
public:
	void Resize(Image& image, int newWidth, int newHeight);
};


class PhotoEditor {
private:
	Image image;
	Filter** filters;
	int FilterCount;
};


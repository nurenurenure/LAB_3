#include "header.h"
#include <iostream>


//работа с ПАЛИТРОЙ
Palette::Palette(int InitialCapacity) : size(0), capacity(InitialCapacity) {
	pixels = new Pixel[capacity];
}

Palette::~Palette() {
	delete[] pixels;
}

int Palette::GetSize() {
	return size;
}

int Palette::GetCapacity() {
	return capacity;
}

void Palette::Clear() {
	size = 0;
}

//работа с ИЗОБРАЖЕНИЕМ
Image::Image(int w, int h) : width(w), height(h) {
	pixels = new Pixel* [height];
	for (int i = 0; i < height; i++) {
		pixels[i] = new Pixel[width];
	}
}
Image::~Image() {
	for (int i = 0; i < height; i++) {
		delete[] pixels[i];
	}
	delete[] pixels;
}

int Image::GetHeight() {
	return height;
}

int Image::GetWidth() {
	return width;
}

Pixel Image::GetPixel(int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return pixels[y][x];
	}
	return Pixel();  // Возвращаем черный пиксель по умолчанию
}
void Image::SetPixel(int x, int y, Pixel& pixel) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		pixels[y][x] = pixel;
	}
}


void Image::Resize(int newWidth, int newHeight) {
	Pixel** newPixels = new Pixel * [newHeight];
	for (int i = 0; i < newHeight; i++) {
		newPixels[i] = new Pixel[newWidth];
	}

	int minWidth = (newWidth < width) ? newWidth : width;
	int minHeight = (newHeight < height) ? newHeight : height;

	for (int y = 0; y < minHeight; y++) {
		for (int x = 0; x < minWidth; x++) {
			newPixels[y][x] = pixels[y][x];
		}
	}

	for (int i = 0; i < height; i++) {
		delete[] pixels[i];
	}
	delete[] pixels;

	pixels = newPixels;
	width = newWidth;
	height = newHeight;
}

//Работа с классом Pixel
Pixel::Pixel(int r, int g, int b) : R(r), G(g), B(b) {}

int Pixel::GetR() { return R; }
int Pixel::GetG() { return G; }
int Pixel::GetB() { return B; }

void Pixel::SetR(int r) { R = r; }
void Pixel::SetG(int g) { G = g; }
void Pixel::SetB(int b) { B = b; }

int Pixel::GetGray() {
	return (R + G + B) / 3;
}

//работа с фильтрами
void BlackAndWhite::Apply(Image& image) {
	for (int y = 0; y < image.GetHeight(); y++) {
		for (int x = 0; x < image.GetWidth(); x++) {
			Pixel pixel = image.GetPixel(x, y);
			int gray = pixel.GetGray();
			Pixel grayPixel(gray, gray, gray);
			image.SetPixel(x, y, grayPixel);
		}
	}
}

BrightnessFilter::BrightnessFilter(int level) : brightness(level) {}

void BrightnessFilter::Apply(Image& image) {
	for (int y = 0; y < image.GetHeight(); y++) {
		for (int x = 0; x < image.GetWidth(); x++) {
			Pixel pixel = image.GetPixel(x, y);

			int r = std::max(0, std::min(255, pixel.GetR() + brightness));
			int g = std::max(0, std::min(255, pixel.GetG() + brightness));
			int b = std::max(0, std::min(255, pixel.GetB() + brightness));
			Pixel newpixel(r, g, b);
			image.SetPixel(x, y, newpixel);
		}
	}
}
//методы класса PhotoEditor
void PhotoEditor::ApplyFilter(Filter* filter) {
		filters[FilterCount++] = filter;
		filter->Apply(image);
}

void PhotoEditor::ShowImageInfo() {
	std::cout << "Image width: " << image.GetWidth() << ", height: " << image.GetHeight() << std::endl;
}





int main()
{
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

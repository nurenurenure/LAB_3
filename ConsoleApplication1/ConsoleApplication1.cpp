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
Image BlackAndWhiteFilter::Apply(Image image) {
	for (int y = 0; y < image.GetHeight(); y++) {
		for (int x = 0; x < image.GetWidth(); x++) {
			Pixel pixel = image.GetPixel(x, y);
			int gray = pixel.GetGray();
			Pixel grayPixel(gray, gray, gray);
			image.SetPixel(x, y, grayPixel);
		}
	}
	return image;
}

BrightnessFilter::BrightnessFilter(int level) : brightness(level) {}

Image BrightnessFilter::Apply(Image image) {
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
	return image;
}
//методы класса PhotoEditor
void PhotoEditor::ShowImageInfo() {
	std::cout << "Image width: " << image.GetWidth() << ", height: " << image.GetHeight() << std::endl;
}


//методы класса Gradient
Gradient::Gradient(Pixel start, Pixel end) :StartColor(start), EndColor(end) {}
Image Gradient::Apply(Image image) {
		int width = image.GetWidth();
		int height = image.GetHeight();
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// Вычисляем отношение текущей позиции x к ширине изображения
				float ratio = static_cast<float>(x) / (width - 1);

				// Вычисляем цвета пикселей на основе отношения
				int red = static_cast<int>(StartColor.GetR() + ratio * (EndColor.GetR() - StartColor.GetR()));
				int green = static_cast<int>(StartColor.GetG() + ratio * (EndColor.GetG() - StartColor.GetG()));
				int blue = static_cast<int>(StartColor.GetB() + ratio * (EndColor.GetB() - StartColor.GetB()));
				Pixel newpixel(red, green, blue);

				image.SetPixel(x, y, newpixel);
			}
		}
		return image;
}



int main()
{    // Пример использования new и delete
	// Создаем объект Pixel с помощью new
	Pixel* p1 = new Pixel(255, 0, 0);
	std::cout << "Pixel p1: Red = " << p1->GetR() << ", Green = " << p1->GetG() << ", Blue = " << p1->GetB() << std::endl;
	// Удаляем объект Pixel с помощью delete
	delete p1;


// Пример использования new[] и delete[] для работы с массивами

// Создаем массив пикселей с помощью new[]
	Pixel* pixelArray = new Pixel[3];
	pixelArray[0] = Pixel(255, 0, 0); 
	pixelArray[1] = Pixel(0, 255, 0);  
	pixelArray[2] = Pixel(0, 0, 255);  

	std::cout << "Pixel array:" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << "Pixel " << i << ": Red = " << pixelArray[i].GetR()
			<< ", Green = " << pixelArray[i].GetG()
			<< ", Blue = " << pixelArray[i].GetB() << std::endl;
	}


	delete[] pixelArray;

	// Работа со ссылками
	Image* image = new Image(1, 2); 

	// Устанавливаем пиксели
	Pixel pixel1(100, 100, 100);
	Pixel pixel2(50, 50, 50);
	image->SetPixel(0, 0, pixel1);   
	image->SetPixel(0, 1, pixel2);             

	std::cout << "Image size: " << image->GetWidth() << "x" << image->GetHeight() << std::endl;


	delete image;

	// Динамический массив объектов класса Pixel
	int numPixels = 3;
	Pixel* pixelArray2 = new Pixel[numPixels];

	pixelArray2[0] = Pixel(255, 0, 0); 
	pixelArray2[1] = Pixel(0, 255, 0);  
	pixelArray2[2] = Pixel(0, 0, 255);  


	for (int i = 0; i < numPixels; i++) {
		std::cout << "Pixel " << i << ": Red = " << pixelArray2[i].GetR()
			<< ", Green = " << pixelArray2[i].GetG()
			<< ", Blue = " << pixelArray2[i].GetB() << std::endl;
	}
	delete[] pixelArray2;


	// Массив динамических объектов класса Pixel
	Pixel** dynamicPixelArray = new Pixel * [numPixels];  // Массив указателей на Pixel

	// Создаем объекты динамически
	dynamicPixelArray[0] = new Pixel(255, 255, 0); 
	dynamicPixelArray[1] = new Pixel(255, 0, 255);  
	dynamicPixelArray[2] = new Pixel(0, 255, 255);  

	for (int i = 0; i < numPixels; i++) {
		std::cout << "Pixel " << i << ": Red = " << dynamicPixelArray[i]->GetR()
			<< ", Green = " << dynamicPixelArray[i]->GetG()
			<< ", Blue = " << dynamicPixelArray[i]->GetB() << std::endl;
	}

	// Удаляем каждый динамически созданный объект
	for (int i = 0; i < numPixels; i++) {
		delete dynamicPixelArray[i];
	}

	delete[] dynamicPixelArray;
}

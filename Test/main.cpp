#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>

#include <Graphics/ImageLoader.h>

#include <Windows.h>

void XMLTest()
{
	XMLNode *node = XMLLoader::LoadFromFile("d:\\test.xml");
	float d = (*node)[0].GetValueAsFloat();

	uint32_t cyce = (*node)["sss"]["dzieciak2"].GetAttribAsUInt32("cyce");
	float chuj = (*node)["sss"]["dzieciak2"].GetAttribAsFloat("chuj");
}

void PNGTest()
{
	uint8_t *data;
	uint32_t width;
	uint32_t height;
	uint32_t bytesCount;

	ImageLoader::LoadFromFile("c:\\Users\\majak\\Downloads\\titlescreen.png", data, width, height, bytesCount);

	HDC hdc = GetDC(NULL);
	for (uint32_t y = 0; y < height; y++)
		for (uint32_t x = 0; x < width; x++)
		{
			SetPixel(hdc, x + 600, y + 600, RGB(data[y * (width * bytesCount) + x * bytesCount + 0],
												data[y * (width * bytesCount) + x * bytesCount + 1],
												data[y * (width * bytesCount) + x * bytesCount + 2]));
		}

	int dupa = 0;
}

int main()
{
	PNGTest();

	return 0;
}


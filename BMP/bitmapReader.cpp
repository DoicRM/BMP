#include "bitmapReader.hpp"

struct FileHeader {
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} File;

struct PictureHeader {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} Picture;

struct ColorsRGB {
    char R;
    char G;
    char B;
} Rgb;

int BitmapReader::readBitmapFile(const char* fileName)
{
    FILE* file;
    file = fopen(fileName, "rb");

    if (file == nullptr)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        std::cout << "Error occurred opening file: file does not exist." << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        return -1;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    std::cout << "Successfully opened file '" + std::string(fileName) + "'!" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    char c1, c2;
    std::cout << "Do you want to display data of a loaded bitmap? [y/n]: ";
    std::cin >> c1;
    c1 = tolower(c1);

    if (c1 == 'y')
    {
        printBitmapMetadata(file);
        std::cout << std::endl;
    }

    std::cout << "Do you want to create a negative for a loaded bitmap? [y/n]: ";
    std::cin >> c2;
    c2 = tolower(c2);

    if (c2 == 'y')
    {
        createNegative(file);
    }
    else {
        return 0;
    }
}

void BitmapReader::printBitmapMetadata(FILE* file)
{
    std::cout << "\nBITMAP INFORMATION" << std::endl;
    std::cout << "------------------" << std::endl;

    fread(&File.bfType, sizeof(File.bfType), 1, file);
    std::cout << "Type: " << File.bfType << std::endl;

    fread(&File.bfSize, sizeof(File.bfSize), 1, file);
    std::cout << "File size: " << File.bfSize << " bytes" << std::endl;

    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, file);
    std::cout << "Reserved1: " << File.bfReserved1 << std::endl;

    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, file);
    std::cout << "Reserved2: " << File.bfReserved2 << std::endl;

    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, file);
    std::cout << "Image data item: " << File.bfOffBits << std::endl << std::endl;

    fseek(file, 14, SEEK_SET);
    fread(&Picture.biSize, sizeof(Picture.biSize), 1, file);
    std::cout << "Information headline size: " << Picture.biSize << std::endl;

    fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, file);
    std::cout << "Width: " << Picture.biWidth << "px" << std::endl;

    fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, file);
    std::cout << "Height: " << Picture.biHeight << "px" << std::endl;

    fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, file);
    std::cout << "Number of plates: " << Picture.biPlanes << std::endl;

    fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, file);
    std::cout << "Number of bits per pixel (1, 4, 8, or 24): " << Picture.biBitCount << std::endl;

    fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, file);
    std::cout << "Compression (0=none, 1=RLE-8, 2=RLE-4): " << Picture.biCompression << std::endl;

    fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, file);
    std::cout << "Size of the drawing itself: " << Picture.biSizeImage << std::endl;

    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, file);
    std::cout << "Horizontal resolution: " << Picture.biXPelsPerMeter << std::endl;

    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, file);
    std::cout << "Vertical resolution: " << Picture.biYPelsPerMeter << std::endl;

    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, file);
    std::cout << "Number of colors in palette: " << Picture.biClrUsed << std::endl;

    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, file);
    std::cout << "Important colors in palette: " << Picture.biClrImportant << std::endl;
}

int BitmapReader::createNegative(FILE* file)
{
    std::cout << "\nCREATING A NEGATIVE" << std::endl;
    std::cout << "-------------------" << std::endl;

    FILE* negativeFile = fopen("negative.bmp", "wb");

    if (negativeFile == nullptr)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        std::cout << "Error occurred creating file." << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        return -1;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    std::cout << "Successfully created file 'negative.bmp'!" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    fseek(negativeFile, 0, SEEK_SET);
    fwrite(&File.bfType, sizeof(File.bfType), 1, negativeFile);
    fwrite(&File.bfSize, sizeof(File.bfSize), 1, negativeFile);
    fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, negativeFile);
    fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, negativeFile);
    fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, negativeFile);

    fseek(negativeFile, 14, SEEK_SET);
    fwrite(&Picture.biSize, sizeof(Picture.biSize), 1, negativeFile);
    fwrite(&Picture.biWidth, sizeof(Picture.biWidth), 1, negativeFile);
    fwrite(&Picture.biHeight, sizeof(Picture.biHeight), 1, negativeFile);
    fwrite(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, negativeFile);
    fwrite(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, negativeFile);
    fwrite(&Picture.biCompression, sizeof(Picture.biCompression), 1, negativeFile);
    fwrite(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, negativeFile);
    fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, negativeFile);
    fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, negativeFile);
    fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, negativeFile);
    fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, negativeFile);

    fseek(negativeFile, sizeof(File.bfOffBits), SEEK_SET);

    int bmpImg;

    for (int i = File.bfOffBits; i < File.bfSize; i++)
    {
        fseek(file, i, SEEK_SET);
        fseek(negativeFile, i, SEEK_SET);
        fread(&bmpImg, 3, 1, file);
        bmpImg = INT_MAX - bmpImg;
        fwrite(&bmpImg, 3, 1, negativeFile);
    }

    fclose(file);
    fclose(negativeFile);

    std::cout << "Negative creating completed." << std::endl;

    return 0;
}
#pragma once
#include <iostream>
#include <stdio.h>
#include <Windows.h>

class BitmapReader
{
public:
    static int readBitmapFile(const char* fileName);
private:
    static void printBitmapMetadata(FILE* file);
};
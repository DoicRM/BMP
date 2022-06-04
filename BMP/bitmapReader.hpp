#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
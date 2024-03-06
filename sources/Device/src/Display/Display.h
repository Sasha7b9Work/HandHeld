// 2024/03/01 22:45:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Colors.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>


namespace Display
{
    static const int WIDTH = 160;
    static const int HEIGHT = 80;

    static const int NUMBER_PARTS_HEIGHT = 8;          // �� ������� ������ ������ ������. ������� ��� ����� ������������ �����������,
                                                // ����� �������� ������ ��������

    void Init();

    void Update();

    namespace Buffer
    {
        static const uint SIZE = WIDTH * HEIGHT / NUMBER_PARTS_HEIGHT;

        // ���������� ��������� �� ������
        uint8 *GetLine(int y);
    }
}


struct Pixel
{
    void Set(int x, int y, const Color &color = Color::NUMBER) const;
};


struct HLine
{
    HLine(int w) : width(w) { }
    void Draw(int x, int y, const Color &color = Color::NUMBER) const;
private:
    const int width;
};


struct VLine
{
    VLine(int h) : height(h) { }
    void Draw(int x, int y, const Color &color = Color::NUMBER) const;
private:
    const int height;
};


struct Rect
{
    Rect(int w, int h) : width(w), height(h) { }
    void Draw(int x, int y, const Color &color = Color::NUMBER) const;
    void Fill(int x, int y, const Color &color = Color::NUMBER) const;
private:
    const int width;
    const int height;
};


struct Char
{
    Char(char s) : symbol((uint8)s) { }
    int Write(int x, int y, const Color &color = Color::NUMBER) const;
private:
    uint8 symbol;
};


template<int capacity = 64>
struct Text
{
    Text(pchar format, ...)
    {
        std::va_list args;
        va_start(args, format);
        std::vsprintf(text, format, args);
        va_end(args);
    }
    void Write(int x, int y, const Color &color = Color::NUMBER) const
    {
        color.SetAsCurrent();

        pchar pointer = text;

        while (*pointer)
        {
            x = Char(*pointer++).Write(x, y);
            x++;
        }
    }
private:
    char text[capacity];
};

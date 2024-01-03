#include "ImageEditor.h"
#include <cmath>
#include<cstdlib>
#include <ctime>

ImageEditor::ImageEditor(string inFileName)
{
	pic = Picture(inFileName);
}

void ImageEditor::save(string outFileName)
{
    pic.save(outFileName);
}

int ImageEditor::min3(int x1, int x2, int x3)
{
    if(x1 <= x2 && x1 <= x3)
    {
        return x1;
    }
    else if(x2 <= x1 && x2 <= x3)
    {
        return x2;
    }
    else
    {
        return x3;
    }
}

int ImageEditor::max3(int x1, int x2, int x3)
{
    if(x1 >= x2 && x1 >= x3)
    {
        return x1;
    }
    else if(x2 >= x1 && x2 >= x3)
    {
        return x2;
    }
    else
    {
        return x3;
    }
}
int ImageEditor::getHue(int x, int y)
{
    int r = pic.red(x, y);
    int g = pic.green(x, y);
    int b = pic.blue(x,y);
    int min = min3(r, g, b);
    int max = max3(r, g, b);

    double hue = 0.0;

    if(min == max)
    {
        return 0;
    }
    if(r == max)
    {
        hue = ((double)g - b)/(max - min);
    }
    else if(g == max)
    {
        hue = 2.0 + ((double)b - r)/(max - min);
    }
    else
    {
        hue = 4.0 + ((double)r - g)/(max - min);
    }

    hue *= 60;
    if(hue < 0)
    {
        hue += 360;
    }
    return round(hue);
}

void ImageEditor::swapPixels(int x1, int y1, int x2, int y2)
{
    int rTemp = pic.red(x1, y1);
    int gTemp = pic.green(x1, y1);
    int bTemp = pic.blue(x1, y1);

    pic.set(x1, y1, pic.red(x2, y2), pic.green(x2,y2), pic.blue(x2,y2));
    pic.set(x2, y2, rTemp, gTemp, bTemp);
}

void ImageEditor::sort()
{
    int width = pic.width();
    int height = pic.height();

    for (int rowSelect = 0; rowSelect < height; rowSelect++)
    {
        for (int colSelect = 0; colSelect < width; colSelect++)
        {
            int maxHue = getHue(colSelect, rowSelect);
            int colMax = colSelect;
            int rowMax = rowSelect;

            for (int row = rowSelect; row < height; row++)
            {
                int col = 0;
                if (row == rowSelect)
                {
                    col = colSelect;
                }

                for (; col < width; col++)
                {
                    int hue = getHue(col, row);
                    if (hue > maxHue)
                    {
                        maxHue = hue;
                        rowMax = row;
                        colMax = col;
                    }
                }
            }

            swapPixels(colSelect, rowSelect, colMax, rowMax);
        }
    }
}




void ImageEditor::unitTests()
{
    srand((unsigned int)time(0));

    cout << "Testing min3..." << endl;
    if (min3(1, 2, 3) == 1 && min3(4, 2, 3) == 2 && min3(1, 2, 0) == 0 && min3(2, 2, 2) == 2 && min3(1, 2, 1) == 1)
    {
        cout << "min3 passed" << endl;
    }
    else
    {
        cout << "min3 failed" << endl;
    }

    cout << "Testing max3..." << endl;
    if (max3(1, 2, 3) == 3 && max3(4, 2, 3) == 4 && max3(1, 2, 0) == 2 && max3(2, 2, 2) == 2 && max3(1, 2, 1) == 2)
    {
        cout << "max3 passed" << endl;
    }
    else
    {
        cout << "max3 failed" << endl;
    }

    cout << "Testing getHue..." << endl;
    bool huePassed = true;
    int col = rand() % pic.width();
    int row = rand() % pic.height();
    int rTemp = pic.red(col, row);
    int gTemp = pic.green(col, row);
    int bTemp = pic.blue(col, row);
    pic.set(col, row, 22, 33, 44);
    if (getHue(col, row) != 210)
    {
        cout << "Expected: 210 from {22,33,44}." << endl << "received: " << getHue(col, row) << endl;
        huePassed = false;
    }
    pic.set(col, row, 55, 10, 0);
    if (getHue(col, row) != 11)
    {
        cout << "Expected: 11 from {55,10,0}." << endl << "received: " << getHue(col, row) << endl;
        huePassed = false;
    }
    pic.set(col, row, rTemp, gTemp, bTemp);
    if (huePassed)
    {
        cout << "getHue passed" << endl;
    }
    else
    {
        cout << "getHue failed" << endl;
    }

    cout << "Testing swapPixels" << endl;
    int col1 = rand() % pic.width();
    int row1 = rand() % pic.height();
    int col2 = rand() % pic.width();
    int row2 = rand() % pic.height();
    int r1 = pic.red(col1, row1);
    int g1 = pic.green(col1, row1);
    int b1 = pic.blue(col1, row1);
    int r2 = pic.red(col2, row2);
    int g2 = pic.green(col2, row2);
    int b2 = pic.blue(col2, row2);
    swapPixels(col1, row1, col2, row2);
    if (pic.red(col1, row1) == r2 && pic.green(col1, row1) == g2 && pic.blue(col1, row1) == b2 &&
        pic.red(col2, row2) == r1 && pic.green(col2, row2) == g1 && pic.blue(col2, row2) == b1)
    {
        cout << "swapPixels passed" << endl;
    }
    else
    {
        cout << "swapPixels failed" << endl;
    }
}

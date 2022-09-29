#include <iostream>
#include "fstream"
#include "D:\kino\proect\imagelib\Image.h"
using namespace std;

int main()
{
    Image img(3, 3);
    img.random();
    Image img2(img);
    try
    {
        img.Get_Pixel(1, 1) = 7;
    }
    catch (...)
    {
        cout << "error" << endl;
    }

    img.show();
    Image bimg = img.upscale();
    bimg.show();
    
    ImageSave aboba(bimg, "image.txt");
    ImageLoad aboba2("image.txt");
    Image newimg = aboba2.GetImage();
    newimg.show();
    return 0;
}
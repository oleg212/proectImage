#pragma once
#include <iostream>
#include "fstream"
#include <sstream>
#define MAXLEN =int(1000)
using namespace std;

class Image
{
public:
    int h;
    int w;
    unsigned short** arr;
public:

    Image(int _h = 0, int _w = 0)
    {
        h = _h;
        w = _w;
        arr = new unsigned short* [h];
        
        for (int i = 0; i < h; i++)
        {
            arr[i] = new unsigned short[w];
            for (int j = 0; j < w; j++) {
                arr[i][j] = 0;
            }
        }
    }
    Image(const Image& a)
    {
        h = a.h;
        w = a.w;
        arr = new unsigned short* [h];
        for (int i = 0; i < h; i++)
        {
            arr[i] = new unsigned short[w];
        }
        for (int i = 0; i < h; i++)
        {
            for (int k = 0; k < w; k++)
            {
                arr[i][k] = a.arr[i][k];
            }
        }
    }
    int GetH() {
        return h;
    }
    int GetW() {
        return w;
    }
    unsigned short** GetArr() {
        return arr;
    }
    Image upscale()
    {
        Image bigimg(h*2,w*2);

        for (int i = 0; i < h * 2 - 1; i += 2) {
            for (int j = 1; j < w * 2 - 1; j+=2) {
                bigimg.Get_Pixel(i, j - 1) = arr[i / 2][j / 2];
                bigimg.Get_Pixel(i, j) = (arr[i / 2][j / 2] + arr[i / 2][j / 2 + 1])/2;
            }
            bigimg.Get_Pixel(i, w*2-2) = arr[i / 2][w / 2+1];

        }

        for (int i = 1; i < h * 2 - 1; i += 2) {
            for (int j = 0; j < w * 2 - 1; j += 1) {
                
                bigimg.Get_Pixel(i, j) = (bigimg.Get_Pixel(i-1,j)+bigimg.Get_Pixel(i+1,j))/2;
            }
            

        }
        for (int i = 0; i < h * 2 - 1; i += 1) {
            bigimg.Get_Pixel(i, w * 2 - 1) = bigimg.Get_Pixel(i, w * 2 - 2);
        }
        for (int j = 0; j < w * 2 ; j += 1) {
            bigimg.Get_Pixel(h*2-1, j) = bigimg.Get_Pixel(h * 2 -2, j);
        }

        return bigimg;
    }
    void show()
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++) {
                printf("%d; ", arr[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    char* data()
    {
        char* out = new char[h*w];
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++) {
                out[i*h+j]=arr[i][j];
            }
           
        }
        cout << out << endl;
        return out;
    }
    void random()
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++) {
                arr[i][j] = rand()%10;
            }
        }

    }
    Image& operator =(const Image& image)
    {
        if (this == &image)
        {
            return *this;
        }
        for (int i = 0; i < h; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
        h = image.h;
        w = image.w;
        arr = new unsigned short* [h];
        for (int i = 0; i < h; i++)
        {
            arr[i] = new unsigned short[w];
            for (int k = 0; k < w; k++)
            {
                arr[i][k] = image.arr[i][k];
            }
        }
        return *this;
    }
    unsigned short& Get_Pixel(int _h, int _w)
    {
        if (_w < 0 || _h < 0 || _w >= w || _h >= h)
        {
            throw 1;
        }
        return arr[_h][_w];
    }

    ~Image()
    {
        delete[] arr[0];
        delete[] arr;
    }
};


class ImageSave {
private:
    Image image;
    string name;
public:
    ImageSave(Image _image, string _name) {
        image = Image(_image);
        name = _name;
        
        ofstream out(name);
        if (out.is_open()) {
            int h = image.GetH();
            int w = image.GetW();
            unsigned short** arr = image.GetArr();

            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < w; j++) {
                    out << arr[i][j] << "; ";

                }
                out << "\n";
            }
            out.close();
        }
        else { throw"can't save file :("; };
    }
};

class ImageLoad : public Image {

    string name;
public:
    ImageLoad(string _name) {
        ifstream in(_name);
        if (in.is_open()) {
            int ht = 0;
            int wt = 0;
            int tsz = 0;
            string a = "";
            char ch;

            string massiv[sizeof(in)];


            while (in.get(ch)) {
                if (ch == '\n') { ht++; }
                if (ch == ';') { tsz++;}
                if ((ch != ';') && (ch != '\n')) { massiv[tsz] += ch; }
                a += ch;
            }
            this->h = ht;
            this->w = tsz / h;
            arr = new unsigned short* [h];

            

            for (int i = 0; i < h; i++)
            {
                arr[i] = new unsigned short[w];
                for (int j = 0; j < w; j++) {
                    arr[i][j] = std::stoi(massiv[i*w+j]);
                }
            }
            
        }
        else { throw("cant open file :("); }
        in.close();
        
    }
    Image GetImage() {
        Image newimg(h, w);
        for (int i = 0; i < h; i++)
        {
            
            for (int j = 0; j < w; j++) {
                newimg.arr[i][j] = arr[i][j];
            }
        }
        return newimg;
        
    }

};
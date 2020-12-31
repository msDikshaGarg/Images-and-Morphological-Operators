#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

typedef struct Pixel
{
    unsigned char rgb[3];
};
struct PPM {
    Pixel* mPixels = nullptr;
    char mType[3];
    unsigned int mRows;
    unsigned int mColumns;
    unsigned int size;
    unsigned int mMaxValue;
};

PPM load(const string fileName);
PPM load1(const string fileName);

class Image
{
public:

    PPM ppmFile;
    Image operator+ (const Image& ppmFile);
    Image operator+= (const Image& ppmFile);
    Image operator- (const Image& ppmFile);
    Image operator-= (const Image& ppmFile);
    Image operator* (const float m);
    Pixel& operator[] (int i);
    Image gamma(const float gamma);
    Image applyGamma(const float val, const float maxValue);
    Image alpha(const float alpha, const Image& img);
    Image applyAlpha(const float alpha, const Image& img);
    void save(const string fileName);
    //PPM * generate (const string & fileName)    

};


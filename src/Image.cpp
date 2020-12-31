#include "Image.h"

PPM load(const string fileName)
{
    ifstream imageFile(fileName);
    PPM ppmImage;

    imageFile >> ppmImage.mType;
    imageFile >> ppmImage.mColumns;
    imageFile >> ppmImage.mRows;
    ppmImage.size = ppmImage.mColumns * ppmImage.mRows;
    imageFile >> ppmImage.mMaxValue;

    ppmImage.mPixels = new Pixel[ppmImage.size];

    int i = 0;
    //if (ppmImage.mType == "P3")
    //{
    while (i < (ppmImage.size - 1))
    {
        unsigned int r, g, b;
        imageFile >> r;
        imageFile >> g;
        imageFile >> b;
        ppmImage.mPixels[i].rgb[0] = static_cast<unsigned char>(r);
        ppmImage.mPixels[i].rgb[1] = static_cast<unsigned char>(g);
        ppmImage.mPixels[i].rgb[2] = static_cast<unsigned char>(b);
        ++i;
    }
    cout << "Loaded file." << endl;
    //}
    //else 
    //{
    //    cout<< "nope"<<endl;
    //}
    /*}
    else if (ppmImage.mType == "P2")
    {
    while (i < (ppmImage.size - 1))
    {
        unsigned int r;
        imageFile >> r;
        ppmImage.mPixels[i].rgb[0] = static_cast<unsigned char>(r);
        ++i;
    }
    cout << "Loaded P2 file." << endl;
    }
    else if (ppmImage.mType == "P6")
    {
    while (i < (ppmImage.size - 1))
    {
        unsigned char r, g, b;
        imageFile >> r;
        imageFile >> g;
        imageFile >> b;
        ppmImage.mPixels[i].rgb[0] = static_cast<unsigned char>(r);
        ppmImage.mPixels[i].rgb[1] = static_cast<unsigned char>(g);
        ppmImage.mPixels[i].rgb[2] = static_cast<unsigned char>(b);
        ++i;
    }
    cout << "Loaded P6 file." << endl;
    }
    else 
    {
    while (i < (ppmImage.size - 1))
    {
        unsigned char r;
        imageFile >> r;
        ppmImage.mPixels[i].rgb[0] = static_cast<unsigned char>(r);
        ++i;
    }
    cout << "Loaded P5 file." << endl;
    }*/
    imageFile.close();
    return ppmImage;
}

PPM load1(const string fileName)
{
    ifstream imageFile(fileName);
    ofstream myfile("../images/temp.ppm");
    PPM ppmImage;
    string line;
   
    if (myfile.is_open())
    {
        while (getline(imageFile, line))
        {
            if (line.rfind("#", 0) == 0) {
           
            }
            else {
                myfile << line << endl;
            }
        }
        myfile.close();
    }
    imageFile.close();
    return ppmImage;
}



Image Image::operator+(const Image& img)
{
    Image resImage = Image();
    int mTypeLength = sizeof(img.ppmFile.mType) / sizeof(img.ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = img.ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[min(this->ppmFile.size, img.ppmFile.size)];

    resImage.ppmFile.mColumns = img.ppmFile.mColumns;
    resImage.ppmFile.mRows = img.ppmFile.mRows;
    resImage.ppmFile.mMaxValue = img.ppmFile.mMaxValue;
    resImage.ppmFile.size = min(this->ppmFile.size, img.ppmFile.size);

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(static_cast<int>(this->ppmFile.mPixels[i].rgb[0]) + static_cast<int>(img.ppmFile.mPixels[i].rgb[0]));
        resImage.ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>(static_cast<int>(this->ppmFile.mPixels[i].rgb[1]) + static_cast<int>(img.ppmFile.mPixels[i].rgb[1]));
        resImage.ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>(static_cast<int>(this->ppmFile.mPixels[i].rgb[2]) + static_cast<int>(img.ppmFile.mPixels[i].rgb[2]));
    }

    return resImage;
}

Image Image::operator+=(const Image& img)
{
    for (auto i = 0; i < this->ppmFile.size; i++) {
        this->ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>((static_cast<int>(this->ppmFile.mPixels[i].rgb[0]) + static_cast<int>(img.ppmFile.mPixels[i].rgb[0])) / 2);
        this->ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>((static_cast<int>(this->ppmFile.mPixels[i].rgb[1]) + static_cast<int>(img.ppmFile.mPixels[i].rgb[1])) / 2);
        this->ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>((static_cast<int>(this->ppmFile.mPixels[i].rgb[2]) + static_cast<int>(img.ppmFile.mPixels[i].rgb[2])) / 2);
    }

    return *this;
}

Image Image::operator-(const Image& img)
{
    Image resImage = Image();
    int mTypeLength = sizeof(img.ppmFile.mType) / sizeof(img.ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = img.ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[min(this->ppmFile.size, img.ppmFile.size)];

    resImage.ppmFile.mColumns = img.ppmFile.mColumns;
    resImage.ppmFile.mRows = img.ppmFile.mRows;
    resImage.ppmFile.mMaxValue = img.ppmFile.mMaxValue;
    resImage.ppmFile.size = min(this->ppmFile.size, img.ppmFile.size);

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(min(255, max(static_cast<int>(this->ppmFile.mPixels[i].rgb[0]) - static_cast<int>(img.ppmFile.mPixels[i].rgb[0]), 0)));
        resImage.ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>(min(255, max(static_cast<int>(this->ppmFile.mPixels[i].rgb[1]) - static_cast<int>(img.ppmFile.mPixels[i].rgb[1]), 0)));
        resImage.ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>(min(255, max(static_cast<int>(this->ppmFile.mPixels[i].rgb[2]) - static_cast<int>(img.ppmFile.mPixels[i].rgb[2]), 0)));
    }

    return resImage;
}

Image Image::operator-=(const Image& img)
{
    for (auto i = 0; i < this->ppmFile.size; i++) {
        this->ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(min(255, max(static_cast<int>(this->ppmFile.mPixels[i].rgb[0]) - static_cast<int>(img.ppmFile.mPixels[i].rgb[0]), 0)));
        this->ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>(min(255, max(static_cast<int>(this->ppmFile.mPixels[i].rgb[1]) - static_cast<int>(img.ppmFile.mPixels[i].rgb[1]), 0)));
        this->ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>(min(255, max(static_cast<int>(this->ppmFile.mPixels[i].rgb[2]) - static_cast<int>(img.ppmFile.mPixels[i].rgb[2]), 0)));
    }

    return *this;
}

Image Image::operator*(const float m)
{
    Image resImage = Image();
    int mTypeLength = sizeof(this->ppmFile.mType) / sizeof(this->ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = this->ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[this->ppmFile.size];

    resImage.ppmFile.mColumns = this->ppmFile.mColumns;
    resImage.ppmFile.mRows = this->ppmFile.mRows;
    resImage.ppmFile.mMaxValue = this->ppmFile.mMaxValue;
    resImage.ppmFile.size = this->ppmFile.size;

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(min(255.0, max((static_cast<double>(this->ppmFile.mPixels[i].rgb[0]) * m), 0.0)));
        resImage.ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>(min(255.0, max((static_cast<double>(this->ppmFile.mPixels[i].rgb[1]) * m), 0.0)));
        resImage.ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>(min(255.0, max((static_cast<double>(this->ppmFile.mPixels[i].rgb[2]) * m), 0.0)));
    }

    return resImage;
}

Pixel& Image::operator[](int i)
{
    return this->ppmFile.mPixels[i];
}

Image Image::gamma(const float gamma)
{
    Image resImage = Image();
    Image tmpImage = Image();
    int mTypeLength = sizeof(this->ppmFile.mType) / sizeof(this->ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = this->ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[this->ppmFile.size];

    resImage.ppmFile.mColumns = this->ppmFile.mColumns;
    resImage.ppmFile.mRows = this->ppmFile.mRows;
    resImage.ppmFile.mMaxValue = this->ppmFile.mMaxValue;
    resImage.ppmFile.size = this->ppmFile.size;

    tmpImage = this->applyGamma(gamma, this->ppmFile.mMaxValue);

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i] = tmpImage.ppmFile.mPixels[i];
    }

    return resImage;
}

Image Image::applyGamma(const float val, const float maxValue)
{
    Image resImage = Image();
    int mTypeLength = sizeof(this->ppmFile.mType) / sizeof(this->ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = this->ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[this->ppmFile.size];

    resImage.ppmFile.mColumns = this->ppmFile.mColumns;
    resImage.ppmFile.mRows = this->ppmFile.mRows;
    resImage.ppmFile.mMaxValue = this->ppmFile.mMaxValue;
    resImage.ppmFile.size = this->ppmFile.size;

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(min(255.0, max(static_cast<double>(maxValue * pow((this->ppmFile.mPixels[i].rgb[0] / maxValue), val)), 0.0)));
        resImage.ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>(min(255.0, max(static_cast<double>(maxValue * pow((this->ppmFile.mPixels[i].rgb[1] / maxValue), val)), 0.0)));
        resImage.ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>(min(255.0, max(static_cast<double>(maxValue * pow((this->ppmFile.mPixels[i].rgb[2] / maxValue), val)), 0.0)));
    }
    return resImage;
}

Image Image::alpha(const float alpha, const Image& img)
{
    Image resImage = Image();
    Image tmpImage = Image();
    int mTypeLength = sizeof(this->ppmFile.mType) / sizeof(this->ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = this->ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[this->ppmFile.size];

    resImage.ppmFile.mColumns = this->ppmFile.mColumns;
    resImage.ppmFile.mRows = this->ppmFile.mRows;
    resImage.ppmFile.mMaxValue = this->ppmFile.mMaxValue;
    resImage.ppmFile.size = this->ppmFile.size;

    tmpImage = this->applyAlpha(alpha, img);

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i] = tmpImage.ppmFile.mPixels[i];
    }

    return resImage;
}

Image Image::applyAlpha(const float alpha, const Image& img)
{
    Image resImage = Image();
    int mTypeLength = sizeof(this->ppmFile.mType) / sizeof(this->ppmFile.mType[0]);
    for (auto i = 0; i < mTypeLength; i++) {
        resImage.ppmFile.mType[i] = this->ppmFile.mType[i];
    }

    resImage.ppmFile.mPixels = new Pixel[this->ppmFile.size];

    resImage.ppmFile.mColumns = this->ppmFile.mColumns;
    resImage.ppmFile.mRows = this->ppmFile.mRows;
    resImage.ppmFile.mMaxValue = this->ppmFile.mMaxValue;
    resImage.ppmFile.size = this->ppmFile.size;

    for (auto i = 0; i < resImage.ppmFile.size; i++) {
        resImage.ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>((this->ppmFile.mPixels[i].rgb[0] * alpha) + ((1 - alpha) * img.ppmFile.mPixels[i].rgb[0]));
        resImage.ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>((this->ppmFile.mPixels[i].rgb[1] * alpha) + ((1 - alpha) * img.ppmFile.mPixels[i].rgb[1]));
        resImage.ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>((this->ppmFile.mPixels[i].rgb[2] * alpha) + ((1 - alpha) * img.ppmFile.mPixels[i].rgb[2]));
    }

    return resImage;
}

void Image::save(const string fileName)
{
    ofstream saveFile(fileName, ofstream::trunc);
    if (!saveFile)
    {
        cout << "Error saving: " << fileName << endl;
        return;
    }
    else
    {
        saveFile << this->ppmFile.mType << endl;
        saveFile << this->ppmFile.mColumns << " " << this->ppmFile.mRows << endl;
        saveFile << this->ppmFile.mMaxValue << endl;
        for (auto i = 0; i < this->ppmFile.size; ++i) {
            saveFile << static_cast<unsigned int>(this->ppmFile.mPixels[i].rgb[0]) << endl
                << static_cast<unsigned int>(this->ppmFile.mPixels[i].rgb[1]) << endl
                << static_cast<unsigned int>(this->ppmFile.mPixels[i].rgb[2]) << endl;
        }
        cout << "Saved file." << endl;
        saveFile.close();
    }
}


#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<exception>
#include "Image.h"

int main(int argc, char* argv[])
{
    try {
        Image img1, img2;
        Image imgAdd, imgSub, imgMul, imgGamma, imgAlpha;
        img1.ppmFile = load1(string("../images/Mandrill.ppm"));
        img1.ppmFile = load(string("../images/temp.ppm"));
        img2.ppmFile = load1(string("../images/tandon_stacked_color.ppm"));
        img2.ppmFile = load(string("../images/temp.ppm"));
        imgAdd = img1 + img2;
        imgSub = img1 - img2;
        imgMul = img1 * 2.0;
        imgGamma = img1.gamma(0.5);
        imgAlpha = img1.alpha(0.3, img2);
        img1 += img2;
        img1 -= img2;
        imgAdd.save(string("added.ppm"));
        imgSub.save(string("subtracted.ppm"));
        imgMul.save(string("mulx2.ppm"));
        img1.save(string("add_assign.ppm"));
        img1.save(string("sub_assign.ppm"));
        imgGamma.save(string("gamma.ppm"));
        imgAlpha.save(string("alpha.ppm"));
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}

#include "bitmap.cpp"
#include <iostream>
#include <fstream>



int main(int argc, char** argv)
{
    Bitmap bmap;
    if (argc <= 1)
    {
        bmap.set("ch1.bmp");
    }
    else{
        bmap.set(argv[1]);
    }
    cout << bmap.posPict << endl;

    bmap.hideFile("hello.txt");
    bmap.getFile("secret.txt");

    return 0;
}
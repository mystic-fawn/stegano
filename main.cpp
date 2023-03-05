#include "bitmap.cpp"
#include <iostream>
#include <fstream>

string argument;

int main(int argc, char** argv)
{
    Bitmap bmap;
    if (argc <= 2)
    {
        cout << "Need more argument" << endl;
    }
    argument = argv[2];
    if(argument == "hide")
    {
        cout << argv[1] << " hide in " << argv[3] << endl;
        bmap.set(argv[3]);
        bmap.hideFile(argv[1]);
    }
    if(argument == "get" )
    {
        cout << argv[3] << " extracted from " << argv[1] << endl;
        bmap.set(argv[1]);
        bmap.getFile(argv[3]);
    }
    argument = argv[1];
    if(argument == "read" || argument == "Read")
    {
        bmap.set(argv[2]);
        bmap.Read();
        cout << "good";
    }

    return 0;
}
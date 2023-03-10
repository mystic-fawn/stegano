#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <iostream>
#include <fstream>
using namespace std;

class Bitmap
{
    public:
        Bitmap();
        Bitmap(string file);
        ~Bitmap();

        void hideFile(string namefile);
        void getFile(string namefile);
        void Read();//print the hiden text
        void set(string file);

    private:
        int header = 14;
        fstream bmp;
        void readBmap(string file);
        void getPos(int deb, int fin);
        void getField(int deb, int fin);
        void getSize(int deb, int fin);
        void returnPos();
        void setCursorPos(int pos);
        void modifyChar(int value, int bit);
        void writeone(char ch, int pos);
        int getweak(long pos);
        int field[2];
        int size[4];
        int pos[4];
        int posPict;
        char* buff;
        int* decbuff;



};


#endif
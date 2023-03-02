#include "bitmap.hpp"

Bitmap::Bitmap()
{

}

Bitmap::Bitmap(string file)
{
    readBmap(file);

}

Bitmap::~Bitmap()
{
    bmp.close();
}

void Bitmap::set(string file)
{
    readBmap(file);
}

void Bitmap::readBmap(string file)
{
    bmp.open(file, ios::binary | ios::in | ios::out);
    buff = new char[header];
    decbuff = new int[header];
    bmp.read(buff, header);
    for(int i = 0; i < header; i++)
    {
        decbuff[i] = buff[i];
    }
    getPos(10, 13);
    getField(0,1);
    getSize(2, 5);
}

void Bitmap::getPos(int deb, int fin)
{
    int size = fin - deb + 1;
    for(int i = 0; i < size; i++)
    {
        pos[i] = decbuff[deb + i];
    }
    returnPos();
    setCursorPos(posPict);
}

void Bitmap::getField(int deb, int fin)
{
    for(int i = 0; i <= fin - deb; i++)
    {
        field[i] = decbuff[deb + i];
    }
}

void Bitmap::getSize(int deb, int fin)
{
    for(int i = 0; i <= fin - deb; i++)
    {
        size[i] = decbuff[deb + i];
    }
}

void Bitmap::returnPos()
{
    int* binary;
    binary = new int[32];
    for(int i = 4; i > 0; i--)
    {
        int num = pos[i-1];
        if(num < 0)
        {
            num += 256;
        }
        for(int j = 0; j < 8; j++)
        {
            int pow = 1;
            for(int k = 0; k < 7-j; k++)
            {
                pow *= 2;
            }  
            binary[(4-i)*8+j] = num / pow;
            num %= pow;
        }
    }
    posPict = 0;
    int pow = 1;
    for(int i = 31; i >= 0; i--)
    {
        posPict += binary[i] * pow;
        pow *= 2;
    }
}

void Bitmap::setCursorPos(int pos)
{
    bmp.seekg(pos, ios::beg);
}

void Bitmap::modifyChar(int pos, int bit)
{
    bmp.seekg(pos, ios::beg);
    char ch;
    int num = bmp.get();
    if(num < 0)
        {
            num += 256;
        }
    int* binary;
    binary = new int[8];
    for(int i = 0; i < 8; i++)
    {
        int pow = 1;
        for(int j = 0; j < 7-i; j++)
        {
            pow *= 2;
        }
        binary[i] = num / pow;
        num %= pow;
    }
    num = 0;
    int pow = 1;
    binary[7] = bit;
    for(int i = 7; i >= 0; i--)
    {
        num += binary[i] * pow;
        pow *= 2;
    }
    if(num > 128)
    {
        num -= 256;
    }
    ch = num;
    bmp.seekp(pos, ios::beg);
    bmp.put(ch);
    delete binary;
}

void Bitmap::writeone(char ch, int pos)
{
    int* binary;
    binary = new int[8];
    int num = ch;
    if(num < 0)
    {
        num += 256;
    }
    for(int i = 0; i < 8; i++)
    {
        int pow = 1;
        for(int j = 0; j < 7-i; j++)
        {
            pow *= 2;
        }
        binary[i] = num / pow;
        num %= pow;
    }
    for(int i = 0; i < 8; i++)
    {
        modifyChar(pos + i, binary[i]);
    }
}

void Bitmap::hideFile(string namefile)
{
    fstream file;
    file.open(namefile, ios::binary | ios::in);
    file.seekg(0, ios::end);
    int minSize = file.tellg();
    file.seekg(0, ios::beg);

    
    char ch;

    for(int i = 0; i < minSize; i++)
    {
        ch = file.get();
        writeone(ch, posPict + i*8);
    }

}

void Bitmap::getFile(string namefile)
{
    fstream secret;
    secret.open(namefile, ios::binary | ios::out | ios::trunc);
    bmp.seekg(posPict, ios::beg);
    int repBin[8];
    int repnum;
    char chrep;
    int size = 100;
    for(int k = 0; k < size; k++)
    {
    repnum = 0;
    for(int i = 0; i < 8; i++)
    {
        repBin[i] = getweak(posPict+ i + 8*k);
    }
    for(int i = 0; i < 8; i++)
    {
        int pow = 1;
        for(int j = i; j < 7; j++)
        {
            pow *= 2;
        }
        repnum += repBin[i] * pow;
    }
    chrep = repnum;
    secret.put(chrep);
    }
}

int Bitmap::getweak(int pos)
{
    int bit = 0;
    bmp.seekg(pos, ios::beg);
    char ch = bmp.get();
    int num = ch;
    if(num < 0)
    {
        num += 256;
    }
    bit = num % 2;
    return bit;
}
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[]){
    std::ifstream image;
    std::string filetype = ".565";
    std::string filename;
    std::string a1 = argv[1];
    std::string a2 = argv[2];
    std::string a3 = argv[3];
    std::string a4 = argv[4];
    std::string a5 = argv[5];
    std::string a6 = argv[6];
    std::string a7 = argv[7];
    uint32_t width = 0;
    uint32_t height = 0;
    bool textmode = false;
    if(argc >= 7){
        if(a1 == "file"){
            filename = a2;
            filename.erase(filename.find_first_of('.')); //get only filename, discard all after '.' including '.'
            filename.append(filetype);
            image.open(a2, std::ios::binary);
            printf("%s\n", image.is_open() ? "true" : "false");
            if(!image.is_open()){
                printf("Unable to open file! Make sure file exists!\n");
                return 1;
            }
        }
        if(a7 == "text"){
            textmode = true;
        }
        else{
            printf("Invalid first argument! Must be 'file'\n");
            return 1;
        }
        if(a3 == "w"){
            width = atoi(a4.c_str());
        }
        else if(a3 == "h"){
            height = atoi(a4.c_str());
        }
        else{
            printf("Invalid 3rd argument! Must be 'w' or 'h'. You put %s\n", a3);
            return 1;
        }
        if(a5 == "w" && width == 0){
            width = atoi(a6.c_str());
        }
        else if(a5 == "h" && height == 0){
            height = atoi(a6.c_str());
        }
        else{
            printf("Invalid 5th argument! Must be 'w' or 'h'. You put %s\n", a5);
            return 1;
        }
    }
    else{
        printf("Too few arguments!\n");
    }
    uint8_t r;
    uint8_t g;
    uint8_t b;
    if((width > 256 || height > 256) && !textmode){
        printf("Size too big/not in text mode\n");
        return 1;
    }
    uint64_t size = width * height;
    char *rgbarray = new char[size*3];
    printf("Reading image\n");
    image.read(rgbarray, size*3);
   image.close();
   printf("Making new image file\n");
   std::ofstream rgb565(filename.c_str(), std::ios::out | std::ios::binary);
   uint16_t rgb;
   char *rgb5658bit = new char[size*2];
   uint32_t j = 0;
   for(uint32_t i = 0; i < size*3; i += 3){
    r = rgbarray[i];
    g = rgbarray[i+1];
    b = rgbarray[i+2];
    rgb = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    rgb5658bit[j++] = rgb >> 8;
    if(!textmode){
        rgb5658bit[j++] = rgb & 0xFF;
    }
    //printf("%u\n", j);
   }
   if(!textmode){
    rgb565.put(width);
    rgb565.put(height);
    rgb565.write(rgb5658bit, size*2);
   }
   if(textmode){
    rgb565.write(rgb5658bit, size);
   }
   rgb565.close();
   delete rgb5658bit;
   delete rgbarray;
   return 0;
}


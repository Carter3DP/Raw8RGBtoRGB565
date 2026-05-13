#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[]){
    std::ifstream image;
    std::string filetype = ".565";
    std:string filename;
    std::string a1 = argv[1];
    std::string a2 = argv[2];
    std::string a3 = argv[3];
    std::string a4 = argv[4];
    std::string a5 = argv[5];
    std::string a6 = argv[6];
    uint8_t width = 0;
    uint8_t height = 0;
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
    char rgbarray[256*256*3];
    printf("Reading image\n");
    //image.read(rgbarray, size*3);
    uint32_t size = width * height;
    printf("here %u %u %u\n", width, height, size);
    if(size*3 <= 256*256*3){
        image.read(rgbarray, size*3);
    }
   image.close();
   printf("Making new image file\n");
   std::ofstream rgb565(filename.c_str(), std::ios::out | std::ios::binary);
   printf("%s\n", rgb565.is_open() ? "true" : "false");
   uint16_t rgb;
   char rgb5658bit[256*256*2];
   uint32_t j = 0;
   for(uint32_t i = 0; i < size*3; i += 3){
    r = rgbarray[i];
    //printf("r: %u\n", r);
    g = rgbarray[i+1];
    //printf("g: %u\n", g);
    b = rgbarray[i+2];
    //printf("b: %u\n", b);
    rgb = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    //printf("rgb: %u\n", rgb);
    uint8_t rgb565low = rgb << 8;
    rgb565low = rgb >> 8;
    rgb5658bit[j] = rgb >> 8;
    rgb5658bit[j+1] = rgb565low;
    j+=2;
    printf("%u\n", j);
   }
   rgb565.put(width);
   rgb565.put(height);
   printf("here %u %u %u\n", width, height, size);
   rgb565.write(rgb5658bit, size*2);
   printf("here %u %u %u\n", width, height, size);
   rgb565.close();
   return 0;
}


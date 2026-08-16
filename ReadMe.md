# Raw8RGBtoRGB565
Convert raw 8bit RGB files to a RGB565 format.  
Files generated have the following structure: first byte contains the width, second byte contains the height, and the rest of the bytes contain the rgb565 data, high byte first, low byte second.  
Intended for use with the Adafruit GFX library, specifically Adafruit_GFX::drawRGBBitmap().

## Usage
First argument must be file follow by the filename, and interchangably, w followed by image width, and h followed by image height.  
``` ./Convert.exe file image.data w 256 h 256 ``` or ``` ./Convert.exe file image.data h 256 w 256 ```  
Image must be below 256x256 and width and height specified must also be below 256, unless it is a text file, in which case input "text" as the final argument, and the size requirement is bypassed
If exporting with GIMP, Alpha Channel must be removed.

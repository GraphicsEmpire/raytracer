#ifndef __SIMPLE_BMP
#define __SIMPLE_BMP

struct bmpheader_t{
  //Header
  char headerB;
  char headerM;
  uint32_t headerbmpsize;              
  uint16_t headerapp0;
  uint16_t headerapp1;
  uint32_t headerpixelsoffset;

  //DIB header
  uint32_t dibheadersize;
  uint32_t dibwidth;
  uint32_t dibheight;
  uint16_t dibplane;
  uint16_t dibdepth;
  uint32_t dibcompression;
  uint32_t dibsize; 
  uint32_t dibhor;
  uint32_t dibver;
  uint32_t dibpal;
  uint32_t dibimportant;
  
};


struct bmp_t{
  struct bmpheader_t header;
  uint32_t width;
  uint32_t height;
  uint32_t *pixels;
};

int writebmp(char *filename,struct bmp_t *bitmap);

int readbmp(char *filename,struct bmp_t *bitmap);
//-1 file access error
//-2 invalid BMP
//-3 memory allocation error
 

#endif

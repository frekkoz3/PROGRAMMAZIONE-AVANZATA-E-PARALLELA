#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "netpbm.h"

int open_image(char * path, netpbm_ptr img)
{
  //se usassimo w+ il file verrebbe generato se non esiste 
  //e poi verrebbe 'sbiancato' se esistesse
  FILE * fd = fopen(path, "r+");
  //otteniamo il file descriptor
  img->fd = fd;
  if (fd == NULL){
    return -1;
  }
  //otteniamo la dimensione totale
  struct stat fileStat;
  stat(path, &fileStat);
  img->size = fileStat.st_size;
  //leggiamo l'intestazione
  if (fscanf(fd, "P5\n%d %d\n255\n", &img->width, &img->height) != 2){
    fclose(fd);
    return -2;
  }
  //troviamo l'offset
  img->offset = ftell(fd);
  //mappiamo in memoria il file
  img->data = mmap(NULL, img->size, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(fd), 0);
  if (img->data == MAP_FAILED) {
    fclose(fd);
    return -3;
  }
  return 0;
}

int empty_image(char * path, netpbm_ptr img, int width, int height)
{
  FILE * fd = fopen(path, "w+");
  if (fd == NULL) {
    return -4;
  }
  int written = fprintf(fd, "P5\n%d %d\n255\n", width, height);
  ftruncate(fileno(fd), written + width * height);
  fclose(fd);
  return open_image(path, img);
}

char * pixel_at(netpbm_ptr img, int x, int y)
{
  if (img == NULL){
    return NULL;
  }
  if ( (x >= img->width) || (y >= img->height) || (x < 0) || (y < 0)){
    return NULL;
  }
  
  return img->data + (img->offset + y*img->width + x);
  // equivalent to return &img->data[img->offset + y*img->width + x]
}

int close_image(netpbm_ptr img)
{
  if (img == NULL){
    return -4;
  }
  munmap(img->data, img->size);
  fclose(img->fd);
  return 0;
}
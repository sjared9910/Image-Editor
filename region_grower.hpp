// define your class here
#ifndef _REGION_GROWER_HPP_
#define _REGION_GROWER_HPP_

#include <utility>
#include <iostream>
#include <math.h>

#include "image.h"
#include "Stack.hpp"
#include "Node.hpp"
#include "lodepng.h"

class RegionGrower
{
private:
  //Pixel stack
  Stack<std::pair< uint16_t, uint16_t>> PixelStack;
  //Image file created by string input
  Image<Pixel> Input;
  //image width
  std::size_t width;
  //image height
  std::size_t height;
  //seed width
  uint16_t SeedWidth;
  //seed height
  uint16_t SeedHeight;
  //Pixel struct of colors to be changed
  Pixel replacement;
  
public:
  //Takes string input and turns into an image file
  bool SetImage(std::string input);

  //Takes input of two numbers for the seed position as X Y cords
  bool SetSeed(uint16_t x, uint16_t y);

  //sets pixel replacement
  bool SetReplacement(const Pixel& p);

  //pixel and seed replacement operation
  void Update();

  //Outputs image as string output name
  bool GetOutput(std::string output);

  //Returns image
  Image<Pixel> returnImage();

  //Returns seeds in a vector
  std::vector<uint16_t> returnSeed();

  //Returns replaced pixels
  Pixel returnPixels();
};

#endif

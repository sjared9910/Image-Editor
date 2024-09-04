#include "region_grower.hpp"

//Takes string input and turns into an image file
bool RegionGrower::SetImage(std::string input)
{
    //check to make sure last 4 characters of input string are .png
    int length = input.length();
    std::string fileTest = input.substr((length - 4), length);

    //if the file is a png
    if (fileTest == ".png")
    {
        //reads input file
        std::vector<unsigned char> raw;
        unsigned w, h;

        // decode the png
        unsigned error = lodepng::decode(raw, w, h, input.c_str());

        //If an error was found
        if (error)
        {
            return false;
        }

        //takes raw data and puts it into image
        Image<Pixel> im(w, h);
        std::size_t idx = 0;
        for (std::size_t i = 0; i < im.width(); ++i)
            for (std::size_t j = 0; j < im.height(); ++j) 
            {
                im(i, j).red = raw[idx++];
                im(i, j).green = raw[idx++];
                im(i, j).blue = raw[idx++];
                im(i, j).alpha = raw[idx++];
            }
        Input = im;
        return true;
    }
    //file input was not a png
    return false;
}

//Returns image file
Image<Pixel> RegionGrower::returnImage()
{
    return Input;
}

//Takes input of two unsigned 16 bit numbers for the seed position
bool RegionGrower::SetSeed(uint16_t x, uint16_t y)
{
    //Check to make sure x and y values are within range of the image
    if ( x >= 0 && x <= Input.width() && y >= 0 && y <= Input.height())
    {
        //sets variables to input for return in tests
        SeedWidth = x;
        SeedHeight = y;

        //Adds Pixel location into the pixel stack
        std::pair< uint16_t, uint16_t> SeedPosition;
        SeedPosition.first = x;
        SeedPosition.second = y;
        PixelStack.push(SeedPosition);

        return true;
    }
    //If the seed location wasnt valid
    return false;
}

//Returns seeds in a vector
std::vector<uint16_t> RegionGrower::returnSeed()
{
    //assignes seed values to vectors
    std::vector<uint16_t> seeds;
    seeds.push_back(SeedWidth);
    seeds.push_back(SeedHeight);

    return seeds;
}

//Sets the replacement pixel spectrum
bool RegionGrower::SetReplacement(const Pixel& p)
{
    //check to make sure alpha is within rgb spectrum
    if (p.alpha >= 0 && p.alpha <= 255)
    {
        //check to make sure blue is within rgb spectrum
        if (p.blue >= 0 && p.blue <= 255)
        {
            //check to make sure green is within rgb spectrum
            if (p.green >= 0 && p.green <= 255)
            {
                //check to make sure red is within rgb spectrum
                if (p.red >= 0 && p.red <= 255)
                {
                    //sets replacement to pixel struct input
                    replacement = p;
                    return true;
                }
            }
        }
    }
    //Any value wasnt within rgb spectrum
    return false;
}

//Returns replacement pixel struct
Pixel RegionGrower::returnPixels()
{
    return replacement;
}

//Goes through image changing each pixel in accordance to pixel replacement and seed position
void RegionGrower::Update()
{
    for (std::size_t i = 0; i < Input.width(); ++i)
    {
        for (std::size_t j = 0; j < Input.height(); ++j)
        {
            if (Input(i, j).alpha < 1)
            {
                Input(i, j).alpha = 255;
                Input(i, j).red = 255;
                Input(i, j).green = 255;
                Input(i, j).blue = 255;
            }
        }
    }

    while (!PixelStack.isEmpty())
    {
        std::pair< uint16_t, uint16_t> Top = PixelStack.peekPop();
        Pixel current = Input(Top.first, Top.second);

        //pixel below
        if (Top.second != 0 && Top.second - 1 >= 0)
        {
            Pixel below = Input(Top.first, Top.second - 1);

            if (below != replacement && below == current)
            {
                std::pair< uint16_t, uint16_t> input;
                input.first = Top.first;
                input.second = Top.second - 1;
                PixelStack.push(input);
            }
        }

        //pixel above
        if (Top.second != Input.height() && Top.second + 1 < Input.height())
        {
            Pixel above = Input(Top.first, Top.second + 1);

            if (above != replacement && above == current)
            {
                std::pair< uint16_t, uint16_t> input;
                input.first = Top.first;
                input.second = Top.second + 1;
                PixelStack.push(input);
            }
        }

        //pixel left
        if (Top.first != 0 && Top.first - 1 >= 0)
        {
            Pixel left = Input(Top.first - 1, Top.second);

            if (left != replacement && left == current)
            {
                std::pair< uint16_t, uint16_t> input;
                input.first = Top.first - 1;
                input.second = Top.second;
                PixelStack.push(input);
            }
        }

        //pixel right
        if (Top.first != Input.width() && Top.first + 1 < Input.width())
        {
            Pixel right = Input(Top.first + 1, Top.second);

            if (right != replacement && right == current)
            {
                std::pair< uint16_t, uint16_t> input;
                input.first = Top.first + 1;
                input.second = Top.second;
                PixelStack.push(input);
            }
        }

        Input(Top.first, Top.second).red = replacement.red;
        Input(Top.first, Top.second).green = replacement.green;
        Input(Top.first, Top.second).blue = replacement.blue;
    }

    for (std::size_t i = 0; i < Input.width(); ++i)
    {
        for (std::size_t j = 0; j < Input.height(); ++j)
        {
            if (Input(i, j).red == 255 && Input(i, j).green == 255 && Input(i, j).blue == 255)
            {
                Input(i, j).alpha = 0;
                Input(i, j).red = 0;
                Input(i, j).green = 0;
                Input(i, j).blue = 0;
            }
        }
    }
}

bool RegionGrower::GetOutput(std::string output)
{
    //Test to make sure last 4 characters in string are .png
    int length = output.length();
    std::string fileTest = output.substr((length - 4), length);

    //if the filename is a png
    if (fileTest == ".png")
    {
        //writes input image to file
        std::vector<unsigned char> raw(4 * Input.width() * Input.height());

        //Puts image back into raw data
        std::size_t idx = 0;
        for (std::size_t i = 0; i < Input.width(); ++i)
            for (std::size_t j = 0; j < Input.height(); ++j) {
                raw[idx++] = Input(i, j).red;
                raw[idx++] = Input(i, j).green;
                raw[idx++] = Input(i, j).blue;
                raw[idx++] = Input(i, j).alpha;
            }

        // encode the image
        unsigned error = lodepng::encode(output.c_str(), raw, Input.width(), Input.height());

        //If an error was found
        if (error)
        {
            return false;
        }
        return true;
    }
    //if output filename isnt a png
    return false;
}


#include <iostream>
#include <windows.h>
#include "image.h"
#include "region_grower.hpp"
using namespace std;

//For folder reading the images
const std::string SEP =
#if defined(_WIN32)
"\\";
#else
"/";
#endif

//Function delcarations
void compare();
void fill();
void grayscale();

int main() 
{
	while (true)
	{
		//Main output
		cout << "Please place your images within the test folder within the project folder" << endl;
		string usage;
		cout << "Enter your usage type (Compare, Fill, Grayscale) or type exit: ";
		cin >> usage;

		//Changes the string to lower case for checking
		for (auto& k : usage){ k = tolower(k);}

		//Compare usage where two images are compared to see if they are the same
		if (usage == "compare")
		{
			compare();
			//Waits for user to hit the enter key
			cout << "Press the enter key to continue" << endl;
			int k = 0;
			while (k != 13) { k = _getwch(); }
		}
		//Fills a region of an image by giving a X Y coordinate and specifying the RGB fill color
		else if (usage == "fill")
		{
            fill();
            //Waits for user to hit the enter key
            cout << "Press the enter key to continue" << endl;
            int k = 0;
            while (k != 13) { k = _getwch(); }
		}
		//Takes an inputted image and outputs it as grayscale
		else if (usage == "grayscale")
		{
			grayscale();
			//Waits for user to hit the enter key
			cout << "Press the enter key to continue" << endl;
			int k = 0;
			while (k != 13) { k = _getwch(); }
		}
		else if (usage == "exit")
		{
			return 0;
		}
		else
		{
			cout << "Invalid usage type, please try again";
		}
		system("CLS");
	}
}

//Compare usage where two images are compared to see if they are the same
void compare()
{
    try {
        //Console output
        string test1, test2;
        cout << "Input the file names to be compared as (filename1.png) (filename2.png): ";
        cin >> test1 >> test2;

        Image<Pixel> input1 = readFromFile(("Test" + SEP + test1));
        Image<Pixel> input2 = readFromFile(("Test" + SEP + test1));

        // check size are the same
        if ((input1.width() != input2.width()) ||
            (input1.height() != input2.height())) {
            cout << "Images differ\n";
            return;
        }
        // compare each pixel, stop on first difference
        bool ok = true;
        for (intmax_t i = 0; i < input1.width(); ++i)
            for (intmax_t j = 0; j < input1.height(); ++j) {
                if (input1(i, j) != input2(i, j)) {
                    ok = false;
                    break;
                }
            }
        //Difference found
        if (!ok) {
            cout << "Images differ.\n";
            return;
        }
    }
    //catches and outputs any errors
    catch (exception& ex) {
        cerr << ex.what() << endl;
        return;
    }
    cout << "Images identical.\n";
    return;
}

//Fills a region of an image by giving a X Y coordinate and specifying the RGB fill color
void fill()
{
	//sets strings of inputs
	string input, output;
	cout << "Input the file name to be filled and output file name as (inputname.png) (outputname.png): ";
	cin >> input >> output;

	//Prompt for coordinates to fill
	unsigned int SeedX, SeedY;
	cout << "Input the X Y coordinate to file as (X cord) (Y cord): ";
	cin >> SeedX >> SeedY;

	//Prompt for RGB values
	unsigned int Red, Green, Blue;
	cout << "Enter the RGB values as (Red) (Green) (Blue): ";
	cin >> Red >> Green >> Blue;

	RegionGrower m;

	//Sets the image from the input
	bool inputtest = m.SetImage(("Test" + SEP + input));

	//If the set image returned false
	if (!inputtest)
	{
		//returns error message
		cout << "Error the input image file cannot be opened" << endl;
		return;
	}

	//Sets seeds from input
	bool seedtest = m.SetSeed(SeedX, SeedY);

	//If the seeds were invalid
	if (!seedtest)
	{
		//returns error message
		cout << "Error the seed is at an invalid position" << endl;
		return;
	}

	//Sets pixels
	//check to make sure red is within rgb spectrum
	bool pixelSet = false;
	if (Red >= 0 && Red <= 255)
	{
		//check to make sure blue is within rgb spectrum
		if (Blue >= 0 && Blue <= 255)
		{
			//check to make sure green is within rgb spectrum
			if (Green >= 0 && Green <= 255)
			{
				pixelSet = m.SetReplacement({ (unsigned char)Red, (unsigned char)Green, (unsigned char)Blue, 255 });
			}
		}
	}

	//If pixels were invalid
	if (!pixelSet)
	{
		cout << "Error replacement color is invalid" << endl;
		return;
	}

	//color fill
	m.Update();

	//Outputs png file
	bool outputtest = m.GetOutput(("Test" + SEP + output));

	//If output file couldnt be made
	if (!outputtest)
	{
		//return error message
		cout << "Error the output file is not specified or cannot be opened for writing" << endl;
		return;
	}
	//If everything worked
	return;

	
	//If amount of inputs didnt equal 8
	cout << "Error not enough inputs" << endl;
	return;
}

//Takes an inputted image and outputs it as grayscale
void grayscale()
{
    //Console output
    string input, output;
    cout << "Input the file to be turned to gray scale and output file name as (inputname.png) (outputname.png): ";
    cin >> input >> output;

    // declare and read the bitmap
    Image<Pixel> Input;
    Input = readFromFile("Test" + SEP + (input));

    // convert each pixel to grayscale using RGB->YUV
    for (int j = 0; j < Input.height(); j++)
    {
        for (int i = 0; i < Input.width(); i++)
        {
            int Temp = (int)floor(0.299 * Input(i, j).red +
                0.587 * Input(i, j).green +
                0.114 * Input(i, j).blue);
            uint8_t TempBYTE = (uint8_t)Temp;
            Input(i, j).red = TempBYTE;
            Input(i, j).green = TempBYTE;
            Input(i, j).blue = TempBYTE;
        }
    }
    // write the output file
    writeToFile(Input, ("Test" + SEP + output));
}
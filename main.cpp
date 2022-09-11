#include <AK/String.h>
#include <AK/Format.h>
#include <AK/Vector.h>
#include <LibCore/System.h>
#include <LibCore/ArgsParser.h>
#include <LibCore/File.h>
#include <LibMain/Main.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace AK;
using namespace Core;
using namespace std;

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}
#include "vars.h"

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    char const* image_location = nullptr;
    char const* debug = nullptr;

    ArgsParser args_parser;
    args_parser.add_positional_argument(image_location, "Location of the image", "image");
    args_parser.add_positional_argument(debug, "Enable debug mode", "debug", ArgsParser::Required::No);
    args_parser.parse(arguments);

    // find out the absolute path
    String image_string_path = String(image_location);

    // set the debug global variable
    if (debug == nullptr) debug = "false";
    if (strcmp(debug, "true") == 0) {
        warnln("Enabled the debug mode! {}", debug);
        DEBUG_MODE = 1;
    }

    String image_absolute_path = File::absolute_path(image_string_path);
    outln("Your image: {}", image_absolute_path);

    // read pixel data from the image
    int width,height,pixel_structure;
    unsigned char *data = stbi_load(image_absolute_path.characters(), &width, &height, &pixel_structure, 0);

    if (data == nullptr || width <= 0 || height <= 0 || pixel_structure != 4) {
        warnln("Failed reading pixel data from the image.");
        return 1;
    }

    for (int y_index = 0; y_index < height; y_index++) {
        for (int x_index = 0; x_index < width; x_index++) {
            int pixel_index = (y_index * width * 4) + (x_index * 4);

            unsigned char red_data = data[pixel_index];
            unsigned char green_data = data[pixel_index+1];
            unsigned char blue_data = data[pixel_index+2];
            unsigned char alpha_data = data[pixel_index+3];

            if (DEBUG_MODE == 1) printf("Pixel at %d,%d\twith red value: %d\tand green value: %d\tand blue value: %d\tand alpha value: %d\n", y_index, x_index, red_data, green_data, blue_data, alpha_data);

            // TODO: Include the alpha channel as well
            unsigned char greyscale_data = (red_data * 0.30) + (green_data * 0.59) + (blue_data * 0.11);

	    // figure out which ascii to use 
	    int ascii_index = (int) ((greyscale_data * (sizeof(brightness_ascii) / sizeof(char)-1)) / 255);
	    char *ascii = brightness_ascii + ascii_index; 
	    printf("%c", *ascii);
        }
	printf("\n");
    }

    return 0;
}

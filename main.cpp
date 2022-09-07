#include <AK/String.h>
#include <AK/Format.h>
#include <LibCore/System.h>
#include <LibCore/ArgsParser.h>
#include <LibCore/File.h>
#include <LibMain/Main.h>
#include <stdio.h>
#include <unistd.h>

using namespace AK;
using namespace Core;

ErrorOr<int> serenity_main(Main::Arguments arguments)
{

    char const* image_location = nullptr;

    ArgsParser args_parser;
    args_parser.add_positional_argument(image_location, "Location of the image", "image");
    args_parser.parse(arguments);

    // find out the absolute path
    String image_string_path = String(image_location);
    String image_absolute_path = File::absolute_path(image_string_path);
    outln("Your image: {}", image_absolute_path);

    return 0;
}

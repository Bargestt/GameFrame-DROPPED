#include <iostream>

#include <application.h>

#include "config.h"

using namespace std;

int main(int argc, char *argv[])
{
    Config cfg;

    //TODO: Read config file

    Application app(cfg);
    app.run();

    return 0;
}

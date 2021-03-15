#include<iostream>

using namespace std;

bool loadMedia();

bool loadMedia()
{
    bool success = true;
    gTexture = loadTexture("city2.jpg");
    if(gTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    return success;
}



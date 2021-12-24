//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_IMAGELOADER_H
#define BROKERAPP_IMAGELOADER_H

#include <string>
#include <glad/glad.h>

class ImageLoader {
public:
    static bool loadTexture(const char* filename, GLuint* out_texture, int* out_width, int* out_height);

};


#endif //BROKERAPP_IMAGELOADER_H

#include <image.hpp>

#if defined(_WIN32)
#define GL_CLAMP_TO_EDGE 0x812F 
#include <gl/GL.h>

#define STBI_WINDOWS_UTF8
#else
#include <GL/gl.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cassert>

namespace Utils {

	void ImageTexture::CreateTexture(const char* filename)
	{
		unsigned char* image_data = stbi_load(filename, &m_width, &m_height, NULL, 4);
		if (image_data == NULL) {
			image_data = stbi_load("ass.jpg", &m_width, &m_height, NULL, 4);
		    assert(image_data && "Something really broken!");
		}

		// Create a OpenGL texture identifier
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

		// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
					 image_data);

		stbi_image_free(image_data);
	}

}

#include <vector>

#include "gltexture.h"
#include "glselect.h"
#include "gltypes.h"
#include "logger.h"
#include "base/directory.h"
#include "lodepng/lodepng.h"

using namespace ps;
using namespace sda;
//using namespace ps::utils;
using namespace ps::dir;
using namespace  std;

namespace ps {
namespace opengl {


GLTexture::GLTexture() {
    m_texunit = 0;
    m_gltex = INVALID_GLBUFFER;
}

GLTexture::GLTexture(const AnsiStr& strFP, int texunit) {
    m_texunit = texunit;
    m_gltex = INVALID_GLBUFFER;
    if(!read(strFP)) {
        vlogerror("Texture creation failed for file: %s", strFP.cptr());
    }
}

GLTexture::GLTexture(const Pixmap& pixmap, int texunit) {

	m_texunit = texunit;


}

GLTexture::~GLTexture() {
    cleanup();
}

void GLTexture::cleanup() {
    if(glIsTexture(m_gltex))
        glDeleteTextures(1, &m_gltex);
}

GLuint GLTexture::create_checkerboard(int w, int h, int step) {

	vector<GLubyte> vimg;
	vimg.resize(w * h * 4);

	int i, j, c;
	U32 index = 0;
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			c = (((i & step) == 0) ^ ((j & step) == 0));
			c = c * 255;

			vec4u8 color(c, c, c, 255);
			color.store(&vimg[index]);

			index += 4;
		}
	}

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			&vimg[0]);

	//Params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}


GLTexture* GLTexture::CheckerBoard()
{
    GLTexture* pgltex = new GLTexture();

    const int TEX_SIZE = 256;
    GLuint gltex = create_checkerboard(TEX_SIZE, TEX_SIZE);

    vec3i dim = vec3i(TEX_SIZE, TEX_SIZE, 4);
    pgltex->set(dim, gltex, 0);
    return pgltex;
}


bool GLTexture::read(const AnsiStr& strFP) {
    if(!FileExists(strFP))
        return false;
    ImageFileType ft = GetFileType(strFP);
    if(ft != iftPNG)
        return false;

    //Cleanup before reading the image file
    this->cleanup();

    //Generate Texture
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glActiveTexture(GL_TEXTURE0 + m_texunit);
    glGenTextures(1, &m_gltex);
    glBindTexture(GL_TEXTURE_2D, m_gltex);

    //Load image data
    switch (ft) {
    case iftPNG:
        read_png(strFP);
        break;
    default:
        break;
    }

    //Params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();
    return true;
}

bool GLTexture::read_png(const AnsiStr& strFP) {

    vector<U8> data;
    U32 w, h;
    U32 error = lodepng::decode(data, w, h, strFP.cptr());
    if(error) {
        vlogerror("Unable to load png image from file: %s", strFP.cptr());
        return false;
    }

    m_dim = vec3i(w, h, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_dim.x, m_dim.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    return true;
}

bool GLTexture::write(const AnsiStr& strFP) {
    return false;
}

void GLTexture::set(const vec3i& dim, U32 handle, int texunit) {
    cleanup();
    m_dim = dim;
    m_gltex = handle;
    m_texunit = texunit;
}

void GLTexture::set(const Pixmap& pixmap, int texunit) {
    cleanup();

    m_dim = vec3i(pixmap.width(), pixmap.height(), pixmap.depth());
    m_gltex = GL_INVALID_VALUE;
    m_texunit = texunit;
            
    //Generate Texture
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glActiveTexture(GL_TEXTURE0 + m_texunit);
    
    glGenTextures(1, &m_gltex);
    glBindTexture(GL_TEXTURE_2D, m_gltex);

    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap.width(), pixmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 pixmap.const_data());

    //Params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopAttrib();
}

void GLTexture::bind() {
    if(m_gltex != INVALID_GLBUFFER) {
        glActiveTexture(GL_TEXTURE0 + m_texunit);
        glBindTexture(GL_TEXTURE_2D, m_gltex);
    }
}

void GLTexture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture::ImageFileType GLTexture::GetFileType(const AnsiStr &strFP) {
    AnsiStr strExt = ps::dir::ExtractFileExt(strFP);
    strExt.toUpper();

    if(strExt == "BMP")
        return iftBMP;
    else if(strExt == "PNG")
        return iftPNG;
    else if(strExt == "JPG")
        return iftJPG;
    else
        return iftUnsupported;
}

}
}


#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "base/vec.h"
#include "base/str.h"
#include "base/pixmap.h"
#include "glbindable.h"

using namespace ps;
using namespace ps::base;

namespace ps {
    namespace opengl {
     
        class GLTexture : public GLBindable {
        public:
            GLTexture();
            GLTexture(const Pixmap& pixmap);
            GLTexture(const AnsiStr& strFP, int texunit = 0);
            virtual ~GLTexture();
            
            //Enums
            enum ImageFileType {iftPNG, iftBMP, iftJPG, iftUnsupported};
            
            //IO
            void cleanup();
            bool read(const AnsiStr& strFP);
            bool write(const AnsiStr& strFP);

            //setter
            void set(const vec3i& dim, U32 handle, int texunit = 0);
            void set(const Pixmap& pixmap, int texunit = 0);
            
            //Binding
            void bind();
            void unbind();
            
            //Dimension
            vec3i dim() const {return m_dim;}

            //Set
            U32 handle() const {return m_gltex;}

            
            //Statics
            static ImageFileType GetFileType(const AnsiStr& strFP);
            static GLTexture* CheckerBoard();

            static U32 create_checkerboard(int w, int h, int step = 8);
        private:
            bool read_png(const AnsiStr& strFP);
            
        protected:
            int m_texunit;
            U32 m_gltex;
            vec3i m_dim;
        };
    }
}


#endif

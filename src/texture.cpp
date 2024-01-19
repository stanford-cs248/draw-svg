#include "texture.h"
#include "color.h"

#include <assert.h>
#include <iostream>
#include <algorithm>

using namespace std;

namespace CS248 {

inline void uint8_to_float( float dst[4], unsigned char* src ) {
  uint8_t* src_uint8 = (uint8_t *)src;
  dst[0] = src_uint8[0] / 255.f;
  dst[1] = src_uint8[1] / 255.f;
  dst[2] = src_uint8[2] / 255.f;
  dst[3] = src_uint8[3] / 255.f;
}

inline void float_to_uint8( unsigned char* dst, float src[4] ) {
  uint8_t* dst_uint8 = (uint8_t *)dst;
  dst_uint8[0] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[0])));
  dst_uint8[1] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[1])));
  dst_uint8[2] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[2])));
  dst_uint8[3] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[3])));
}

void Sampler2DImp::generate_mips(Texture& tex, int startLevel) {

  // NOTE: 
  // This starter code allocates the mip levels and generates a level 
  // map by filling each level with placeholder data in the form of a 
  // color that differs from its neighbours'. You should instead fill
  // with the correct data!

  // Advanced Task
  // Implement mipmap for trilinear filtering

  // check start level
  if ( startLevel >= tex.mipmap.size() ) {
    std::cerr << "Invalid start level"; 
  }

  // allocate sublevels
  int baseWidth  = tex.mipmap[startLevel].width;
  int baseHeight = tex.mipmap[startLevel].height;
  int numSubLevels = (int)(log2f( (float)max(baseWidth, baseHeight)));

  numSubLevels = min(numSubLevels, kMaxMipLevels - startLevel - 1);
  tex.mipmap.resize(startLevel + numSubLevels + 1);

  int width  = baseWidth;
  int height = baseHeight;
  for (int i = 1; i <= numSubLevels; i++) {

    MipLevel& level = tex.mipmap[startLevel + i];

    // handle odd size texture by rounding down
    width  = max( 1, width  / 2); assert(width  > 0);
    height = max( 1, height / 2); assert(height > 0);

    level.width = width;
    level.height = height;
    level.texels = vector<unsigned char>(4 * width * height);

  }

  // fill all 0 sub levels with interchanging colors
  Color colors[3] = { Color(1,0,0,1), Color(0,1,0,1), Color(0,0,1,1) };
  for(size_t i = 1; i < tex.mipmap.size(); ++i) {

    Color c = colors[i % 3];
    MipLevel& mip = tex.mipmap[i];

    for(size_t i = 0; i < 4 * mip.width * mip.height; i += 4) {
      float_to_uint8( &mip.texels[i], &c.r );
    }
  }

}

Color Sampler2DImp::sample_nearest(Texture& tex, 
                                   float u, float v, 
                                   int level) {

  // Task 4: Implement nearest neighbour interpolation
  // return magenta for invalid level
  if (level >= tex.mipmap.size()) {
    return Color(1,0,1,1);
  }

  int u_sample_x = (int)floor(u * tex.width);
  int v_sample_y = (int)floor(v * tex.height);
  int i = 4 * (tex.width * v_sample_y + u_sample_x);
  Color sample = Color(
    tex.mipmap[level].texels[i],
    tex.mipmap[level].texels[i + 1],
    tex.mipmap[level].texels[i + 2],
    tex.mipmap[level].texels[i + 3]
  );
  uint8_to_float( &sample.r, &tex.mipmap[level].texels[i] );
  return sample;

}

Color Sampler2DImp::sample_bilinear(Texture& tex, 
                                    float u, float v, 
                                    int level) {
  
  // Task 4: Implement bilinear filtering
  // return magenta for invalid level
  if (level >= tex.mipmap.size()) {
    return Color(1,0,1,1);
  }

  // Helper functions to convert uv coords to texel index.
  auto uv_to_tex = [](Texture& tex, int u, int v) {
    return 4 * (tex.width * v + u);
  };

  auto get_tex_sample = [](Texture& tex, int level, int i) {
    int i_ = max(0, min((int)(4 * tex.width * tex.height - 4), i));
    Color sample = Color(
      tex.mipmap[level].texels[i_],
      tex.mipmap[level].texels[i_ + 1],
      tex.mipmap[level].texels[i_ + 2],
      tex.mipmap[level].texels[i_ + 3]
    );
    uint8_to_float( &sample.r, &tex.mipmap[level].texels[i] );
    return sample;
  };

  float x = u * tex.width - 0.5;
  float y = v * tex.height - 0.5;
  int xl = floor(x);
  int xr = xl + 1;
  int yt = floor(y);
  int yb = yt + 1;
  
  int tl_i = uv_to_tex(tex, xl, yt);
  int tr_i = uv_to_tex(tex, xr, yt);
  int ll_i = uv_to_tex(tex, xl, yb);
  int lr_i = uv_to_tex(tex, xr, yb);

  Color tl_sample = get_tex_sample(tex, level, tl_i);
  Color tr_sample = get_tex_sample(tex, level, tr_i);
  Color ll_sample = get_tex_sample(tex, level, ll_i);
  Color lr_sample = get_tex_sample(tex, level, lr_i);

  Color top_blend = (1 - (x - xl)) * tl_sample + (x - xl) * tr_sample;
  Color bot_blend = (1 - (x - xl)) * ll_sample + (x - xl) * lr_sample;

  Color sample = (1 - (y - yt)) * top_blend + (y - yt) * bot_blend;  
  return sample;
}

Color Sampler2DImp::sample_trilinear(Texture& tex, 
                                     float u, float v, 
                                     float u_scale, float v_scale) {

  // Advanced Task
  // Implement trilinear filtering

  // return magenta for invalid level
  return Color(1,0,1,1);

}

} // namespace CS248

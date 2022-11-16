/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"

namespace life {
            

  Canvas::Canvas(size_t w = 0, size_t h = 0, short bs = 5){
    m_pixels.reserve(w*h*bs);
  }
    /// Destructor.
  Canvas::~Canvas(void){}
    /// Copy constructor.
  Canvas::Canvas(const Canvas& target){
    this->m_pixels = target.m_pixels; 
    this->m_height = target.m_height;
    this->m_width = target.m_width;
    this->m_block_size = target.m_block_size;    
  }
  /// Assignment operator.
  Canvas& Canvas::operator=(const Canvas& target){
    Canvas(target);
  }

  //=== Members
  /// Clear the canvas with black color.
  void Canvas::clear(const Color& c = BLACK){
    for(size_t i{0}; i <= m_pixels.size();i+=4){
      m_pixels[i] = c.channels[Color::R];
      m_pixels[i+1] = c.channels[Color::G];
      m_pixels[i+2] = c.channels[Color::B];
      m_pixels[i+3] = 255;
    }
  }
  /// Set the color of a pixel on the canvas.
  void Canvas::pixel(coord_t row, coord_t col, const Color& c){
    m_pixels[row*col*image_depth] = c.channels[Color::R];
    m_pixels[row*col*image_depth+1] = c.channels[Color::G];
    m_pixels[row*col*image_depth+2] = c.channels[Color::B];
    m_pixels[row*col*image_depth+3] = 255;
  }
  /// Get the pixel color from the canvas.
  Color Canvas::pixel(coord_t row, coord_t col) const{
    return Color( m_pixels[row*col*image_depth],
                  m_pixels[row*col*image_depth+1],
                  m_pixels[row*col*image_depth+2]
                );
  }

}  // namespace life

//================================[ canvas.cpp ]================================//

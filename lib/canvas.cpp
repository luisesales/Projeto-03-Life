/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"

namespace life {
            

  Canvas::Canvas(size_t w = 0, size_t h = 0, short bs = 5){
    m_width = w;
    m_height= h;
    m_block_size = bs;
    m_pixels.reserve(w*h*image_depth);
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
    for(size_t i{0}; i <= (m_pixels.size()-image_depth);i+=image_depth){
        m_pixels[i] = c.channels[Color::R];
        m_pixels[i+1] = c.channels[Color::G];
        m_pixels[i+2] = c.channels[Color::B];
        m_pixels[i+3] = 255;
    }
  }
  /// Set the color of a pixel on the canvas.
  void Canvas::pixel(coord_t row, coord_t col, const Color& c){
    //Check if params are greater or equal than the size of the vector
    if(row >= m_width || col >= m_height) return;
    
    //Change into real pixel sizes
    row*=m_block_size;
    col*=m_block_size;
    
    //Color The Pixel with its color
    for (size_t i{0}; i <= m_block_size; i++){
      for(size_t j{0}; j <= m_block_size; j++){
        auto b_offset = (row+i)*(col+j)*image_depth;
        m_pixels[b_offset] = c.channels[Color::R];
        m_pixels[b_offset+1] = c.channels[Color::G];
        m_pixels[b_offset+2] = c.channels[Color::B];
        m_pixels[b_offset+3] = 255;
      }
      
    }
    
    
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
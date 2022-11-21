//! This class implements a life board in the Conway's Game of Life.
/*!
 * @file life.h
 *
 * @details Class Life, to simulate the Conway's Game of Life.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 * @update 2019, April 2nd.
 * @version     v1.1
 */

#ifndef _LIFE_H_
#define _LIFE_H_

#include <cassert>
#include <cstring>  // std::memcpy().
#include <iostream>
#include <set>
#include <sstream>  // std::ostringstream
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;
using std::unordered_map;

#include "canvas.h"

struct Cell {
  size_t row;
  size_t col;
  Cell(size_t r, size_t c): row{r}, col{c} {}
};

namespace life {

/// A life configuration.
class LifeCfg {

 public:
    LifeCfg();  // lines, columns
    ~LifeCfg(){ /* empty */ };
    /* void set_alive(const std::vector<Location2>&);
    void update(void);
    std::string to_string(void) const;
    bool operator==(const LifeCfg&) const;
    LifeCfg& operator=(const LifeCfg& _rhs);
    bool extinct(void) const;
    size_type rows(void) const;
    size_type cols(void) const; */
};

}  // namespace life

class SimulationLog{

 public:
    SimulationLog();
    /// Retorna true se chave já existir.
    bool find(const std::string& key) const;
    /// Inserir uma nova configuração.
    void insert(const std::string& key, unsigned long value);
    /// Recuperar a info do Log.
    unsigned long get(const std::string& key) const;
};

#endif

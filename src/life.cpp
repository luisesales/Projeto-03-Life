/**
 * LLSeq class implementation.
 *
 */

#include "life.h"

namespace life {
/// Basic constructor that creates a life board with default dimensions.
class LifeCfg {
  std::vector<Cell> m_alive;  // Lista de células vivas.
  std::vector<Cell> m_dead;

 public:
  //Ctro.
  LifeCfg(const vector<Cell>& input_cell);
  // Retorna a chave associada a uma configuração.
  std::string get_key(void) const;
  // Retorna as células vivas
  std::vector<Cell> LifeCfg::set_alive(void) const;
};

/// Ctro.
LifeCfg::LifeCfg(const vector<Cell>& input_cell) { m_alive = input_cell; }

/// Retorna a chave associada a esta configuração
std::string LifeCfg::get_key(void) const {
  std::ostringstream oss;
  for (const Cell& c : m_alive) {
    oss << c.row << "-" << c.col << " ";
  }
  return oss.str();
}

///Retorna as células vivas
std::vector<Cell> LifeCfg::set_alive(void) const{
   return m_alive;
}
}

// TODO

}  // namespace life

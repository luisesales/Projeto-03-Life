/**
 * LLSeq class implementation.
 *
 */

#include "life.h"

namespace life {
/// Basic constructor that creates a life board with default dimensions.
class LifeCfg {
  std::vector<Cell> m_alive;  // Lista de células vivas.
  std::vector<Cell> m_dead;  // Lista de células mortas.


 public:
  //Ctro.
  LifeCfg(const vector<Cell>& input_cell);
  // Retorna a chave associada a uma configuração.
  std::string get_key(void) const;
  // Retorna as células vivas
  std::vector<Cell> LifeCfg::set_alive(void) const;
  //Verifica se todas as células morreram
  bool extinct(void) const;
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
///Retorna um booliano que representa se todas as células morreram ou não
bool LifeCfg::extinct(void) const{
  return m_alive.size() == 0;
}


}

// TODO
class SimulationLog {
 private:
  std::unordered_map<std::string, unsigned long> m_data_base;

 public:
  SimulationLog();
  /// Retorna true se chave já existir.
  bool find(const std::string& key) const;
  /// Inserir uma nova configuração.
  void insert(const std::string& key, unsigned long value);
  /// Recuperar a info do Log.
  unsigned long get(const std::string& key) const;

  
};

bool SimulationLog::find(const std::string& key) const{
  return m_data_base.count(key) != 0;
}

unsigned long SimulationLog::get(const std::string& key) const{
  return m_data_base.at(key);
}

void SimulationLog::insert(const std::string& key, unsigned long value){
  m_data_base.insert({key,value});
}  // namespace life


class SimulationManager{
  private:

}
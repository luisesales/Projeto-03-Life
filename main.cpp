#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using std::vector;

/*
 *  CFG 4 x 5
 *   . . . . .
 *   . x . . .
 *   . x x . .
 *   . . . . .
 */

struct Cell {
  int row;
  int col;
  Cell(int r, int c) : row{r}, col{c} {}
};

/// Classe representando uma configuração
class LifeCfg {
  std::vector<Cell> m_alive;  // Lista de células vivas.

 public:
  LifeCfg(const vector<Cell>& input_cell);
  // Retorna a chave associada a uma configuração.
  std::string get_key(void) const;
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

void SimulationLog::insert(const std::string& key, unsigned long value){
  m_data_base.insert({key,value});
}

int main(int argc, char* argv[]) {
  vector<Cell> input{{1, 1}, {2, 2}, {2, 3}};

  // Criando uma configuração
  LifeCfg current{input};
  // Criando o Log de gerações.
  SimulationLog log;

  std::cout << ">>> Chave = " << std::quoted(current.get_key()) << "\n";
  std::cout << "    Hash(" << std::quoted(current.get_key())
            << ") = " << std::hash<std::string>{}(current.get_key()) << "\n";

  // Mantem o controle da geração
  unsigned long current_generation{1};

  std::string key = current.get_key();
  // Processo de insercao de uma nova geração
  // (1) Verificar se geracao ja existe.
  if (log.find(key)) {
    std::cout << ">>> Entrou em estabilidade com a geracao: ";
    std::cout << log.get(key) << "\n";
  } else { // Não existe!!!
    // (2) entao precisamos inserir
    log.insert(key, current_generation);
  }

  return 0;
}

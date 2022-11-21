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
  // Verifica se todas as células morreram
  bool extinct(void) const;
  // Atualiza as Células vivas pra uma nova geração de acordo com as regras
  void update(const LifeCfg& target);
  // Modifica as configurações por outra recebida por parâmetro
  LifeCfg& operator=(const LifeCfg& _rhs);
  // Compara duas configurações e retorna se são iguais o não
  bool operator==(const LifeCfg&) const;
  //
  size_t rows(void) const;
  size_t cols(void) const;
};

/// Ctro.
LifeCfg::LifeCfg(const vector<Cell>& input_cell) {
   m_alive = input_cell; 
   }

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

///Atualiza as células para uma nova geração
void LifeCfg::update(const LifeCfg& target){
  LifeCfg(target.m_alive);
}

LifeCfg& LifeCfg::operator=(const LifeCfg& target) {
  LifeCfg(target.m_alive);
}

// TODO
class SimulationLog {
 private:
  std::unordered_map<std::string, unsigned long> m_data_base;

 public:
  SimulationLog();
  // Retorna true se chave já existir.
  bool find(const std::string& key) const;
  // Inserir uma nova configuração.
  void insert(const std::string& key, unsigned long value);
  // Recuperar a info do Log.
  unsigned long get(const std::string& key) const;
  // Encerra o programa no caso de encontrar uma estabilidade de gerações
  bool stable(const std::string& key) const;

};

/// Procura por configuração enviada por parâmetro
bool SimulationLog::find(const std::string& key) const{
  return m_data_base.count(key) != 0;
}

/// Retorna configuração em posição específica
unsigned long SimulationLog::get(const std::string& key) const{
  return m_data_base.at(key);
}

/// Insere nova configuração
void SimulationLog::insert(const std::string& key, unsigned long value){
  m_data_base.insert({key,value});
}  // namespace life

/// Verifica se a configuração entrou em estabilidade
bool SimulationLog::stable(const std::string& key) const{
  return m_data_base.count(key) > 1;
}


class SimulationManager{
  private:
  unordered_map<bool,char> p{{true , '@'},{false , '#'}};
  std::vector<std::vector<bool>> board; // Tabuleiro com as posições onde há células vivas
  size_t amount; // Quantidade de loops limite
  LifeCfg Cfg; // Configuração da Aplicação
  SimulationLog Log // Banco de dados de gerações

  public:
  // Ctro
  SimulationManager(const vector<vector<bool>>& input);

  // Ler as configs enviadas pelo arquivo de configuração
  void readConfig(void);

  // Atualizar as gerações
  void update(void);

  // Printa o resultado de uma geração 
  void print(){
    string result{""};
    for(auto x : board){
      for(size_t i{0}; i < x.size();i++){
        result+=p[x[i]];
      }
      result+="\n";
    }
    std::cout << result << std::endl;
  }
};

/// Ctro
SimulationManager::SimulationManager(const vector<vector<bool>>& input){
    this->board = input;
}

void SimulationManager::update(void){
  size_t generations{0};
  string key{""};
  while(generations < amount || !Cfg.extinct() || !Log.stable(key)){
    key = Cfg.get_key();
    generations++;

  }
}

}

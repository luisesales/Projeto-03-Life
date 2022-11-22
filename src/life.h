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
  std::vector<Cell> m_alive;  // Lista de células vivas.
  //std::vector<Cell> m_dead;  // Lista de células mortas.


 public:
  //Ctro.
  LifeCfg(const vector<Cell>& input_cell = {});
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

 

class SimulationLog {
 private:
  std::unordered_map<std::string, unsigned long> m_data_base; // Banco de dados de todas as gerações do programa

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


class SimulationManager{
  private:
  unordered_map<bool,char> p{{true , '@'},{false , '#'}}; // Transformador de tabuleiro para resultado no console
  std::vector<std::vector<bool>> board; // Tabuleiro com as posições onde há células vivas
  size_t amount; // Quantidade de loops limite
  LifeCfg Cfg; // Configuração da Aplicação
  SimulationLog Log; // Banco de dados de gerações

  public:
  // Ctro
  SimulationManager(const vector<vector<bool>>& input = {{}});

  // Ler as configs enviadas pelo arquivo de configuração
  int readConfig(void);

  // Atualizar as gerações
  void play(void);

  // Printa no console o resultado de uma geração 
  void print(void);

};


} // namespace life
#endif

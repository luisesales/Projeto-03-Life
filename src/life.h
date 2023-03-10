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
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctype.h>

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;
using std::unordered_map;

#include "../lib/canvas.h"  
#include "../lib/lodepng.h"
#include "../lib/tip.h"


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
  std::vector<Cell> set_alive(void) const;
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
  Canvas Can; // Gerador de Imagens Canvas
  Color alive; // Cor dos espaços vivos
  Color bkg; // Cor para os espaços ondenão há células
  size_t fps; // FPS de imagens a serem geradas

  public:
  // Ctro
  SimulationManager(const vector<vector<bool>>& input = {{}});

  // Ler as configs enviadas pelo arquivo de configuração
  int readConfig(void);

  // Atualizar as gerações
  std::string play(void);

  // Printa no console o resultado de uma geração 
  void print(void);

  // Gerador de imagens em png
  void encode_png(const char* filename, const unsigned char* image, unsigned width, unsigned height);

  // Divisor de strings em vector
  std::vector<std::string> split(const std::string & input_str, char delimiter='.');

  // Gerador de Imagens ppm
  bool save_ppm3(const char* file_name,
               const unsigned char* data,
               size_t w,
               size_t h,
               size_t d=4);
};


} // namespace life
#endif

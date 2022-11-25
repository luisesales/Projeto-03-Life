/**
 * LLSeq class implementation.
 *
 */

#include "life.h"
#include "tip.h"

namespace life {
/// Basic constructor that creates a life board with default dimensions.

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



/// Ctro
SimulationManager::SimulationManager(const vector<vector<bool>>& input){
    this->board = input;
}

/// Atualiza as gerações de acordo com as regras
void SimulationManager::play(void){
  size_t generations{0}; // Contador de gerações
  string key{""}; // Chave de busca no banco de dados de gerações
  string reason; // Razão para qual o programa vai parar
  bool index{true}; // Controlador de continuidade do jogo
  
  while(index){  
    // Checar se chegou ao limite de gerações
    if(generations >= amount){
      reason = "Atingiu o número de Gerações Desejado";
      index = false;
    }
    // Checar se chegou a extinção
    else if(Cfg.extinct()){
      reason = "Foi Extinto";
      index = false;
    }
    // Checar se chegou em estabilidade
    else if(Log.stable(key)){
      reason = "Entrou em Estabilidade";
      index = false;
    }
    // Aplicar as regras e pular para proxima geração
    else{
      // Recolhe a Chave
      key = Cfg.get_key();

      // Adiciona chave no database caso não existe ou adiciona 1 ao contador caso a chave já exista 
      Log.insert(key,1);

      // Aumenta-se o contador de gerações atual
      generations++;

      // Atualiza-se o tabuleiro pra nova geração

      // Printa-se o novo tabuleiro
      SimulationManager::print();
    }
  }
}
/// Printa no console o resultado de uma geração
void SimulationManager::print(void){
    string result{""}; // String do que será mostrado no console
    for(auto x : board){
      for(size_t i{0}; i < x.size();i++){
        result+=p[x[i]];
      }
      result+="\n";
    }
    std::cout << result << std::endl;
  }

/// Lê as configurações do arquivo de configurações
int SimulationManager::readConfig(void){
  std::ifstream bReader; // Leitor do Board
  char * line; // Variável onde vai ser slavo cada linha
  size_t nCol; // Quantidade de colunas do Tabuleiro
  size_t nLin; // Quantidade de Linhas do Tabuleiro
  size_t aux{0}; // Auxiliar para cessar todas as linhas do tabuleiro
  char cel; // Caractere que vai determinar onde tem as células vivas
  vector<Cell> CfgR; // VEctor que irá ser transformado no m_alive

  TIP reader{ ".config/glife.ini" };
    // Check for any parser error.
    if (not reader.parsing_ok()) {
      std::cerr << ">> Sorry, parser failed with message: " << reader.parser_error_msg() << "\n";
        return 1;
    }

    // Try to get pi value.
    auto val = reader.get_int("ROOT", "max_gen");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"max_gen\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        //std::cout << "Max gen is " << val << '\n';
        this->amount = val;
    }
    // Ler dados do canvas

    // Lendo a cor dos blocos onde há células
    auto colorA = reader.get_str("image","alive");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"alive\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } 

    // Lendo a cor dos blocos onde não há ceĺulas
    auto colorBkg = reader.get_str("image","bkg");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"bkg\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } 

    // Lendo o tamanho do pixel virtual
    auto BlockS = reader.get_int("image","block_size");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"block_size\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } 

    

    // Try to get user current active status.
    auto create_img = reader.get_bool("image", "generate_image");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"generate_image\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        //std::cout << "Generate Image situation is " << std::boolalpha << create_img << '\n';
    }

    // Try to get user current active status.
    auto fps = reader.get_int("text", "fps");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"fps\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        //std::cout << "FPS value is " << fps << '\n';
    }
    Canvas Caux(nCol,nLin,BlockS);  // Canvas auxiliar que será jogado ao canvas principal
    // Aplica-se cor de fundo do canvas
    Caux.clear(life::color_pallet[colorBkg]);

    // Lê-se o arquivo
    bReader.open(".config/board.txt");

    // Verifica se foi aberto com sucesso
    if(!bReader.is_open()){
      std::cout << ">>> Error while opening board file" << '\n';
      return 1;
    }
    // Lê-se a quantidade de linhas e colunas
    bReader.getline(line,3);
    // Verifica-se se a primeira linha é válida
    if(isdigit(line[0]) && line[1] == ' ' && isdigit(line[2])){
      nLin = (size_t) line[0];
      nCol = (size_t) line[2];

      // Lê-se o caractere que determina onde há células
      bReader.getline(line,1);
      cel = line[0];
      
      // Vai pegar cada linha do tabuleiro
      while(bReader.getline(line,nCol) && aux < nLin){
        string l = line;
        for(size_t i{0}; i < nCol;i++){
          if(l[i] == cel){
            // Determina onde no board há células
            board[aux][i] = 1;
            // Aplica a Cor de célula viva no Canvas
            Caux.pixel(aux,i,life::color_pallet[colorA]);
            // Adiciona um objeto de Cell ao Vector auxiliar
            CfgR.push_back({aux,i});
          }
          else{
            board[aux][i] = 0;
          }
        }
        aux++;
      }

      // Atualiza o Cfg com o vector auxiliar
      Cfg.update(CfgR);
    }
    else{
      std::cout << ">>> Error while reading Lines and Columns" << '\n';
      return 1;
    }
    bReader.close();

    // Aplicando valores ao canvas
    Can = Caux;

    return EXIT_SUCCESS;
}

}

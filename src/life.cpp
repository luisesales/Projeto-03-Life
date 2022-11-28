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

/// Saves an image as a **ascii** PPM file.
bool SimulationManager::save_ppm3(const char* file_name,
               const unsigned char* data,
               size_t w,
               size_t h,
               size_t d)
{
  std::ofstream ofs_file(file_name, std::ios::out);
  if (not ofs_file.is_open())
    return false;

    // TODO: Complete a geração do arquivo PPM!!


  ofs_file.close();

  return true;
}

// Example 1
// Encode from raw pixels to disk with a single function call
// The image argument has width * height RGBA pixels or width * height * 4 bytes
void SimulationManager::encode_png(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  // Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  // if there's an error, display it
  if (error)
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

/// Splits the input string based on `delimiter` into a list of substrings.
std::vector<std::string> SimulationManager::split(const std::string & input_str, char delimiter){
    // Store the tokens.
    std::vector<std::string> tokens;
    // read tokens from a string buffer.
    std::istringstream iss;
    iss.str(input_str);
    // This will hold a single token temporarily.
    std::string token;
    while (std::getline(iss >> std::ws, token, delimiter))
        tokens.emplace_back(token);
    return tokens;
}


/// Atualiza as gerações de acordo com as regras
string SimulationManager::play(void){
  size_t generations{0}; // Contador de gerações
  string key{""}; // Chave de busca no banco de dados de gerações
  string reason; // Razão para qual o programa vai parar
  bool index{true}; // Controlador de continuidade do jogo
  vector<vector<bool>> checked; // Verificador sobre as casas já acessadas de cada geração
  short neighbor; // Contador de Vizinhos por celulas
  vector<vector<bool>> nBoard; // Tabuleiro para a proxima geração
  vector<Cell> n_alive; // Vector que atualizará o m_alive para a proxima geração
  
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
      // Reinicia-se o canvas
      Can.clear(bkg);

      // Recolhe a Chave
      key = Cfg.get_key();

      // Adiciona chave no database caso não existe ou adiciona 1 ao contador caso a chave já exista 
      Log.insert(key,1);

      // Aumenta-se o contador de gerações atual
      generations++;

      // Atualiza-se o tabuleiro pra nova geração
      // Reiniciamos o tabuleiro para ler  a proxima geração
      nBoard.clear();
      n_alive.clear();
      for(size_t i{0}; i < board.size();i++){
        for (size_t j {0}; j < board[i].size();j++){
          // Reiniciamos o número de vizinhos para cada caso de teste
          neighbor = 0;
          for(short x{-1};x <= 1;x++){
            for(short y{-1};y <= 1;y++){
              // Verifica-se se a posição de vizinho já foi checada
              if(checked[i+x][j+y] == 0){
                // Passa-se em todas as posições vizinhas daquela célula
                if(board[i+x][j+y] == 1 && (y+j != j || x+i != i)){
                  neighbor++;
                }
              }
            }  
          }
          // Verifica-se as condições de acordo com as regras do jogo
          if(neighbor >= 4 || neighbor <= 1) nBoard[i][j] = 0;
          else if(neighbor == 3) {
            Can.pixel(i,j);
            nBoard[i][j] = 1;
            n_alive.push_back({i,j});
          }
          checked[i][j] = 1;
        }
      }
      // Atualiza-se o tabuleiro
      board = nBoard;
      LifeCfg nCfg(n_alive);
      Cfg.update(nCfg);
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
    alive = life::color_pallet[colorA];

    // Lendo a cor dos blocos onde não há ceĺulas
    auto colorBkg = reader.get_str("image","bkg");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"bkg\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } 
    bkg = life::color_pallet[colorBkg];

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
    auto f = reader.get_int("text", "fps");
    if (not reader.parsing_ok()) {
        std::cout << ">>> Error while retrieving \"fps\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
      fps = f;
        //std::cout << "FPS value is " << fps << '\n';
    }
    Canvas Caux(nCol,nLin,BlockS);  // Canvas auxiliar que será jogado ao canvas principal
    // Aplica-se cor de fundo do canvas
    Caux.clear(bkg);

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
            Caux.pixel(aux,i,alive);
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

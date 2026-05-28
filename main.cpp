#include <iostream>
#include <string>
#include <memory>

class Usuario {
    std::string nome_;
    std::string telefone_;

public:
    Usuario(std::string nome, std::string contato) : nome_(nome), telefone_(contato) {
        std::cout << "\nUsuario criado: " << nome_ << "\n";
    }
    
    ~Usuario() {
        std::cout << "~Usuario destruido: " << nome_ << "\n";
    }
    
    std::string get_nome() const { return nome_; }
    std::string get_telefone() const { return telefone_; }
    
    void validar_telefone() const {
        if (telefone_.length() == 13) {
            std::cout << "Telefone validado com sucesso.\n";
        } else {
            std::cout << "Telefone invalido. Deve ter 13 caracteres (Formato: 83 91234-5678)\n";
        }
    }
};

class Imovel {
    int quartos_disponiveis_;
    float aluguel_mensal_;
    std::string bairro_;
    float distancia_ufpb_;

public:
    Imovel(int quartos, float aluguel, std::string bairro, float distancia) 
        : quartos_disponiveis_(quartos), aluguel_mensal_(aluguel), bairro_(bairro), distancia_ufpb_(distancia) {
        std::cout << "\nImovel criado.\n";
    }
    
    ~Imovel() {
        std::cout << "~Imovel destruido.\n";
    }
    
    int get_quartos_disponiveis() const { return quartos_disponiveis_; }
    float get_aluguel_mensal() const { return aluguel_mensal_; }
    std::string get_bairro() const { return bairro_; }
    float get_distancia_ufpb() const { return distancia_ufpb_; }
    
    float calcular_preco_vaga() const {
        float preco = 0.0f;
        if (quartos_disponiveis_ > 0) {
            preco = aluguel_mensal_ / quartos_disponiveis_;
        }
        std::cout << "Valor calculado por vaga: R$ " << preco << "\n";
        return preco;
    }

    bool verificar_localizacao() const {
        if (distancia_ufpb_ <= 2.5f) {
            std::cout << "Localizado perto da UFPB.\n";
            return true;
        }
        std::cout << "Precisa de transporte para chegar a UFPB.\n";
        return false;
    }
};

class Anuncio {
    std::string titulo_;
    std::unique_ptr<Imovel> imovel_;
    std::shared_ptr<Usuario> anunciante_;

public:
    Anuncio(std::string titulo, int quartos, float aluguel, std::string bairro, float distancia, std::shared_ptr<Usuario> anunciante) 
        : titulo_(titulo), anunciante_(anunciante) {
        imovel_ = std::make_unique<Imovel>(quartos, aluguel, bairro, distancia);
        std::cout << "\nAnuncio criado: " << titulo_ << "\n";
    }
    
    ~Anuncio() {
        std::cout << "~Anuncio destruido: " << titulo_ << "\n";
    }
    
    std::string get_titulo() const { return titulo_; }
    std::shared_ptr<Usuario> get_anunciante() const { return anunciante_; }
    
    void exibir_anuncio() const {
        std::cout << "\n--- ANUNCIO UFLX ---\n";
        std::cout << "Titulo: " << titulo_ << "\n";
        std::cout << "Anunciante: " << anunciante_->get_nome() << " | Contato: " << anunciante_->get_telefone() << "\n";
        std::cout << "Bairro: " << imovel_->get_bairro() << "\n";
        imovel_->calcular_preco_vaga();
        imovel_->verificar_localizacao();
        std::cout << "--------------------\n\n";
    }
};

class Interesse {
    std::shared_ptr<Usuario> interessado_;
    std::weak_ptr<Anuncio> anuncio_alvo_;
    std::string mensagem_;

public:
    Interesse(std::shared_ptr<Usuario> interessado, std::shared_ptr<Anuncio> anuncio_alvo, std::string mensagem) 
        : interessado_(interessado), anuncio_alvo_(anuncio_alvo), mensagem_(mensagem) {
        std::cout << "\nInteresse registrado por: " << interessado_->get_nome() << "\n";
    }

    ~Interesse() {
        std::cout << "~Interesse destruido.\n";
    }

    std::shared_ptr<Usuario> get_interessado() const { return interessado_; }
    std::weak_ptr<Anuncio> get_anuncio_alvo() const { return anuncio_alvo_; }
    std::string get_mensagem() const { return mensagem_; }

    void processar_interesse() const {
        if (auto anuncio_ref = anuncio_alvo_.lock()) {
            std::cout << "\n ---- NOVO INTERESSE ---- \n";
            std::cout << "Anuncio: " << anuncio_ref->get_titulo() << "\n";
            std::cout << "Interessado: " << interessado_->get_nome() << " (" << interessado_->get_telefone() << ")\n";
            std::cout << "Mensagem: \"" << mensagem_ << "\"\n";
            std::cout << "-------------------------------\n";
        }
    }
};

int main() {
    std::cout << "--- Iniciando o Sistema ---\n\n";

    auto proprietario = std::make_shared<Usuario>("Artur Almeida", "83 99999-0000");
    proprietario->validar_telefone();

    auto cliente = std::make_shared<Usuario>("Maria Eloisa", "83 91234-5678");
    cliente->validar_telefone();

    {
        auto anuncio_vaga = std::make_shared<Anuncio>("Vaga em AP com 2 quartos", 2, 800.0f, "Castelo Branco", 1.5f, proprietario);
        anuncio_vaga->exibir_anuncio();
        
        Interesse interesse_maria(cliente, anuncio_vaga, "Tenho interesse na vaga, podemos agendar uma visita?");
        interesse_maria.processar_interesse();
    } 

    std::cout << "\nO usuario principal ainda existe no sistema: " << proprietario->get_nome() << "\n";
    std::cout << "O estudante interessado ainda existe: " << cliente->get_nome() << "\n\n";

    return 0;
}
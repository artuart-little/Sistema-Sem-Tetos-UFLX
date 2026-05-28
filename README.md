# Sistema UFLX

**Nome:** Artur Rodrigues Nunes de Almeida

**Matrícula:** 20250018637

## Descrição do Domínio
O UFLX é um sistema de comércio de imóveis voltado para estudantes universitários. A plataforma permite que proprietários anunciem vagas ou imóveis completos e que estudantes demonstrem interesse nessas ofertas, facilitando o contato direto entre as partes. Assim como o nome referencia ("UFLX"), é uma OLX para estudantes universitários encontrar mais facilmente parceiros próximos para encontrar moradia.

## Diagrama UML

```mermaid
classDiagram
    class Usuario {
        -string nome_
        -string telefone_
        +Usuario(string nome, string contato)
        +~Usuario()
        +get_nome() string
        +get_telefone() string
        +validar_telefone() void
    }

    class Imovel {
        -int quartos_disponiveis_
        -float aluguel_mensal_
        -string bairro_
        -float distancia_ufpb_
        +Imovel(int quartos, float aluguel, string bairro, float distancia)
        +~Imovel()
        +get_quartos_disponiveis() int
        +get_aluguel_mensal() float
        +get_bairro() string
        +get_distancia_ufpb() float
        +calcular_preco_vaga() float
        +verificar_localizacao() bool
    }

    class Anuncio {
        -string titulo_
        -unique_ptr~Imovel~ imovel_
        -shared_ptr~Usuario~ anunciante_
        +Anuncio(string titulo, int quartos, float aluguel, string bairro, float distancia, shared_ptr~Usuario~ anunciante)
        +~Anuncio()
        +get_titulo() string
        +get_anunciante() shared_ptr~Usuario~
        +exibir_anuncio() void
    }

    class Interesse {
        -shared_ptr~Usuario~ interessado_
        -weak_ptr~Anuncio~ anuncio_alvo_
        -string mensagem_
        +Interesse(shared_ptr~Usuario~ interessado, shared_ptr~Anuncio~ anuncio_alvo, string mensagem)
        +~Interesse()
        +get_interessado() shared_ptr~Usuario~
        +get_anuncio_alvo() weak_ptr~Anuncio~
        +get_mensagem() string
        +processar_interesse() void
    }

    Anuncio "1" *-- "1" Imovel : compoe
    Anuncio "1" o-- "1" Usuario : agrega
    Interesse "1" o-- "1" Usuario : agrega
    Interesse "1" o-- "1" Anuncio : observa (agrega)

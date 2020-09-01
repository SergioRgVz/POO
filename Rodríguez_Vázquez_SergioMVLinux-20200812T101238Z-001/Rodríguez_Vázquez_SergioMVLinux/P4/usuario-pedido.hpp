#ifndef USUARIO_PEDIDO
#define USUARIO_PEDIDO

#include <map>
#include <set>

class Pedido;
class Usuario;

class Usuario_Pedido
{
public:
    typedef std::set<Pedido *> Pedidos;

    void asocia(Usuario &U, Pedido &P)
    {
        UsuarioPedido[&U].insert(&P);
        PedidoUsuario[&P] = &U;
    }

    void asocia(Pedido &P, Usuario &U)
    {
        asocia(U, P);
    }
    
    Pedidos pedidos(Usuario &U){return UsuarioPedido[&U]; }
    Usuario *cliente(Pedido &P){return PedidoUsuario[&P]; }
    
private:
    std::map<Pedido *, Usuario *> PedidoUsuario;
    std::map<Usuario *, Pedidos> UsuarioPedido;
};

#endif
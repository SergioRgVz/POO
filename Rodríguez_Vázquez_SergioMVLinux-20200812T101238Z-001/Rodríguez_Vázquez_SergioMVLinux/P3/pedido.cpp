#include "pedido.hpp"

unsigned Pedido::N_pedidos = 0;

//Constructor
Pedido::Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F):n_p_(N_pedidos + 1), tarjeta_(&T), fpedido_(F), importe_(0.)
{
    if(U.n_articulos() == 0)
        throw Pedido::Vacio(&U);
    if(T.titular() != &U)
        throw Pedido::Impostor(&U);
    if(T.caducidad() < F)
        throw Tarjeta::Caducada(T.caducidad());

    Usuario::Articulos carroaux = U.compra(); //Hacemos esto para leer y borrar en un contenedor auxiliar y dejar el original intacto, de otra forma los iteradores fallarian

    bool pedido_vacio = true;

    for(auto &[articulo, cantidad]: carroaux)
    {
        if(articulo->stock() < cantidad)
        {
            const_cast<Usuario::Articulos &>(U.compra()).clear();
            throw Pedido::SinStock(articulo);
        }

        articulo->stock() -= cantidad;
        PA.pedir(*this, *articulo, articulo->precio(), cantidad);
        importe_ += articulo->precio() * cantidad;
        U.compra(*articulo, 0);
        pedido_vacio = false;
    }
    if(pedido_vacio == true)
        throw Pedido::Vacio(&U);

    UP.asocia(U, *this);
    n_p_ += N_pedidos;
}


std::ostream& operator <<(std::ostream &os, const Pedido &P)
{
    os << std::left << std::setw(13) << "Núm. pedido: " << P.numero() << std::endl
       << std::left << std::setw(13) << "Fecha: " << P.fecha() << std::endl
       << std::left << std::setw(13) << "Pagado con: " << P.tarjeta()->tipo() << "n.º: " << P.tarjeta()->numero() << std::endl
       << std::left << std::setw(13) << "Importe: " << std::fixed << std::setprecision(2) << P.total() << " €" << std::endl;

    return os;
}
#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iomanip>
#include <iostream>

class Pedido_Articulo;
class Tarjeta;
class Usuario_Pedido;

class Pedido
{
public:
    //Constructor
    Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F = Fecha());

    //OBSERVADORES
    const int numero() const noexcept {return n_p_;}
    const Tarjeta* tarjeta() const noexcept {return tarjeta_;}
    const Fecha fecha() const noexcept {return fpedido_;}
    const double total() const noexcept {return importe_;}
    static unsigned n_total_pedidos() noexcept {return N_pedidos;}

    //VACIO
    class Vacio
    {
        Usuario* us_;
        public:
            Vacio(Usuario* us): us_(us){}
            Usuario& usuario() const noexcept{return *us_;}
    };

    //IMPOSTOR
    class Impostor
    {
        Usuario* us_;
        public:
            Impostor(Usuario* us): us_(us){}
            Usuario& usuario() const noexcept {return *us_;} 
    };

    //SINSTOCK
    class SinStock
    {
        Articulo *art_;
        public:
            SinStock(Articulo *art): art_(art){};
            Articulo& articulo() const noexcept{return *art_;};
    };
private:
    int n_p_; //Numero de pedido, empieza en 1 y se incrementa en 1 tambien
    const Tarjeta* tarjeta_; //tarjeta con la que pagan
    Fecha fpedido_; //Fecha del pedido
    double importe_; //importe del pedido
    static unsigned N_pedidos; //Numero de pedidos hechos
};

std::ostream& operator <<(std::ostream& os, const Pedido& P);

#endif //PEDIDO_HPP
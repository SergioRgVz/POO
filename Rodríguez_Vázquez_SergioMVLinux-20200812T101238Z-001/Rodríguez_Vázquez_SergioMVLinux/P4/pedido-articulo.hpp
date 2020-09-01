#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iostream>
#include <iomanip>
#include "articulo.hpp"
#include "pedido.hpp"

////Clase LineaPedido
class Pedido;
class LineaPedido
{
public:
    //Constructor
    explicit LineaPedido(double precio, unsigned cantidad = 1);


    //Observadores
    const double precio_venta() const noexcept {return precio_;}
    const unsigned cantidad() const noexcept {return cantidad_;}

    //Con el destructor por defecto nos vale 
private:
    double precio_;
    unsigned cantidad_;
};

std::ostream& operator<<(std::ostream &os, const LineaPedido &LP);

class OrdenaPedidos
{
public:
    bool operator()(const Pedido *P1, const Pedido *P2) const;//{return P1->numero() < P2->numero();}
};
class OrdenaArticulos
{
public:
    bool operator()(const Articulo *A1, const Articulo *A2) const{return A1->referencia() < A2->referencia();}
};
class Pedido_Articulo
{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    // typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedidoArticulo; 
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    // typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArticuloPedido;

    //Pedir
    void pedir( Pedido &P,  Articulo &A, double precio, unsigned cantidad = 1); //Pedido Articulo
    void pedir( Articulo &A,  Pedido &P, double precio, unsigned cantidad = 1); //Articulo Pedido

    ItemsPedido &detalle(Pedido &P);
    Pedidos ventas(Articulo &A);

    std::ostream &mostrarDetallePedidos(std::ostream &os);
    std::ostream &mostrarVentasArticulos(std::ostream &os);
private:
    // PedidoArticulo pedart_;
    // ArticuloPedido artped_;
    
    std::map<Pedido *, ItemsPedido, OrdenaPedidos> pedart_;
    std::map<Articulo *, Pedidos, OrdenaArticulos> artped_;
    // artped_ a;
    // pedart_ b;
};

std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &P);
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &I) ;




#endif //PEDIDO_ARTICULO_HPP
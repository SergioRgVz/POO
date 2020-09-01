#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double precio, unsigned cantidad): precio_(precio), cantidad_(cantidad) {}

std::ostream& operator<<(std::ostream &os, const LineaPedido &LP)
{
    os << std::fixed << std::setprecision(2) << LP.precio_venta() << " €\t" << LP.cantidad();

    return os; 
}

bool OrdenaPedidos::operator()(const Pedido *P1, const Pedido *P2) const
{
    return P1->numero() < P2->numero();
}

void Pedido_Articulo::pedir( Pedido &P,  Articulo &A, double precio, unsigned cantidad)
{
    pedart_[&P].insert(std::make_pair(&A, LineaPedido(precio, cantidad)));
    artped_[&A].insert(std::make_pair(&P, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir( Articulo &A,  Pedido &P, double precio, unsigned cantidad)
{
    pedir(P, A, precio, cantidad);
}

Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(Pedido &P)
{
    return pedart_[&P];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo &A)
{
    return artped_[&A];
}

std::ostream &Pedido_Articulo::mostrarDetallePedidos(std::ostream &os)
{
    double total = 0;

    for(const auto &i: pedart_)
    {
        os << "Pedido núm. " << i.first->numero()
           << "\nCliente: " << i.first->tarjeta()->titular()->nombre()
           << "\tFecha: " << i.first->fecha() << i.second;

        total += i.first->total();
    }

    os << std::fixed << "\nTOTAL VENTAS:\t" << std::setprecision(2)
       << total << " €" << std::endl;

    return os;
}

std::ostream &Pedido_Articulo::mostrarVentasArticulos(std::ostream &os)
{
    for(const auto &i: artped_)
    {
        os << "Ventas de [" << (i.first)->referencia() << "] \""
           << (i.first)->titulo() << "\"\n"
           << i.second << std::endl;
    }
    os << std::endl;
    return os;
}



std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &P)
{
    double precio = 0;
    unsigned total = 0;
    Pedido_Articulo::Pedidos::const_iterator it;
    os << std::endl << "====================================================\n" << std::endl;
    os << "PVP \t Cant. \t Fecha venta \n";
    os << "====================================================\n" << std::endl;
    for(auto iter: P)
    {
        os << " " << iter.second.precio_venta() << "€\t";
        os << iter.second.cantidad() << "\t";
        os << iter.first->fecha() << std::endl;
        precio += (iter.second.precio_venta() * iter.second.cantidad());
        total += iter.second.cantidad();
    }
    os << "====================================================\n" << std::endl;
    os << std::fixed << std::setprecision(2) << precio << " €\t" << total << std::endl;

    return os;
}

std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &I)
{
    double precio = 0;
    Pedido_Articulo::ItemsPedido::const_iterator i;
    os << std::endl <<"====================================================\n" << std::endl;
    os << "PVP \t Cant. \t Articulo \n";
    os << "====================================================\n" << std::endl;
    for(i = I.begin(); i != I.end(); i++)
    {
        os << " " << i->second.precio_venta() << " €\t";
        os << i->second.cantidad() << "\t";
        os << "[" << i->first->referencia() << "] ";
        os << "\""<< i->first->titulo() <<  "\"" << std::endl;
        precio = precio + i->second.precio_venta() * i->second.cantidad();
    }

    os << "====================================================\n" << std::endl;
    os << std::fixed << std::setprecision(2) << precio << " €" << std::endl;
    return os;
}

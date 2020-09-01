#include "pedido.hpp"

unsigned Pedido::N_pedidos = 1;
// Pedido::N_pedidos = 0;
//Constructor
Pedido::Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F):n_p_(N_pedidos), tarjeta_(&T), fpedido_(F), importe_(0)
{//TODO
	Usuario::Articulos carrito = U.compra();
	bool vacio = true;
	if(carrito.empty())
		throw Vacio(U);
	if(T.titular() != &U)
		throw Impostor(U);
	if(T.caducidad() < F)
		throw Tarjeta::Caducada(T.caducidad());
	if(!T.activa())
		throw Tarjeta::Desactivada();
	Usuario::Articulos::const_iterator i = carrito.begin();
	while(i != carrito.end()){
		Articulo *actual = i->first;
		if(LibroDigital *ld = dynamic_cast<LibroDigital*>(actual)){
			if(ld->f_expir() >= F){
				PA.pedir(*this, *actual, actual->precio(), i->second);
				importe_ += i->second * actual->precio();
				vacio = false;
			}
			U.compra(*actual, 0);
		}else if (ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(actual)){
			if(i->second > aa->stock()){
				while(i != carrito.end()){
					U.compra(*i->first, 0);
					++i;
				}
				throw SinStock(actual);
			}
			PA.pedir(*this, *actual, actual->precio(), i->second);
			aa->stock() -= i->second;
			importe_ += i->second * actual->precio();
			U.compra(*actual, 0);
			vacio = false;
		}
		++i;
	}
	if(vacio)
		throw Vacio(U);
	UP.asocia(U, *this);
	N_pedidos++;
}


std::ostream& operator <<(std::ostream &os, const Pedido &P)
{
     os << std::left << std::setw(13) << "Núm. pedido: " << P.numero() << std::endl
        << std::left << std::setw(13) << "Fecha: " << P.fecha() << std::endl
        << std::left << std::setw(13) << "Pagado con: " << P.tarjeta()->tipo() << " n.o.: " << P.tarjeta()->numero() << std::endl
        << std::left << std::setw(13) << "Importe: " << std::fixed << std::setprecision(2) << P.total() << " €" << std::endl;
    // os << std::left;
    // os << "Núm. pedido: " << P.numero() << std::endl;
    // os << std::setw(13) << "Fecha: " << P.fecha() << std::endl;
    // os << std::setw(13) << "Pagado con: " << P.tarjeta()->tipo() << " n.o: " << P.tarjeta()->numero() << std::endl;
    // os << std::setw(13) << "Importe: " << std::fixed << std::setprecision(2) << P.total() << " €" << std::endl;

	// os << "Núm. pedido: " << P.numero() << '\n';
	// os << "Fecha:       " << P.fecha() << '\n';
	// os << "Pagado con:  " << (P.tarjeta())->tipo() << ' ' << (P.tarjeta())->numero() << '\n';
	// os << "Importe:     " << std::fixed << std::setprecision(2) << P.total() << " €";    
    return os;
}


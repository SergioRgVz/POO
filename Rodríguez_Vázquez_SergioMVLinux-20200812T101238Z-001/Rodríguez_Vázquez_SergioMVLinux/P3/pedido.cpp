#include "pedido.hpp"

unsigned Pedido::N_pedidos = 1;
// Pedido::N_pedidos = 0;
//Constructor
Pedido::Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F):n_p_(N_pedidos), tarjeta_(&T), fpedido_(F), importe_(0)
{//TODO
    // if(U.n_articulos() == 0)
    //     throw Pedido::Vacio(&U);
    // if(T.titular() != &U)
    //     throw Pedido::Impostor(&U);
    // if(T.caducidad() < F)
    //     throw Tarjeta::Caducada(T.caducidad());
    // if(!T.activa())
    //     throw Tarjeta::Desactivada();

    // Usuario::Articulos carroaux = U.compra(); //Hacemos esto para leer y borrar en un contenedor auxiliar y dejar el original intacto, de otra forma los iteradores fallarian

    // for(auto c: U.compra()) //C es una tupa <Articulo *, unsigned cantidad>, con ello comprobamos que hay stock suficiente para los articulos del pedido
    // {
    //     if(c.first->stock() < c.second)
    //     {
    //         for(auto& iter: carroaux)
    //             U.compra(*iter.first, 0);
    //         // const_cast<Usuario::Articulos&>(U.compra()).clear();
    //         throw SinStock(c.first);
    //     }
    // }
    // //bool pedido_vacio = true;
    // for(auto &c : carroaux)
    // {
    // //     if(articulo->stock() < cantidad)
    // //     {
    // //         const_cast<Usuario::Articulos &> (U.compra()).clear();
    // //         throw Pedido::SinStock(articulo);
    // //     }

    // //     articulo->stock() -= cantidad;
    // //     PA.pedir(*this, *articulo, articulo->precio(), cantidad);
    // //     importe_ += articulo->precio() * cantidad;
    // //     U.compra(*articulo, 0);
    // //     pedido_vacio = false;
    // // }
    // // if(pedido_vacio == true)
    // //     throw Pedido::Vacio(&U);

    //     Articulo* pa = c.first;
    //     unsigned cantidad = c.second;
    //     double precio = pa->precio();

    //     pa->stock() -= cantidad;
    //     PA.pedir(*this, *pa, precio, cantidad);
    //     importe_ += precio * cantidad;
    //     U.compra(*pa, 0);
    // }


    // UP.asocia(U, *this);
    // N_pedidos++;
    // n_p_ += N_pedidos;
    	Usuario::Articulos carrito = U.compra();
	if(carrito.empty())
		throw Pedido::Vacio(&U);
	if(T.titular() != &U)
		throw Pedido::Impostor(&U);
	if(T.caducidad() < F)
		throw Tarjeta::Caducada(T.caducidad());
	if(!T.activa())
		throw Tarjeta::Desactivada();
	Usuario::Articulos::const_iterator i = carrito.begin();
	while(i != carrito.end()){
		Articulo *actual = i->first;
		if(i->second > actual->stock()){
			while(i != carrito.end()){
				U.compra(*i->first, 0);
				++i;
			}
			throw SinStock(actual);
		}
		PA.pedir(*this, *actual, actual->precio(), i->second);
		actual->stock() -= i->second;
		importe_ += i->second * actual->precio();
		U.compra(*actual, 0);
		++i;
	}
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


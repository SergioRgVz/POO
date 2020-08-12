#ifndef FECHA_HPP
#define FECHA_HPP

class Fecha
{
public:
    //Constructores de la clase Fecha
    explicit Fecha(int dia=0, int mes=0, int anno=0);
    Fecha(const char *cadena);

    //Observadores de la clase
    int dia() const;
    int mes() const;
    int anno() const;

    //Operadores de asignacion de suma y resta
    Fecha &operator+=(int dia);
    Fecha &operator-=(int dia);

    //Preincremento y postincremento
    Fecha& operator--();
    Fecha operator--(int);

    //Operador de conversion implicita a const char*
    operator const char*() const;

    //Operador suma de una Fecha con un entero
    Fecha operator +(int dia) const;

    //Operador resta de una Fecha con un entero
    Fecha operator -(int dia) const;

    //Constantes estaticas de la clase
    static const int AnnoMinimo;
    static const int AnnoMaximo;

    //Clase anidada Invalida que es el tipo de las excepciones
    class Invalida
    {
    public:
        Invalida(const char *cadena);
        const char *por_que() const;
    private:
        char *info;
    };
    private:
        int d, m, y;
        void comprobar();
};
    
    bool operator==(const Fecha &fecha1, const Fecha &fecha2);
    bool operator<(const Fecha &fecha1, const Fecha &fecha2);
    bool operator>(const Fecha &fecha1, const Fecha &fecha2);
    bool operator!=(const Fecha &fecha1, const Fecha &fecha2);
    bool operator<=(const Fecha &fecha1, const Fecha &fecha2);
    bool operator>=(const Fecha &fecha1, const Fecha &fecha2);

    inline bool operator==(const Fecha &fecha1, const Fecha &fecha2)
    {
        return (fecha1.dia() == fecha2.dia() && fecha1.mes() == fecha2.mes() && fecha1.anno() == fecha2.anno());
    }

#endif //FECHA_HPP
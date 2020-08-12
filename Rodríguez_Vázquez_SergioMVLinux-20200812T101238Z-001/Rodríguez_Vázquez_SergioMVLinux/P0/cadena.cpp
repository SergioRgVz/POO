#include "cadena.hpp"
#include <cstring>
#include <stdexcept>

Cadena::Cadena(unsigned n, char relleno): s_(new char[n + 1]), tam_(n)
{
    for(int i = 0; i < tam_; i++)
        s_[i] = relleno;
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena &copia): s_(new char[copia.tam_ + 1]), tam_(copia.tam_)
{
    strcpy(s_,copia.s_);
}

Cadena::Cadena(const char *caracteres): s_(new char[copia.tam_ + 1]), tam_(strlen(caracteres))
{
    for(int i = 0; i <= tam_; i++)
        s_[i] = caracteres[i];
}

Cadena &Cadena::operator=(const Cadena &copia)
{
    if(this != &copia)
    {
        if(tam_ != copia.tam_)
        {
            delete[] s_;
            tam_ = copia.tam_;
            s_ = new char[tam_];
        }
    for(int i = 0; i <= tam_; i++)
        s_[i] = copia-s_[i];
    }
    return *this;
}

char Cadena::operator[](unsigned i) const
{
    return *(s_ + i);
}

char Cadena::operator[](unsigned i)
{
    return *(s_ + i);
}

char Cadena::at(unsigned i) const
{
    if(i >= tam_)
    {
        throw std::out_of_range{"Indice fuera del rango. "};
    }
    else
    {
        return *(s_ + i);
    }  
}

char &Cadena::at(unsigned i)
{
    if(i >= tam_)
    {
        throw std::out_of_range{"Indice fuera del rango. "};
    }
    else
    {
        return *(s_ + i);
    }  
}

Cadena Cadena::substr(unsigned i, unsigned tam) const
{
    if(i >= tam_)
        throw std::out_of_range{"Indice fuera del rango. "};
    else
    {
        int carposibles = tam_ - i;
        if(carposibles < tam)
            throw std::out_of_range{"Numero de caracteres se salen del limite. "};
        else
        {
            Cadena c{tam};
            for(int j = 0; j < c.tam_; j++)
                c.s_[j] = s_[i + j];
            c.s_[tam_] = '\0';
            return c;
        }
        
    }
}

unsigned Cadena::length() const
{
    return tam_;
}

Cadena::~Cadena()
{
    delete[] s_;
}

Cadena& Cadena::operator+=(const Cadena &copia)
{
    Cadena aux{*this};
    delete [] s_;
    s_ = new char[tam_ + copia.tam_ + 1];
    tam_ = copia.tam_ + aux.tam_;
    strcpy(s_, aux.s_);
    strcat(s_, copia.s_);
    return *this;
}

Cadena operator+(const Cadena &cad1, const Cadena &cad2)
{
    Cadena aux{cad1};
    aux +=  cad2;
    return aux;
}

Cadena::operator const char *() const
{
    return s_;
}

bool operator<(const Cadena &cad1, const Cadena &cad2)
{
    return(strcmp(cad1, cad2) < 0);
}

bool operator==(const Cadena &cad1, const Cadena &cad2)
{
    return(strcmp(cad1, cad2) == 0);
}

bool operator!=(const Cadena &cad1, const Cadena &cad2)
{
    return !(cad1==cad2);
}

bool operator<=(const Cadena &cad1, const Cadena &cad2)
{
    return !(cad2 < cad1);
}

bool operator>=(const Cadena &cad1, const Cadena &cad2)
{
    return !(cad1 < cad2);
}

bool operator>(const Cadena &cad1, const Cadena &cad2)
{
    return cad2 < cad1;
}
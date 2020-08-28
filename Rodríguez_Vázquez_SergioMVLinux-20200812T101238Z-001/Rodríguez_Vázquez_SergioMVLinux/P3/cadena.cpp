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

Cadena::Cadena(const char *caracteres): s_(new char[std::strlen(caracteres) + 1]), tam_(std::strlen(caracteres))
{
    for(int i = 0; i <= tam_; i++)
        s_[i] = caracteres[i];
}

Cadena::Cadena(Cadena &&C): s_(C.s_), tam_(C.tam_)
{
    C.tam_ = 0;
    C.s_ = nullptr;
}



Cadena &Cadena::operator=(const Cadena &copia) noexcept
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
        s_[i] = copia.s_[i];
    }
    return *this;
}

Cadena &Cadena::operator=(const char *cadena) noexcept
{
    delete[] s_;
    tam_ = std::strlen(cadena);

    s_ = new char[tam_ + 1];
    std::strcpy(s_, cadena);

    return *this;
}

Cadena &Cadena::operator=(Cadena &&C) noexcept
{
    if(this != &C)
    {
        delete[] s_;

        tam_ = C.tam_;
        s_ = C.s_;

        C.s_ = nullptr;
        C.tam_ = 0;
    }
    return *this;
}

char Cadena::operator[](unsigned i) const
{
    return *(s_ + i);
}

char& Cadena::operator[](unsigned i)
{
    return *(s_ + i);
}

const char *Cadena::c_str() const noexcept
{
    return s_;
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


Cadena::~Cadena()
{
    delete[] s_;
}

Cadena& Cadena::operator+=(const Cadena &copia) noexcept
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

/*Cadena::operator const char *() const
{
    return s_;
}*/

bool operator<(const Cadena &cad1, const Cadena &cad2) noexcept
{
    if(cad1.length() < cad2.length()) return true;
    if(cad1.length() > cad2.length()) return false;

    int last = cad1.length();
    for(int i = 0; i < last; i++)
    {
    if ((static_cast<int>(cad1.at(i))) < (static_cast<int>(cad2.at(i)))) return true;
    }

    return false;
}

bool operator==(const Cadena &cad1, const Cadena &cad2) noexcept
{
    if(cad1.length() != cad2.length()) return false;
    for(int i = 0; i < cad1.length(); i++)
    {
        if(cad1[i] != cad2[i]) return false;
    }
    return true;
}

bool operator!=(const Cadena &cad1, const Cadena &cad2) noexcept
{
    return !(cad1==cad2);
}

bool operator<=(const Cadena &cad1, const Cadena &cad2) noexcept
{
    if(cad1 == cad2) return true;
    return !(cad2 < cad1);
}

bool operator>=(const Cadena &cad1, const Cadena &cad2) noexcept
{
    if(cad1 == cad2) return true;
    return !(cad1 < cad2);
}

bool operator>(const Cadena &cad1, const Cadena &cad2) noexcept
{
    return (cad2 < cad1);
}

std::ostream &operator<<(std::ostream &os, const Cadena &C)
{
    os << C.c_str();

    return os;
}

std::istream &operator>>(std::istream &is, Cadena &C)
{
    char *cadena = new char[33];
    int i = 0;
    char aux;

    while(isspace(is.get()) && is.good())
    {}
    is.unget();

    while(i <32 && !isspace(is.peek()) && is.good() && is.peek() != '\n' && is.peek() != '\0')
    {
        aux = is.get();

        if(is.good())
            cadena[i++] = aux;
    }

    cadena[i] = '\0';
    C = cadena;
    
    delete[] cadena;

    return is;
}
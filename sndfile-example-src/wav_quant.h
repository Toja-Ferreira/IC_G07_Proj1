#ifndef WAVQUANT_H
#define WAVQUANT_H

#include <iostream>
#include <vector>

class WAVQuant{
    private:
        short bit_cut;
        size_t n;
        std::vector<short> quant;
    
    public:
    WAVQuant(size_t n, short bit_cut){
        this->bit_cut = bit_cut;
        this-> n  = n;
        quant.resize(n);
    }
    void uniform_scalar(const std::vector<short>& samples){
        size_t i{ };
        for(auto &s: samples){
            quant[i++] = s >> bit_cut;
        }
    }
    void print_quant(){
        for(auto& s: quant){
            std::cout <<s << std::endl;
        }
    }
    std::vector<short> get_quant(){

        std::vector<short> new_quant;
        new_quant.resize(n);

        size_t i{ };
        for(auto& s: quant){
            new_quant[i++]= s<<bit_cut;
        }
        return new_quant;
    }
};

#endif
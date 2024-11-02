#include "IFB.h"

template <typename T>
IFB<T>::IFB(std::map<std::string, T> inputs,
        std::map<std::pair<std::string, std::string>, T>  outputs, 
        std::vector<IFB*> next){

            this->inputs = inputs;
            this->outputs = outputs;
            this->next = next;

        }

template <typename T>
void IFB<T>::call(){
    this->execute();
    this->sentOutputs();
}

//TODO: do this func
template <typename T>
void IFB<T>::sentOutputs(){

}
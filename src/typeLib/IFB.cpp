#include "IFB.h"

IFB::IFB(std::map<std::string, std::string> inputs, 
            std::map<std::string, std::string> connections, 
            std::vector<std::string> next,
            std::string FBname){

            this->FBname = FBname;
            this->connections = connections;
            this->inputs = inputs;
            this->outputs = outputs;
            this->next = next;

        }


void IFB::call(GlobalOutputs* outputs){
    this->execute(outputs);
    this->sentOutputs();
}

std::map<std::string, std::string> IFB::getConnections(){
    return this->connections;
}

//TODO: do this funcz
void IFB::sentOutputs(){

}

void IFB::setNext(std::vector<std::string> newNext){
    this->next=newNext;
}

std::vector<std::string> IFB::getNext(){
    return this->next;
}

std::map<std::string, std::string> IFB::getInputs(){
    return this->inputs;
}

void IFB::setInputs(std::map<std::string, std::string> inputs){
    this->inputs = inputs;
}


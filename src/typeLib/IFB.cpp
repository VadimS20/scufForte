#include "IFB.h"

IFB::IFB(std::map<std::string, std::string> inputs,
            GlobalOutputs* outputs, 
            std::map<std::string, std::string> connections, 
            std::vector<IFB*> next,
            std::string FBname){

            this->FBname = FBname;
            this->connections = connections;
            this->inputs = inputs;
            this->outputs = outputs;
            this->next = next;
            this->outputs = GlobalOutputs::getInstance(outputs->getOutputs());

        }


void IFB::call(){
    this->execute();
    this->sentOutputs();
}

std::map<std::string, std::string> IFB::getConnections(){
    return this->connections;
}

//TODO: do this funcz
void IFB::sentOutputs(){

}

void IFB::setNext(std::vector<IFB*> newNext){
    this->next=newNext;
}

std::vector<IFB*> IFB::getNext(){
    return this->next;
}

std::map<std::string, std::string> IFB::getInputs(){
    return this->inputs;
}

void IFB::setInputs(std::map<std::string, std::string> inputs){
    this->inputs = inputs;
}


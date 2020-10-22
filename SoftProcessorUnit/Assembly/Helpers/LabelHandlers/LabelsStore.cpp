//
//  HashTable.cpp
//  SPUAsm
//
//  Created by Александр Дремов on 16.10.2020.
//

#include "LabelsStore.hpp"
#include <cstdlib>
#include <cstring>


JMPLabel::JMPLabel(JMPLabel* previous, char* name) {
    if (previous != nullptr)
        previous->next = this;
    this->nameLen = strlen(name);
    this->name = (char*)calloc(this->nameLen + 1, sizeof(char));
    this->next = nullptr;
    this->used = 0;
    this->positionTo = -1;
    this->positionFrom = -1;
    strcpy(this->name, name);
}

JMPLabel::~JMPLabel(){
    free(this->name);
}

void JMPLabel::wasUsed() {
    this->used++;
}

void JMPLabel::foundToPosition(unsigned int position) {
    this->positionTo = (long)position;
}


void JMPLabelsStore::newLabel(char* label) {
    JMPLabel* previous = this->last;
    JMPLabel* newLabel = new JMPLabel(this->last, label);
    if (this->last == nullptr)
        this->first = (this->last = newLabel);
    else
        this->last  = newLabel;
    
    
    JMPLabel* current = this->first;
    while (current != nullptr && current != this->last) {
        if (strcmp(current->name, newLabel->name) == 0){
            previous->next = nullptr;
            this->last = previous;
            delete newLabel;
            throw "Label exists";
        }
        
        current = current->next;
    }
}

void JMPLabelsStore::setLabelToPosition(char* label, unsigned int position) {
    JMPLabel* current = this->getLabel(label);
    
    if (current == nullptr) {
        this->newLabel(label);
        current = this->last;
    }
    
    current->wasUsed();
    if (current->used != 1) {
        throw "This label was used";
    }
    current->positionTo = (long)position;
}

void JMPLabelsStore::setLabelFromPosition(char* label, unsigned int position) {
    JMPLabel* current = this->getLabel(label);
    
    if (current == nullptr) {
        this->newLabel(label);
        current = this->last;
    }
    current->positionFrom = (long)position;
}

JMPLabel* JMPLabelsStore::getLabel(char* label) const {
    JMPLabel* current = this->first;
    while (current != nullptr) {
        if (strcmp(current->name, label) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return nullptr;
}

JMPLabelsStore::~JMPLabelsStore() {
    JMPLabel* current = this->first;
    
    while (current != nullptr) {
        JMPLabel* next = current->next;
        delete current;
        current = next;
    }
}

long int JMPLabelsStore::getLabelToPosition(char* label) const {
    JMPLabel* current = this->first;
    while (current != nullptr) {
        if (strcmp(current->name, label) == 0) {
            return current->positionTo;
        }
        current = current->next;
    }
    return -1;
}

JMPLabelsStore::JMPLabelsStore() {
    this->first = nullptr;
    this->last = nullptr;
}

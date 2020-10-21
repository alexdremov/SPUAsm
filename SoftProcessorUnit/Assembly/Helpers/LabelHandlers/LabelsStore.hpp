//
//  HashTable.hpp
//  SPUAsm
//
//  Created by Александр Дремов on 16.10.2020.
//

#ifndef LabelsStore_hpp
#define LabelsStore_hpp

#include <cstdio>

struct JMPLabel {
    char*  name                 ;
    size_t nameLen              ;
    unsigned int    used        ;
    long int    positionTo      ;
    long int    positionFrom    ;
    JMPLabel* next              ;
    
    
    JMPLabel(JMPLabel* previous, char* name);
    
    ~JMPLabel();
    
    void wasUsed();
    
    void foundToPosition(unsigned int position);
};

struct JMPLabelsStore {
    JMPLabel* first;
    JMPLabel* last;
    
    void newLabel(char* label);
    
    void setLabelToPosition(char* label, unsigned int position);
    
    void setLabelFromPosition(char* label, unsigned int position);
    
    long int getLabelToPosition(char* label) const;
    
    JMPLabel* getLabel(char* label) const;
    
    JMPLabelsStore();
    
    ~JMPLabelsStore();
};


#endif /* LabelsStore_hpp */

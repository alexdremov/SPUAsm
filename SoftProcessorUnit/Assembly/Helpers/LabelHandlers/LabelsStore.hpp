//
//  HashTable.hpp
//  SPUAsm
//
//  Created by Александр Дремов on 16.10.2020.
//

#ifndef LabelsStore_hpp
#define LabelsStore_hpp

#include <stdio.h>

struct JMPLabel {
    char*  name                  = NULL;
    size_t nameLen               = 0;
    unsigned int    used         = 0;
    long int    positionTo       = -1;
    long int    positionFrom     = -1;
    JMPLabel* next               = NULL;
                
    
    JMPLabel(JMPLabel* previous, char* name);
    
    ~JMPLabel();
    
    void wasUsed();
    
    void foundToPosition(unsigned int position);
};

struct JMPLabelsStore {
    JMPLabel* first = NULL;
    JMPLabel* last  = NULL;
    
    void newLabel(char* label);
    
    void setLabelToPosition(char* label, unsigned int position);
    
    void setLabelFromPosition(char* label, unsigned int position);
    
    long int getLabelToPosition(char* label);
    
    JMPLabel* getLabel(char* label);
    
    JMPLabelsStore();
    
    ~JMPLabelsStore();
};


#endif /* LabelsStore_hpp */

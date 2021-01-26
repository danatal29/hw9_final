
#include <iostream>
#include <stddef.h>
#include "port.h"

#define PORT_FIELDS 2
#define SEGMENTS 4
#define BYTE 8


/*c'tor*/
Port::Port(String pattern):Field(pattern,PORT){
    range[0]=0;
    range[1]=0;
}


/**
 * @brief Sets the legal range of values of port - [range[0],range[1]]
 * Returns true on success, fails if val is an illegal rule 
 */
bool Port::set_value(String val){
    String *fields;
    size_t fields_amount=0;
    const char *delim="-";
    val=val.trim();
    val.split(delim,&fields,&fields_amount);
    if (fields_amount!=PORT_FIELDS){
        delete [] fields;
        return false;
    }
    fields[0]=fields[0].trim();
    fields[1]=fields[1].trim();
    range[0]=fields[0].to_integer();
    range[1]=fields[1].to_integer();
    delete [] fields;
    return true;

}

/**
 * @brief Returns true if val is within legal range - range[0],range[1]
 */
bool  Port::match_value(String val) const{
    int port_num=val.to_integer();
    return ((port_num>=range[0])&&(port_num<=range[1]));
}



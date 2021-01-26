
#include <iostream>
#include <stddef.h>
#include "ip.h"
#include <cmath>

#define MASK_SEGMENT 2
#define SEGMENTS 4
#define BYTE 8



Ip::Ip(String pattern):Field(pattern,IP),low(0),high(0){

}

/**
 * @brief Returns integral address's value
 * Returns true on success, fails if val is an illegal rule 
 * caller to calc value need to delete subfields
*/
unsigned int calc_value(String val,const char *delim,String **fields,
                                                          bool *succ){
    size_t counter_fields=0;
    /*split address 127.0.0.1 to 127,0,0,1*/
    val.split(delim,fields,&counter_fields);
    if(counter_fields!=SEGMENTS){
        *succ= false;
        return 1;
    }

    /*assist array, holds sub address int value*/
    int ip_val[SEGMENTS];

    for (int i=0; i<SEGMENTS ; i++){
        ((*fields)[i])=((*fields)[i]).trim();
        ip_val[i]=((*fields)[i]).to_integer();
    }
    /*bitwise calculation of address*/
    unsigned int ip= ((ip_val[0])<<BYTE*3) | ((ip_val[1])<<BYTE*2) |
                     ((ip_val[2])<<BYTE) | ((ip_val[3]));
    *succ= true;
    return ip;
}


/**
 * @brief Sets the legal range of values of Ip - [low,high]
 * Returns true on success, fails if val is an illegal rule 
 * caller to calc value and split needs to delete[]
*/
bool Ip::set_value(String val){
    String *fields;
    String *sub_fields;
    size_t counter_fields;
    const char *delim= "/";
    const char *sub_delim= ".";
    bool succ= false;

    /*splitting rule to address and mask*/
    /*field[0] is address and field[1]*/
    val.split(delim,&fields,&counter_fields);
    if(counter_fields!=MASK_SEGMENT){
        delete [] fields;
        return false;
    }
    for (int i=0; i<MASK_SEGMENT ;i++){
        fields[i]=fields[i].trim();
    }
    int mask=(fields[1]).to_integer();
    /*calculate address's value*/
    unsigned int ip= calc_value(fields[0],sub_delim,&sub_fields,&succ);
    if(succ==false){
        delete [] fields;
        delete [] sub_fields;
        return false;
    }
    /*bitewise calc low and high*/
    int dont_care_bits= SEGMENTS*BYTE-mask;
    /* shifting back and forth replaces with zeros*/
    low= (ip>>dont_care_bits)<<dont_care_bits;
    high= low + pow(2,dont_care_bits) -1;
    delete [] fields;
    delete [] sub_fields;
    return true;
}

/**
 * @brief Returns true if val is within legal range - [low,high]
 */
bool Ip::match_value(String val) const{\
    /*initiating params for calc_value()*/
    const char *delim=".";
    String *fields;
    bool succ=false;

    unsigned int ip_val = calc_value(val,delim,&fields,&succ);
    if (succ==false){
        delete [] fields;
        return false;
    }
    if((ip_val>=low)&&(ip_val<=high)){
        delete [] fields;
        return true;
    }
    delete [] fields;
    return false;
}


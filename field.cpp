
#include <stddef.h>
#include <iostream>
#include <string.h>
#include "field.h"
#include "ip.h"
#include "port.h"

/*DEFINES*/
#define MASK_SEGMENT 2
#define SUB_FIELDS 2
#define SEGMENTS 4
#define BYTE 8


/*c'tor*/
Field::Field(String pattern, field_type type):type(type){
    this->pattern=pattern;
}

/*c'tor*/
Field::Field(String pattern) :type(GENERIC) {
      this->pattern=pattern;
}

/*d'tor*/
Field::~Field(){
}

/**
 * @brief Virtual emulator - proxy to relevant set_value() - Ip/Port\
 * Returns bool token for succ/fail, fails if there's no matching type 
*/
bool Field::set_value(String val){
    if(type==IP){
        return (Ip*)this->set_value(val);
    }
    if(type==PORT){
        return (Port*)this->set_value(val);
    }
    return false;
}

/**
 * @brief Virtual emulator - proxy to relevant match_value() - Ip/Port\
 * Returns bool token for succ/fail, fails if there's no matching type 
*/
bool Field::match_value(String val)const{
    if(type==IP){

        return ((Ip*)this)->match_value(val);
    }
    if(type==PORT){
        return ((Port*)this)->match_value(val);
    }
    return false;
}

/**
 * @brief Returns true is "packets"'s integral value is within legal range
 * fails is split() fails, or value is out of legal range
*/
bool Field::match(String packet){
    /*initiate params for split()*/
    String *fields;
    String *sub_fields;
    size_t field_count;
    size_t sub_field_count;

    const char *delim=",";
    const char *sub_delim="=";
    /*splitting to packet fields*/
    packet.split(delim,&fields,&field_count);
    if (field_count!=SEGMENTS){
        delete [] fields;
        delete [] sub_fields;
        return false;
    }
    /*split each field to pattern and val*/
    for (size_t i=0; i<field_count; i++){
        fields[i]=fields[i].trim();
        (fields[i]).split(sub_delim,&sub_fields,&sub_field_count);
        if(sub_field_count!=SUB_FIELDS){
            continue;
        }
        /*temp_type is pattern of field*/

        String temp_type= sub_fields[0].trim();
        /*if (true), no need to check other fields*/
        if (temp_type.equals(pattern)){
            String temp_val = sub_fields[1].trim();
            delete [] fields;
            delete [] sub_fields;
            /*check if val is within legal interval*/
            return match_value(temp_val);
        }
    }
    delete [] fields;
    delete [] sub_fields;
    return false;
}

/** getters **/
field_type Field::get_type() const{
    return type;
}

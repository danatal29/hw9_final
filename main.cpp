#include <iostream>
#include <stdlib.h>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"




int main(int argc, char **argv) {
    /*varifing args legitimacy*/
    if((check_args(argc,argv)) != 0){
        exit (1);
    }
    /*initiate params for split()*/
    const char *delim="=";
    String *tmp_ptr;
    String **fields = &tmp_ptr;
    size_t field_count;
    String rule(argv[1]);

    /*split rule to "pattern" and "val"*/
    rule=rule.trim();
    rule.split(delim,fields,&field_count);
    String pattern=((*fields)[0]);
    String val=((*fields)[1]);
    pattern=pattern.trim();
    val=val.trim();
    
    /*refering to relevant class according to pattern*/
    if((pattern.equals("src-ip"))||(pattern.equals("dst-ip"))){
        Ip ip_rule(pattern);
        ip_rule.set_value(val);
        parse_input(ip_rule);
    }
    else if((pattern.equals("src-port"))||(pattern.equals("dst-port"))){
        Port port_rule(pattern);
        port_rule.set_value(val);
        parse_input(port_rule);

    }

    delete[] *fields;
    return 0;
}








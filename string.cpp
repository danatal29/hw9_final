
#include <stddef.h>
#include <iostream>
#include "string.h"
#include <string.h>


/**
* @brief Initiates an empty string - c'tor
*/
String::String(): length(0){
    data= new char [1];
    strcpy(data,"\0");
}


/**
 * @brief Initiates string from other string - copy c'tor
 */
String::String(const String &str) {
    if(str.data==NULL){
        exit (1);
    }
    data= new char [str.length+1];
    strcpy(data,str.data);
    length=str.length;
}


/**
 * @brief Initiates a string from char array - c'tor
 */
String::String(const char *str)  {
    if (str == NULL) {
        exit(1);
    }
    data = new char[strlen(str) + 1];
    strcpy(data, str);
    length = strlen(str);
}

/**
 * @brief Deletes a String - d'tor
 */
String::~String() {
    delete[] data;

}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs) {
    /*error if they're the same and data is deleted*/
    if(this != &rhs) {
        delete[] data; 
        if (rhs.data==NULL) {
            data=NULL;
        }
        data = new char[rhs.length+1];
        strcpy(data, rhs.data);
        length=rhs.length;
    }
    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str) {
    delete[] data; 
    if (str==NULL) { 
        data=NULL;
    }

    data = new char[strlen(str)+1];
    strcpy(data, str);
    length = strlen(str);
    return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const {
    if(rhs.data==NULL){
        if(data==NULL) {
            return true;
        }
        return false;
    }
    return (!strcmp(data, rhs.data));
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const {
    if(rhs==NULL){
        if(data==NULL) {
            return true;
        }
        return false;
    }
    return (!strcmp(data, rhs));
}

/**
 * @brief Returns number of fields in data, seperated by delimiters
 */
size_t count_fields (const char *delimiters, const char *data,size_t length)  {
    char buf1[length+1] ;
    strcpy(buf1,data);
    size_t count = 0;
    char *ptr  = strtok(buf1, delimiters);
    while(ptr != NULL){
        count++;
        ptr = strtok(NULL, delimiters);
    }
    return count;
}

/**
 * @brief Saving field's in "data" as an array  - "*fields"
 * Allocates memory for each String that the user must delete (using delete[]).
 * @note Does not affect this. Returns true on success, fails on faulty pointers.
 */
bool fill_array(const char *delimiters, String *fields,const char *data, size_t length)  {

    if ((delimiters == NULL) || (fields == NULL)) {
        return false;
    }

    char buf1[length+1] ;
    strcpy(buf1,data);
    int i = 0;
    char *sub_string = strtok(buf1, delimiters);

    while (sub_string != NULL) {
        size_t temp_size = strlen(sub_string);
        char temp_token[temp_size+1];
        strcpy(temp_token,sub_string);
        String *field=new String(temp_token);
        fields[i] = *field;
        delete field;
        sub_string = strtok(NULL, delimiters);
        i++;
    }
    return true;
}




/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const{
    *size= count_fields(delimiters, data, length);

    if(output==NULL){ 
        return;
    }

    String *fields= new String [*size];
    if(fill_array(delimiters,fields, data, length)) {
        *output = fields;
        return;
    }
    exit(1);
}

/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
    return atoi(data);
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const{
    char *start = data;
    char *end = (start+length-1);
    const char white_space=' ';
    size_t counter = length;

    /*calc length of post trim() string */
    while (*start == white_space){
        start++;
        counter--;
    }
    while(*end==white_space){
        end--;
        counter--;
    }
    /*copy only relevant part of string*/
    char temp_str[counter+1];
    strncpy(temp_str,start,counter);
    temp_str[counter] = '\0';
    String trim_str(temp_str);
    return trim_str;
}



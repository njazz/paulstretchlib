#include "XMLwrapper.h"

XMLwrapper::XMLwrapper(){}
    XMLwrapper::~XMLwrapper(){}

    /********************************/
    /*         SAVE to XML          */
    /********************************/

    //returns 0 if ok or -1 if the file cannot be saved
    int XMLwrapper::saveXMLfile(const char *filename){ return -1;};

    //returns the new allocated string that contains the XML data (used for clipboard)
    //the string is NULL terminated
    char XMLwrapper::*getXMLdata() { return 0; };

    //add simple parameter (name and value)
    void XMLwrapper::addpar(const char *name,int val) {};
    void XMLwrapper::addparreal(const char *name,REALTYPE val) {};

    //add boolean parameter (name and boolean value)
    //if the value is 0 => "yes", else "no"
    void XMLwrapper::addparbool(const char *name,int val) {};

    //add string parameter (name and string)
    void XMLwrapper::addparstr(const char *name,const char *val) {};

    //add a branch
    void XMLwrapper::beginbranch(const char *name) {};
    void XMLwrapper::beginbranch(const char *name, int id) {};

    //this must be called after each branch (nodes that contains child nodes)
    void XMLwrapper::endbranch() {};

    /********************************/
    /*        LOAD from XML         */
    /********************************/

    //returns 0 if ok or -1 if the file cannot be loaded
    int XMLwrapper::loadXMLfile(const char *filename) { return -1;};

    //used by the clipboard
    bool XMLwrapper::putXMLdata(char *xmldata) { return false;};

    //enter into the branch
    //returns 1 if is ok, or 0 otherwise
    int XMLwrapper::enterbranch(const char *name) { return 0;};


    //enter into the branch with id
    //returns 1 if is ok, or 0 otherwise
    int XMLwrapper::enterbranch(const char *name, int id) { return 0;};

    //exits from a branch
    void XMLwrapper::exitbranch() {};

    //get the the branch_id and limits it between the min and max
    //if min==max==0, it will not limit it
    //if there isn't any id, will return min
    //this must be called only imediately after enterbranch()
    int XMLwrapper::getbranchid(int min, int max) { return 0;};

    //it returns the parameter and limits it between min and max
    //if min==max==0, it will not limit it
    //if no parameter will be here, the defaultpar will be returned
    int XMLwrapper::getpar(const char *name,int defaultpar,int min,int max) { return 0;};

    //the same as getpar, but the limits are 0 and 127
    int XMLwrapper::getpar127(const char *name,int defaultpar) { return 0;};

    int XMLwrapper::getparbool(const char *name,int defaultpar) { return 0;};

    void XMLwrapper::getparstr(const char *name,char *par,int maxstrlen){}
    REALTYPE XMLwrapper::getparreal(const char *name,REALTYPE defaultpar) { return 0; };
    REALTYPE XMLwrapper::getparreal(const char *name,REALTYPE defaultpar,REALTYPE min,REALTYPE max) { return 0;};



    //opens a file and parse only the "information" data on it
    //returns "true" if all went ok or "false" on errors
    bool XMLwrapper::checkfileinformation(char *filename) { return false;};

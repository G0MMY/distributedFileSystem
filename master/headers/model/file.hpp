#ifndef FILE_HPP
#define FILE_HPP

class File {
    char* name;
    char* salt;

public:
    File(char* name, char* salt): name{name}, salt{salt} { }

    char* GetName();
};

#endif

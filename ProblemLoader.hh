#ifndef PROBLEMLOADER_HH
#define	PROBLEMLOADER_HH

#include <dlfcn.h>
#include <string>
#include <iostream>
#include "Problem.hh"

class ProblemLoader {
public:
    ProblemLoader();
    ~ProblemLoader();
    
    Problem *load(const std::string &libPath);
    void    close();
    Problem *getProblem() const;
private:
    std::string _libPath;
    void        *_sharedLibrary;
    Problem     *_problem;
    create_t    *_constructor;
    destroy_t   *_destructor;
};

#endif	/* PROBLEMLOADER_HH */


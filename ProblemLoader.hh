/* 
 * File:   ProblemLoader.hh
 * Author: jeremy
 *
 * Created on 17 December 2015, 15:23
 */

#ifndef PROBLEMLOADER_HH
#define	PROBLEMLOADER_HH

#include <dlfcn.h>
#include <string>
#include <iostream>
#include "Problem.hh"

class ProblemLoader {
public:
    ProblemLoader(std::string libPath);
    ~ProblemLoader();
    
    Problem *getProblem() const;
private:
    std::string _libPath;
    void        *_sharedLibrary;
    Problem     *_problem;
    create_t    *_constructor;
    destroy_t   *_destructor;
};

#endif	/* PROBLEMLOADER_HH */


#ifndef PROBLEMLOADER_HH
#define	PROBLEMLOADER_HH

#include <dlfcn.h>
#include <string>
#include <iostream>
#include "Problem.hh"

class ProblemLoader {
public:
    ProblemLoader();
    
    /**
     * load a library into the libraryLoader
     * @param libPath, shared library path
     * @return the loaded problem. Throw an error if the function encounters an issue. 
     */
    Problem *load(const std::string &libPath);
    
    /**
     * CLose the current library and delete the current problem
     */
    void    close();
    
    /**
     * get the current problem
     * @return the current problem or NULL if not problem is loaded
     */
    Problem *getProblem() const;
private:
    // pointer to a shared library entrance
    void        *_sharedLibrary;
    // pointer to the current problem
    Problem     *_problem;
    // Pointer to the Problem constructor
    create_t    *_constructor;
};

#endif	/* PROBLEMLOADER_HH */


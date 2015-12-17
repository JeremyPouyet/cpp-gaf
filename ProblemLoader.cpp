/* 
 * File:   ProblemLoader.cpp
 * Author: jeremy
 * 
 * Created on 17 December 2015, 15:23
 */

#include "ProblemLoader.hh"

ProblemLoader::ProblemLoader(std::string libPath) : 
_libPath(libPath)
{
    _sharedLibrary = dlopen("./EquationProblem.so", RTLD_LAZY);
    if (!_sharedLibrary) {
        std::cerr << "Cannot open lib" << std::endl;
        //return 1;
    }
    
    dlerror();
    _constructor = (create_t *)dlsym(_sharedLibrary, "create");
    const char * dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load create symbol" << dlsym_error << std::endl;
        //return 1;
    }
    
    _destructor = (destroy_t *)dlsym(_sharedLibrary, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load destroy symbol " << dlsym_error << std::endl;
        //return 1;
    }
    _problem = _constructor();
}

ProblemLoader::~ProblemLoader() {
    _destructor(_problem);
    dlclose(_sharedLibrary);
}

Problem * ProblemLoader::getProblem() const {
    return _problem;
}


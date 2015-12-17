#include "ProblemLoader.hh"

ProblemLoader::ProblemLoader() 
: _sharedLibrary(NULL), _problem(NULL) {}

Problem *ProblemLoader::load(const std::string &libPath) {
    _sharedLibrary = dlopen("./EquationProblem.so", RTLD_LAZY);
    if (!_sharedLibrary)
        throw "Cannot open lib";
    
    dlerror();
    _constructor = (create_t *)dlsym(_sharedLibrary, "create");
    const char * dlsym_error = dlerror();
    if (dlsym_error)
        throw "Cannot load create symbol: " + dlsym_error;
    
    _destructor = (destroy_t *)dlsym(_sharedLibrary, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
        throw "Cannot load destroy symbol: " + dlsym_error;
    _problem = _constructor();
    return _problem;
}

void ProblemLoader::close() {
    if (_problem) {
        _destructor(_problem);
        _problem = NULL;
    }
    if (_sharedLibrary) {
        dlclose(_sharedLibrary);
        _sharedLibrary = NULL;
    }
}

ProblemLoader::~ProblemLoader() {
    close();
}

Problem * ProblemLoader::getProblem() const {
    return _problem;
}


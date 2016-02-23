#include "ProblemLoader.hh"

ProblemLoader::ProblemLoader() 
: _sharedLibrary(NULL), _problem(NULL) {}

Problem *ProblemLoader::load(const std::string &libPath) {
    _sharedLibrary = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!_sharedLibrary) {
        std::cerr << "Cannot open lib " + libPath + ":" + dlerror() << std::endl;
        return NULL;
    }
    dlerror();
    _constructor = (create_t *)dlsym(_sharedLibrary, "create");
    const char * dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load create symbol: " + std::string(dlsym_error) << std::endl;
        return NULL;
    }
    _destructor = (destroy_t *)dlsym(_sharedLibrary, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load destroy symbol: " + std::string(dlsym_error) << std::endl;
        return NULL;
    }
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

Problem *ProblemLoader::getProblem() const {
    return _problem;
}


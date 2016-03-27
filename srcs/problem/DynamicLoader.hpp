#pragma once

#include <dlfcn.h>
#include <string>
#include <iostream>

template <class T>
class DynamicLoader {
public:

    /**
     * load a library into the libraryLoader
     * @param libPath, shared library path
     * @return the loaded problem. Throw an error if the function encounters an issue. 
     */
    T *load(const std::string &libPath) {
        _sharedLibrary = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!_sharedLibrary) {
            std::cerr << "Cannot open lib " + libPath + ":" + dlerror() << std::endl;
            return NULL;
        }
        dlerror();
        _constructor = (create_t *) dlsym(_sharedLibrary, "create");
        const char * dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load create symbol: " + std::string(dlsym_error) << std::endl;
            return NULL;
        }
        dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load destroy symbol: " + std::string(dlsym_error) << std::endl;
            return NULL;
        }
        _dynamicObject = _constructor();
        return _dynamicObject;
    }

    /**
     * CLose the current library and delete the current problem
     */
    void close() {
        if (_dynamicObject) {
            delete _dynamicObject;
            _dynamicObject = NULL;
        }
        if (_sharedLibrary) {
            dlclose(_sharedLibrary);
            _sharedLibrary = NULL;
        }
    }

    /**
     * get the current problem
     * @return the current problem or NULL if not problem is loaded
     */
    T *getDynamicObject() const {
        return _dynamicObject;
    }
private:
    typedef T* create_t();

    // pointer to a shared library entrance
    void *_sharedLibrary = NULL;
    // pointer to the current problem
    T *_dynamicObject = NULL;
    // Pointer to the Problem constructor
    create_t *_constructor = NULL;
};
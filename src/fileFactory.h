#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include "trace.h"

#include <memory>
#include <string>

namespace cas
{
    struct FileFactory
    {
        typedef std::auto_ptr<std::istream> reader_pointer_type;
        typedef std::auto_ptr<std::ostream> writer_pointer_type;
        
        static reader_pointer_type createFileReader(const std::string& path);
        static writer_pointer_type createFileWriter(const std::string& path);

    private:
        //no objects
        ~FileFactory();
    };
}

#endif //FILEFACTORY_H

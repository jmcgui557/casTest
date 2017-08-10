#include "fileFactory.h"

#include <fstream>

namespace cas
{
    FileFactory::reader_pointer_type FileFactory::createFileReader(const std::string& path)
    {
        return FileFactory::reader_pointer_type(new std::ifstream(path.c_str()));
    }
    
    FileFactory::writer_pointer_type FileFactory::createFileWriter(const std::string& path)
    {
        return FileFactory::writer_pointer_type(new std::ofstream(path.c_str()));
    }
}


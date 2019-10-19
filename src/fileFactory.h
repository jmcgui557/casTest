// The "Clean And Simple Test" (CAST) software framework, tools, and
// documentation are distributed under the terms of the MIT license a
// copy of which is included with this package (see the file "LICENSE"
// in the CAS poject tree's root directory).  CAST may be used for any
// purpose, including commercial purposes, at absolutely no cost. No
// paperwork, no royalties, no GNU-like "copyleft" restrictions, either.
// Just download it and use it.
// 
// Copyright (c) 2017 Randall Lee White

#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <memory>
#include <string>

namespace cas
{
    struct FileFactory
    {
        typedef std::unique_ptr<std::istream> reader_pointer_type;
        typedef std::unique_ptr<std::ostream> writer_pointer_type;
        
        static reader_pointer_type createFileReader(const std::string& path);
        static writer_pointer_type createFileWriter(const std::string& path);

    private:
        //no objects
        ~FileFactory();
    };
}

#endif //FILEFACTORY_H

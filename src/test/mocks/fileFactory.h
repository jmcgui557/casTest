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

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <sstream>

namespace cas
{
    struct FileFactory
    {
        typedef std::istringstream* reader_pointer_type;
        typedef std::ostringstream* writer_pointer_type;
        typedef std::map<std::string, reader_pointer_type> ReaderMap;
        typedef std::map<std::string, writer_pointer_type> WriterMap;
        
        //For production
        //typedef std::auto_ptr<std::istream> reader_pointer_type;
        //typedef std::auto_ptr<std::ostream> writer_pointer_type;
        
        static reader_pointer_type createFileReader(const std::string& path)
        {
            ReaderMap::iterator r(readers().find(path));

            if(r != readers().end())
                return (*r).second;

            reader_pointer_type reader(new std::istringstream());

            readers().insert(std::make_pair(path, reader));
            
            return reader;
        }

        static writer_pointer_type createFileWriter(const std::string& path)
        {
            WriterMap::iterator w(writers().find(path));

            if(w != writers().end())
                return (*w).second;

            writer_pointer_type writer(new std::ostringstream());

            writers().insert(std::make_pair(path, writer));
            
            return writer;
        }

        static std::string getOutput(const std::string& path)
        {
            WriterMap::const_iterator w(writers().find(path));

            if(w == writers().end())
                return "";

            return (*w).second->str();
        }

        static void deleteFileReader(const std::string& path)
        {
            ReaderMap::iterator r(readers().find(path));

            if(r == readers().end())
                return;

            reader_pointer_type reader((*r).second);

            readers().erase(r);
            
            delete reader;
        }
        
        static void deleteFileWriter(const std::string& path)
        {
            WriterMap::iterator w(writers().find(path));

            if(w == writers().end())
                return;

            writer_pointer_type writer((*w).second);

            writers().erase(w);
            
            delete writer;
        }
        
        static void setReadData(const std::string& dat)
        {
            data() = dat;
        }

        static std::string& data()
        {
            static std::string dat;
            return dat;
        }

        struct DeleteSecond
        {

            void operator()(ReaderMap::value_type pair)
            {
                delete pair.second;
            }
            
            void operator()(WriterMap::value_type pair)
            {
                delete pair.second;
            }
            
        private:
        };

        static void reset()
        {
            std::for_each(readers().begin(),
                          readers().end(),
                          DeleteSecond());

            readers().clear();
            
            std::for_each(writers().begin(),
                          writers().end(),
                          DeleteSecond());

            writers().clear();
        }
    private:
        static ReaderMap& readers()
        {
            static ReaderMap readerMap;
            return readerMap;
        }
        
        static WriterMap& writers()
        {
            static WriterMap writerMap;
            return writerMap;
        }
        
        //no objects
        ~FileFactory();
    };
}

#endif //FILEFACTORY_H

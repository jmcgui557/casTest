#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include "trace.h"

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
	    cas_print("writer: " << path);
	    WriterMap::iterator w(writers().find(path));

	    if(w != writers().end())
		return (*w).second;

	    writer_pointer_type writer(new std::ostringstream());

	    writers().insert(std::make_pair(path, writer));
	    
	    return writer;
	}

	static std::string getOutput(const std::string& path)
	{
	    cas_print("getOutput(): " << path);
	    
	    WriterMap::const_iterator w(writers().find(path));

	    if(w == writers().end())
		return "";

	    cas_print("\tstored: " << (*w).second->str());
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

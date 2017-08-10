#ifndef TSMAKEFILE_H
#define TSMAKEFILE_H

#include <iostream>
#include <string>

namespace cas
{
    struct TestSuiteMakefile
    {
	struct xRecipeNotFound{};
	
	TestSuiteMakefile()
	{};
	
	TestSuiteMakefile(std::istream& in)
	{}
	
	void addRecipe(const std::string& testSuiteName)
	{}
	
	const std::string& getRecipe(const std::string& targetName) const
	{
	    static std::string s;
	    return s;
	}
	
	void read(std::istream& in)
	{}
	
	void write(std::ostream& out) const
	{}
	
    private:
    };
}

#endif //TSMAKEFILE_H


#include "tsMakefile.h"

namespace cas
{
    TestSuiteMakefile::TestSuiteMakefile()
    {}

    TestSuiteMakefile::TestSuiteMakefile(std::istream& in)
    {
        read(in);
    }

    void TestSuiteMakefile::addRecipe(const std::string& testSuiteName)
    {
        std::string recipe("\t$(MAKE) -f ");
        recipe += testSuiteName;
        recipe += ".mak $@\n";
    
        updateRecipe("all", recipe);
        updateRecipe("%", recipe);
    }

    const std::string& TestSuiteMakefile::getRecipe(const std::string& targetName) const
    {
        RecipeMap::const_iterator r(recipes.find(targetName));
    
        if(recipes.end() == r)
            throw xRecipeNotFound();
    
        return (*r).second;
    }

    void TestSuiteMakefile::write(std::ostream& out) const
    {
        RecipeMap::const_reverse_iterator
            r(recipes.rbegin()),
            e(recipes.rend());
    
        while(r != e)
        {
            out << (*r).first << ":\n"
                << (*r).second << "\n";
        
            ++r;
        }
    }
    
    bool TestSuiteMakefile::isDuplicate(const std::string& newGoal,
                                        const std::string& currentGoal)
    {
        return std::string::npos != currentGoal.find(newGoal);
    }
    
    void TestSuiteMakefile::read(std::istream& in)
    {
        std::string l;
        while(std::getline(in, l))
        {
            if(std::string::npos != l.find("all:"))
                readRecipe("all", in);
            else if(std::string::npos != l.find("%"))
                readRecipe("%", in);
        }
    }
    
    void TestSuiteMakefile::readRecipe(const std::string& target,
                                       std::istream& in)
    {
        std::string l;
        while(std::getline(in, l))
        {
            if("" == l)
                break;
            
            if(std::string::npos != l.find("$(MAKE)"))
            {
                l += '\n';
                updateRecipe(target, l);
            }
        }
    }
        
    void TestSuiteMakefile::updateRecipe(const std::string& target,
                                         const std::string& recipe)
    {
        RecipeMap::iterator r(recipes.find(target));

        if(recipes.end() == r)
            recipes.insert(std::make_pair(target, recipe));
        else if(!isDuplicate(recipe, (*r).second))
            (*r).second += recipe;
    }
}

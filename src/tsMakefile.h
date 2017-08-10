#ifndef TSMAKEFILE_H
#define TSMAKEFILE_H

#include <exception>
#include <iostream>
#include <map>
#include <string>

namespace cas
{
    struct TestSuiteMakefile
    {
        struct xRecipeNotFound : std::exception{};
        
        TestSuiteMakefile();
        TestSuiteMakefile(std::istream& in);
        
        void addRecipe(const std::string& testSuiteName);
        const std::string& getRecipe(const std::string& targetName) const;
        
        void read(std::istream& in);
        void write(std::ostream& out) const;
        
    private:
        bool isDuplicate(const std::string& newGoal,
                         const std::string& currentGoal);
        
        void readRecipe(const std::string& target,
                        std::istream& in);
        
        void updateRecipe(const std::string& target,
                          const std::string& recipe);
        
        typedef std::map<std::string, std::string> RecipeMap;
        
        RecipeMap recipes;
    };
}

#endif //TSMAKEFILE_H


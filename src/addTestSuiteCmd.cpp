#include "addTestSuiteCmd.h"

#include "castUtil.h"
#include "cmdLine.h"
#include "fileFactory.h"

#include <fstream>

namespace cas
{
    AddTestSuiteCmd::AddTestSuiteCmd(const CmdLine& cmdLine)
        : CastCmd(cmdLine),
          castDir_(getCastDir()),
          testName_(),
          makefileName_(),
          templateName_(),
          makefile_()
    {
        if(2 > cmdLine.args.size())
            throw xCastCmd("Too few args for -addTestSuite command");

        if(castDir_.empty())
            throw xCastCmd("$CAST_DIR not defined");
        
        testName_ = cmdLine.args[1];
        makefileName_ = testName_ + ".mak";
        templateName_ = castDir_ + "/rules.make/testTemplate.mak";
    }
        
    bool AddTestSuiteCmd::exec()
    {
        if(!createMakeFile(castDir_))
            throw xCastCmd("Couldn't copy makefile template");
        
        createSource();
        
        return true;
    }
        
    bool AddTestSuiteCmd::createMakeFile(const std::string& castDir)
    { 
        FileFactory::reader_pointer_type mkTemplate(FileFactory::createFileReader(templateName_.c_str()));
        FileFactory::writer_pointer_type makefile(FileFactory::createFileWriter(makefileName_.c_str()));
        
        if(!createMakefileFromTemplate(*mkTemplate,
                                       *makefile,
                                       testName_))
            return false;
        
        return updateMainMakefile();
    }
        
    bool AddTestSuiteCmd::createSource()
    {
        std::string srcName(testName_);
        srcName += ".tpp";
        
        FileFactory::writer_pointer_type src(FileFactory::createFileWriter(srcName.c_str()));
        
        *src << "#include \"testCase.h\"\n\n"
             << "DEFINE_TEST(SanityTest)\n"
             << "void run()\n"
             << "{\n"
             << "    bool val(false);\n\n"
             << "    CK(true == val);\n"
             << "}\n"
             << "END_DEF\n\n"
             << std::endl;
        
        return true;
    }
    
    void AddTestSuiteCmd::readMakefile()
    {
        FileFactory::reader_pointer_type mkfile(FileFactory::createFileReader("Makefile"));
        
        makefile_.read(*mkfile);
    }
    
    bool AddTestSuiteCmd::updateMainMakefile()
    {
        readMakefile();
        makefile_.addRecipe(testName_);
        writeMakefile();
        
        return true;
    }
    
    void AddTestSuiteCmd::writeMakefile()
    {
        FileFactory::writer_pointer_type mkfile(FileFactory::createFileWriter("Makefile"));
        
        makefile_.write(*mkfile);
    }
} //namespace cas

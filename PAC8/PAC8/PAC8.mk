##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PAC8
ConfigurationName      :=Debug
WorkspacePath          :=/Users/ivan/Desktop/C/university/PAC8
ProjectPath            :=/Users/ivan/Desktop/C/university/PAC8/PAC8
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ivan  Marin 
Date                   :=20/04/2020
CodeLitePath           :="/Users/ivan/Library/Application Support/CodeLite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="PAC8.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/gj/mwjbqbh10zj7g1jr9sjlhych0000gn/T/AppTranslocation/E99203BA-9E25-419D-A801-99EC402D349B/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/source_fairgroundRide.c$(ObjectSuffix) $(IntermediateDirectory)/source_main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/source_fairgroundRide.c$(ObjectSuffix): source/fairgroundRide.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_fairgroundRide.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_fairgroundRide.c$(DependSuffix) -MM source/fairgroundRide.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/C/university/PAC8/PAC8/source/fairgroundRide.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_fairgroundRide.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_fairgroundRide.c$(PreprocessSuffix): source/fairgroundRide.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_fairgroundRide.c$(PreprocessSuffix) source/fairgroundRide.c

$(IntermediateDirectory)/source_main.c$(ObjectSuffix): source/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/source_main.c$(DependSuffix) -MM source/main.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/C/university/PAC8/PAC8/source/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_main.c$(PreprocessSuffix): source/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_main.c$(PreprocessSuffix) source/main.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



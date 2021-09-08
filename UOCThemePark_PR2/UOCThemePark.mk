##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=UOCThemePark
ConfigurationName      :=Release
WorkspacePath          :=/Users/ivan/Desktop/programacion/UOCThemePark_PR2
ProjectPath            :=/Users/ivan/Desktop/programacion/UOCThemePark_PR2
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ivan  Marin 
Date                   :=02/06/2020
CodeLitePath           :="/Users/ivan/Library/Application Support/CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
ObjectsFileList        :="UOCThemePark.txt"
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
CXX      := g++
CC       := gcc
CXXFLAGS :=  -Wno-unused-result -g -O2 -Wall $(Preprocessors)
CFLAGS   :=  -Wno-unused-result -g -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/gj/mwjbqbh10zj7g1jr9sjlhych0000gn/T/AppTranslocation/E99203BA-9E25-419D-A801-99EC402D349B/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_management.c$(ObjectSuffix) $(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IntermediateDirectory)/src_visitor.c$(ObjectSuffix) $(IntermediateDirectory)/src_queue.c$(ObjectSuffix) $(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IntermediateDirectory)/src_util.c$(ObjectSuffix) $(IntermediateDirectory)/src_fairgroundRide.c$(ObjectSuffix) $(IntermediateDirectory)/src_stack.c$(ObjectSuffix) $(IntermediateDirectory)/src_menu.c$(ObjectSuffix) \
	$(IntermediateDirectory)/src_iomenu.c$(ObjectSuffix) 



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
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM src/main.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/src_management.c$(ObjectSuffix): src/management.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_management.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_management.c$(DependSuffix) -MM src/management.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/management.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_management.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_management.c$(PreprocessSuffix): src/management.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_management.c$(PreprocessSuffix) src/management.c

$(IntermediateDirectory)/src_test.c$(ObjectSuffix): src/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_test.c$(DependSuffix) -MM src/test.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_test.c$(PreprocessSuffix): src/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_test.c$(PreprocessSuffix) src/test.c

$(IntermediateDirectory)/src_visitor.c$(ObjectSuffix): src/visitor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_visitor.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_visitor.c$(DependSuffix) -MM src/visitor.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/visitor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_visitor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_visitor.c$(PreprocessSuffix): src/visitor.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_visitor.c$(PreprocessSuffix) src/visitor.c

$(IntermediateDirectory)/src_queue.c$(ObjectSuffix): src/queue.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_queue.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_queue.c$(DependSuffix) -MM src/queue.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/queue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_queue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_queue.c$(PreprocessSuffix): src/queue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_queue.c$(PreprocessSuffix) src/queue.c

$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_api.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_api.c$(DependSuffix) -MM src/api.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix) src/api.c

$(IntermediateDirectory)/src_util.c$(ObjectSuffix): src/util.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_util.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_util.c$(DependSuffix) -MM src/util.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/util.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_util.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_util.c$(PreprocessSuffix): src/util.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_util.c$(PreprocessSuffix) src/util.c

$(IntermediateDirectory)/src_fairgroundRide.c$(ObjectSuffix): src/fairgroundRide.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_fairgroundRide.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_fairgroundRide.c$(DependSuffix) -MM src/fairgroundRide.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/fairgroundRide.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_fairgroundRide.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_fairgroundRide.c$(PreprocessSuffix): src/fairgroundRide.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_fairgroundRide.c$(PreprocessSuffix) src/fairgroundRide.c

$(IntermediateDirectory)/src_stack.c$(ObjectSuffix): src/stack.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_stack.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_stack.c$(DependSuffix) -MM src/stack.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/stack.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_stack.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_stack.c$(PreprocessSuffix): src/stack.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_stack.c$(PreprocessSuffix) src/stack.c

$(IntermediateDirectory)/src_menu.c$(ObjectSuffix): src/menu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_menu.c$(DependSuffix) -MM src/menu.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/menu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_menu.c$(PreprocessSuffix): src/menu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_menu.c$(PreprocessSuffix) src/menu.c

$(IntermediateDirectory)/src_iomenu.c$(ObjectSuffix): src/iomenu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_iomenu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_iomenu.c$(DependSuffix) -MM src/iomenu.c
	$(CC) $(SourceSwitch) "/Users/ivan/Desktop/programacion/UOCThemePark_PR2/src/iomenu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_iomenu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_iomenu.c$(PreprocessSuffix): src/iomenu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_iomenu.c$(PreprocessSuffix) src/iomenu.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/



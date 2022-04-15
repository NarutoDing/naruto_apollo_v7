class Logger:                                                                       
  BOLD='\033[1m'
  RED='\033[0;31m'
  GREEN='\033[32m'
  WHITE='\033[34m'
  YELLOW='\033[33m'
  ENDC = '\033[0m'                                                          
  @staticmethod                                                              
  def log_info(info):                                                      
    print(Logger.WHITE + Logger.BOLD + "[info]" + Logger.ENDC, info)                                                
  @staticmethod                                                              
  def log_error(info):                                                        
    print(Logger.RED + "[error]" + Logger.ENDC, info)
  @staticmethod
  def log_warning(info):                                                        
    print(Logger.YELLOW + "[warning]" + Logger.ENDC, info)
  @staticmethod
  def log_ok(info):                                                        
    print(Logger.GREEN + Logger.BOLD + "[ok]" + Logger.ENDC, info)
loger=Logger()

try:
    import os
    import sys
    import json
    import shutil
    import zipfile
    import argparse
    import traceback
    import subprocess

    from sys import platform
    from datetime import datetime
except Exception as err:
    print("\nError: Couldn't import few required libraries in buildHelper.py", err, "\nPlease use python3 from Main/Tool/python3.x.y QC8 project\n")
    sys.exit(1)

class BuildUtils:
    
    def __init__(self):
        self.m_CWD = ""
        self.m_HOST_OS = ""
        self.m_BUILD_TARGET_NAME = ""
        self.m_BUILD_OS_NAME = ""
        self.m_BUILD_TYPE = ""
        self.m_MAIN_DIR_PATH = ""
        self.m_BUILD_DIR_PATH = ""
        self.m_TOOLCHAIN_PATH = ""
        self.m_CMAKELIST_PATH = ""
        self.m_PYTHON_PATH = "" 
        self.m_CMAKE_BIN_PATH = "" 
        self.m_OPENVX_LIB_PATH = ""
        self.m_SMARTEYE_LIB_PATH = ""
        self.m_SCRIPT_DIR_PATH = ""
        self.m_SDP_PATH = ""
        self.m_OpenCV_PATH = ""
        self.m_PYTHON_PATH = ""
        self.m_REPOS_LIST = list()
        self.m_BUILD_CLEAN = False
        self.m_SYNC = ""
        self.m_ONLY_MAKE = False 
        self.m_REPO_RESET = False
        self.m_REPO_STATUS = False
        self.m_GRAPH_INPUT_TYPE = ""
        self.m_FORCE_ZIP = False
        self.m_TEST_SCOPE = ""
        self.m_TEST_CLEAN = False
        self.m_GTEST_ROOT_PATH = ""
        self.m_CURR_TEST_TARGET = ""
        self.m_TEST_BUILD_PATH = ""
        self.m_TEST_TARGET_PATH = ""
        self.m_TEST_TARGETS_DICT = dict()
        self.m_TEST_TARGETS_VALID = list()
        self.m_TEST_TARGETS_INPUT = list()
        self.m_TEST_TARGET_DEPENDENCIES_DICT = dict()
        self.m_pythonVersion = sys.version_info
        self.m_PROJECT = "" 
    def __del__(self):
        pass
            
    """
      Function to prinb build description
    """
    def printBuildDetails(self, type="BUILD"):
        print("\n#####################################################################\n")
        if type == "BUILD":
            loger.log_info("Current Build Description:")
            print("\n\t>> Detected Host OS :", self.m_HOST_OS.upper(), "\n")
            print("\t>> Build for :", self.m_BUILD_TARGET_NAME.upper(), "Platform \n")
            print("\t>> Build for OS:", self.m_BUILD_OS_NAME.upper(), "\n")
            print("\t>> Build Type:", self.m_BUILD_TYPE.upper(), "\n")
            print("\t>> Build Path:", self.m_BUILD_DIR_PATH, "\n")
            print("\t>> OpenVX Lib Path:", self.m_OPENVX_LIB_PATH, "reserved\n")
        if type == "TEST":
            print("Current Test Build Description:")
            print("\n\t>> Detected Host OS :", self.m_HOST_OS.upper(), "\n")
            print("\t>> Test Component:", self.m_CURR_TEST_TARGET.upper(), "\n")
            print("\t>> Test Build Path:", self.m_TEST_BUILD_PATH, "\n")
            print("\t>> GTest Tool Path:", self.m_GTEST_ROOT_PATH, "\n")
        print("\t>> Python Tool Path:", self.m_PYTHON_PATH, "\n")
        print("\t>> OpenCV Tool Path:", self.m_OpenCV_PATH, "\n")
        print("\t>> Cmake Tool Path:", self.m_CMAKE_BIN_PATH, "\n")
        print("\t>> Script Location:", self.m_SCRIPT_DIR_PATH, "\n")
        print("\n#####################################################################\n")
    
    
    """
      Function to valdate path
    """
    def checkPath(self, path):
        if not os.path.exists(path):
            print("\nError: Path Not Found -", path, "\n")
            return 1
        return 0
    """
      Function to update Main working directory and other requireds paths
    """
    def prepareWorkSpace(self, type="BUILD", scope="PROJECT"):
        self.m_CWD = os.getcwd()
        namespace = sys._getframe(1).f_globals 
        scriptPath = namespace['__file__']
        scriptDir = os.path.dirname(scriptPath)
        self.m_SCRIPT_DIR_PATH = os.path.abspath(scriptDir)
        self.m_PYTHON_PATH = os.path.abspath(os.environ["PYTHON_BIN_PATH"])
        self.m_CMAKE_BIN_PATH = os.path.abspath(os.environ["CMAKE_BIN_PATH"])
        self.m_OpenCV_PATH = os.path.abspath(os.environ["OpenCV_DIR"])
        
        if type == "BUILD":
            os.chdir(self.m_SCRIPT_DIR_PATH)
            self.m_MAIN_DIR_PATH = os.path.abspath(os.path.join(self.m_SCRIPT_DIR_PATH,".."))
        elif type == "TEST":
            self.m_TEST_SCOPE = scope
            utilityScriptPath = os.path.realpath(__file__)
            utilityScriptDir = os.path.dirname(utilityScriptPath)
            os.chdir(utilityScriptDir)
            self.m_MAIN_DIR_PATH = os.path.abspath(os.path.join(*["add here"]))
            if self.checkPath(self.m_MAIN_DIR_PATH):
                raise Exception("Please update build utlity script, to get proper Main directory path")
                self.m_GTEST_ROOT_PATH = os.path.abspath(os.environ['GTEST_ROOT'])
            os.chdir(self.m_SCRIPT_DIR_PATH)
        return 0
    """
      Function to create directory else if directory already exsits clears the directory
    """
    def createAndClearDirectory(self, newPath):
        try:
            if os.path.exists(newPath): 
                print("Given directory is already present ...")
                if not self.m_ONLY_MAKE: 
                  print("Cleaning the directory,", newPath)
                  print("\nCleaning ...", end="")
                  for root, subDirs, files in os.walk(newPath):
                      print(".", end="")
                      for file in files:
                          os.remove(os.path.join(root, file))
                      for dir in subDirs:
                          shutil.rmtree(os.path.join(root, dir))
                          print(".", end="")
                  print("\n")
            else:    
                os.makedirs(newPath)
            return newPath
        except Exception as err:
            print(err)
            raise Exception('\nWhile creating folder - ' + os.path.join(path, directory))

    """
      Function to parse json keys
    """
    def parseBuildInputJson(self, inputJsonDir):
      inputJsonPath = os.path.join(inputJsonDir, "inputConfig.json")
      if self.checkPath(inputJsonPath): 
            raise Exception('inputConfig.json file is missing in script folder. Please add inputConfig.json file.')
      fh = open(inputJsonPath, "r")
      jsonData = json.load(fh)
      return 0
    
    """
      Function to parse inputs
    """
    def parseAndValidateInputs(self):      
        self.parseBuildInputJson(self.m_SCRIPT_DIR_PATH)
        self.m_HOST_OS = platform.lower()
        if(self.m_HOST_OS == "win32"):
            self.m_HOST_OS = "windows"
    
        parser = argparse.ArgumentParser(description='Build System for Apollo Project')
        parser.add_argument('-p', '--platform_os',
                           type=str.lower,
                           default='host-linux',
                           choices=['host-linux', 'host-windows',  'nvidiahost-linux'],
                           metavar='',
                           help='Build Platform. Ex: host-linux(default), nvidia-linux, nvidiahost-linux',
                           required=False)
                           
        parser.add_argument('-b', '--build_type',
                           type=str.lower,
                           default='debug',
                           choices=['debug', 'release'],
                           metavar='',
                           help='Build Type - debug(default), release',
                           required=False)
                           
        parser.add_argument('-i', '--input_type',
                           type=str.lower,
                           default='camera',
                           choices=['camera', 'video'],
                           metavar='',
                           help='Input for LODZ and SE graphs',
                           required=False)

        parser.add_argument('-z', '--zip',
                           help='Option zip to do force zip for debug mode build',
                           action='store_true')
                           
        parser.add_argument('--sync',
                           help='Option sync to do git lfs pull on git repositories',
                           action='store_true')
                           
        parser.add_argument('--status',
                           help='Option status to do repo status on repo',
                           action='store_true')
                           
        parser.add_argument('--reset',
                           help='Option reset to do repo reset. Removes all local changes.',
                           action='store_true')
                           
        parser.add_argument('--clean',
                           help='Option clean to clear build directory',
                           action='store_true')
                           
        parser.add_argument('-m', '--make',
                           help='Option to just "make" without clearing build directory',
                           action='store_true')
       
        parser.add_argument('-v', '--version', 
                            action='version',
                            version='%(prog)s 1.0', help="Show program's version number and exit.")
                        
                           
        # Parse the argument
        args = parser.parse_args()
    
        self.m_BUILD_NAME = args.platform_os
        
        self.m_BUILD_CLEAN = args.clean
        
        self.m_SYNC = args.sync
        
        self.m_ONLY_MAKE = args.make
        
        self.m_REPO_RESET = args.reset
        
        self.m_REPO_STATUS = args.status    
                
        self.m_FORCE_ZIP = args.zip
                
        self.m_BUILD_TARGET_NAME = self.m_BUILD_NAME.split("-")[0]
        
        self.m_BUILD_OS_NAME = self.m_BUILD_NAME.split("-")[1]
        
        self.m_GRAPH_INPUT_TYPE = args.input_type

        os.environ['TARGET'] = self.m_BUILD_NAME.upper()
        

        if self.m_BUILD_TARGET_NAME == "nvidiahost":
            print(self.m_BUILD_OS_NAME)

        
        if self.m_BUILD_OS_NAME != "linux"  and self.m_BUILD_OS_NAME != "windows" and self.m_BUILD_OS_NAME != "nvidia" and self.m_BUILD_OS_NAME != "rtlinux":
            print("\nError: Invalid Arguments. Allowed os are only qnx for qc8 and linux, windows for host.\n")
            raise Exception('Invalid Arguments.')
        
        
        if self.m_BUILD_OS_NAME != self.m_HOST_OS and self.m_BUILD_TARGET_NAME == "host":
            print("\nError: Platform mismatch. Current System detected is \"", self.m_HOST_OS, "\". Trying to build for \"", self.m_BUILD_OS_NAME, "\" is not supported.\n")
            raise Exception('Invalid Arguments.')
    
        self.m_BUILD_TYPE = args.build_type
        
        if self.m_BUILD_TYPE != "release" and self.m_BUILD_TYPE != "debug":
            print("\nError: Invalid Arguments. Allowed Build Types are only Release and Debug.\n")
            raise Exception('Invalid Arguments.')
            
        if self.m_BUILD_TARGET_NAME == "nvidia":
            self.m_BUILD_OS_NAME = "Linux4Tegra"
            self.m_PYTHON_PATH = ""
            self.m_CMAKE_BIN_PATH = ""
        return 0
                
    """
      Function to execute linux command using subprocess library and get realtime outputs
    """
    def executeCommand(self, command, processWorkingDir):
        loger.log_info(command + processWorkingDir)
        process = subprocess.Popen(command, cwd=processWorkingDir, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True, executable="/bin/bash")
        print("\n##############################################################\n")
        while True:
            out = process.stdout.readline()
            if out == '' and process.poll() is not None:
                break
            if out:       
                print(out.strip())
        print("\n##############################################################\n")
        returncode = process.poll()
        return returncode
       
    def getGraphInput(self):
        return ""
        
    
    """
      Function to execute cmake and make
    """
    def buildFor(self, cmakeCommand, makeCommand, buildPath):
        if not self.m_ONLY_MAKE:
            print("\n\nExecuting CMake...........\n")
            if(self.executeCommand(cmakeCommand, buildPath)):
                raise Exception('CMake Error in - ' + buildPath)
   
        print("\n\nExecuting Make...........\n")
        if(self.executeCommand(makeCommand, buildPath)):
            raise Exception('Make Error in - ' + buildPath)
        return 0

        
        
  
    """
      Function to build for host-linux
    """
    def buildHostLinux(self):
        print("######################### Inside Host Build #########################")
        print("\n\n\nStarting Build\nBuilding.................\n")
        cmakeCmd = self.m_CMAKE_BIN_PATH  + " -DCMAKE_BUILD_TYPE=" + self.m_BUILD_TYPE.capitalize()  + " " + self.m_CMAKELIST_PATH
        makeCmd = "make -j4 "
        self.printBuildDetails()
        self.buildFor(cmakeCmd, makeCmd, self.m_BUILD_DIR_PATH)
        loger.log_ok("Build Success")
        return 0
           
    """
      Function to build for Nvidia
    """
    def buildNvidiaLinux(self):
        print("################## Inside Nvidia Linux Build ##################")
        print("\n\n\nStarting Build\nBuilding.................\n")
        print(self.m_CMAKE_BIN_PATH)
        print(os.path.exists(self.m_OPENVX_LIB_PATH))
        self.m_SMARTEYE_LIB_PATH = os.path.join(*[self.m_MAIN_DIR_PATH,"Platform","CPU", "Libraries","Third-Party","smart-eye-lib-nvidia-linux", "trackercore_armv8"])
        cmakeCmd = "cmake" + " -DOPENVX_PATH=" + self.m_OPENVX_LIB_PATH + " -DCMAKE_BUILD_TYPE=" + self.m_BUILD_TYPE.capitalize() + self.getGraphInput() + " " + self.m_CMAKELIST_PATH 
        makeCmd = "make -j4"
        self.printBuildDetails()
        self.buildFor(cmakeCmd, makeCmd, self.m_BUILD_DIR_PATH)
        print("\n\n######### Build Success ##########\n")
        return 0
  

    """
      Function to build for nvidiaHost
    """
    def buildNvidiaHostLinux(self):
        print("################## Inside nvidiaHost Build ##################")
        self.printBuildDetails()
        print("\n\n\nStarting Build\nBuilding.................\n")
        print(self.m_TOOLCHAIN_PATH)
        print(self.m_CMAKE_BIN_PATH)
        print(self.m_BUILD_TYPE.capitalize(),"\n")
        print((self.m_OPENVX_LIB_PATH),"\n")
        print(os.path.exists(self.m_OPENVX_LIB_PATH),"\n")
        self.m_SMARTEYE_LIB_PATH = os.path.join(*[self.m_MAIN_DIR_PATH,"Platform","CPU", "Libraries", "Third-Party", "smart-eye-lib-nvidia-linux", "trackercore_armv8"])
        
        Tools_Path = os.environ["TOOL_BASE_PATH"]
        CUDA_INCLUDE_DIRS = os.path.join(*[Tools_Path,"cuda-10.2","targets","aarch64-linux","include"])
        CUDA_CUDART_LIBRARY = os.path.join(*[Tools_Path,"cuda-10.2","targets","aarch64-linux","lib","libcudart.so"])
        TENSORRT_ROOT = os.path.join(*[Tools_Path,"TensorRT","usr"])
        TensorRT_INCLUDE_DIR = os.path.join(*[Tools_Path,"TensorRT","usr","include","aarch64-linux-gnu"])
        TensorRT_LIBRARY = os.path.join(*[Tools_Path,"TensorRT","usr","lib","aarch64-linux-gnu","libnvinfer.so"])

        cmakeCmd = self.m_CMAKE_BIN_PATH + " -DOPENVX_PATH="+ self.m_OPENVX_LIB_PATH + " -DCMAKE_BUILD_TYPE=" + self.m_BUILD_TYPE.capitalize() + self.getGraphInput() + " -DCMAKE_TOOLCHAIN_FILE=" + self.m_TOOLCHAIN_PATH + " " + self.m_CMAKELIST_PATH + " " + "-DCUDA_INCLUDE_DIRS=" + CUDA_INCLUDE_DIRS + " " + "-DCUDA_CUDART_LIBRARY=" + CUDA_CUDART_LIBRARY + " " + "-DTENSORRT_ROOT=" + TENSORRT_ROOT + " " + "-DTensorRT_INCLUDE_DIR=" + TensorRT_INCLUDE_DIR + " " + "-DTensorRT_LIBRARY=" + TensorRT_LIBRARY + " " + "-DLIBCXX_INSTALL_FILESYSTEM_LIBRARY=YES" + " "  + "-DCMAKE_CXX_STANDARD=17" + " " + "-DCMAKE_CXX_FLAGS=-O3" + " "
        makeCmd = "make -j4"
        self.printBuildDetails()
        self.buildFor(cmakeCmd, makeCmd, self.m_BUILD_DIR_PATH)
        print("\n\n######### Build Success ##########\n")
        return 0
    
    """
      Function to build the apollo project
    """
    def buildProject(self, CMAKELIST_PATH, BUILD_DIR_PATH, TOOLCHAIN_PATH=None):
        BUILD_DIR_PATH = os.path.abspath(self.createAndClearDirectory(os.path.join(*[BUILD_DIR_PATH,self.m_BUILD_NAME])))
        os.chdir(BUILD_DIR_PATH)
        self.m_BUILD_DIR_PATH = BUILD_DIR_PATH
        self.m_TOOLCHAIN_PATH = TOOLCHAIN_PATH
        self.m_CMAKELIST_PATH = CMAKELIST_PATH
        if self.m_HOST_OS == "linux":
            if self.m_BUILD_NAME == "host-linux":
                self.buildHostLinux()  
            elif self.m_BUILD_NAME == "nvidia-linux":
                self.buildNvidiaLinux()    
            elif self.m_BUILD_NAME == "nvidiahost-linux":
                self.buildNvidiaHostLinux()    
        elif self.m_HOST_OS == "windows":
            if self.m_BUILD_NAME == "host-windows":
                self.buildHostLinux()
            elif self.m_BUILD_NAME == "nvidia-linux":
                self.buildNvidiaLinux() 
            elif self.m_BUILD_NAME == "nvidiahost-linux":
                self.buildNvidiaHostLinux()
        self.copyFilesToBinForRun()      
                
        if (self.m_BUILD_TYPE == "release") or (self.m_FORCE_ZIP == True):
            now = datetime.now()
            dateNtime = now.strftime("%d_%m_%Y-%H_%M")
            releaseDirPath = os.path.abspath(os.path.join(*[".", self.m_BUILD_TYPE.capitalize()+"-"+self.m_BUILD_NAME+"-"+dateNtime]))
            print("\nCopying necessary files to Main/src/CPU/Build/" + self.m_BUILD_TYPE.capitalize()+"-"+self.m_BUILD_NAME+"-"+dateNtime +"\nCopying ..........\n")
            self.copyAndZipFilesForRelease(releaseDirPath)
    




    """
      Function to zip a folder
    """
    def zipTheFolder(self, folderToZip, whereToPlaceZip):
        try:
            zipHandle = zipfile.ZipFile(whereToPlaceZip+'.zip', 'w', zipfile.ZIP_DEFLATED)
            cwd = os.getcwd()
            os.chdir(os.path.join(folderToZip, ".."))
            print("\nZipping the folder", folderToZip, "\n")
            print("Zipping ...", end="")
            for root, dirs, files in os.walk(os.path.basename(os.path.normpath(folderToZip))):
                print(".", end="")
                for file in files:
                    zipHandle.write(os.path.join(root, file))
            print("\nFolder zipped into", whereToPlaceZip+'.zip\n')
            shutil.rmtree(folderToZip)
            os.chdir(cwd)#switching back to original directory
            print("#####################################################\n\n")
            return 0
        except Exception as err:
            print(err)
            raise Exception('\nWhile archiving folder - ' + folderToZip)
    
    
    
    
    """
      Function to copy required files for running app from bin
    """
    def copyFilesToBinForRun(self):
        binPath = os.path.abspath("bin")
        if (self.m_pythonVersion[0] == 3 and self.m_pythonVersion[1] > 8):
            if self.m_BUILD_TARGET_NAME.startswith("nvidia"):
                if os.path.exists(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-nvidia","lib"])):
                    shutil.copytree(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-nvidia","lib"]), os.path.join(binPath, "OpenCv"), copy_function=shutil.copy, dirs_exist_ok=True)
            elif self.m_BUILD_TARGET_NAME == "host":
                if os.path.exists(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-x86","lib"])):
                    shutil.copytree(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-x86","lib"]), os.path.join(binPath, "OpenCv"), copy_function=shutil.copy, dirs_exist_ok=True)
        else:
            if self.m_BUILD_TARGET_NAME.startswith("nvidia"):
                #create opencv folder      
                if os.path.exists(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-nvidia","lib"])):
                    if os.path.exists(os.path.join(binPath, "OpenCv")):
                        shutil.rmtree(os.path.join(binPath, "OpenCv"))
                    shutil.copytree(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-nvidia","lib"]), os.path.join(binPath, "OpenCv"), copy_function=shutil.copy)
            elif self.m_BUILD_TARGET_NAME == "host":
                #create opencv folder      
                if os.path.exists(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-x86","lib"])):
                    if os.path.exists(os.path.join(binPath, "OpenCv")):
                        shutil.rmtree(os.path.join(binPath, "OpenCv"))
                    shutil.copytree(os.path.join(*[os.environ['TOOL_BASE_PATH'],"OpenCv-4.5.3","install","linux-x86","lib"]), os.path.join(binPath, "OpenCv"), copy_function=shutil.copy)

        if self.m_PROJECT == "build":
            print("")

        releaseNotesFile = ""
        for path, dirs, files in os.walk(os.path.join(self.m_MAIN_DIR_PATH,"Doc")):
            for file in files:
                if "releasenotes" in file.lower():
                    releaseNotesFile = file
        if releaseNotesFile:
            shutil.copyfile(os.path.join(*[self.m_MAIN_DIR_PATH,"Doc",releaseNotesFile]), os.path.join(binPath, releaseNotesFile))
        else:
            print("") 

    """
      Function to copy required files for release
    """
    def copyAndZipFilesForRelease(self, RELEASE_DIR_PATH):
        releasePath = os.path.abspath(RELEASE_DIR_PATH)
        
        if (os.path.exists('bin')):
            shutil.copytree('bin', releasePath, copy_function=shutil.copy)
        else:
            raise Exception('Error: bin folder missing in build directory')
        
        releaseNotesFile = ""
        for path, dirs, files in os.walk(os.path.join(self.m_MAIN_DIR_PATH,"Doc")):
            for file in files:
                if "releasenotes" in file.lower():
                    releaseNotesFile = file
        if releaseNotesFile:
            shutil.copyfile(os.path.join(*[self.m_MAIN_DIR_PATH,"Doc",releaseNotesFile]), os.path.join(releasePath, releaseNotesFile))
        else: 
            print("\n\nError:RealeaseNotes is missing in Main/Doc folder.\n\n")
        shutil.copyfile(os.path.join(*[self.m_MAIN_DIR_PATH,"Doc","READ_ME.txt"]), os.path.join(releasePath, "READ_ME.txt"))
        os.chdir("..")
        zipPath = self.zipTheFolder(releasePath, os.path.join(*[self.m_MAIN_DIR_PATH,"..",os.path.basename(os.path.normpath(releasePath))]))
        return 0



    """
      Function to clean folder
    """
    def buildClean(self):
        folderPath = self.m_BUILD_DIR_PATH
        if(os.path.exists(folderPath)):
            if(os.path.isdir(folderPath)):
                print("cleaning Build Folder,", folderPath, ".......")
                shutil.rmtree(folderPath)
        else:
            print("Build Folder is already cleaned\n")

        folderPath = os.path.abspath(os.path.join(self.m_MAIN_DIR_PATH, ".."))
        print("\ncleaning Release folders in Workspace,", folderPath, ".......")
        for root, dirs, files in os.walk(folderPath):
            for file in files:
                file_ = file.lower()
                if (file_.startswith("release") or file_.startswith("debug")):
                    print(file)
                    os.remove(os.path.join(root, file))
        print("\n\tClean Success.\n")
        sys.exit(0)
        
    
    

    """
      Function to clean workspace folder
    """
    def cleanWorkSpace(self):
        folderPath = os.path.abspath(os.path.join(self.m_MAIN_DIR_PATH, ".."))
        print("\ncleaning Release Zip files in Workspace,", folderPath, ".......")
        for root, dirs, files in os.walk(folderPath):
            for file in files:
                file_ = file.lower()
                if ((file_.startswith("release") or file_.startswith("debug")) and file_.endswith(".zip")):
                    print(file)
                    os.remove(os.path.join(root, file))
        print("\n\n")
        return 0
        
        
    
    """
      Function for git lfs pull of a repo
    """
    def gitLfsPull(self, repoPath):
        print("\n\nChecking out mainline branch for ", os.path.basename(os.path.normpath(repoPath)), "\n")
        print("\nExecuting git lfs pull on ->\t", repoPath, "\n")
        if (self.executeCommand("git lfs pull", repoPath)):
                raise Exception('Git Lfs Pull Error - ' + os.path.basename(os.path.normpath(repoPath)))
        return 0
        
        
    
    """
      Function for git clone of a repo
    """
    def gitClone(self, repoLink, clonePath, dirName):
        print("\nExecuting git clone on ->\t", repoLink, "\n")
        if os.path.exists(os.path.abspath(dirName)):
            self.executeCommand("rm -rf " + dirName , clonePath)
        if (self.executeCommand("git clone \"" + repoLink + "\"", clonePath)):
            raise Exception('Git Clone Error - ' + repoLink)
        return 0
                
    
        
    """
      Function for syncing of a repo
    """
    def repoSync(self, ENABLE_REPO_SYNC=False):
        try:
            if (self.executeCommand("repo forall -c \"git lfs pull\"", os.path.join(self.m_MAIN_DIR_PATH, ".."))):
                    raise Exception("git lfs pull Error: Please check permissions and repo lfs config.")
        except Exception as err:
            print(err)

        for repo in self.m_REPOS_LIST: 
            self.gitLfsPull(repo)
        if ENABLE_REPO_SYNC == True:
            if (self.executeCommand("repo sync", os.path.join(self.m_MAIN_DIR_PATH, ".."))):
                raise Exception("Repo Sync error. Try --sync after doing a --reset.")
        sys.exit(0)
           
    
    
    """
      Function for reseting the repo - removes local changes and brings repo to mainline HEAD
    """
    def repoReset(self, branches):
        print("\nResetting the repo .........")
        for branch in branches:
            if (self.executeCommand("repo forall -c \"git reset --hard origin/" + branch + "\"", os.path.join(self.m_MAIN_DIR_PATH, ".."))):
                raise Exception('Repo Reset Error - ' + self.m_MAIN_DIR_PATH)
        sys.exit(0)
       
       
        
    """
      Function for reseting the repo - removes local changes and brings repo to mainline HEAD
    """
    def repoStatus(self):
        print("\nRepo Status ....")
        if (self.executeCommand("find . -name .git -execdir bash -c 'echo -en \"\033[1;31m\"repo: \"\033[1;34m\"; basename \"`git rev-parse --show-toplevel`\"; git status -s' \;", self.m_MAIN_DIR_PATH)):
            raise Exception('Repo Reset Error - ' + self.m_MAIN_DIR_PATH)
        sys.exit(0)
   
   
   
   
##############################Test########################################
   
   
    """
      Function to clean test folder
    """
    def testClean(self):
        if self.m_TEST_SCOPE == "COMPONENT":
            self.m_TEST_TARGET_PATH = self.m_SCRIPT_DIR_PATH
            self.m_TEST_BUILD_PATH = os.path.join(self.m_TEST_TARGET_PATH, "build_tests")
        print(self.m_TEST_BUILD_PATH)
        if(os.path.isdir(self.m_TEST_BUILD_PATH)):
            os.chdir(self.m_TEST_BUILD_PATH)
            if (self.executeCommand("make clean-all", self.m_TEST_BUILD_PATH)):
                raise Exception('Make Clean Error')
        print("Clean Success.")
        if self.m_TEST_SCOPE == "COMPONENT":
            sys.exit(0)
        return 0

   
    """
      Function to clean test folder
    """
    def testProjectClean(self):
        for i, TEST_TARGET_NAME in enumerate(self.m_TEST_TARGETS_VALID):
            print("\t",i+1,">", TEST_TARGET_NAME)
            print("\n#####################################################################\n")
            print("Cleaning Folders of Target ->\t" + TEST_TARGET_NAME)
            self.m_TEST_TARGET_PATH = self.m_TEST_TARGETS_DICT.get(TEST_TARGET_NAME)
            self.m_TEST_BUILD_PATH = os.path.join(self.m_TEST_TARGET_PATH, "build_tests")
            self.testClean()
            print("Project Clean Success.")
            sys.exit(0)
    
            
        
    """
      Function to parse json keys
    """
    def parseTestConfigJson(self, inputJsonDir):
        try:
            inputJsonPath = os.path.join(inputJsonDir, "inputTestConfig.json")
            if self.checkPath(inputJsonPath): 
                  raise Exception('inputTestConfig.json file is missing in script folder. Please add inputTestConfig.json file.')
            fh = open(inputJsonPath, "r")
            jsonData = json.load(fh)
            TEST_COMPONENTS = jsonData['TEST_COMPONENTS']
            for comp in TEST_COMPONENTS:
                testTarget = os.path.basename(os.path.normpath(comp))
                testTargetPath = os.path.join(*[os.path.abspath(comp), "Verification", "UnitTest"])
                self.m_TEST_TARGETS_DICT[testTarget] = testTargetPath
            self.m_TEST_TARGETS_VALID = [ele for ele in self.m_TEST_TARGETS_DICT.keys() if os.path.exists(self.m_TEST_TARGETS_DICT[ele])]
            return 0
        except Exception as err:
            print(err)
            raise Exception('\nWhile parsing test input json- ' + inputJsonPath) 
      
    """
      Function to build and testing, gtest and lcov (code coverage) commands are embedded in test component cmake file 
    """
    def buildAndTest(self):
        print("################## Inside Host Build and Test ##################")
        print("\n\n\nStarting Build and Test .................\n")   
        cmakeCmd = self.m_CMAKE_BIN_PATH + " .."
        makeCmd = "make -j4"
        self.printBuildDetails(type="TEST")
        self.buildFor(cmakeCmd, makeCmd, self.m_TEST_BUILD_PATH)
        print("\n\n######### Build and Test Success ##########\n")
        return 0
        
    """
      Function to copy test reports
    """
    def copyTestReoprtsForReview(self):
        print("copyTestReoprtsForReview==========================================")
        resultReportsPath = os.path.abspath(self.createAndClearDirectory(os.path.join(self.m_CWD, "test_reports")))
        reportsPath = os.path.abspath(self.createAndClearDirectory(os.path.join(resultReportsPath, self.m_CURR_TEST_TARGET+"_reports")))
        print("\nCopying Test Reports to Review Folder .....\n")
        if (self.m_pythonVersion[0] == 3 and self.m_pythonVersion[1] > 8):
            shutil.copytree(os.path.join(*[self.m_TEST_TARGET_PATH,"reports","unit_test_report"]), os.path.join(reportsPath,"unit_test_report"), copy_function = shutil.copy, dirs_exist_ok=True)
            shutil.copytree(os.path.join(*[self.m_TEST_TARGET_PATH,"reports","code_coverage_report"]), os.path.join(reportsPath,"code_coverage_report"), copy_function = shutil.copy, dirs_exist_ok=True)
        else:
            if os.path.exists(os.path.join(reportsPath,"unit_test_report")):
                shutil.rmtree(os.path.join(reportsPath,"unit_test_report"))
            shutil.copytree(os.path.join(*[self.m_TEST_TARGET_PATH,"reports","unit_test_report"]), os.path.join(reportsPath,"unit_test_report"), copy_function = shutil.copy)
            if os.path.exists(os.path.join(reportsPath,"code_coverage_report")):
                shutil.rmtree(os.path.join(reportsPath,"code_coverage_report"))
            shutil.copytree(os.path.join(*[self.m_TEST_TARGET_PATH,"reports","code_coverage_report"]), os.path.join(reportsPath,"code_coverage_report"), copy_function = shutil.copy)
        return 0 
        
        
        
    
    """
      Function to parse input json for dependencies
    """
    def getTestTargetDependenciesJson(self, inputJsonDir):
        try:
            print("\nGetting the test target dependecies ....\n")
            inputJsonPath = os.path.join(inputJsonDir, "inputTestConfig.json")
            if self.checkPath(inputJsonPath): 
                  raise Exception('inputTestConfig.json file is missing in script folder. Please add inputTestConfig.json file.')
            fh = open(inputJsonPath, "r")
            jsonData = json.load(fh)
            TARGET_DEPENDENCIES = jsonData['TARGET_DEPENDENCIES']
            for dependency, pathDict in TARGET_DEPENDENCIES.items(): 
                self.m_TEST_TARGET_DEPENDENCIES_DICT[dependency] = self.m_TEST_TARGET_DEPENDENCIES_DICT.get(dependency, {"REPO_LINK": "", "DIR_NAME": "", "PROJECT_LEVEL_PATH": ""})
                self.m_TEST_TARGET_DEPENDENCIES_DICT[dependency]["REPO_LINK"] = pathDict["REPO_LINK"]
                self.m_TEST_TARGET_DEPENDENCIES_DICT[dependency]["DIR_NAME"] = pathDict["DIR_NAME"]
                self.m_TEST_TARGET_DEPENDENCIES_DICT[dependency]["PROJECT_LEVEL_PATH"] = os.path.abspath(os.path.join(*[self.m_MAIN_DIR_PATH,"..",pathDict["PROJECT_LEVEL_PATH"]]))
            return 0
        except Exception as err:
            print(err)
            raise Exception('\nWhile parsing test input json for dependencies- ' + inputJsonPath)
    
    
    """
      Function to get depencies of test target and sync them
    """
    def syncTestTargetDependencies(self, clonePath):
        for dependency, pathDict in self.m_TEST_TARGET_DEPENDENCIES_DICT.items():
            self.gitClone(pathDict["REPO_LINK"], clonePath, pathDict["DIR_NAME"])
        return 0
    
    
    
    """
      Function for testing a target component
    """
    def testComponent(self, TEST_TARGET_PATH, TEST_BUILD_PATH, TEST_CMAKELIST_PATH):
        #creating build folder
        print("testComponent=============================================")
        self.m_TEST_TARGET_PATH = TEST_TARGET_PATH
        self.m_TEST_BUILD_PATH = os.path.abspath(self.createAndClearDirectory(TEST_BUILD_PATH))
        os.chdir(self.m_TEST_TARGET_PATH)
        self.getTestTargetDependenciesJson(self.m_TEST_TARGET_PATH)
        if self.m_TEST_SCOPE == "COMPONENT":
            self.syncTestTargetDependencies(self.m_TEST_TARGET_PATH)
            # set env variables
            for dependency, pathDict in self.m_TEST_TARGET_DEPENDENCIES_DICT.items():
                os.environ[dependency] = os.path.abspath(pathDict["DIR_NAME"])
        elif self.m_TEST_SCOPE == "PROJECT":
            # set env variables
            for dependency, pathDict in self.m_TEST_TARGET_DEPENDENCIES_DICT.items():
                os.environ[dependency] = os.path.abspath(pathDict["PROJECT_LEVEL_PATH"])
        os.chdir(self.m_TEST_BUILD_PATH)
        if TEST_CMAKELIST_PATH == None or TEST_CMAKELIST_PATH == "..":
            TEST_CMAKELIST_PATH = os.path.abspath("..")
        self.m_TEST_CMAKELIST_PATH = TEST_CMAKELIST_PATH
        #build and test
        self.buildAndTest()
        return 0

    
    
    
    """
      Function for testing multiple components
    """
    def testProject(self, TEST_BUILD_PATH=None, TEST_CMAKELIST_PATH=None):
        self.m_HOST_OS = platform.lower()
        if(self.m_HOST_OS == "win32"):
            self.m_HOST_OS = "windows"
        print("\n#####################################################################\n")
        print("\tConsidered targets under test are as below:")
        for i, testTragetName in enumerate(self.m_TEST_TARGETS_INPUT):
                print("\t",i+1,">", testTragetName)
        print("\n#####################################################################\n")

        if self.m_HOST_OS == "linux": 
            for TEST_TARGET_NAME in self.m_TEST_TARGETS_INPUT:
                self.m_CURR_TEST_TARGET = TEST_TARGET_NAME
                TEST_TARGET_PATH = self.m_TEST_TARGETS_DICT.get(testTragetName)
                if TEST_BUILD_PATH == None:
                    TEST_BUILD_PATH = os.path.join(TEST_TARGET_PATH, "build_tests")
                self.testComponent(TEST_TARGET_PATH, TEST_BUILD_PATH, TEST_CMAKELIST_PATH)
                #copy results to release folder for review
                self.copyTestReoprtsForReview()
        else: 
            raise Exception("Currently only tests on Linux OS is supported.")
        return 0
                

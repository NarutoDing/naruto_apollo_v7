#!../../../Main/Tools/python-3.9.5/bin python3


"""
    File name: apollo_build_script.py
    Author: dingjiangang
    Date created: 12/03/2022
    Python Version: 3.9.5
    Description: Script used to build for supported platforms, host, qc8, nvidia and so on

For reference, below is legacy shell comands used earlier to build the project.
#!/bin/bash
"""



import os
import sys
import traceback
toolsbasepath = os.environ["TOOL_BASE_PATH"]
os.environ["CC"] = "/usr/bin/gcc"
os.environ["CXX"] = "/usr/bin/g++"
buildutilspath = os.path.join(toolsbasepath, "ApolloBuildEnv")
sys.path.append(buildutilspath)
from buildUtils import BuildUtils

###############################################################################

if __name__ == "__main__":
    try:
        buildUtility = BuildUtils()
        buildUtility.prepareWorkSpace()
        buildUtility.parseAndValidateInputs()
        if buildUtility.m_BUILD_CLEAN:
            buildUtility.buildClean()
        if buildUtility.m_SYNC:
            buildUtility.repoSync()
        if buildUtility.m_REPO_RESET:
            buildUtility.repoReset()
        if buildUtility.m_REPO_STATUS:
            buildUtility.repoStatus()

        buildUtility.m_PROJECT = "apollo"

        TOOLCHAIN_PATH = ""
        if buildUtility.m_BUILD_TARGET_NAME == "nvidia":
            os.environ["TensorRT_LODZ"] = "TRUE"
        elif buildUtility.m_BUILD_TARGET_NAME == "nvidiahost":
            os.environ["TensorRT_LODZ"] = "TRUE"
            TOOLCHAIN_PATH = os.path.abspath("toolchain_nvidia_aarch64le.cmake")
            
        BUILD_DIR_PATH = os.path.abspath(buildUtility.createAndClearDirectory(os.path.join(*[buildUtility.m_MAIN_DIR_PATH,"build"])))
        os.path.abspath(buildUtility.createAndClearDirectory(os.path.join(*[buildUtility.m_MAIN_DIR_PATH,"build/"])))
        os.chdir(BUILD_DIR_PATH)
        CMAKELIST_PATH = os.path.abspath("..")
        print(TOOLCHAIN_PATH)
        buildUtility.buildProject(CMAKELIST_PATH, BUILD_DIR_PATH, TOOLCHAIN_PATH)
    except Exception as err:
        print("\nScript logged traceback:\n#### Start ####\n")
        print("\nError:", err,"\n\n")
        traceback.print_exception(*sys.exc_info())
        print("#### End ####\n")
        sys.exit(1)

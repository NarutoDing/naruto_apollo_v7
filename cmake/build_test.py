#!../../../Main/Tools/python-3.9.5/bin python3


"""
    File name: build_test.py
    Author: dingjiangang
    Date created: 2022
    Python Version: 3.9.5
    Description: Purpose of this script is to replace the current
                 shell script used to run the unit test

For reference, below is legacy shell comands used earlier to build the project.
#!/bin/bash


"""

import os
import sys
import traceback
toolsbasepath = os.environ["TOOL_BASE_PATH"]
buildutilspath = os.path.join(toolsbasepath, "BuildUtils")
sys.path.append(buildutilspath)
from buildUtils import BuildUtils




###############################################################################

if __name__ == "__main__":

    try:
        buildUtility = BuildUtils()
        buildUtility.prepareWorkSpace(type="TEST")
        buildUtility.parseAndValidateTestInputs()
        if buildUtility.m_TEST_CLEAN:
            buildUtility.testProjectClean()
        buildUtility.testProject()
    except Exception as err:
        print("\n\n\nScript logged traceback:\n#### Start ####\n")
        print("\nError:", err,"\n\n")
        traceback.print_exception(*sys.exc_info())
        print("#### End ####\n")
        sys.exit(1)

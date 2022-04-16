#!../../../Main/Tools/python-3.9.5/bin python3
"""
    File name: create_proto_cmakelist.py
    Author: dingjiangang
    Date created: 12/03/2022
    Python Version: 3.9.5
    Description: Script used to build for supported platforms, host, qc8, nvidia and so on

For reference, below is legacy shell comands used earlier to build the project.
#!/bin/bash
"""


import os
import sys
import re
from pathlib import Path
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

class NarutoApolloCreateCmakelist:
  def __init__(self):
    self.m_hello = "show create cmakelist test"
  def __del__(self):
    pass
  def Hello(self):
    print(self.m_hello)
  def GetNarutoApolloRootPath(self):
    current_script_path = os.path.abspath(sys.argv[0])
    naruto_apollo_root_path = os.path.abspath(os.path.join(current_script_path, '../../../'))
    return naruto_apollo_root_path
  def CreateCmakelist(self, modules_name):
    naruto_apollo_root_path = self.GetNarutoApolloRootPath()
    for root, dirs, files in os.walk(naruto_apollo_root_path, topdown=True):
      for dir in dirs:
        sub_dir = os.path.join(root,dir)
        match_condition_1 = re.search("/naruto_apollo_v7"+ "/"+ modules_name ,sub_dir)
        #match_condition_2 = re.search("proto",sub_dir)
        proto_match_index = sub_dir.find('proto')
        proto_str = sub_dir[proto_match_index:]
        match_condition_3 = re.search("proto_bundle",sub_dir)
        match_condition_4 = re.search("protocol",sub_dir)
        match_condition_5 = re.search("proto_adapter",sub_dir)
        macht_condition_6 = os.path.exists(sub_dir+'/'+'BUILD')
        macht_condition_7 = os.path.exists(sub_dir+'/'+'BUILD_')
        if modules_name == 'cyber':
          if match_condition_1 and (proto_str != 'proto') and (not match_condition_3) and (not match_condition_4) and (not match_condition_5) \
             and (macht_condition_6 or macht_condition_7):
            module_unit_path = os.path.join(root,dir)
            #print(module_unit_path)
            self.WriteCmakelistInfo(module_unit_path, modules_name)
        if modules_name == 'modules':
          if (match_condition_1 or match_condition_4) and (proto_str != 'proto') and (not match_condition_3)  and (not match_condition_5) \
             and (macht_condition_6 or macht_condition_7):
            module_unit_path = os.path.join(root,dir)
            if module_unit_path.find('proto/math') != -1:
              #print(module_unit_path)
              continue
            #print(module_unit_path)
            self.WriteCmakelistInfo(module_unit_path, modules_name)
  def GetProjectName(self, path, modules_name):
    str_lit = []
    str_lit = path.split('/')
    rest_str_list = str_lit.copy()
    project_name = ""
    for (i,v) in enumerate(str_lit):
      if v == modules_name:
        break
      rest_str_list.remove(v)
    rest_str_list_size = len(rest_str_list)
    for (j,k) in enumerate(rest_str_list):
      project_name += k
      if j == rest_str_list_size - 1:
        break
      project_name += '_'
    return project_name
  def GetAliasName(self, path, library_name):
    library_name_space = ''
    cc_string = 'cc_'
    middle_path_list = path.split('naruto_apollo_v7')
    pre_lib_path_list = middle_path_list[1].split('/')
    for (i,v) in enumerate(pre_lib_path_list):
      if i >= 1:
        library_name_space += v
        library_name_space += '::'
    library_name_space += library_name
    return library_name_space
  def WriteCmakelistInfo(self, path, modules_name):
    GetApolloCompileContent = []
    middle_path = path.split('naruto_apollo_v7')
    del middle_path[0]
    cmakelist_path = path + "/" + "CMakeLists.txt"
    project_name = self.GetProjectName(path, modules_name)
    #ok now we get every cmakelist compile content
    get_apollo_compile_shared_lib_content = self.GetApolloCompileContent(path, modules_name, 'cc_library')
    get_apollo_compile_binary_content = self.GetApolloCompileContent(path, modules_name, 'cc_binary')
    get_apollo_compile_cuda_lib_content = self.GetApolloCompileContent(path, modules_name, 'cuda_library')
    #print(get_apollo_compile_cuda_lib_content)
    #print(get_apollo_compile_binary_content)
    name_space = ''
    gobal_header = ''
    cuda_srcs_deps_list = []
    with open(cmakelist_path,'w+') as f:
      f.write('cmake_minimum_required(VERSION 3.16)') 
      f.write('\n')
      cmakelist_project_name = 'project' + '(' + project_name + ')'
      f.write('\n')
      f.write(cmakelist_project_name)
      f.write('\n')
      f.write('message'+'(' + "\"" + '${Green}' + ' [info] ' + project_name + ' cmakelist ' + '${ColourReset}' + "\"" + ')')
      f.write('\n')
      f.write('\n')
      global_virtual_cc = 'set(' + 'virtual_cc' + '  ' + '$ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)'
      for (i,v) in enumerate(get_apollo_compile_shared_lib_content):
        have_cc_file_flag = False
        #info if srcs list is no .cc file
        srcs_name_list = v[1]['srcs']
        for(src_name_index, src_name_value) in enumerate(srcs_name_list):
          if src_name_value.find('.cc') != -1:
            have_cc_file_flag = True
        if have_cc_file_flag == False:
          f.write('set(' + 'virtual_cc' + '  ' + '$ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)')
          f.write('\n')
        if len(v[1]['srcs']) != 0:
          if v[1]['srcs'][0] == '*.cc':
            #print(cmakelist_path)
            f.write('file(GLOB all_srcs ./*.cc)')
            f.write('\n')
        library_name = v[0]['name'][0]
        add_library_name = project_name + '_' + library_name
        if (len(v[1]['srcs']) == 0) and (len(v[2]['hdrs']) == 0):
          gobal_header = add_library_name + '_header'
          #f.write('set(' + 'virtual_cc' + '  ' + '$ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)')
          #f.write('\n')
        f.write("add_library(" + add_library_name + '  SHARED')
        f.write('\n')
        srcs_name = v[1]['srcs']
        for (j,c) in enumerate(srcs_name):
          #if c == ' ':
              #print(j,c)
              #c = '${virtual_cc}'
          #print(j,c)
          #if c.find(':') != -1:
          if c.find(':') != -1:
            #f.write('  ' + '${all_srcs}')
            #f.write('\n')
            #print(cuda_srcs_deps_list)
            cuda_srcs_deps_list.append(c)
          elif (c == '*.cc') and (c.find(':') == -1):
            f.write('  ' + '${all_srcs}')
            f.write('\n')
          elif c.find(':') == -1:
            f.write('  ' + c)
            f.write('\n')
        if have_cc_file_flag == False:
            f.write('  ' + '${' + 'virtual_cc' + '}')
            f.write('\n') 
        #print(cuda_srcs_deps_list)
        hdrs_name = v[2]['hdrs']
        
        for (m,n) in enumerate(hdrs_name):
          if len(srcs_name) == 0:
            f.write('  ' + n)
            f.write('\n')
        #if (len(srcs_name) == 0) and (len(hdrs_name) == 0):
          #f.write('  ' + '${' + 'virtual_cc' + '}')
          #f.write('\n')
        f.write(')')
        f.write('\n')
        f.write('set_target_properties(' + add_library_name + '  PROPERTIES LINKER_LANGUAGE CXX)')
        f.write('\n')
        deps_name = v[3]['deps']
        #print(deps_name)
        if deps_name != []:
          f.write('target_link_libraries(' + add_library_name)
          f.write('\n')
          for (m,n) in enumerate(deps_name):
            f.write('  ' + n)
            f.write('\n')
          for (cuda_index, cuda_value) in enumerate(cuda_srcs_deps_list):
            f.write('  ' + cuda_value[1:])
            f.write('\n')
          f.write(')')
        f.write('\n')
        library_name_space = self.GetAliasName(path, library_name)
        f.write('add_library(' + library_name_space +  '  ALIAS  ' + ' ' +  add_library_name + ')')
        f.write('\n')
        f.write('\n')
        cuda_srcs_deps_list = []
      for (s,h) in enumerate(get_apollo_compile_binary_content):
        #print(get_apollo_compile_binary_content)
        binary_name = h[0]['name'][0]
        match_so_index = binary_name.find('.so')
        if match_so_index != -1:
          golbal_header_name = project_name + '_' + binary_name[0:match_so_index]
          golbal_header = 'virtual_cc'
        else:
          golbal_header_name = project_name + '_' + binary_name
          golbal_header = 'virtual_cc'
        if (len(h[1]['srcs']) == 0) and (len(h[2]['hdrs']) == 0):
          #f.write("file(GLOB" + ' ' + golbal_header_name + '_header' + ' ' + './*.h)')
          f.write('set(' + 'virtual_cc' + '  ' + '$ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)')
          f.write('\n')
        if match_so_index != -1:
          add_library_name = binary_name[0:match_so_index]
          f.write("add_library(" + add_library_name + '  SHARED')
          f.write('\n')
          srcs_name = h[1]['srcs']
          for (z,u) in enumerate(srcs_name):
            f.write('  ' + u)
            f.write('\n')
          hdrs_name = h[2]['hdrs']
          for (q,w) in enumerate(hdrs_name):
            if len(srcs_name) == 0:
              f.write('  ' + w)
              f.write('\n')
          if (len(srcs_name) == 0) and (len(hdrs_name) == 0):
            f.write('  ' + '${' + golbal_header + '}')
            f.write('\n')
          f.write(')')
          f.write('\n')
          f.write('set_target_properties(' + add_library_name + '  PROPERTIES LINKER_LANGUAGE CXX)')
          f.write('\n')
          deps_name = h[3]['deps']
          if deps_name != []:
            f.write('target_link_libraries(' + add_library_name)
            f.write('\n')
            for (m,n) in enumerate(deps_name):
              f.write('  ' + n)
              f.write('\n')
            f.write(')')
          f.write('\n')
        else:
          add_binary_name = binary_name
          f.write("add_executable(" + add_binary_name)
          f.write('\n')
          srcs_name = h[1]['srcs']
          for (z,u) in enumerate(srcs_name):
            if u.find(':') != -1:
              u = ''
            f.write('  ' + u)
            f.write('\n')
          hdrs_name = h[2]['hdrs']
          for (q,w) in enumerate(hdrs_name):
            if len(srcs_name) == 0:
              f.write('  ' + w)
              f.write('\n')
          if (len(srcs_name) == 0) and (len(hdrs_name) == 0):
            f.write('  ' + '${' + golbal_header + '}')
            f.write('\n')
          f.write(')')
          f.write('\n')
          deps_name = h[3]['deps']
          if deps_name != []:
            f.write('target_link_libraries(' + add_binary_name)
            f.write('\n')
            for (m,n) in enumerate(deps_name):
              f.write('  ' + n)
              f.write('\n')
            f.write(')')
          f.write('\n')
      #print(cuda_srcs_deps_list)
      for (index,value) in enumerate(get_apollo_compile_cuda_lib_content):
        cuda_library_name = value[0]['name'][0]
        add_cuda_library_name = project_name + '_' + cuda_library_name
        f.write("cuda_add_library(" + add_cuda_library_name)
        f.write('\n')
        cuda_srcs_name = value[1]['srcs']
        for (j1,c1) in enumerate(cuda_srcs_name):
          #print(j1,c1)
          f.write('  ' + c1)
          f.write('\n')
        f.write(')')
        f.write('\n')
        f.write('set_target_properties(' + add_cuda_library_name + '  PROPERTIES LINKER_LANGUAGE CXX)')
        f.write('\n')
        deps_name = value[3]['deps']
        if deps_name != []:
          f.write('target_link_libraries(' + add_cuda_library_name)
          f.write('\n')
          for (m1,n1) in enumerate(deps_name):
            f.write('  ' + n1)
            f.write('\n')
          f.write(')')
        f.write('\n')
        cuda_library_name_space = self.GetAliasName(path, cuda_library_name)
        f.write('add_library(' + cuda_library_name_space +  '  ALIAS  ' + ' ' +  add_cuda_library_name + ')')
        f.write('\n')
        f.write('\n')
  def GetLibraryNameSpace(self, path, modules_name):
    str_lit = []
    str_lit = path.split('/')
    rest_str_list = str_lit.copy()
    library_name_space = ""
    for (i,v) in enumerate(str_lit):
      if v == modules_name:
        break
      rest_str_list.remove(v)
    rest_str_list_size = len(rest_str_list)
    for (j,k) in enumerate(rest_str_list):
      library_name_space += k
      if j == rest_str_list_size - 1:
        break
      library_name_space += '::'
    library_name_space += '::' 
    return library_name_space
  def GetOtherLibraryNameSpace(self, library_depend):
    library_name_space = ''
    library_name_space_unit_list = library_depend.split('/')
    library_name_space_unit_list_copy = library_name_space_unit_list.copy()
    for (i,v) in enumerate(library_name_space_unit_list):
      if v == '':
        library_name_space_unit_list_copy.remove(v)
    library_name_space_unit_list_copy_size = len(library_name_space_unit_list_copy)
    match_index = library_name_space_unit_list_copy[-1].find(':')
    last_space = ''
    #print(library_name_space_unit_list_copy[-1])
    if match_index != -1:
      if library_name_space_unit_list_copy[-1].find('third_party:libtorch') != -1:
        last_space = '${' + library_name_space_unit_list_copy[-1][match_index+1:] + '}'
      else:
        last_space = library_name_space_unit_list_copy[-1][0:match_index] + ':' + library_name_space_unit_list_copy[-1][match_index:]
    else:
      last_space = library_name_space_unit_list_copy[-1] + '::' + library_name_space_unit_list_copy[-1]
    for (j,k) in enumerate(library_name_space_unit_list_copy):
      if j == library_name_space_unit_list_copy_size - 1:
        break
      library_name_space += k
      library_name_space += '::'
    library_name_space += last_space
    return library_name_space
  def GetLibraryDepends(self, library_value, path, modules_name):
    library_depend_name_space = ''
    library_name_space = self.GetLibraryNameSpace(path, modules_name)
    if library_value.find(':') == 0:
      library_depend_name_space = library_name_space + library_value[1:]
      #print(path, "  ", modules_name, "  ", library_value, " ", library_depend_name_space)
    if library_value.find('//') == 0:
      library_depend_name_space = self.GetOtherLibraryNameSpace(library_value)
    #here is to use thirdparty platforms//cpu:x86_64
    
    if library_value.find('@') == 0:
      if library_value.find('glog') != -1:
        library_depend_name_space = '$' + '{' + 'glog_LIBRARIES' + '}'
      if library_value.find('protobuf') != -1:
        library_depend_name_space = '$' + '{' + 'Protobuf_LIBRARIES' + '}' 
      if library_value.find('gflags') != -1:
        library_depend_name_space = '$' + '{' + 'gflags_LIBRARIES' + '}'
      if library_value.find('python_lib') != -1:
        library_depend_name_space = '$' + '{' + 'python_lib' + '}' 
      if library_value.find('uuid') != -1:
        library_depend_name_space = '-luuid'
      if library_value.find('fftw3') != -1:
        library_depend_name_space = '$' + '{' + 'fftw3' + '}'
      if library_value.find('yaml-cpp') != -1:
        library_depend_name_space = '$' + '{' + 'yaml' + '}'
      if library_value.find('eigen') != -1:
        library_depend_name_space = '$' + '{' + 'eigen' + '}'  
      if library_value.find('boost') != -1:
        library_depend_name_space = '$' + '{' + 'boost' + '}'
      if library_value.find('com_google_absl') != -1:
        library_depend_name_space = '$' + '{' + 'absl' + '}'
      if library_value.find('sqlite3') != -1:
        library_depend_name_space = '$' + '{' + 'sqlite3' + '}' 
      if library_value.find('com_github_nlohmann_json') != -1:
        library_depend_name_space = '$' + '{' + 'json' + '}' 
      if library_value.find('civetweb') != -1:
        library_depend_name_space = '$' + '{' + 'civetweb' + '}' 
      if library_value.find('opencv') != -1:
        library_depend_name_space = '$' + '{' + 'opencv' + '}'
      if library_value.find('pcl') != -1:
        library_depend_name_space = '$' + '{' + 'pcl' + '}' 
      if library_value.find('ffmpeg') != -1:
        library_depend_name_space = '$' + '{' + 'ffmpeg' + '}'
      if library_value.find('proj') != -1:
        library_depend_name_space = '$' + '{' + 'proj' + '}'	   
      if library_value.find('@fastrtps') != -1:
        library_depend_name_space = '$' + '{' + 'fastrtps_LIB_DIR' + '}' + '/libfastrtps.so'
      if library_value.find('@fastcdr') != -1:
        library_depend_name_space = '$' + '{' + 'fastcdr_LIB_DIR' + '}' + '/libfastcdr.so' 
      if library_value.find('portaudio') != -1:
        library_depend_name_space = '$' + '{' + 'portaudio' + '}' 
      if library_value.find('tinyxml2') != -1:
        library_depend_name_space = '$' + '{' + 'tinyxml2' + '}'  
      if library_value.find('local_config_cuda') != -1:
        library_depend_name_space = '$' + '{' + 'cuda' + '}'
      if library_value.find('com_github_grpc_grpc') != -1:
        library_depend_name_space = '$' + '{' + 'grpc' + '}'
      if library_value.find('npp') != -1:
        library_depend_name_space = '$' + '{' + 'npp' + '}'
      if library_value.find('caffe') != -1:
        library_depend_name_space = '$' + '{' + 'caffe' + '}'
      if library_value.find('tensorrt') != -1:
        library_depend_name_space = '$' + '{' + 'tensorrt' + '}'
      if library_value.find('vtk') != -1:
        library_depend_name_space = '$' + '{' + 'vtk' + '}'
      if library_value.find('cblas') != -1:
        library_depend_name_space = '$' + '{' + 'cblas' + '}'
      if library_value.find('ipopt') != -1:
        library_depend_name_space = '$' + '{' + 'ipopt' + '}'
      if library_value.find('adolc') != -1:
        library_depend_name_space = '$' + '{' + 'adolc' + '}'
      if library_value.find('osqp') != -1:
        library_depend_name_space = '$' + '{' + 'osqp' + '}'
      if library_value.find('ad_rss') != -1:
        library_depend_name_space = '$' + '{' + 'ad_rss' + '}'
      if library_value.find('ncurses5') != -1:
        library_depend_name_space = '$' + '{' + 'CURSES_LIBRARIES' + '}'
    if library_depend_name_space == "third_party::tf2::tf2":
      library_depend_name_space = "${tf2}"
    return library_depend_name_space

    
  def GetMapContent(self, content, head, path, modules_name):
    map_unit = dict()
    if head == 'name':
      name_value_list = []
      content_list = content.split('"')
      name_value_list.append(content_list[1])
      map_unit[head] = name_value_list
      return map_unit
    elif head == 'srcs':
      srcs_value_list = []
      content_list = content.split('"')
      for (i,v) in enumerate(content_list):
        #print(i,v)
        if (v.rfind('cc') != -1) or (v.rfind('.cu') != -1)  or (v.rfind(':') != -1):
          srcs_value_list.append(v)
      map_unit[head] = srcs_value_list
      return map_unit
    elif head == 'hdrs':
      hdrs_value_list = []
      hrds_content_list = content.split('"')
      for (i,v) in enumerate(hrds_content_list):
        if v.rfind('.h') != -1:
          sym_index = v.find(':')
          if sym_index != -1:
            hdrs_value_list.append(v[sym_index+1:])
          else:
            hdrs_value_list.append(v)
      map_unit[head] = hdrs_value_list
      return map_unit
    elif head == 'deps':
      deps_value_list = []
      content_list = content.split('"')
      content_list_copy = content_list.copy()
      for (i,v) in enumerate(content_list):
        if v == '':
          content_list_copy.remove(v)
        if v == 'deps = [':
          content_list_copy.remove(v)
        if v.find('visibility') != -1:
          content_list_copy.remove(v)
      for (m,n) in enumerate(content_list_copy):
        #print(m,n)
        library_value = self.GetLibraryDepends(n, path, modules_name) 
        #print(library_value)
        deps_value_list.append(library_value)
      deps_value_list_copy = deps_value_list.copy()
      deps_value_list = list(set(deps_value_list))
      deps_value_list.sort(key=deps_value_list_copy.index)
      #rint(deps_value_list)
      map_unit[head] = deps_value_list
      return map_unit
  def ProcessCompileUnitContent(self, compile_unit_list, path, modules_name):
    #key word have name srcs hdrs deps //  cc_library cc_binary
    collect_info_list = []
    name_unit_map = dict()
    srcs_unit_map = dict()
    hdrs_unit_map = dict()
    deps_unit_map = dict()
    name_content = ''
    srcs_content = ''
    hdrs_content = ''
    deps_content = ''
    for (i,v) in enumerate(compile_unit_list):
      collect_unit_info_list = []
      if v.find('glob(') != -1:
        compile_unit = v
      else:
        compile_unit = re.findall(r'[(](.*?)[)]', v)[0]
      name_position_index = compile_unit.find('name')
      srcs_position_index = compile_unit.find('srcs')
      hdrs_position_index = compile_unit.find('hdrs')
      deps_position_index = compile_unit.find('deps')
      if srcs_position_index != -1:
        name_content = compile_unit[name_position_index:srcs_position_index]
      elif (srcs_position_index == -1) and (hdrs_position_index != -1):
        name_content = compile_unit[name_position_index:hdrs_position_index]
      elif (srcs_position_index == -1) and (hdrs_position_index == -1) and (deps_position_index != -1):
        name_content = compile_unit[name_position_index:deps_position_index]
      name_visibility_option = name_content.find('visibility')
      name_linkstatic_option = name_content.find('linkstatic')
      name_testonly_option = name_content.find('testonly')
      if name_visibility_option != -1:
        name_content = name_content[0:name_visibility_option]
      if name_linkstatic_option != -1:
        name_content = name_content[0:name_linkstatic_option]
      if name_testonly_option != -1:
        name_content = name_content[0:name_testonly_option]
      if srcs_position_index == -1:
        srcs_content = ''
      elif hdrs_position_index != -1:
        srcs_content = compile_unit[srcs_position_index:hdrs_position_index]
      elif deps_position_index != -1:
        srcs_content = compile_unit[srcs_position_index:deps_position_index]
      else:
        srcs_content = compile_unit[srcs_position_index:-1]
      src_select_option = srcs_content.find('select(')
      if src_select_option != -1:
        srcs_content = ''
      #print(srcs_content, srcs_position_index, hdrs_position_index)
      if hdrs_position_index == -1:
        hdrs_content = ''
      elif deps_position_index != -1:
        hdrs_content = compile_unit[hdrs_position_index:deps_position_index]
      else:
        hdrs_content = compile_unit[hdrs_position_index:-1]
      hdrs_linkopts_option = hdrs_content.find('linkopts')
      hdrs_copts_option = hdrs_content.find('copts')
      hdrs_data_option = hdrs_content.find('data')
      hdrs_visibility_option = hdrs_content.find('visibility')
      if hdrs_linkopts_option != -1:
        hdrs_content = hdrs_content[0:hdrs_linkopts_option]
      if hdrs_copts_option != -1:
        hdrs_content = hdrs_content[0:hdrs_copts_option]
      if hdrs_data_option != -1:
        hdrs_content = hdrs_content[0:hdrs_data_option]
      if hdrs_visibility_option != -1:
        hdrs_content = hdrs_content[0:hdrs_visibility_option]
      
      if deps_position_index == -1:
        deps_content = ''
      else:
        deps_content = compile_unit[deps_position_index:-1]
      #print(name_content, srcs_content, hdrs_content, deps_content)
      name_unit_map = self.GetMapContent(name_content, 'name', path, modules_name)
      srcs_unit_map = self.GetMapContent(srcs_content, 'srcs', path, modules_name)
      hdrs_unit_map = self.GetMapContent(hdrs_content, 'hdrs', path, modules_name)
      deps_unit_map = self.GetMapContent(deps_content, 'deps', path, modules_name)
      collect_unit_info_list.append(name_unit_map)
      collect_unit_info_list.append(srcs_unit_map)
      collect_unit_info_list.append(hdrs_unit_map)
      collect_unit_info_list.append(deps_unit_map)
      collect_info_list.append(collect_unit_info_list)
    return collect_info_list

    
  def GetApolloCompileContent(self, path, modules_name, compile_unit_name):
    build_path = path + "/" + "BUILD" 
    build_path_1 = path + "/" + "BUILD_"
    line_num_conter_build = 0
    line_num_conter_build_ = 0
    start_valid_line_num_build = 0
    start_valid_line_num_build_ = 0
    end_valid_line_num_build = 0
    end_valid_line_num_build_ = 0
    compile_unit_list = []
    compile_unit_content = ""
    proto_compile_content = []
    #key word have name srcs hdrs deps //  cc_library cc_binary
    try:
      with open(build_path, 'r+') as f:
        for line_build in f.readlines():
          build_proto_library_match_condition = line_build.startswith(compile_unit_name)
          if build_proto_library_match_condition:
            start_valid_line_num_build = line_num_conter_build + 1
          if (line_num_conter_build + 1 >= start_valid_line_num_build) and (start_valid_line_num_build != 0):
            build_proto_library_match_end_condition = line_build.startswith(")")
            line_build = line_build.strip()
            line_build = line_build.rstrip(',')
            compile_unit_content += line_build
            if build_proto_library_match_end_condition:
              compile_unit_list.append(compile_unit_content)
              compile_unit_content = ""
              start_valid_line_num_build = 0
              end_valid_line_num_build = line_num_conter_build
          line_num_conter_build = line_num_conter_build + 1 
      
    except:
      with open(build_path_1, 'r+') as f1:
        for line_build_ in f1:
          build1_proto_library_match_condition = line_build_.startswith(compile_unit_name)
          if build1_proto_library_match_condition:
            start_valid_line_num_build_ = line_num_conter_build_ + 1
          if (line_num_conter_build_ + 1 >= start_valid_line_num_build_) and (start_valid_line_num_build_ != 0):
            build_proto_library_match_end_condition_ = line_build_.startswith(")")
            line_build_ = line_build_.strip()
            line_build_ = line_build_.rstrip(',')
            compile_unit_content += line_build_
            if build_proto_library_match_end_condition_:
              compile_unit_list.append(compile_unit_content)
              compile_unit_content = ""
              start_valid_line_num_build_ = 0
              end_valid_line_num_build_ = line_num_conter_build_ 
            line_num_conter_build_ = line_num_conter_build_ + 1
    #print(compile_unit_list)
    proto_compile_content = self.ProcessCompileUnitContent(compile_unit_list, path, modules_name)
    return proto_compile_content
  def CreateRootCmakelistContent(self):
    naruto_apollo_root_path = self.GetNarutoApolloRootPath()
    root_cmakelist = naruto_apollo_root_path + '/CMakeLists.txt'
    sub_cmakelist_list = []
    for root, dirs, files in os.walk(naruto_apollo_root_path, topdown=True):
      for dir in dirs:
        sub_dir = os.path.join(root,dir)
        match_condition_0 = re.search("/naruto_apollo_v7"+ "/"+ 'modules' ,sub_dir)
        match_condition_1 = re.search("/naruto_apollo_v7"+ "/"+ 'cyber' ,sub_dir)
        #match_condition_2 = re.search("proto",sub_dir)
        match_condition_3 = re.search("proto_bundle",sub_dir)
        match_condition_4 = re.search("protocol",sub_dir)
        match_condition_5 = re.search("proto_adapter",sub_dir)
        macht_condition_6 = os.path.exists(sub_dir+'/'+'BUILD')
        macht_condition_7 = os.path.exists(sub_dir+'/'+'BUILD_')
        if (match_condition_0 or match_condition_1)   and (not match_condition_3) and (not match_condition_4) and (not match_condition_5) \
           and (macht_condition_6 or macht_condition_7):
          module_unit_path = os.path.join(root,dir)
          module_unit_path_list = module_unit_path.split('naruto_apollo_v7')
          sub_name = module_unit_path_list[1][1:]
          sub_cmakelist_list.append(sub_name)
    cmakelist_info = \
 '''#******************************************************************************
# Root CMake configuration file for naruto_apollo project
#
# Put here only sub-projects includes, global config options,
# target configuration, toolchain selection and so on.
#
# Copyright: dingjiangang 2022
# All Rights Reserved
#
# This file is part of NarutoApollo Application
# It is not a good case for this project, in the future, i will change it by a
# standard approach.
#******************************************************************************
'''
    cmakelist_color_info = \
'''
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()
'''
    common_option_info = \
'''
message("${Green} [info] naruto_apollo cmakelist ${ColourReset}")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -fPIC  -pthread -mavx -march=native ")
option(BUILD_SHARED_LIBS "build as shared library" ON)
include_directories($ENV{NARUTO_APOLLO_ROOT})
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
include($ENV{TOOL_BASE_PATH}/../cmake/fastrtps.cmake)
include($ENV{TOOL_BASE_PATH}/../cmake/fastcdr.cmake)
include($ENV{TOOL_BASE_PATH}/../cmake/gflags.cmake)
include($ENV{TOOL_BASE_PATH}/../cmake/glog.cmake)
set(Python_INLCUDE_DIRS $ENV{TOOL_BASE_PATH}/Python-3.9.5/include/python3.9)
include_directories(${Python_INLCUDE_DIRS})

#system lib search
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
find_package(CUDA REQUIRED)
'''
    set_compile_module_switch = \
'''
set(CyberCompile 1)
set(ModulesCompile 1)
'''
    with open(root_cmakelist, 'w+') as f:
      f.write(cmakelist_info)  
      f.write('cmake_minimum_required(VERSION 3.16)')  
      f.write('\n')
      f.write('project(naruto_apollo  VERSION 1.0.0 LANGUAGES C CXX ASM)')
      f.write('\n')
      f.write(cmakelist_color_info)
      f.write('\n')
      f.write(common_option_info)
      f.write('\n')
      f.write(set_compile_module_switch)
      f.write('\n')
      f.write('#add_sub_modules here')
      f.write('#====================to build cyber====================')
      f.write('\n')
      f.write('if (${CyberCompile})')
      f.write('\n')
      for (i,v) in enumerate(sub_cmakelist_list):
        if v.find('cyber') == 0:
          f.write('  ' + 'add_subdirectory(' + v + ')')
          f.write('\n')
      f.write('endif()')
      f.write('\n')
      f.write('#====================to build apollo modules====================')
      f.write('\n')
      f.write('if (${ModulesCompile})')
      f.write('\n')
      for (m,n) in enumerate(sub_cmakelist_list):
        if n.find('modules') == 0:
          f.write('  ' + 'add_subdirectory(' + n + ')')
          f.write('\n')
      f.write('endif()')
      f.write('\n')
if __name__ == "__main__":
  create_cmakelist = NarutoApolloCreateCmakelist()
  create_cmakelist.Hello()
  create_cmakelist.GetNarutoApolloRootPath()
  create_cmakelist.CreateRootCmakelistContent()
  #cyber and modules
  create_cmakelist.CreateCmakelist("modules") 
  create_cmakelist.CreateCmakelist("cyber")
  

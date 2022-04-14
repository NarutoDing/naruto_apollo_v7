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

class NarutoApolloProtoCreateCmakelist:
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
    for root, dirs, files in os.walk(naruto_apollo_root_path):
      for dir in dirs:
        sub_dir = os.path.join(root,dir)
        match_condition_1 = re.search("/naruto_apollo_v7"+ "/"+ modules_name ,sub_dir)
        match_condition_2 = re.search("proto",sub_dir)
        match_condition_3 = re.search("proto_bundle",sub_dir)
        match_condition_4 = re.search("protocol",sub_dir)
        match_condition_5 = re.search("proto_adapter",sub_dir)
        match_condition_6 = re.search("proto/math",sub_dir)
        match_condition_7 = re.search('host-linux',sub_dir)
        #if match_condition_6:
          #print(sub_dir)
        if modules_name == 'cyber':
          if match_condition_1 and match_condition_2 and (not match_condition_3) and (not match_condition_4) and (not match_condition_5) and (not match_condition_7):
            proto_path = os.path.join(root,dir)
            self.WriteCmakelistInfo(proto_path, modules_name)
        if modules_name == 'modules':
          if ((match_condition_1 and match_condition_2) or  match_condition_6) and (not match_condition_3) and (not match_condition_4) and (not match_condition_5) and (not match_condition_7):
            proto_path = os.path.join(root,dir)
            self.WriteCmakelistInfo(proto_path, modules_name)
  def GetProjectName(self, path, modules_name):
    #print(path, modules_name)
    str_lit = []
    str_lit = path.split('/')
    rest_str_list = str_lit.copy()
    project_name = ""
    for (i,v) in enumerate(str_lit):
      if v == modules_name:
        break
      rest_str_list.remove(v)
    rest_str_list_size = len(rest_str_list)
    #print(rest_str_list)
    for (j,k) in enumerate(rest_str_list):
      project_name += k
      if j == rest_str_list_size - 1:
        break
      project_name += '_'
    #print(project_name)
    return project_name
  def GetProjectNameSpace(self, path, modules_name, dep_name):
    name_space = ""
    cc_string = 'cc_'
    colon_mathc_index = dep_name.find(':')
    double_slash_index = dep_name.find('/')
    if colon_mathc_index == 0:
      str_list = []
      str_list = path.split('/')
      rest_str_list = str_list.copy()
      for (i,v) in enumerate(str_list):
        if v == modules_name:
          break
        rest_str_list.remove(v)
      proto_match_index = dep_name.rfind('proto')
      proto_match_value_name_space = dep_name[1:proto_match_index] + cc_string + 'proto'
      rest_str_list_size = len(rest_str_list)
      for (j,k) in enumerate(rest_str_list):
        name_space += k
        if j == rest_str_list_size - 1:
          break
        name_space += '::'
      name_space = name_space + '::' + proto_match_value_name_space
    #print(name_space)
    if double_slash_index == 0:
      spilt_dep_list = dep_name.split('/')
      spilt_dep_list_copy = spilt_dep_list.copy()
      for (m,n) in enumerate(spilt_dep_list):
        if n == "":
          spilt_dep_list_copy.remove(n)
      last_dep_split_list = spilt_dep_list_copy[-1].split(':')
      last_proto_match_index = last_dep_split_list[1].rfind('proto')
      last_proto_match_value_name_space = last_dep_split_list[1][0:last_proto_match_index] + cc_string + 'proto'
      
      spilt_dep_list_copy_length = len(spilt_dep_list_copy)
      for (x,y) in enumerate(spilt_dep_list_copy):
        name_space += y
        name_space += '::'
        if x == spilt_dep_list_copy_length - 2:
          break
      #print(name_space, last_dep_split_list[0],last_proto_match_value_name_space)
      name_space = name_space + last_dep_split_list[0] + '::' + last_proto_match_value_name_space
      
    #print(name_space)
    return name_space
  def GetAliasName(self, path, library_name):
    library_name_space = ''
    cc_string = 'cc_'
    middle_path_list = path.split('naruto_apollo_v7')
    pre_lib_path_list = middle_path_list[1].split('/')
    for (i,v) in enumerate(pre_lib_path_list):
      if i >= 1:
        library_name_space += v
        library_name_space += '::'
    proto_match_index = library_name.rfind('proto')
    proto_match_value_name_space = library_name[0:proto_match_index] + cc_string + 'proto'
    library_name_space += proto_match_value_name_space
    return library_name_space
    #print(library_name_space)
    #print(pre_lib_path_list)
  def WriteCmakelistInfo(self, path, modules_name):
    cc_string = 'cc_'
    cc_format = 'pb.cc'
    GetProtoCompileContent = []
    middle_path = path.split('naruto_apollo_v7')
    del middle_path[0]
    cmakelist_path = path + "/" + "CMakeLists.txt"
    project_name = self.GetProjectName(path, modules_name)
    print(cmakelist_path)
    GetProtoCompileContent = self.GetProtoCompileContent(path, modules_name)
    #print(GetProtoCompileContent)
    name_space = ''
    with open(cmakelist_path,'w+') as f:
      f.write('cmake_minimum_required(VERSION 3.16)') 
      f.write('\n')
      cmakelist_project_name = 'project' + '(' + project_name + ')'
      #print(cmakelist_project_name)
      f.write('\n')
      f.write(cmakelist_project_name)
      f.write('\n')
      f.write('message'+'(' + "\"" + '${Green}' + ' [info] ' + project_name + ' cmakelist ' + '${ColourReset}' + "\"" + ')')
      f.write('\n')
      f.write("include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)")
      f.write('\n')
      f.write("file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}" + middle_path[0] + '/*.proto)')
      f.write('\n')
      f.write('list(LENGTH  proto_files  length)')
      f.write('\n')
      f.write('if(${length} GREATER 0)')
      f.write('\n')
      f.write('  ' + 'naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})')
      f.write('\n')
      f.write('endif()')
      f.write('\n')
      f.write('\n')
      for (i,v) in enumerate(GetProtoCompileContent):
        #add_library(cyber_proto_topology_change_cc_proto SHARED
        library_name = v[0]['name'][0]
        proto_index = library_name.rfind('proto')
        add_library_name = project_name + '_' + library_name[0:proto_index] + cc_string + 'proto'
        f.write("add_library(" + add_library_name + '  SHARED')
        f.write('\n')
        srcs_name = v[1]['srcs']
        for (j,c) in enumerate(srcs_name):
          src_name_index = c.rfind('proto')
          src_name = c[0:src_name_index] + cc_format
          f.write('  ' + src_name)
          f.write('\n')
        f.write(')')
        f.write('\n')
        f.write('set_target_properties(' + add_library_name + '  PROPERTIES LINKER_LANGUAGE CXX)')
        f.write('\n')
        
        deps_name = v[2]['deps']
        if deps_name != []:
          f.write('target_link_libraries(' + add_library_name)
          f.write('\n')
          for (m,n) in enumerate(deps_name):
            name_space = self.GetProjectNameSpace(path, modules_name, n)
            #print(name_space)
            f.write('  ' + name_space)
            f.write('\n')
          f.write(')')
        f.write('\n')
        library_name_space = self.GetAliasName(path, library_name)
        f.write('add_library(' + library_name_space +  '  ALIAS  ' + ' ' +  add_library_name + ')')
        #add_library(cyber::proto::topology_change_cc_proto ALIAS cyber_topology_change_cc_proto)
        f.write('\n')
        f.write('\n')
        #target_link_libraries
        
        #print(i,v)
  def GetMapContent(self, content, head):
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
      #print(content_list)
      for (i,v) in enumerate(content_list):
        if v.rfind('proto') != -1:
          srcs_value_list.append(v)
      map_unit[head] = srcs_value_list
      return map_unit
    elif head == 'deps':
      deps_value_list = []
      
      content_list = content.split('"')
      #print(content_list)
      for (i,v) in enumerate(content_list):
        value_index = v.rfind('proto')
        if value_index != -1:
          temp_value = v[:value_index + 5]
          deps_value_list.append(temp_value)
      map_unit[head] = deps_value_list
      #print(map_unit)
      return map_unit
    
  def ProcessCompileUnitContent(self, compile_unit_list):
    collect_info_list = []
    name_unit_map = dict()
    srcs_unit_map = dict()
    deps_unit_map = dict()
    for (i,v) in enumerate(compile_unit_list):
      collect_unit_info_list = []
      compile_unit = re.findall(r'[(](.*?)[)]', v)[0]
      name_position_index = compile_unit.find('name')
      srcs_position_index = compile_unit.find('srcs')
      deps_position_index = compile_unit.find('deps')
      name_content = compile_unit[name_position_index:srcs_position_index]
      srcs_content = compile_unit[srcs_position_index:deps_position_index]
      deps_content = compile_unit[deps_position_index:]
      name_unit_map = self.GetMapContent(name_content, 'name')
      srcs_unit_map = self.GetMapContent(srcs_content, 'srcs')
      deps_unit_map = self.GetMapContent(deps_content, 'deps')
      collect_unit_info_list.append(name_unit_map)
      collect_unit_info_list.append(srcs_unit_map)
      collect_unit_info_list.append(deps_unit_map)
      #print(name_unit_map, srcs_unit_map, deps_unit_map)
      #print(collect_unit_info_list)
      collect_info_list.append(collect_unit_info_list)
    return collect_info_list

    
  def GetProtoCompileContent(self, path, modeles_name):
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
    try:
      with open(build_path, 'r+') as f:
        for line_build in f.readlines():
          build_proto_library_match_condition = line_build.startswith("proto_library")
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
          build1_proto_library_match_condition = line_build_.startswith("proto_library")
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
    proto_compile_content = self.ProcessCompileUnitContent(compile_unit_list)
    return proto_compile_content
          


if __name__ == "__main__":
  create_cmakelist = NarutoApolloProtoCreateCmakelist()
  create_cmakelist.Hello()
  create_cmakelist.GetNarutoApolloRootPath()
  #cyber and modules
  create_cmakelist.CreateCmakelist("modules") 
  create_cmakelist.CreateCmakelist("cyber")
  

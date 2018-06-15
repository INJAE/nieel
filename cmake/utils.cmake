function(subdirectory_list_f result target_dir)
    file(GLOB children RELATIVE ${target_dir} ${target_dir}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${target_dir}/${child})
            subdirectory_list_f(dirlist ${target_dir}/${child})
            list(APPEND dirlist ${target_dir}/${child})
            #message("${dirlist}")
        endif()
    endforeach()
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction()

function(subdirectory_list result target_dir)
    file(GLOB children RELATIVE ${target_dir} ${target_dir}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${target_dir}/${child})
            get_subdirectory_list(dirlist ${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction()

function(file_list result_ target_dir_)
    file(GLOB files ${target_dir_}/*)
    set(filelist "")
    foreach(file_ ${files})
        if(NOT IS_DIRECTORY ${file_}) 
            list(APPEND filelist ${file_})
        endif()
    endforeach()
    set(${result_} ${filelist} PARENT_SCOPE)
endfunction()

macro(get_third_party_list)
    file(GLOB_RECURSE find_file "${MODULE_PATH}/*.cmake")
    FOREACH(file ${find_file})
        include(${file})
    ENDFOREACH()
endmacro()
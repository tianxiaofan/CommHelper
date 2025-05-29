# 使用说明
# # ts文件所在路径，qm文件也在这个路径下
# set(all_ts_root
# ${CMAKE_CURRENT_SOURCE_DIR}/translations
# )
# # 翻译文件
# set(proj_ts_file
#     ${CMAKE_CURRENT_SOURCE_DIR}/translations/tugs_zh_CN.ts
#     ${CMAKE_CURRENT_SOURCE_DIR}/translations/tugs_jp.ts
# )

# # 指定要翻译哪些文件夹
# set(project_translate_root
# ${CMAKE_CURRENT_SOURCE_DIR}/src
# )


# include(carete_qm_update_ts)

# # 添加翻译
# CREATE_QM_UPDATE_TS(TARGET_NAME ${PROJECT_NAME}
# TS_ROOT ${all_ts_root}
# ALL_TS_FILE ${proj_ts_file}
# ALL_TRANSLATE_ROOT ${project_translate_root}
# )

# i18N
function(CREATE_QM_UPDATE_TS)
    set(option)
    # TARGET_NAME-项目名称
    set(oneValueArgs TS_ROOT TARGET_NAME)
    # ALL_TS_FILE-所有文件
    # ALL_TRANSLATE_ROOT-要翻译哪些文件夹下的源码文件
    set(multiValueArgs ALL_TS_FILE ALL_TRANSLATE_ROOT)
    # 固定写法
    cmake_parse_arguments(TS_QM "${option}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
    # 查找Qt目录
    get_filename_component(qt_bin_dir ${QT_MOC_EXECUTABLE} DIRECTORY)

    set(update_all_ts_files ${WHICH_PROJECT_NAME}_UPDATE_ALL_TS)
    set(create_all_qm_files ${WHICH_PROJECT_NAME}_CREATE_QM_FILE)

    add_custom_target(${update_all_ts_files} ALL)
    add_custom_target(${create_all_qm_files} ALL)

    # 手动查找翻译需要的程序
    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        find_file(LUPDATE_PATH lupdate ${qt_bin_dir})
        find_file(LRELEASE_PATH lrelease ${qt_bin_dir})
    elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
        find_file(LUPDATE_PATH lupdate.exe ${qt_bin_dir})
        find_file(LRELEASE_PATH lrelease.exe ${qt_bin_dir})
    endif()

    # 把Ts文件提取出来
    foreach(TS_FILE ${TS_QM_ALL_TS_FILE})
        # 得到文件名
        get_filename_component(LOCAL_LANGUAGE_NAME ${TS_FILE} NAME_WE)
        # 指定TS项目名称
        set(TS_TARGET_NAME "${WHICH_PROJECT_NAME}_UPATE_TS_${LOCAL_LANGUAGE_NAME}")
        # 用于更新项目文件中的翻译
        add_custom_target(${TS_TARGET_NAME} COMMAND ${LUPDATE_PATH} ${TS_QM_ALL_TRANSLATE_ROOT} -ts ${TS_FILE} VERBATIM)

        # 将 update_ts_file_<name>添加到update_all_ts_file项目的依赖
        add_dependencies(${update_all_ts_files} ${TS_TARGET_NAME})
        # 准备qm文件
        set(QM_TARGET_NAME "${WHICH_PROJECT_NAME}_CREATE_QM_${LOCAL_LANGUAGE_NAME}")
        set(QM_FILE "${TS_QM_TS_ROOT}/${LOCAL_LANGUAGE_NAME}.qm")

        # qm文件转换
        add_custom_target(${QM_TARGET_NAME} COMMAND ${LRELEASE_PATH} ${TS_FILE} -qm ${QM_FILE} VERBATIM)

        # 因为须先有TS文件，才能生成qm文件
        add_dependencies(${QM_TARGET_NAME} ${TS_TARGET_NAME})
        add_dependencies(${create_all_qm_files} ${QM_TARGET_NAME})

        SET_PROPERTY(TARGET ${create_all_qm_files} PROPERTY FOLDER "LANGUAGE")
        SET_PROPERTY(TARGET ${QM_TARGET_NAME} PROPERTY FOLDER "LANGUAGE")
        SET_PROPERTY(TARGET ${update_all_ts_files} PROPERTY FOLDER "LANGUAGE")
        SET_PROPERTY(TARGET ${TS_TARGET_NAME} PROPERTY FOLDER "LANGUAGE")

    endforeach(TS_FILE ${TS_QM_ALL_TS_FILE})

    IF (NOT ${WHICH_PROJECT_NAME})
    add_dependencies(${WHICH_PROJECT_NAME} ${QM_TARGET_NAME})
    ENDIF()

endfunction()

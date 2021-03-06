file(GLOB HEADERS "include/sophiatx/plugins/custom_tokens/*.hpp")

add_library(custom_tokens_plugin SHARED
            custom_tokens_plugin.cpp
            custom_tokens_api.cpp
            custom_tokens_plugin_export.cpp
           )

target_link_libraries(custom_tokens_plugin chain_plugin sophiatx_chain sophiatx_protocol sophiatx_utilities json_rpc_plugin)

target_include_directories(custom_tokens_plugin PUBLIC "include")

if (CLANG_TIDY_EXE)
    set_target_properties(
            custom_tokens_plugin PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif (CLANG_TIDY_EXE)

install(TARGETS
        custom_tokens_plugin

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
